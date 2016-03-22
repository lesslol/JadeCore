#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "throne_of_thunder.h"

enum SummonAdds
{
    STONE_GAZER = 69172,
    FARRAKI_SKIRMISHER = 69173,
    FARRAKI_WASTEWALKER = 69175,

    GURUBASHI_BLOODLORD = 69167,
    GURUBASHI_VENOM_PRIEST = 69164,
    VENOMOUS_EFFUSION = 69314,

    DRAKKARI_WARRIOR = 69184,
    DRAKKARI_CHAMPION = 69185,
    DRAKKARI_WARLORD = 69178,

    AMANI_PROTECTOR = 69169,
    AMANAI_FLAME_CASTER = 69168,
    AMANI_WAR_BEAR = 69177,
    AMANI_BEAST_SHAMAN = 69176,

    DINOMANCER = 69221,
    WAR_GOD_JALAK = 69374,

    LIGHTNING_NOVA_TOTEM = 69215,
    FROZEN_ORB = 69268,
    DIREHORN_SPIRIT = 70688,
    //custom
    FARAKKI_CONTROLLER = 250000,
    GURUBASHI_CONTROLLER = 250001,
    DRAKKARI_CONTROLLER = 250002,
    AMANI_CONTROLLER = 250003,
};
enum doors
{
    DOOR_FORK = 90,
    DOOR_GURUB = 91,
    DOOR_DAKKARI = 92,
    DOOR_AMANI = 93,
};
enum actionse
{
    ACTION_CHARGE_DOOR_FORK = 188,
    ACTION_CHARGE_DOOR_GURUB = 189,
    ACTION_CHARGE_DOOR_DAKKARI = 190,
    ACTION_CHARGE_DOOR_AMANI = 191,
};
enum Talks
{
    TALK_KILL = 80, //"Your skull is gonna make a fine ornament for my tusks" // 36012 kill
    TALK_DEATH = 81, //"Horridon... destroy them!" // 36008 death
    TALK_AGGRO = 82, //"Haha.. now it be my turn. You're gonna see what it means to be a war god!" // 36007 aggro
    TALK_INTRO = 83,// "Welcome weaklings, to the rebirth of the Zandalari Empire!" // 36009 intro
    TALK_INTRO02 = 84, //"The tribe has assembled, you face not one force but the combined might of all the Troll Empire. The hand of Zul will spend all the continents of Azeroth once again and the lesser races will know pain!" // 36010 intro
    TALK_INTRO03 = 85, //"Now witness the true might of the beast war, Horridon!" // intro 03 36011
    TALK_GATE_DRAKKARI = 86, //"Drakkari Tribes! show the the might of the frozen north!" // drakkari gate 36013
    TALK_GATE_GURUBASHI = 87, //"Gurubashi send their corpses down the river with your jungle poison" // gurubashi gate 36014
    TALK_GATE_FRAKARI = 88, // "Faraki tribe, flee their flesh with the fury of the sands!" // farakri gate 36015
    TALK_GATE_AMANI = 89, // "Amani tribe! avenge your fallen warlord in the name of Zul'jin!" // amani gate 36016
};
enum Heroic
{
    SPELL_FIRE_FIXATION = 140946,
    // SPELL_WEAK_LINK = , hard coded
    SPELL_DIRE_CALL = 137458,
    CREATURE_DIRE_HORN_SPIRIT = 70688,
};

class spell_double_swipe : public SpellScriptLoader
{
public:
    spell_double_swipe() : SpellScriptLoader("spell_double_swipe") { }

    class spell_double_swipe_front_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_double_swipe_front_SpellScript);

        void RemoveNonConeTargets(std::list<WorldObject*>& targets)
        {
            bool backCheck = backCheck = GetSpellInfo()->Id == 136740 ? true : false;
            for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                if (!backCheck)
                {
                    if (!GetCaster()->isInFront((*itr), M_PI * 0.5f))
                        targets.remove((*itr));
                }
                else
                {
                    if (!GetCaster()->isInBack((*itr)), M_PI * 0.5)
                        targets.remove((*itr));
                }
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_double_swipe_front_SpellScript::RemoveNonConeTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
        }
    };


    SpellScript* GetSpellScript() const
    {
        return new spell_double_swipe_front_SpellScript();
    }
};

class spell_horridon_chain_lightning : public SpellScriptLoader
{
public:
    spell_horridon_chain_lightning() : SpellScriptLoader("spell_horridon_chain_lightning") { }

    class spell_horridon_chain_lightning_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_horridon_chain_lightning_SpellScript);

        bool Validate(SpellEntry const * spellEntry)
        {
            if (!sSpellStore.LookupEntry(spellEntry->Id))
                return false;

            return true;
        }

        bool Load()
        {
            return true;
        }

        void HandleOnHit()
        {
            SetHitDamage(int32(GetHitDamage() + (GetHitDamage() * 0.5)));
        }


        void Register()
        {
            OnHit += SpellHitFn(spell_horridon_chain_lightning_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_horridon_chain_lightning_SpellScript();
    }
};

enum FarkEvents
{
    SUMMON_GAZER_INITAL = 1,
    SUMMON_GAZER = 2,
    SUMMON_WASTE_WALKER_INITAL = 4,
    SUMMON_WASTE_WALKER = 5,
    SUMMON_DINOMANCER = 6,
};

class npc_Fark_Controller : public CreatureScript
{
public:
    npc_Fark_Controller() : CreatureScript("horridon_Fark_Controller") { }

