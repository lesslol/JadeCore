/*
*	Copyright (C) 2016 - 20XX Cybrann <>
*/

#include "siege_of_orgrimmar.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

// First phase abilities
/*
	During the Assault Phase, Iron Juggernaut uses several abilities against your raid.

	Flame Vents is a frontal cone attack that Iron Juggernaut regularly casts. 
	In addition to dealing high Fire damage, this spell also applies a stacking debuff on affected players, 
	increasing their Fire damage taken by 10% per stack, and causing them to take moderate Fire damage every second. 
	This spell requires a tank switch.

	Borer Drill is an ability that Iron Juggernaut uses roughly every 20 seconds. 
	The boss causes several earth spikes to travel along the ground in several directions, 
	dealing high Physical damage to any players who are hit by them.

	Laser Burn is a nuke that deals high Fire damage to random raid members, 
	and that also leaves a Fire damage DoT on these players. It is unavoidable.

	Mortar Cannon is a shadow crash sort of mechanic. The boss targets a random ranged raid member, 
	and he fires a projectile at their location. The projectile lands 3 seconds later, 
	dealing very high Fire damage in an 8-yard radius. The boss casts this ability roughly every 12 seconds.

	Crawler Mines are small adds that Iron Juggernaut spawns in random locations behind him. 
	The adds spawn in groups of 3, roughly every 20 seconds. These adds cannot be killed, they do not attack, 
	and they do not need to be tanked. The adds remain stationary where they spawn, and, 6 seconds later they explode, 
	dealing very high raid-wide Physical damage. This explosion can be prevented if a player stomps a mine into the ground 
	(by right clicking it while in its melee range). Doing so causes that player to take an extremely high amount of damage 
	(1,250,000 Physical damage) and be knocked up into the air.
*/

// Second phase abilities
/*
	During the Siege Phase, Iron Juggernaut uses 6 abilities against your raid. He continues to use 
	Crawler Mines just like before, and he has some new abilities.

	Seismic Activity Icon Seismic Activity is a constant raid-wide damaging aura that is present during this phase. 
	It deals a moderate amount of Physical damage every second.
	
	Shock Pulse Icon Shock Pulse is a spell that Iron Juggernaut often uses. 
	It knocks all raid members back a very great distance.
	
	Demolisher Cannons Icon Demolisher Cannons is a nuke that Iron Juggernaut often uses. 
	It deals moderate Fire damage to random raid members, and to any other players in a 6-yard radius. It is unavoidable.
	
	Cutter Laser Icon Cutter Laser is a damaging laser beam that Iron Juggernaut uses to chase a 
	random player for 10 seconds. At the point of impact, the laser deals a high amount of Fire damage every second.
	
	Explosive Tar Icon Explosive Tar are damaging and slowing void zones that Iron Juggernaut creates. 
	While these void zones do low damage, they explode if they come in contact with a Cutter Laser, 
	which causes them to deal high raid-wide Fire damage.
	
	During this phase, Iron Juggernaut is stationary and he does not need to be tanked.
*/

enum Spells
{
	// Borer Drill
	SPELL_BORER_DRILL					= 144209,
	SPELL_BORER_DRILL_DOT				= 144218,

	// Flame Vents
	SPELL_FLAME_VENTS					= 144464,
	SPELL_IGNITE_ARMOR					= 144467,

	// Laser Burn
	SPELL_LASER_BURN					= 144459,

	// Crawler Mine
	SPELL_CRAWLER_MINE_BLAST_ONPLAYER	= 123,
	SPELL_CRAWLER_MINE_BLAST			= 144766,
	SPELL_CRAWLER_MINE_DETONATING		= 144718,

	// Mortar Cannon
	// SPELL_MORTAR_CANNON_MARK			= ?,
	// SPELL_MORTAR_CANNON				= ?,

	// Heroic only: Riotchet
	SPELL_RIOTCHET						= 144327,
	SPELL_RIOTCHET_ONE					= 144375,
	SPELL_RIOTCHET_TWO					= 144356,

	// Heroic only: Mortar Barrage
	SPELL_MORTAR_BARRAGE				= 144553,
	SPELL_MORTAR_BARRAGE_ONE			= 144554,
	SPELL_MORTAR_BARRAGE_TWO			= 144555,
	SPELL_MORTAR_BARRAGE_DAMAGE			= 144556,

	// Seismic Activity
	SPELL_SEISMIC_ACTIVITY_TRIGGER		= 144483,
	SPELL_SEISMIC_ACTIVITY_DAMAGE		= 144484,

