#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"

enum eSpells
{
	// Secured Stockpile of Spoils
    SPELL_GB_11010_ARMAGEDDON_CLASS_DEFENSE_SYSTEME = 145864,
    SPELL_UNSTABLE_DEFENSE_SYSTEME                  = 145685,

	// Animated Stone Mogu
	SPELL_HARDEN_FLESH                              = 144922,
	SPELL_EARTHEN_SHARD                             = 144923,

	// Burial Urn - Sparks of Life
	SPELL_PULSE                                     = 142765,
	SPELL_NOVA                                      = 142775,

	// Quillen Guardian
	SPELL_CARNIVOROUS_BITE                          = 144853,

	// Modified Anima Golem
	SPELL_MATTER_SCRAMBLE                           = 145393,
	SPELL_CRIMSON_RECONSTITUTION                    = 145271,

	// Mogu Shadow Ritualist
	SPELL_TORMENT                                   = 142934,
	SPELL_FORBIDDEN_MAGIC                           = 145240,
	SPELL_MOGU_RUNE_OF_POWER                        = 145460,

	// Jun Wei
	SPELL_SHADOW_VOLLEY                             = 148515,

	// Zu Yin
	SPELL_MOLTEN_FIST                               = 148518,

	// Xiang Lin
	SPELL_JADE_TEMPEST                              = 148582,

	// Kun Da
	SPELL_FRACTURE                                  = 148513,

	// Sri'tik Bombardrier
	SPELL_GUSTING_BOMB                              = 145718,
	SPELL_THROW_EXPLOSIVES                          = 145706,

	// Amber Encased Kunchong
	SPELL_ENCAPSULED_PHEROMONES                     = 145748,

	// Kor'thik Warcaller
	SPELL_ENRAGE                                    = 145692,

	// Zar'thik Amber Priest
	SPELL_MANTID_SWARM                              = 145808,
	SPELL_RESIDUE                                   = 145790,

	// Ser'thik Wind Wielder
	SPELL_WINDSTORM                                 = 145817,
	SPELL_RAGE_OF_THE_EMPRESS                       = 145812,

	// Commanders
	SPELL_SET_TO_BLOW                               = 145993,
	SPELL_PHEROMONE_CLOUD                           = 148760,

	// Ancient Brewmaster Spirit
	SPELL_KEG_TOSS                                  = 146217,
	SPELL_BREATH_OF_FIRE                            = 146222,
	SPELL_BLADE_OF_THE_HUNDRED_STEPS                = 146081,

	// Wise Mistweaver Spirit
	SPELL_GUSTING_CRANE_KICK                        = 146180,
	SPELL_EMINENCE                                  = 146189,
	SPELL_STAFF_OF_RESONATING_WATER                 = 146679,

	// Nameless Windwalker Spirit
	SPELL_PATH_OF_BLOSSOMS                          = 146257,
	SPELL_CLAW_OF_BURNING_ANGER                     = 146142,
};

enum eEvents
{
	EVENT_HARDEN_FLESH     = 1,
	EVENT_EARTHEN_SHARD    = 2,

	EVENT_PULSE            = 3,
	EVENT_NOVA             = 4,
	EVENT_SUMMON_SPARK     = 5,

	EVENT_CARNIVOROUS_BITE = 6,

	EVENT_MATTER_SCRAMBLE  = 7,
	EVENT_CRIMSON_RECONSTITUTION = 8,

	EVENT_TORMENT                = 9,
	EVENT_FORBIDDEN_MAGIC        = 10,
	EVENT_MOGU_RUNE_OF_POWER     = 11,

	EVENT_SHADOW_VOLLEY          = 12,

	EVENT_MOLTEN_FIST            = 13,

	EVENT_JADE_TEMPEST           = 14,

	EVENT_FRACTURE               = 15,

	EVENT_GUSTING_BOMB           = 16,
	EVENT_THROW_EXPLOSIVES       = 17,

	EVENT_ENCAPSULDER_PHEROMONES = 18,

	EVENT_ENRAGE                 = 19,

	EVENT_MANTID_SWARM           = 20,
	EVENT_RESIDUE                = 21,

