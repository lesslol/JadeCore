
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Util.h"
#pragma once

enum eFilterEffectResult
{
    FILTER_EFFECT_RESULT_NONE = 0,
    FILTER_EFFECT_RESULT_AURA_SPECIFIC,
    FILTER_EFFECT_RESULT_CREATURE_ONLY,
    FILTER_EFFECT_RESULT_PLAYER_ONLY,
};

///< A list that takes all of them from db and checks if in list spell memory has the following checkcast results
enum eCheckCastResult
{
    CHECK_CAST_RESULT_NONE = 0,
    CHECK_CAST_RESULT_AURA_SPECIFIC,
    CHECK_CAST_RESULT_AURA_MISSING_FROM_CASTER,
    CHECK_CAST_RESULT_AURA_MISSING_FROM_TARGET,
    CHECK_CAST_RESULT_ITEM_MISSING_FROM_CASTER,
    CHECK_CAST_RESULT_BEHIND_ONLY,
    CHECK_CAST_RESULT_INFRONT_ONLY,
    CHECK_CAST_RESULT_STEALTH_ONLY,
    CHECK_CAST_RESULT_WATER_ONLY,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_WARRIOR,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_PALADIN,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_DEATHKNIGHT,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_MONK,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_MAGE,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_WARLOCK,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_PRIEST,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_ROUGE,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_DRUID,
    CHECK_CAST_RESULT_CLASS_SPECIFIC_SHAMAN,
    CHECK_CAST_RESULT_MOUNTED_ONLY,
    CHECK_CAST_RESULT_MOUNTED_NON,
    CHECK_CAST_RESULT_RANGELIMIT_5,
    CHECK_CAST_RESULT_RANGELIMIT_10,
    CHECK_CAST_RESULT_RANGELIMIT_20,
    CHECK_CAST_RESULT_RANGELIMIT_30,
    CHECK_CAST_RESULT_RANGELIMIT_50,
    CHECK_CAST_RESULT_RANGELIMIT_100,
    CHECK_CAST_RESULT_RANGELIMIT_5000,
    CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_85,
    CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_65,
    CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_45,
    CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_25,
    CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_10,
    CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_85,
    CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_65,
    CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_45,
    CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_25,
    CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_10,
    CHECK_CAST_PLAYERS_ONLY,
    CHECK_CAST_CREATURES_ONLY,
};

enum eSpellStatusFlags
{
    FILTER_SPELL_ENABLED = 0,
    FILTER_SPELL_DISABLED = 1,
    FILTER_SPELL_DISABLED_SECURITY,
};

enum eManualTargets
{
    MANUAL_TARGETS_DBC = 0,
    MANUAL_TARGETS_MANUAL = 1,
    MANUAL_TARGETS_MANUAL_CASTER = 2,
    MANUAL_TARGETS_MANUAL_AOE_FRIENDLY = 3,
    MANUAL_TARGETS_MANUAL_AOE_HOSTILE = 4,
    MANUAL_TARGETS_MANUAL_CASTER_TARGET = 5,
    MANUAL_TARGETS_MANUAL_PET_TARGET = 6,

    MANUALTARGETS_ENUM_SIZE
};

enum eHookSelections
{
    // Spells
    HOOK_SELECTION_CAST_AFTER = 0,
    HOOK_SELECTION_CAST_ON,
    HOOK_SELECTION_HIT_ON,
    HOOK_SELECTION_HIT_AFTER,
    HOOK_SELECTION_APPLY_ON,
    HOOK_SELECTION_DUMMY_AFTER,

    // Auras
    HOOK_SELECTION_APPLY_AFTER,
    HOOK_SELECTION_REMOVE_ON,
    HOOK_SELECTION_REMOVE_AFTER,
    HOOK_SELECTION_PERIODIC,
};

enum eConsumptionSelections
{
    // Aura
    CONSUMED_AURA_ID = 1,

    // Power
    CONSUMED_MANA,
    CONSUMED_RAGE,
    CONSUMED_ENERGY,
    CONSUMED_HEALTH,
    CONSUMED_SPELL_CD,

    // Deffects
    CONSUMED_APPLY_DEBUFF_UPON,
};

