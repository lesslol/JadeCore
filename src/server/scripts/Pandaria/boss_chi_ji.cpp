/*
    World Boss: Chi-Ji <The Red Crane>

    ======= QUEST =======
    [90] Celestial Blessings

    Wrathion says: Great Red Crane! Hear our plea.
    Wrathion says: My champion and I seek your blessing of Hope.
    Chi-Ji says: My my, the child of the Worldbreaker, proof that none are beyond redemption. I am honored by your visit.
    Chi-Ji says: Tell me, Son of the Earth-Warder: What is the nature of hope?
    Wrathion says: Hope is...a belief of a better tomorrow.
    Chi-Ji says: You speak, but doubt your own words.
    // Wrathion kneels
    Wrathion says: ...Great Crane. You have not seen what I have seen.
    Chi-Ji says: You underestimate me.
    Wrathion says: ...the fire that once burned the sky will return. It is inevitable. The Burning Legion WILL find Azeroth.
    Wrathion says: Seas of blood, cities in ruins! Who are we - one divided world - to stand against a legion?
    Wrathion says: You speak of hope. Believe me, the thinnest silver of belief that we might somehow survive the coming devastation is all that sustains me.
    Chi-Ji says: Rise, son of Deathwing. I will give you my blessing, for you need it more than any I have ever met.
    // Wrathion stands
    Chi-Ji says: I challenge you not to think of hope as a vague and unimaginable future.
    Chi-Ji says: Live EVERY day with hope in your heart. In doing so, you CREATE the future you dream of.
    Wrathion says: ...thank you, Great Crane.

    Intro
    Emperor Shaohao yells: The Red Crane saw hope in me, and instructed me to look inward. Despite my visage of despair, I found this hope, and the despair was vanquished.

    Death
    Emperor Shaohao yells: You have walked the trial of hope, and learned of the path of the red crane. May it guide your footsteps through time.
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CreatureTextMgr.h"

enum Texts
{
    // Chi Ji
    SAY_INTRO = 0, // When faced with challenges, the like you have never seen, what do you hope for? What is the future you seek?
    SAY_AGGRO = 1, // Then let us begin!
    SAY_DEATH = 2, // Your hope shines brightly, and even more brightly when you work together to overcome. It will ever light your way, in even the darkest of places.
    SAY_SLAY = 3, // Do not give up on yourself!
    SAY_BEACON_HOPE = 4, // Believe in one another, and let others carry hope for you.
    SAY_CRANE_RUSH = 5,  // 0 - Without hope, there is no brightness in the future. ; 1 - Create the destiny you seek.

    //XEUN
    SAY_XUEN_AGGRO = 6, // Haha.. the trial commensenses
    SAY_XUEN_INTRO = 7, // Strength is far more then simple physocal frowess, when you are truly pested.. will you be able to tell the difference - between Strength and Power.
    SAY_XUEN_KILL = 8, // Return twice as powerful
    SAY_XUEN_SPELL1 = 9, // Believe in your strength
    SAY_XUEN_SPELL2 = 10, // You have the power to change your destiny
    SAY_XUEN_SPELL3 = 11, // Do not mistake the power offers for TRUE strength!
    SAY_XUEN_DIE = 12, // You are strong.. stronger even then you realize, carry this thought into the darkness a head, let it shield you.

    // YULON
    SAY_YULON_AGGRO = 13, // The trial begins! (38222)
    SAY_YULON_DEATH = 14, // Your wisdom has seen you through this trial, may it ever light your way out of dark places. (38223)
    SAY_YULON_INTRO = 15, // The lesson of true wisdom lies within you dear heroes and in the choices you make. When face with overwhelming darkness, will you make the right decisions?  (38224)
    SAY_YULON_KILL  = 16, // Learn from your mistakes! (38225)
    SAY_YULON_SPELL01 = 17, // Listen to your inner voice, and seek out the truth (38226)
    SAY_YULON_SPELL02 = 18, // Do not let your judgement be clouded in trial times. (38227)
    SAY_YULONG_SPELL03 = 19, // Always consider the consiquences of your actions. (38228)

    // Niuzao
    SAY_NIUZAO_AGGRO = 20, // We shall see..
    SAY_NIUZAO_DEATH = 21, // Though you will surrounded by force.. greater the you can ever imagine. You fortitude will allow you to endure, remember this in the time a head.
    SAY_NIUZAO_INTRO = 22, // Can you stand on the tallest peak? winds and sleet bufferting your skins.. until the tree weavers and the mountains fall into the sea.
    SAY_NIUZAO_KILL = 23, // You must persevere!
    SAY_NIUZAO_SPELL01 = 24, // The winds maybe strong and sleet may sting!
    SAY_NIUZAO_SPELL02 = 25, // You are the mountain, unmoveable by all but time!
    SAY_NIUZAO_SPELL03 = 26, // Be vigilant in your stand, or you'll never achieve your goals!
};

enum Spells
{
    // Boss
    SPELL_INSPIRING_SONG    = 144468, // Heal spell.
    SPELL_FIRESTORM_SUMMON  = 144461, // Summons NPC_FIRESTORM in 15y.
    SPELL_BEACON_OF_HOPE_S  = 144473, // Summons NPC_BEACON_OF_HOPE.
    SPELL_BLAZING_SONG      = 144471, // Per. dmg. boss aura. Triggers 144472 dmg. each 2s, 65y radius.
    SPELL_CRANE_RUSH        = 144470, // 66 and 33%. Triggers 144495 each sec, summoning NPC_CHILD_OF_CHIJI each 0.5s in 5y.

    // NPCs
    SPELL_FIRESTORM_AURA    = 144463, // Per. dmg. npc aura. Triggers 144462 dmg. each 2s.
    SPELL_BEACON_OF_HOPE_A  = 144474, // Per. dmg. decrease npc aura. Triggers 144475 each 1s, 10y radius.
    SPELL_BURNING_NOVA_A    = 144493, // Per. dmg. npc aura. Triggers 144494 dmg. each 2s, 4y radius.

    SPELL_SPECTRAL_SWIPE      = 144638,
    SPELL_CRACKLING_LIGHTNING = 144633,
    SPELL_CHI_BARRAGE = 144643,

    SPELL_JADEFLAME_BUFFET = 144630,
    SPELL_JADEFIRE_BREATH = 144530,
    SPELL_JADEFIRE_BOLT = 147454,
    SPELL_JADEFIRE_BLAZE = 144537,
    SPELL_JADEFIRE_WALL = 144533,
    SPELL_JADE_FIRE_DMG = 144539,

    SPELL_CHARGE_DUMMY = 144608,
    SPELL_CHARGE_DAMAGE = 144609,
    SPELL_HEAD_BUTT = 147382,
    SPELL_MASSIVE_QUAKE_AURA = 144611,
    SPELL_MASSIVE_QUAKE_DAMAGE = 144612,
    SPELL_OXEN_FORTITUDE = 144606,
};

enum Events
{
    EVENT_INSPIRING_SONG   = 1, // 20s from aggro, 30s after.
    EVENT_FIRESTORM        = 2, // 12s from aggro, 45s after.
    EVENT_BEACON_OF_HOPE   = 3, // 45s from aggro, 65s after.
    EVENT_BLAZING_SONG     = 4, // 9s after beacon of hope.
    EVENT_CRANE_RUSH       = 5,  // 66 and 33%.

    // Xuen
    EVENT_SPECTRAL_SWIPE      = 6,
    EVENT_LEAP                = 7,
    EVENT_CRACKLING_LIGHTNING = 8,
    EVENT_CHI_CARRAGE         = 9,
    EVENT_AGILITY             = 10,

    EVENT_JADEFLAME_BUFFET    = 11,
    EVENT_JADEFIRE_BREATH     = 12,
    EVENT_JADEFIRE_BOLT       = 13,
    EVENT_JADEFIRE_BLAZE      = 14,
    EVENT_JADEFIRE_WALL       = 15,

    EVENT_CHARGE_NIUZAO       = 16,
    EVENT_HEADBUTT            = 17,
    EVENT_MASSIVE_QUAKE       = 18,
    EVENT_FORTITUDE           = 19,
    EVENT_CHARGE_EXECUTE      = 20,
    EVENT_CHARGE_DROP         = 21,

};
enum Npcs
{
    NPC_FIRESTORM          = 71971,
    NPC_BEACON_OF_HOPE     = 71978,
    NPC_CHILD_OF_CHIJI     = 71990,
    NPC_JADEFIRE_WALL      = 72020,
    NPC_JADEFIRE_BUFFET    = 535631,
};

enum CraneRushStates
{
    DONE_NONE              = 0, // No casts done.
    DONE_66                = 1, // First cast done.
    DONE_33                = 2  // Both casts done.
};

Position NiuzaoCharge[6] = 
{
    {-748.489f, -5018.333f, -6.277176f},
    {-749.945f, -4954.650f, -6.277176f},
    {-559.781f, -4950.705f, -6.277176f},
    {-556.898f, -5080.271f, -6.277087f},
    {-742.904f, -5085.499f, -6.277087f},
    {-748.489f, -5018.333f, -6.277176f},
};

class boss_chi_ji : public CreatureScript
{
    public:
        boss_chi_ji() : CreatureScript("boss_chi_ji") { }

        struct boss_chi_jiAI : public ScriptedAI
        {
            boss_chi_jiAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

            EventMap _events;
            SummonList summons;
            uint8 craneRushDone;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _events.Reset();
                summons.DespawnAll();

                craneRushDone = DONE_NONE;
            }
    
            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);

                _events.ScheduleEvent(EVENT_INSPIRING_SONG, urand(18000, 23000)); // 18-23
                _events.ScheduleEvent(EVENT_FIRESTORM, urand(12000, 14000));      // 12-14
                _events.ScheduleEvent(EVENT_BEACON_OF_HOPE, urand(44000, 48000)); // 44-48
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_SLAY);
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(false);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
                summons.DespawnAll();

                /*
                const std::list<HostileReference*>& threatlist = me->getThreatManager().getThreatList();

                std::list<Unit*> targetList;
                targetList.clear();
                for (std::list<HostileReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                {
                std::list<Unit*>::iterator itr = targetList.begin();
                itr-
                }
                */
                /*
                QueryResult result = CharacterDatabase.PQuery("SELECT guid, quest FROM character_queststatus_weekly WHERE id = %u", guid, 99999);

                Field* dields = result->Fetch();
                uint32 bop = dields[0].GetUInt32();
                uint32 lb = dields[1].GetUInt32();
                */

                Quest const* quest = sObjectMgr->GetQuestTemplate(99999);

                if (!quest)
                    return;

                std::list<Player*> pl_list;
                pl_list.clear();

                me->GetPlayerListInGrid(pl_list, 50.0f);

                if (pl_list.empty())
                    return;

                for (auto itr : pl_list)
                {
                    if (itr->CheckWeeklyCooldown(99999))
                    {
                        itr->AddQuest(quest, me);
                        itr->CompleteQuest(99999);
                        itr->RewardQuest(quest, 0, me, true);
                        itr->SetWeeklyQuestStatus(99999);
                    }
                    else
                    {
                        ChatHandler(itr->GetSession()).PSendSysMessage("You are saved for this loot, this can only acquired once a week");
                    }
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                switch (summon->GetEntry())
                {
                    case NPC_FIRESTORM:
                        summon->AddAura(SPELL_FIRESTORM_AURA, summon);
                        summon->SetReactState(REACT_PASSIVE);
						summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        summon->SetSpeed(MOVE_WALK, 0.7f);
                        summon->SetSpeed(MOVE_RUN, 0.7f);
                        summon->GetMotionMaster()->MoveRandom(20.0f);
                        break;

                    case NPC_BEACON_OF_HOPE:
                        summon->AddAura(SPELL_BEACON_OF_HOPE_A, summon);
                        summon->SetReactState(REACT_PASSIVE);
                        break;

                    case NPC_CHILD_OF_CHIJI:
                    {
                        summon->AddAura(SPELL_BURNING_NOVA_A, summon);
                        summon->SetReactState(REACT_PASSIVE);
                        summon->SetSpeed(MOVE_WALK, 0.85f);
                        summon->SetSpeed(MOVE_RUN, 0.85f);
                        float x, y, z;
                        summon->GetClosePoint(x, y, z, summon->GetObjectSize() / 3, 50.0f);
                        summon->GetMotionMaster()->MovePoint(1, x, y, z); // Move forward 50y (enough time to despawn properly).
                        summon->DespawnOrUnsummon(30000); // Spell time is 1 minute, but it's too much to move the Child constantly.
                        break;
                    }

                    default: break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                // Set Crane Rush phases execution.
                if (me->HealthBelowPct(67) && craneRushDone == DONE_NONE || me->HealthBelowPct(34) && craneRushDone == DONE_66)
                {
                    _events.ScheduleEvent(EVENT_CRANE_RUSH, 2000);
                    craneRushDone++;
                }

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INSPIRING_SONG:
                            DoCast(me, SPELL_INSPIRING_SONG);
                            _events.ScheduleEvent(EVENT_INSPIRING_SONG, urand(35000, 40000));
                            break;

                        case EVENT_FIRESTORM:
                            DoCast(me, SPELL_FIRESTORM_SUMMON);
                            _events.ScheduleEvent(EVENT_FIRESTORM, urand(43000, 47000));
                            break;

                        case EVENT_BEACON_OF_HOPE:
                            Talk(SAY_BEACON_HOPE);
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                DoCast(target, SPELL_BEACON_OF_HOPE_S);
                            _events.ScheduleEvent(EVENT_BLAZING_SONG, urand(8000, 9500));
                            _events.ScheduleEvent(EVENT_BEACON_OF_HOPE, urand(70000, 75000)); // 65 + Blazing Song delay.
                            break;

                        case EVENT_BLAZING_SONG:
                            DoCast(me, SPELL_BLAZING_SONG);
                            break;

                        case EVENT_CRANE_RUSH:
                            Talk(SAY_CRANE_RUSH);
                            DoCast(me, SPELL_CRANE_RUSH); // Channeled.
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_chi_jiAI(creature);
        }
};