	EVENT_WINDSTORM              = 22,
	EVENT_RAGE_OF_THE_EMPRESS    = 23,

	EVENT_SET_TO_BLOW            = 24,
	EVENT_PHEROMONE_CLOUD        = 25,

	EVENT_KEG_TOSS               = 26,
	EVENT_BREATH_OF_FIRE         = 27,
	EVENT_BLADE_OF_THE_HUNDRED_STEPS = 28,

	EVENT_GUSTING_CRANE_KICK     = 29,
	EVENT_EMINENCE               = 30,
	EVENT_STAFF_OF_RESONATING_WATER = 31,

	EVENT_PATH_OF_BLOSSOMS       = 32,
	EVENT_CLAW_OF_BURNING_ANGER  = 33,
};

enum eSays
{
};

enum eCreatures
{
	// Ligthweight Crates - Mogu
	CREATURE_ANIMATED_STONE_MOGU        = 71380,
	CREATURE_BURIAL_URN                 = 71382,
	CREATURE_SPARK_OF_LIFE              = 71433,
	CREATURE_QUILLEN_GUARDIAN           = 71378,

	// Stout Crates - Mogu
	CREATURE_MODIFIED_ANIMA_GOLEM       = 71395,
	CREATURE_MOGU_SHADOW_RITUALIST      = 71393,

	// Massive Crates - Mogu
	CREATURE_JUN_WEI                    = 73723,
	CREATURE_ZU_YIN                     = 73724,
	CREATURE_XIANG_LIN                  = 73725,
	CREATURE_KUN_DA                     = 71408,

	// Lightweight Crates - Mandit
	CREATURE_SRITHIK_BOMBARDIER         = 71385,
	CREATURE_AMBER_ENCASED_KUNCHONG     = 71388,
	CREATURE_KORTHIK_WARCALLER          = 71383,

	// Stout Crates - Mantid
	CREATURE_ZARTHIK_AMBER_PRIEST       = 71397,
	CREATURE_SERTHIK_WIND_WIELDER       = 71405,

	// Massive Crates - Mantid
	CREATURE_COMMANDER_TIK              = 73951,
	CREATURE_COMMANDER_IKTAL            = 73948,
	CREATURE_COMMANDER_NAKAZ            = 73949,
	CREATURE_COMMANDER_ZAKTAR           = 71409,

	// Pandaren Crates
	CREATURE_ANCIENT_BREWMASTER_SPIRIT  = 71427,
	CREATURE_WISE_MISTWEAVER_SPIRIT     = 71428,
	CREATURE_NAMELESS_WINDWALKER_SPIRIT = 71430,
};

enum eGameobjects
{

};

class boss_secured_stockpile_of_spoils : public CreatureScript
{
	public:
		boss_secured_stockpile_of_spoils() : CreatureScript("boss_secured_stockpile_of_spoils") { }

		struct boss_secured_stockpile_of_spoilsAI : public BossAI
		{
			boss_secured_stockpile_of_spoilsAI(Creature* creature) : BossAI(creature, DATA_SPOILS_OF_PANDARIA)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				_Reset();
			}

			void JustDied()
			{
				_JustDied();
			}

			void JustReachedHome()
			{
				_JustReachedHome();
			}

			void EnterCombat()
			{
				_EnterCombat();
			}

			void UpdateAI(const uint32 diff)
			{
				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new boss_secured_stockpile_of_spoilsAI(pCreature);
		}
};

/*********************/
//    Mogu Crates    //
/*********************/

// Lightweight Crates
class mob_animated_stone_mogu : public CreatureScript
{
	public:
		mob_animated_stone_mogu() : CreatureScript("mob_animated_stone_mogu") { }

		struct mob_animated_stone_moguAI : ScriptedAI
		{
			mob_animated_stone_moguAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_HARDEN_FLESH, urand(5000, 10000));
				events.ScheduleEvent(EVENT_EARTHEN_SHARD, urand(7000, 12000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_HARDEN_FLESH:
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 40.0f, true))
							{
								DoCast(target, SPELL_HARDEN_FLESH);
							}