    struct npc_Fark_ControllerAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_Fark_ControllerAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        bool destroyed;
        EventMap events;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            destroyed = false;
            events.ScheduleEvent(SUMMON_GAZER_INITAL, 20 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_GAZER, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WASTE_WALKER_INITAL, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WASTE_WALKER, 40 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_DINOMANCER, 60 * IN_MILLISECONDS);
        }

        void UpdateAI(uint32 const diff)
        {
            if (destroyed)
                return;
            events.Update(diff);
            switch (events.ExecuteEvent())
            {
            case SUMMON_GAZER_INITAL:
                SummonCreature(STONE_GAZER);
                SummonCreature(FARRAKI_SKIRMISHER);
                break;
            case SUMMON_GAZER:
                SummonCreature(STONE_GAZER);
                SummonCreature(FARRAKI_SKIRMISHER);
                events.ScheduleEvent(SUMMON_GAZER, 40 * IN_MILLISECONDS);
                break;
            case SUMMON_WASTE_WALKER_INITAL:
                SummonCreature(FARRAKI_WASTEWALKER);
                break;
            case SUMMON_WASTE_WALKER:
                SummonCreature(FARRAKI_WASTEWALKER);
                SummonCreature(FARRAKI_WASTEWALKER);
                events.ScheduleEvent(SUMMON_WASTE_WALKER, 40 * IN_MILLISECONDS);
                break;
            case SUMMON_DINOMANCER:
                SummonCreature(DINOMANCER);
                break;
            }
        }

        void SummonCreature(uint32 entry)
        {
            if (Creature * summon = me->SummonCreature(entry, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
            {
                summons.Summon(summon);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                    summon->GetMotionMaster()->MoveChase(target);
            }
        }

        void DespawnSummons()
        {
            summons.DespawnAll();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_Fark_ControllerAI(creature);
    }
};

enum GuruEvents
{
    SUMMON_BLOODLORD_INITAL = 1,
    SUMMON_BLOODLORD = 2,
    SUMMON_VENOM_PRIEST_INITAL = 3,
    SUMMON_VENOM_PRIEST = 4,
    SUMMON_G_DINOMANCER = 5,
};

class npc_guru_Controller : public CreatureScript
{
public:
    npc_guru_Controller() : CreatureScript("horridon_guru_Controller") { }

    struct npc_guru_ControllerAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_guru_ControllerAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        bool destroyed;
        EventMap events;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            destroyed = false;
            events.ScheduleEvent(SUMMON_BLOODLORD_INITAL, 20 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_BLOODLORD, 30 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_VENOM_PRIEST_INITAL, 20 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_VENOM_PRIEST, 45 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_G_DINOMANCER, 60 * IN_MILLISECONDS);
        }

        void UpdateAI(uint32 const diff)
        {
            if (destroyed)
                return;
            events.Update(diff);
            switch (events.ExecuteEvent())
            {
            case SUMMON_BLOODLORD_INITAL:
                SummonCreature(GURUBASHI_BLOODLORD);
                break;
            case SUMMON_GAZER:
                SummonCreature(GURUBASHI_BLOODLORD);
                SummonCreature(GURUBASHI_BLOODLORD);
                events.ScheduleEvent(SUMMON_BLOODLORD, 50 * IN_MILLISECONDS);
                break;
            case SUMMON_VENOM_PRIEST_INITAL:
                SummonCreature(GURUBASHI_VENOM_PRIEST);
                break;
            case SUMMON_VENOM_PRIEST:
                SummonCreature(GURUBASHI_VENOM_PRIEST);
                SummonCreature(GURUBASHI_VENOM_PRIEST);
                events.ScheduleEvent(SUMMON_VENOM_PRIEST, 50 * IN_MILLISECONDS);
                break;
            case SUMMON_G_DINOMANCER:
                SummonCreature(DINOMANCER);
                break;
            }
        }

        void SummonCreature(uint32 entry)
        {
            if (Creature * summon = me->SummonCreature(entry, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
            {
                summons.Summon(summon);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                    summon->GetMotionMaster()->MoveChase(target);
            }
        }

        void DespawnSummons()
        {
            summons.DespawnAll();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_guru_ControllerAI(creature);
    }
};

enum DrakEvents
{
    SUMMON_WARRIOR_INITAL = 1,
    SUMMON_WARRIOR = 2,
    SUMMON_WARLORD_INITAL = 3,
    SUMMON_WARLORD = 4,
    SUMMON_D_DINOMANCER
};

class npc_drak_Controller : public CreatureScript
{
public:
    npc_drak_Controller() : CreatureScript("horridon_drak_Controller") { }

    struct npc_drak_ControllerAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_drak_ControllerAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        bool destroyed;
        EventMap events;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            destroyed = false;
            events.ScheduleEvent(SUMMON_WARRIOR_INITAL, 20 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WARRIOR, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WARLORD_INITAL, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WARLORD, 40 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_G_DINOMANCER, 60 * IN_MILLISECONDS);
        }

        void UpdateAI(uint32 const diff)
        {
            if (destroyed)
                return;
            events.Update(diff);
            switch (events.ExecuteEvent())
            {
            case SUMMON_WARRIOR_INITAL:
                SummonCreature(DRAKKARI_CHAMPION);
                SummonCreature(DRAKKARI_WARRIOR);
                break;
            case SUMMON_WARRIOR:
                SummonCreature(DRAKKARI_CHAMPION);
                SummonCreature(DRAKKARI_WARRIOR);
                events.ScheduleEvent(SUMMON_WARRIOR, 35 * IN_MILLISECONDS);
                break;
            case SUMMON_WARLORD_INITAL:
                SummonCreature(DRAKKARI_WARLORD);
                break;
            case SUMMON_WARLORD:
                SummonCreature(DRAKKARI_WARLORD);
                SummonCreature(DRAKKARI_WARLORD);
                events.ScheduleEvent(SUMMON_WARLORD, 35 * IN_MILLISECONDS);
                break;
            case SUMMON_D_DINOMANCER:
                SummonCreature(DINOMANCER);
                break;
            }
        }

        void SummonCreature(uint32 entry)
        {
            if (Creature * summon = me->SummonCreature(entry, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
            {
                summons.Summon(summon);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                    summon->GetMotionMaster()->MoveChase(target);
            }
        }

        void DespawnSummons()
        {
            summons.DespawnAll();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_drak_ControllerAI(creature);
    }
};

enum AmaniAddEvents
{
    SUMMON_PROTECTOR_INITAL = 1,
    SUMMON_PROTECTOR = 2,
    SUMMON_WARBEAR_INITAL = 3,
    SUMMON_WARBEAR = 4,
    SUMMON_A_DINOMANCER = 5,
};

class npc_amani_Controller : public CreatureScript
{
public:
    npc_amani_Controller() : CreatureScript("horridon_amani_Controller") { }

    struct npc_amani_ControllerAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_amani_ControllerAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        bool destroyed;
        EventMap events;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            destroyed = false;
            events.ScheduleEvent(SUMMON_PROTECTOR_INITAL, 20 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_PROTECTOR, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WARBEAR_INITAL, 35 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_WARBEAR, 45 * IN_MILLISECONDS);
            events.ScheduleEvent(SUMMON_A_DINOMANCER, 60 * IN_MILLISECONDS);
        }

        void UpdateAI(uint32 const diff)
        {
            if (destroyed)
                return;
            events.Update(diff);
            switch (events.ExecuteEvent())
            {
            case SUMMON_PROTECTOR_INITAL:
                SummonCreature(AMANI_PROTECTOR);
                SummonCreature(AMANAI_FLAME_CASTER);
                break;
            case SUMMON_PROTECTOR:
                SummonCreature(AMANI_PROTECTOR);
                SummonCreature(AMANAI_FLAME_CASTER);
                events.ScheduleEvent(SUMMON_PROTECTOR, 35 * IN_MILLISECONDS);
                break;
            case SUMMON_WARBEAR_INITAL:
                SummonCreature(AMANI_WAR_BEAR);
                break;
            case SUMMON_WARBEAR:
                SummonCreature(AMANI_WAR_BEAR);
                SummonCreature(AMANI_WAR_BEAR);
                events.ScheduleEvent(SUMMON_WARBEAR, 35 * IN_MILLISECONDS);
                break;
            case SUMMON_A_DINOMANCER:
                SummonCreature(DINOMANCER);
                break;
            }
        }

        void SummonCreature(uint32 entry)
        {
            if (Creature * summon = me->SummonCreature(entry, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
            {
                summons.Summon(summon);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                    summon->GetMotionMaster()->MoveChase(target);
            }
        }

        void DespawnSummons()
        {
            summons.DespawnAll();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_amani_ControllerAI(creature);
    }
};

enum Events
{
    EVENT_HORRIDON_CHARGE = 1,
    EVENT_TRIPLE_PUNCTURE,
    EVENT_DOUBLE_SWIPE,
    EVENT_DIRE_CALL, //Heroic Only
    EVENT_BERSERK,
    EVENT_NEXT_DOOR,
    EVENT_INITAL_DOOR,
};

enum Timers
{
    TIME_BERSERK = (12 * MINUTE) * IN_MILLISECONDS,
    TIME_DINOMANCER = MINUTE* IN_MILLISECONDS,
    TIME_PUNCTURE = 10 * IN_MILLISECONDS,
    TIME_DOUBLE_SWIPE = 16 * IN_MILLISECONDS,
    TIME_CHARGE = 33 * IN_MILLISECONDS,
    TIME_NEXT_DOOR = 40 * IN_MILLISECONDS,
    TIME_INITAL_DOOR = 20 * IN_MILLISECONDS,
};

enum Horridon_Spells
{
    DOUBLE_SWIPE = 136741,
    POST_CHARGE_DOUBLE_SWIPE = 136770, // Why Blizz?
    CHARGE = 136769,
    TRIPLE_PUNCTURE = 136767,
    RAMPAGE = 136821,
    HEADACHE = 137294,
};

enum OrbofControls
{
    ORB_FARAKKI = 218193,
    ORB_GURUBASHI = 218374,
    ORB_DRAKKARI = 218375,
    ORB_AMANI = 218376,
    SPELL_FARAKKI = 137433,
    SPELL_GURUBASHI = 137442,
    SPELL_DRAKKARI = 137443,
    SPELL_AMANI = 137444,
};

class boss_horridon : public CreatureScript
{
public:
    boss_horridon() : CreatureScript("boss_horridon") { }

    struct boss_horridonAI : public BossAI
    {
        boss_horridonAI(Creature* creature) : BossAI(creature, DATA_HORRIDON)
        {
            pInstance = creature->GetInstanceScript();
            me->setFaction(35);
        }

        InstanceScript* pInstance;
        EventMap events;
        uint8 currentDoor;
        bool wargod;
        Unit * chargeTarget;
        uint64 doorGUIDS[3];

        int8 doorNumber;
        void Reset()
        {
            DespawnAdds();
            _Reset();
            events.Reset();
            currentDoor = 0;
            chargeTarget = NULL;
            doorNumber = 0;
            wargod = false;
            for (int i = 0; i <= 3; i++)
                doorGUIDS[i] = 0;

            if (Creature* wargod = me->FindNearestCreature(WAR_GOD_JALAK, 500.0f, true))
            {
                wargod->Respawn();
                wargod->AI()->Reset();
                wargod->GetMotionMaster()->MovePoint(0, wargod->GetHomePosition());
            }
        }
        void DoAction(const int32 action)
        {
            switch (action)
            {
            case ACTION_CHARGE_DOOR_GURUB:
                if (Creature* gurub = me->FindNearestCreature(GURUBASHI_CONTROLLER, 500.0f, true))
                    me->CastSpell(gurub, CHARGE);

                ActivateDoor(2);
                break;
            case ACTION_CHARGE_DOOR_FORK:
                if (Creature* fark = me->FindNearestCreature(FARAKKI_CONTROLLER, 500.0f, true))
                    me->CastSpell(fark, CHARGE);
                ActivateDoor(1);
                break;
            case ACTION_CHARGE_DOOR_AMANI:
                if (Creature* amani = me->FindNearestCreature(AMANI_CONTROLLER, 500.0f, true))
                    me->CastSpell(amani, CHARGE);
                break;
            case ACTION_CHARGE_DOOR_DAKKARI:
                if (Creature* dak = me->FindNearestCreature(DRAKKARI_CONTROLLER, 500.0f, true))
                    me->CastSpell(dak, CHARGE);
                ActivateDoor(3);
                break;
            }
        }
        void JustReachedHome()
        {
            _JustReachedHome();
            DespawnAdds();
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                pInstance->SetBossState(DATA_HORRIDON, FAIL);
            }

            if (GameObject* JinrokhDoor = instance->instance->GetGameObject(instance->GetData64(DATA_HORRIDON)))
            {
                JinrokhDoor->UseDoorOrButton();
            }
        }
        void EnterCombat(Unit* attacker)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();
            }

            if (GameObject* JinrokhDoor = instance->instance->GetGameObject(instance->GetData64(DATA_HORRIDON)))
            {
                JinrokhDoor->UseDoorOrButton();
            }

            if (me->GetMap()->IsHeroic())
                events.ScheduleEvent(EVENT_DIRE_CALL, 60000);

            events.ScheduleEvent(EVENT_DOUBLE_SWIPE, TIME_DOUBLE_SWIPE);
            events.ScheduleEvent(EVENT_HORRIDON_CHARGE, TIME_CHARGE);
            events.ScheduleEvent(EVENT_TRIPLE_PUNCTURE, TIME_PUNCTURE);
            events.ScheduleEvent(EVENT_INITAL_DOOR, TIME_INITAL_DOOR);
            events.ScheduleEvent(EVENT_BERSERK, TIME_BERSERK);
        }
        void JustDied(Unit* killer)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                pInstance->SetBossState(DATA_HORRIDON, DONE);
            }
            DespawnAdds();
            _JustDied();
        }

        void AddSummon(Creature * creature)
        {
            summons.Summon(creature);
        }

        void ChargeDoor()
        {
            me->InterruptNonMeleeSpells(true);
            switch (currentDoor)
            {
            case 0:
                me->GetMotionMaster()->MoveCharge(5503.f, 5681.f, 130.f);
                break;
            case 1:
                me->GetMotionMaster()->MoveCharge(5364.f, 5686.f, 130.f);
                break;
            case 2:
                me->GetMotionMaster()->MoveCharge(5498.f, 5819.f, 130.f);
                break;
            case 3:
                me->GetMotionMaster()->MoveCharge(5365.f, 5818.f, 130.f);
                break;
            }
        }

        void DespawnAdds()
        {
            me->DespawnCreaturesInArea(STONE_GAZER);
            me->DespawnCreaturesInArea(FARRAKI_SKIRMISHER);
            me->DespawnCreaturesInArea(FARRAKI_WASTEWALKER);
            me->DespawnCreaturesInArea(GURUBASHI_BLOODLORD);
            me->DespawnCreaturesInArea(GURUBASHI_VENOM_PRIEST);
            me->DespawnCreaturesInArea(VENOMOUS_EFFUSION);
            me->DespawnCreaturesInArea(DRAKKARI_WARRIOR);
            me->DespawnCreaturesInArea(DRAKKARI_CHAMPION);
            me->DespawnCreaturesInArea(DRAKKARI_WARLORD);
            me->DespawnCreaturesInArea(AMANI_PROTECTOR);
            me->DespawnCreaturesInArea(AMANAI_FLAME_CASTER);
            me->DespawnCreaturesInArea(AMANI_WAR_BEAR);
            me->DespawnCreaturesInArea(AMANI_BEAST_SHAMAN);
            me->DespawnCreaturesInArea(250003);

            if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[0]))
                static_cast<npc_Fark_Controller::npc_Fark_ControllerAI*>(controller->GetAI())->DespawnSummons();

            if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[1]))
                static_cast<npc_guru_Controller::npc_guru_ControllerAI*>(controller->GetAI())->DespawnSummons();

            if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[2]))
                static_cast<npc_drak_Controller::npc_drak_ControllerAI*>(controller->GetAI())->DespawnSummons();

            if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[3]))
                static_cast<npc_amani_Controller::npc_amani_ControllerAI*>(controller->GetAI())->DespawnSummons();
            summons.DespawnAll();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->GetHealthPct() <= 30.f && !wargod)
            {
                if (Creature *wergod = me->FindNearestCreature(WAR_GOD_JALAK, 500.0f, true))
                {
                    wergod->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    wergod->setFaction(16);

                    wergod->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                }
                wargod = true;
            }
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_DIRE_CALL:
            {
                me->CastSpell(me, SPELL_DIRE_CALL);

                Position pos;
                me->GetRandomNearPosition(pos, 30.0f);

                Creature* spirit = me->SummonCreature(CREATURE_DIRE_HORN_SPIRIT, pos, TEMPSUMMON_DEAD_DESPAWN);

                std::list<Player*> pl_list;
                std::list<Player*>::const_iterator it = pl_list.begin();
                std::advance(it, urand(0, pl_list.size() - 1));

                while ((*it)->HasAura(SPELL_FIRE_FIXATION))
                {
                    std::list<Player*> pl_list;
                    std::list<Player*>::const_iterator it = pl_list.begin();
                    std::advance(it, urand(0, pl_list.size() - 1));
                }

                spirit->AddAura(SPELL_FIRE_FIXATION, (*it));
                spirit->GetMotionMaster()->MoveFollow((*it), 0, 0, MOTION_SLOT_ACTIVE);
                spirit->AddThreat((*it), 6000.0f);

                events.ScheduleEvent(EVENT_DIRE_CALL, 60000);
                break;
            }
            case EVENT_BERSERK:
                me->CastSpell(me, 61715);
                break;
            case EVENT_DOUBLE_SWIPE:
                me->CastSpell(me, DOUBLE_SWIPE);
                events.ScheduleEvent(EVENT_DOUBLE_SWIPE, TIME_DOUBLE_SWIPE);
                break;
            case EVENT_HORRIDON_CHARGE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                {
                    me->CastSpell(target, CHARGE);
                    chargeTarget = target;
                }
                events.ScheduleEvent(EVENT_HORRIDON_CHARGE, TIME_CHARGE);
                break;
            case EVENT_TRIPLE_PUNCTURE:
                DoCastVictim(TRIPLE_PUNCTURE);
                events.ScheduleEvent(EVENT_TRIPLE_PUNCTURE, TIME_PUNCTURE);
                break;
            case EVENT_INITAL_DOOR:
                currentDoor = 0;
                ActivateDoor(0);
                break;
            case EVENT_NEXT_DOOR:
                currentDoor += 1;
                ActivateDoor(currentDoor);
                break;
            }

            DoMeleeAttackIfReady();
        }
        uint8 GetActiveDoor() { return currentDoor; }

        void ActivateDoor(uint8 door)
        {
            doorNumber = 0;

            if (!me->HasAura(137240))
            {
                me->AddAura(137240, me);
            }
            else
            {
                AuraPtr aura = me->GetAura(137240);

                if (aura)
                {
                    aura->SetStackAmount(aura->GetStackAmount() + 1);
                }
            }

            if (Creature* jalak = me->FindNearestCreature(WAR_GOD_JALAK, 1000.0f, true))
            {
                Creature * control = nullptr;
                if (pInstance)
                {
                    switch (door)
                    {
                    case 0:
                        doorNumber = 90,
                            control = me->SummonCreature(FARAKKI_CONTROLLER, 5503.f, 5681.f, 130.f);

                        jalak->AI()->Talk(TALK_GATE_FRAKARI);
                        break;
                    case 1:
                        doorNumber = 91,
                            control = me->SummonCreature(GURUBASHI_CONTROLLER, 5364.f, 5686.f, 130.f);

                        jalak->AI()->Talk(TALK_GATE_GURUBASHI);
                        break;
                    case 2:
                        doorNumber = 92,
                            control = me->SummonCreature(DRAKKARI_CONTROLLER, 5498.f, 5819.f, 130.f);

                        jalak->AI()->Talk(TALK_GATE_DRAKKARI);
                        break;
                    case 3:
                        doorNumber = 93,
                            control = me->SummonCreature(AMANI_CONTROLLER, 5365.f, 5818.f, 130.f);

                        jalak->AI()->Talk(TALK_GATE_AMANI);
                        break;
                    case 4:
                        if (!wargod)
                        {
                            if (Creature *wergod = me->FindNearestCreature(WAR_GOD_JALAK, 500.0f, true))
                            {
                                wergod->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                wergod->setFaction(16);

                                wergod->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                            }
                            wargod = true;
                        }
                        break;
                    }
                    if (control)
                    {
                        AddSummon(control);
                        doorGUIDS[door] = control->GetGUID();
                    }
                }
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                if (id == EVENT_CHARGE)
                {
                    if (chargeTarget)
                    {
                        me->InterruptNonMeleeSpells(true);
                        me->CastSpell(me, POST_CHARGE_DOUBLE_SWIPE);
                        events.CancelEvent(EVENT_DOUBLE_SWIPE); //Reschedule (blizzlike)
                        events.ScheduleEvent(EVENT_DOUBLE_SWIPE, TIME_DOUBLE_SWIPE);
                    }
                    else
                    {
                        me->InterruptNonMeleeSpells(true);
                        DoCast(HEADACHE);
                        DestroyDoor(currentDoor);
                        events.ScheduleEvent(EVENT_NEXT_DOOR, TIME_NEXT_DOOR);
                    }
                    chargeTarget = NULL;
                }
            }
        }

        void DestroyDoor(uint8 door)
        {
            switch (door)
            {
            case 0:
                if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[0]))
                    static_cast<npc_Fark_Controller::npc_Fark_ControllerAI*>(controller->GetAI())->destroyed = true;
                break;
            case 1:
                if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[1]))
                    static_cast<npc_guru_Controller::npc_guru_ControllerAI*>(controller->GetAI())->destroyed = true;
                break;
            case 2:
                if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[2]))
                    static_cast<npc_drak_Controller::npc_drak_ControllerAI*>(controller->GetAI())->destroyed = true;
                break;
            case 3:
                if (Creature* controller = me->GetMap()->GetCreature(doorGUIDS[3]))
                    static_cast<npc_amani_Controller::npc_amani_ControllerAI*>(controller->GetAI())->destroyed = true;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_horridonAI(creature);
    }
};

