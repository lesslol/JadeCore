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
	BOSS_DARK_SHAMAN_KORANTHAL,
};

enum eSpells
{
	SPELL_TWISTED_ELEMENTS = 119300, // 1
	SPELL_SHADOW_STORM = 119971, // 2
};

enum eEvents
{
	EVENT_TWISTED_ELEMENTS = 1,
	EVENT_SHADOW_STORM = 2,
};

enum eTexts
{
	TALK_AGGRO,
	TALK_DEATH,
	TALK_ARCING_SMASH,
	TALK_KILL,
	TALK_INFERNO_CHARGE,
};

class boss_dark_shaman_koranthal : public CreatureScript
{
public:
	boss_dark_shaman_koranthal() : CreatureScript("boss_dark_shaman_koranthal") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_dark_shaman_koranthal_AI(creature);
	}

	struct boss_dark_shaman_koranthal_AI : public BossAI
	{
		boss_dark_shaman_koranthal_AI(Creature* creature) : BossAI(creature, BOSS_DARK_SHAMAN_KORANTHAL)
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

		void JustDied(Unit* /*killer*/)
		{
			_JustDied();
			Talk(TALK_DEATH);
		}

		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(EVENT_TWISTED_ELEMENTS, 2500);
			events.ScheduleEvent(EVENT_SHADOW_STORM, 20500);
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

				case EVENT_TWISTED_ELEMENTS:
				{
					me->CastSpell(me, SPELL_TWISTED_ELEMENTS, true);
					events.ScheduleEvent(EVENT_TWISTED_ELEMENTS, 7500);
					break;
				}
				case EVENT_SHADOW_STORM:
				{
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
						DoCast(target, SPELL_SHADOW_STORM);
					events.ScheduleEvent(EVENT_SHADOW_STORM, 20000);
					Talk(TALK_INFERNO_CHARGE);
					break;
				}
			  }
			}
			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_dark_shaman_koranthal()
{
	new boss_dark_shaman_koranthal();
}