	//Shock Pulse
	SPELL_SHOCK_PULSE					= 144485,

	// Demolisher Cannon
	SPELL_DEMOLISHER_CANNON				= 144153,

	// Cutter Laser
	SPELL_CUTTER_LASER					= 144918,

	// Explosive Tar
	SPELL_EXPLOSIVE_TAR					= 144498,
	SPELL_EXPLOSIVE_TAR_EXPLOSION		= 123321,
};

enum Events
{
	EVENT_PHASE_ONE					= 1,
	EVENT_PHASE_TWO					= 2,
	EVENT_BORER_DRILL				= 3,
	EVENT_LASER_BURN				= 4,
	EVENT_CRAWLER_MINES				= 5,
	EVENT_FLAME_VENTS				= 6,
	// EVENT_MORTAR_CANNON				= 5, TODO

	// Heroic only
	EVENT_RIOTCHET					= 7,
	EVENT_MORTAR_BARRAGE			= 8,

	EVENT_SEISMIC_ACTIVITY			= 9,
	EVENT_SEISMIC_ACTIVITY_DAMAGE	= 10,
	EVENT_SHOCK_PULSE				= 11,
	EVENT_DEMOLISHER_CANNONS		= 12,
	EVENT_CUTTER_LASER				= 13,
	EVENT_EXPLOSIVE_TAR				= 14,

	// Crawler Mine events
	EVENT_CRAWLER_MINE_DETONATING	= 30,

	// Borer Drill npc
	EVENT_BORER_DRILL_DOT			= 31,
};

enum Creatures
{
	CREATURE_CRAWLER_MINE	= 321321,
};

Position JuggernautSpawnPosition = { 123.0f, 123.0f, 123.0f, 123.0f };

class boss_iron_juggernaut : public CreatureScript
{
	public:
		boss_iron_juggernaut() : CreatureScript("boss_iron_juggernaut") { }

		struct boss_iron_juggernautAI : public BossAI
		{
			boss_iron_juggernautAI(Creature* creature) : BossAI(creature, DATA_IRON_JUGGERNAUT)
			{
				m_Instance = creature->GetInstanceScript();
			}

			InstanceScript* m_Instance;
			uint32 phase;
			Unit* target;

			void Reset() override
			{
				_Reset();
				events.Reset();
				summons.DespawnAll();

				switch (me->GetMap()->GetDifficulty())
				{
					case MAN10_DIFFICULTY:
						me->SetMaxHealth(450000000);
						break;
					case MAN10_HEROIC_DIFFICULTY:
						me->SetMaxHealth(592000000);
						break;
					case MAN25_DIFFICULTY:
						me->SetMaxHealth(1400000000);
						break;
					case MAN25_HEROIC_DIFFICULTY:
						me->SetMaxHealth(1800000000);
						break;
				}

				phase = 1;
			}

			void JustReachedHome()
			{
				_JustReachedHome();

				if (m_Instance)
				{
					m_Instance->SetBossState(DATA_IRON_JUGGERNAUT, FAIL);
				}
			}

			void EnterCombat()
			{
				events.ScheduleEvent(EVENT_FLAME_VENTS, 10000); // TODO: Timer and Spell
				events.ScheduleEvent(EVENT_BORER_DRILL, urand(18000, 20000));
				events.ScheduleEvent(EVENT_CRAWLER_MINES, urand(19000, 21000)); // TODO: Spell/Creature/Whatever
				events.ScheduleEvent(EVENT_LASER_BURN, 10000); // TODO: Timer
				// events.ScheduleEvent(EVENT_MORTAR_CANNON, 12000); TODO

				events.ScheduleEvent(EVENT_PHASE_TWO, 120000);

				// Heroic spell here
				if (me->GetMap()->IsHeroic())
					events.ScheduleEvent(EVENT_RIOTCHET, 15000); // TODO: Spell
			}