enum FarrakiSpells
{
    SPELL_STONE_GAZE = 136708,
    SPELL_BLAZING_SUNLIGHT = 136719,
    SPELL_SAND_TRAP = 136725,
    SPELL_SAND_TRAP_TRIGGER = 136724,
};

enum FarrakiEvents
{
    EVENT_STONE_GAZE = 1,
    EVENT_SUNLIGHT = 2,
    EVENT_SAND_TRAP = 3,
};

enum FarrakiTimers
{
    TIMER_STONE_GAZE = 12 * IN_MILLISECONDS, // Guessed
    TIMER_SUNLIGHT = 6 * IN_MILLISECONDS, // Guessed
    TIMER_SAND_TRAP = 10 * IN_MILLISECONDS, // Guessed
};

class npc_stonegazer : public CreatureScript
{
public:
    npc_stonegazer() : CreatureScript("horridon_stonegazer") { }

    struct npc_stonegazerAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_stonegazerAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_STONE_GAZE, TIMER_STONE_GAZE);
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_STONE_GAZE:
                DoCastVictim(SPELL_STONE_GAZE);
                events.ScheduleEvent(EVENT_STONE_GAZE, TIMER_STONE_GAZE);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stonegazerAI(creature);
    }
};

class npc_wastewalker : public CreatureScript
{
public:
    npc_wastewalker() : CreatureScript("horridon_wastewalker") { }