class boss_xuen: public CreatureScript
{
public:
    boss_xuen() : CreatureScript("boss_xuen") { }

    struct boss_xuenAI : public ScriptedAI
    {
        boss_xuenAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

        EventMap _events;
        SummonList summons;

        uint64 Target = NULL;

        void Reset()
        {
            _events.Reset();
            summons.DespawnAll();

            Target = NULL;

            me->setFaction(16);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_XUEN_AGGRO);

            _events.ScheduleEvent(EVENT_AGILITY, 80 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_CHARGE, 15 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_CHI_CARRAGE, urand(30000, 35000));
            _events.ScheduleEvent(EVENT_CRACKLING_LIGHTNING, urand(43000, 47000));
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_XUEN_KILL);
        }

        void EnterEvadeMode()
        {
            Reset();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_XUEN_DIE);
            summons.DespawnAll();

            Quest const* quest = sObjectMgr->GetQuestTemplate(99998);

            if (!quest)
                return;

            std::list<Player*> pl_list;
            me->GetPlayerListInGrid(pl_list, 50.0f);

            if (pl_list.empty())
                return;

            for (auto itr : pl_list)
            {
                itr->AddQuest(quest, me);
                itr->CompleteQuest(99998);
                itr->RewardQuest(quest, 0, me, true);
                itr->SetWeeklyQuestStatus(99998);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_AGILITY:
                    DoCast(me, 144631);
                    _events.ScheduleEvent(EVENT_AGILITY, 80 * TimeConstants::IN_MILLISECONDS);
                    Talk(SAY_XUEN_SPELL3);
                    break;
                case EVENT_CHARGE:
                    if (Unit* l_Target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        me->CastSpell(l_Target->GetPositionX(), l_Target->GetPositionY(), l_Target->GetPositionZ(), 133071, true);
                        Target = l_Target->GetGUID();
                    }

                    _events.ScheduleEvent(EVENT_CHARGE, 15 * TimeConstants::IN_MILLISECONDS);
                    _events.ScheduleEvent(EVENT_SPECTRAL_SWIPE, 4 * TimeConstants::IN_MILLISECONDS);
                    break;
                case EVENT_SPECTRAL_SWIPE:
                    if (Target != NULL)
                    {
                        if (Unit* unit = sObjectAccessor->GetUnit(*me, Target))
                        {
                            me->CastSpell(unit, Spells::SPELL_SPECTRAL_SWIPE);
                        }
                    }
                    break;
                case EVENT_CHI_CARRAGE:
                    if (Unit* l_Target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        Talk(SAY_XUEN_SPELL1);
                        DoCast(l_Target, 144643);
                    }

                    _events.ScheduleEvent(EVENT_CHI_CARRAGE, urand(30000, 35000));
                    break;
                case EVENT_CRACKLING_LIGHTNING:
                    Talk(SAY_XUEN_SPELL2);
                    me->CastSpell(me, 144635);
                    _events.ScheduleEvent(EVENT_CRACKLING_LIGHTNING, urand(43000, 47000));
                    break;
                default: break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_xuenAI(creature);
    }
};

