/*
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "BattlePetMgr.h"
#include "ByteBuffer.h"
#include "DatabaseEnv.h"
#include "DB2Enums.h"
#include "DB2Stores.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "WorldPacket.h"
#include "WorldSession.h"

BattlePetMgr::~BattlePetMgr()
{
    for (auto &battlePet : BattlePets)
        delete battlePet;

    BattlePets.clear();
}

void BattlePetMgr::LoadFromDb(PreparedQueryResult result)
{
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint64 id            = fields[0].GetUInt64();
        uint16 speciesId     = fields[1].GetUInt16();
        std::string nickname = fields[2].GetString();
        uint32 timestamp     = fields[3].GetUInt32();
        uint8 level          = fields[4].GetUInt8();
        uint16 xp            = fields[5].GetUInt16();
        uint16 health        = fields[6].GetUInt16();
        uint8 quality        = fields[7].GetUInt8();
        uint8 breedId        = fields[8].GetUInt8();
        uint16 flags         = fields[9].GetUInt16();

        // check if battle pet species exists
        auto battlePetSpeciesEntry = sBattlePetSpeciesStore.LookupEntry(speciesId);
        if (!battlePetSpeciesEntry)
        {
            sLog->outError(LOG_FILTER_SQL, "Species %u defined in `account_battle_pet` for Battle Pet " UI64FMTD "  does not exist, skipped!",
                speciesId, id);
            continue;
        }

        // check if battle pet breed is valid
        if (breedId > BATTLE_PET_MAX_BREED)
        {
			sLog->outError(LOG_FILTER_SQL, "Breed %u defined in `account_battle_pet` for Battle Pet " UI64FMTD " is not valid, skipped!",
                breedId, id);
            continue;
        }

        // client supports up to legendary quality but currently players can not obtain legendary pets
        if (quality > ITEM_QUALITY_LEGENDARY)
        {
			sLog->outError(LOG_FILTER_SQL, "Quality %u defined in `account_battle_pet` for Battle Pet " UI64FMTD " is invalid, skipped!",
                quality, id);
            continue;
        }

        // softcap, client supports up to level 255
        if (level > BATTLE_PET_MAX_LEVEL)
        {
			sLog->outError(LOG_FILTER_SQL, "Level %u defined in `account_battle_pet` for Battle Pet " UI64FMTD " is invalid, skipped!",
                quality, id);
            continue;
        }

        BattlePet* battlePet = new BattlePet(id, speciesId, battlePetSpeciesEntry->FamilyId,
            nickname, timestamp, level, xp, health, quality, breedId, flags, m_owner);

        battlePet->InitialiseAbilities(false);

        BattlePets.insert(battlePet);
    } while (result->NextRow());
}

void BattlePetMgr::SaveToDb(SQLTransaction& trans)
{
    // save slots to database before battle pets
    SaveSlotsToDb(trans);

    // player has no battle pets, no need to save
    if (BattlePets.empty())
        return;

    auto battlePetItr = BattlePets.begin();
    while (battlePetItr != BattlePets.end())
    {
        BattlePet* battlePet = *battlePetItr++;
        if (!battlePet)
            return;

        switch (battlePet->GetDbState())
        {
            // remove any pending battle pets from memory and database
            case BATTLE_PET_DB_STATE_DELETE:
            {
                PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_ACCOUNT_BATTLE_PET);
                stmt->setUInt32(0, m_owner->GetSession()->GetAccountId());
                stmt->setUInt64(1, battlePet->GetId());
                trans->Append(stmt);

                BattlePets.erase(battlePet);
                delete battlePet;

                break;
            }
            // save any pending battle pets to the database
            case BATTLE_PET_DB_STATE_SAVE:
            {
                PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_DEL_ACCOUNT_BATTLE_PET);
                stmt->setUInt32(0, m_owner->GetSession()->GetAccountId());
                stmt->setUInt64(1, battlePet->GetId());
                trans->Append(stmt);

                stmt = CharacterDatabase.GetPreparedStatement(LOGIN_INS_ACCOUNT_BATTLE_PET);
                stmt->setUInt32(0, m_owner->GetSession()->GetAccountId());
                stmt->setUInt64(1, battlePet->GetId());
                stmt->setUInt16(2, battlePet->GetSpecies());
                stmt->setString(3, battlePet->GetNickname());
                stmt->setUInt32(4, battlePet->GetTimestamp());
                stmt->setUInt8 (5, battlePet->GetLevel());
                stmt->setUInt16(6, battlePet->GetXp());
                stmt->setUInt16(7, battlePet->GetCurrentHealth());
                stmt->setUInt8 (8, battlePet->GetQuality());
                stmt->setUInt8 (9, battlePet->GetBreed());
                stmt->setUInt16(10, battlePet->GetFlags());
                trans->Append(stmt);

                battlePet->SetDbState(BATTLE_PET_DB_STATE_NONE);
                break;

            }
            // no changes have been made to the battle pet, no need to save
            case BATTLE_PET_DB_STATE_NONE:
            default:
                break;
        }
    }
}

void BattlePetMgr::LoadSlotsFromDb(PreparedQueryResult result)
{
    if (!result)
        return;

    Field* fields = result->Fetch();
    m_loadoutFlags = fields[3].GetUInt8();

    // update flag and spell state for new account characters
    if (m_loadoutFlags != BATTLE_PET_LOADOUT_SLOT_FLAG_NONE
        && !m_owner->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_BATTLE_PET))
    {
        m_owner->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_BATTLE_PET);

        m_owner->learnSpell(SPELL_BATTLE_PET_TRAINING, false);
        m_owner->learnSpell(SPELL_TRACK_PETS, false);
        m_owner->learnSpell(SPELL_REVIVE_BATTLE_PETS, false);

        // flag character to learn Battle Pet Training passive on add to map
        m_pendingPassive = true;
    }

    // 3 minute cooldown on login for Revive Battle Pets (125439)
    uint32 cooldownRemaining = m_owner->GetRemainingSpellCooldown(SPELL_REVIVE_BATTLE_PETS);
    if (!cooldownRemaining || cooldownRemaining < 3 * 60 * IN_MILLISECONDS)
        m_owner->AddSpellCooldown(SPELL_REVIVE_BATTLE_PETS, 0, 3 * 60 * IN_MILLISECONDS);

    for (uint8 i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; i++)
    {
        uint64 id = fields[i].GetUInt64();
        if ((!HasLoadoutSlot(i) || !GetBattlePet(id)) && id != 0)
        {
            sLog->outError(LOG_FILTER_SQL, "Battle Pet slot %u in `account_battle_pet_slots` for account %u is invalid!",
                i, m_owner->GetSession()->GetAccountId());

            // error occured, reset loadout slot and flag for database save
            SetLoadoutSlot(i, 0, true);
        }
        else
            SetLoadoutSlot(i, id, false);
    }
}

void BattlePetMgr::SaveSlotsToDb(SQLTransaction& trans)
{
    // no changes have been made to the loadout slots, no need to save
    if (!m_loadoutSave)
        return;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(LOGIN_DEL_ACCOUNT_BATTLE_PET_SLOTS);
    stmt->setUInt32(0, m_owner->GetSession()->GetAccountId());
    trans->Append(stmt);

    // save loadout slots to database
    stmt = CharacterDatabase.GetPreparedStatement(LOGIN_INS_ACCOUNT_BATTLE_PET_SLOTS);
    stmt->setUInt32(0, m_owner->GetSession()->GetAccountId());
    stmt->setUInt64(1, GetLoadoutSlot(BATTLE_PET_LOADOUT_SLOT_1));
    stmt->setUInt64(2, GetLoadoutSlot(BATTLE_PET_LOADOUT_SLOT_2));
    stmt->setUInt64(3, GetLoadoutSlot(BATTLE_PET_LOADOUT_SLOT_3));
    stmt->setUInt8 (4, m_loadoutFlags);
    trans->Append(stmt);

    m_loadoutSave = false;
}

uint8 BattlePetMgr::GetLoadoutSlotForBattlePet(uint64 id) const
{
    for (uint8 i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; i++)
        if (GetLoadoutSlot(i) == id)
            return i;

    return BATTLE_PET_LOADOUT_SLOT_NONE;
}

void BattlePetMgr::UnlockLoadoutSlot(uint8 slot)
{
    if (HasLoadoutSlot(slot))
        return;

    if (slot >= BATTLE_PET_MAX_LOADOUT_SLOTS)
        return;

    switch (slot)
    {
        case BATTLE_PET_LOADOUT_SLOT_1:
            SetLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_1);
            break;
        // unlock both second slot and trap
        case BATTLE_PET_LOADOUT_SLOT_2:
            SetLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_2);
            SetLoadoutFlag(BATTLE_PET_LOADOUT_TRAP);
            break;
        case BATTLE_PET_LOADOUT_SLOT_3:
            SetLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_3);
            break;
    }

    SetLoadoutSlot(slot, 0, true);

    // alert client of new loadout slot
    SendPetBattleSlotUpdate(true);
}

void BattlePetMgr::SetLoadoutSlot(uint8 slot, uint64 guid, bool save)
{
    if (!HasLoadoutSlot(slot))
        return;

    m_loadout[slot] = guid;

    if (save)
        m_loadoutSave = true;
}


uint64 BattlePetMgr::GetLoadoutSlot(uint8 slot) const
{
    if (!HasLoadoutSlot(slot))
        return 0;

    return m_loadout[slot];
}

bool BattlePetMgr::HasLoadoutSlot(uint8 slot) const
{
    if (!m_loadoutFlags)
        return false;

    switch (slot)
    {
        case BATTLE_PET_LOADOUT_SLOT_1:
            return HasLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_1);
        case BATTLE_PET_LOADOUT_SLOT_2:
            return HasLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_2);
        case BATTLE_PET_LOADOUT_SLOT_3:
            return HasLoadoutFlag(BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_3);
    }

    return false;
}

void BattlePetMgr::SetLoadoutFlag(uint8 flag)
{
    if (HasLoadoutFlag(flag))
        return;

    m_loadoutFlags |= flag;
    m_loadoutSave = true;
}

bool BattlePetMgr::CanStoreBattlePet(uint16 species) const
{
    // check if battle pet species exists
    auto battlePetEntry = sBattlePetSpeciesStore.LookupEntry(species);
    if (!battlePetEntry)
        return false;

    // player is only allowed a maximum of 500 battle pets
    if (BattlePets.size() > BATTLE_PET_MAX_JOURNAL_PETS)
        return false;

    // player is only allowed 3 of each battle pet unless it has BATTLE_PET_FLAG_UNIQUE flag
    uint8 speciesCount = GetBattlePetCount(species);
    if (HasBattlePetSpeciesFlag(species, BATTLE_PET_FLAG_UNIQUE) && speciesCount >= 1)
        return false;

    if (speciesCount >= BATTLE_PET_MAX_JOURNAL_SPECIES)
        return false;

    return true;
}

#define BATTLE_PET_ABILITY_TRAP          427
#define BATTLE_PET_ABILITY_STRONG_TRAP   77
#define BATTLE_PET_ABILITY_PRISTINE_TRAP 135
#define BATTLE_PET_ABILITY_GM_TRAP       549

uint32 BattlePetMgr::GetTrapAbility() const
{
    if (HasLoadoutFlag(BATTLE_PET_LOADOUT_TRAP))
        return BATTLE_PET_ABILITY_TRAP;
    if (HasLoadoutFlag(BATTLE_PET_LOADOUT_STRONG_TRAP))
        return BATTLE_PET_ABILITY_STRONG_TRAP;
    if (HasLoadoutFlag(BATTLE_PET_LOADOUT_PRISTINE_TRAP))
        return BATTLE_PET_ABILITY_PRISTINE_TRAP;
    if (HasLoadoutFlag(BATTLE_PET_LOADOUT_GM_TRAP))
        return BATTLE_PET_ABILITY_GM_TRAP;

    return 0;
}

void BattlePetMgr::Create(uint16 speciesId, uint8 level, uint8 breed, uint8 quality, bool ignoreChecks)
{
    // make sure player can store more battle pets
    if (!CanStoreBattlePet(speciesId) && !ignoreChecks)
        return;

    auto battlePetEntry = sBattlePetSpeciesStore.LookupEntry(speciesId);
    ASSERT(battlePetEntry);

    // create and add battle pet to player
    uint64 id = sObjectMgr->GenerateBattlePetId();

    if (!breed)
        breed = sObjectMgr->BattlePetGetRandomBreed(speciesId);

    if (!quality)
        quality = sObjectMgr->BattlePetGetRandomQuality(speciesId);

    BattlePet* battlePet = new BattlePet(id, speciesId, battlePetEntry->FamilyId, level, quality, breed, m_owner);
    battlePet->InitialiseAbilities(false);

    BattlePets.insert(battlePet);

    // notify client of the new battle pet
    SendBattlePetUpdate(battlePet, true);
}

void BattlePetMgr::Delete(BattlePet* battlePet)
{
    if (!battlePet)
        return;

    if (battlePet->GetDbState() == BATTLE_PET_DB_STATE_DELETE)
        return;

    // this shouldn't happen since the client doesn't allow releasing of slotted Battle Pets
    uint8 srcSlot = GetLoadoutSlotForBattlePet(battlePet->GetId());
    if (srcSlot != BATTLE_PET_LOADOUT_SLOT_NONE)
    {
        SetLoadoutSlot(srcSlot, 0, true);
        SendPetBattleSlotUpdate(false);
    }

    battlePet->SetDbState(BATTLE_PET_DB_STATE_DELETE);
}

BattlePet* BattlePetMgr::GetBattlePet(uint64 id) const
{
    for (auto battlePet : BattlePets)
        if (battlePet->GetId() == id)
            return battlePet;

    return nullptr;
}

// returns the amount of battle pets the player has of a single species
uint8 BattlePetMgr::GetBattlePetCount(uint16 speciesId) const
{
    uint8 counter = 0;
    for (auto const &battlePet : BattlePets)
        if (battlePet->GetSpecies() == speciesId)
            counter++;

    return counter;
}

void BattlePetMgr::UnSummonCurrentBattlePet(bool temporary)
{
    if (!m_summon || !m_summonId)
        return;

    // store summon id for temporary removal
    m_summonLastId = temporary ? m_summonId : 0;
    m_summonId = 0;

    // remove summoned battle pet from the world
    m_summon->UnSummon();

    m_summon = NULL;
}

void BattlePetMgr::ResummonLastBattlePet()
{
    if (!m_summonLastId)
        return;

    if (!m_owner->isAlive())
        return;

    // resummon battle pet into the world
    m_summonId = m_summonLastId;
    m_owner->CastSpell(m_owner, GetBattlePetSummonSpell(GetBattlePet(m_summonId)->GetSpecies()), true);
    m_summonLastId = 0;
}

void BattlePetMgr::SendBattlePetJournal()
{
    uint32 petCount = 0;
    ByteBuffer journalData, loadoutData;

    WorldPacket data(SMSG_BATTLEPET_JOURNAL, 6 + 2 + BattlePets.size() * (1 + 8 + 2 + 4 + 4 + 4 + 4 +
        4 + 4 + 2 + 2 + 4 + 1 + 2 + 16) + BATTLE_PET_MAX_LOADOUT_SLOTS * (1 + 8 + 1 + 1));

    size_t countPos = data.bitwpos();
    data.WriteBits(petCount, 19);

    for (auto const &battlePet : BattlePets)
    {
        if (battlePet->GetDbState() == BATTLE_PET_DB_STATE_DELETE)
            continue;

        ObjectGuid petEntry = battlePet->GetId();

        data.WriteBitSeq<7>(petEntry);
        data.WriteBit(!battlePet->GetQuality());
        data.WriteBitSeq<3, 5, 1, 6>(petEntry);
        data.WriteBit(false);                       // NoRename
        data.WriteBit(!battlePet->GetBreed());
        data.WriteBit(!battlePet->GetFlags());
        data.WriteBit(false);                       // OwnerInfo
        data.WriteBits(battlePet->GetNickname().size(), 7);
        data.WriteBitSeq<0, 2, 4>(petEntry);

        journalData << uint16(battlePet->GetLevel());
        journalData.WriteByteSeq<7>(petEntry);
        journalData << uint32(battlePet->GetCurrentHealth());
        journalData << uint32(battlePet->GetSpecies());
        journalData << uint32(battlePet->GetSpeed());
        journalData << uint32(battlePet->GetPower());
        journalData << uint32(battlePet->GetMaxHealth());
        journalData.WriteByteSeq<6>(petEntry);
        journalData << uint32(battlePet->GetNpc());
        journalData.WriteByteSeq<4, 2, 3, 0>(petEntry);

        if (uint16 flags = battlePet->GetFlags())
            journalData << uint16(flags);

        if (uint16 breed = battlePet->GetBreed())
            journalData << uint16(breed);

        journalData << uint32(battlePet->GetDisplayId());

        if (uint8 quality = battlePet->GetQuality())
            journalData << uint8(quality);

        journalData << uint16(battlePet->GetXp());
        journalData.WriteByteSeq<1, 5>(petEntry);
        journalData.WriteString(battlePet->GetNickname());

        petCount++;
    }

    data.WriteBit(1);                               // HasJournalLock
    data.WriteBits(BATTLE_PET_MAX_LOADOUT_SLOTS, 25);

    for (uint8 i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; i++)
    {
        ObjectGuid loadoutEntry = GetLoadoutSlot(i);

        data.WriteBit(0);                           // HasSlotIndex
        data.WriteBit(!HasLoadoutSlot(i));
        data.WriteBit(1);                           // HasCollarId
        data.WriteBit(0);
        data.WriteBitSeq<1, 4, 5, 6, 0, 2, 3, 7>(loadoutEntry);

        loadoutData.WriteByteSeq<2, 1, 3, 6, 7, 4, 5, 0>(loadoutEntry);
        loadoutData << uint8(i);
        // loadoutData << uint32(collarId);
    }

    data.FlushBits();
    data.PutBits(countPos, petCount, 19);

    data.append(loadoutData);
    data.append(journalData);
    data << uint16(0);                              // TrapLevel

    m_owner->GetSession()->SendPacket(&data);
}

void BattlePetMgr::SendBattlePetUpdate(BattlePet* battlePet, bool notification)
{
    if (!battlePet)
        return;

    CreatureTemplate const* creatureTemplate = sObjectMgr->GetCreatureTemplate(sBattlePetSpeciesStore.LookupEntry(battlePet->GetSpecies())->NpcId);
    if (!creatureTemplate)
        return;

    ObjectGuid petEntry = battlePet->GetId();

    WorldPacket data(SMSG_BATTLEPET_UPDATE, 1 + 8 + 4 + 4 + 4 + 1 + 4 + 4 + 4 + 2 + 4 + 2 + 16 + 2 + 4 + 1);
    data.WriteBits(1, 19);
    data.WriteBit(false);                           // NoRename
    data.WriteBitSeq<0>(petEntry);
    data.WriteBit(!battlePet->GetQuality());
    data.WriteBitSeq<4>(petEntry);
    data.WriteBit(!battlePet->GetFlags());
    data.WriteBitSeq<7, 2, 1>(petEntry);
    data.WriteBit(false);                           // OwnerInfo
    data.WriteBits(battlePet->GetNickname().size(), 7);
    data.WriteBitSeq<5, 6, 3>(petEntry);
    data.WriteBit(!battlePet->GetBreed());
    data.WriteBit(notification);
    data.FlushBits();

    data << uint32(creatureTemplate->Modelid1);
    data.WriteByteSeq<1>(petEntry);
    data << uint32(battlePet->GetCurrentHealth());
    data << uint16(battlePet->GetLevel());
    data << uint32(battlePet->GetSpeed());
    data.WriteByteSeq<7>(petEntry);
    data << uint32(battlePet->GetMaxHealth());
    data << uint32(creatureTemplate->Entry);
    data << uint16(battlePet->GetXp());
    data.WriteByteSeq<0, 4, 6>(petEntry);
    data << uint32(battlePet->GetSpecies());
    data.WriteByteSeq<3, 2>(petEntry);

    if (uint16 breed = battlePet->GetBreed())
        data << uint16(breed);

    data.WriteByteSeq<5>(petEntry);
    data.WriteString(battlePet->GetNickname());

    if (uint16 flags = battlePet->GetFlags())
        data << uint16(flags);

    data << uint32(battlePet->GetPower());

    if (uint8 quality = battlePet->GetQuality())
        data << uint8(quality);

    m_owner->GetSession()->SendPacket(&data);
}

void BattlePetMgr::SendPetBattleSlotUpdate(bool notification)
{
    ByteBuffer loadoutData;

    WorldPacket data(SMSG_PET_BATTLE_SLOT_UPDATE, 4 + BATTLE_PET_MAX_LOADOUT_SLOTS * (1 + 8 + 1));
    data.WriteBits(BATTLE_PET_MAX_LOADOUT_SLOTS, 25);
    data.WriteBit(notification);
    data.WriteBit(0);                                           // AutoSlotted

    for (uint8 i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; i++)
    {
        ObjectGuid petEntry = GetLoadoutSlot(i);

        data.WriteBit(0);
        data.WriteBit(1);                                       // HasCollarId
        data.WriteBitSeq<3, 1, 5, 4, 6, 2, 7, 0>(petEntry);
        data.WriteBit(0);                                       // HasSlotIndex
        data.WriteBit(!HasLoadoutSlot(i));

        //data << uint32(collarId);
        loadoutData.WriteByteSeq<3, 7, 6, 2, 1, 5, 4, 0>(petEntry);
        loadoutData << uint8(i);
    }

    data.FlushBits();
    data.append(loadoutData);

    m_owner->GetSession()->SendPacket(&data);
}