#define MAX_CHECK_CAST_FLAGS 40

/*
Parameters explained:

p_EffIndentifier = EFF INDENTFIER
P_Info   = SPELL INFO
*/

class FilterCheckTypeIdPlayerOnly
{
public:
    FilterCheckTypeIdPlayerOnly() {}

    bool operator()(WorldObject* object)
    {
        if (object->GetTypeId() == TYPEID_PLAYER)
            return false;
        else
            return true;
    }
};

class FilterCheckTypeIdCreatureOnly
{
public:
    FilterCheckTypeIdCreatureOnly() {}

    bool operator()(WorldObject* object)
    {
        if (object->GetTypeId() != TYPEID_PLAYER)
            return false;
        else
            return true;
    }
};

void ChangeFromDbc(const SpellInfo* p_Info)
{
    if (p_Info)
    {
        SpellInfo* l_Spell = const_cast<SpellInfo*>(p_Info);

        if (!l_Spell)
            return;

        // Load then loop through stmt rows and load them inside a list, then return the list to main function.
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_HARD_VALUES);
        stmt->setUInt32(0, p_Info->Id);
        PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

        std::list<uint32> l_listRows;

        if (spell_result)
        {
            Field* l_Field = spell_result->Fetch();

            // AttEx
            uint32 l_AttEx =  l_Field[1].GetUInt32();
            uint32 l_AttEx2 = l_Field[2].GetUInt32();
            uint32 l_AttEx3 = l_Field[3].GetUInt32();
            uint32 l_AttEx4 = l_Field[4].GetUInt32();
            uint32 l_AttEx5 = l_Field[5].GetUInt32();
            uint32 l_AttEx6 = l_Field[6].GetUInt32();
            uint32 l_AttEx7 = l_Field[7].GetUInt32();
            uint32 l_AttEx8 = l_Field[8].GetUInt32();
            uint32 l_AttEx9 = l_Field[9].GetUInt32();

            // Dispel Type
            uint32 l_DispelType = l_Field[10].GetUInt32();

            // Base points
            uint32 effect_0_basepoints = l_Field[11].GetUInt32();
            uint32 effect_1_basepoints = l_Field[12].GetUInt32();
            uint32 effect_2_basepoints = l_Field[13].GetUInt32();
            uint32 effect_3_basepoints = l_Field[14].GetUInt32();
            uint32 effect_4_basepoints = l_Field[15].GetUInt32();
            // Misc values
            uint32 effect_0_misc_a = l_Field[16].GetUInt32();
            uint32 effect_0_misc_b = l_Field[17].GetUInt32();
            uint32 effect_1_misc_a = l_Field[18].GetUInt32();
            uint32 effect_1_misc_b = l_Field[19].GetUInt32();
            uint32 effect_2_misc_a = l_Field[20].GetUInt32();
            uint32 effect_2_misc_b = l_Field[21].GetUInt32();
            uint32 effect_3_misc_a = l_Field[22].GetUInt32();
            uint32 effect_3_misc_b = l_Field[23].GetUInt32();
            uint32 effect_4_misc_a = l_Field[24].GetUInt32();
            uint32 effect_4_misc_b = l_Field[25].GetUInt32();
            uint32 effect_0_target_a = l_Field[26].GetUInt32();
            uint32 effect_0_target_b = l_Field[27].GetUInt32();
            uint32 effect_1_target_a = l_Field[28].GetUInt32();
            uint32 effect_1_target_b = l_Field[29].GetUInt32();
            uint32 effect_2_target_a = l_Field[30].GetUInt32();
            uint32 effect_2_target_b = l_Field[31].GetUInt32();
            uint32 effect_3_target_a = l_Field[32].GetUInt32();
            uint32 effect_3_target_b = l_Field[33].GetUInt32();
            uint32 effect_4_target_a = l_Field[34].GetUInt32();
            uint32 effect_4_target_b = l_Field[35].GetUInt32();
            uint32 effect_0_effect_type = l_Field[36].GetUInt32();
            uint32 effect_1_effect_type = l_Field[37].GetUInt32();
            uint32 effect_2_effect_type = l_Field[38].GetUInt32();
            uint32 effect_3_effect_type = l_Field[39].GetUInt32();
            uint32 effect_4_effect_type = l_Field[40].GetUInt32();

            // Attributes                       
            if (l_AttEx > 1)
            l_Spell->AttributesEx = l_AttEx;
            if (l_AttEx2 > 1)
            l_Spell->AttributesEx2 = l_AttEx2;
            if (l_AttEx3 > 1)
            l_Spell->AttributesEx3 = l_AttEx3;
            if (l_AttEx4 > 1)
            l_Spell->AttributesEx4 = l_AttEx4;
            if (l_AttEx5 > 1)
            l_Spell->AttributesEx5 = l_AttEx5;
            if (l_AttEx6 > 1)
            l_Spell->AttributesEx6 = l_AttEx6;
            if (l_AttEx7 > 1)
            l_Spell->AttributesEx7 = l_AttEx7;
            if (l_AttEx8 > 1)
            l_Spell->AttributesEx8 = l_AttEx8;
            if (l_AttEx9 > 1)
            l_Spell->AttributesEx9 = l_AttEx9;

            if (l_DispelType > 1)
            l_Spell->Dispel = l_DispelType;

            if (effect_0_basepoints > 1)
                l_Spell->Effects[0].BasePoints = effect_0_basepoints;
            if (effect_1_basepoints > 1);
            l_Spell->Effects[1].BasePoints = effect_1_basepoints;
            if (effect_2_basepoints > 1)
            l_Spell->Effects[2].BasePoints = effect_2_basepoints;
            if (effect_3_basepoints > 1)
            l_Spell->Effects[3].BasePoints = effect_3_basepoints;
            if (effect_4_basepoints > 1)
            l_Spell->Effects[4].BasePoints = effect_4_basepoints;
            if (effect_0_misc_a > 1)
            l_Spell->Effects[0].MiscValue = effect_0_misc_a;
            if (effect_0_misc_b > 1)
            l_Spell->Effects[0].MiscValueB = effect_0_misc_b;
            if (effect_1_misc_a > 1)
            l_Spell->Effects[1].MiscValue = effect_1_misc_a;
            if (effect_1_misc_b > 1)
            l_Spell->Effects[1].MiscValueB = effect_1_misc_b;
            if (effect_2_misc_a > 1)
            l_Spell->Effects[2].MiscValue = effect_2_misc_a;
            if (effect_2_misc_b > 1)
            l_Spell->Effects[2].MiscValueB = effect_2_misc_b;
            if (effect_3_misc_a > 1)
            l_Spell->Effects[3].MiscValue = effect_3_misc_a;
            if (effect_3_misc_b > 1)
            l_Spell->Effects[3].MiscValueB = effect_3_misc_b;
            if (effect_4_misc_a > 1)
            l_Spell->Effects[4].MiscValue = effect_4_misc_a;
            if (effect_4_misc_b > 1)
            l_Spell->Effects[4].MiscValueB = effect_4_misc_b;

            if (effect_0_target_a > 1)
            l_Spell->Effects[0].TargetA = effect_0_target_a;
            if (effect_0_target_b > 1)
            l_Spell->Effects[0].TargetB = effect_0_target_b;
            if (effect_1_target_a > 1)
            l_Spell->Effects[1].TargetA = effect_1_target_a;
            if (effect_1_target_b> 1)
            l_Spell->Effects[1].TargetB = effect_1_target_b;
            if (effect_2_target_a > 1)
            l_Spell->Effects[2].TargetA = effect_2_target_a;
            if (effect_2_target_b > 1)
            l_Spell->Effects[2].TargetB = effect_2_target_b;
            if (effect_3_target_a > 1)
            l_Spell->Effects[3].TargetA = effect_3_target_a;
            if (effect_3_target_b > 1)
            l_Spell->Effects[3].TargetB = effect_3_target_b;
            if (effect_4_target_a > 1)
            l_Spell->Effects[4].TargetA = effect_4_target_a;
            if (effect_4_target_b > 1)
            l_Spell->Effects[4].TargetB = effect_4_target_b;
            if (effect_0_effect_type > 1)
            l_Spell->Effects[0].Effect = effect_0_effect_type;
            if (effect_1_effect_type > 1)
            l_Spell->Effects[1].Effect = effect_1_effect_type;
            if (effect_2_effect_type > 1)
            l_Spell->Effects[2].Effect = effect_2_effect_type;
            if (effect_3_effect_type > 1)
            l_Spell->Effects[3].Effect = effect_3_effect_type;
            if (effect_4_effect_type > 1)
            l_Spell->Effects[4].Effect = effect_4_effect_type;
        }
    }
}

