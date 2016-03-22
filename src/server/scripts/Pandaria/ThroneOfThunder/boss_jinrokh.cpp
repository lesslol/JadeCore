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

Position centerTrigger = { 5892.54f, 6262.93f, 124.035f, 3.124630f };
Position Statues[4] =
{
    { 5942.01f, 6310.80f, 148.946f, 4.098326f },
    { 5939.49f, 6215.77f, 152.630f, 2.311547f },
    { 5841.41f, 6214.92f, 151.430f, 0.882122f },
    { 5842.95f, 6312.26f, 151.260f, 5.376692f },
};

enum eeSpells
{
    // Jin'rokh the breakfart
    SPELL_FOCUSED_LIGHTNING_SUMMON = 139206,
    SPELL_FOCUSED_LIGHTNING_ORB_TICK = 137423,
    SPELL_FOCUSED_LIGHTNING_VISUAL = 137425,
    SPELL_FOCUSED_LIGHTNING_UNKNOWN_DAMAGE = 139210,
    SPELL_LIGHTNING_FISSURE_SUMMON = 137479,
    SPELL_LIGHTNING_FISSURE_EFFECTIVE_AURA = 137480,
    SPELL_LIGHTNING_FISSURE_CLOSE_YARD_TICK_UNKNOWN = 137485,
    SPELL_LIGHTNING_FISSURE_UNKNOWN_EXPLOSION = 137485,
    SPELL_LIGHTNING_FISSURE_DAMAGE_CONDUCT_WITH_ORB_UNKNOWN = 138133,
    SPELL_LIGHTNING_FISSURE_IMPLOSION_ORB_CONTACT = 137507,
    SPELL_STATIC_BURST = 137162,
    SPELL_STATIC_WOUND = 138349, // APPLIED AFTER BURST TO THE TANK
    SPELL_THUNDERING_THROW_PLAYER_HIT_GROUND = 137167,
    SPELL_THUNDERING_THROW_JUMPING_TO_STATUE = 137173,
    SPELL_THUNDERING_THROW_JUMPING_FROM_STATUE = 140580,
    SPELL_THUNDERING_THROW_UNKNOWN_DAMAGE = 137370,
    SPELL_THUNDERING_THROW_STUN = 137371,
    SPELL_THUNDERING_THROW_BOSS_GRASPING_PLAYER = 140594,
    SPELL_THUNDERING_THROW_DUMMY = 140597,
    SPELL_THUNDERING_THROW_LIGHTNING_ANIMATION = 140606,
    SPELL_FLUDITIY = 138002,
    SPELL_THROW_DUMMY = 137180,
    SPELL_CONDUTIVE_WATER_SUMMON = 137145,
    SPELL_CONDUCTIVE_WATER_VISUAL = 137277,
    SPELL_CONDUCTIVE_WATER_SIZE = 137694,
    SPELL_CONDUCTIVE_WATER_ELECTERTUED = 137978, // FUCK GRAMMAR
    SPELL_CONDUTIVE_WATER_LIGHTNING_VISUAL = 138568,
    SPELL_ELECTRIFYING_WATER = 138006,
    SPELL_LIGHTNING_STORM = 137313,
    SPELL_LIGHTNING_STORM_DOT = 140560,
    SPELL_LIGHTNING_VISUAL = 140549,
    SPELL_WATER_SPROUT_VISUAL = 137340,
    SPELL_CONDUCTIVE_WATER_ELECTERT_VISUAL = 137978,

    // HEROIC
    SPELL_IONIZATION_DUMMY = 138732,
    SPELL_IONIZATION_EXPLOSION = 138733,