    struct npc_wastewalkerAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_wastewalkerAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_SUNLIGHT, TIMER_SUNLIGHT);
            events.ScheduleEvent(EVENT_SAND_TRAP, TIMER_SAND_TRAP);
        }


        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_SUNLIGHT:
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_BLAZING_SUNLIGHT);
                events.ScheduleEvent(EVENT_SUNLIGHT, TIMER_SUNLIGHT);
                break;
            case EVENT_SAND_TRAP:
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                    DoCast(target, SPELL_SAND_TRAP);
                events.ScheduleEvent(EVENT_SAND_TRAP, TIMER_SAND_TRAP);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wastewalkerAI(creature);
    }
};

class npc_sand_trap : public CreatureScript
{
public:
    npc_sand_trap() : CreatureScript("horridon_sand_trap") { }

    struct npc_sand_trapAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_sand_trapAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            creature->CastSpell(creature, SPELL_SAND_TRAP_TRIGGER);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sand_trapAI(creature);
    }
};

enum GurubashiSpells
{
    SPELL_RENDING_CHARGE = 136653,
    SPELL_VENOM_BOLT_VOLLEY = 136587,
    SPELL_VENOMOUS_EFFUSION = 136644,
    SPELL_LIVING_POISON = 136645,
};

enum GurubashiTimer
{
    TIMER_RENDING_CHARGE = 10 * IN_MILLISECONDS, // Guessed
    TIMER_VENOM_VOLLEY = 6 * IN_MILLISECONDS, // Guessed
    TIMER_EFFUSION = 20 * IN_MILLISECONDS, // Guessed
};