int32 CheckSpellHook(int32 p_EffIndentifier, const SpellInfo* p_Info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT);
    stmt->setUInt32(0, p_Info->Id);
    stmt->setUInt32(1, p_EffIndentifier);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int8 EffectType = field[2].GetInt8();

        return EffectType;
    }
}

std::list<uint32> GetAllIndentifiers(const SpellInfo* p_Info)
{
    printf("func");

    std::list<uint32> l_listRows;
    // Load then loop through stmt rows and load them inside a list, then return the list to main function.
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT_NON_INDENTIFIERS);
    stmt->setUInt32(0, p_Info->Id);
    PreparedQueryResult l_Result = CharacterDatabase.Query(stmt);

    printf("stmt");
    
    if (l_Result)
    {
        uint32 count = 0;

        do
        {
            printf("allident");

            Field* l_Field = l_Result->Fetch();
            uint8 l_Indetifier = l_Field[1].GetUInt8();

            l_listRows.push_back(l_Indetifier);
        } while (l_Result->NextRow());

        printf("rowempty");

        if (!l_listRows.empty())
        return l_listRows;

        printf("rows num: %u", count);
    }
}

bool CheckSpellRequirement(int32 p_EffIndentifier, Player* player, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT);
    stmt->setUInt32(0, info->Id);
    stmt->setUInt32(1, p_EffIndentifier);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        uint32 talentId = field[3].GetUInt32();

        if (player->HasSpell(talentId))
            return true;
    }

    return false;
}

