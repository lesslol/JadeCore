#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"

enum eSpells
{
	SPELL_ANCIENT_MIASMA	 = 142861,
	SPELL_ARCING_SMASH		 = 142815,
	SPELL_SEISMIC_SLAM		 = 142849,
	SPELL_DISPLACED_ENERGY	 = 142913,
	SPELL_EXPEL_MIASMA		 = 143199,
	SPELL_BREATH_OF_YSHAARJ  = 142842,
	SPELL_ERADICATE			 = 143916,
	SPELL_BLOOD_RAGE		 = 142879,
    SPELL_IMPLODING_ENERGY	 = 142986,
	SPELL_FATAL_STRIKE		 = 142990,
	SPELL_RELENTLESS_ASSAULT = 143261,
	SPELL_BREATH_DAMAGE		 = 142816,
	SPELL_DISPLACED_ENERGY_D = 142928,
	SPELL_BLOOD_RAGE_DAMAGE  = 142890,
	SPELL_ANCIENT_BARRIER	 = 142864,
	SPELL_ANCIENT_MIASMA_VIS = 143018,
	SPELL_ANCIENT_MIASMA_DMG = 142906,
};

enum eEvents
{
	EVENT_ARCING_SMASH_FIRST		= 1,
	EVENT_ARCING_SMASH_SECOND		= 2,
	EVENT_ARCING_SMASH_THIRD		= 3,
	EVENT_ARCING_SMASH_DAMAGE		= 4,
	EVENT_DESPAWN_ARCING_SMASH		= 5,
	EVENT_SEISMIC_SLAM				= 6,
	EVENT_DISPLACED_ENERGY			= 7,
	EVENT_ERADICATE					= 8,
	EVENT_BREATH_OF_YSHARRJ			= 9,
	EVENT_EXPEL_MIASMA				= 10,
	EVENT_AGRESSIVE					= 11,
	EVENT_BLOOD_RAGE				= 12,
	EVENT_PHASE_ONE					= 13,
	EVENT_IMPLODING_ENERGY			= 14,
	EVENT_PHASE_TWO					= 15,
};

enum Phases
{
	PHASE_ONE = 1,
	PHASE_TWO = 2,
};

enum eCreatures
{
	CREATURE_ARCING_SMASH   = 71455,
	CREATURE_ANCIENT_MIASMA = 71513,
};

enum eTexts
{
	MALKOROK_INTRO					= 1,
	MALKOROK_AGGRO					= 2,
	MALKOROK_ARCING_SMASH			= 3, // 0, 1 or 2 in database
	MALKOROK_BREATH_OF_YSHAARJ		= 6, // 0 or 1 in database
	MALKOROK_BLOOD_RAGE_1			= 7,
	MALKOROK_BLOOD_RAGE_2			= 8,
	MALKOROK_BERSERK				= 9,
	MALKOROK_WIPE					= 10,
	MALKOROK_DEATH					= 11,
};

class boss_malkorok : public CreatureScript
{
	public:
		boss_malkorok() : CreatureScript("boss_malkorok") { }

		struct boss_malkorokAI : public BossAI
		{
			boss_malkorokAI(Creature* creature) : BossAI(creature, DATA_MALKOROK)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			uint8 arcingSmashController;

			void Reset()
			{
				_Reset();
				arcingSmashController = 0;

				me->SetReactState(REACT_AGGRESSIVE);
				me->setFaction(16);
				me->setPowerType(POWER_RAGE);
				me->SetMaxPower(POWER_RAGE, 100);

				events.Reset();
				events.SetPhase(PHASE_ONE);
			}

			void JustDied(Unit* /*killer*/)
			{
				Talk(MALKOROK_DEATH);
			}

			void KilledUnit(Unit* u)
			{
			}


