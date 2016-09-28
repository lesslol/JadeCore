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

#ifndef __TRINITY_BATTLEPETMGR_H
#define __TRINITY_BATTLEPETMGR_H

#include <map>
#include <string>

#include "Common.h"
#include <ace/Singleton.h>
#include "DatabaseEnv.h"
#include "DBCEnums.h"
#include "DBCStores.h"
#include "DB2Stores.h"

#ifndef BATTLE_PET_MGR_H
#define BATTLE_PET_MGR_H

#include "BattlePet.h"
#include "Common.h"
#include "TemporarySummon.h"

typedef std::set<BattlePet*> BattlePetSet;

#define BATTLE_PET_MAX_JOURNAL_SPECIES 3
#define BATTLE_PET_MAX_JOURNAL_PETS    500
#define BATTLE_PET_MAX_LOADOUT_SLOTS   3

#define BATTLE_PET_TRIGGER_NPC         40721

enum BattlePetLoadoutSlots
{
	BATTLE_PET_LOADOUT_SLOT_1 = 0,
	BATTLE_PET_LOADOUT_SLOT_2 = 1,
	BATTLE_PET_LOADOUT_SLOT_3 = 2,
	BATTLE_PET_LOADOUT_SLOT_NONE = 3,
};

// custom flags used in 'account_battle_pet_slots' table
enum BattlePetLoadoutFlags
{
	BATTLE_PET_LOADOUT_SLOT_FLAG_NONE = 0x00,
	BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_1 = 0x01,
	BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_2 = 0x02,
	BATTLE_PET_LOADOUT_SLOT_FLAG_SLOT_3 = 0x04,
	BATTLE_PET_LOADOUT_TRAP = 0x08,
	BATTLE_PET_LOADOUT_STRONG_TRAP = 0x10,
	BATTLE_PET_LOADOUT_PRISTINE_TRAP = 0x20,
	BATTLE_PET_LOADOUT_GM_TRAP = 0x40
};

enum BattlePetJournalFlags
{
	BATTLE_PET_JOURNAL_FLAG_NONE = 0x00,
	BATTLE_PET_JOURNAL_FLAG_FAVORITES = 0x01,
	BATTLE_PET_JOURNAL_FLAG_COLLECTED = 0x02,
	BATTLE_PET_JOURNAL_FLAG_NOT_COLLECTED = 0x04,
	BATTLE_PET_JOURNAL_FLAG_UNKNOWN_1 = 0x08,
	BATTLE_PET_JOURNAL_FLAG_ABILITY_1 = 0x10, // ability flags are set if the second ability for that slot is selected
	BATTLE_PET_JOURNAL_FLAG_ABILITY_2 = 0x20, // ...
	BATTLE_PET_JOURNAL_FLAG_ABILITY_3 = 0x40  // ...
};

enum BattlePetSpells
{
	SPELL_BATTLE_PET_SUMMON = 118301,
	SPELL_BATTLE_PET_TRAINING_PASSIVE = 119467,
	SPELL_BATTLE_PET_TRAINING = 125610,
	SPELL_TRACK_PETS = 122026,
	SPELL_REVIVE_BATTLE_PETS = 125439
};

class BattlePetMgr
{
public:
	BattlePetMgr(Player* owner)
		: m_owner(owner), m_summon(NULL), m_summonId(0), m_summonLastId(0), m_loadoutFlags(0),
		m_loadoutSave(false), m_pendingPassive(false) { }

	~BattlePetMgr();

	void LoadFromDb(PreparedQueryResult result);
	void SaveToDb(SQLTransaction& trans);
	void LoadSlotsFromDb(PreparedQueryResult result);
	void SaveSlotsToDb(SQLTransaction& trans);

	void Create(uint16 speciesId, uint8 level = 1, uint8 breed = 0, uint8 quality = 0, bool ignoreChecks = false);
	void Delete(BattlePet* battlePet);

	Player* GetOwner() const { return m_owner; }
	uint8 GetBattlePetCount(uint16 speciesId) const;
	BattlePet* GetBattlePet(uint64 id) const;
	uint8 GetLoadoutSlotForBattlePet(uint64 id) const;

	uint64 GetCurrentSummonId() const { return m_summonId; }
	TempSummon* GetCurrentSummon() const { return m_summon; }
	void SetCurrentSummonId(uint64 summonId) { m_summonId = summonId; }
	void SetCurrentSummon(TempSummon* summon) { m_summon = summon; }

	bool HasLoadoutSlot(uint8 slot) const;
	uint64 GetLoadoutSlot(uint8 slot) const;
	void SetLoadoutSlot(uint8 slot, uint64 guid, bool save);
	void UnlockLoadoutSlot(uint8 slot);

	bool HasLoadoutFlag(uint8 flag) const { return (m_loadoutFlags & flag) != 0; };
	void SetLoadoutFlag(uint8 flag);

	bool CanStoreBattlePet(uint16 species) const;
	uint32 GetTrapAbility() const;

	bool HasPendingPassiveLearn() const { return m_pendingPassive; }

	void UnSummonCurrentBattlePet(bool temporary);
	void ResummonLastBattlePet();

	void SendBattlePetJournal();
	void SendBattlePetUpdate(BattlePet* battlePet, bool notification);
	void SendPetBattleSlotUpdate(bool notification);

	BattlePetSet BattlePets;

private:
	Player* m_owner;

	TempSummon* m_summon;
	uint64 m_summonId;
	uint64 m_summonLastId;

	bool m_loadoutSave;
	uint8 m_loadoutFlags;
	uint64 m_loadout[BATTLE_PET_MAX_LOADOUT_SLOTS];

	bool m_pendingPassive;
};

#endif

#endif