    SPELL_LIGHTNING_STRIKE_ADD_VISUAL = 137966, // ADD VISUAL, add scale 0.3
    SPELL_LIGHNING_STRIKE_VISUAL = 138299,
    SPELL_LIGHTNING_STRIKE_HIT = 137647,
};
enum eeTriggers
{
    TRIGGER_WATER = 69469,
    TRIGGER_FISSURE = 69609,
    TRIGGER_FOCUSED_LIGHTNING_ORB = 70174,
    TRIGGER_THUNDERING_THROWING = 836571,
    TRIGGER_THUNDERING_EXPLODE = 543673,
    TRIGGER_LIGHTNING_STRIKE_PILLAR = 324213,
    TRIGGER_LIGHTNING_STRIKE_STAR = 324124,
};
enum eeEvents
{
    // Jinrokh
    EVENT_SPELL_FOCUSED_LIGHTNING = 100,
    EVENT_SPELL_LIGHTNING_FISSURE = 101,
    EVENT_SPELL_IMPLOSION = 102,
    EVENT_SPEL_STATIC_BURST = 103,
    EVENT_SPELL_STATIC_WOUND = 104,
    EVENT_BERSERK = 105, // jelly druid
    EVENT_THUNDERING_THROW = 106,
    EVENT_LIGHTNING_STORM = 107,
    EVENT_SPELL_FOCUSED_LIGHTNING_SUMMON = 108,
    EVENT_LIGHTNING_STORM_REMOVE_AURA = 109,
    EVENT_THUNDERING_THROW_JUMP_TARGET = 110,
    EVENT_THUNDERING_THROW_JUMP_TARGET_2 = 111,

    // heroic
    EVENT_IONIZATION = 112,
    EVENT_LIGHTNING_STRIKE = 113,
};
enum eeTalks
{
    JINROKH_AGGRO = 0, // I must break you.. (35547)
    JINROKH_INTRO = 1, // The Thunda' King give me power.. come.. I'll show you! (35550)
    JINROKH_DEATH = 2, // How.. you.. beat.. me.. (35549)
    JINROKH_BERSERK = 3, // Bored.. you die now! (35548)
    JINROKH_KILL = 4, // Weak... (35551) / So easy to break..(35552)
    JINROKH_SPELL_1 = 5, // Smash... (35553)
    JINROKH_SPELL_2 = 6, // I'll crush your bones! (35554)
    JINROKH_SPELL_3 = 7, // I call the storm! (35555)
    JINROKH_SPELL_4 = 8, // Zap... (35556)
};
enum eeTimers
{
    JINROKH_FOCUSED_LIGHTNING_INTERVAL = 15000,
    JINROKH_SPELL_STATIC_BURST_INTERVAL = 30000,
    JINROKH_BERSERK_INTERVAL = 420000,
    JINROKH_SPELL_STATIC_WOUND_INTERVAL = 5000,
    JINROKH_THUNDERING_THROW_INTERVAL = 30000,
    JINROKH_THUNDERING_THROW_INTERVAL_2ND_HIT = 90000,
    JINROKH_EVENT_LIGHTNING_STORM_INTERVAL = 90000,
    JINROKH_IONIZATION_INTERVAL = 90000, //starts with 1 minute after the fight
};
enum eeActions
{
    ACTION_TRIGGER_PILLAR = 4324,
};
class RemoveIfTanks
{
public:
    RemoveIfTanks() {}
    bool operator()(WorldObject* object)
    {
        if (object->GetTypeId() == TYPEID_PLAYER)
            if (Player* pobject = object->ToPlayer())
                if (pobject->GetSpecializationId(pobject->GetActiveSpec() == SPEC_WARRIOR_PROTECTION) || pobject->GetSpecializationId(pobject->GetActiveSpec() == SPEC_PALADIN_PROTECTION)
                    || pobject->GetSpecializationId(pobject->GetActiveSpec() == SPEC_DROOD_BEAR) || pobject->GetSpecializationId(pobject->GetActiveSpec() == SPEC_MONK_BREWMASTER) ||
                    pobject->GetSpecializationId(pobject->GetActiveSpec() == SPEC_DK_BLOOD))
                    return true;
                else
                    return false;
    }
};
class jinrokh_lightning_strikes : public BasicEvent
{
public:
    explicit jinrokh_lightning_strikes(Unit* unit, int value) : obj(unit), modifier(value)
    {
    }

    bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
    {
        if (obj)
        {
            if (InstanceScript* instance = obj->GetInstanceScript())
            {
                switch (modifier)
                {
                case 0:
                    /*
                    Position pos;
                    obj->GetRandomNearPosition(pos, 40.0f);
                    printf("tesla");
                    obj->SummonCreature(TRIGGER_LIGHTNING_STRIKE_PILLAR, pos, TEMPSUMMON_MANUAL_DESPAWN);
                    */
                    std::list<Creature*> triggers;
                    triggers.clear();
                    obj->GetCreatureListWithEntryInGrid(triggers, TRIGGER_LIGHTNING_STRIKE_PILLAR, 400.0f);

                    if (triggers.empty())
                        return false;

                    std::list<Creature*>::const_iterator it = triggers.begin();
                    std::advance(it, urand(0, triggers.size() - 1));

                    (*it)->AI()->DoAction(ACTION_TRIGGER_PILLAR);

                    obj->m_Events.AddEvent(new jinrokh_lightning_strikes(obj, 0), obj->m_Events.CalculateTime(500));
                    break;
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
class boss_jinkorh : public CreatureScript
{
public:
    boss_jinkorh() : CreatureScript("boss_jinkorh") { }

    struct boss_jinkorhAI : public BossAI
    {
        boss_jinkorhAI(Creature* creature) : BossAI(creature, DATA_JINKORH)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        Unit* target; // ORB
        Unit* target_throw;

        bool intro;

        void Reset()
        {
            _Reset();
            events.Reset();
            summons.DespawnAll();

            intro = false;
            target = NULL;
            target_throw = NULL;

            for (int i = 0; i < 4; i++)
            {
                Creature* trigger = me->SummonCreature(TRIGGER_THUNDERING_THROWING, Statues[i], TEMPSUMMON_MANUAL_DESPAWN);
            }
        }
        void JustReachedHome()
        {
            _JustReachedHome();

            DespawnCreaturesInArea(TRIGGER_FISSURE, me);
            DespawnCreaturesInArea(TRIGGER_WATER, me);
            DespawnCreaturesInArea(TRIGGER_LIGHTNING_STRIKE_STAR, me);

            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LIGHTNING_STORM_DOT);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_THUNDERING_THROW_LIGHTNING_ANIMATION);

            if (GameObject* JinrokhDoor = instance->instance->GetGameObject(instance->GetData64(DATA_JINROKH_DOOR)))
            {
                JinrokhDoor->UseDoorOrButton();
            }

            if (pInstance)
                pInstance->SetBossState(DATA_JINKORH, FAIL);
        }
        void EnterCombat(Unit* attacker)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();
            }

            if (GameObject* JinrokhDoor = instance->instance->GetGameObject(instance->GetData64(DATA_JINROKH_DOOR)))
            {
                JinrokhDoor->UseDoorOrButton();
            }

            Talk(JINROKH_AGGRO);

            events.ScheduleEvent(EVENT_THUNDERING_THROW, JINROKH_THUNDERING_THROW_INTERVAL);
            events.ScheduleEvent(EVENT_SPELL_FOCUSED_LIGHTNING, JINROKH_FOCUSED_LIGHTNING_INTERVAL);
            events.ScheduleEvent(EVENT_SPEL_STATIC_BURST, JINROKH_SPELL_STATIC_BURST_INTERVAL);
            events.ScheduleEvent(EVENT_LIGHTNING_STORM, JINROKH_EVENT_LIGHTNING_STORM_INTERVAL);
            events.ScheduleEvent(EVENT_BERSERK, JINROKH_BERSERK_INTERVAL);

            if (me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_IONIZATION, 5555);
        }
        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }
        void SummonedCreatureDespawn(Creature* summon)
        {
            summons.Despawn(summon);
        }
        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
                Talk(JINROKH_KILL);
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && !intro && me->IsWithinDistInMap(who, 40.0f))
            {
                intro = true;
                Talk(JINROKH_INTRO);

                me->CastSpell(me, SPELL_THUNDERING_THROW_LIGHTNING_ANIMATION);
            }
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
        void JustDied(Unit* killer)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                pInstance->SetBossState(DATA_JINKORH, DONE);
            }

            DespawnCreaturesInArea(TRIGGER_FISSURE, me);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LIGHTNING_STORM_DOT);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_THUNDERING_THROW_LIGHTNING_ANIMATION);

            _JustDied();
            Talk(JINROKH_DEATH);
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
            case EVENT_IONIZATION:
            {
                me->CastSpell(me->getVictim(), SPELL_IONIZATION_DUMMY);
                /*
                std::list<Player*> pl_list;
                pl_list.clear();

                me->GetPlayerListInGrid(pl_list, 300.0f);

                if (pl_list.empty())
                return;

                pl_list.remove_if(RemoveIfTanks());

                for (auto itr : pl_list)
                {
                me->CastSpell(itr, SPELL_IONIZATION_DUMMY, true);
                }
                */

                events.ScheduleEvent(EVENT_IONIZATION, 90000);
                break;
            }
            case EVENT_BERSERK:
                me->CastSpell(me, 47008); // berserk
                events.ScheduleEvent(EVENT_BERSERK, JINROKH_BERSERK_INTERVAL);
                break;
            case EVENT_SPELL_FOCUSED_LIGHTNING:
                me->CastSpell(me, SPELL_FOCUSED_LIGHTNING_SUMMON);
                events.ScheduleEvent(EVENT_SPELL_FOCUSED_LIGHTNING, 15000);
                break;
                /*
                case EVENT_SPELL_FOCUSED_LIGHTNING_SUMMON:
                SpellInfo const* spell = sSpellMgr->GetSpellInfo(SPELL_FOCUSED_LIGHTNING_SUMMON);
                me->SummonCreature(TRIGGER_FOCUSED_LIGHTNING_ORB, spell->dest);
                break;
                */
            case EVENT_SPEL_STATIC_BURST:
                Talk(JINROKH_SPELL_4);

                me->CastSpell(me, SPELL_STATIC_BURST);
                events.ScheduleEvent(EVENT_SPEL_STATIC_BURST, JINROKH_SPELL_STATIC_BURST_INTERVAL);
                events.ScheduleEvent(EVENT_SPELL_STATIC_WOUND, JINROKH_SPELL_STATIC_WOUND_INTERVAL);
                break;
            case EVENT_SPELL_STATIC_WOUND:
                if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 50.0f, true))
                    me->CastSpell(target, SPELL_STATIC_WOUND);
                break;
            case EVENT_THUNDERING_THROW:
                if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 50.0f, true))
                {
                    me->CastSpell(target, SPELL_THUNDERING_THROW_DUMMY);
                    target->SetDisableGravity(true);
                    target->SetHover(true);
                    target->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 5.0f, 6.0f);
                }

                Talk(JINROKH_SPELL_2);
                events.ScheduleEvent(EVENT_THUNDERING_THROW, JINROKH_THUNDERING_THROW_INTERVAL_2ND_HIT);
                events.ScheduleEvent(EVENT_THUNDERING_THROW_JUMP_TARGET, 4000);
                break;
            case EVENT_THUNDERING_THROW_JUMP_TARGET:
            {
                if (target_throw = me->getVictim())
                {
                    target_throw->CastSpell(target_throw, 137370); // damage
                    target_throw->AddAura(SPELL_THUNDERING_THROW_STUN, target_throw);
                    target_throw->AddAura(SPELL_THUNDERING_THROW_BOSS_GRASPING_PLAYER, target_throw);
                }
                events.ScheduleEvent(EVENT_THUNDERING_THROW_JUMP_TARGET_2, 5000);
                break;
            }
            case EVENT_THUNDERING_THROW_JUMP_TARGET_2:
            {
                if (target_throw != NULL)
                {
                    if (Creature* trigger_statues = me->FindNearestCreature(TRIGGER_THUNDERING_THROWING, 300.0f, true))
                    {
                        trigger_statues->DespawnOrUnsummon(30000);

                        if (target_throw && target_throw->IsInWorld())
                        {
                            target_throw->SetDisableGravity(false);
                            target_throw->SetHover(false);
                            target_throw->CastSpell(trigger_statues, SPELL_THUNDERING_THROW_JUMPING_TO_STATUE);
                        }
                    }
                }
                break;
            }
            case EVENT_LIGHTNING_STORM:
                me->GetMotionMaster()->MoveJump(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), 5.0f, 6.0f, me->GetOrientation());

                Talk(JINROKH_SPELL_3);

                if (me->GetMap()->IsHeroic())
                    me->m_Events.AddEvent(new jinrokh_lightning_strikes(me, 0), me->m_Events.CalculateTime(800));

                me->CastSpell(me, SPELL_LIGHTNING_VISUAL);
                me->CastSpell(me, SPELL_LIGHTNING_STORM);

                events.ScheduleEvent(EVENT_LIGHTNING_STORM, JINROKH_EVENT_LIGHTNING_STORM_INTERVAL);
                events.ScheduleEvent(EVENT_LIGHTNING_STORM_REMOVE_AURA, 16000); // spell duration from dbc
                break;
            case EVENT_LIGHTNING_STORM_REMOVE_AURA:
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LIGHTNING_STORM_DOT);
                events.CancelEvent(EVENT_LIGHTNING_STRIKE);
                me->m_Events.KillAllEvents(true);

                DespawnCreaturesInArea(TRIGGER_LIGHTNING_STRIKE_STAR, me);
                break;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_jinkorhAI(creature);
    }
};
class npc_focused_lightning_orb : public CreatureScript
{
public:
    npc_focused_lightning_orb() : CreatureScript("npc_focused_lightning_orb") { }