			void JustDied(Unit* killer)
			{
				if (m_Instance)
				{
					m_Instance->SetBossState(DATA_IRON_JUGGERNAUT, DONE);
				}

				_JustDied();
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;
				
				if (me->HasUnitState(UNIT_STATE_CASTING) && phase != 2)
					return;
				

				switch (events.ExecuteEvent())
				{
					case EVENT_PHASE_ONE:
					{
						if (phase == 2)
						{
							phase = 1;
							events.Reset();

							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE);
							me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);

							events.ScheduleEvent(EVENT_FLAME_VENTS, 10000); // TODO: Timer and Spell
							events.ScheduleEvent(EVENT_BORER_DRILL, urand(18000, 20000));
							events.ScheduleEvent(EVENT_CRAWLER_MINES, urand(19000, 21000)); // TODO: Spell
							events.ScheduleEvent(EVENT_LASER_BURN, 10000); // TODO: Timer
							// events.ScheduleEvent(EVENT_MORTAR_CANNON, 12000); TODO

							events.ScheduleEvent(EVENT_PHASE_TWO, 120000);

							// Heroic spell here
							if (me->GetMap()->IsHeroic())
								events.ScheduleEvent(EVENT_RIOTCHET, 15000); // TODO: Spell

							break;
						}
						else
							break;
					}

					case EVENT_FLAME_VENTS:
					{
						if (phase == 1)
						{
							if (Unit* target = me->getVictim())
							{
								me->CastSpell(target, SPELL_FLAME_VENTS);
								me->CastSpell(target, SPELL_IGNITE_ARMOR);
							}

							events.ScheduleEvent(EVENT_FLAME_VENTS, 10000); // TODO: Timer and Spell
							break;
						}
						else
							break;
					}

					case EVENT_BORER_DRILL:
					{
						if (phase == 1)
						{
							float posX = me->GetPositionX();
							float posY = me->GetPositionY();
							float ang = me->GetOrientation();
							float posZ = me->GetPositionZ();
							float pX = urand(posX-30.0f, posX+30.0f);
							float pY = urand(posY-30.0f, posY+30.0f);

							me->SummonCreature(71906, pX, pY, posZ, ang, TEMPSUMMON_MANUAL_DESPAWN);							

							events.ScheduleEvent(EVENT_BORER_DRILL, urand(18000, 20000));
							break;
						}
						else
							break;
					}

					case EVENT_LASER_BURN:
					{
						if (phase == 1)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								me->CastSpell(target, SPELL_LASER_BURN);
							}