int32 ReturnSpellId(int32 p_EffIndentifier, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT);
    stmt->setUInt32(0, info->Id);
    stmt->setUInt32(1, p_EffIndentifier);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        uint32 l_SpellIdBonus = field[4].GetUInt32();

        return l_SpellIdBonus;
    }

    return 0;
}

int32 ReturnSpellChance(int32 p_EffIndentifier, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT);
    stmt->setUInt32(0, info->Id);
    stmt->setUInt32(1, p_EffIndentifier);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        uint32 Chance = field[6].GetUInt32();

        return Chance;
    }

    return 0;
}

int32 ReturnSpellRadius(int32 p_EffIndentifier, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_EFFECT);
    stmt->setUInt32(0, info->Id);
    stmt->setUInt32(1, p_EffIndentifier);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 Radius = field[7].GetInt32();

        return Radius;
    }

    return 0;
}


std::list<uint64> ReturnSpellBonusTargetsGUID(int32 p_EffIndentifier, Unit* p_Caster, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    std::list<uint64> l_ListTempGUID;

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int8 spell_bonus_targets = field[5].GetInt8();

        switch (spell_bonus_targets)
        {
        case eManualTargets::MANUAL_TARGETS_MANUAL_CASTER:
        {
            if (p_Caster)
                l_ListTempGUID.push_back(p_Caster->GetGUID());
            break;
        }
        case eManualTargets::MANUAL_TARGETS_MANUAL_CASTER_TARGET:
        {
            if (p_Caster->getVictim())
                l_ListTempGUID.push_back(p_Caster->getVictim()->GetGUID());
            break;
        }
        case eManualTargets::MANUAL_TARGETS_MANUAL_AOE_HOSTILE:
        {
            UnitList l_Targets;
            JadeCore::AnyUnfriendlyUnitInObjectRangeCheck u_check(p_Caster, p_Caster, ReturnSpellRadius(p_EffIndentifier, info));
            JadeCore::UnitListSearcher<JadeCore::AnyUnfriendlyUnitInObjectRangeCheck> searcher(p_Caster, l_Targets, u_check);
            p_Caster->VisitNearbyObject(ReturnSpellRadius(p_EffIndentifier, info), searcher);

            if (!l_Targets.empty())
            {
                for (UnitList::iterator iter = l_Targets.begin(); iter != l_Targets.end(); ++iter)
                {
                    if ((*iter) && (*iter)->IsInWorld())
                        l_ListTempGUID.push_back((*iter)->GetGUID());
                }
            }
            break;
        }
        case eManualTargets::MANUAL_TARGETS_MANUAL_AOE_FRIENDLY:
        {
            UnitList l_Targets;
            JadeCore::AnyFriendlyUnitInObjectRangeCheck u_check(p_Caster, p_Caster, ReturnSpellRadius(p_EffIndentifier, info));
            JadeCore::UnitListSearcher<JadeCore::AnyFriendlyUnitInObjectRangeCheck> searcher(p_Caster, l_Targets, u_check);
            p_Caster->VisitNearbyObject(ReturnSpellRadius(p_EffIndentifier, info), searcher);

            if (!l_Targets.empty())
            {
                for (UnitList::iterator iter = l_Targets.begin(); iter != l_Targets.end(); ++iter)
                {
                    if ((*iter) && (*iter)->IsInWorld())
                        l_ListTempGUID.push_back((*iter)->GetGUID());
                }
            }
            break;
        }
        }

        return l_ListTempGUID;

        l_ListTempGUID.clear();
    }
}