    struct npc_focused_lightning_orbAI : public ScriptedAI
    {
        InstanceScript* pInstance;
        //
        npc_focused_lightning_orbAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        Player* target = NULL;
        int32 orbtick;
        int32 speedstack;

        void Reset()
        {
            orbtick = 500;
            speedstack = 6000;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->CastSpell(me, SPELL_FOCUSED_LIGHTNING_VISUAL, true);
            me->setFaction(16);
            me->SetHealth(6000000);

            target = me->FindNearestPlayer(200.0f, true);
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && who->IsWithinDistInMap(me, 2.0f)) // Player
            {
                me->CastSpell(who, SPELL_FOCUSED_LIGHTNING_UNKNOWN_DAMAGE);
                me->CastSpell(me, SPELL_LIGHTNING_FISSURE_SUMMON);

                if (Creature* water = me->FindNearestCreature(TRIGGER_WATER, 10.0f, true))
                {
                    water->AddAura(SPELL_CONDUCTIVE_WATER_ELECTERT_VISUAL, water);
                    water->RemoveAura(SPELL_CONDUCTIVE_WATER_VISUAL);

                }
                me->DespawnOrUnsummon();
                // i think it's handled autoamtically from dmg increase of fludity               
            }
            else if (who && who->IsInWorld() && who->GetEntry() == TRIGGER_FISSURE && who->IsWithinDistInMap(me, 2.0f)) // FISSURE
            {
                me->CastSpell(who, SPELL_LIGHTNING_FISSURE_IMPLOSION_ORB_CONTACT);
                me->DespawnOrUnsummon();
            }
        }
        void UpdateAI(uint32 const diff)
        {
            // follow
            if (target && target->IsInWorld())
            {
                if (!me->isMoving())
                {
                    me->GetMotionMaster()->MovePoint(1, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
                }
            }

            if (orbtick <= diff)
            {
                std::list<Player*> list_players;
                me->GetPlayerListInGrid(list_players, 300.0f);

                for (auto itr : list_players)
                {
                    itr->CastSpell(itr, SPELL_FOCUSED_LIGHTNING_ORB_TICK);
                }
                orbtick = 500;
            }
            else
                orbtick -= diff;

            if (speedstack <= diff)
            {
                speedstack = 6000;
                me->SetSpeed(MOVE_RUN, me->GetSpeed(MOVE_RUN) + 0.1, true);
            }
            else speedstack -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_focused_lightning_orbAI(creature);
    }
};
/*
class spell_focused_lightning_detonated_water : public SpellScriptLoader
{
public:
spell_focused_lightning_detonated_water() : SpellScriptLoader("spell_focused_lightning_detonated_water") { }

class spell_scholomance_spells_damage_Sp : public SpellScript
{
PrepareSpellScript(spell_scholomance_spells_damage_Sp);

void HandleDamage(SpellEffIndex /*effIndex)
{
if (!GetCaster() || !GetHitUnit())
return;

if (GetHitUnit()->HasAura(SPELL_FLUDITIY))
{
SetHitDamage(GetHitUnit()->GetMaxHealth());
}
}

void Register()
{
OnEffectHitTarget += SpellEffectFn(spell_scholomance_spells_damage_Sp::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
}

};
SpellScript* GetSpellScript() const
{
return new spell_scholomance_spells_damage_Sp();
}
};
*/
class npc_trigger_statue : public CreatureScript
{
public:
    npc_trigger_statue() : CreatureScript("npc_trigger_statue") { }

