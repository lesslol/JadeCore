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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"

enum eSpells
{
	SPELL_ANCIENT_MIASMA     = 142861,
	SPELL_ARCING_SMASH       = 142815,
	SPELL_SEISMIC_SLAM       = 142849,
	SPELL_DISPLACED_ENERGY   = 142913,
	SPELL_EXPEL_MIASMA       = 143199,
	SPELL_BREATH_OF_YSHAARJ  = 142842,
	SPELL_ERADICATE          = 143916,
	SPELL_BLOOD_RAGE         = 142879,
	SPELL_IMPLODING_ENERGY   = 142986,
	SPELL_FATAL_STRIKE       = 142990,
	SPELL_RELENTLESS_ASSAULT = 143261,
	SPELL_BREATH_DAMAGE      = 142816,
	SPELL_DISPLACED_ENERGY_D = 142928,
	SPELL_BLOOD_RAGE_DAMAGE  = 142890,
	SPELL_ANCIENT_BARRIER_L  = 142864,
	SPELL_ANCIENT_BARRIER_M  = 142865,
	SPELL_ANCIENT_BARRIER_H  = 142866,
	SPELL_ANCIENT_MIASMA_VIS = 143018,
	SPELL_ANCIENT_MIASMA_DMG = 142906,
};

enum eEvents
{
	EVENT_ARCING_SMASH_FIRST   = 1,
	EVENT_ARCING_SMASH_SECOND  = 2,
	EVENT_ARCING_SMASH_THIRD   = 3,
	EVENT_ARCING_SMASH_ROOT	   = 4,
	EVENT_DESPAWN_ARCING_SMASH = 5,
	EVENT_SEISMIC_SLAM         = 6,
	EVENT_DISPLACED_ENERGY     = 7,
	EVENT_ERADICATE            = 8,
	EVENT_BREATH_OF_YSHARRJ    = 9,
	EVENT_EXPEL_MIASMA         = 10,
	EVENT_AGRESSIVE            = 11,
	EVENT_BLOOD_RAGE           = 12,
	EVENT_PHASE_ONE            = 13,
	EVENT_IMPLODING_ENERGY     = 14,
	EVENT_PHASE_TWO            = 15,
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
	MALKOROK_INTRO             = 1,
	MALKOROK_AGGRO             = 2,
	MALKOROK_ARCING_SMASH      = 3, // 0, 1 or 2 in database
	MALKOROK_BREATH_OF_YSHAARJ = 6, // 0 or 1 in database
	MALKOROK_BLOOD_RAGE        = 7,
	MALKOROK_BERSERK           = 9,
	MALKOROK_WIPE              = 10,
	MALKOROK_DEATH             = 11,
};