			void EnterCombat(Unit* unit)
			{
				Talk(MALKOROK_AGGRO);
			
				float homeX = me->GetHomePosition().GetPositionX();
				float homeY = me->GetHomePosition().GetPositionY();
				float homeZ = me->GetHomePosition().GetPositionZ();
				me->SummonCreature(CREATURE_ANCIENT_MIASMA, homeX, homeY, homeZ, 5.0f, TEMPSUMMON_MANUAL_DESPAWN);

				events.SetPhase(PHASE_ONE);
				events.ScheduleEvent(EVENT_SEISMIC_SLAM, urand(13000, 17000), 0, PHASE_ONE);
				events.ScheduleEvent(EVENT_ARCING_SMASH_FIRST, 15000, 0, PHASE_ONE);
				events.ScheduleEvent(EVENT_IMPLODING_ENERGY, urand(13000, 17000), 0, PHASE_ONE);
				events.ScheduleEvent(EVENT_PHASE_TWO, 120000, 0, PHASE_ONE);
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				events.Update(diff);


				switch (events.ExecuteEvent())
				{
					case EVENT_PHASE_ONE:
					{
						DoCast(me, SPELL_RELENTLESS_ASSAULT);

						events.SetPhase(PHASE_ONE);
						events.ScheduleEvent(EVENT_SEISMIC_SLAM, urand(13000, 17000), 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_ARCING_SMASH_FIRST, 15000, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_IMPLODING_ENERGY, urand(13000, 17000), 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_PHASE_TWO, 120000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_DAMAGE:
					{
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
						me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
						if (Unit* target = me->FindNearestCreature(CREATURE_ARCING_SMASH, 50.00f, true))
						{
							DoCast(target, SPELL_ARCING_SMASH);
						}

						if (arcingSmashController == 1)
						{
							events.ScheduleEvent(EVENT_ARCING_SMASH_SECOND, 15000, 0, PHASE_ONE);
						}
					
						if (arcingSmashController == 2)
						{
							events.ScheduleEvent(EVENT_ARCING_SMASH_THIRD, 15000, 0, PHASE_ONE);
						}

						if (arcingSmashController == 3)
						{
							events.ScheduleEvent(EVENT_ARCING_SMASH_FIRST, 25000, 0, PHASE_ONE);
						}

						break;
					}

					case EVENT_ARCING_SMASH_FIRST:
					{
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
						me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
						Talk(MALKOROK_ARCING_SMASH);
						arcingSmashController = 1;
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
						{
							float posX = target->GetPositionX();
							float posY = target->GetPositionY();
							float posZ = target->GetPositionZ();
							float posO = target->GetOrientation();

							me->SummonCreature(CREATURE_ARCING_SMASH, posX, posY, posZ, posO, TEMPSUMMON_TIMED_DESPAWN, 5000);
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_DAMAGE, 1000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_SECOND:
					{
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
						me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
						arcingSmashController = 2;
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
						{
							float posX = target->GetPositionX();
							float posY = target->GetPositionY();
							float posZ = target->GetPositionZ();
							float posO = target->GetOrientation();

							me->SummonCreature(CREATURE_ARCING_SMASH, posX, posY, posZ, posO, TEMPSUMMON_TIMED_DESPAWN, 5000);
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_DAMAGE, 1000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_THIRD:
					{
						me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
						me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
						arcingSmashController = 3;
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
						{
							float posX = target->GetPositionX();
							float posY = target->GetPositionY();
							float posZ = target->GetPositionZ();
							float posO = target->GetOrientation();

							me->SummonCreature(CREATURE_ARCING_SMASH, posX, posY, posZ, posO, TEMPSUMMON_MANUAL_DESPAWN);
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_DAMAGE, 1000, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_BREATH_OF_YSHARRJ, 10000, 0, PHASE_ONE);
						break;
					}

					case EVENT_BREATH_OF_YSHARRJ:
					{
						DoCast(SPELL_BREATH_OF_YSHAARJ);

						events.ScheduleEvent(EVENT_DESPAWN_ARCING_SMASH, 2500, 0, PHASE_ONE);
						break;
					}

					case EVENT_DESPAWN_ARCING_SMASH:
					{
						std::list<Creature*> creatures;
						me->GetCreatureListWithEntryInGrid(creatures, CREATURE_ARCING_SMASH, 500.0f);

						for (auto itr : creatures)
						{
							DoCast(itr, SPELL_BREATH_DAMAGE);
							itr->DespawnOrUnsummon();
						}
					
						break;
					}

					case EVENT_SEISMIC_SLAM:
					{
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
						{
							std::list<Player*> pl_list;
							target->GetPlayerListInGrid(pl_list, 5.0f);
							for (auto itr : pl_list)
							{
								DoCast(itr, SPELL_SEISMIC_SLAM);
							}

							DoCast(target, SPELL_SEISMIC_SLAM);
						}

						events.ScheduleEvent(EVENT_SEISMIC_SLAM, 19500, PHASE_ONE);
						break;
					}

					case EVENT_PHASE_TWO:
					{
						events.Reset();
						events.SetPhase(PHASE_TWO);

						DoCast(SPELL_BLOOD_RAGE);
						events.ScheduleEvent(EVENT_BLOOD_RAGE, 1000, 0, PHASE_TWO);
						events.ScheduleEvent(EVENT_DISPLACED_ENERGY, 5000, 0, PHASE_TWO);
						events.ScheduleEvent(EVENT_PHASE_ONE, 20000, 0, PHASE_TWO);
						break;
					}

					case EVENT_BLOOD_RAGE:
					{
						DoCast(SPELL_BLOOD_RAGE_DAMAGE);

						events.ScheduleEvent(EVENT_BLOOD_RAGE, 1000, 0, PHASE_TWO);
						break;
					}

					case EVENT_DISPLACED_ENERGY:
					{
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
						{
							DoCast(target, SPELL_DISPLACED_ENERGY);
						}

						events.ScheduleEvent(EVENT_DISPLACED_ENERGY, 5000, 0, PHASE_TWO);
						break;
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new boss_malkorokAI(pCreature);
		}
};

class mob_ancient_miasma : public CreatureScript
{
	public:
		mob_ancient_miasma() : CreatureScript("mob_ancient_miasma") { }

		struct mob_ancient_miasmaAI : public ScriptedAI
		{
			mob_ancient_miasmaAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				me->SetInCombatWithZone();
				DoCast(SPELL_ANCIENT_MIASMA_VIS);
				DoCast(SPELL_ANCIENT_MIASMA_DMG);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
				me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_ancient_miasmaAI(pCreature);
		}
};

class spell_displaced_energy : public SpellScriptLoader
{
	public:
		spell_displaced_energy() : SpellScriptLoader("spell_displaced_energy") { }

		class spell_displaced_energy_AuraScript : public AuraScript
		{
			PrepareAuraScript(spell_displaced_energy_AuraScript);

			void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
			{
				if (Unit* caster = GetCaster())
					caster->CastSpell(caster, SPELL_DISPLACED_ENERGY_D);
			}

			void Register()
			{
				OnEffectRemove += AuraEffectRemoveFn(spell_displaced_energy_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
			}
		};

		AuraScript* GetAuraScript() const
		{
			return new spell_displaced_energy_AuraScript();
		}
};

class spell_blood_rage : public SpellScriptLoader
{
	public:
		spell_blood_rage() : SpellScriptLoader("spell_blood_rage") { }

		class spell_blood_rage_SpellScript : public SpellScript
		{
			PrepareSpellScript(spell_blood_rage_SpellScript);

			bool Load()
			{
				players = 1;
				return true;
			}

			void CountTargets(std::list<WorldObject*>& targets)
			{
				players = targets.size();
			}

			void SplitDamage(SpellEffIndex /*eff*/)
			{
				SetHitDamage(int32(GetHitDamage() / players));
			}

			void Register()
			{
				OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_blood_rage_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
				OnEffectHitTarget += SpellEffectFn(spell_blood_rage_SpellScript::SplitDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
			}

			private:
				uint8 players;
		};

		SpellScript* GetSpellScript() const
		{
			return new spell_blood_rage_SpellScript();
		}
};

class spell_ancient_barrier : public SpellScriptLoader
{
	public:
		spell_ancient_barrier() : SpellScriptLoader("spell_ancient_barrier") { }

		class spell_ancient_barrier_AuraScript : public AuraScript
		{
			PrepareAuraScript(spell_ancient_barrier_AuraScript);

			void HandleDummy(AuraEffectPtr /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
			{
				if (Unit* caster = GetCaster())
					if (Unit* player = GetTarget())
					{
						int32 absorb = player->GetHealingTakenInPastSecs(1);
						absorb = absorb + absorb;
						caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER, &absorb, NULL, NULL, true);
					}
			}

			void Register()
			{
				OnEffectAbsorb += AuraEffectAbsorbFn(spell_ancient_barrier_AuraScript::HandleDummy, EFFECT_0);
			}
		};

		AuraScript* GetAuraScript() const
		{
			return new spell_ancient_barrier_AuraScript();
		}
};

void AddSC_boss_malkorok()
{
	new boss_malkorok();

	new spell_displaced_energy();
	new spell_blood_rage();
	new spell_ancient_barrier();
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