    struct npc_trigger_statueAI : public CreatureAI
    {
        npc_trigger_statueAI(Creature* creature) : CreatureAI(creature)
        {

        }
        InstanceScript* pInstance;
        Creature* target = NULL;
        Player* playerwho = NULL;
        int32 throwingexplosion;
        int32 watersprout;


        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && who->IsWithinDistInMap(me, 10.0f)) // Player
            {
                if (target = me->FindNearestCreature(TRIGGER_THUNDERING_EXPLODE, 200.0f, true))
                {
                    who->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 15.0f, 8.0f);
                    //who->CastSpell(target, SPELL_THUNDERING_THROW_JUMPING_FROM_STATUE);
                }
                throwingexplosion = 4000;

                playerwho = who->ToPlayer();
            }
        }
        void UpdateAI(uint32 const diff)
        {
            if (InstanceScript* instance = me->GetInstanceScript())
            {
                if (Creature* Jinrokh = instance->instance->GetCreature(instance->GetData64(DATA_JINKORH)))
                {
                    me->SetFacingToObject(Jinrokh);
                }
            }

            if (throwingexplosion <= diff)
            {
                if (target != NULL)
                {
                    playerwho->CastSpell(target, SPELL_THUNDERING_THROW_PLAYER_HIT_GROUND);
                    target->SummonCreature(TRIGGER_WATER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    me->CastSpell(target, SPELL_CONDUTIVE_WATER_LIGHTNING_VISUAL);
                    me->CastSpell(me, SPELL_WATER_SPROUT_VISUAL);

                    target = NULL;
                }
            }
            else
                throwingexplosion -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trigger_statueAI(creature);
    }
};
class npc_lightning_fissure : public CreatureScript
{
public:
    npc_lightning_fissure() : CreatureScript("npc_lightning_fissure") { }