// 71454 - Malkorok
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
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->SummonCreature(CREATURE_ANCIENT_MIASMA, homeX, homeY, homeZ, 5.0f, TEMPSUMMON_MANUAL_DESPAWN);

						events.SetPhase(PHASE_ONE);
						events.ScheduleEvent(EVENT_SEISMIC_SLAM, urand(13000, 17000), 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_ARCING_SMASH_FIRST, 15000, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_IMPLODING_ENERGY, urand(13000, 17000), 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_PHASE_TWO, 120000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_ROOT:
					{
						me->SetControlled(false, UNIT_STATE_ROOT);
						me->DisableRotate(false);
						break;
					}

					case EVENT_ARCING_SMASH_FIRST:
					{
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
						{
							if (Creature* summArcingSmash = me->SummonCreature(CREATURE_ARCING_SMASH, *target, TEMPSUMMON_MANUAL_DESPAWN))
							{
								me->SetOrientation(me->GetAngle(summArcingSmash));
								me->SetControlled(true, UNIT_STATE_ROOT);
								me->DisableRotate(true);
								me->SetFacingTo(me->GetAngle(summArcingSmash));
								me->SendMovementFlagUpdate();
								Talk(MALKOROK_ARCING_SMASH);
								DoCast(summArcingSmash, SPELL_ARCING_SMASH);
							}
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_ROOT, 0, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_ARCING_SMASH_SECOND, 15000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_SECOND:
					{
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
						{
							if (Creature* summArcingSmash = me->SummonCreature(CREATURE_ARCING_SMASH, *target, TEMPSUMMON_MANUAL_DESPAWN))
							{
								me->SetOrientation(me->GetAngle(summArcingSmash));
								me->SetControlled(true, UNIT_STATE_ROOT);
								me->DisableRotate(true);
								me->SetFacingTo(me->GetAngle(summArcingSmash));
								me->SendMovementFlagUpdate();
								Talk(MALKOROK_ARCING_SMASH);
								DoCast(summArcingSmash, SPELL_ARCING_SMASH);
							}
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_ROOT, 0, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_ARCING_SMASH_THIRD, 15000, 0, PHASE_ONE);
						break;
					}

					case EVENT_ARCING_SMASH_THIRD:
					{
						float homeX = me->GetHomePosition().GetPositionX();
						float homeY = me->GetHomePosition().GetPositionY();
						float homeZ = me->GetHomePosition().GetPositionZ();
						me->GetMotionMaster()->MoveJump(homeX, homeY, homeZ, 40.0f, 40.0f);

						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
						{
							if (Creature* summArcingSmash = me->SummonCreature(CREATURE_ARCING_SMASH, *target, TEMPSUMMON_MANUAL_DESPAWN))
							{
								me->SetOrientation(me->GetAngle(summArcingSmash));
								me->SetControlled(true, UNIT_STATE_ROOT);
								me->DisableRotate(true);
								me->SetFacingTo(me->GetAngle(summArcingSmash));
								me->SendMovementFlagUpdate();
								Talk(MALKOROK_ARCING_SMASH);
								DoCast(summArcingSmash, SPELL_ARCING_SMASH);
							}
						}

						events.ScheduleEvent(EVENT_ARCING_SMASH_ROOT, 0, 0, PHASE_ONE);
						events.ScheduleEvent(EVENT_BREATH_OF_YSHARRJ, 10000, 0, PHASE_ONE);
						break;
					}

					case EVENT_BREATH_OF_YSHARRJ:
					{
						DoCast(SPELL_BREATH_OF_YSHAARJ);

						events.ScheduleEvent(EVENT_ARCING_SMASH_FIRST, 15000, 0, PHASE_ONE);
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

						events.ScheduleEvent(EVENT_SEISMIC_SLAM, urand(13000, 17000), 0, PHASE_ONE);
						break;
					}

					case EVENT_PHASE_TWO:
					{
						events.Reset();
						events.SetPhase(PHASE_TWO);
						me->DespawnCreaturesInArea(CREATURE_ANCIENT_MIASMA);
						std::list<Player*> pl_list;
						me->GetPlayerListInGrid(pl_list, 100.0f);
						for (auto itr : pl_list)
						{
							if (itr->HasAura(SPELL_ANCIENT_MIASMA_DMG))
								itr->RemoveAura(SPELL_ANCIENT_MIASMA_DMG);

							if (itr->HasAura(SPELL_ANCIENT_MIASMA))
								itr->RemoveAura(SPELL_ANCIENT_MIASMA);
						}

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

// 71513 - Ancient Miasma
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
			EventMap events;

			void Reset() override
			{
				me->SetInCombatWithZone();
				DoCast(SPELL_ANCIENT_MIASMA_VIS);
				std::list<Player*> pl_list;
				me->GetPlayerListInGrid(pl_list, 100.0f);
				for (auto itr : pl_list)
				{
					if (!itr->HasAura(SPELL_ANCIENT_MIASMA_DMG))
						me->AddAura(SPELL_ANCIENT_MIASMA_DMG, itr);

					if (!itr->HasAura(SPELL_ANCIENT_MIASMA))
						me->AddAura(SPELL_ANCIENT_MIASMA, itr);
				}

				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
				me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_ancient_miasmaAI(pCreature);
		}
};


// 142913 - Displaced Energy
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

// 142890 - Blood Rage
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

// 142861 - Ancient Miasma
class spell_ancient_barrier : public SpellScriptLoader
{
	public:
		spell_ancient_barrier() : SpellScriptLoader("spell_ancient_barrier") { }

		class spell_ancient_barrier_AuraScript : public AuraScript
		{
			PrepareAuraScript(spell_ancient_barrier_AuraScript);

			void OnUpdate(uint32 diff)
			{
				if (Unit* caster = GetCaster())
					if (Unit* player = GetTarget())
					{
						int32 absorb = player->GetHealingTakenInPastSecs(1);
						int32 health = player->GetMaxHealth();

						if (!(player->HasAura(SPELL_ANCIENT_BARRIER_L)) && !(player->HasAura(SPELL_ANCIENT_BARRIER_M)) && !(player->HasAura(SPELL_ANCIENT_BARRIER_H)))
							caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_L, &absorb, NULL, NULL, true);

						int32 remainingAbsorb;
						int32 newAbsorb;
						uint32 casterGuid = caster->GetGUID();

						if (player->HasAura(SPELL_ANCIENT_BARRIER_L))
						{
							remainingAbsorb = player->GetRemainingPeriodicAmount(casterGuid, SPELL_ANCIENT_BARRIER_L, SPELL_AURA_SCHOOL_ABSORB);
							newAbsorb = remainingAbsorb+absorb;
						}

						if (player->HasAura(SPELL_ANCIENT_BARRIER_M))
						{
							remainingAbsorb = player->GetRemainingPeriodicAmount(casterGuid, SPELL_ANCIENT_BARRIER_M, SPELL_AURA_SCHOOL_ABSORB);
							newAbsorb = remainingAbsorb + absorb;
						}

						if (player->HasAura(SPELL_ANCIENT_BARRIER_H))
						{
							remainingAbsorb = player->GetRemainingPeriodicAmount(casterGuid, SPELL_ANCIENT_BARRIER_H, SPELL_AURA_SCHOOL_ABSORB);
							newAbsorb = remainingAbsorb + absorb;
						}

						// If the remaining absorb + the new absorb is between 15% and 85% health cast visual for medium strenght shield
						if (newAbsorb >= health * 15 / 100 && newAbsorb < health * 85 / 100)
						{
							if (player->HasAura(SPELL_ANCIENT_BARRIER_L))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_L); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_M, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_M))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_M); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_M, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_H))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_H); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_M, &newAbsorb, NULL, NULL, true);
							}
						}

						// If the remaining absorb + the new absorb is lower than 15% health cast visual for low strenght shield
						if (newAbsorb < health * 15 / 100 && newAbsorb >= 0)
						{
							if (player->HasAura(SPELL_ANCIENT_BARRIER_L))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_L); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_L, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_M))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_M); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_L, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_H))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_H); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_L, &newAbsorb, NULL, NULL, true);
							}
						}

						// If the remaining absorb + the new absorb is lower or equal to max health and bigger than 85% health cast visual for high strenght shield
						if (newAbsorb >= health * 85 / 100 && newAbsorb <= health)
						{
							if (player->HasAura(SPELL_ANCIENT_BARRIER_L))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_L); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_M))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_M); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_H))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_H); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}
						}
						// If the remaining absorb + the new absorb is bigger than max health set it to be equal to the max health
						if (newAbsorb > health)
						{
							newAbsorb = health;
							
							if (player->HasAura(SPELL_ANCIENT_BARRIER_L))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_L); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_M))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_M); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}

							if (player->HasAura(SPELL_ANCIENT_BARRIER_H))
							{
								player->RemoveAura(SPELL_ANCIENT_BARRIER_H); // prevents buggs
								caster->CastCustomSpell(player, SPELL_ANCIENT_BARRIER_H, &newAbsorb, NULL, NULL, true);
							}
						}
					}
			}

			void Register()
			{
				OnAuraUpdate += AuraUpdateFn(spell_ancient_barrier_AuraScript::OnUpdate);
			}
		};

		AuraScript* GetAuraScript() const
		{
			return new spell_ancient_barrier_AuraScript();
		}
};