Position Waves[3] = 
{
    {-741.666f, -5090.383f, -6.276f},
    {-683.549f, -5091.770f, -6.276f},
    {-598.750f, -5093.851f, -6.276f},
};
Position WavePoint[3] =
{
    { -736.801f, -4938.373f, -6.277f },
    { -683.906f, -4941.415f, -6.277f },
    { -597.101f, -4941.426f, -6.277f },
};

class boss_yulon : public CreatureScript
{
public:
    boss_yulon() : CreatureScript("boss_yulon") { }

    struct boss_yulonAI : public ScriptedAI
    {
        boss_yulonAI(Creature* creature) : ScriptedAI(creature), summons(me) 
        {
            intro = false;
        }

        EventMap _events;
        SummonList summons;
        bool intro;

        uint64 Target = NULL;

        void Reset()
        {
            _events.Reset();
            summons.DespawnAll();

            Target = NULL;

            me->setFaction(16);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && !intro && me->IsWithinDistInMap(who, 40.0f))
            {
                intro = true;

                Talk(SAY_YULON_INTRO);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_YULON_AGGRO);

            _events.ScheduleEvent(EVENT_JADEFIRE_BLAZE, 10 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_JADEFIRE_BOLT, 14 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_JADEFIRE_BREATH, 30 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_JADEFIRE_WALL, 45000);
            _events.ScheduleEvent(EVENT_JADEFLAME_BUFFET, 25);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_YULON_KILL);
        }

        void EnterEvadeMode()
        {
            Reset();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_YULON_DEATH);
            summons.DespawnAll();

            Quest const* quest = sObjectMgr->GetQuestTemplate(99997);

            if (!quest)
                return;

            std::list<Player*> pl_list;
            me->GetPlayerListInGrid(pl_list, 50.0f);

            if (pl_list.empty())
                return;

            for (auto itr : pl_list)
            {
                itr->AddQuest(quest, me);
                itr->CompleteQuest(99997);
                itr->RewardQuest(quest, 0, me, true);
                itr->SetWeeklyQuestStatus(99997);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_JADEFIRE_BOLT:
                    {
                        std::list<Player*> listPlayers;
                        me->GetPlayerListInGrid(listPlayers, 60.0f);

                        if (listPlayers.empty())
                            return;

                        for (auto itr : listPlayers)
                        {
                            me->CastSpell(itr, SPELL_JADEFIRE_BOLT, true);
                        }

                        _events.ScheduleEvent(EVENT_JADEFIRE_BOLT, 15 * TimeConstants::IN_MILLISECONDS);
                        break;
                    }
                    case EVENT_JADEFIRE_BREATH:
                        if (Unit* l_Target = me->getVictim())
                        {
                            me->CastSpell(l_Target, SPELL_JADEFIRE_BREATH);
                        }

                        _events.ScheduleEvent(EVENT_JADEFIRE_BREATH, 30 * TimeConstants::IN_MILLISECONDS);
                        break;
                    case EVENT_JADEFIRE_BLAZE:
                        me->CastSpell(me->getVictim(), SPELL_JADEFLAME_BUFFET);
                        _events.ScheduleEvent(EVENT_JADEFIRE_BLAZE, 14 * TimeConstants::IN_MILLISECONDS);
                        break;
                    case EVENT_JADEFLAME_BUFFET:
                        Position pos;
                        me->GetRandomNearPosition(pos, 40.0f);

                        me->SummonCreature(NPC_JADEFIRE_BUFFET, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);

                        _events.ScheduleEvent(EVENT_JADEFLAME_BUFFET, 30 * TimeConstants::IN_MILLISECONDS);
                        break;
                    case EVENT_JADEFIRE_WALL:
                        for (int32 i = 0; i < 4; i++)
                        {
                            Creature* wave = me->SummonCreature(NPC_JADEFIRE_WALL, Waves[i], TEMPSUMMON_TIMED_DESPAWN, 60000);
                            if (wave)
                                wave->GetMotionMaster()->MovePoint(0, WavePoint[i].GetPositionX(), WavePoint[i].GetPositionY(), WavePoint[i].GetPositionZ());
                        }
                        _events.ScheduleEvent(EVENT_JADEFIRE_WALL, 50000);
                        break;
                    default: break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_yulonAI(creature);
    }
};

