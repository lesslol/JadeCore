#include "Customized_Ability_System.h"

/*
TODO:

creating finished alpha template for smartspellscripting - > Check V
modifying tables to a general and specific effects, right now it's combined - this is bad. -> Check V
modifying getallindetifier logic to allow me to take indetifiers from tables
finish the hard_values for bool load
adding consumption cpp part
finishing all other tables cpp part
*/

/// Manual cooldown remover
class manual_basic_cooldown_remover : public BasicEvent
{
public:
    explicit manual_basic_cooldown_remover(uint32 p_Guid, int p_Value) : m_Obj(p_Guid), m_Modifier(p_Value) { }

    bool Execute(uint64 p_CurrTime, uint32 p_Diff)
    {
        if (m_Obj != NULL)
        {
            if (Player* l_Player = sObjectMgr->GetPlayerByLowGUID(m_Obj))
            {
                l_Player->RemoveSpellCooldown(m_Modifier, true);
            }
        }

        return true;
    }

private:
    uint32 m_Obj;
    int m_Modifier;
};

class spell_automatic_spell_mechanism : public SpellScriptLoader
{
public:
    spell_automatic_spell_mechanism() : SpellScriptLoader("spell_automatic_spell_mechanism") { }

    class spell_automatic_spell_mechanism_spell_Script : public SpellScript
    {
        PrepareSpellScript(spell_automatic_spell_mechanism_spell_Script);

        bool Load()
        {
            if (!GetSpellInfo())
                return false;

            ChangeFromDbc(GetSpellInfo());
        }