enum GurubashiEvent
{
    EVENT_RENDING_CHARGE = 1,
    EVENT_VOLLEY = 2,
    EVENT_EFFUSION = 3,
};

class npc_bloordlord : public CreatureScript
{
public:
    npc_bloordlord() : CreatureScript("horridon_bloordlord") { }

    struct npc_bloordlordAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_bloordlordAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_RENDING_CHARGE, TIMER_RENDING_CHARGE);
            DoCast(attacker, SPELL_RENDING_CHARGE);
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_RENDING_CHARGE:
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                {
                    DoCast(target, SPELL_RENDING_CHARGE);
                    me->getThreatManager().addThreat(target, 10000);
                    me->TauntApply(target);
                }
                events.ScheduleEvent(EVENT_RENDING_CHARGE, TIMER_RENDING_CHARGE);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloordlordAI(creature);
    }
};

class npc_venom_priest : public CreatureScript
{
public:
    npc_venom_priest() : CreatureScript("horridon_venom_priest") { }

    struct npc_venom_priestAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_venom_priestAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_VOLLEY, TIMER_VENOM_VOLLEY);
            events.ScheduleEvent(EVENT_EFFUSION, TIMER_EFFUSION);
        }


        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_VOLLEY:
                DoCast(SPELL_VENOM_BOLT_VOLLEY);
                events.ScheduleEvent(EVENT_VOLLEY, TIMER_VENOM_VOLLEY);
                break;
            case EVENT_EFFUSION:
                DoCast(SPELL_VENOMOUS_EFFUSION);
                events.ScheduleEvent(EVENT_EFFUSION, TIMER_EFFUSION);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_venom_priestAI(creature);
    }
};

