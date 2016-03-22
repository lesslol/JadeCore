/*
* Copyright (C) 2012-2013 JadeCore <http://www.pandashan.com/>
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "ScriptedCreature.h"
#include "throne_of_thunder.h"  

enum eeSpells
{
    SPELL_COSMETIC_LIGHTNING_STORM = 140549,
    SPELL_SUMMON_LEI_SHEN_EFFECT = 139206,
    SPELL_SELF_STUN = 45066,

    // Tortos
    SPELL_FURIOUS_STONE_BREATH_DUMMY = 133939,
    SPELL_FURIOUS_STONE_BREATH_DAMAGE = 133946,
    SPELL_ROCK_FALL = 134475, // on trigger
    SPELL_QUAKE_STOMP = 134920, // decrease rockfall interval by 8 sec upon cast
    SPELL_SNAPPING_BITE = 135251,
    SPELL_GROWING_FURY = 136010,
    SPELL_CALL_OF_TORTOS = 136294,
    // Whirl Turtle
    SPELL_WHIRL = 133974,
    SPELL_WHIRL_DAMAGE = 134011,
    SPELL_SHELL_BLOCK = 133971,
    SPELL_CONCUSSION = 134092,
    // Vampiric Bat Cave
    SPELL_DRAIN_THE_WEAK = 135103, // less then 350,000 hp
};
enum eeTriggers
{

};
enum Creatures
{
    CREATURE_LEI_SHEN = 68397,
    TRIGGER_LIGHTNING_STORM = 423526,
    TRIGGER_ROCKFALL = 68219,

    CREATURE_WHIRL_TURTLE = 67966,
    CREATURE_VAMPIRIC_BAT_CAVE = 68497, // 30 sec
};
enum eeEvents
{
    // Tortos
    EVENT_ROCK_FALL = 400,
    EVENT_FURIOUS_STONE_BREATH = 401,
    EVENT_QUAKE_STOMP = 402,
    EVENT_SNAPPING_BITE = 403,
    EVENT_GROWING_FURY = 404,
    EVENT_SUMMON_BAT_CAVES = 406,
    EVENT_SUMMON_TURTLES = 407,
    EVENT_CALL_OF_TORTOS = 408,
    EVENT_NORMALIZE_ROCK_FALL = 409,
    // Bat Cave
    EVENT_DRAIN_THE_WEAK = 405,
};
enum eeActions
{

};
enum eeTalks
{
    // Bridge Event Lei Shen
    LEI_SHEN_TALK_01 = 0, // Haha... These insects do not know their place, Karazal. If you wish to prove your might on such weaklings, it matters not to me! (35586)
    LEI_SHEN_TALK_02 = 1, // You have swept the filth from my doorstep, perhaps you're worthy of my attention. (35587)
    LEI_SHEN_TALK_03 = 2, // But your tresspass ends here! None may enter my forbidden stronghold, I shall rebuild this bridge with your bones for bricks! (35588)
};
enum Times
{
    FURIOUS_STONE_BREATH_TIME = 45000,
};

Position Lei_Shen = { 6046.39f, 4986.15f, 148.021f, 1.541749f };
Position LightningStormTrigger = { 6050.47f, 5084.22f, 151.343f, 1.634183f };
Position TortosLair = { 6045.22f, 5101.67f, -43.113f, 4.535460f };
class tortos_bridge_Event : public BasicEvent
{
public:
    explicit tortos_bridge_Event(Unit* unit, int value) : obj(unit), modifier(value)
    {
    }

    bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
    {
        if (InstanceScript* instance = obj->GetInstanceScript())
        {
            if (obj)
            {
                switch (modifier)
                {
                case 0:
                {
                    std::list<Player*> pl_list;
                    obj->GetPlayerListInGrid(pl_list, 500.0f);

                    if (pl_list.empty())
                        return false;

                    for (auto itr : pl_list)
                    {
                        itr->AddAura(45066, itr);
                    }

                    Creature* lei_shen = obj->SummonCreature(CREATURE_LEI_SHEN, Lei_Shen, TEMPSUMMON_MANUAL_DESPAWN);
                    if (lei_shen)
                    {
                        lei_shen->SetObjectScale(2.5);
                        lei_shen->AI()->Talk(LEI_SHEN_TALK_01);

                        obj->m_Events.AddEvent(new tortos_bridge_Event(lei_shen, 1), obj->m_Events.CalculateTime(10000));
                    }
                    break;
                }
                case 1:
                {
                    if (Creature* lei_shen = obj->ToCreature())
                        lei_shen->AI()->Talk(LEI_SHEN_TALK_02);

                    obj->m_Events.AddEvent(new tortos_bridge_Event(obj, 2), obj->m_Events.CalculateTime(10000));
                    break;
                }
                case 2:
                {
                    if (Creature* lei_shen = obj->ToCreature())
                        lei_shen->AI()->Talk(LEI_SHEN_TALK_03);

                    obj->m_Events.AddEvent(new tortos_bridge_Event(obj, 3), obj->m_Events.CalculateTime(6000));
                    break;
                }
                case 3:
                {              
                 Creature* lightning_storm_trigger = obj->SummonCreature(TRIGGER_LIGHTNING_STORM, LightningStormTrigger, TEMPSUMMON_TIMED_DESPAWN);
                 if (lightning_storm_trigger)
                 {
                     lightning_storm_trigger->setFaction(35);
                     lightning_storm_trigger->CastSpell(lightning_storm_trigger, SPELL_COSMETIC_LIGHTNING_STORM);
                     obj->m_Events.AddEvent(new tortos_bridge_Event(obj, 4), obj->m_Events.CalculateTime(15000));
                 }
                break;
                }
                case 4:
                {
                    std::list<Player*> pl_list;
                    obj->GetPlayerListInGrid(pl_list, 500.0f);

                    if (pl_list.empty())
                        return false;

                    for (auto itr : pl_list)
                    {
                        itr->NearTeleportTo(TortosLair.GetPositionX(), TortosLair.GetPositionY(), TortosLair.GetPositionZ(), TortosLair.GetOrientation());
                    }
                    instance->DoRemoveAurasDueToSpellOnPlayers(45066);
                    instance->DoRemoveAurasDueToSpellOnPlayers(140560);
                    break;
                }
                }
            }
        }
        return true;
    }
private:
    Creature* storm;
    Unit* obj;
    int modifier;
    int Event;
};
class creature_tortos_intro_bridge : public CreatureScript
{
public:
    creature_tortos_intro_bridge() : CreatureScript("creature_tortos_intro_bridge") { }

    struct creature_tortos_intro_bridgeAI : public ScriptedAI
    {
        creature_tortos_intro_bridgeAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            intro = false;
        }

        InstanceScript* pInstance;
        EventMap events;
        bool intro;

        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f) && !intro)
            {
                intro = true;
                me->m_Events.AddEvent(new tortos_bridge_Event(me, 0), me->m_Events.CalculateTime(500));
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new creature_tortos_intro_bridgeAI(creature);
    }
};
class boss_tortos : public CreatureScript
{
public:
    boss_tortos() : CreatureScript("boss_tortos") { }

    struct boss_tortosAI : public BossAI
    {
        boss_tortosAI(Creature* creature) : BossAI(creature, DATA_TORTOS)
        {
            pInstance = creature->GetInstanceScript();
            intro = false;
        }

        InstanceScript* pInstance;
        EventMap events;

        bool intro;
        float damage;
        int32 hppcts;
        uint32 intervaldmg;

        void Reset()
        {
            _Reset();
            events.Reset();
            summons.DespawnAll();
            intervaldmg = 45000;

            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);

            me->SetMaxHealth(179000000);
            me->SetHealth(179000000);

            me->setFaction(16);
        }
        void JustReachedHome()
        {
            _JustReachedHome();
            summons.DespawnAll();
        } 
        void EnterCombat(Unit* attacker)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();
            }

            events.ScheduleEvent(EVENT_SNAPPING_BITE, 12000);
            events.ScheduleEvent(EVENT_ROCK_FALL, 15000);
            events.ScheduleEvent(EVENT_QUAKE_STOMP, urand(18000, 20000));
            events.ScheduleEvent(EVENT_SUMMON_BAT_CAVES, 50000);
            events.ScheduleEvent(EVENT_CALL_OF_TORTOS, 25000);
            events.ScheduleEvent(EVENT_FURIOUS_STONE_BREATH, 45000);
        }
        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }
        void SummonedCreatureDespawn(Creature* summon)
        {
            summons.Despawn(summon);
        }
        void DespawnCreaturesInArea(uint32 entry, WorldObject* object)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, object, entry, 300.0f);
            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_FURIOUS_STONE_BREATH:
                {
                    me->CastSpell(me->getVictim(), SPELL_FURIOUS_STONE_BREATH_DAMAGE);
                    events.ScheduleEvent(EVENT_FURIOUS_STONE_BREATH, 45000);
                    break;
                }
            case EVENT_SNAPPING_BITE:
                me->CastSpell(me->getVictim(), SPELL_SNAPPING_BITE);
                events.ScheduleEvent(EVENT_SNAPPING_BITE, 6000);
                break;
            case EVENT_ROCK_FALL:
                for (int i = 0; i <= 6; i++)
                {
                    if (Unit* pl = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        Position pos;
                        pl->GetRandomNearPosition(pos, 30.0f);

                        me->SummonCreature(TRIGGER_ROCKFALL, pos, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    }
                }
                events.ScheduleEvent(EVENT_ROCK_FALL, 15000);
                break;
            case EVENT_QUAKE_STOMP:
            {
                for (int i = 0; i <= 6; i++)
                {
                    if (Unit* pl = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        Position pos;
                        pl->GetRandomNearPosition(pos, 30.0f);

                        me->SummonCreature(TRIGGER_ROCKFALL, pos, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    }
                }

                me->CastSpell(me, SPELL_QUAKE_STOMP);
                events.ScheduleEvent(EVENT_QUAKE_STOMP, urand(18000, 24000));
                break;
            }
            case EVENT_SUMMON_BAT_CAVES:
                if (Unit* pl = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                {
                    for (int i = 0; i <= 5; i++)
                    {
                        Creature* vampiric = me->SummonCreature(CREATURE_VAMPIRIC_BAT_CAVE, pl->GetPositionX(), pl->GetPositionY(), pl->GetPositionZ(), pl->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN);

                        if (vampiric)
                            vampiric->SetReactState(REACT_AGGRESSIVE);
                    }
                    events.ScheduleEvent(EVENT_SUMMON_BAT_CAVES, 50000);
                }
                break;
            case EVENT_CALL_OF_TORTOS:
                for (int i = 0; i < 3; i++)
                {
                    me->SummonCreature(CREATURE_WHIRL_TURTLE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
                }
                events.ScheduleEvent(EVENT_CALL_OF_TORTOS, 35000);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_tortosAI(creature);
    }
};
class boss_whirl_turtle : public CreatureScript
{
public:
    boss_whirl_turtle() : CreatureScript("boss_whirl_turtle") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
            if (Creature* tortos = instance->instance->GetCreature(instance->GetData64(DATA_TORTOS)))
            {
                creature->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
                creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                creature->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                creature->GetMotionMaster()->MoveJump(tortos->GetPositionX(), tortos->GetPositionY(), tortos->GetPositionZ(), 40.0F, 10.0F, 10.0f);
                creature->AddAura(SPELL_CONCUSSION, creature);

                //creature->RemoveAura(SPELL_SHELL_BLOCK);
                if (tortos->HasUnitState(UNIT_STATE_CASTING))
                {
                    tortos->CastStop();
                    tortos->AddAura(136431, tortos);
                }
                creature->DespawnOrUnsummon(6000);
            }
        return true;
    }
    struct boss_whirl_turtleAI : public ScriptedAI
    {
        boss_whirl_turtleAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        
        uint32 interval;
        uint32 intervalperswitch;
        bool spell;

        void Reset()
        {
            interval = 4000;
            intervalperswitch = 0;

            me->setFaction(16);
            me->AddAura(SPELL_WHIRL, me);

            spell = false;

            me->SetSpeed(MOVE_RUN, 0.8f, true);
            me->GetMotionMaster()->MovePoint(0, 6041.14f, 4987.92f, -61.198f);
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && spell && me->IsWithinDistInMap(who, 3.0f))
            {
                if (!who->HasAura(134030))
                {
                    who->AddAura(134030, who);
                }
            }
        }
        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->GetHealthPct() <= 15 && me->getFaction() == 16)
            {
                spell = true;
                me->RemoveAura(SPELL_WHIRL);
                me->RemoveAllAuras();
                me->setFaction(35);
                me->CastSpell(me, SPELL_SHELL_BLOCK);

                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
            }
        }
        void UpdateAI(const uint32 diff)
        {
            if (me->HasAura(SPELL_SHELL_BLOCK))
                return;

            // damage
            if (interval <= diff)
            {
                std::list<Player*> list_pl;
                me->GetPlayerListInGrid(list_pl, 2.0f);

                if (list_pl.empty())
                    return;

                for (auto itr : list_pl)
                {
                    itr->CastSpell(itr, SPELL_WHIRL_DAMAGE);
                }

                interval = 4000;
            }
            else
                interval -= diff;
            // switch target
            if (intervalperswitch <= diff)
            {
                if (Player* pl = me->FindNearestPlayer(80.0f))
                    me->GetMotionMaster()->MoveFollow(pl, 0.0f, 0.0f, MOTION_SLOT_ACTIVE);

                intervalperswitch = 8000;
            }
            else
                intervalperswitch -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_whirl_turtleAI(creature);
    }
};
class npc_vampiric_bat : public CreatureScript
{
public:
    npc_vampiric_bat() : CreatureScript("npc_vampiric_bat") { }

    struct boss_whirl_turtleAI : public ScriptedAI
    {
        boss_whirl_turtleAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;

        uint32 interval;

        void Reset()
        {
            interval = urand(8000, 10000);
        }
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            // damage
            if (interval <= diff)
            {
                if (me->getVictim() && me->getVictim()->GetHealth() <= 350000)
                    me->CastSpell(me->getVictim(), SPELL_DRAIN_THE_WEAK);

                interval = urand(8000, 10000);
            }
            else
                interval -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_whirl_turtleAI(creature);
    }
};
class rockfall_trigger : public CreatureScript
{
public:
    rockfall_trigger() : CreatureScript("rockfall_trigger") { }

    struct rockfall_triggerAI : public Scripted_NoMovementAI
    {
        rockfall_triggerAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;

        uint32 interval;

        void Reset()
        {
            me->CastSpell(me, SPELL_ROCK_FALL);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new rockfall_triggerAI(creature);
    }
};
class spell_quake_stomp_damage : public SpellScriptLoader
{
public:
    spell_quake_stomp_damage() : SpellScriptLoader("spell_quake_stomp_damage") { }

    class spell_quake_stomp_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_quake_stomp_damage_SpellScript);

        void RecalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (GetHitUnit())
                SetHitDamage(GetHitUnit()->GetMaxHealth() * 0.45);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_quake_stomp_damage_SpellScript::RecalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_quake_stomp_damage_SpellScript();
    }
};

void AddSC_tortos()
{
    new boss_tortos();
    new boss_whirl_turtle();
    new npc_vampiric_bat();
    new rockfall_trigger();
    new creature_tortos_intro_bridge();
    new spell_quake_stomp_damage();
}
