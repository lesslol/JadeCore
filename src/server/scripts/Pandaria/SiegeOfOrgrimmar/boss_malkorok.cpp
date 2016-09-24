#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eBosses
{
	BOSS_MALKOROK,
};

enum eSpells
{
	SPELL_ACIENT_MIASMA = 142861, 
	SPELL_ARCING_SMASH = 142815, 
	SPELL_SEISMIC_SLAM = 142851, 
	SPELL_DISPLACED_ENERGY = 142913, 
	SPELL_EXPEL_MIASMA = 143199, 
	SPELL_BREATH_OF_YSHAARJ = 142842, 
	SPELL_ERADICATE = 143916,  
	SPELL_BLOOD_RAGE = 142879,
    SPELL_IMPLODING_ENERGY = 142986,
	SPELL_FATAL_STRIKE = 142990
};

enum eEvents
{
	EVENT_ARCING_SMASH = 2,
	EVENT_SEISMIC_SLAM = 3,
	EVENT_DISPLACED_ENERGY = 4,
	EVENT_ERADICATE = 7,
	EVENT_BREATH_OF_YSHARRJ = 6,
	EVENT_EXPEL_MIASMA = 5,
	EVENT_ARCING_SMASH_TARGET_SPAWN = 8,
	EVENT_AGRESSIVE = 10,
	EVENT_BLOOD_RAGE = 11,
	EVENT_PHASE1 = 12,
	EVENT_IMPLODING_ENERY = 13
};

enum Phases
{
	PHASE_ONE = 1,
	PHASE_TWO = 2,
};

enum eCreatures
{
	CREATURE_Malkorok = 71454,
	CREATURE_ARCING_SMASH = 71455
};

enum eTexts
{
	MALKOROK_INTRO,
	MALKOROK_AGGRO,
	MALKOROK_ARCING_SMASH_1,
	MALKOROK_ARCING_SMASH_2,
	MALKOROK_ARCING_SMASH_3,
	MALKOROK_BREATH_OF_YSHAARJ_1,
	MALKOROK_BREATH_OF_YSHAARJ_2,
	MALKOROK_BLOOD_RAGE_1,
	MALKOROK_BLOOD_RAGE_2,
	MALKOROK_BERSERK,
	MALKOROK_WIPE,
	MALKOROK_DEATH
};