int32 ReturnSpellCooldown(const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 l_CooldownTimer = field[8].GetInt32();

        return l_CooldownTimer;
    }

    return 0;
}

void CheckSpellEffectFilter(Unit* p_Caster, std::list<WorldObject*>& unitList, const SpellInfo* p_Info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM);
    stmt->setUInt32(0, p_Info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int8 Indetifier = field[4].GetInt32();

        switch (Indetifier)
        {
        case eFilterEffectResult::FILTER_EFFECT_RESULT_CREATURE_ONLY:
            unitList.remove_if(FilterCheckTypeIdCreatureOnly());
            break;
        case eFilterEffectResult::FILTER_EFFECT_RESULT_PLAYER_ONLY:
            unitList.remove_if(FilterCheckTypeIdPlayerOnly());
            break;
        case eFilterEffectResult::FILTER_EFFECT_RESULT_NONE:
            return;
            break;
        }
    }

    return;
}

bool ReturnSpellFlagStatus(Unit* p_Caster, const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 l_StatusFlag = field[1].GetInt32();

        switch (l_StatusFlag)
        {
        case eSpellStatusFlags::FILTER_SPELL_DISABLED:
        {
            if (p_Caster->GetTypeId() == TYPEID_PLAYER)
                ChatHandler(p_Caster->ToPlayer()->GetSession()).PSendSysMessage("This spell is currently disabled.");
            return false;
            break;
        }
        case eSpellStatusFlags::FILTER_SPELL_DISABLED_SECURITY:
        {
            if (p_Caster->GetTypeId() == TYPEID_PLAYER)
                if (p_Caster->ToPlayer()->GetSession()->GetSecurity() <= 0)
                    return false;
            break;
        }
        default:
            break;
        }

        return true;
    }

    return true;
}

int32 ReturnSpellGlobalCooldown(const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 l_GlobalCooldownTimer = field[9].GetInt32();

        return l_GlobalCooldownTimer;
    }

    return 0;
}

bool ReturnCheckCastTemplateId(const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_CHECKCAST);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 l_CheckCastTemplateId = field[2].GetInt32();

        if (l_CheckCastTemplateId > 0)
            return l_CheckCastTemplateId;
    }

    return false;
}

bool ReturnConsumptionTableId(const SpellInfo* info)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_CHECKCAST);
    stmt->setUInt32(0, info->Id);
    PreparedQueryResult spell_result = CharacterDatabase.Query(stmt);

    if (spell_result)
    {
        Field* field = spell_result->Fetch();
        int32 l_CheckCastTemplateId = field[3].GetInt32();

        if (l_CheckCastTemplateId > 0)
            return l_CheckCastTemplateId;
    }

    return false;
}