							events.ScheduleEvent(EVENT_LASER_BURN, 10000); // TODO: Timer
							break;
						}
						else
							break;
					}

					case EVENT_CRAWLER_MINES:
					{
						if (phase == 1 || phase == 2)
						{
							float positionX = me->GetPositionX();
							float positionY = me->GetPositionY();
							float positionZ = me->GetPositionZ();
							float orientation = me->GetOrientation();
							float newX;
							float newY;
							bool positiveX = positionX > 0;
							bool positiveY = positionY > 0;

							if (positiveX)
							{
								newX = urand(positionX-10.0f, positionX-30.0f);
							}
							else if (!positiveX)
							{
								newX = urand(positionX+10.0f, positionX+30.0f);
							}

							if (positiveY)
							{
								newY = urand(positionY-10.0f, positionY-30.0f);
							}
							else if (!positiveY)
							{
								newY = urand(positionY+10.0f, positionY+30.0f);
							}

							Position crawlers = { newX, newY, positionZ, orientation };

							for (int i = 0; i <= 3; i++)
								me->SummonCreature(CREATURE_CRAWLER_MINE, crawlers, TEMPSUMMON_MANUAL_DESPAWN);
						}
						else
							break;
					}

					/*case EVENT_MORTAR_CANNON:
					{
						// TODO: I can't even find spell ids for this mechanic
						if (phase == 1)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true)
							{
								me->CastSpell(target, SPELL_MORTAR_CANNON_MARK);
								me->CastSpell(target, SPELL_MORTAR_CANNON);
							}

							events.ScheduleEvent(EVENT_MORTAR_CANNON, 12000);
							break;
						}

						break;
					}*/

					case EVENT_RIOTCHET:
					{
						if (phase == 1)
						{
							std::list<Player*> pl_list;
							target->GetPlayerListInGrid(pl_list, 100.0f);
							if (target->GetTypeId() == TYPEID_PLAYER)
							{
								if (Player* victim = target->ToPlayer())
								{
									if (victim->GetSpecializationId(victim->GetActiveSpec()) == SPEC_WARRIOR_ARMS
										|| SPEC_WARRIOR_FURY
										|| SPEC_WARRIOR_PROTECTION
										|| SPEC_PALADIN_PROTECTION
										|| SPEC_PALADIN_RETRIBUTION
										|| SPEC_ROGUE_ASSASSINATION
										|| SPEC_ROGUE_COMBAT
										|| SPEC_ROGUE_SUBTLETY
										|| SPEC_DK_BLOOD
										|| SPEC_DK_FROST
										|| SPEC_DK_UNHOLY
										|| SPEC_DROOD_BEAR
										|| SPEC_DROOD_CAT
										|| SPEC_MONK_BREWMASTER
										|| SPEC_MONK_WINDWALKER
										|| SPEC_SHAMAN_ENHANCEMENT)
									{
										return;
									}
									else if (victim->GetSpecializationId(victim->GetActiveSpec()) == SPEC_DROOD_BALANCE
										|| SPEC_DROOD_RESTORATION
										|| SPEC_MAGE_ARCANE
										|| SPEC_MAGE_FIRE
										|| SPEC_MAGE_FROST
										|| SPEC_WARLOCK_AFFLICTION
										|| SPEC_WARLOCK_DESTRUCTION
										|| SPEC_WARLOCK_DEMONOLOGY
										|| SPEC_HUNTER_BEASTMASTER
										|| SPEC_HUNTER_MARKSMAN
										|| SPEC_HUNTER_SURVIVAL
										|| SPEC_PRIEST_DISCIPLINE
										|| SPEC_PRIEST_HOLY
										|| SPEC_PRIEST_SHADOW
										|| SPEC_SHAMAN_ELEMENTAL
										|| SPEC_SHAMAN_RESTORATION
										|| SPEC_MONK_MISTWEAVER
										|| SPEC_PALADIN_HOLY)
									{
										me->CastSpell(target, SPELL_RIOTCHET);
									}
								}
							}

							events.ScheduleEvent(EVENT_RIOTCHET, 15000);
							break;
						}
					}

					case EVENT_PHASE_TWO:
					{
						if (phase == 1)
						{
							phase = 2;
							events.Reset();

							me->GetMotionMaster()->MovePoint(1, JuggernautSpawnPosition);

							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE);
							me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);

							events.ScheduleEvent(EVENT_SEISMIC_ACTIVITY, 1);
							events.ScheduleEvent(EVENT_SHOCK_PULSE, 1);
							events.ScheduleEvent(EVENT_DEMOLISHER_CANNONS, 1);
							events.ScheduleEvent(EVENT_CUTTER_LASER, 1);
							events.ScheduleEvent(EVENT_EXPLOSIVE_TAR, 1);
							events.ScheduleEvent(EVENT_CRAWLER_MINES, urand(19000, 21000));

							events.ScheduleEvent(EVENT_PHASE_ONE, 60000);

							if (me->GetMap()->IsHeroic())
								events.ScheduleEvent(EVENT_MORTAR_BARRAGE, 2500);
						}						
					}

					case EVENT_SEISMIC_ACTIVITY:
					{
						if (phase == 2)
						{
							me->CastSpell(me, SPELL_SEISMIC_ACTIVITY_TRIGGER);
							me->CastSpell(me, SPELL_SEISMIC_ACTIVITY_DAMAGE);

							events.ScheduleEvent(EVENT_SEISMIC_ACTIVITY_DAMAGE, 1000);
							break;
						}
						else
							break;
					}

					case EVENT_SEISMIC_ACTIVITY_DAMAGE:
					{
						if (phase == 2)
						{
							me->CastSpell(me, SPELL_SEISMIC_ACTIVITY_DAMAGE);

							events.ScheduleEvent(EVENT_SEISMIC_ACTIVITY_DAMAGE, 1000);
							break;
						}
						else
							break;
					}

					case EVENT_SHOCK_PULSE:
					{
						if (phase == 2)
						{
							me->CastSpell(me, SPELL_SHOCK_PULSE);

							events.ScheduleEvent(EVENT_SHOCK_PULSE, 1);
							break;
						}
						else
							break;
					}

					case EVENT_DEMOLISHER_CANNONS:
					{
						if (phase == 2)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								me->CastSpell(target, SPELL_DEMOLISHER_CANNON);
							}

							events.ScheduleEvent(EVENT_DEMOLISHER_CANNONS, 1);
							break;
						}
						else
							break;
					}

					case EVENT_CUTTER_LASER:
					{
						if (phase == 2)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								me->CastSpell(target, SPELL_CUTTER_LASER);
							}

							events.ScheduleEvent(EVENT_CUTTER_LASER, 1);
							break;
						}
						else
							break;
					}

					case EVENT_EXPLOSIVE_TAR:
					{
						if (phase == 2)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								me->CastSpell(target, SPELL_EXPLOSIVE_TAR);
							}

							events.ScheduleEvent(EVENT_EXPLOSIVE_TAR, 1);
							break;
						}
						else
							break;
					}

					case EVENT_MORTAR_BARRAGE:
					{
						if (phase == 2)
						{
							if (Unit* target = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								me->CastSpell(target, SPELL_MORTAR_BARRAGE_DAMAGE);
							}

							events.ScheduleEvent(EVENT_MORTAR_BARRAGE, 2500);
							break;
						}
						else
							break;
					}
				}

				if (phase == 1)
					DoMeleeAttackIfReady();
				else
					return;
			}
		};

		CreatureAI* GetAI(Creature* creature) const override
		{
			return new boss_iron_juggernautAI(creature);
		}
};