class npc_venom_effusion : public CreatureScript
{
public:
    npc_venom_effusion() : CreatureScript("horridon_venom_effusion") { }

    struct npc_venom_effusionAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_venom_effusionAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
            if (Player * target = me->SelectNearestPlayerNotGM())
                me->GetAI()->AttackStart(target);
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_VOLLEY, TIMER_VENOM_VOLLEY);
        }


        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_VOLLEY:
                DoCast(SPELL_VENOM_BOLT_VOLLEY);
                events.ScheduleEvent(EVENT_VOLLEY, TIMER_VENOM_VOLLEY);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_venom_effusionAI(creature);
    }
};

class npc_living_poison : public CreatureScript
{
public:
    npc_living_poison() : CreatureScript("horridon_living_poison") { }

    struct npc_living_poisonAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_living_poisonAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            creature->CastSpell(creature, SPELL_LIVING_POISON);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_living_poisonAI(creature);
    }
};

enum DrakkariSpells
{
    SPELL_UNCONTROLLED = 136709,
    SPELL_MORTAL_STRIKE = 136670,
    SPELL_FROZEN_ORB = 136564,
    SPELL_FROZEN_BOLT = 136573,
};

enum DrakkariEvents
{
    EVENT_MORTAL_STRIKE = 1,
    EVENT_FROZEN_ORB = 2,
    EVENT_NEW_TARGET = 3,
};

enum DrakkariTimer
{
    TIMER_MORTAL_STRIKE = 8 * IN_MILLISECONDS,
    TIMER_FROZEN_ORB = 12 * IN_MILLISECONDS,
    TIMER_NEW_TARGET = 10 * IN_MILLISECONDS,
};

class npc_uncontrolled : public CreatureScript
{
public:
    npc_uncontrolled() : CreatureScript("horridon_uncontrolled") { }

    struct npc_uncontrolledAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_uncontrolledAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            DoCast(SPELL_UNCONTROLLED);
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            DoCast(SPELL_UNCONTROLLED);
            events.ScheduleEvent(EVENT_NEW_TARGET, TIMER_NEW_TARGET);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_uncontrolledAI(creature);
    }
};

class npc_frozen_warlord : public CreatureScript
{
public:
    npc_frozen_warlord() : CreatureScript("horridon_frozen_warlord") { }

    struct npc_frozen_warlordAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_frozen_warlordAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_MORTAL_STRIKE, TIMER_MORTAL_STRIKE);
            events.ScheduleEvent(EVENT_FROZEN_ORB, TIMER_FROZEN_ORB);
        }


        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_MORTAL_STRIKE:
                DoCastVictim(SPELL_MORTAL_STRIKE);
                events.ScheduleEvent(EVENT_MORTAL_STRIKE, TIMER_MORTAL_STRIKE);
                break;
            case EVENT_FROZEN_ORB:
                DoCast(SPELL_FROZEN_ORB);
                events.ScheduleEvent(EVENT_FROZEN_ORB, TIMER_FROZEN_ORB);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frozen_warlordAI(creature);
    }
};

class npc_frozen_orb : public CreatureScript
{
public:
    npc_frozen_orb() : CreatureScript("horridon_frozen_orb") { }

    struct npc_frozen_orbAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_frozen_orbAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            creature->CastSpell(creature, SPELL_FROZEN_BOLT);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frozen_orbAI(creature);
    }
};

enum AmaniSpells
{
    SPELL_FIREBALL = 136465,
    SPELL_SWIPE = 136463,
    SPELL_CHAIN_LIGHTNING = 136480,
    SPELL_HEX = 136512,
    SPELL_LIGHTNING_TOTEM = 136487,
    SPELL_LIGHTNING_NOVA = 136489,
};

enum AmaniEvents
{
    EVENT_FIREBALL = 1,
    EVENT_SWIPE = 2,
    EVENT_CHAIN_LIGHTNING = 3,
    EVENT_HEX = 4,
    EVENT_LIGHTNING_TOTEM = 5,
};