class boss_malkorok : public CreatureScript
{
public:
	boss_malkorok() : CreatureScript("boss_malkorok") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_malkorok_AI(creature);
	}

	struct boss_malkorok_AI : public BossAI
	{
		boss_malkorok_AI(Creature* creature) : BossAI(creature, BOSS_MALKOROK)
		{}
		void Reset()
		{
			me->SetReactState(REACT_AGGRESSIVE);
			events.Reset();
			_Reset();
			me->setFaction(14);
			me->setPowerType(POWER_RAGE);
			me->SetMaxPower(POWER_RAGE, 100);
			events.SetPhase(PHASE_ONE);
		}

		void JustDied(Unit* /*killer*/)
		{
			DoCastToAllHostilePlayers(SPELL_ACIENT_MIASMA);
			Talk(MALKOROK_AGGRO);
			std::list<Player*> pl_list;
			me->GetPlayerListInGrid(pl_list, 500.0f);
			for (auto itr : pl_list)
			{
				itr->RemoveAura(SPELL_ACIENT_MIASMA);
			}
		}

		void KilledUnit(Unit* u)
		{
		}


		void EnterCombat(Unit* unit)
		{
			DoCastToAllHostilePlayers(SPELL_ACIENT_MIASMA);           
			Talk(MALKOROK_AGGRO);
			std::list<Player*> pl_list;
			me->GetPlayerListInGrid(pl_list, 500.0f);
			for (auto itr : pl_list)
			{
				me->AddAura(SPELL_ACIENT_MIASMA, itr);
			}
			events.SetPhase(PHASE_ONE);
			events.ScheduleEvent(EVENT_SEISMIC_SLAM, 5000, PHASE_ONE);
			events.ScheduleEvent(EVENT_ARCING_SMASH, 11000, PHASE_ONE);
			events.ScheduleEvent(EVENT_BREATH_OF_YSHARRJ, 68000, PHASE_ONE);
			me->AddAura(SPELL_FATAL_STRIKE, me);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_ARCING_SMASH:
				{
					me->CastSpell(me->FindNearestCreature(CREATURE_ARCING_SMASH, 50.00f, true), SPELL_ARCING_SMASH);
					events.ScheduleEvent(EVENT_ARCING_SMASH, 19000, PHASE_ONE);
					events.ScheduleEvent(EVENT_IMPLODING_ENERY, 10000, PHASE_ONE);
					uint8 text = urand(1, 3);
					if (text == 1)
					{
						Talk(MALKOROK_ARCING_SMASH_1);
					}
					else if (text == 2)
					{
						Talk(MALKOROK_ARCING_SMASH_2);
					}
					else if (text == 3)
					{
						Talk(MALKOROK_ARCING_SMASH_3);
					}
					break;
				}
				case EVENT_SEISMIC_SLAM:
				{
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
					me->CastSpell(target, SPELL_SEISMIC_SLAM, false);
					events.ScheduleEvent(EVENT_SEISMIC_SLAM, 19500);
					break;
				}
				case EVENT_BREATH_OF_YSHARRJ:
				{
					me->CastSpell(me, SPELL_BREATH_OF_YSHAARJ, false);
					events.ScheduleEvent(EVENT_BREATH_OF_YSHARRJ, 70000, PHASE_ONE);
					events.ScheduleEvent(EVENT_SEISMIC_SLAM, 7500, PHASE_ONE);
					events.ScheduleEvent(EVENT_ARCING_SMASH, 14000, PHASE_ONE);
					uint8 textbreath = urand(1, 2);
					if (textbreath == 1)
					{
						Talk(MALKOROK_BREATH_OF_YSHAARJ_1);
					}
					else if (textbreath == 2)
					{
						Talk(MALKOROK_BREATH_OF_YSHAARJ_1);
					}
					break;
				}
				case EVENT_EXPEL_MIASMA:
				{
					me->CastSpell(me, SPELL_EXPEL_MIASMA, false);
					events.ScheduleEvent(EVENT_SEISMIC_SLAM, 7500, PHASE_ONE);
					events.ScheduleEvent(EVENT_ARCING_SMASH, 14000, PHASE_ONE);
					events.ScheduleEvent(EVENT_BREATH_OF_YSHARRJ, 70000, PHASE_ONE);
					break;
				}
				case EVENT_ERADICATE:
				{
					me->CastSpell(me, SPELL_ERADICATE, false);
					break;
				}
				case EVENT_ARCING_SMASH_TARGET_SPAWN:
				{
					me->GetMotionMaster()->MoveJump(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), 40.0f, 40.0f);
					Unit* target = SelectTarget(SELECT_TARGET_RANDOM);
					me->SummonCreature(CREATURE_ARCING_SMASH, target->GetPositionX(), target->GetPositionY(), me->GetPositionZ(), 10.0f, TEMPSUMMON_TIMED_DESPAWN, 5000);
					break;
				}
				case EVENT_BLOOD_RAGE:
				{
				events.SetPhase(PHASE_TWO);
				me->SetPower(POWER_RAGE, 100, false);
				me->CastSpell(me, SPELL_BLOOD_RAGE);
				events.ScheduleEvent(EVENT_PHASE1, 22500);
				events.ScheduleEvent(EVENT_DISPLACED_ENERGY, 3500, PHASE_TWO);
				}
				case EVENT_IMPLODING_ENERY:
				{
				me->CastSpell(me, SPELL_IMPLODING_ENERGY);
				}
				case EVENT_PHASE1:
				{
				events.SetPhase(PHASE_ONE);
				}
				case EVENT_DISPLACED_ENERGY:
				{
				me->CastSpell(me, SPELL_DISPLACED_ENERGY);
				events.ScheduleEvent(EVENT_DISPLACED_ENERGY, 11000, PHASE_TWO);
				}
				default:
					break;
				}
			}
			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_malkorok()
{
	new boss_malkorok();
}

/*
INSERT INTO creature_text VALUES
(71454, 0, 0, "Nazgrim has failed us. Kor'kron, destroy these intruders!", 14, 0, 100, 0, 0, 'MALKOROK_INTRO'),
(71454, 1, 0, "I will never fail the Warchief!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_AGGRO'),
(71454, 2, 0, "Weaklings!", 14, 0, 100, soundId, 'MALKOROK_ARCING_SMASH_1'),
(71454, 2, 1, "You dare challenge the Warchief?", 14, 0, 100, 0, 0, soundId, 'MALKOROK_ARCING_SMASH_2'),
(71454, 2, 2, "Garrosh gives me strength!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_ARCING_SMASH_3'),
(71454, 3, 0, "Witness the might of the True Horde!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_BREATH_OF_YSHAARJ_1'),
(71454, 3, 1, "The power of the Warchief will overwhelm you!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_BREATH_OF_YSHAARJ_2'),
(71454, 4, 0, "The True Horde cannot be STOPPED!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_BLOOD_RAGE_1'),
(71454, 4, 1, "Stand and FACE ME!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_BLOOD_RAGE_2'),
(71454, 5, 0, "The overwhelming power!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_BERSERK'),
(71454, 6, 0, "The Warchief demands it!", 14, 0, 100, 0, 0, soundId, 'MALKOROK_WIPE'),
(71454, 7, 0, "To die... for the warchief... is... an... honor...", 14, 0, 100, 0, 0, soundId, 'MALKOROK_DEATH');
*/