    struct npc_lightning_fissureAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_lightning_fissureAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);

            creature->CastSpell(creature, SPELL_LIGHTNING_FISSURE_EFFECTIVE_AURA);
            creature->setFaction(16);
        }

        int tick;
        void Reset()
        {
            tick = 500;
        }
        void UpdateAI(uint32 const diff)
        {
            if (tick <= diff)
            {
                std::list<Player*> list_players;
                me->GetPlayerListInGrid(list_players, 3.0f);

                for (auto itr : list_players)
                {
                    itr->CastSpell(itr, SPELL_LIGHTNING_FISSURE_CLOSE_YARD_TICK_UNKNOWN);
                }
                tick = 500;
            }
            else
                tick -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lightning_fissureAI(creature);
    }
};
class npc_corrupted_water : public CreatureScript
{
public:
    npc_corrupted_water() : CreatureScript("npc_corrupted_water") { }

    struct npc_corrupted_waterAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_corrupted_waterAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            creature->CastSpell(creature, SPELL_CONDUCTIVE_WATER_VISUAL);
            creature->setFaction(16);
        }
        int32 sizetimer;
        int32 maxsize;

        void Reset()
        {
            sizetimer = 2000;
            maxsize = 0;
        }
        void UpdateAI(uint32 const diff)
        {
            if (sizetimer <= diff)
            {
                if (maxsize < 25)
                {
                    me->CastSpell(me, SPELL_CONDUCTIVE_WATER_SIZE);
                    sizetimer = 2000;

                    maxsize++;
                }
            }
            else
                sizetimer -= diff;

            if (!me->HasAura(SPELL_CONDUCTIVE_WATER_ELECTERT_VISUAL))
            {
                // loads / farts from list;
                std::list<Player*> playerlist;

                float scale = me->GetFloatValue(OBJECT_FIELD_SCALE_X);

                JadeCore::AnyPlayerInObjectRangeCheck u_check(me, scale, true);
                JadeCore::PlayerListSearcher<JadeCore::AnyPlayerInObjectRangeCheck> searcher(me, playerlist, u_check);
                me->VisitNearbyObject(scale, searcher);

                for (std::list<Player*>::const_iterator itr = playerlist.begin(); itr != playerlist.end(); itr++)
                {
                    if (!(*itr)->HasAura(SPELL_FLUDITIY))
                        (*itr)->AddAura(SPELL_FLUDITIY, (*itr));
                }
            }
            else
            {
                // loads / farts from list;
                std::list<Player*> playerlist;

                float scale = me->GetFloatValue(OBJECT_FIELD_SCALE_X);

                JadeCore::AnyPlayerInObjectRangeCheck u_check(me, scale, true);
                JadeCore::PlayerListSearcher<JadeCore::AnyPlayerInObjectRangeCheck> searcher(me, playerlist, u_check);
                me->VisitNearbyObject(scale, searcher);

                for (std::list<Player*>::const_iterator itr = playerlist.begin(); itr != playerlist.end(); itr++)
                {
                    if (!(*itr)->HasAura(SPELL_FLUDITIY))
                        (*itr)->AddAura(SPELL_ELECTRIFYING_WATER, (*itr));
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_corrupted_waterAI(creature);
    }
};

class spell_cast_dot_lightning_storm : public SpellScriptLoader
{
public:
    spell_cast_dot_lightning_storm() : SpellScriptLoader("spell_cast_dot_lightning_storm") { }

    class spell_cast_dot_lightning_storm_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_cast_dot_lightning_storm_AuraScript);

        void HandlePeriodic(constAuraEffectPtr /*aurEff*/)
        {
            PreventDefaultAction();

            std::list<Player*> listplayer;

            GetCaster()->GetPlayerListInGrid(listplayer, 300.0f);

            if (listplayer.empty())
                return;

            for (auto itr : listplayer)
            {
                itr->AddAura(SPELL_LIGHTNING_STORM_DOT, itr);
            }

            // Turn water into electerified waters
            std::list<Creature*> listcreatures;
            GetCaster()->GetCreatureListWithEntryInGrid(listcreatures, TRIGGER_WATER, 300.0f);

            if (listcreatures.empty())
                return;

            for (auto itr : listcreatures)
            {
                if (!itr->HasAura(SPELL_CONDUCTIVE_WATER_ELECTERT_VISUAL))
                {
                    itr->AddAura(SPELL_CONDUCTIVE_WATER_ELECTERT_VISUAL, itr);
                    itr->RemoveAura(SPELL_CONDUCTIVE_WATER_VISUAL);
                }
            }
        }
        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_cast_dot_lightning_storm_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_cast_dot_lightning_storm_AuraScript();
    }
};