class npc_yulon_wall : public CreatureScript
{
public:
    npc_yulon_wall() : CreatureScript("npc_yulon_wall") { }

    struct npc_yulon_wallAI : public ScriptedAI
    {
        npc_yulon_wallAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap _events;

        uint64 Target = NULL;

        uint32 diffs;

        void Reset()
        {
            diffs = 500;

            me->SetSpeed(MOVE_RUN, 2.8f, true);

            me->setFaction(16);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_JADEFIRE_WALL);

            me->SetFlag(UNIT_FIELD_FLAGS, UnitFlags::UNIT_FLAG_NON_ATTACKABLE | UnitFlags::UNIT_FLAG_DISABLE_MOVE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (diffs <= diff)
            {
                std::list<Player*> pl_list;
                me->GetPlayerListInGrid(pl_list, 3.5f);

                if (pl_list.empty())
                    return;

                for (auto itr : pl_list)
                {
                    if (me->IsWithinDistInMap(itr, 5.0f))
                        me->CastSpell(itr, SPELL_JADE_FIRE_DMG);
                }

                diffs = 1000;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_yulon_wallAI(creature);
    }
};

class npc_yulon_buffet : public CreatureScript
{
public:
    npc_yulon_buffet() : CreatureScript("npc_yulon_buffet") { }

