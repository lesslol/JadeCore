/*
Intro isn't scripted
*/
/*
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
*/
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
	BOSS_ADAROGG,
};

enum eSpells
{
	SPELL_FLAME_BREATH = 119420, // 1
	SPELL_INFERNO_CHARGE = 119405, // 2
};

enum eEvents
{
	EVENT_FLAME_BREATH = 1,
	EVENT_INFERNO_CHARGE = 2,
};

enum eTexts
{
	TALK_AGGRO,
	TALK_DEATH,
	TALK_ARCING_SMASH,
	TALK_KILL,
	TALK_INFERNO_CHARGE,
};

class boss_adarogg : public CreatureScript
{
public:
	boss_adarogg() : CreatureScript("boss_adarogg") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_adarogg_AI(creature);
	}

	struct boss_adarogg_AI : public BossAI
	{
		boss_adarogg_AI(Creature* creature) : BossAI(creature, BOSS_ADAROGG)
		{}
		void Reset()
		{
			me->SetReactState(REACT_AGGRESSIVE);
			events.Reset();
			_Reset();
		}

		void KilledUnit(Unit* u)
		{
			Talk(TALK_KILL);
		}


		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(EVENT_FLAME_BREATH, 5500);
			events.ScheduleEvent(EVENT_INFERNO_CHARGE, 20500);
			Talk(TALK_AGGRO);
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

				case EVENT_FLAME_BREATH:
				{
					me->CastSpell(me, SPELL_FLAME_BREATH, true);
					events.ScheduleEvent(EVENT_FLAME_BREATH, 7500);
					break;
				}
				case EVENT_INFERNO_CHARGE:
				{
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
					DoCast(target, SPELL_INFERNO_CHARGE);
					events.ScheduleEvent(EVENT_INFERNO_CHARGE, 20000);
					Talk(TALK_INFERNO_CHARGE);
					break;
				}
			  }
			}
			DoMeleeAttackIfReady();
		}
	};
};

	void AddSC_boss_adarogg()
{
	new boss_adarogg();
}