class spell_remove_thunder_strike_damage : public SpellScriptLoader
{
public:
    spell_remove_thunder_strike_damage() : SpellScriptLoader("spell_remove_thunder_strike_damage") { }

    class spell_remove_thunder_strike_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_remove_thunder_strike_damage_SpellScript);

        void RemoveInvalidTargets(std::list<WorldObject*>& targets)
        {
            targets.remove(GetCaster());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_remove_thunder_strike_damage_SpellScript::RemoveInvalidTargets, EFFECT_0, 25);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_remove_thunder_strike_damage_SpellScript();
    }
};
class spell_lightning_storm_dot : public SpellScriptLoader
{
public:
    spell_lightning_storm_dot() : SpellScriptLoader("spell_lightning_storm_dot") { }

    class spell_lightning_storm_dot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_lightning_storm_dot_SpellScript);

        void HandleOnHit()
        {
            if (GetCaster() && GetHitUnit())
                SetHitDamage(15000);
        }

        void Register()
        {

            OnHit += SpellHitFn(spell_lightning_storm_dot_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_lightning_storm_dot_SpellScript();
    }
};
class npc_lightning_strike_pillar : public CreatureScript
{
public:
    npc_lightning_strike_pillar() : CreatureScript("npc_lightning_strike_pillar") { }