    struct npc_yulon_wallAI : public Scripted_NoMovementAI
    {
        npc_yulon_wallAI(Creature* creature) : Scripted_NoMovementAI(creature) { }

        EventMap _events;

        uint32 diffs; 

        void Reset()
        {
            diffs = 500;

            me->setFaction(16);
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_JADEFIRE_BLAZE);

            me->SetFlag(UNIT_FIELD_FLAGS, UnitFlags::UNIT_FLAG_NON_ATTACKABLE | UnitFlags::UNIT_FLAG_DISABLE_MOVE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (diffs <= diff)
            {
                diffs = 1000;

                std::list<Player*> pl_list;
                me->GetPlayerListInGrid(pl_list, 2.3f);

if (pl_list.empty())
return;

for (auto itr : pl_list)
{
    if (me->IsWithinDistInMap(itr, 2.3f))
        itr->CastSpell(itr, 144538);
}

            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_yulon_wallAI(creature);
    }
};

class spell_xeon_chu : public SpellScriptLoader
{
public:
    spell_xeon_chu() : SpellScriptLoader("spell_xeon_chu") { }

    class spell_xeon_chuAI : public AuraScript
    {
        PrepareAuraScript(spell_xeon_chuAI);

        void HandlePeriodic(constAuraEffectPtr /*aurEff*/)
        {
            if (GetCaster())
            {
                std::list<Player*> l_Playerlists;
                GetCaster()->GetPlayerListInGrid(l_Playerlists, 300.0f);

                if (l_Playerlists.empty())
                    return;

                for (auto itr : l_Playerlists)
                {
                    itr->CastSpell(itr, 144633);
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_xeon_chuAI::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_xeon_chuAI();
    }
};

enum actionss
{
    action_activate = 1,
    action_reset = 2,
};

// Boss Niuzao
class mob_trigger_niuzao_charge : public CreatureScript
{
public:
    mob_trigger_niuzao_charge() : CreatureScript("mob_trigger_niuzao_charge") { }

    struct boss_niuzaoAI : public ScriptedAI
    {
        boss_niuzaoAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
        }

        EventMap _events;
        SummonList summons;
        bool intro;

        void Reset()
        {
            intro = false;
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
            case action_reset:
                intro = false;
                break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!intro)
            {
                if (Creature* niuzao = me->FindNearestCreature(71954, 5.0f))
                {
                    intro = true;

                    if (niuzao->GetAI())
                        niuzao->GetAI()->DoAction(action_activate);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_niuzaoAI(creature);
    }
};

// Boss Niuzao
class boss_niuzao : public CreatureScript
{
public:
    boss_niuzao() : CreatureScript("boss_niuzao") { }

    struct boss_niuzaoAI : public ScriptedAI
    {
        boss_niuzaoAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            intro = false;
        }

        EventMap _events;
        SummonList summons;
        bool intro;
        uint32 diffcd;
        uint32 intet;

        void Reset()
        {
            _events.Reset();
            summons.DespawnAll();

            me->setFaction(16);  

            diffcd = 2000;
            intet = 0;

            // Remove fortitude
            std::list<Player*> listPlayers;
            me->GetPlayerListInGrid(listPlayers, 300.0f);

            if (listPlayers.empty())
                return;

            for (auto itr : listPlayers)
            {
                if (itr->HasAura(144607))
                itr->RemoveAura(144607);
            }

            std::list<Creature*> triggers;
            me->GetCreatureListWithEntryInGrid(triggers, 59484, 500.0f);

            if (triggers.empty())
                return;

            for (auto itr : triggers)
            {
                if (itr->GetAI())
                    itr->GetAI()->DoAction(action_reset);
            }

            me->RemoveAura(SPELL_CHARGE_DUMMY);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_NIUZAO_AGGRO);

            _events.ScheduleEvent(EVENT_HEADBUTT, 15 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_FORTITUDE, 40 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_MASSIVE_QUAKE, 30 * TimeConstants::IN_MILLISECONDS);
            _events.ScheduleEvent(EVENT_CHARGE_EXECUTE, 55000);
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
            case action_activate:
                intet++;
                break;
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->IsInWorld() && who->GetTypeId() == TYPEID_PLAYER && !intro && me->IsWithinDistInMap(who, 40.0f))
            {
                intro = true;

                Talk(SAY_NIUZAO_INTRO);
            }
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_NIUZAO_KILL);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_NIUZAO_DEATH);
            summons.DespawnAll();