        void HandleCooldownAndConsumption()
        {
            if (GetCaster() && GetCaster()->GetTypeId() == TypeID::TYPEID_PLAYER)
            {
                Unit* l_Caster = GetCaster();

                if (GetSpellInfo())
                {
                    // Spell cooldown
                    if (ReturnSpellCooldown(GetSpellInfo()) > 0)
                    {
                        /// TrinityCore Handling
                        //l_Caster->ToPlayer()->GetSpellHistory()->AddCooldown(newInfo->Id, 0, std::chrono::seconds(ReturnSpellCooldown(newInfo)));

                        l_Caster->m_Events.AddEvent(new manual_basic_cooldown_remover(l_Caster->ToPlayer()->GetGUIDLow(), GetSpellInfo()->Id), l_Caster->m_Events.CalculateTime(ReturnSpellCooldown(GetSpellInfo()) * TimeConstants::IN_MILLISECONDS));

                        /// Mists of Pandaria Handling
                        l_Caster->ToPlayer()->AddSpellCooldown(GetSpellInfo()->Id, 0, uint32(time(NULL) + ReturnSpellCooldown(GetSpellInfo())));
                    }

                    // Global cooldown
                    if (ReturnSpellGlobalCooldown(GetSpellInfo()) > 0)
                    {
                        /// JadeCore Core Handling - Wrath of The Lich King
                        //l_Caster->ToPlayer()->GetSpellHistory()->AddGlobalCooldown(newInfo, ReturnSpellGlobalCooldown(newInfo));

                        /// Mists of Pandaria Handling
                        l_Caster->ToPlayer()->AddSpellCooldown(GetSpellInfo()->Id, 0, ReturnSpellGlobalCooldown(GetSpellInfo()));
                    }


                    // Handles Consumption table
                    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_CONSUMPTIONTEMPLATEID);

                    if (ReturnConsumptionTableId(GetSpellInfo()))
                    {
                        stmt->setUInt32(0, ReturnConsumptionTableId(GetSpellInfo()));
                        PreparedQueryResult l_ConsumptionResult = CharacterDatabase.Query(stmt);

                        if (l_ConsumptionResult)
                        {
                            Field* field = l_ConsumptionResult->Fetch();

                            // 0 = the id of the checkcast template, so it's skipped
                            for (int i = 1; i <= 5; i++)
                            {
                                uint32 l_Consumption = field[i].GetUInt32();

                                if (field[i].GetUInt32() >= 1)
                                {
                                    switch (i)
                                    {
                                    case eConsumptionSelections::CONSUMED_AURA_ID:
                                        if (l_Caster->HasAura(l_Consumption))
                                        {
                                            AuraPtr l_Aura = l_Caster->GetAura(l_Consumption);

                                            if (l_Aura)
                                            {
                                                if (l_Aura->GetStackAmount() > 1)
                                                {
                                                    l_Aura->SetStackAmount(l_Aura->GetStackAmount() - 1);
                                                }
                                                else
                                                    l_Caster->RemoveAura(l_Consumption);
                                            }
                                        }
                                        break;
                                    case eConsumptionSelections::CONSUMED_MANA:
                                        if (l_Caster->GetPower(POWER_MANA))
                                            l_Caster->SetPower(POWER_MANA, l_Caster->GetPower(POWER_MANA) - l_Consumption, true);
                                        break;
                                    case eConsumptionSelections::CONSUMED_ENERGY:
                                        if (l_Caster->GetPower(POWER_ENERGY))
                                            l_Caster->SetPower(POWER_ENERGY, l_Caster->GetPower(POWER_ENERGY) - l_Consumption, true);
                                        break;
                                    case eConsumptionSelections::CONSUMED_RAGE:
                                        if (l_Caster->GetPower(POWER_RAGE))
                                            l_Caster->SetPower(POWER_RAGE, l_Caster->GetPower(POWER_RAGE) - l_Consumption, true);
                                        break;
                                    case eConsumptionSelections::CONSUMED_HEALTH:
                                        if (l_Caster->GetHealth())
                                            l_Caster->SetHealth(l_Caster->GetHealth() - l_Consumption);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
   
        SpellCastResult CheckCast()
        {
            if (Unit* l_Caster = GetCaster())
            {
                if (GetSpellInfo())
                {
                    /// Spell Flag Status
                    if (!ReturnSpellFlagStatus(l_Caster, GetSpellInfo()))
                        return SPELL_FAILED_DONT_REPORT;

                    // Handles Consumption table
                    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_CONSUMPTIONTEMPLATEID);

                    if (ReturnConsumptionTableId(GetSpellInfo()) >= 1)
                    {
                        stmt->setUInt32(0, ReturnConsumptionTableId(GetSpellInfo()));
                        PreparedQueryResult l_ConsumptionResult = CharacterDatabase.Query(stmt);

                        if (l_ConsumptionResult)
                        {
                            Field* field = l_ConsumptionResult->Fetch();

                            // 0 = the id of the checkcast template, so it's skipped
                            for (int i = 1; i <= 6; i++)
                            {
                                uint32 l_Consumption = field[i].GetUInt32();

                                if (field[i].GetUInt32() >= 1)
                                {
                                    switch (i)
                                    {
                                    case eConsumptionSelections::CONSUMED_AURA_ID:
                                        if (!l_Caster->HasAura(l_Consumption))
                                            return SPELL_FAILED_DONT_REPORT;
                                        break;
                                    case eConsumptionSelections::CONSUMED_MANA:
                                        if (l_Caster->GetPower(POWER_MANA) < l_Consumption)
                                            return SPELL_FAILED_DONT_REPORT;
                                        break;
                                    case eConsumptionSelections::CONSUMED_ENERGY:
                                        if (l_Caster->GetPower(POWER_ENERGY) < l_Consumption)
                                            return SPELL_FAILED_DONT_REPORT;
                                        break;
                                    case eConsumptionSelections::CONSUMED_HEALTH:
                                        if (l_Caster->GetHealth() < l_Consumption)
                                            return SPELL_FAILED_DONT_REPORT;
                                        break;
                                    case eConsumptionSelections::CONSUMED_SPELL_CD:
                                        if (const SpellInfo* p_Info = sSpellMgr->GetSpellInfo(l_Consumption))
                                        {
                                            if (l_Caster->GetTypeId() != TYPEID_PLAYER)
                                                return SPELL_FAILED_DONT_REPORT;

                                            if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->HasSpellCooldown(l_Consumption))
                                                return SPELL_FAILED_DONT_REPORT;

                                            else if (!l_Caster->ToPlayer()->HasSpellCooldown(l_Consumption))
                                            {
                                                l_Caster->ToPlayer()->AddSpellCooldown(l_Consumption, 0, time(NULL) + p_Info->RecoveryTime);
                                            }
                                        }
                                        break;
                                    case eConsumptionSelections::CONSUMED_APPLY_DEBUFF_UPON:
                                        if (const SpellInfo* p_Info = sSpellMgr->GetSpellInfo(l_Consumption))
                                        {
                                            if (l_Caster && l_Caster->isAlive())
                                                l_Caster->AddAura(l_Consumption, l_Caster);
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    if (ReturnCheckCastTemplateId(GetSpellInfo()) >= 1)
                    {                    
                        // Next, load any items that were saved
                        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CUSTOMIZED_ABILITY_SYSTEM_CHECKCASTTEMPLATEID);
                        stmt->setUInt32(0, GetSpellInfo()->Id);
                        stmt->setUInt32(1, ReturnCheckCastTemplateId(GetSpellInfo()));
                        PreparedQueryResult l_CheckCastResult = CharacterDatabase.Query(stmt);

                        if (l_CheckCastResult)
                        {
                            Field* field = l_CheckCastResult->Fetch();

                            // 0 = the id of the checkcast template, so it's skipped
                            for (int i = 1; i <= 38; i++)
                            {
                                uint32 l_Entry = field[i].GetUInt32();

                                if (l_Entry == 1)
                                {
                                    switch (i)
                                    {
                                        // Class specific
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_DEATHKNIGHT:
                                        if (l_Caster->getClass() != CLASS_DEATH_KNIGHT)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Death Knight only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_WARRIOR:
                                        if (l_Caster->getClass() != CLASS_WARRIOR)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Warrior only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_MAGE:
                                        if (l_Caster->getClass() != CLASS_MAGE)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Mage only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_PALADIN:
                                        if (l_Caster->getClass() != CLASS_PALADIN)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Paladin only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_WARLOCK:
                                        if (l_Caster->getClass() != CLASS_WARLOCK)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Warlock only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_ROUGE:
                                        if (l_Caster->getClass() != CLASS_ROGUE)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Rogue only");
                                        break;
                                        /*
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_MONK:       // Uncomment if above MOP patch.
                                    if (l_Caster->getClass() != CLASS_MONK)

                                    return SPELL_FAILED_DONT_REPORT;

                                    if (l_Caster->ToPlayer())
                                    ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Monk only");
                                    break;
                                    */
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_DRUID:
                                        if (l_Caster->getClass() != CLASS_DRUID)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Druid only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_SHAMAN:
                                        if (l_Caster->getClass() != CLASS_SHAMAN)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Shaman only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_CLASS_SPECIFIC_PRIEST:
                                        if (l_Caster->getClass() != CLASS_PRIEST)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Class specific: Priest only");
                                        break;
                                        // Type ID
                                    case eCheckCastResult::CHECK_CAST_CREATURES_ONLY:
                                        if (l_Caster->GetTypeId() == TYPEID_PLAYER)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Creatures only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_PLAYERS_ONLY:
                                        if (l_Caster->GetTypeId() != TYPEID_PLAYER)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Players only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_AURA_MISSING_FROM_CASTER:
                                        if (!l_Caster->HasAura(i))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Aura Specific: Aura Missing");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_BEHIND_ONLY:
                                        if (l_Caster->getVictim() && !l_Caster->isInBack(l_Caster->getVictim()))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Orientation Specific: Behind Only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_WATER_ONLY:
                                        if (!l_Caster->IsInWater())
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Water Only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_INFRONT_ONLY:
                                        if (l_Caster->getVictim() && !l_Caster->isInFront(l_Caster->getVictim()))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Infront Only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_STEALTH_ONLY:
                                        if (!l_Caster->HasAuraType(SPELL_AURA_MOD_STEALTH))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Stealth only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_MOUNTED_ONLY:
                                        if (!l_Caster->IsMounted())
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Type Specific: Mounted only");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_ITEM_MISSING_FROM_CASTER:
                                        if (l_Caster->ToPlayer() && !l_Caster->ToPlayer()->HasItemCount(i, 1))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Item Specific: Item Missing");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_85:
                                        if (l_Caster->GetHealthPct() > 85)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Health only below 85%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_65:
                                        if (l_Caster->GetHealthPct() > 65)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Health only below 65%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_45:
                                        if (l_Caster->GetHealthPct() > 45)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Health only below 45%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_25:
                                        if (l_Caster->GetHealthPct() > 25)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Health only below 25%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_CASTER_10:
                                        if (l_Caster->GetHealthPct() > 10)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Health only below 10%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_85:
                                        if (l_Caster->getVictim() && l_Caster->getVictim()->GetHealthPct() > 85)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Target Health only below 85%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_65:
                                        if (l_Caster->getVictim() && l_Caster->getVictim()->GetHealthPct() > 65)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Target Health only below 65%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_45:
                                        if (l_Caster->getVictim() && l_Caster->getVictim()->GetHealthPct() > 45)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Target Health only below 45%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_25:
                                        if (l_Caster->getVictim() && l_Caster->getVictim()->GetHealthPct() > 25)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Target Health only below 25%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_HEALTH_LIMIT_TARGET_10:
                                        if (l_Caster->getVictim() && l_Caster->getVictim()->GetHealthPct() > 10)
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Power Specific: Target Health only below 10%");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_5:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 5))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 5 Maximum");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_10:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 10))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 10 Maximum");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_20:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 20))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 20 Maximum");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_30:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 30))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 30 Maximum");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_50:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 50))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 50 Maximum");
                                        break;
                                    case eCheckCastResult::CHECK_CAST_RESULT_RANGELIMIT_5000:
                                        if (l_Caster->ToPlayer() && l_Caster->ToPlayer()->GetSelectedUnit() && !l_Caster->ToPlayer()->GetSelectedUnit()->IsWithinDistInMap(l_Caster, 5000))
                                            return SPELL_FAILED_DONT_REPORT;

                                        if (l_Caster->ToPlayer())
                                            ChatHandler(l_Caster->ToPlayer()->GetSession()).PSendSysMessage("Range Specific: Range limit 5000 Maximum");
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

                return SPELL_CAST_OK;
            }

            return SPELL_CAST_OK;
        }

        /// Bonus effects
        void HandleHitHooks()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            if (GetSpellInfo())
            {
                if (GetAllIndentifiers(GetSpellInfo()).empty())
                    return;

                for (auto itr : GetAllIndentifiers(GetSpellInfo()))
                {
                    // Chance for the effect ot proc
                    if (roll_chance_i(ReturnSpellChance(itr, GetSpellInfo())))
                    {
                        if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                        {
                            // Check for a spell requirement
                            if (!CheckSpellRequirement(itr, GetCaster()->ToPlayer(), GetSpellInfo()))
                                return;
                        }

                        if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId(itr, GetSpellInfo())))
                        {
                            // Get targets handling for Bonus effect
                            if (ReturnSpellBonusTargetsGUID(itr, GetCaster(), GetSpellInfo()).empty())
                                return;

                            // Loop through targets guid
                            for (auto ite : ReturnSpellBonusTargetsGUID(itr, GetCaster(), GetSpellInfo()))
                            {
                                if (Unit* l_Unit = sObjectAccessor->GetUnit(*GetCaster(), ite))
                                {
                                    GetCaster()->CastSpell(l_Unit, newInfo->Id, true);
                                }
                            }

                            HandleCooldownAndConsumption();
                        }
                    }
                }
            }
        }

        void HandleCastHooks()
        {
                if (!GetCaster())
                    return;

                if (GetSpellInfo())
                {
                    if (GetAllIndentifiers(GetSpellInfo()).empty())
                        return;

                    for (auto itr : GetAllIndentifiers(GetSpellInfo()))
                    {
                        if (CheckSpellHook(itr, GetSpellInfo()) == eHookSelections::HOOK_SELECTION_CAST_AFTER || CheckSpellHook(itr, GetSpellInfo()) == eHookSelections::HOOK_SELECTION_CAST_ON)
                        {
                            if (roll_chance_i(ReturnSpellChance(itr, GetSpellInfo())))
                            {
                                if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
                                {
                                    // Check for a spell requirement
                                    if (!CheckSpellRequirement(itr, GetCaster()->ToPlayer(), GetSpellInfo()))
                                        return;
                                }

                                if (const SpellInfo* newInfo = sSpellMgr->GetSpellInfo(ReturnSpellId(itr, GetSpellInfo())))
                                {
                                    if (ReturnSpellBonusTargetsGUID(itr, GetCaster(), GetSpellInfo()).empty())
                                        return;

                                    for (auto ite : ReturnSpellBonusTargetsGUID(itr, GetCaster(), GetSpellInfo()))
                                    {
                                        if (Unit* l_Unit = sObjectAccessor->GetUnit(*GetCaster(), ite))
                                        {
                                            GetCaster()->CastSpell(l_Unit, newInfo->Id, true);
                                        }
                                    }

                                    HandleCooldownAndConsumption();
                                }
                            }
                        }
                    }
                }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_automatic_spell_mechanism_spell_Script::CheckCast);
            OnCast += SpellCastFn(spell_automatic_spell_mechanism_spell_Script::HandleCastHooks);
            AfterCast += SpellCastFn(spell_automatic_spell_mechanism_spell_Script::HandleCastHooks);
            OnHit += SpellHitFn(spell_automatic_spell_mechanism_spell_Script::HandleHitHooks);
            AfterHit += SpellHitFn(spell_automatic_spell_mechanism_spell_Script::HandleHitHooks);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_automatic_spell_mechanism_spell_Script();
    }
};

void AddSC_customized_ability_system()
{
    new spell_automatic_spell_mechanism();
}