    struct npc_lightning_strike_pillarAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;
        //
        npc_lightning_strike_pillarAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        int32 orbtick;
        bool activated;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->setFaction(16);
            me->SetHealth(6000000);
            orbtick = 6000000;
            activated = false;
        }
        void DoAction(const int32 action)
        {
            switch (action)
            {
            case ACTION_TRIGGER_PILLAR:
                activated = true;
                orbtick = 3000;
                me->CastSpell(me, SPELL_LIGHNING_STRIKE_VISUAL, false);
                break;
            }
        }
        void UpdateAI(uint32 const diff)
        {
            if (activated)
            {
                if (orbtick <= diff)
                {
                    std::list<Player*> list_players;
                    me->GetPlayerListInGrid(list_players, 4.0f);

                    for (auto itr : list_players)
                    {
                        itr->EnvironmentalDamage(DAMAGE_FIRE, 90000);
                        //itr->CastSpell(itr, SPELL_FOCUSED_LIGHTNING_ORB_TICK);
                    }

                    for (int i = 0; i < 5; i++)
                    {
                        me->SummonCreature(TRIGGER_LIGHTNING_STRIKE_STAR, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 15000);
                    }

                    me->DespawnOrUnsummon(0);
                    me->Respawn();
                    me->AI()->Reset();
                }
                else
                    orbtick -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lightning_strike_pillarAI(creature);
    }
};
class npc_lightning_star : public CreatureScript
{
public:
    npc_lightning_star() : CreatureScript("npc_lightning_star") { }

    struct npc_lightning_starAI : public ScriptedAI
    {
        InstanceScript* pInstance;
        //
        npc_lightning_starAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        int32 orbtick;
        int32 moverandom;

        void Reset()
        {
            orbtick = 2000;
            moverandom = 0;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->setFaction(16);
            me->SetHealth(6000000);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_LIGHTNING_STRIKE_ADD_VISUAL);
            me->SetObjectScale(0.5f);
        }
        void UpdateAI(uint32 const diff)
        {
            if (orbtick <= diff)
            {
                std::list<Player*> list_players;
                me->GetPlayerListInGrid(list_players, 1.2f);

                for (auto itr : list_players)
                {
                    itr->EnvironmentalDamage(DAMAGE_FIRE, 24000);
                }
                orbtick = 2000;
            }
            else
                orbtick -= diff;

            if (moverandom <= diff)
            {
                me->SetSpeed(MOVE_RUN, 14.0f, true);
                me->GetMotionMaster()->MoveRandom(60.0f);
                moverandom = 6000;
            }
            else
                moverandom -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lightning_starAI(creature);
    }
};

class spell_ionization_removal : public SpellScriptLoader
{
public:
    spell_ionization_removal() : SpellScriptLoader("spell_ionization_removal") { }

    class spell_ionization_removalAuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ionization_removalAuraScript);

        void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (GetTarget()->GetTypeId() == TYPEID_PLAYER)
                {
                    if (GetTarget())
                    {
                        std::list<Player*> pl_list;

                        GetTarget()->GetPlayerListInGrid(pl_list, 6.0f);

                        if (pl_list.empty())
                            return;

                        for (auto itr : pl_list)
                        {
                            if (itr->isAlive())
                                itr->EnvironmentalDamage(DAMAGE_FIRE, 45000);
                        }

                        GetTarget()->ToPlayer()->EnvironmentalDamage(DAMAGE_FIRE, 45000);
                        GetTarget()->CastSpell(GetTarget(), SPELL_IONIZATION_EXPLOSION);
                    }
                }
            }
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_ionization_removalAuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ionization_removalAuraScript();
    }
};

void AddSC_boss_jinrokh()
{
    new boss_jinkorh();
    // spells
    new spell_cast_dot_lightning_storm();
    new spell_remove_thunder_strike_damage();
    new spell_ionization_removal();
    //new spell_targets_ionization();
    // npcs
    new npc_corrupted_water();
    new npc_focused_lightning_orb();
    new npc_trigger_statue();
    new npc_lightning_fissure();
    new spell_lightning_storm_dot();
    // heroic
    new npc_lightning_strike_pillar();
    new npc_lightning_star();
}

