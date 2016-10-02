/*
* Copyright (C) 2016-20XX JadeCore <https://jadecore.tk/>
* Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "Group.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"  
#include "ScriptedEscortAI.h"

Position position_fishes[10] =
{
    {1377.13f, 430.445f, 259.625f, 6.073042f},
    {1377.39f, 433.498f, 258.581f, 6.026639f},
    {1378.70f, 436.913f, 257.302f, 6.069634f},
    {1379.69f, 439.320f, 256.425f, 6.002878f},
    {1380.43f, 441.691f, 255.591f, 6.032494f},
    {1504.97f, 428.732f, 260.156f, 3.375731f},
    {1504.99f, 434.240f, 258.287f, 3.285412f},
    {1503.18f, 438.124f, 256.905f, 3.375733f},
    {1502.40f, 439.633f, 256.367f, 3.438565f},
    {1501.92f, 442.107f, 255.545f, 3.462126f},
};
Position position_fishes_fallen_pool_tender_1st[5] =
{
    {1414.53f, 497.657f, 246.884f, 0.669453f},
    {1411.31f, 502.096f, 246.882f, 0.763953f},
    {1411.10f, 507.700f, 246.882f, 0.034953f},
    {1412.48f, 513.044f, 246.888f, 0.007924f},
    {1413.71f, 516.612f, 246.891f, 5.895080f},
};
Position position_fishes_fallen_pool_tender_2st[5] =
{
    { 1469.15f, 499.434f, 246.884f, 2.386790f },
    { 1470.01f, 504.444f, 246.884f, 2.971790f },
    { 1470.81f, 508.671f, 246.882f, 3.067930f},
    { 1470.59f, 514.213f, 246.895f, 3.695170f},
    { 1469.0f, 519.948f, 246.893f,  4.119670f },
};
Position position_fallen_pool_tender[2] =
{
    {1423.380f, 505.545f, 246.880f, 3.430770f},
    {1460.640f, 509.049f, 246.882f, 0.258838f},
};

enum Talks
{
    // 1st boss
    TALK_1 = 1, // Ah.. we adventure together again, except this time.. I'm afraid circumstances are much.. more die (38120)
    TALK_2 = 2, // Oh.. what has become of the vale? (38121)
    TALK_3 = 3, // The land is scarred.. the everblooming trees and plants wither and die.. as the water from the pools drains away. (38122)
    TALK_4 = 4, // Come.. let us see what other horrors Garrosh has unleashed upon our land. (38123)
    TALK_5 = 5, // Once the Titans used these life-giving waters, to create and shape all life in Pandaria (38124)
    TALK_6 = 6, // It is these waters that kept the water in bloom, they run off into the the Valley of Four Winds.. created the most furtile farms in the whole world! (38125)
    TALK_7 = 7, // And now.. the Melignants of the old gods has menifested themselves into this old waters (38126)
    TALK_8 = 8, // Such a foul.. foul.. thing.. destroy it, before it seeps deep into the soil, and corrupt all of Pandaria! (38127)
    TALK_9 = 9, // Ah.. you have done it, the waters are pure once more. (38128)

    // 2nd boss
    TALK_10 = 10, // Can you feel the life giving energy flow through you? (38129)
    TALK_11 = 11, // It'll take much time for vale to heal, but you have giving us hope (38130)
    TALK_12 = 12, // Can it be?... Oh no.. no! NO! (38131)
    TALK_13 = 13, // The Golden Lotus?! but.. the pledged their life to defend this place!
};
enum eEvents
{
    EVENT_TALK_1              = 20,
    EVENT_TALK_2              = 22,
    EVENT_TALK_3              = 23,
    EVENT_TALK_4              = 24,
    EVENT_TALK_5              = 25,
    EVENT_TALK_6              = 26,
    EVENT_TALK_7              = 27,
    EVENT_TALK_8              = 28,
    EVENT_TALK_9              = 29,
	EVENT_FPT_WATERBOLT       = 30,
	EVENT_FPT_CORRUPTED_WATER = 31,
	EVENT_AD_RUSHING_WATERS   = 32,
};

enum MobSpells
{
    SPELL_INITIATE_BUBBLE_SHIELD = 147333,

    SPELL_FPT_BUBBLE_SHIELD_AURA = 147450,
    SPELL_FPT_WATERBOLT          = 147398,
    SPELL_FPT_CORRUPTED_WATER    = 147351,

    SPELL_AD_RUSHING_WATERS      = 147185,
};

enum Mobs
{
    NPC_TORMENTED_INITIATE       = 73349,
    NPC_FALLEN_POOL_TENDER       = 73342,
    NPC_AQUEOUS_DEFENDER         = 73191,
};

// Tormented Initiate 73349.
class npc_soo_tormented_initiate : public CreatureScript
{
    public:
        npc_soo_tormented_initiate() : CreatureScript("npc_soo_tormented_initiate") { }

        struct npc_soo_tormented_initiate_AI : public ScriptedAI
        {
            npc_soo_tormented_initiate_AI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() { }

            void EnterCombat(Unit* who)
            {
                std::list<Creature*> nearList;
                GetCreatureListWithEntryInGrid(nearList, me, NPC_TORMENTED_INITIATE, 20.0f);
                GetCreatureListWithEntryInGrid(nearList, me, NPC_FALLEN_POOL_TENDER, 20.0f);
                if (!nearList.empty())
                    for (auto nearMob : nearList)
                        if (!nearMob->isInCombat())
                            nearMob->AI()->DoZoneInCombat();
            }

            void DamageTaken(Unit* who, uint32& damage)
            {
                if (Spell* spell = me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    if (spell->m_spellInfo->Id == SPELL_INITIATE_BUBBLE_SHIELD)
                        me->InterruptNonMeleeSpells(true);
            }

            void EnterEvadeMode()
            {
                me->AddUnitState(UNIT_STATE_EVADE);

                me->RemoveAllAuras();
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MovementExpired();
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                me->ClearUnitState(UNIT_STATE_EVADE);
            }

            void JustDied(Unit* killer) { }

            void UpdateAI(uint32 const diff)
            {
                // Maintain Bubble Shield cast on Fallen Pool Tender.
                if (!me->HasUnitState(UNIT_STATE_CASTING) && !me->HasUnitState(UNIT_STATE_EVADE) && !me->isInCombat())
                    if (Creature* poolTender = me->FindNearestCreature(NPC_FALLEN_POOL_TENDER, 20.0f, true))
                        DoCast(poolTender, SPELL_INITIATE_BUBBLE_SHIELD);

                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_soo_tormented_initiate_AI(creature);
        }
};

// Fallen Pool Tender 73342.
class npc_soo_fallen_pool_tender : public CreatureScript
{
    public:
        npc_soo_fallen_pool_tender() : CreatureScript("npc_soo_fallen_pool_tender") { }

        struct npc_soo_fallen_pool_tender_AI : public ScriptedAI
        {
            npc_soo_fallen_pool_tender_AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                // Remove Bubble Shield aura.
                if (me->HasAura(SPELL_FPT_BUBBLE_SHIELD_AURA))
                    me->RemoveAurasDueToSpell(SPELL_FPT_BUBBLE_SHIELD_AURA);

                events.ScheduleEvent(EVENT_FPT_WATERBOLT, 2000);
                events.ScheduleEvent(EVENT_FPT_CORRUPTED_WATER, 7000);
            }

            void EnterEvadeMode()
            {
                me->AddUnitState(UNIT_STATE_EVADE);

                me->RemoveAllAuras();
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MovementExpired();
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                me->ClearUnitState(UNIT_STATE_EVADE);
            }

            void JustDied(Unit* killer) { }

            void UpdateAI(uint32 const diff)
            {
                // Maintain Bubble Shield aura OOC.
                if (!me->HasAura(SPELL_FPT_BUBBLE_SHIELD_AURA) && !me->HasUnitState(UNIT_STATE_EVADE) && !me->isInCombat())
                    DoCast(me, SPELL_FPT_BUBBLE_SHIELD_AURA);

                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FPT_WATERBOLT:
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_FPT_WATERBOLT);
                            events.ScheduleEvent(EVENT_FPT_WATERBOLT, 3000);
                            break;
                        }

                        case EVENT_FPT_CORRUPTED_WATER:
                        {
                            DoCast(me, SPELL_FPT_CORRUPTED_WATER);
                            events.ScheduleEvent(EVENT_FPT_CORRUPTED_WATER, urand(17000, 20000));
                            break;
                        }

                        default: break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_soo_fallen_pool_tender_AI(creature);
        }
};

// Aqueous Defender 73191.
class npc_soo_aqueous_defender : public CreatureScript
{
    public:
        npc_soo_aqueous_defender() : CreatureScript("npc_soo_aqueous_defender") { }

        struct npc_soo_aqueous_defender_AI : public ScriptedAI
        {
            npc_soo_aqueous_defender_AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                events.ScheduleEvent(EVENT_AD_RUSHING_WATERS, urand(3000, 5000));
            }

            void EnterEvadeMode()
            {
                me->AddUnitState(UNIT_STATE_EVADE);

                me->RemoveAllAuras();
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MovementExpired();
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                me->ClearUnitState(UNIT_STATE_EVADE);
            }

            void JustDied(Unit* killer) { }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_AD_RUSHING_WATERS:
                        {
                            DoCast(me, SPELL_AD_RUSHING_WATERS);
                            events.ScheduleEvent(EVENT_AD_RUSHING_WATERS, urand(20000, 24000));
                            break;
                        }

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_soo_aqueous_defender_AI(creature);
        }
};
/*
class siege_of_orgrimmar_lorewalker_cho : public CreatureScript
{
public:
    siege_of_orgrimmar_lorewalker_cho() : CreatureScript("siege_of_orgrimmar_lorewalker_cho") { }

    struct soo_triggers : public CreatureAI
    {
        soo_triggers(Creature* creature) : CreatureAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            intro = false;
            eighth = false;
        }

        InstanceScript* pInstance;
        EventMap events;

        bool intro;
        bool eighth;
        uint32 interval;
        
        void Reset()
        { 
            me->setFaction(35);

            me->SetSpeed(MOVE_RUN, 1.6f);
            me->SetReactState(REACT_PASSIVE);

            events.ScheduleEvent(EVENT_TALK_1, 1000);

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void DamageTaken(Unit* /*attacker*//*, uint32& damage)
        {
            damage = 0;
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
            case ACTION_LAST_TALK_BEFORE_BOSS:
                if (!eighth)
                    eighth = true;
                events.ScheduleEvent(EVENT_TALK_8, 100);
                break;
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 40.0f) && !intro)
            {
                if (Creature* Immersus = pInstance->instance->GetCreature(pInstance->GetData64((DATA_IMMERSEUS))))
                {
                    if (Immersus->IsWithinDistInMap(who, 60.0f))
                    {
                        intro = true;
                        Immersus->DespawnOrUnsummon(25000);

                        if (Immersus->GetAI())
                            Immersus->GetAI()->DoAction(ACTION_LAST_TALK_BEFORE_BOSS);
                    }
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!me->GetMotionMaster()->GetMotionSlot(MOTION_SLOT_ACTIVE))
            {
                if (Player* nearest = me->FindNearestPlayer(60.0f, true))
                {
                    me->GetMotionMaster()->MovePoint(0, nearest->GetPositionX() + 3, nearest->GetPositionY() + 5, nearest->GetPositionZ());
                }
            }

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_TALK_1:
                {
                    Talk(TALK_1);
                    events.ScheduleEvent(EVENT_TALK_2, 12000);
                    break;
                }
                case EVENT_TALK_2:
                {
                    Talk(TALK_2);
                    events.ScheduleEvent(EVENT_TALK_3, 15000);
                    break;
                }
                case EVENT_TALK_3:
                {
                    Talk(TALK_3);
                    events.ScheduleEvent(EVENT_TALK_4, 18000);
                    break;
                }
                case EVENT_TALK_4:
                {
                    Talk(TALK_4);
                    events.ScheduleEvent(EVENT_TALK_5, 15000);
                    break;
                }
                case EVENT_TALK_5:
                {
                    Talk(TALK_5);
                    events.ScheduleEvent(EVENT_TALK_6, 15000);
                    break;
                }
                case EVENT_TALK_6:
                {
                    Talk(TALK_6);
                    events.ScheduleEvent(EVENT_TALK_7, 15000);
                    break;
                }
                case EVENT_TALK_7:
                {
                    Talk(TALK_7);
                    break;
                }
                case EVENT_TALK_8:
                {
                    Talk(TALK_8);
                    break;
                }
                case EVENT_TALK_9:
                {
                    Talk(TALK_9);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new soo_triggers(creature);
    }
};
*/
void AddSC_siege_of_orgrimmar()
{
    // new siege_of_orgrimmar_lorewalker_cho();
	new npc_soo_tormented_initiate();
	new npc_soo_fallen_pool_tender();
	new npc_soo_aqueous_defender();
}