							events.ScheduleEvent(EVENT_HARDEN_FLESH, urand(5000, 10000));
							break;
						}

						case EVENT_EARTHEN_SHARD:
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 40.0f, true))
							{
								DoCast(target, SPELL_EARTHEN_SHARD);
							}

							events.ScheduleEvent(EVENT_EARTHEN_SHARD, urand(7000, 12000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_animated_stone_moguAI(pCreature);
		}
};

class mob_burial_urn : public CreatureScript
{
	public:
		mob_burial_urn() : CreatureScript("mob_burial_urn") { }

		struct mob_burial_urnAI : public ScriptedAI
		{
			mob_burial_urnAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_SUMMON_SPARK, urand(10000, 15000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_SUMMON_SPARK:
						{
							float posX = me->GetPositionX();
							float posY = me->GetPositionY();
							float posZ = me->GetPositionZ();
							float posO = me->GetOrientation();

							me->SummonCreature(CREATURE_SPARK_OF_LIFE, posX, posY, posZ, posO, TEMPSUMMON_MANUAL_DESPAWN);
							events.ScheduleEvent(EVENT_SUMMON_SPARK, urand(10000, 15000));
							break;
						}
					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_burial_urnAI(pCreature);
		}
};

class mob_spark_of_life : public CreatureScript
{
	public:
		mob_spark_of_life() : CreatureScript("mob_spark_of_life") { }

		struct mob_spark_of_lifeAI : public ScriptedAI
		{
			mob_spark_of_lifeAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				DoCast(me, SPELL_PULSE);
			}

			void JustDied(Unit* /*killer*/)
			{
				DoCast(SPELL_NOVA);
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_spark_of_lifeAI(pCreature);
		}
};

class mob_quilen_gardians : public CreatureScript
{
	public:
		mob_quilen_gardians() : CreatureScript("mob_quilen_gardians") { }

		struct mob_quilen_gardiansAI : public ScriptedAI
		{
			mob_quilen_gardiansAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_CARNIVOROUS_BITE, urand(5000, 7000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_CARNIVOROUS_BITE:
						{
							DoCastVictim(SPELL_CARNIVOROUS_BITE);

							events.ScheduleEvent(EVENT_CARNIVOROUS_BITE, urand(5000, 7000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_quilen_gardiansAI(pCreature);
		}
};

class gob_lightweight_crate_mogu : public GameObjectScript
{
	public:
		gob_lightweight_crate_mogu() : GameObjectScript("gob_lightweight_crate_mogu") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMobs = urand(1, 3);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMobs)
			{
				case 1: // Animated Stone Mogu
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_ANIMATED_STONE_MOGU, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2: // Burial Urn
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_BURIAL_URN, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 3: // Quillen Guardians
				{
					Position pos[4] = 
					{
						{ posX, posY, posZ, posO },
						{ posX+2.0f, posY, posZ, posO },
						{ posX+1.0f, posY-1.0f, posZ, posO },
						{ posX, posY, posZ-2.0f, posO },
					};

					for (int i = 0; i < 4; i++)
						go->SummonCreature(CREATURE_QUILLEN_GUARDIAN, pos[i], TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

// Stout Crates
class mob_modified_anima_golem : public CreatureScript
{
	public:
		mob_modified_anima_golem() : CreatureScript("mob_modified_anima_golem") { }

		struct mob_modified_anima_golemAI : public ScriptedAI
		{
			mob_modified_anima_golemAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_MATTER_SCRAMBLE, 20000);
				events.ScheduleEvent(EVENT_CRIMSON_RECONSTITUTION, 15000);
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_MATTER_SCRAMBLE:
						{
							DoCast(me, SPELL_MATTER_SCRAMBLE);

							events.ScheduleEvent(EVENT_MATTER_SCRAMBLE, 20000);
							break;
						}

						case EVENT_CRIMSON_RECONSTITUTION:
						{
							DoCast(me, SPELL_CRIMSON_RECONSTITUTION);

							events.ScheduleEvent(EVENT_CRIMSON_RECONSTITUTION, 15000);
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_modified_anima_golemAI(pCreature);
		}
};

class mob_mogu_shadow_ritualist : public CreatureScript
{
	public:
		mob_mogu_shadow_ritualist() : CreatureScript("mob_mogu_shadow_ritualist") { }

		struct mob_mogu_shadow_ritualistAI : public ScriptedAI
		{
			mob_mogu_shadow_ritualistAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_TORMENT, urand(5000, 10000));
				events.ScheduleEvent(EVENT_MOGU_RUNE_OF_POWER, 15000);
				events.ScheduleEvent(EVENT_FORBIDDEN_MAGIC, 10000);
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_TORMENT:
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 40.0f, true))
							{
								DoCast(target, SPELL_TORMENT);
							}

							events.ScheduleEvent(EVENT_TORMENT, urand(5000, 10000));
							break;
						}

						case EVENT_MOGU_RUNE_OF_POWER:
						{
							DoCast(me, SPELL_MOGU_RUNE_OF_POWER);

							events.ScheduleEvent(EVENT_MOGU_RUNE_OF_POWER, 15000);
							break;
						}

						case EVENT_FORBIDDEN_MAGIC:
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 40.0f, true))
							{
								DoCast(target, SPELL_FORBIDDEN_MAGIC);
							}

							events.ScheduleEvent(EVENT_FORBIDDEN_MAGIC, 15000);
							break;
						}
					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_mogu_shadow_ritualistAI(pCreature);
		}
};

class gob_stout_crate_mogu : public GameObjectScript
{
	public:
		gob_stout_crate_mogu() : GameObjectScript("gob_stout_crate_mogu") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 2);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1: // Modified Anima Golem
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_MODIFIED_ANIMA_GOLEM, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2: // Mogu Shadow Ritualist
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_MOGU_SHADOW_RITUALIST, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

// Massive Crates
class mob_jun_wei : public CreatureScript
{
	public:
		mob_jun_wei() : CreatureScript("mob_jun_wei") { }