enum AmaniTimer
{
    TIMER_FIREBALL = 6 * IN_MILLISECONDS,
    TIMER_SWIPE = 5 * IN_MILLISECONDS,
    TIMER_CHAIN_LIGHTNING = 7 * IN_MILLISECONDS,
    TIMER_HEX = 12 * IN_MILLISECONDS,
    TIMER_LIGHTNING_TOTEM = 15 * IN_MILLISECONDS,
};

class npc_flamecaster : public CreatureScript
{
public:
    npc_flamecaster() : CreatureScript("horridon_flamecaster") { }

    struct npc_flamecasterAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_flamecasterAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_FIREBALL, TIMER_FIREBALL);
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_FIREBALL:
                DoCastVictim(SPELL_FIREBALL);
                events.ScheduleEvent(EVENT_FIREBALL, TIMER_FIREBALL);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flamecasterAI(creature);
    }
};

class npc_warbear : public CreatureScript
{
public:
    npc_warbear() : CreatureScript("horridon_warbear") { }

    struct npc_warbearAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_warbearAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void JustDied(Unit* killer)
        {
            SummonCreature(AMANI_BEAST_SHAMAN);
        }

        void SummonCreature(uint32 entry)
        {
            if (Creature * summon = me->SummonCreature(entry, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
            {
                if (pInstance)
                {
                    if (Creature * horridon = me->GetCreature(*me, pInstance->GetData64(DATA_HORRIDON)))
                        static_cast<boss_horridon::boss_horridonAI*>(horridon->GetAI())->AddSummon(summon);
                }
            }
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_SWIPE, TIMER_SWIPE);
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_SWIPE:
                DoCastVictim(SPELL_SWIPE);
                events.ScheduleEvent(EVENT_SWIPE, TIMER_SWIPE);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_warbearAI(creature);
    }
};

class npc_beast_shaman : public CreatureScript
{
public:
    npc_beast_shaman() : CreatureScript("horridon_beast_shaman") { }

    struct npc_beast_shamanAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_beast_shamanAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, TIMER_CHAIN_LIGHTNING);
            events.ScheduleEvent(EVENT_HEX, TIMER_HEX);
            events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, TIMER_LIGHTNING_TOTEM);
        }


        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_CHAIN_LIGHTNING:
                DoCastVictim(SPELL_CHAIN_LIGHTNING);
                events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, TIMER_CHAIN_LIGHTNING);
                break;
            case EVENT_HEX:
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_HEX);
                events.ScheduleEvent(EVENT_HEX, TIMER_HEX);
                break;
            case EVENT_LIGHTNING_TOTEM:
                DoCast(SPELL_LIGHTNING_TOTEM);
                events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, TIMER_LIGHTNING_TOTEM);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_beast_shamanAI(creature);
    }
};

class npc_lightning_totem : public CreatureScript
{
public:
    npc_lightning_totem() : CreatureScript("horridon_lightning_totem") { }

    struct npc_lightning_totemAI : public Scripted_NoMovementAI
    {
        InstanceScript* pInstance;

        npc_lightning_totemAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->CastSpell(creature, SPELL_LIGHTNING_NOVA);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lightning_totemAI(creature);
    }
};

enum ZandalariSpells
{
    SPELL_DINO_MENDING = 136797,
    SPELL_DINO_FORM = 137237,
    SPELL_BESTIAL_CRY = 136817,
};

enum ZandalariEvents
{
    EVENT_MENDING = 1,
    EVENT_BESTIAL_CRY = 2,
};

enum Zandalari_Timers
{
    TIMER_MENDING = 30 * IN_MILLISECONDS,
    TIMER_BESTIAL_CRY = 15 * IN_MILLISECONDS,
};

class npc_dinomancer : public CreatureScript
{
public:
    npc_dinomancer() : CreatureScript("horridon_dinomancer") { }

    struct npc_dinomancerAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_dinomancerAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }
        EventMap events;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_MENDING, TIMER_MENDING);
            if (Creature * horridon = me->FindNearestCreature(68476, 250.f))
                DoCast(horridon, SPELL_DINO_MENDING);
        }

        void EnterCombat(Unit* attacker)
        {
            events.ScheduleEvent(EVENT_MENDING, TIMER_MENDING);
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            }
        }

        void JustDied(Unit* killer)
        {
            if (pInstance)
            {
                if (Creature* horridon = me->FindNearestCreature(BOSS_HORRIDON, 500.0f, true))
                {
                    if (boss_horridon::boss_horridonAI* linkAI = CAST_AI(boss_horridon::boss_horridonAI, horridon->GetAI()))
                    {
                        switch (linkAI->doorNumber)
                        {
                        case DOOR_FORK:
                        {
                            horridon->GetAI()->DoAction(ACTION_CHARGE_DOOR_FORK);
                            if (Creature * fork_trigger = me->FindNearestCreature(FARAKKI_CONTROLLER, 250.f))
                            {
                                fork_trigger->DespawnOrUnsummon(500);
                            }
                            break;
                        }
                        case DOOR_DAKKARI:
                        {
                            horridon->GetAI()->DoAction(ACTION_CHARGE_DOOR_DAKKARI);
                            if (Creature * dakkari_trigger = me->FindNearestCreature(DRAKKARI_CONTROLLER, 250.f))
                            {
                                dakkari_trigger->DespawnOrUnsummon(500);
                            }
                            break;
                        }
                        case DOOR_GURUB:
                        {
                            horridon->GetAI()->DoAction(ACTION_CHARGE_DOOR_GURUB);
                            if (Creature * gurub_trigger = me->FindNearestCreature(GURUBASHI_CONTROLLER, 250.f))
                            {
                                gurub_trigger->DespawnOrUnsummon(500);
                            }
                            break;
                        }
                        case DOOR_AMANI:
                        {
                            horridon->GetAI()->DoAction(ACTION_CHARGE_DOOR_AMANI);
                            if (Creature * amani_trigger = me->FindNearestCreature(AMANI_CONTROLLER, 250.f))
                            {
                                amani_trigger->DespawnOrUnsummon(500);
                            }
                            break;
                        }
                        }
                    }
                }


                /*
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                if (Creature * horridon = me->FindNearestCreature(68476, 250.f))
                {
                static_cast<boss_horridon::boss_horridonAI*>(horridon->GetAI())->ChargeDoor();
                /*
                switch (static_cast<boss_horridon::boss_horridonAI*>(horridon->GetAI())->GetActiveDoor())
                {
                case 0:
                me->SummonGameObject(ORB_FARAKKI, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, 0, 0, 0, 0, 300);
                break;
                case 1:
                me->SummonGameObject(ORB_GURUBASHI, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, 0, 0, 0, 0, 300);
                break;
                case 2:
                me->SummonGameObject(ORB_DRAKKARI, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, 0, 0, 0, 0, 300);
                break;
                case 3:
                me->SummonGameObject(ORB_AMANI, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, 0, 0, 0, 0, 300);
                break;
                }
                }
                */
            }

        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetHealthPct() <= 50.f && !me->HasAura(SPELL_DINO_FORM))
            {
                events.CancelEvent(EVENT_MENDING);
                DoCast(SPELL_DINO_FORM);
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_MENDING:
                if (Creature * horridon = me->FindNearestCreature(68476, 250.f))
                    DoCast(horridon, SPELL_DINO_MENDING);

                events.ScheduleEvent(EVENT_MENDING, TIMER_MENDING);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dinomancerAI(creature);
    }
};