class npc_crawler_mine : public CreatureScript
{
	public:
		npc_crawler_mine() : CreatureScript("npc_crawler_mine") { }

		bool OnGossipHello(Player* player, Creature* creature)
		{
			if (player->GetTypeId() != TYPEID_PLAYER)
				return false;

			creature->DespawnOrUnsummon(0);
			creature->CastSpell(player, SPELL_CRAWLER_MINE_BLAST_ONPLAYER, true);
			return true;
		}

		struct npc_crawler_mineAI : public ScriptedAI
		{
			npc_crawler_mineAI(Creature* creature) : ScriptedAI(creature)
			{
				m_Instance = creature->GetInstanceScript();
			}

			InstanceScript* m_Instance;

			void Reset() override
			{
				me->SetReactState(ReactStates::REACT_PASSIVE);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE);
				me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
				me->SetInCombatWithZone();
				events.ScheduleEvent(EVENT_CRAWLER_MINE_DETONATING, 6000);
			}

			void UpdateAI(const uint32 diff)
			{
				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				switch (events.ExecuteEvent())
				{
					case EVENT_CRAWLER_MINE_DETONATING:
					{
						me->CastSpell(me, SPELL_CRAWLER_MINE_BLAST, true);
						me->DespawnOrUnsummon(0);
						break;
					}
				}
			}
		};

		CreatureAI* GetAI(Creature* creature) const override
		{
			return new npc_crawler_mineAI(creature);
		}
};

// 71906 - Borer Drill target
class npc_borer_drill : public CreatureScript
{
	public:
		npc_borer_drill() : CreatureScript("npc_borer_drill") { }

		struct npc_borer_drillAI : public Scripted_NoMovementAI
		{
			npc_borer_drillAI(Creature* creature) : Scripted_NoMovementAI(creature)
			{
				m_Instance = creature->GetInstanceScript();
			}

			InstanceScript* m_Instance;

			void Reset() override
			{
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);

				me->setFaction(16);
				events.ScheduleEvent(EVENT_BORER_DRILL_DOT, 1);
			}

			void UpdateAI(const uint32 diff)
			{
				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				switch (events.ExecuteEvent())
				{
					case EVENT_BORER_DRILL_DOT:
					{
						std::list<Player*> pl_list;
						me->GetPlayerListInGrid(pl_list, 9.0f);

						if (!pl_list.empty())
						{
							Unit* target;
							me->CastSpell(target, SPELL_BORER_DRILL_DOT);
						}

						me->CastSpell(me, SPELL_BORER_DRILL);

						events.ScheduleEvent(EVENT_BORER_DRILL_DOT, 1);
					}
				}
			}			
		};

		CreatureAI* GetAI(Creature* creature) const override
		{
			return new npc_borer_drillAI(creature);
		}
};

// 144218
class spell_borer_drill_dot : public SpellScriptLoader
{
	public:
		spell_borer_drill_dot() : SpellScriptLoader("spell_borer_drill_dot") { }

		class spell_borer_drill_dot_SpellScript : public SpellScript
		{
			PrepareSpellScript(spell_borer_drill_dot_SpellScript);

			void HandleDamage(SpellEffIndex /*effIndex*/)
			{
				if (Unit* caster = GetCaster())
				{
					int32 damage = 75000;
					SetHitDamage(damage);
				}
			}

			void Register()
			{
				OnEffectHitTarget += SpellEffectFn(spell_borer_drill_dot_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
			}
		};

		SpellScript* GetSpellScript() const
		{
			return new spell_borer_drill_dot_SpellScript();
		}
};

void AddSC_boss_iron_juggernaut()
{
	// Boss
	new boss_iron_juggernaut();

	// Creatures
	new npc_crawler_mine();
	new npc_borer_drill();

	// Spells
	new spell_borer_drill_dot();
}