		struct mob_jun_weiAI : public ScriptedAI
		{
			mob_jun_weiAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_SHADOW_VOLLEY, urand(5000, 10000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_SHADOW_VOLLEY:
						{
							DoCast(SPELL_SHADOW_VOLLEY);

							events.ScheduleEvent(EVENT_SHADOW_VOLLEY, urand(5000, 10000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_jun_weiAI(pCreature);
		}
};

class mob_zu_yin : public CreatureScript
{
	public:
		mob_zu_yin() : CreatureScript("mob_zu_yin") { }

		struct mob_zu_yinAI : public ScriptedAI
		{
			mob_zu_yinAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_MOLTEN_FIST, urand(5000, 10000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_MOLTEN_FIST:
						{
							DoCast(SPELL_MOLTEN_FIST);

							events.ScheduleEvent(EVENT_MOLTEN_FIST, urand(5000, 10000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_zu_yinAI(pCreature);
		}
};

class mob_xiang_lin : public CreatureScript
{
	public:
		mob_xiang_lin() : CreatureScript("mob_xiang_lin") { }

		struct mob_xiang_linAI : public ScriptedAI
		{
			mob_xiang_linAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_JADE_TEMPEST, urand(5000, 10000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_JADE_TEMPEST:
						{
							DoCast(SPELL_JADE_TEMPEST);

							events.ScheduleEvent(EVENT_JADE_TEMPEST, urand(5000, 10000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_xiang_linAI(pCreature);
		}
};

class mob_kun_da : public CreatureScript
{
	public:
		mob_kun_da() : CreatureScript("mob_kun_da") { }

		struct mob_kun_daAI : public ScriptedAI
		{
			mob_kun_daAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{
				events.ScheduleEvent(EVENT_FRACTURE, urand(5000, 10000));
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_FRACTURE:
						{
							DoCast(SPELL_FRACTURE);

							events.ScheduleEvent(EVENT_FRACTURE, urand(5000, 10000));
							break;
						}
					}
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_kun_daAI(pCreature);
		}
};

class gob_massive_crate_mogu : public GameObjectScript
{
	public:
		gob_massive_crate_mogu() : GameObjectScript("gob_massive_crate_mogu") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 4);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_JUN_WEI, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_ZU_YIN, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 3:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_XIANG_LIN, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 4:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_KUN_DA, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

/***********************/
//    Mantid Crates    //
/***********************/
// Lightweight Crates
class mob_srithik_bombadiers : public CreatureScript
{
	public:
		mob_srithik_bombadiers() : CreatureScript("mob_srithik_bombadiers") { }

		struct mob_srithik_bombadiersAI : public ScriptedAI
		{
			mob_srithik_bombadiersAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_srithik_bombadiersAI(pCreature);
		}
};

class mob_amber_encased_kunchongs : public CreatureScript
{
	public:
		mob_amber_encased_kunchongs() : CreatureScript("mob_amber_encased_kunchongs") { }

		struct mob_amber_encased_kunchongsAI : public ScriptedAI
		{
			mob_amber_encased_kunchongsAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_amber_encased_kunchongsAI(pCreature);
		}
};

class mob_korthik_warcallers : public CreatureScript
{
	public:
		mob_korthik_warcallers() : CreatureScript("mob_korthik_warcallers") { }

		struct mob_korthik_warcallersAI : public ScriptedAI
		{
			mob_korthik_warcallersAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_korthik_warcallersAI(pCreature);
		}
};

class gob_lightweight_crate_mantid : public GameObjectScript
{
	public:
		gob_lightweight_crate_mantid() : GameObjectScript("gob_lightweight_crate_mantid") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 3);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_SRITHIK_BOMBARDIER, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_AMBER_ENCASED_KUNCHONG, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 3:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_KORTHIK_WARCALLER, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

// Stout Crates
class mob_zarthik_amber_priests : public CreatureScript
{
	public:
		mob_zarthik_amber_priests() : CreatureScript("mob_zarthik_amber_priests") { }

		struct mob_zarthik_amber_priestsAI : public ScriptedAI
		{
			mob_zarthik_amber_priestsAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_zarthik_amber_priestsAI(pCreature);
		}
};

class mob_setthik_wind_wielders : public CreatureScript
{
	public:
		mob_setthik_wind_wielders() : CreatureScript("mob_setthik_wind_wielders") { }

		struct mob_setthik_wind_wieldersAI : public ScriptedAI
		{
			mob_setthik_wind_wieldersAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_setthik_wind_wieldersAI(pCreature);
		}
};

class gob_stout_crate_mantid : public GameObjectScript
{
	public:
		gob_stout_crate_mantid() : GameObjectScript("gob_stout_crate_mantid") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 2);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_SERTHIK_WIND_WIELDER, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_ZARTHIK_AMBER_PRIEST, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

// Massive Crates
class mob_commander_tik : public CreatureScript
{
	public:
		mob_commander_tik() : CreatureScript("mob_commander_tik") { }

		struct mob_commander_tikAI : public ScriptedAI
		{
			mob_commander_tikAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_commander_tikAI(pCreature);
		}
};

class mob_commander_iktal : public CreatureScript
{
	public:
		mob_commander_iktal() : CreatureScript("mob_commander_iktal") { }

		struct mob_commander_iktalAI : public ScriptedAI
		{
			mob_commander_iktalAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_commander_iktalAI(pCreature);
		}
};

class mob_commander_nakaz : public CreatureScript
{
	public:
		mob_commander_nakaz() : CreatureScript("mob_commander_nakaz") { }

		struct mob_commander_nakazAI : public ScriptedAI
		{
			mob_commander_nakazAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_commander_nakazAI(pCreature);
		}
};

class mob_commander_zaktar : public CreatureScript
{
	public:
		mob_commander_zaktar() : CreatureScript("mob_commander_zaktar") { }

		struct mob_commander_zaktarAI : public ScriptedAI
		{
			mob_commander_zaktarAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_commander_zaktarAI(pCreature);
		}
};

class gob_massive_crate_mantid : public GameObjectScript
{
	public:
		gob_massive_crate_mantid() : GameObjectScript("gob_massive_crate_mantid") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 4);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_COMMANDER_TIK, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_COMMANDER_IKTAL, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 3:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_COMMANDER_NAKAZ, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 4:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_COMMANDER_ZAKTAR, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

/*************************/
//    Pandaren Crates    //
/*************************/
class mob_ancient_brewmaster_spirits : public CreatureScript
{
	public:
		mob_ancient_brewmaster_spirits() : CreatureScript("mob_ancient_brewmaster_spirits") { }

		struct mob_ancient_brewmaster_spiritsAI : public ScriptedAI
		{
			mob_ancient_brewmaster_spiritsAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_ancient_brewmaster_spiritsAI(pCreature);
		}
};

class mob_wise_mistweaver_spirits : public CreatureScript
{
	public:
		mob_wise_mistweaver_spirits() : CreatureScript("mob_wise_mistweaver_spirits") { }

		struct mob_wise_mistweaver_spiritsAI : public ScriptedAI
		{
			mob_wise_mistweaver_spiritsAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_wise_mistweaver_spiritsAI(pCreature);
		}
};

class mob_nameless_windwalker_spirits : public CreatureScript
{
	public:
		mob_nameless_windwalker_spirits() : CreatureScript("mob_nameless_windwalker_spirits") { }

		struct mob_nameless_windwalker_spiritsAI : public ScriptedAI
		{
			mob_nameless_windwalker_spiritsAI(Creature* creature) : ScriptedAI(creature)
			{
				pInstance = creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset() override
			{

			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{

					}
				}
			}
		};

		CreatureAI* GetAI(Creature* pCreature) const
		{
			return new mob_nameless_windwalker_spiritsAI(pCreature);
		}
};

class gob_pandaren_crate : public GameObjectScript
{
	public:
		gob_pandaren_crate() : GameObjectScript("gob_pandaren_crate") { }

		bool OnGossipHello(Player* /*player*/, GameObject* go)
		{
			uint32 randomMob = urand(1, 3);
			float posX = go->GetPositionX();
			float posY = go->GetPositionY();
			float posZ = go->GetPositionZ();
			float posO = go->GetOrientation();

			switch (randomMob)
			{
				case 1:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_ANCIENT_BREWMASTER_SPIRIT, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 2:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_WISE_MISTWEAVER_SPIRIT, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}

				case 3:
				{
					Position pos = { posX, posY, posZ, posO };

					go->SummonCreature(CREATURE_NAMELESS_WINDWALKER_SPIRIT, pos, TEMPSUMMON_MANUAL_DESPAWN);
					break;
				}
			}

			return true;
		}
};

void AddSC_spoils_of_pandaria()
{
    new boss_secured_stockpile_of_spoils();

    /*********************/
	//    Mogu Crates    //
	/*********************/
	// Lightweight Crates
	new mob_animated_stone_mogu();
	new mob_burial_urn();
	new mob_quilen_gardians();
	new gob_lightweight_crate_mogu();

	// Stout Crates
	new mob_modified_anima_golem();
	new mob_mogu_shadow_ritualist();
	new gob_stout_crate_mogu();

	// Massive Crates
	new mob_jun_wei();
	new mob_zu_yin();
	new mob_xiang_lin();
	new mob_kun_da();
	new gob_massive_crate_mogu();

	/***********************/
	//    Mantid Crates    //
	/***********************/
	// Lightweight Crates
	new mob_srithik_bombadiers();
	new mob_amber_encased_kunchongs();
	new mob_korthik_warcallers();
	new gob_lightweight_crate_mantid();

	// Stout Crates
	new mob_zarthik_amber_priests();
	new mob_setthik_wind_wielders();
	new gob_stout_crate_mantid();

	// Massive Crates
	new mob_commander_tik();
	new mob_commander_iktal();
	new mob_commander_nakaz();
	new mob_commander_zaktar();
	new gob_massive_crate_mantid();

	/*************************/
	//    Pandaren Crates    //
	/*************************/
	new mob_ancient_brewmaster_spirits();
	new mob_wise_mistweaver_spirits();
	new mob_nameless_windwalker_spirits();
	new gob_pandaren_crate();
};