            Quest const* quest = sObjectMgr->GetQuestTemplate(99996);

            if (!quest)
                return;

            std::list<Player*> pl_list;
            me->GetPlayerListInGrid(pl_list, 50.0f);

            if (pl_list.empty())
                return;

            for (auto itr : pl_list)
            {
                itr->AddQuest(quest, me);
                itr->CompleteQuest(99996);
                itr->RewardQuest(quest, 0, me, true);
                itr->SetWeeklyQuestStatus(99996);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (intet >= 4)
            {
                me->SetSpeed(MOVE_RUN, 1.12f);
                me->RemoveAura(SPELL_CHARGE_DUMMY);
                me->SetReactState(REACT_AGGRESSIVE);

                _events.ScheduleEvent(EVENT_HEADBUTT, 15 * TimeConstants::IN_MILLISECONDS);
                _events.ScheduleEvent(EVENT_FORTITUDE, 40 * TimeConstants::IN_MILLISECONDS);
                _events.ScheduleEvent(EVENT_MASSIVE_QUAKE, 30 * TimeConstants::IN_MILLISECONDS);

                me->RemoveAura(SPELL_CHARGE_DUMMY);

                _events.ScheduleEvent(EVENT_CHARGE_EXECUTE, 55000);

                events.ScheduleEvent(EVENT_CHARGE_DROP, 1);
                me->GetMotionMaster()->MoveCharge(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), 42.0f);
            }

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HEADBUTT:
                {
                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    if (Unit* victim = me->getVictim())
                    {
                        me->CastSpell(victim, SPELL_HEAD_BUTT, true);
                        //me->getHostileRefManager().deleteReference(victim);
                    }

                    events.ScheduleEvent(EVENT_HEADBUTT, 15000);
                    break;
                }
                case EVENT_FORTITUDE:
                {
                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;


                    me->CastSpell(me, 144606);

                    events.ScheduleEvent(EVENT_MASSIVE_QUAKE, 2000);
                    _events.ScheduleEvent(EVENT_FORTITUDE, 35 * TimeConstants::IN_MILLISECONDS);
                    break;
                }
                case EVENT_MASSIVE_QUAKE:
                {
                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        return;

                    me->CastSpell(me, SPELL_MASSIVE_QUAKE_AURA);
                    break;
                }
                case EVENT_CHARGE_EXECUTE:
                {
                    std::list<Creature*> triggers;
                    me->GetCreatureListWithEntryInGrid(triggers, 59484, 700.0f);

                    if (triggers.empty())
                        return;

                    for (auto itr : triggers)
                    {
                        if (itr->GetAI())
                            itr->GetAI()->DoAction(action_reset);
                    }

                    me->CastSpell(me, SPELL_CHARGE_DUMMY);

                    events.Reset();

                    me->SetSpeed(MOVE_RUN, 22.0f);

                    intet = 0;

                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MoveCharge(NiuzaoCharge[0].GetPositionX(), NiuzaoCharge[0].GetPositionY(), NiuzaoCharge[0].GetPositionZ(), 42.0f);
                    break;
                }
 
                default: break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_niuzaoAI(creature);
    }
};


void AddSC_boss_chi_ji()
{
    new boss_chi_ji();

    new spell_xeon_chu();
    new boss_xuen();

    new boss_yulon();
    new npc_yulon_wall();
    new npc_yulon_buffet();

    new boss_niuzao();
    new mob_trigger_niuzao_charge();
}