Position homepositionhorridon = { 5494.64f, 5753.87f, 129.604f, 2.547900f };
class wargod_intro : public BasicEvent
{
public:
    explicit wargod_intro(Unit* unit, int value) : obj(unit), modifier(value)
    {
    }

    bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
    {
        if (InstanceScript* instance = obj->GetInstanceScript())
        {
            if (Creature* war_god = obj->FindNearestCreature(WAR_GOD_JALAK, 500.0f, true))
            {
                if (Creature* horridon = obj->FindNearestCreature(BOSS_HORRIDON, 500.0f, true))
                {
                    switch (modifier)
                    {
                    case 0:
                        war_god->AI()->Talk(TALK_INTRO);
                        war_god->m_Events.AddEvent(new wargod_intro(war_god, 1), war_god->m_Events.CalculateTime(8000));
                        break;
                    case 1:
                        war_god->AI()->Talk(TALK_INTRO02);
                        war_god->m_Events.AddEvent(new wargod_intro(war_god, 2), war_god->m_Events.CalculateTime(8000));
                        break;
                    case 2:
                        war_god->AI()->Talk(TALK_INTRO03);
                        war_god->m_Events.AddEvent(new wargod_intro(war_god, 3), war_god->m_Events.CalculateTime(6000));
                        break;
                    case 3:
                        horridon->GetMotionMaster()->MovePoint(0, homepositionhorridon.GetPositionX(), homepositionhorridon.GetPositionY(), homepositionhorridon.GetPositionZ());
                        horridon->SetHomePosition(homepositionhorridon);
                        horridon->setFaction(16);
                        horridon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NON_ATTACKABLE);
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
class npc_wargodjalak : public CreatureScript
{
public:
    npc_wargodjalak() : CreatureScript("horridon_wargodjalak") { }

    struct npc_wargodjalakAI : public ScriptedAI
    {
        InstanceScript* pInstance;

        npc_wargodjalakAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
            intro = false;
        }
        EventMap events;
        bool intro;
        void Reset()
        {
            events.Reset();
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        }
        void EnterCombat(Unit* attacker)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            }
            Talk(TALK_AGGRO);
            events.ScheduleEvent(EVENT_BESTIAL_CRY, TIMER_BESTIAL_CRY);
        }
        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && !intro && me->IsWithinDistInMap(who, 90.0f))
            {
                intro = true;
                Talk(TALK_INTRO);

                me->m_Events.AddEvent(new wargod_intro(me, 0), me->m_Events.CalculateTime(4000));
            }
        }
        void JustDied(Unit* killer)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                if (Creature * horridon = me->FindNearestCreature(68476, 250.f))
                    horridon->CastSpell(horridon, RAMPAGE);

                Talk(TALK_DEATH);
            }
        }
        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
                Talk(TALK_KILL);
        }
        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
            case EVENT_BESTIAL_CRY:
                DoCast(SPELL_BESTIAL_CRY);
                events.ScheduleEvent(EVENT_MENDING, TIMER_MENDING);
                break;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wargodjalakAI(creature);
    }
};
class npc_direhornspirit : public CreatureScript
{
public:
    npc_direhornspirit() : CreatureScript("npc_direhornspirit") { }

    struct npc_direhornspiritAI : public ScriptedAI
    {
        npc_direhornspiritAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset() override
        {
            events.Reset();
        }
        void DamageTaken(Unit* attacker, uint32 &damage, SpellInfo const* p_SpellInfo)
        {
            if (attacker && attacker->IsInWorld())
            {
                me->GetMotionMaster()->MoveKnockbackFrom(me->GetPositionX(), me->GetPositionY(), 5.0f, 5.0f);
            }
        }
        void OnAddThreat(Unit* victim, float& fThreat, SpellSchoolMask /*schoolMask*/, SpellInfo const* /*threatSpell*/)
        {
            if (!victim->HasAura(SPELL_FIRE_FIXATION, me->GetGUID()))
                fThreat = 0;
            return;
        }
        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    private:

    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_direhornspiritAI(creature);
    }
};
void AddSC_boss_horridon()
{
    new spell_double_swipe();
    new boss_horridon();
    new npc_stonegazer();
    new npc_wastewalker();
    new npc_sand_trap();
    new npc_bloordlord();
    new npc_venom_priest();
    new npc_venom_effusion();
    new npc_living_poison();
    new npc_uncontrolled();
    new npc_frozen_warlord();
    new npc_frozen_orb();
    new npc_flamecaster();
    new npc_warbear();
    new npc_beast_shaman();
    new npc_lightning_totem();
    new npc_dinomancer();
    new npc_wargodjalak();
    new npc_Fark_Controller();
    new npc_guru_Controller();
    new npc_drak_Controller();
    new npc_amani_Controller();
    new spell_horridon_chain_lightning();
    new npc_direhornspirit();
}