// 142842 - Breath of Y'shaarj
class spell_breath_of_yshaarj : public SpellScriptLoader
{
	public:
		spell_breath_of_yshaarj() : SpellScriptLoader("spell_breath_of_yshaarj") { }

		class spell_breath_of_yshaarj_SpellScript : public SpellScript
		{
			PrepareSpellScript(spell_breath_of_yshaarj_SpellScript);

			void HandleAfterCast()
			{
				if (InstanceScript* m_Instance = GetCaster()->GetInstanceScript())
					if (Creature * malkorok = m_Instance->instance->GetCreature(m_Instance->GetData64(eData::DATA_MALKOROK)))
					{
						std::list<Creature*> npc_list;
						malkorok->GetCreatureListWithEntryInGrid(npc_list, CREATURE_ARCING_SMASH, 100.0f);
						for (auto itr : npc_list)
						{
							malkorok->CastSpell(itr, SPELL_BREATH_DAMAGE);
							itr->DespawnOrUnsummon(0);
						}
					}
			}

			void Register()
			{
				AfterCast += SpellCastFn(spell_breath_of_yshaarj_SpellScript::HandleAfterCast);
			}
		};

		SpellScript* GetSpellScript() const
		{
			return new spell_breath_of_yshaarj_SpellScript();
		}
};

void AddSC_boss_malkorok()
{
	new boss_malkorok();

	new mob_ancient_miasma();

	new spell_displaced_energy();
	new spell_blood_rage();
	new spell_ancient_barrier();
	new spell_breath_of_yshaarj();
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