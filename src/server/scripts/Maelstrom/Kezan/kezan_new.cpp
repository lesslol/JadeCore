#include "Vehicle.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "GameObjectAI.h"
#include "ScriptedFollowerAI.h"
#include "CreatureTextMgr.h"
#include "RandomMovementGenerator.h"

enum Quests
{
    QUEST_TROUBLE_IN_THE_MINES                  = 14075,
    QUEST_TAKING_CARE_OF_BUSINESS               = 14138,
    QUEST_KAJA_COLA                             = 25473,
    QUEST_MEGS_IN_MARKETING                     = 28349,
    QUEST_DO_IT_YOURSELF                        = 14070,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND             = 14069,
    QUEST_ROLLING_WITH_MY_HOMIES                = 14071,
    QUEST_THE_REPLACEMENTS                      = 24488,
    QUEST_NECESSARY_ROUGHNESS                   = 24502,
    QUEST_FOURTH_AND_GOAL                       = 28414,
    QUEST_OFF_TO_THE_BANK_FEMALE                = 26711,
    QUEST_OFF_TO_THE_BANK_MALE                  = 26712,
    QUEST_THE_NEW_YOU_FEMALE                    = 14110,
    QUEST_THE_NEW_YOU_MALE                      = 14109,
    QUEST_LIFE_OF_THE_PARTY_MALE                = 14113,
    QUEST_LIFE_OF_THE_PARTY_FEMALE              = 14153,
    QUEST_PIRATE_PARTY_CRASHERS                 = 14115,
    QUEST_THE_UNINVITED_GUEST                   = 14116,
    QUEST_A_BAZILLION_MACAROONS                 = 14120,
    QUEST_ROBBING_HOODS                         = 14121,
    QUEST_THE_GREAT_BANK_HEIST                  = 14122,
    QUEST_WALTZ_RIGHT_IN                        = 14123,
    QUEST_LIBERATE_THE_KAJAMITE                 = 14124,
    QUEST_STEADY_SHOT                           = 14007,
    QUEST_ARCANE_MISSILES                       = 14008,
    QUEST_FLASH_HEAL                            = 14009,
    QUEST_EVISCERATE                            = 14010,
    QUEST_PRIMAL_STRIKE                         = 14011,
    QUEST_IMMOLATE                              = 14012,
    QUEST_CHARGE                                = 14013,
    QUEST_447                                   = 14125,
    QUEST_LIFE_SAVINGS                          = 14126,
    QUEST_DONT_GO_INTO_THE_LIGHT                = 14239,
};

enum QuestObjectives
{
    QUEST_OBJECTIVE_IZZY_PICKED_UP              = 265516,
    QUEST_OBJECTIVE_BRUNO_BEATEN_DOWN           = 265427,
    QUEST_OBJECTIVE_OVERLOAD_DEFECTIVE_GEN      = 266731,
};

enum Spells
{
    SPELL_QUEST_INVISIBILITY_DETECTION_1        = 60922,
    SPELL_QUEST_INVISIBILITY_DETECTION_2        = 49417,
    SPELL_QUEST_INVISIBILITY_DETECTION_3        = 49416,
    SPELL_QUEST_INVISIBILITY_DETECTION_4        = 80818,
    SPELL_QUEST_INVISIBILITY_DETECTION_5        = 94566,
    SPELL_QUEST_INVISIBILITY_DETECTION_6        = 81010,
    SPELL_QUEST_INVISIBILITY_DETECTION_7        = 81019,
    PHASE_QUEST_ZONE_SPECIFIC_1                 = 59073,
    PHASE_QUEST_ZONE_SPECIFIC_2                 = 59074,
    PHASE_QUEST_ZONE_SPECIFIC_3                 = 59087,
    PHASE_QUEST_ZONE_SPECIFIC_4                 = 67789,
    PHASE_QUEST_ZONE_SPECIFIC_5                 = 68480,
    PHASE_QUEST_ZONE_SPECIFIC_6                 = 68481,
    PHASE_QUEST_ZONE_SPECIFIC_7                 = 68482,
    PHASE_QUEST_ZONE_SPECIFIC_8                 = 68483,
    // Life of the Part spells
    SPELL_AWESOME_PARTY_ENSEMBLE                = 66908,
    SPELL_LOTP_OUTFIT_SECONDARY                 = 66985,
    SPELL_LOTP_OUTFIT_FEMALE                    = 66927,
    SPELL_LOTP_OUTFIT_MALE                      = 66928,
    SPELL_LOTP_PAPARAZZI                        = 66929,

    SPELL_KEYS_TO_THE_HOT_ROD                   = 91551,
};

enum Shared
{
    ACTION_QUEST_PROGRESS                       = -1,

    NPC_HOT_ROD                                 = 34840,
    NPC_ACE                                     = 34957,
    NPC_GOBBER                                  = 34958,
    NPC_IZZY                                    = 34959,
    NPC_INVIS_ACE                               = 34892,
    NPC_INVIS_GOBBER                            = 34954,
    NPC_INVIS_IZZY                              = 34890,
    NPC_HOTROD_KILL_CREDIT                      = 48323,
    NPC_KEZAN_CITIZEN                           = 35063,

    ITEM_NEW_OUTFIT                             = 47046,
    ITEM_COOL_SHADES                            = 47047,
    ITEM_SHINY_BLING                            = 47045,

    MOOK_EVENT_ID                               = 1067435,
};

static const uint32 SummonHomieSpellEntry[3]=
{
    66644,
    66645,
    66646,
};

enum HomiesMask
{
    HOMIES_NULL         = 0x0,
    HOMIE_ACE           = 0x1,
    HOMIE_GOBBER        = 0x2,
    HOMIE_IZZY          = 0x4,
    HOMIES_NOT_ALLOWED  = 0x8,
    HOMIES_FULL         = HOMIE_ACE | HOMIE_GOBBER | HOMIE_IZZY,
};

const uint8 HomiesType[3]=
{
    HOMIE_ACE,
    HOMIE_GOBBER,
    HOMIE_IZZY,
};

enum MarkMask
{
    MARK_MASK_BRUNO     = 1 << 2,
    MARK_MASK_FRANKIE   = 1 << 3,
    MARK_MASK_JACK      = 1 << 1,
    MARK_MASK_SUDSY     = 1 << 0,

    MARK_MASK_GAPPY     = 1 << 2,
    MARK_MASK_SZABO     = 1 << 3,
    MARK_MASK_MISSA     = 1 << 0,

    MARK_MASK_FULL      = MARK_MASK_BRUNO | MARK_MASK_FRANKIE | MARK_MASK_JACK | MARK_MASK_SUDSY,
};

namespace Kezan
{
    uint8 const GetHomiesStatus(Player* player)
    {
        switch (player->getGender())
        {
            case GENDER_MALE:
                {
                    if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_MALE) == QUEST_STATUS_INCOMPLETE ||
                        player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_MALE) == QUEST_STATUS_COMPLETE)
                        return HOMIES_NOT_ALLOWED;

                    RewardedQuestSet::const_iterator complete_quest_life;
                    complete_quest_life = player->getRewardedQuests().find(QUEST_LIFE_OF_THE_PARTY_MALE);

                    if (complete_quest_life != player->getRewardedQuests().end())
                        return HOMIES_NOT_ALLOWED;
                }
                break;
            case GENDER_FEMALE:
                {
                    if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_FEMALE) == QUEST_STATUS_INCOMPLETE ||
                        player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_FEMALE) == QUEST_STATUS_COMPLETE)
                        return HOMIES_NOT_ALLOWED;

                    RewardedQuestSet::const_iterator complete_quest_life;
                    complete_quest_life = player->getRewardedQuests().find(QUEST_LIFE_OF_THE_PARTY_FEMALE);

                    if (complete_quest_life != player->getRewardedQuests().end())
                        return HOMIES_NOT_ALLOWED;
                }
                break;
        }

        if (player->IsQuestRewarded(QUEST_ROLLING_WITH_MY_HOMIES))
            return HOMIES_FULL;

        QuestStatusMap::iterator itr = player->getQuestStatusMap().find(QUEST_ROLLING_WITH_MY_HOMIES);

        if (itr == player->getQuestStatusMap().end())
            return HOMIES_NOT_ALLOWED;

        uint8 homiesMask = HOMIES_NULL;
        QuestStatusData& questStatus = itr->second;

        if (questStatus.Status == QUEST_STATUS_COMPLETE)
            return HOMIES_FULL;

        if (questStatus.Status == QUEST_STATUS_INCOMPLETE)
            for (uint8 index = 0; index < 3; ++index)
                if (player->GetQuestObjectiveCounter(QUEST_OBJECTIVE_IZZY_PICKED_UP + index))
                    homiesMask |= HomiesType[index];

        return homiesMask;
    }

    class CreatureEntryAndSummonerGuidCheck
    {
        public:
            CreatureEntryAndSummonerGuidCheck(WorldObject const& obj, uint32 entry, float range)
                : i_obj(obj)
                , i_entry(entry)
                , i_range(range)
            { }

            bool operator()(Creature* u)
            {
                if (u->GetEntry() == i_entry &&
                    u->IsSummon() &&
                    u->ToTempSummon()->GetSummonerGUID() == i_obj.GetGUID() &&
                    i_obj.IsWithinDistInMap(u, i_range))
                {
                    i_range = i_obj.GetDistance(u); // use found unit range as new range limit for next check
                    return true;
                }

                return false;
            }

            float GetLastRange() const { return i_range; }

        private:
            WorldObject const& i_obj;
            float  i_range;
            uint32 i_entry;

            // prevent clone this object
            CreatureEntryAndSummonerGuidCheck(CreatureEntryAndSummonerGuidCheck const&);
    };

    Creature* GetHomie(Player* player, uint32 entry, float dist)
    {
        Creature* target = NULL;
        CreatureEntryAndSummonerGuidCheck checker(*player, entry, dist);
        Trinity::CreatureLastSearcher<CreatureEntryAndSummonerGuidCheck> searcher(player, target, checker);
        Trinity::VisitNearbyGridObject(player, dist, searcher);
        return target;
    }

    class PersonalPlayerUpdateMookEvent : public BasicEvent
    {
        public:
            PersonalPlayerUpdateMookEvent(Player* player)
                : m_player(player)
            { }

        private:
            bool Execute(uint64 /*time*/, uint32 /*diff*/)
            {
                if (m_player->GetAreaId() != 4768)
                    return true;

                if (m_player->IsInCombat())
                {
                    m_player->m_Events.AddEvent(new PersonalPlayerUpdateMookEvent(m_player), m_player->m_Events.CalculateTime(1000), true, MOOK_EVENT_ID);
                    return true;
                }

                if (m_player->GetQuestStatus(14123) == QUEST_STATUS_INCOMPLETE || m_player->GetQuestStatus(14123) == QUEST_STATUS_COMPLETE)
                {
                    if (!m_player->HasAura(67435))
                    {
                        m_player->CastSpell(m_player, 67435, false);

                        if (m_player->IsVehicle())
                        {
                            float x, y, z, o;
                            m_player->GetPosition(x, y, z, o);

                            if (Creature* mook = m_player->SummonCreature(48925, x, y, z, o))
                                mook->EnterVehicle(m_player, 0);
                        }
                    }
                }

                return true;
            }

            Player* m_player;
    };
};

class zone_kezan : public WorldMapScript
{
    public:
        zone_kezan() : WorldMapScript("zone_kezan", 648) { }

    private:
        class InitAfterLoadEvent : public BasicEvent
        {
            public:
                InitAfterLoadEvent(Player* player)
                    : m_player(player)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/)
                {
                    PhaseShiftSet phaseIds;
                    PhaseShiftSet terrainswaps;
                    PhaseShiftSet worldMapAreaIds;

                    phaseIds.insert(378);
                    m_player->GetSession()->SendSetPhaseShift(phaseIds, terrainswaps, worldMapAreaIds);

                    if (m_player->HasAura(66392))
                        m_player->CastSpell(m_player, 66393, false);

                    const uint8 homiesMask = Kezan::GetHomiesStatus(m_player);

                    for (uint8 index = 0; index < 3; ++index)
                        if (homiesMask & HomiesType[index])
                            m_player->CastSpell(m_player, SummonHomieSpellEntry[index], false);

                    if (m_player->HasAura(69010))
                    {
                        m_player->CastSpell(m_player, 69283, false);
                        m_player->CastSpell((Unit*)NULL, 69043, false);
                        m_player->CastSpell((Unit*)NULL, 69018, false);
                    }

                    return true;
                }

                Player* m_player;
        };

        void OnPlayerEnter(Map* /*map*/, Player* player)
        {
            player->m_Events.AddEvent(new InitAfterLoadEvent(player), player->m_Events.CalculateTime(250));
        }

        void OnPlayerEnterArea(Map* /*map*/, Player* player, uint32 oldArea, uint32 newArea)
        {
            if (oldArea == newArea)
                return;

            if (oldArea == 4773 || oldArea == 4771)
                //player->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, MARK_MASK_FULL);

            if (newArea == 4773)
            {
                if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_INCOMPLETE ||
                    player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_INCOMPLETE))
                {
                    static const uint8 MarkMask[3]=
                    {
                        MARK_MASK_GAPPY,
                        MARK_MASK_SZABO,
                        MARK_MASK_MISSA,
                    };

                    uint8 markMask = 0;

                    if (!player->HasItemCount(ITEM_COOL_SHADES, 1))
                        markMask |= MARK_MASK_MISSA;

                    if (!player->HasItemCount(ITEM_SHINY_BLING, 1))
                        markMask |= MARK_MASK_GAPPY;

                    if (!player->HasItemCount(ITEM_NEW_OUTFIT, 1))
                        markMask |= MARK_MASK_SZABO;

                    //player->SetByteFlag(PLAYER_FIELD_BYTES2, 3, markMask);
                }
            }

            if (newArea == 4771)
            {
                if (player->IsQuestRewarded(QUEST_DO_IT_YOURSELF))
                    return;

                QuestStatusMap::iterator itr = player->getQuestStatusMap().find(QUEST_DO_IT_YOURSELF);

                if (itr == player->getQuestStatusMap().end())
                    return;

                QuestStatusData& questStatus = itr->second;

                if (questStatus.Status == QUEST_STATUS_COMPLETE)
                    return;

                if (questStatus.Status == QUEST_STATUS_INCOMPLETE)
                {
                    static const uint8 MarkMask[4]=
                    {
                        MARK_MASK_BRUNO,
                        MARK_MASK_FRANKIE,
                        MARK_MASK_JACK,
                        MARK_MASK_SUDSY,
                    };

                    uint8 markMask = 0;

                    for (uint8 index = 0; index < 4; ++index)
                        if (player->GetQuestObjectiveCounter(QUEST_OBJECTIVE_BRUNO_BEATEN_DOWN + index) == 0)
                            markMask |= MarkMask[index];

                    //player->SetByteFlag(PLAYER_FIELD_BYTES2, 3, markMask);
                }
            }

            if (newArea == 4768)
            {
                if (player->GetQuestStatus(14123) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(14123) == QUEST_STATUS_COMPLETE)
                {
                    if (!player->HasAura(67435))
                    {
                        player->CastSpell(player, 67435, false);

                        if (player->IsVehicle())
                        {
                            float x, y, z, o;
                            player->GetPosition(x, y, z, o);

                            if (Creature* mook = player->SummonCreature(48925, x, y, z, o))
                                mook->EnterVehicle(player, 0);
                        }
                    }
                }
            }

            if (oldArea == 4768)
            {
                player->RemoveAura(67435);
                player->m_Events.DeleteEventId(MOOK_EVENT_ID);
            }
        }
};

// Taking Care of Business 14138 & Kaja'Cola 25473 & Megs in Marketing 28349
#define    GOSSIP_GO_TO_THE_BOAT    "Okay, Sassy, I'm ready to go."

class npc_kezan_sassy_sardwrench : public CreatureScript
{
    public:
        npc_kezan_sassy_sardwrench() : CreatureScript("npc_kezan_sassy_sardwrench") { }

    private:
        enum talks
        {
            SASSY_SAY_TAKING_CARE_OF_BUSINESS   = 0,
            SASSY_SAY_MORE_LATER                = 1,
            SASSY_DO_IT_YOURSELF                = 2,
            SASSY_SAY_PIRATE_PARTY_CRASHERS     = 3,
            SASSY_SAY_UNINVITED_GUEST           = 4,
            SASSY_SAY_THE_GREAT_BANK_HEIST      = 5,
            SASSY_SAY_447                       = 6,
            SASSY_SAY_LIFE_SAVINGS              = 7,

            GOSSIP_ACTION_LIFE_SAVINGS          = 1001,
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            uint32 gossipId = 14590;

            if ((player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_MALE) == QUEST_STATUS_INCOMPLETE) &&
                player->GetQuestStatus(QUEST_PIRATE_PARTY_CRASHERS) == QUEST_STATUS_NONE)
                gossipId = 17572;

            if ((player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_FEMALE) == QUEST_STATUS_INCOMPLETE) &&
                player->GetQuestStatus(QUEST_PIRATE_PARTY_CRASHERS) == QUEST_STATUS_NONE)
                gossipId = 17572;

            if ((player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_MALE) == QUEST_STATUS_COMPLETE) &&
                player->GetQuestStatus(QUEST_PIRATE_PARTY_CRASHERS) & (QUEST_STATUS_NONE | QUEST_STATUS_INCOMPLETE))
                gossipId = 17573;

            if ((player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_FEMALE) == QUEST_STATUS_COMPLETE) &&
                player->GetQuestStatus(QUEST_PIRATE_PARTY_CRASHERS) & (QUEST_STATUS_NONE | QUEST_STATUS_INCOMPLETE))
                gossipId = 17573;

            if ((player->GetQuestStatus(QUEST_PIRATE_PARTY_CRASHERS) == QUEST_STATUS_COMPLETE) &&
                player->GetQuestStatus(QUEST_A_BAZILLION_MACAROONS) == QUEST_STATUS_NONE)
                gossipId = 17574;

            if (player->GetQuestStatus(QUEST_A_BAZILLION_MACAROONS) & (QUEST_STATUS_COMPLETE | QUEST_STATUS_INCOMPLETE))
                gossipId = 17575;

            if (player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_COMPLETE &&
                player->GetQuestStatus(QUEST_THE_GREAT_BANK_HEIST) == QUEST_STATUS_COMPLETE &&
                player->GetQuestStatus(QUEST_WALTZ_RIGHT_IN) == QUEST_STATUS_COMPLETE &&
                player->GetQuestStatus(QUEST_LIBERATE_THE_KAJAMITE) == QUEST_STATUS_COMPLETE)
                gossipId = 17576;

            if (player->GetQuestStatus(QUEST_LIFE_SAVINGS) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GO_TO_THE_BOAT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_LIFE_SAVINGS);

            player->PrepareQuestMenu(creature->GetGUID());
            player->SEND_GOSSIP_MENU(gossipId, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_LIFE_SAVINGS)
            {
                player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_5);
                player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_8, false);
                player->CastSpell(player, 70318, false);
                player->SaveToDB();
                creature->CastSpell(player, 70319, false, NULL, NULL, player->GetGUID());
            }

            return true;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_KAJA_COLA:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_MORE_LATER, player->GetGUID(), true);
                    }
                    break;
                case QUEST_LIFE_OF_THE_PARTY_MALE:
                case QUEST_LIFE_OF_THE_PARTY_FEMALE:
                    player->RemoveAura(SPELL_AWESOME_PARTY_ENSEMBLE);
                    player->RemoveAura(SPELL_LOTP_OUTFIT_SECONDARY);
                    player->RemoveAura(SPELL_LOTP_OUTFIT_FEMALE);
                    player->RemoveAura(SPELL_LOTP_OUTFIT_MALE);
                    player->RemoveAura(SPELL_LOTP_PAPARAZZI);
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_1);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_2, false);
                    player->SaveToDB();
                    break;
                case QUEST_PIRATE_PARTY_CRASHERS:
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_2);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_3, false);
                    player->SaveToDB();
                    break;
                case QUEST_A_BAZILLION_MACAROONS:
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_4);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_5, false);
                    player->SaveToDB();
                    break;
                case QUEST_THE_GREAT_BANK_HEIST:
                    {
                        if (player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_REWARDED &&
                            player->GetQuestStatus(QUEST_WALTZ_RIGHT_IN) == QUEST_STATUS_REWARDED &&
                            player->GetQuestStatus(QUEST_LIBERATE_THE_KAJAMITE) == QUEST_STATUS_REWARDED)
                        {
                            player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_5);
                            player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_6, false);
                            player->SaveToDB();
                        }
                    }
                    break;
            }

            return true;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_TAKING_CARE_OF_BUSINESS:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_TAKING_CARE_OF_BUSINESS, player->GetGUID(), true);
                    }
                    break;
                case QUEST_DO_IT_YOURSELF:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_DO_IT_YOURSELF, player->GetGUID(), true);
                    }
                    break;
                case QUEST_PIRATE_PARTY_CRASHERS:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_PIRATE_PARTY_CRASHERS, player->GetGUID(), true);
                    }
                    break;
                case QUEST_THE_UNINVITED_GUEST:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_UNINVITED_GUEST, player->GetGUID(), true);
                    }
                    break;
                case QUEST_THE_GREAT_BANK_HEIST:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_THE_GREAT_BANK_HEIST, player->GetGUID(), true);
                    }
                    break;
                case QUEST_447:
                    {
                        if (player->GetPhaseMask() == 8192)
                            player->CompleteQuest(QUEST_447);
                        else if (creature->IsAIEnabled)
                            creature->AI()->Talk(SASSY_SAY_447, player->GetGUID(), true);
                    }
                    break;
                case QUEST_LIFE_SAVINGS:
                    {
                        if (creature->IsAIEnabled && player->GetPhaseMask() == 8192)
                            creature->AI()->Talk(SASSY_SAY_LIFE_SAVINGS, player->GetGUID(), true);
                    }
                    break;
            }

            return true;
        }
};

class npc_kezan_life_savings_hot_rod : public CreatureScript
{
    public:
        npc_kezan_life_savings_hot_rod() : CreatureScript("npc_kezan_life_savings_hot_rod") { }

    private:
        class PartnerTalkEvent : public BasicEvent
        {
            public:
                PartnerTalkEvent(uint64 partnerGUID, uint64 playerGUID)
                    : m_partnerGUID(partnerGUID)
                    , m_playerGUID(playerGUID)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/)
                {
                    enum
                    {
                        PARTNER_SAY_BREAK = 3,
                    };

                    Creature* partner = ObjectAccessor::GetObjectInWorld(m_partnerGUID, (Creature*)NULL);

                    if (partner && partner->IsAIEnabled)
                        partner->AI()->Talk(PARTNER_SAY_BREAK, m_playerGUID, true);

                    return true;
                }

                uint64 m_playerGUID;
                uint64 m_partnerGUID;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_MOVEMENT    = 1,
                EVENT_SAY_OTHER_WAY     = 2,
                EVENT_CONTINUE_MOVEMENT = 3,
                EVENT_SAY_GET_OUT       = 4,
                EVENT_JUMP              = 5,
                EVENT_SKID              = 6,

                SAY_OTHER_WAY           = 1,
                SAY_GET_OUT             = 2,
                SAY_OH_NO               = 3,

                NPC_CHIP_ENDALE         = 35054,
                NPC_CANDY_CANE          = 35053,
            };

            EventMap events;
            uint64 sassyGUID;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                Reset();
            }

            void Reset()
            {
                events.Reset();
                sassyGUID = 0;
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (Creature* sassy = me->SummonCreature(37680, *me))
                {
                    sassyGUID = sassy->GetGUID();
                    sassy->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                    sassy->EnterVehicle(me, 0);
                    events.ScheduleEvent(EVENT_START_MOVEMENT, 1000);
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (!apply && seatId == 0)
                    if (Creature* sassy = who->ToCreature())
                        sassy->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_MOVEMENT:
                            me->CastSpell(me, 70329, false);
                            me->GetMotionMaster()->MoveSplinePath(1, false, false, 20.f);
                            events.ScheduleEvent(EVENT_SAY_OTHER_WAY, me->GetSplineDuration());
                            break;
                        case EVENT_SAY_OTHER_WAY:
                            {
                                if (Creature* sassy = ObjectAccessor::GetCreature(*me, sassyGUID))
                                    if (sassy->IsAIEnabled)
                                        sassy->AI()->Talk(SAY_OTHER_WAY, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_CONTINUE_MOVEMENT, 1000);
                            }
                            break;
                        case EVENT_CONTINUE_MOVEMENT:
                            me->GetMotionMaster()->MoveSplinePath(2, false, false, 20.f);
                            events.ScheduleEvent(EVENT_SAY_GET_OUT, 1000);
                            events.ScheduleEvent(EVENT_JUMP, me->GetSplineDuration());
                            break;
                        case EVENT_SAY_GET_OUT:
                            {
                                if (Creature* sassy = ObjectAccessor::GetCreature(*me, sassyGUID))
                                    if (sassy->IsAIEnabled)
                                        sassy->AI()->Talk(SAY_GET_OUT, me->ToTempSummon()->GetSummonerGUID(), true);
                            }
                            break;
                        case EVENT_JUMP:
                            me->GetMotionMaster()->MoveJump(-7849.337f, 1841.155f, 7.607844f, 20.f, 20.f);
                            events.ScheduleEvent(EVENT_SKID, me->GetSplineDuration());
                            break;
                        case EVENT_SKID:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    if (Player* player = summoner->ToPlayer())
                                    {
                                        player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_7);
                                        player->CompleteQuest(QUEST_LIFE_SAVINGS);
                                        player->SaveToDB();

                                        if (Creature* sassy = ObjectAccessor::GetCreature(*me, sassyGUID))
                                            if (sassy->IsAIEnabled)
                                                sassy->AI()->Talk(SAY_OH_NO, player->GetGUID(), true);

                                        if (Creature* partner = me->FindNearestCreature(player->getGender() == GENDER_MALE ? NPC_CANDY_CANE : NPC_CHIP_ENDALE, 30.f))
                                            player->m_Events.AddEvent(new PartnerTalkEvent(partner->GetGUID(), player->GetGUID()), player->m_Events.CalculateTime(1000));
                                    }
                                }

                                me->CastSpell(me, 70325, false);
                                me->DespawnOrUnsummon(1000);
                            }
                            break;
                    }
                }
            }
        };
};

class spell_kezan_life_savings_hand_over_the_keys : public SpellScriptLoader
{
    public:
        spell_kezan_life_savings_hand_over_the_keys() : SpellScriptLoader("spell_kezan_life_savings_hand_over_the_keys") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    player->DestroyItemCount(46856, 1, true);
                    player->RemoveAura(91551);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class go_kezan_ls_rope_ladder : public GameObjectScript
{
    public:
        go_kezan_ls_rope_ladder() : GameObjectScript("go_kezan_ls_rope_ladder"){ }

    private:
        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            player->TeleportTo(648, -7864.02f, 1831.4f, -0.956502f, 6.12391f);
            player->GetMotionMaster()->MoveJump(-7861.84f, 1831.27f, 8.53755f, 5.0f, 15.0f);
            player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_7);
            player->CompleteQuest(QUEST_LIFE_SAVINGS);
            return true;
        }
};

class go_kezan_yacht_boarding_mortar : public GameObjectScript
{
    public:
        go_kezan_yacht_boarding_mortar() : GameObjectScript("go_kezan_yacht_boarding_mortar"){ }

    private:
        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            player->TeleportTo(648, -7879.2f, 1828.67f, 5.55337f, 0.251894f);
            player->CastSpell(player, 92633, false);
            player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_7);
            player->CompleteQuest(QUEST_LIFE_SAVINGS);
            return true;
        }
};

class npc_kezan_socialite : public CreatureScript
{
    public:
        npc_kezan_socialite() : CreatureScript("npc_kezan_socialite") { }

    private:
        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->HasAura(67435))
            {
                player->SEND_GOSSIP_MENU(17550, creature->GetGUID());
                return true;
            }

            return false;
        }
};

class npc_kezan_foreman_dampwick : public CreatureScript
{
    public:
        npc_kezan_foreman_dampwick() : CreatureScript("npc_kezan_foreman_dampwick") { }

    private:
        enum
        {
            SAY_GIFT                = 1,
            SAY_OUCH                = 2,
            SAY_OKAY                = 3,
            SAY_BOSS                = 4,

            EVENT_TALK_GIFT         = 1,
            EVENT_TALK_OUCH         = 2,
            EVENT_TALK_OKAY         = 3,
            EVENT_RAND_YELL         = 1,
            YELL_ON_TROLLS          = 6,

            AREA_KAJAMITE_MINE      = 4766,

            SPELL_SASSYS_INCENTIVE  = 82025,
        };

        class PersonalPlayerEvent : public BasicEvent
        {
            public:
                PersonalPlayerEvent(Player* player, Creature* creature, uint8 eventId)
                    : m_creature(creature)
                    , m_player(player)
                    , m_eventId(eventId)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/)
                {
                    switch (m_eventId)
                    {
                        case EVENT_TALK_GIFT:
                            {
                                if (m_player && m_creature && m_player->GetExactDist2dSq(m_creature) < 2500.f && m_creature->IsAIEnabled)
                                    m_creature->AI()->Talk(SAY_GIFT, m_player->GetGUID(), true);

                                m_creature->m_Events.AddEvent(new PersonalPlayerEvent(m_player, m_creature, EVENT_TALK_OUCH), m_creature->m_Events.CalculateTime(1000));
                            }
                            break;
                        case EVENT_TALK_OUCH:
                            {
                                if (m_player && m_creature && m_player->GetExactDist2dSq(m_creature) < 2500.f && m_creature->IsAIEnabled)
                                {
                                    m_creature->AI()->Talk(SAY_OUCH, m_player->GetGUID(), true);
                                    m_creature->CastSpell(m_creature, SPELL_SASSYS_INCENTIVE, false);
                                }

                                m_creature->m_Events.AddEvent(new PersonalPlayerEvent(m_player, m_creature, EVENT_TALK_OKAY), m_creature->m_Events.CalculateTime(3000));
                            }
                            break;
                        case EVENT_TALK_OKAY:
                            {
                                if (m_player && m_creature && m_player->GetExactDist2dSq(m_creature) < 2500.f && m_creature->IsAIEnabled)
                                    m_creature->AI()->Talk(SAY_OKAY, m_player->GetGUID(), true);
                            }
                            break;
                    }

                    return true;
                }

                Creature* m_creature;
                Player* m_player;
                uint8 m_eventId;
        };

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
                creature->m_Events.AddEvent(new PersonalPlayerEvent(player, creature, EVENT_TALK_GIFT), creature->m_Events.CalculateTime(250));

            if (quest->GetQuestId() == QUEST_LIBERATE_THE_KAJAMITE)
            {
                if (player->GetQuestStatus(QUEST_THE_GREAT_BANK_HEIST) == QUEST_STATUS_REWARDED &&
                    player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_REWARDED &&
                    player->GetQuestStatus(QUEST_WALTZ_RIGHT_IN) == QUEST_STATUS_REWARDED)
                {
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_5);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_6, false);
                    player->SaveToDB();
                }
            }

            return true;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_KAJA_COLA)
                creature->AI()->Talk(SAY_BOSS, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            uint32 gossipId = 14684;

            if (player->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_COMPLETE &&
                player->GetQuestStatus(QUEST_TROUBLE_IN_THE_MINES) == QUEST_STATUS_COMPLETE)
                gossipId = 14731;

            if (player->GetQuestStatus(QUEST_THE_UNINVITED_GUEST) & (QUEST_STATUS_COMPLETE | QUEST_STATUS_INCOMPLETE))
                gossipId = 14762;

            player->PrepareQuestMenu(creature->GetGUID());
            player->SEND_GOSSIP_MENU(gossipId, creature->GetGUID());
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                if (me->GetPhaseMask() == 1)
                {
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_RAND_YELL, urand(5000, 10000));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RAND_YELL)
                {
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();

                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                            if (player->GetPhaseMask() == 1 && player->GetAreaId() == AREA_KAJAMITE_MINE)
                                Talk(YELL_ON_TROLLS, player->GetGUID(), true);

                    events.ScheduleEvent(EVENT_RAND_YELL, 30000, 60000);
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class go_kezan_active_object : public GameObjectScript
{
    public:
        go_kezan_active_object() : GameObjectScript("go_kezan_active_object") { }

    private:
        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new gameobject_script_impl(go);
        }

        struct gameobject_script_impl : public GameObjectAI
        {
            gameobject_script_impl(GameObject* go) : GameObjectAI(go) { }

            void InitializeAI() override
            {
                go->setActive(true);
            }
        };
};

// Quest Good Help is Hard to Find 14069
class spell_kezan_goblin_all_in_1_der_belt_shocker : public SpellScriptLoader
{
    public:
        spell_kezan_goblin_all_in_1_der_belt_shocker() : SpellScriptLoader("spell_kezan_goblin_all_in_1_der_belt_shocker") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex /*effIndex*/)
            {
                enum
                {
                    SAY_TAZER       = 1,
                };

                if (Creature* target = GetHitCreature())
                {
                    if (target->IsAIEnabled)
                        target->AI()->Talk(SAY_TAZER);

                    target->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    target->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                    target->RemoveAllAuras();
                    target->DespawnOrUnsummon(5000);
                }

                if (Player * const player = GetCaster()->ToPlayer())
                    player->KilledMonsterCredit(34830);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

// Class quests and trainers
class at_kezan_ktc : public AreaTriggerScript
{
    public:
        at_kezan_ktc() : AreaTriggerScript("at_kezan_ktc") { }

    private:
        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            enum
            {
                SPELL_POWER_WORD_FORTITUDE  = 74973,
                NPC_SISTER_GOLDSKIMMER      = 34692,

                TALK_POWER_WORD_FORTITUDE   = 1,
            };

            if (!(player->GetPhaseMask() & 4 || player->HasAura(SPELL_POWER_WORD_FORTITUDE)))
            {
                if (Creature* sister = player->FindNearestCreature(NPC_SISTER_GOLDSKIMMER, 50.f))
                {
                    sister->CastSpell(player, SPELL_POWER_WORD_FORTITUDE, true);

                    if (sister->IsAIEnabled)
                        sister->AI()->Talk(TALK_POWER_WORD_FORTITUDE, player->GetGUID(), true);
                }
            }

            return true;
        }
};

class npc_kezan_sister_goldskimmer : public CreatureScript
{
    public:
        npc_kezan_sister_goldskimmer() : CreatureScript("npc_kezan_sister_goldskimmer") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            enum
            {
                SISTER_GOLDSKIMMER_QUEST_ACCEPT = 0,
            };

            if (quest->GetQuestId() == QUEST_FLASH_HEAL)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SISTER_GOLDSKIMMER_QUEST_ACCEPT, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_PRIEST)
            {
                player->SEND_GOSSIP_MENU(14601, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14602, creature->GetGUID());
            return false;
        }
};

class npc_kezan_maxx_avalanche : public CreatureScript
{
    public:
        npc_kezan_maxx_avalanche() : CreatureScript("npc_kezan_maxx_avalanche") { }

    private:
        enum
        {
            EVENT_LBOLT_FOR_FIZZ            = 1,
            EVENT_LBOLT_FOR_EVOL            = 2,
            EVENT_TALK_IDIOTS               = 3,

            SAY_PRIMAL_STRIKE               = 0,
            SAY_IDIOTS                      = 1,

            SPELL_LIGHTNING_BOLT_FOR_FIZZ   = 69630,
            SPELL_LIGHTNING_BOLT_FOR_EVOL   = 69626,

            NPC_FIZZ_LIGHTER                = 34689,
            NPC_EVOL_FINGERS                = 34696,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_PRIMAL_STRIKE)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_PRIMAL_STRIKE, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_SHAMAN)
            {
                player->SEND_GOSSIP_MENU(14807, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14808, creature->GetGUID());
            return false;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                if (!(me->GetPhaseMask() & 16388))
                {
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_LBOLT_FOR_FIZZ, urand(5000, 10000));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LBOLT_FOR_FIZZ:
                            {
                                if (Creature* target = me->FindNearestCreature(NPC_FIZZ_LIGHTER, 30.f))
                                    me->CastSpell(target, SPELL_LIGHTNING_BOLT_FOR_FIZZ, false);

                                events.ScheduleEvent(EVENT_LBOLT_FOR_EVOL, 2000);
                            }
                            break;
                        case EVENT_LBOLT_FOR_EVOL:
                            {
                                if (Creature* target = me->FindNearestCreature(NPC_EVOL_FINGERS, 30.f))
                                    me->CastSpell(target, SPELL_LIGHTNING_BOLT_FOR_EVOL, false);

                                events.ScheduleEvent(EVENT_TALK_IDIOTS, 2000);
                            }
                            break;
                        case EVENT_TALK_IDIOTS:
                            Talk(SAY_IDIOTS);
                            me->ModifyPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                            events.ScheduleEvent(EVENT_LBOLT_FOR_FIZZ, urand(25000, 50000));
                            break;
                    }
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_fizz_lighter : public CreatureScript
{
    public:
        npc_kezan_fizz_lighter() : CreatureScript("npc_kezan_fizz_lighter") { }

    private:
        enum
        {
            SAY_ARCANE_MISSILES = 0,

            EVENT_FIREBALL      = 1,

            SPELL_FIREBALL      = 45595,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ARCANE_MISSILES)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_ARCANE_MISSILES, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_MAGE)
            {
                player->SEND_GOSSIP_MENU(14805, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14806, creature->GetGUID());
            return false;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                SetCombatMovement(false);

                if (!(me->GetPhaseMask() & 16388))
                {
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_FIREBALL, urand(500, 2500));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    me->CastSpell((Unit*)NULL, SPELL_FIREBALL, false);
                    events.ScheduleEvent(EVENT_FIREBALL, 3000);
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_evol_fingers : public CreatureScript
{
    public:
        npc_kezan_evol_fingers() : CreatureScript("npc_kezan_evol_fingers") { }

    private:
        enum
        {
            SAY_IMMOLATE        = 0,

            EVENT_SHADOW_BOLT   = 1,

            SPELL_SHADOW_BOLT   = 33335,
            NPC_FIZZ_LIGHTER    = 34689,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_IMMOLATE)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_IMMOLATE, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_WARLOCK)
            {
                player->SEND_GOSSIP_MENU(14595, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14596, creature->GetGUID());
            return false;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                SetCombatMovement(false);

                if (!(me->GetPhaseMask() & 16388))
                {
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(500, 2500));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    if (Creature* target = me->FindNearestCreature(NPC_FIZZ_LIGHTER, 40.f))
                        me->CastSpell(target, SPELL_SHADOW_BOLT, false);

                    events.ScheduleEvent(EVENT_SHADOW_BOLT, 3000);
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_bamm_megabomb : public CreatureScript
{
    public:
        npc_kezan_bamm_megabomb() : CreatureScript("npc_kezan_bamm_megabomb") { }

    private:
        enum
        {
            SAY_STEADY_SHOT = 0,

            EVENT_SHOOT_GUN = 1,

            SPELL_SHOOT_GUN = 65977,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_STEADY_SHOT)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_STEADY_SHOT, player->GetGUID(), true);

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_HUNTER)
            {
                player->SEND_GOSSIP_MENU(14796, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14797, creature->GetGUID());
            return false;
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                SetCombatMovement(false);

                if (!(me->GetPhaseMask() & 16388))
                {
                    me->setActive(true);
                    events.ScheduleEvent(EVENT_SHOOT_GUN, urand(3500, 5000));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    std::list<Creature*> targets;
                    me->GetCreatureListWithEntryInGrid(targets, 48304, 30.f);

                    if (!targets.empty())
                    {
                        Creature* target = Trinity::Containers::SelectRandomContainerElement(targets);

                        if (target)
                            me->CastSpell(target, SPELL_SHOOT_GUN, false);
                    }

                    events.ScheduleEvent(EVENT_SHOOT_GUN, urand(3500, 5000));
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_slinky_sharpshiv : public CreatureScript
{
    public:
        npc_kezan_slinky_sharpshiv() : CreatureScript("npc_kezan_slinky_sharpshiv") { }

    private:
        enum
        {
            SAY_EVISCERATE      = 0,
            SAY_WALTZ_RIGHT_IN  = 1,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_EVISCERATE:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_EVISCERATE, player->GetGUID(), true);
                    }
                    break;
                case QUEST_WALTZ_RIGHT_IN:
                    {
                        if (creature->IsAIEnabled)
                        creature->AI()->Talk(SAY_WALTZ_RIGHT_IN, player->GetGUID(), true);
                    }
                    break;
            }

            return true;
        }

        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
        {
            if (quest->GetQuestId() == QUEST_WALTZ_RIGHT_IN)
            {
                if (player->GetQuestStatus(QUEST_THE_GREAT_BANK_HEIST) == QUEST_STATUS_REWARDED &&
                    player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_REWARDED &&
                    player->GetQuestStatus(QUEST_LIBERATE_THE_KAJAMITE) == QUEST_STATUS_REWARDED)
                {
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_5);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_6, false);
                    player->SaveToDB();
                }
            }

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_ROGUE)
            {
                player->PrepareQuestMenu(creature->GetGUID());
                player->SEND_GOSSIP_MENU(14811, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(14812, creature->GetGUID());
            return false;
        }
};

class npc_kezan_warrior_matic_nx_01 : public CreatureScript
{
    public:
        npc_kezan_warrior_matic_nx_01() : CreatureScript("npc_kezan_warrior_matic_nx_01") { }

    private:
        enum
        {
            SAY_CHARGE  = 0,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_CHARGE)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_CHARGE, player->GetGUID(), true);

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getClass() != CLASS_WARRIOR)
            {
                player->SEND_GOSSIP_MENU(15000, creature->GetGUID());
                return true;
            }

            return false;
        }
};

const uint32 Homies[3]=
{
    NPC_ACE,
    NPC_GOBBER,
    NPC_IZZY
};

const uint32 InvisHomiesEntry[3]=
{
    NPC_INVIS_ACE,
    NPC_INVIS_GOBBER,
    NPC_INVIS_IZZY
};

const uint64 DetectSpellsEntry[3]=
{
    SPELL_QUEST_INVISIBILITY_DETECTION_1,
    SPELL_QUEST_INVISIBILITY_DETECTION_2,
    SPELL_QUEST_INVISIBILITY_DETECTION_3
};

class npc_kezan_megs_dreadshredder : public CreatureScript
{
    public:
        npc_kezan_megs_dreadshredder() : CreatureScript("npc_kezan_megs_dreadshredder") { }

    private:
        enum talks
        {
            DREADSHREDDER_SAY_USE_KEYS      = 0,
            DREADSHREDDER_SAY_YOU_LIKE_IT   = 1,
            DREADSHREDDER_SAY_FINISH        = 2,
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (creature->GetPhaseMask() == 4)
            {
                player->SEND_GOSSIP_MENU(14658, creature->GetGUID());
                return true;
            }

            return false;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ROLLING_WITH_MY_HOMIES)
            {
                if (Vehicle* vehicle = player->GetVehicle())
                {
                    if (vehicle->GetCreatureEntry() == NPC_HOT_ROD)
                    {
                        player->KilledMonsterCredit(NPC_HOTROD_KILL_CREDIT, 0);

                        for (int i = 0; i < 3; ++i)
                        {
                            if (vehicle->GetPassenger(i + 1))
                                player->KilledMonsterCredit(InvisHomiesEntry[i], 0);
                            else
                                player->CastSpell(player, DetectSpellsEntry[i], false);
                        }

                        return true;
                    }
                }
                else
                {
                    for (int i = 0; i < 3; ++i)
                        player->CastSpell(player, DetectSpellsEntry[i], true);

                    if (creature->IsAIEnabled)
                    {
                        creature->AI()->Talk(DREADSHREDDER_SAY_USE_KEYS, player->GetGUID());
                        creature->AI()->Talk(DREADSHREDDER_SAY_YOU_LIKE_IT, player->GetGUID());
                    }
                }

                player->RemoveAura(SPELL_KEYS_TO_THE_HOT_ROD);
                player->CastSpell(player, SPELL_KEYS_TO_THE_HOT_ROD, false);
            }

            return true;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_ROLLING_WITH_MY_HOMIES:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(DREADSHREDDER_SAY_FINISH, player->GetGUID(), true);
                    }
                    break;
                case QUEST_ROBBING_HOODS:
                    {
                        if (player->GetQuestStatus(QUEST_THE_GREAT_BANK_HEIST) == QUEST_STATUS_REWARDED &&
                            player->GetQuestStatus(QUEST_WALTZ_RIGHT_IN) == QUEST_STATUS_REWARDED &&
                            player->GetQuestStatus(QUEST_LIBERATE_THE_KAJAMITE) == QUEST_STATUS_REWARDED)
                        {
                            player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_5);
                            player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_6, false);
                            player->SaveToDB();
                        }
                    }
                    break;
            }

            return true;
        }
};

enum
{
    ACTION_SPEED_BOOST_APPLIED  = -1,
    ACTION_SPEED_BOOST_REMOVED  = -2,
    ACTION_HOMIE_ENTER          = -3,
    ACTION_FAILED_TO_ENTER      = -4,
};

class npc_kezan_hot_rod : public CreatureScript
{
    public:
        npc_kezan_hot_rod() : CreatureScript("npc_kezan_hot_rod") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public VehicleAI
        {
            creature_script_impl(Creature* creature)
                : VehicleAI(creature)
                , speedState(STATE_NONE)
                , speed(0.1f)
                , boost(0.f)
                , homiesCount(0)
            { }

            enum
            {
                EVENT_UPDATE_MOVEMENT   = 1,

                STATE_NONE              = 0,
                STATE_MOVING            = 1,
                STATE_MAX_SPEED         = 2,
                STATE_BOOST_SPEED       = 4,
            };

            EventMap events;
            uint8 speedState;
            uint8 homiesCount;
            float speed;
            float boost;

            void InitializeAI()
            {
                events.ScheduleEvent(EVENT_UPDATE_MOVEMENT, 250);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_SPEED_BOOST_APPLIED:
                        speedState |= STATE_BOOST_SPEED;
                        break;
                    case ACTION_SPEED_BOOST_REMOVED:
                        speedState &= ~STATE_BOOST_SPEED;
                        boost = 0;
                        break;
                    case ACTION_HOMIE_ENTER:
                        speed = 0.1f;
                        ++homiesCount;
                        speedState &= ~STATE_MAX_SPEED;
                        me->SetSpeed(MOVE_RUN, speed, true);
                        me->SetControlled(true, UNIT_STATE_STUNNED);
                        events.Reset();
                        break;
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (apply)
                {
                    if (Player* player = who->ToPlayer())
                    {
                        player->RemoveAura(SPELL_KEYS_TO_THE_HOT_ROD);
                        const uint8 homiesMask = Kezan::GetHomiesStatus(player);

                        if (homiesMask == HOMIES_NOT_ALLOWED || homiesMask == HOMIES_NULL)
                            return;

                        if (homiesMask == HOMIES_FULL)
                            homiesCount = 3;
                        else
                        {
                            for (uint8 index = 0; index < 3; ++index)
                                if (homiesMask & HomiesType[index])
                                    ++homiesCount;
                        }

                        me->SetControlled(true, UNIT_STATE_STUNNED);
                        return;
                    }

                    if (homiesCount)
                        --homiesCount;

                    if (!homiesCount)
                    {
                        speed = 0.1f;
                        me->SetSpeed(MOVE_RUN, speed, true);
                        me->SetControlled(false, UNIT_STATE_STUNNED);
                        events.RescheduleEvent(EVENT_UPDATE_MOVEMENT, 200);
                    }
                }
                else if (who->GetTypeId() == TYPEID_PLAYER)
                    me->CastSpell(who, 66611, true);
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_UPDATE_MOVEMENT)
                {
                    float x, y, z;
                    me->GetPosition(x, y, z);

                    if (me->IsInWater())
                    {
                        float groundLevel, waterLevel;
                        groundLevel = me->GetMap()->GetHeight(x, y, z);
                        waterLevel = me->GetMap()->GetWaterOrGroundLevel(x, y, z);

                        if (abs(waterLevel - groundLevel) >= 1.5f)
                        {
                            me->CastSpell(me, 50630, true);
                            return;
                        }
                    }
                    else if (!me->GetMap()->IsOutdoors(x, y, z))
                    {
                        me->CastSpell(me, 50630, true);
                        return;
                    }

                    if (me->isMoving())
                    {
                        me->CastSpell((Unit*)NULL, 66301, true);

                        if (!(speedState & STATE_MOVING))
                            speedState |= STATE_MOVING;

                        if (!(speedState & STATE_MAX_SPEED))
                            speed += 0.1f;

                        if (speedState & STATE_BOOST_SPEED)
                        {
                            if (speed < 2.f)
                                speed += 0.1f;

                            boost = speed * 0.5f;
                        }

                        if (speed >= 2.f)
                            speedState |= STATE_MAX_SPEED;

                        me->SetSpeed(MOVE_RUN, speed + boost, true);
                    }
                    else if (speedState != STATE_NONE)
                    {
                        speedState = STATE_NONE;
                        speed = 0.1f;
                        me->RemoveAura(66300);
                        me->SetSpeed(MOVE_RUN, speed, true);
                    }

                    events.ScheduleEvent(EVENT_UPDATE_MOVEMENT, 100);
                }
            }
        };
};

class npc_kezan_homie_follower : public CreatureScript
{
    public:
        npc_kezan_homie_follower(const char* scriptName, uint8 homieId)
            : CreatureScript(scriptName)
            , m_homieId(homieId)
        { }

    private:
        uint8 m_homieId;

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature, m_homieId);
        }

        class EnterHotRodEvent : public BasicEvent
        {
            public:
                EnterHotRodEvent(uint64 meGUID, uint64 hotrodGUID, uint8 seatId)
                    : m_meGUID(meGUID)
                    , m_hotrodGUID(hotrodGUID)
                    , m_seatId(seatId)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/)
                {
                    Unit* me = ObjectAccessor::GetObjectInWorld(m_meGUID, (Creature*)NULL);
                    Unit* hotrod = ObjectAccessor::GetObjectInWorld(m_hotrodGUID, (Creature*)NULL);

                    if (me && hotrod)
                    {
                        me->StopMoving();
                        me->EnterVehicle(hotrod, m_seatId);
                    }
                    else if (me && me->IsAIEnabled)
                        me->GetAI()->DoAction(ACTION_FAILED_TO_ENTER);

                    return true;
                }

                uint64 m_hotrodGUID;
                uint64 m_meGUID;
                uint8 m_seatId;
        };

        struct creature_script_impl : public FollowerAI
        {
            creature_script_impl(Creature* creature, uint8 homieId)
                : FollowerAI(creature)
                , m_homieId(homieId)
                , onStadion(false)
            { }

            enum
            {
                EVENT_CHECK_LEADER_VEHICLE  = 1,
            };

            EventMap events;
            uint8 m_homieId;
            bool onStadion;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetWalk(false);
            }

            void DespawnOnDistanceFail()
            {
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    summoner->CastSpell((Unit*)NULL, SummonHomieSpellEntry[m_homieId], false);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->SetReactState(REACT_PASSIVE);

                Player* player = summoner->ToPlayer();

                if (!player)
                {
                    me->DespawnOrUnsummon();
                    return;
                }

                static const float FollowAngle[3]=
                {
                    M_PI + M_PI / 4,
                    M_PI,
                    M_PI - M_PI / 4,
                };

                SetFollowAngle(FollowAngle[m_homieId]);
                SetMaxFollowDist(50.f);
                SetIngoreLeaderGroup(true);
                StartFollow(player);
                events.ScheduleEvent(EVENT_CHECK_LEADER_VEHICLE, 0);
            }

            void OnControlVehicle(Unit* base, int8 /*seatId*/, bool apply)
            {
                if (!apply)
                {
                    SetFollowPaused(false);
                    events.RescheduleEvent(EVENT_CHECK_LEADER_VEHICLE, 250);
                }
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_FAILED_TO_ENTER)
                {
                    SetFollowPaused(false);
                    events.RescheduleEvent(EVENT_CHECK_LEADER_VEHICLE, 250);
                }
            }

            void UpdateFollowerAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_CHECK_LEADER_VEHICLE)
                {
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    {
                        if (Unit* vehicle = summoner->GetVehicleBase())
                        {
                            if (vehicle->GetEntry() == NPC_HOT_ROD)
                            {
                                SetFollowPaused(true);
                                events.Reset();

                                if (me->GetExactDist2dSq(vehicle) > 9.f)
                                {
                                    float x, y, z = vehicle->GetPositionZ();
                                    vehicle->GetNearPoint2D(x, y, 3.f, vehicle->GetAngle(me), false);
                                    me->GetMotionMaster()->MoveSplinePoint(x, y, z, 7.f, false, false, vehicle);
                                    me->m_Events.AddEvent(new EnterHotRodEvent(me->GetGUID(), vehicle->GetGUID(), m_homieId + 1), me->m_Events.CalculateTime(me->GetSplineDuration()));
                                }
                                else
                                    me->EnterVehicle(vehicle, m_homieId + 1);

                                return;
                            }
                            else if (vehicle->GetEntry() ==  37213 || vehicle->GetEntry() == 37179 && !onStadion)
                            {
                                onStadion = true;

                                static const Position HomiesOnStadionPos[3]=
                                {
                                    {-8247.658f, 1478.638f, 41.221f, 3.15f},
                                    {-8247.034f, 1477.466f, 41.165f, 3.15f},
                                    {-8247.800f, 1476.183f, 41.221f, 3.15f},
                                };

                                SetFollowPaused(true);
                                float x, y, z, o;
                                HomiesOnStadionPos[m_homieId].GetPosition(x, y, z, o);
                                me->GetMotionMaster()->MoveSplinePoint(x, y, z, 12.5f, false, false, NULL, o, true);
                            }
                        }
                        else if (onStadion)
                        {
                            onStadion = false;
                            SetFollowPaused(false);
                        }
                    }

                    events.ScheduleEvent(EVENT_CHECK_LEADER_VEHICLE, 500);
                }
            }
        };
};

// Quest Rolling with my Homies 14071
enum
{
    TYPE_KNOCKBACK_STATE    = 1,

    DATA_KNOCKBACK_ENABLED  = 1,
    DATA_KNOCKBACK_DISABLED = 2,
};

class npc_kezan_citizen : public CreatureScript
{
    public:
        npc_kezan_citizen() : CreatureScript("npc_kezan_citizen") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , knockbackState(DATA_KNOCKBACK_ENABLED)
            { }

            enum
            {
                EVENT_RESET     = 1,
                EVENT_GO_HOME   = 2,

                RANDOM_COMPLAIN = 1,
            };

            EventMap events;
            uint8 knockbackState;

            void Reset()
            {
                me->SetWalk(false);
            }

            uint32 GetData(uint32 data) const
            {
                if (data == TYPE_KNOCKBACK_STATE)
                    return knockbackState;

                return 0;
            }

            void SetData(uint32 type, uint32 data) override
            {
                if (type == TYPE_KNOCKBACK_STATE)
                {
                    knockbackState = data;

                    if (data == DATA_KNOCKBACK_DISABLED)
                        events.ScheduleEvent(EVENT_RESET, me->GetSplineDuration() + 500);
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RESET:
                            knockbackState = DATA_KNOCKBACK_ENABLED;
                            events.ScheduleEvent(EVENT_GO_HOME, 2000);
                            break;
                        case EVENT_GO_HOME:
                            me->SetWalk(true);
                            me->GetMotionMaster()->MoveTargetedHome();
                            break;
                    }
                }
            }
        };
};

class npc_kezan_citizen_immune : public CreatureScript
{
    public:
        npc_kezan_citizen_immune() : CreatureScript("npc_kezan_citizen_immune") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            uint32 GetData(uint32 data) const
            {
                if (data == TYPE_KNOCKBACK_STATE)
                    return DATA_KNOCKBACK_DISABLED;

                return 0;
            }
        };
};

const uint16 TribuneEmotes[15] =
{
    EMOTE_ONESHOT_QUESTION,
    EMOTE_ONESHOT_EXCLAMATION,
    EMOTE_ONESHOT_NO,
    EMOTE_ONESHOT_TALK,
    EMOTE_ONESHOT_POINT,
    EMOTE_ONESHOT_DANCE,
    EMOTE_ONESHOT_CHEER,
    EMOTE_ONESHOT_ROAR,
    EMOTE_ONESHOT_CHICKEN,
    EMOTE_ONESHOT_RUDE,
    EMOTE_ONESHOT_LAUGH,
    EMOTE_ONESHOT_YES,
    EMOTE_ONESHOT_WAVE,
    EMOTE_ONESHOT_SPELL_CAST_OMNI
};

class npc_kezan_citizen_tribune : public CreatureScript
{
    public:
        npc_kezan_citizen_tribune() : CreatureScript("npc_kezan_citizen_tribune") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RANDOM_EMOTE  = 1,
                EVENT_COLA_CAN      = 2,

                SPELL_COLA_CAN      = 75133,
            };

            EventMap events;

            void InitializeAI()
            {
                events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(2000, 5000));
                events.ScheduleEvent(EVENT_COLA_CAN, urand(4000, 8000));
            }

            uint32 GetData(uint32 data) const
            {
                if (data == TYPE_KNOCKBACK_STATE)
                    return DATA_KNOCKBACK_DISABLED;

                return 0;
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RANDOM_EMOTE:
                            me->HandleEmoteCommand(TribuneEmotes[urand(0, 14)]);
                            events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(3000, 7000));
                            break;
                        case EVENT_COLA_CAN:
                            me->CastSpell(me, SPELL_COLA_CAN, false);
                            events.ScheduleEvent(EVENT_COLA_CAN, urand(4000, 10000));
                            break;
                    }
                }
            }
        };
};

class at_kezan_rolling_with_my_homies : public AreaTriggerScript
{
    public:
        at_kezan_rolling_with_my_homies() : AreaTriggerScript("at_kezan_rolling_with_my_homies") { }

    private:
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            enum
            {
                TRIGGER_ID_ACE      = 5497,
                TRIGGER_ID_GOOBER   = 5498,
                TRIGGER_ID_IZZY     = 5499,

                SPELL_SUMMON_ACE    = 66597,
                SPELL_SUMMON_GOOBER = 66599,
                SPELL_SUMMON_IZZY   = 66600,
            };

            const uint8 homiesMask = Kezan::GetHomiesStatus(player);

            if (homiesMask == HOMIES_NOT_ALLOWED || homiesMask == HOMIES_FULL)
                return true;

            uint8 index = 0;
            uint32 summonSpellEntry = SPELL_SUMMON_ACE;

            switch (trigger->id)
            {
                case TRIGGER_ID_ACE:
                    break;
                case TRIGGER_ID_GOOBER:
                    index = 1;
                    summonSpellEntry = SPELL_SUMMON_GOOBER;
                    break;
                case TRIGGER_ID_IZZY:
                    index = 2;
                    summonSpellEntry = SPELL_SUMMON_IZZY;
                    break;
                default:
                    return false;
            }

            if (!(homiesMask & HomiesType[index]))
            {
                player->KilledMonsterCredit(InvisHomiesEntry[index], 0);
                player->RemoveAura(DetectSpellsEntry[index]);
                player->CastSpell(player, summonSpellEntry, false);

                if (Unit* hotrod = player->GetVehicleBase())
                    if (hotrod->IsAIEnabled)
                        hotrod->GetAI()->DoAction(ACTION_HOMIE_ENTER);
            }

            return true;
        }
};

class spell_kezan_rolling_with_my_homie_exit_spell : public SpellScriptLoader
{
    public:
        spell_kezan_rolling_with_my_homie_exit_spell() : SpellScriptLoader("spell_kezan_rolling_with_my_homie_exit_spell") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_KEYS_TO_THE_HOT_ROD, false);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_punch_it_boost : public SpellScriptLoader
{
    public:
        spell_kezan_punch_it_boost() : SpellScriptLoader("spell_kezan_punch_it_boost") { }

    private:
        class aura_script_impl : public AuraScript
        {
            PrepareAuraScript(aura_script_impl);

            enum sBoost
            {
                SPELL_VISUAL_BOOS_1    = 1168,
                SPELL_VISUAL_BOOS_2    = 6695,
            };

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                PreventDefaultAction();

                if (Unit* target = GetTarget())
                {
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_SPEED_BOOST_APPLIED);

                    target->SendPlaySpellVisualKit(SPELL_VISUAL_BOOS_1, 0);
                    target->SendPlaySpellVisualKit(SPELL_VISUAL_BOOS_2, 0);
                }
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                PreventDefaultAction();

                if (Unit* target = GetTarget())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_SPEED_BOOST_REMOVED);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(aura_script_impl::OnApply, EFFECT_0, SPELL_AURA_MOD_SPEED_NOT_STACK, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(aura_script_impl::OnRemove, EFFECT_0, SPELL_AURA_MOD_SPEED_NOT_STACK, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new aura_script_impl();
        }
};

class spell_kezan_hot_rod_knockback : public SpellScriptLoader
{
    public:
        spell_kezan_hot_rod_knockback() : SpellScriptLoader("spell_kezan_hot_rod_knockback") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            class HRKFilter
            {
                public:
                    HRKFilter(Unit* hotRod)
                    : m_hotRod(hotRod)
                { }

                    bool operator()(WorldObject const *object) const
                    {
                        if (m_hotRod->HasInLine(object, 1.75f) && m_hotRod->GetExactDistSq(object) <= 20.f)
                            return false;

                        return true;
                    }

                private:
                    Unit* m_hotRod;
            };

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (Unit* caster = GetCaster())
                    targets.remove_if(HRKFilter(caster));

                if (targets.empty())
                    FinishCast(SPELL_FAILED_BAD_TARGETS);
            }

            void HandleKnockBack(SpellEffIndex effIndex)
            {
                enum
                {
                    RANDOM_COMPLAIN = 1,
                };

                Unit* caster = GetCaster();
                Creature* target = GetHitCreature();

                if (!(caster && target && target->IsAIEnabled))
                    return;

                if (target->GetAI()->GetData(TYPE_KNOCKBACK_STATE) != DATA_KNOCKBACK_ENABLED)
                    PreventHitDefaultEffect(effIndex);
                else
                {
                    target->GetAI()->SetData(TYPE_KNOCKBACK_STATE, DATA_KNOCKBACK_DISABLED);

                    if (urand(0, 100) < 10)
                        if (Vehicle* vehicle = caster->GetVehicleKit())
                            if (Unit* passenger = vehicle->GetPassenger(0))
                                if (Player* player = passenger->ToPlayer())
                                    target->AI()->Talk(RANDOM_COMPLAIN, player->GetGUID());
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_script_impl::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::HandleKnockBack, EFFECT_0, SPELL_EFFECT_KNOCK_BACK);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_hot_rod_honk_horn : public SpellScriptLoader
{
    public:
        spell_kezan_hot_rod_honk_horn() : SpellScriptLoader("spell_kezan_hot_rod_honk_horn") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!(caster && target && target->IsAIEnabled && target->GetAI()->GetData(TYPE_KNOCKBACK_STATE) == DATA_KNOCKBACK_ENABLED))
                    return;

                target->HandleEmoteCommand(EMOTE_ONESHOT_COWER);
                target->SetWalk(false);
                float h_angle = caster->GetOrientation();
                float m_angle = caster->GetAngle(target);
                float angle = target->GetAngle(caster);
                float x, y, z = target->GetPositionZ();

                if (h_angle - m_angle < 0)
                    target->GetNearPoint2D(x, y, 7.0f, angle + M_PI + M_PI / 4);
                else
                    target->GetNearPoint2D(x, y, 7.0f, angle + M_PI - M_PI / 4);

                target->GetMotionMaster()->MovePoint(0, x, y, z);
                target->GetAI()->SetData(TYPE_KNOCKBACK_STATE, DATA_KNOCKBACK_DISABLED);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

// Quests: The Replacements 24488 & Necessary Roughness 24502 & Fourth and Goal 28414
enum
{
    SOUND_WOW_1                         = 17466,
    SOUND_WOW_2                         = 17467,

    SPELL_INCREASED_MOD_DETECTED_RANGE  = 76651,
  
    ACTION_FAIL_NECESSARY_ROUGHNESS     = -1,
    ACTION_SIGNAL_BACK_TO_SHREDDER      = -2,
    ACTION_KICK_FOOTBOMB                = -3,
    ACTION_THROW_FOOTBOMB               = -4,
};

class npc_kezan_coach_crosscheck : public CreatureScript
{
    public:
        npc_kezan_coach_crosscheck() : CreatureScript("npc_kezan_coach_crosscheck") { }

    private:
        enum
        {
            COACH_SAY_GOTTA_HURRY               = 1,
            COACH_SAY_SHREDDER                  = 2,
            COACH_SAY_GOOD_WORK                 = 3,
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) & QUEST_STATUS_COMPLETE)
            {
                player->PrepareQuestMenu(creature->GetGUID());
                player->SEND_GOSSIP_MENU(17551, creature->GetGUID());
                return true;
            }

            return false;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_THE_REPLACEMENTS:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(COACH_SAY_GOTTA_HURRY, player->GetGUID(), true);
                    }
                    break;
                case QUEST_NECESSARY_ROUGHNESS:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(COACH_SAY_SHREDDER, player->GetGUID(), true);

                        player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_4, false);
                    }
                    break;
                case QUEST_FOURTH_AND_GOAL:
                    player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_4, false);
                    break;
            }

            return true;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            if (quest->GetQuestId() == QUEST_FOURTH_AND_GOAL)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(COACH_SAY_GOOD_WORK, player->GetGUID(), true);

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_bilgewater_buccaneer : public CreatureScript
{
    public:
        npc_kezan_bilgewater_buccaneer() : CreatureScript("npc_kezan_bilgewater_buccaneer") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                BUCCANEER_SAY_FOOTBOMBS = 1,
                ACTION_SUMMON_SHARKS    = 1,
            };

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetControlled(true, UNIT_STATE_ROOT);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_SUMMON_SHARKS), me->m_Events.CalculateTime(2000));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_SUMMON_SHARKS)
                {
                    uint64 summonerGUID = me->ToTempSummon()->GetSummonerGUID();

                    if (Player* player = ObjectAccessor::GetPlayer(*me, summonerGUID))
                    {
                        if (player->GetQuestStatus(QUEST_NECESSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE)
                        {
                            Talk(BUCCANEER_SAY_FOOTBOMBS, summonerGUID, true);

                            static const uint32 SummonSharkSpell[8]=
                            {
                                69971,
                                69976,
                                69977,
                                69978,
                                69979,
                                69980,
                                69981,
                                69982
                            };

                            for (int i = 0; i < 8; ++i)
                                player->CastSpell((Unit*)NULL, SummonSharkSpell[i], false);
                        }
                    }
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (seatId != 0)
                    return;

                if (Player* player = who->ToPlayer())
                {
                    if (apply)
                    {
                        player->PlayDirectSound(SOUND_WOW_1, player);
                        player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_4);
                        player->setVehicleEjectPos(-8253.189f, 1481.026f, 41.544f, 0.865f);
                    }
                    else
                    {
                        player->CastSpell((Unit*)NULL, 69987, false);
                        player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_4, true);
                        player->RemoveAura(SPELL_INCREASED_MOD_DETECTED_RANGE);

                        if (player->GetQuestStatus(QUEST_NECESSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE)
                            player->FailQuest(QUEST_NECESSARY_ROUGHNESS);
                    }
                }
            }
        };
};

static const float BuccaneerPos[3] = {-8253.907f, 1484.341f, 41.682f};

class npc_kezan_steamwheedle_shark : public CreatureScript
{
    public:
        npc_kezan_steamwheedle_shark() : CreatureScript("npc_kezan_steamwheedle_shark") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , blown(false)
            { }

            enum
            {
                SPELL_PERMANENT_FEIGN_DEATH = 29266,

                ACTION_FEIGN_DEATH          = 1,
                ACTION_FAIL_QUEST           = 2,

                SHARK_EVENT_ID              = 1037114,
            };

            bool blown;

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->SetWalk(true);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                me->GetMotionMaster()->MovePoint(0, BuccaneerPos[0], BuccaneerPos[1], BuccaneerPos[2]);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_FAIL_QUEST), me->m_Events.CalculateTime(me->GetSplineDuration()), true, SHARK_EVENT_ID);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_FEIGN_DEATH:
                        me->CastSpell(me, SPELL_PERMANENT_FEIGN_DEATH, false);
                        me->DespawnOrUnsummon(3000);
                        break;
                    case ACTION_FAIL_QUEST:
                        {
                            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                summoner->ExitVehicle();
                        }
                        break;
                    case ACTION_THROW_FOOTBOMB:
                        {
                            if (!blown)
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                {
                                    player->PlayDirectSound(SOUND_WOW_1, player);
                                    player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                                }

                                blown = true;
                                me->StopMoving();
                                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                                me->m_Events.DeleteEventId(SHARK_EVENT_ID);
                                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_FEIGN_DEATH), me->m_Events.CalculateTime(500));
                            }
                        }
                        break;
                }
            }
        };
};

class npc_kezan_bilgewater_buccaneer_goal : public CreatureScript
{
    public:
        npc_kezan_bilgewater_buccaneer_goal() : CreatureScript("npc_kezan_bilgewater_buccaneer_goal") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public VehicleAI
        {
            creature_script_impl(Creature* creature)
                : VehicleAI(creature)
                , seatInChange(false)
            { }

            enum
            {
                BUCCANEER_SAY_FOOTBOMB      = 1,
                ACTION_CHANGE_SEAT          = 1,

                NPC_FOURTH_AND_GOAL_TARGET  = 37203,
            };

            bool seatInChange;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->m_movementInfo.pitch = 0.7f;
                me->RemoveExtraUnitMovementFlag(MOVEMENTFLAG2_FULL_SPEED_PITCHING);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_SIGNAL_BACK_TO_SHREDDER:
                        {
                            if (Vehicle* vehicle = me->GetVehicleKit())
                            {
                                if (Unit* passenger = vehicle->GetPassenger(0))
                                {
                                    if (Player* player = passenger->ToPlayer())
                                    {
                                        if (player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) == QUEST_STATUS_INCOMPLETE)
                                        {
                                            player->PlayDirectSound(SOUND_WOW_2, player);
                                            player->KilledMonsterCredit(NPC_FOURTH_AND_GOAL_TARGET, 0);
                                            player->CastSpell((Unit*)NULL, 66322, false);
                                            me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_CHANGE_SEAT), me->m_Events.CalculateTime(1000));
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case ACTION_CHANGE_SEAT:
                        {
                            if (Vehicle* vehicle = me->GetVehicleKit())
                            {
                                if (Unit* passenger = vehicle->GetPassenger(0))
                                {
                                    seatInChange = true;
                                    passenger->ChangeSeat(1);
                                    passenger->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_7);
                                    passenger->CastSpell(passenger, SPELL_QUEST_INVISIBILITY_DETECTION_6, false);

                                    if (Player* player = passenger->ToPlayer())
                                        player->SaveToDB();
                                }
                            }
                        }
                        break;
                }
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId)
            {
                switch (seatId)
                {
                    case 0:
                        passenger->m_movementInfo.t_pos.Relocate(0, 0, -0.08333206f);
                        enterPos.Relocate(0, 0, -0.08333206f);
                        break;
                    case 1:
                        passenger->m_movementInfo.t_pos.Relocate(-0.890625f, 2.095215f, -0.1065292f);
                        enterPos.Relocate(-0.890625f, 2.095215f, -0.1065292f);
                        break;
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (Player* player = who->ToPlayer())
                {
                    if (apply)
                    {
                        if (seatId == 0)
                        {
                            player->PlayDirectSound(SOUND_WOW_2, player);
                            player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_4);
                            player->CastSpell(player, SPELL_INCREASED_MOD_DETECTED_RANGE, false);
                            player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_7, false);
                            me->Whisper(BUCCANEER_SAY_FOOTBOMB, player->GetGUID(), true);
                        }
                        else if (seatInChange)
                            seatInChange = false;

                        player->setVehicleEjectPos(-8253.189f, 1481.026f, 41.544f, 0.865f);
                    }
                    else if (!seatInChange)
                    {
                        player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_7);
                        player->RemoveAura(SPELL_INCREASED_MOD_DETECTED_RANGE);
                        player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_4, false);
                    }
                }
            }
        };
};

class npc_kezan_fourth_and_goal_target : public CreatureScript
{
    public:
        npc_kezan_fourth_and_goal_target() : CreatureScript("npc_kezan_fourth_and_goal_target") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void InitializeAI()
            {
                me->setActive(true);
            }
        };
};

class npc_kezan_deathwing_qfag : public CreatureScript
{
    public:
        npc_kezan_deathwing_qfag() : CreatureScript("npc_kezan_deathwing_qfag") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , vulnerableToBomb(false)
                , flyAway(false)
            { }

            enum
            {
                EVENT_TALK                  = 1,
                EVENT_ATTACK_KAJARO         = 2,
                EVENT_SOUND_GOBLINS_IN_FEAR = 3,
                EVENT_GO_TO_STADION         = 4,
                EVENT_FLY_AWAY              = 5,
                EVENT_ACE_TALK              = 6,
                EVENT_IZZY_TALK             = 7,

                TALK_MORTAL_WORLD           = 1,
                TALK_WHAT_HE_DID            = 2,
                HOMIE_TALK_WHAT_HE_DID      = 1,

                SPELL_XPLOSION              = 91117,
                SPELL_DEATHWINGS_ATTACK     = 66858,

                DEATHWING_SOUND             = 23227,
            };

            EventMap events;
            bool vulnerableToBomb;
            bool flyAway;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MoveSplinePath(1, true, false, 20.f);
                events.ScheduleEvent(EVENT_TALK, 3000);
                events.ScheduleEvent(EVENT_ATTACK_KAJARO, me->GetSplineDuration());

                if (Player* player = summoner->ToPlayer())
                    summoner->PlayDirectSound(DEATHWING_SOUND, player);
            }

            void FlyAway()
            {
                if (!flyAway)
                {
                    flyAway = true;
                    me->GetMotionMaster()->MoveSplinePath(3, true, false, 20.f);
                }
            }

            void DoAction(int32 const action) final
            {
                if (vulnerableToBomb && action == ACTION_KICK_FOOTBOMB)
                {
                    me->CastSpell(me, SPELL_XPLOSION, false);
                    FlyAway();
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK:
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                {
                                    player->PlayDirectSound(14558, player);
                                    Talk(TALK_MORTAL_WORLD, me->ToTempSummon()->GetSummonerGUID(), true);
                                }

                                events.ScheduleEvent(EVENT_SOUND_GOBLINS_IN_FEAR, 3000);
                            }
                            break;
                        case EVENT_SOUND_GOBLINS_IN_FEAR:
                            {
                                static const uint32 fearSounds[4]=
                                {
                                    14556,
                                    14557,
                                    14558,
                                    14559,
                                };

                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                    player->PlayDirectSound(fearSounds[urand(0, 3)], player);

                                events.ScheduleEvent(EVENT_SOUND_GOBLINS_IN_FEAR, 3000);
                            }
                            break;
                        case EVENT_ATTACK_KAJARO:
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                    me->PlayDirectSound(23229, player);

                                me->CastSpell((Unit*)NULL, SPELL_DEATHWINGS_ATTACK, false);
                                me->GetMotionMaster()->MoveSplinePath(2, true, false, 20.f);
                                events.ScheduleEvent(EVENT_GO_TO_STADION, me->GetSplineDuration());
                            }
                            break;
                        case EVENT_GO_TO_STADION:
                            vulnerableToBomb = true;
                            me->CastSpell(me, 69988, false);
                            events.ScheduleEvent(EVENT_FLY_AWAY, 2000);
                            break;
                        case EVENT_FLY_AWAY:
                            {
                                vulnerableToBomb = false;
                                FlyAway();

                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                {
                                    Talk(TALK_WHAT_HE_DID, me->ToTempSummon()->GetSummonerGUID(), true);
                                    player->CastSpell(player, 90615, false);
                                    player->CastSpell(player, 96274, false);
                                }

                                events.CancelEvent(EVENT_SOUND_GOBLINS_IN_FEAR);
                                events.ScheduleEvent(EVENT_ACE_TALK, 2000);
                            }
                            break;
                        case EVENT_ACE_TALK:
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                {
                                    if (Creature* ace = Kezan::GetHomie(player, 34957, 30.f))
                                        if (ace->IsAIEnabled)
                                            ace->AI()->Talk(HOMIE_TALK_WHAT_HE_DID, me->ToTempSummon()->GetSummonerGUID(), true);
                                }

                                events.ScheduleEvent(EVENT_IZZY_TALK, 2000);
                            }
                            break;
                        case EVENT_IZZY_TALK:
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                {
                                    if (Creature* ace = Kezan::GetHomie(player, 34959, 30.f))
                                        if (ace->IsAIEnabled)
                                            ace->AI()->Talk(HOMIE_TALK_WHAT_HE_DID, me->ToTempSummon()->GetSummonerGUID(), true);
                                }
                            }
                            break;
                    }
                }
            }
        };
};

class spell_kezan_kick_footbomb : public SpellScriptLoader
{
    public:
        spell_kezan_kick_footbomb() : SpellScriptLoader("spell_kezan_kick_footbomb") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (caster && target)
                {
                    if (target->GetEntry() == 37203)
                        target->CastSpell(caster, 70062, false);
                    else if (target->GetEntry() == 48572)
                        if (target->IsAIEnabled)
                            target->GetAI()->DoAction(ACTION_KICK_FOOTBOMB);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_fourth_and_goal_signal_back_to_shredder : public SpellScriptLoader
{
    public:
        spell_kezan_fourth_and_goal_signal_back_to_shredder() : SpellScriptLoader("spell_kezan_fourth_and_goal_signal_back_to_shredder") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_SIGNAL_BACK_TO_SHREDDER);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_fourth_and_goal_deathwing_sound_4 : public SpellScriptLoader
{
    public:
        spell_kezan_fourth_and_goal_deathwing_sound_4() : SpellScriptLoader("spell_kezan_fourth_and_goal_deathwing_sound_4") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* deathwing = GetHitCreature();

                if (deathwing->IsSummon())
                    if (Player* player = ObjectAccessor::GetPlayer(*deathwing, deathwing->ToTempSummon()->GetSummonerGUID()))
                        deathwing->PlayDirectSound(GetSpellInfo()->Effects[effIndex].BasePoints, player);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_throw_footbomb : public SpellScriptLoader
{
    public:
        spell_kezan_throw_footbomb() : SpellScriptLoader("spell_kezan_throw_footbomb") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_THROW_FOOTBOMB);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_despawn_event_creature : public SpellScriptLoader
{
    public:
        spell_kezan_despawn_event_creature() : SpellScriptLoader("spell_kezan_despawn_event_creature") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Creature* target = GetHitCreature())
                    target->DespawnOrUnsummon();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

// Quest Do it Yourself 14070
struct KezanDeadbeatsAI : public ScriptedAI
{
    KezanDeadbeatsAI(Creature* creature, uint8 markMask)
        : ScriptedAI(creature)
        , m_markMask(markMask)
    { }

    enum
    {
        ACTION_RESPAWN      = 1,

        TALK_AGGRO          = 1,
        TALK_DEFEATED       = 2,

        ORIGINAL_FACTION    = 7,
        DEFEATED_FACTION    = 2159,
    };

    uint8 m_markMask;
    bool defeated;

    void Reset()
    {
        defeated = false;
        me->setFaction(ORIGINAL_FACTION);
        me->SetStandState(UNIT_STAND_STATE_STAND);
    }

    void DamageTaken(Unit* /*done_by*/, uint32 &damage)
    {
        if (me->GetHealth() <= damage)
        {
            damage = 0;

            if (!defeated)
            {
                defeated = true;
                Talk(TALK_DEFEATED);
                me->SetHealth(1);
                me->CombatStop(true);
                me->setFaction(DEFEATED_FACTION);
                me->SetStandState(UNIT_STAND_STATE_KNEEL);

                std::list<HostileReference*> const& attackers = me->getThreatManager().getThreatList();

                if (attackers.empty())
                    return;

                for (std::list<HostileReference*>::const_iterator itr = attackers.begin(); itr != attackers.end(); ++itr)
                {
                    if (Unit* attacker = Unit::GetUnit((*me), (*itr)->getUnitGuid()))
                    {
                        attacker->CombatStop();

                        if (attacker->GetTypeId() == TYPEID_UNIT)
                            attacker->ToCreature()->AI()->EnterEvadeMode();

                        if (Player* player = attacker->ToPlayer())
                        {
                            //player->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, m_markMask);
                            player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                        }
                    }
                }

                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_RESPAWN), me->m_Events.CalculateTime(5000));
            }
        }
    }

    void DoAction(int32 const action) final
    {
        if (action == ACTION_RESPAWN)
        {
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            me->NearTeleportTo(x, y, z, o);
            me->Respawn(true);
        }
    }

    void EnterCombat(Unit* /*who*/)
    {
        Talk(TALK_AGGRO);
    }

    void UpdateAI(uint32 const diff)
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

class npc_kezan_bruno_flameretardant : public CreatureScript
{
    public:
        npc_kezan_bruno_flameretardant() : CreatureScript("npc_kezan_bruno_flameretardant") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new KezanDeadbeatsAI (creature, MARK_MASK_BRUNO);
        }
};

class npc_kezan_frankie_gearslipper : public CreatureScript
{
    public:
        npc_kezan_frankie_gearslipper() : CreatureScript("npc_kezan_frankie_gearslipper") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kezan_frankie_gearslipperAI (creature);
        }

        struct npc_kezan_frankie_gearslipperAI : public KezanDeadbeatsAI
        {
            npc_kezan_frankie_gearslipperAI(Creature* creature) : KezanDeadbeatsAI(creature, MARK_MASK_FRANKIE) { }

            enum
            {
                EVENT_THROW         = 1,
                SPELL_THROW_GEARS   = 75775,
            };

            EventMap events;

            void Reset()
            {
                events.Reset();
                KezanDeadbeatsAI::Reset();
            }

            void EnterCombat(Unit* who)
            {
                KezanDeadbeatsAI::EnterCombat(who);
                events.ScheduleEvent(EVENT_THROW, urand(2000, 4000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_THROW)
                {
                    me->CastSpell(me->GetVictim(), SPELL_THROW_GEARS, false);
                    events.ScheduleEvent(EVENT_THROW, urand(3500, 7000));
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_jack_the_hammer : public CreatureScript
{
    public:
        npc_kezan_jack_the_hammer() : CreatureScript("npc_kezan_jack_the_hammer") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public KezanDeadbeatsAI
        {
            creature_script_impl(Creature* creature) : KezanDeadbeatsAI(creature, MARK_MASK_JACK) { }

            enum
            {
                EVENT_KNOCKBACK = 1,
                SPELL_KNOCKBACK = 75986,
            };

            EventMap events;

            void Reset()
            {
                events.Reset();
                KezanDeadbeatsAI::Reset();
            }

            void EnterCombat(Unit* who)
            {
                KezanDeadbeatsAI::EnterCombat(who);
                events.ScheduleEvent(EVENT_KNOCKBACK, urand(2000, 4000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_KNOCKBACK)
                {
                    me->CastSpell(me->GetVictim(), SPELL_KNOCKBACK, false);
                    events.ScheduleEvent(EVENT_KNOCKBACK, urand(3500, 7000));
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_sudsy_magee : public CreatureScript
{
    public:
        npc_kezan_sudsy_magee() : CreatureScript("npc_kezan_sudsy_magee") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public KezanDeadbeatsAI
        {
            creature_script_impl(Creature* creature) : KezanDeadbeatsAI(creature, MARK_MASK_SUDSY) { }

            enum
            {
                EVENT_FROSTBOLT     = 1,
                EVENT_BUBBLE_BLAST  = 2,

                SPELL_FROSTBOLT     = 75761,
                SPELL_BUBBLE_BLAST  = 9672,
            };

            EventMap events;

            void Reset()
            {
                events.Reset();
                KezanDeadbeatsAI::Reset();
            }

            void EnterCombat(Unit* who)
            {
                KezanDeadbeatsAI::EnterCombat(who);
                events.ScheduleEvent(EVENT_FROSTBOLT, 0);
                events.ScheduleEvent(EVENT_BUBBLE_BLAST, urand(2500, 5000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FROSTBOLT:
                            me->CastSpell(me->GetVictim(), SPELL_FROSTBOLT, false);
                            events.ScheduleEvent(EVENT_FROSTBOLT, 3500);
                            break;
                        case EVENT_BUBBLE_BLAST:
                            me->CastSpell(me->GetVictim(), SPELL_BUBBLE_BLAST, false);
                            events.ScheduleEvent(EVENT_BUBBLE_BLAST, urand(3500, 7000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

// Quests: Off to the Bank 26711, 26712 & The New You 14110, 14109
enum
{
    SZABO_MENU_ID_1                 = 14700,
    SZABO_MENU_ID_2                 = 14701,
    MISSA_MENU_ID_1                 = 14702,
    MISSA_MENU_ID_2                 = 14703,
    GAPPY_MENU_ID_1                 = 14704,
    GAPPY_MENU_ID_2                 = 14705,
};

class npc_kezan_chip_endale : public CreatureScript
{
    public:
        npc_kezan_chip_endale() : CreatureScript("npc_kezan_chip_endale") { }

    private:
        enum
        {
            SAY_BANK    = 1,
            SAY_PARTY   = 2,
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getGender() == GENDER_MALE)
            {
                player->SEND_GOSSIP_MENU(14694, creature->GetGUID());
                return true;
            }
            else if (creature->GetPhaseMask() & 1024)
            {
                player->SEND_GOSSIP_MENU(17578, creature->GetGUID());
                return true;
            }

            return false;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_OFF_TO_THE_BANK_FEMALE:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_BANK, player->GetGUID(), true);
                    }
                    break;
                case QUEST_LIFE_OF_THE_PARTY_FEMALE:
                    {
                        player->CastSpell(player, SPELL_AWESOME_PARTY_ENSEMBLE, false);
                        player->CastSpell(player, SPELL_LOTP_OUTFIT_SECONDARY, false);
                        player->CastSpell(player, SPELL_LOTP_OUTFIT_FEMALE, false);
                        player->CastSpell(player, SPELL_LOTP_PAPARAZZI, false);
                        player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_1, false);
                        player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_7);

                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_PARTY, player->GetGUID(), true);
                    }
                    break;
            }

            return true;
        }
};

class npc_kezan_candy_cane : public CreatureScript
{
    public:
        npc_kezan_candy_cane() : CreatureScript("npc_kezan_candy_cane") { }

    private:
        enum
        {
            SAY_BANK    = 1,
            SAY_PARTY   = 2,
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getGender() == GENDER_FEMALE)
            {
                player->SEND_GOSSIP_MENU(14693, creature->GetGUID());
                return true;
            }
            else if (creature->GetPhaseMask() & 1024)
            {
                player->SEND_GOSSIP_MENU(17577, creature->GetGUID());
                return true;
            }

            return false;
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_OFF_TO_THE_BANK_MALE:
                    {
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_BANK, player->GetGUID(), true);
                    }
                    break;
                case QUEST_LIFE_OF_THE_PARTY_MALE:
                    {
                        player->CastSpell(player, SPELL_AWESOME_PARTY_ENSEMBLE, false);
                        player->CastSpell(player, SPELL_LOTP_OUTFIT_SECONDARY, false);
                        player->CastSpell(player, SPELL_LOTP_OUTFIT_MALE, false);
                        player->CastSpell(player, SPELL_LOTP_PAPARAZZI, false);
                        player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_1, false);
                        player->RemoveAura(SPELL_QUEST_INVISIBILITY_DETECTION_7);

                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_PARTY, player->GetGUID(), true);
                    }
                    break;
            }

            return true;
        }
};

class npc_kezan_fbok_bank_teller : public CreatureScript
{
    public:
        npc_kezan_fbok_bank_teller() : CreatureScript("npc_kezan_fbok_bank_teller") { }

    private:
        enum
        {
            FBOK_BANK_TELLER_SAY_COOL   = 1,
            FBOK_BANK_TELLER_SAY_NEXT   = 2,

            EVENT_SAY_NEXT              = 1,

            NPC_FBOK_BANK_TELLER        = 35120,
        };

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_OFF_TO_THE_BANK_FEMALE:
                case QUEST_OFF_TO_THE_BANK_MALE:
                {
                    if (creature->IsAIEnabled)
                        creature->AI()->Talk(FBOK_BANK_TELLER_SAY_COOL, player->GetGUID(), true);
                }
            }

            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void InitializeAI()
            {
                if (me->GetPhaseMask() < 3)
                    events.ScheduleEvent(EVENT_SAY_NEXT, urand(5000, 10000));
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_SAY_NEXT)
                {
                    Talk(FBOK_BANK_TELLER_SAY_NEXT);
                    events.ScheduleEvent(EVENT_SAY_NEXT, urand(25000, 35000));
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

#define NEW_OUTFIT  "Szabo, I need a hip, new outfit for the party I'm throwing!"
#define COOL_SHADES "Set me up with the phattest, shiniest bling you got!"
#define SHINY_BLING "I need some cool shades. What will two stacks of macaroons get me?"

enum
{
    SPELL_CREATE_HIP_NEW_OUTFIT                = 66781,
    SPELL_CREATE_COOL_SHADES                   = 66782,
    SPELL_CREATE_SHINY_BLING                   = 66780,

    CITIZEN_SAY_SZABO_SO_COOL                   = 2,
};

class npc_kezan_szabo : public CreatureScript
{
    public:
        npc_kezan_szabo() : CreatureScript("npc_kezan_szabo") { }

    private:
        bool OnGossipHello(Player* player, Creature* creature)
        {
            uint32 textID = 14701;

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_INCOMPLETE) &&
                !player->HasItemCount(ITEM_NEW_OUTFIT, 1) && player->HasItemCount(47044, 3))
            {
                textID = 14700;
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NEW_OUTFIT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            }

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_COMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_COMPLETE) ||
                player->HasItemCount(ITEM_NEW_OUTFIT, 1))
                textID = 14711;

            player->SEND_GOSSIP_MENU(textID, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                player->SEND_GOSSIP_MENU(14702, creature->GetGUID());
                player->CastSpell(player, SPELL_CREATE_HIP_NEW_OUTFIT, false);
                //player->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, MARK_MASK_SZABO);

                if (Creature* citizen = creature->FindNearestCreature(NPC_KEZAN_CITIZEN, 30.f))
                    if (citizen->IsAIEnabled)
                        citizen->AI()->Talk(CITIZEN_SAY_SZABO_SO_COOL, player->GetGUID(), true);
            }

            return true;
        }
};

class npc_kezan_gappy_silvertooth : public CreatureScript
{
    public:
        npc_kezan_gappy_silvertooth() : CreatureScript("npc_kezan_gappy_silvertooth") { }

    private:
        bool OnGossipHello(Player* player, Creature* creature)
        {
            uint32 textID = 14699;

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_INCOMPLETE) &&
                !player->HasItemCount(ITEM_SHINY_BLING, 1) && player->HasItemCount(47044, 5))
            {
                textID = 14697;
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, SHINY_BLING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            }

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_COMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_COMPLETE) ||
                player->HasItemCount(ITEM_SHINY_BLING, 1))
                textID = 14709;

            player->SEND_GOSSIP_MENU(textID, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                player->SEND_GOSSIP_MENU(14698, creature->GetGUID());
                player->CastSpell(player, SPELL_CREATE_SHINY_BLING, false);
                //player->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, MARK_MASK_GAPPY);
            }

            return true;
        }
};

class npc_kezan_missa_spekkies : public CreatureScript
{
    public:
        npc_kezan_missa_spekkies() : CreatureScript("npc_kezan_missa_spekkies") { }

    private:
        bool OnGossipHello(Player* player, Creature* creature)
        {
            uint32 textID = 14704;

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_INCOMPLETE) &&
                !player->HasItemCount(ITEM_COOL_SHADES, 1) && player->HasItemCount(47044, 2))
            {
                textID = 14703;
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, COOL_SHADES, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            }

            if ((player->GetQuestStatus(QUEST_THE_NEW_YOU_FEMALE) == QUEST_STATUS_COMPLETE ||
                player->GetQuestStatus(QUEST_THE_NEW_YOU_MALE) == QUEST_STATUS_COMPLETE) ||
                player->HasItemCount(ITEM_COOL_SHADES, 1))
                textID = 14710;

            player->SEND_GOSSIP_MENU(textID, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                player->SEND_GOSSIP_MENU(14705, creature->GetGUID());
                player->CastSpell(player, SPELL_CREATE_COOL_SHADES, false);
                //player->RemoveByteFlag(PLAYER_FIELD_BYTES2, 3, MARK_MASK_MISSA);
            }

            return true;
        }
};

// Quests Life of the Party 14113, 14153
enum
{
    TYPE_BUBBLY                     = 1,
    TYPE_BUCKET                     = 2,
    TYPE_DANCE                      = 3,
    TYPE_FIREWORKS                  = 4,
    TYPE_HORS_DOEUVRES              = 5,

    SPELL_BUBBLY                    = 66909,
    SPELL_BUCKET                    = 66910,
    SPELL_DANCE                     = 66911,
    SPELL_FIREWORKS                 = 66912,
    SPELL_HORS_DOEUVRES             = 66913,

    ACTION_BUBBLY                   = -1,
    ACTION_BUCKET                   = -2,
    ACTION_DANCE                    = -3,
    ACTION_FIREWORKS                = -4,
    ACTION_HORS_DOEUVRES            = -5,
    ACTION_PLEASURE                 = -6,

    AURA_HAPPY_PARTYGOER            = 66916,
    AURA_PARTYGOER_BUBBLY           = 75042,
    AURA_PARTYGOER_BUCKET           = 75044,
    AURA_DRUNKEN_STUN               = 46957,
    AURA_DRUNKEN_INTOXICATION       = 55664,
    AURA_PARTYGOER_DANCE            = 75046,
    AURA_PARTYGOER_FIREWORKS        = 75048,
    AURA_PARTYGOER_HORS_DOEUVRES    = 75050,

    VIRTUAL_ITEM_BUBBLY             = 2718,
    VIRTUAL_ITEM_HORS_DOEUVRES      = 2202,
	VIRTUAL_ITEM_FIREWORKS          = 9701,
};

class npc_kezan_partygoer : public CreatureScript
{
    public:
        npc_kezan_partygoer() : CreatureScript("npc_kezan_partygoer") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_TALK                  = 1,
                EVENT_RESET                 = 2,

                SAY_NEED_HORS_DOEUVRES      = 1,
                SAY_NEED_BUBBLY             = 2,
                SAY_NEED_FIREWORKS          = 3,
                SAY_NEED_BUCKET             = 4,
                SAY_NEED_DANCE              = 5,
            };

            EventMap events;

            void InitializeAI()
            {
                InitPartygoer();
                events.ScheduleEvent(EVENT_TALK, urand(10000, 40000));
            }

            void InitPartygoer()
            {
                me->RemoveAllAuras();
                uint8 roll = urand(TYPE_BUBBLY, TYPE_HORS_DOEUVRES);

                switch (roll)
                {
                    case TYPE_BUBBLY:
                        me->AddAura(AURA_PARTYGOER_BUBBLY, me);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, VIRTUAL_ITEM_BUBBLY);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_EAT_NO_SHEATHE);
                        break;
                    case TYPE_BUCKET:
                        me->AddAura(AURA_PARTYGOER_BUCKET, me);
                        me->AddAura(AURA_DRUNKEN_STUN, me);
                        me->AddAura(AURA_DRUNKEN_INTOXICATION, me);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                        break;
                    case TYPE_DANCE:
                        me->AddAura(AURA_PARTYGOER_DANCE, me);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DANCE);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                        break;
                    case TYPE_FIREWORKS:
                        me->AddAura(AURA_PARTYGOER_FIREWORKS, me);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, VIRTUAL_ITEM_FIREWORKS);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                        break;
                    case TYPE_HORS_DOEUVRES:
                        me->AddAura(AURA_PARTYGOER_HORS_DOEUVRES, me);
                        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, VIRTUAL_ITEM_HORS_DOEUVRES);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_EAT_NO_SHEATHE);
                        break;
                }
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_PLEASURE)
                {
                    events.CancelEvent(EVENT_TALK);
                    events.ScheduleEvent(EVENT_RESET, 30000);
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK:
                            {
                                if (me->HasAura(AURA_HAPPY_PARTYGOER))
                                    return;

                                uint8 roll = urand(0, 1);

                                if (me->HasAura(AURA_PARTYGOER_BUBBLY))
                                    Talk(SAY_NEED_BUBBLY);

                                if (me->HasAura(AURA_PARTYGOER_BUCKET))
                                    Talk(SAY_NEED_BUCKET);

                                if (me->HasAura(AURA_PARTYGOER_DANCE))
                                    Talk(SAY_NEED_DANCE);

                                if (me->HasAura(AURA_PARTYGOER_FIREWORKS))
                                    Talk(SAY_NEED_FIREWORKS);

                                if (me->HasAura(AURA_PARTYGOER_HORS_DOEUVRES))
                                    Talk(SAY_NEED_HORS_DOEUVRES);

                                events.ScheduleEvent(EVENT_TALK, urand(25000, 75000));
                            }
                            break;
                        case EVENT_RESET:
                            InitPartygoer();
                            events.ScheduleEvent(EVENT_TALK, urand(10000, 40000));
                            break;
                    }
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_kezan_party_inform_ai : public SpellScriptLoader
{
    public:
        spell_kezan_party_inform_ai(const char* scriptName, int8 actionId)
            : SpellScriptLoader(scriptName)
            , m_actionId(actionId)
        { }

        int8 m_actionId;

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl);

        public:
            spell_script_impl(int8 actionId)
                : m_actionId(actionId)
            { }

        private:
            const int8 m_actionId;

            enum
            {
                NPC_KEZAN_PARTYGOER_MALE            = 35175,

                SPELL_PARTYGOER_BUBBLY              = 75122,
                SPELL_PARTYGOER_SUMMON_BUCKET       = 66931,
                SPELL_PARTYGOER_VOMIT               = 43391,
                SPELL_PARTYGOER_SUMMON_DISCO_BALL   = 66930,
                SPELL_PARTYGOER_DANCE               = 75123,
                SPELL_PARTYGOER_HORS_DOEUVRES       = 75124,
                SPELL_PARTYGOER_FIREWORKS_BLUE      = 66917,
                SPELL_PARTYGOER_FIREWORKS_GREEN     = 66918,
                SPELL_PARTYGOER_FIREWORKS_RED       = 66919,

                SAY_THANKS_HORS_DOEUVRES            = 6,
                SAY_THANKS_BUBBLY                   = 7,
                SAY_THANKS_FIREWORKS                = 8,
                SAY_THANKS_BUCKET                   = 9,
                SAY_THANKS_DANCE                    = 10,
            };

            SpellCastResult CheckCast()
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    switch (m_actionId)
                    {
                        case ACTION_BUBBLY:
                            {
                                if (target->HasAura(AURA_PARTYGOER_BUBBLY))
                                    return SPELL_CAST_OK;
                            }
                            break;
                        case ACTION_BUCKET:
                            {
                                if (target->HasAura(AURA_PARTYGOER_BUCKET))
                                    return SPELL_CAST_OK;
                            }
                            break;
                        case ACTION_DANCE:
                            {
                                if (target->HasAura(AURA_PARTYGOER_DANCE))
                                    return SPELL_CAST_OK;
                            }
                            break;
                        case ACTION_FIREWORKS:
                            {
                                if (target->HasAura(AURA_PARTYGOER_FIREWORKS))
                                    return SPELL_CAST_OK;
                            }
                            break;
                        case ACTION_HORS_DOEUVRES:
                            {
                                if (target->HasAura(AURA_PARTYGOER_HORS_DOEUVRES))
                                    return SPELL_CAST_OK;
                            }
                            break;
                    }
                }

                return SPELL_FAILED_BAD_TARGETS;
            }

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* partygoer = GetHitCreature();
                Unit* caster = GetCaster();

                if (!(caster && partygoer && caster->GetTypeId() == TYPEID_PLAYER && partygoer->IsAIEnabled && !partygoer->HasAura(AURA_HAPPY_PARTYGOER)))
                    return;

                if (Player* player = caster->ToPlayer())
                {
                    switch (m_actionId)
                    {
                        case ACTION_BUBBLY:
                            {
                                if (partygoer->HasAura(AURA_PARTYGOER_BUBBLY))
                                {
                                    partygoer->RemoveAura(AURA_PARTYGOER_BUBBLY);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_BUBBLY, false);
                                    partygoer->AI()->Talk(SAY_THANKS_BUBBLY, player->GetGUID());
                                }
                            }
                            break;
                        case ACTION_BUCKET:
                            {
                                if (partygoer->HasAura(AURA_PARTYGOER_BUCKET))
                                {
                                    partygoer->RemoveAura(AURA_PARTYGOER_BUCKET);
                                    partygoer->RemoveAura(AURA_DRUNKEN_STUN);
                                    partygoer->RemoveAura(AURA_DRUNKEN_INTOXICATION);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_SUMMON_BUCKET, false);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_VOMIT, false);
                                    partygoer->AI()->Talk(SAY_THANKS_BUCKET, player->GetGUID());
                                }
                            }
                            break;
                        case ACTION_DANCE:
                            {
                                if (partygoer->HasAura(AURA_PARTYGOER_DANCE))
                                {
                                    partygoer->RemoveAura(AURA_PARTYGOER_DANCE);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_SUMMON_DISCO_BALL, false);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_DANCE, false);
                                    player->CastSpell(player, SPELL_PARTYGOER_DANCE, false);
                                    partygoer->AI()->Talk(SAY_THANKS_DANCE, player->GetGUID());
                                }
                            }
                            break;
                        case ACTION_FIREWORKS:
                            {
                                if (partygoer->HasAura(AURA_PARTYGOER_FIREWORKS))
                                {
                                    partygoer->RemoveAura(AURA_PARTYGOER_FIREWORKS);
                                    player->CastSpell(player, SPELL_PARTYGOER_FIREWORKS_BLUE, false);
                                    player->CastSpell(player, SPELL_PARTYGOER_FIREWORKS_GREEN, false);
                                    player->CastSpell(player, SPELL_PARTYGOER_FIREWORKS_RED, false);
                                    partygoer->AI()->Talk(SAY_THANKS_FIREWORKS, player->GetGUID());
                                }
                            }
                            break;
                        case ACTION_HORS_DOEUVRES:
                            {
                                if (partygoer->HasAura(AURA_PARTYGOER_HORS_DOEUVRES))
                                {
                                    partygoer->RemoveAura(AURA_PARTYGOER_HORS_DOEUVRES);
                                    partygoer->CastSpell(partygoer, SPELL_PARTYGOER_HORS_DOEUVRES, false);
                                    partygoer->AI()->Talk(SAY_THANKS_HORS_DOEUVRES, player->GetGUID());
                                }
                            }
                            break;
                    }

                    partygoer->AddAura(AURA_HAPPY_PARTYGOER, partygoer);
                    partygoer->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                    partygoer->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                    partygoer->GetAI()->DoAction(ACTION_PLEASURE);
                    player->KilledMonsterCredit(NPC_KEZAN_PARTYGOER_MALE, 0);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_script_impl::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl(m_actionId);
        }
};

class npc_kezan_pirate_party_crasher : public CreatureScript
{
    public:
        npc_kezan_pirate_party_crasher() : CreatureScript("npc_kezan_pirate_party_crasher") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature){ }

            enum
            {
                EVENT_RANDOM_TALK           = 1,
                EVENT_SWASHBUCKLING_SLICE   = 2,

                PIRATE_PARTY_CRASHER_SPEACH = 1,
            };

            EventMap events;
            EventMap commonEvents;

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                commonEvents.ScheduleEvent(EVENT_RANDOM_TALK, urand(20000, 120000));
            }

            void DamageTaken(Unit* /*done_by*/, uint32 & /*damage*/)
            {
                if (me->GetReactState() == REACT_PASSIVE)
                    me->SetReactState(REACT_AGGRESSIVE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                commonEvents.Reset();
                events.ScheduleEvent(EVENT_SWASHBUCKLING_SLICE, urand(2000, 5000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                {
                    commonEvents.Update(diff);

                    if (commonEvents.ExecuteEvent() == EVENT_RANDOM_TALK)
                    {
                        Talk(PIRATE_PARTY_CRASHER_SPEACH);
                        commonEvents.ScheduleEvent(EVENT_RANDOM_TALK, urand(20000, 120000));
                    }

                    return;
                }

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_SWASHBUCKLING_SLICE)
                {
                    me->CastSpell(me->GetVictim(), 75361, false);
                    events.ScheduleEvent(EVENT_SWASHBUCKLING_SLICE, urand(2000, 5000));
                }

                DoMeleeAttackIfReady();
            }
        };
 };

class npc_kezan_ktc_waiter : public CreatureScript
{
    public:
        npc_kezan_ktc_waiter() : CreatureScript("npc_kezan_ktc_waiter") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature){ }

            enum
            {
                EVENT_FIND_PIRATE           = 1,

                NPC_PIRATE_PARTY_CRASHER    = 35200,
            };

            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_FIND_PIRATE, 1000);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                {
                    events.Update(diff);

                    if (events.ExecuteEvent() == EVENT_FIND_PIRATE)
                    {
                        if (Creature* pirate = me->FindNearestCreature(NPC_PIRATE_PARTY_CRASHER, 20.f))
                        {
                            if (pirate->IsAIEnabled && !pirate->IsInCombat())
                            {
                                pirate->AI()->AttackStart(me);
                                me->CombatStart(pirate);
                                pirate->CombatStart(me);
                                return;
                            }
                        }

                        events.ScheduleEvent(EVENT_FIND_PIRATE, 1000);
                    }

                    return;
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_kezan_trade_prince_gallywix : public CreatureScript
{
    public:
        npc_kezan_trade_prince_gallywix() : CreatureScript("npc_kezan_trade_prince_gallywix") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_A_BAZILLION_MACAROONS)
            {
                player->AddAura(94656, player);

                if (Creature* caster = player->SummonCreature(37748, -8431.653f, 1350.738f, 129.1189f, 0, TEMPSUMMON_TIMED_DESPAWN, 5000))
                {
                    caster->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, player->GetGUID());
                    caster->CastSpell(caster, 70472, false);
                }
            }

            return true;
        }

        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
        {
            switch (quest->GetQuestId())
            {
                case QUEST_THE_UNINVITED_GUEST:
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_3);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_4, false);
                    player->CastSpell(player, SPELL_QUEST_INVISIBILITY_DETECTION_5, false);
                    break;
                case QUEST_LIFE_SAVINGS:
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_6);
                    player->CastSpell(player, 91847, false);
                    break;
            }

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            switch (creature->GetPhaseMask())
            {
                case 2048:
                    player->SEND_GOSSIP_MENU(15808, creature->GetGUID());
                    return true;
                case 28672:
                    player->PrepareQuestMenu(creature->GetGUID());
                    player->SEND_GOSSIP_MENU(17818, creature->GetGUID());
                    return true;
            }

            return false;
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RAND_TALK     = 1,

                SAY_DEMOTIONS       = 1,
                SAY_RAND_PHASE_1    = 2,
                SAY_RAND_PHASE_END  = 3,
            };

            EventMap events;

            void InitializeAI()
            {
                if (me->GetPhaseMask() == 1032)
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    return;
                }

                me->setActive(true);
                events.ScheduleEvent(EVENT_RAND_TALK, urand(5000, 25000));
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RAND_TALK)
                {
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();

                    if (players.isEmpty())
                        return;

                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    {
                        if (Player* player = itr->GetSource())
                        {
                            if (me->InSamePhase(player) && me->GetExactDist2dSq(player) < 2500.f)
                            {
                                switch (me->GetPhaseMask())
                                {
                                    case 1:
                                        {
                                            if (!urand(0,5) && player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) != QUEST_STATUS_COMPLETE)
                                                Talk(SAY_DEMOTIONS, player->GetGUID(), true);
                                            else
                                                Talk(SAY_RAND_PHASE_1, player->GetGUID(), true);
                                        }
                                        break;
                                    default:
                                        Talk(SAY_RAND_PHASE_END, player->GetGUID(), true);
                                        break;
                                }
                            }
                        }
                    }

                    events.ScheduleEvent(EVENT_RAND_TALK, urand(25000, 50000));
                }
            }
        };
};

//class movie_kezan_life_savings : public MovieScript
//{
//    public:
//        movie_kezan_life_savings() : MovieScript("movie_kezan_life_savings") { }
//
//    private:
//        void OnMovieEnd(Player* player, uint32 const /*movieId*/)
//        {
//            player->RemoveAura(94656);
//            player->RemoveAurasByType(SPELL_AURA_PHASE);
//            player->RemoveAurasByType(SPELL_AURA_MOD_INVISIBILITY_DETECT);
//            player->CastSpell(player, 74100, false);
//            player->CastSpell(player, 69010, false);
//            player->CastSpell(player, 67851, false);
//            player->CastSpell(player, 69283, false);
//            player->CastSpell((Unit*)NULL, 69043, false);
//            player->CastSpell((Unit*)NULL, 69018, false);
//            player->SaveToDB();
//        }
//};

// Quests The Great Bank Heist 14122
enum
{
    ACTION_INFINIFOLD_LOCKPICK  = 1,
    ACTION_BLASTCRACKERS        = 2,
    ACTION_KAJAMITE_DRILL       = 3,
    ACTION_AMAZING_G_RAY        = 4,
    ACTION_EAR_O_SCOPE          = 5,
    ACTION_TIME_OFF             = 6,
};

class npc_kezan_first_bank_of_kezan_vault : public CreatureScript
{
    public:
        npc_kezan_first_bank_of_kezan_vault() : CreatureScript("npc_kezan_first_bank_of_kezan_vault") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                VAULT_SAY_BREAKING                      = 1,
                VAULT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT  = 2,
                VAULT_SAY_VAULT_WILL_BE_CRACKED         = 3,
                VAULT_SAY_GOOD_LUCK                     = 4,
                VAULT_SAY_USE_INFINIFOLD_LOCKPICK       = 5,
                VAULT_SAY_USE_BLASTCRACKERS             = 6,
                VAULT_SAY_USE_KAJAMITE_DRILL            = 7,
                VAULT_SAY_USE_AMAZING_G_RAY             = 8,
                VAULT_SAY_USE_EAR_O_SCOPE               = 9,
                VAULT_SAY_SUCCESS                       = 10,
                VAULT_SAY_CORRECT                       = 11,
                VAULT_SAY_EMPTY_TEXT_CORRECT            = 12,
                VAULT_SAY_INCORRECT                     = 13,
                VAULT_SAY_EMPTY_TEXT_INCORRECT          = 14,
                VAULT_SAY_IS_NO_TIME                    = 15,

                SPELL_INFINIFOLD_LOCKPICK               = 67525,
                SPELL_BLASTCRACKERS                     = 67508,
                SPELL_KAJAMITE_DRILL                    = 67522,
                SPELL_AMAZING_G_RAY                     = 67526,
                SPELL_EAR_O_SCOPE                       = 67524,
                SPELL_TIMER                             = 67502,
                SPELL_TGBH_BUNNY_DRILL_AURA             = 67495,
                SPELL_TGBH_BUNNY_EXPLOSIVES_AURA        = 67496,
                SPELL_TGBH_BUNNY_LISTEN_AURA            = 67497,
                SPELL_TGBH_BUNNY_LOCKPICK_AURA          = 67498,
                SPELL_TGBH_BUNNY_G_RAY_AURA             = 67499,
                SPELL_TGBH_POWER_CORRECT                = 67493,
                SPELL_TGBH_POWER_INCORRECT              = 67494,

                ROLL_INFINIFOLD_LOCKPICK                = 1,
                ROLL_BLASTCRACKERS                      = 2,
                ROLL_KAJAMITE_DRILL                     = 3,
                ROLL_AMAZING_G_RAY                      = 4,
                ROLL_EAR_O_SCOPE                        = 5,

                EVENT_SAY_BREAKING                      = 1,
                EVENT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT  = 2,
                EVENT_SAY_VAULT_WILL_BE_CRACKED         = 3,
                EVENT_SAY_GOOD_LUCK                     = 4,
                EVENT_NEXT_TOOL_FOR_CRACKING            = 5,
                EVENT_DECREASE_ENERGY                   = 6,
            };

            EventMap events;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->setRegeneratingMana(false);
                me->setPowerType(POWER_MANA);
                me->SetMaxPower(POWER_MANA, 100);
                me->SetPower(POWER_MANA, 0);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->SetReactState(REACT_PASSIVE);

                if (Player* player = summoner->ToPlayer())
                    player->KilledMonsterCredit(me->GetEntry(), 0);

                events.ScheduleEvent(EVENT_SAY_BREAKING, 3000);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_INFINIFOLD_LOCKPICK:
                        ToolUsed(me->HasAura(SPELL_TGBH_BUNNY_LOCKPICK_AURA));
                        break;
                    case ACTION_BLASTCRACKERS:
                        ToolUsed(me->HasAura(SPELL_TGBH_BUNNY_EXPLOSIVES_AURA));
                        break;
                    case ACTION_KAJAMITE_DRILL:
                        ToolUsed(me->HasAura(SPELL_TGBH_BUNNY_DRILL_AURA));
                        break;
                    case ACTION_AMAZING_G_RAY:
                        ToolUsed(me->HasAura(SPELL_TGBH_BUNNY_G_RAY_AURA));
                        break;
                    case ACTION_EAR_O_SCOPE:
                        ToolUsed(me->HasAura(SPELL_TGBH_BUNNY_LISTEN_AURA));
                        break;
                    case ACTION_TIME_OFF:
                        me->CastSpell(me, SPELL_TGBH_POWER_INCORRECT, false);
                        Talk(VAULT_SAY_IS_NO_TIME, me->ToTempSummon()->GetSummonerGUID(), true);
                        Talk(VAULT_SAY_EMPTY_TEXT_INCORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                        RemoveEventAuras();
                        events.ScheduleEvent(EVENT_NEXT_TOOL_FOR_CRACKING, 1000);
                        break;
                }
            }

            void ToolUsed(bool correct)
            {
                if (correct)
                {
                    me->CastSpell(me, SPELL_TGBH_POWER_CORRECT, false);
                    Talk(VAULT_SAY_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                    Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);

                    if (me->GetPower(POWER_MANA) == 100)
                    {
                        Talk(VAULT_SAY_SUCCESS, me->ToTempSummon()->GetSummonerGUID(), true);

                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        {
                            me->CastSpell(summoner, 67492, true);
                            me->CastSpell(summoner, 67579, false);
                        }
                    }
                }
                else
                {
                    me->CastSpell(me, SPELL_TGBH_POWER_INCORRECT, false);
                    Talk(VAULT_SAY_INCORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                    Talk(VAULT_SAY_EMPTY_TEXT_INCORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                }

                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    summoner->RemoveAura(SPELL_TIMER);

                RemoveEventAuras();
                events.ScheduleEvent(EVENT_NEXT_TOOL_FOR_CRACKING, 1000);
                events.RescheduleEvent(EVENT_DECREASE_ENERGY, 4000);
            }

            void SelectNextTool()
            {
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    me->CastSpell(summoner, SPELL_TIMER, true);

                uint8 roll = urand(ROLL_INFINIFOLD_LOCKPICK, ROLL_EAR_O_SCOPE);

                switch (roll)
                {
                    case ROLL_INFINIFOLD_LOCKPICK:
                        Talk(VAULT_SAY_USE_INFINIFOLD_LOCKPICK, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->CastSpell(me, SPELL_TGBH_BUNNY_LOCKPICK_AURA, false);
                        break;
                    case ROLL_BLASTCRACKERS:
                        Talk(VAULT_SAY_USE_BLASTCRACKERS, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->CastSpell(me, SPELL_TGBH_BUNNY_EXPLOSIVES_AURA, false);
                        break;
                    case ROLL_KAJAMITE_DRILL:
                        Talk(VAULT_SAY_USE_KAJAMITE_DRILL, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->CastSpell(me, SPELL_TGBH_BUNNY_DRILL_AURA, false);
                        break;
                    case ROLL_AMAZING_G_RAY:
                        Talk(VAULT_SAY_USE_AMAZING_G_RAY, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->CastSpell(me, SPELL_TGBH_BUNNY_G_RAY_AURA, false);
                        break;
                    case ROLL_EAR_O_SCOPE:
                        Talk(VAULT_SAY_USE_EAR_O_SCOPE, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->CastSpell(me, SPELL_TGBH_BUNNY_LISTEN_AURA, false);
                        break;
                }

                Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
            }

            void RemoveEventAuras()
            {
                me->RemoveAura(SPELL_TIMER);
                me->RemoveAura(SPELL_TGBH_BUNNY_LOCKPICK_AURA);
                me->RemoveAura(SPELL_TGBH_BUNNY_EXPLOSIVES_AURA);
                me->RemoveAura(SPELL_TGBH_BUNNY_DRILL_AURA);
                me->RemoveAura(SPELL_TGBH_BUNNY_G_RAY_AURA);
                me->RemoveAura(SPELL_TGBH_BUNNY_LISTEN_AURA);
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SAY_BREAKING:
                            Talk(VAULT_SAY_BREAKING, me->ToTempSummon()->GetSummonerGUID(), true);
                            Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT, 3500);
                            break;
                        case EVENT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT:
                            Talk(VAULT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT, me->ToTempSummon()->GetSummonerGUID(), true);
                            Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_SAY_VAULT_WILL_BE_CRACKED, 3500);
                            break;
                        case EVENT_SAY_VAULT_WILL_BE_CRACKED:
                            Talk(VAULT_SAY_VAULT_WILL_BE_CRACKED, me->ToTempSummon()->GetSummonerGUID(), true);
                            Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_SAY_GOOD_LUCK, 5000);
                            break;
                        case EVENT_SAY_GOOD_LUCK:
                            Talk(VAULT_SAY_GOOD_LUCK, me->ToTempSummon()->GetSummonerGUID(), true);
                            Talk(VAULT_SAY_EMPTY_TEXT_CORRECT, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_NEXT_TOOL_FOR_CRACKING, 2000);
                            events.ScheduleEvent(EVENT_DECREASE_ENERGY, 5000);
                            break;
                        case EVENT_NEXT_TOOL_FOR_CRACKING:
                            SelectNextTool();
                            break;
                        case EVENT_DECREASE_ENERGY:
                            me->ModifyPower(POWER_MANA, -5);
                            events.ScheduleEvent(EVENT_DECREASE_ENERGY, 2500);
                            break;
                    }
                }
            }
        };
};

class go_kezan_first_bank_of_kezan_vault : public GameObjectScript
{
    public:
        go_kezan_first_bank_of_kezan_vault() : GameObjectScript("go_kezan_first_bank_of_kezan_vault"){ }

    private:
        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            return player->GetQuestStatus(QUEST_THE_GREAT_BANK_HEIST) != QUEST_STATUS_INCOMPLETE;
        }
};

class spell_kezan_heist_vault_interact : public SpellScriptLoader
{
    public:
        spell_kezan_heist_vault_interact() : SpellScriptLoader("spell_kezan_heist_vault_interact") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                enum
                {
                    SPELL_TGBH_SUMMON_BUNNY_VEHICLE = 67488,
                };

                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_TGBH_SUMMON_BUNNY_VEHICLE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_heist_vehicle_exit_spell : public SpellScriptLoader
{
    public:
        spell_kezan_heist_vehicle_exit_spell() : SpellScriptLoader("spell_kezan_heist_vehicle_exit_spell") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {

                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    target->ExitVehicle();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_heist_inform_ai : public SpellScriptLoader
{
    public:
        spell_kezan_heist_inform_ai(const char* scriptName, int8 actionId)
            : SpellScriptLoader(scriptName)
            , m_actionId(actionId)
        { }

        int8 m_actionId;

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl);

        public:
            spell_script_impl(int8 actionId)
                : m_actionId(actionId)
            { }

        private:
            const int8 m_actionId;

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(m_actionId);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl(m_actionId);
        }
};

class spell_kezan_heist_timer : public SpellScriptLoader
{
    public:
        spell_kezan_heist_timer() : SpellScriptLoader("spell_kezan_heist_timer") { }

    private:
        class aura_script_impl : public AuraScript
        {
            PrepareAuraScript(aura_script_impl)

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                    if (Unit* target = GetTarget())
                        if (target->IsAIEnabled)
                            target->GetAI()->DoAction(ACTION_TIME_OFF);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(aura_script_impl::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new aura_script_impl();
        }
};

// Quests Robbing Hoods 14121
const uint16 LooterRandomEmote[6] =
{
    EMOTE_ONESHOT_APPLAUD,
    EMOTE_ONESHOT_DANCE,
    EMOTE_ONESHOT_RUDE,
    EMOTE_ONESHOT_ROAR,
    EMOTE_ONESHOT_CHEER,
    EMOTE_ONESHOT_LAUGH,
};

class npc_kezan_hired_looter : public CreatureScript
{
    public:
        npc_kezan_hired_looter() : CreatureScript("npc_kezan_hired_looter") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_HOT_ROD_KNOCKBACK             = 66301,
                SPELL_CREATE_STOLEN_LOOT            = 67041,
                SPELL_THROW_SUPER_SPLODY_COCKTAIL   = 67020,

                EVENT_TROW_SUPER_SPLODY_COCKTAIL    = 1,
                EVENT_TROW_EMOTE                    = 2,
                EVENT_SWASHBUCKLING_SLICE           = 3,
                EVENT_DIE                           = 4,

                ACTION_DIE                          = 1,
            };

            EventMap events;
            EventMap commonEvents;
            bool IsDied;

            void Reset()
            {
                IsDied = false;
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                commonEvents.ScheduleEvent(EVENT_TROW_SUPER_SPLODY_COCKTAIL, urand(5000, 15000));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_DIE)
                    me->Kill(me);
            }

            uint32 GetData(uint32 data) const
            {
                if (data == TYPE_KNOCKBACK_STATE)
                    return DATA_KNOCKBACK_DISABLED;

                return 0;
            }

            void SpellHit(Unit* caster, const SpellInfo* spell)
            {
                if (!IsDied && spell->Id == SPELL_HOT_ROD_KNOCKBACK)
                {
                    IsDied = true;
                    me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_DIE), me->m_Events.CalculateTime(500));

                    if (Vehicle* vehicle = caster->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (Player* player = passenger->ToPlayer())
                                if (player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_INCOMPLETE)
                                    me->CastSpell(player, SPELL_CREATE_STOLEN_LOOT, false);
                }
            }

            void DamageTaken(Unit* /*done_by*/, uint32 & /*damage*/)
            {
                if (me->GetReactState() == REACT_PASSIVE)
                    me->SetReactState(REACT_AGGRESSIVE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                commonEvents.Reset();
                events.ScheduleEvent(EVENT_SWASHBUCKLING_SLICE, urand(2000, 5000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                {
                    commonEvents.Update(diff);

                    if (uint32 eventId = commonEvents.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_TROW_SUPER_SPLODY_COCKTAIL:
                                me->CastSpell((Unit*)NULL, SPELL_THROW_SUPER_SPLODY_COCKTAIL, false);
                                commonEvents.ScheduleEvent(EVENT_TROW_EMOTE, 1000);
                                break;
                            case EVENT_TROW_EMOTE:
                                uint8 roll = urand(0, 5);
                                me->HandleEmoteCommand(LooterRandomEmote[roll]);
                                commonEvents.ScheduleEvent(EVENT_TROW_SUPER_SPLODY_COCKTAIL, urand(5000, 15000));
                                break;
                        }
                    }

                    return;
                }

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_SWASHBUCKLING_SLICE)
                {
                    me->CastSpell(me->GetVictim(), 75361, false);
                    events.ScheduleEvent(EVENT_SWASHBUCKLING_SLICE, urand(2000, 5000));
                }

                DoMeleeAttackIfReady();
            }

        };
};

// Quests Waltz Right In 14123
class npc_kezan_villa_mook_disguise : public CreatureScript
{
    public:
        npc_kezan_villa_mook_disguise() : CreatureScript("npc_kezan_villa_mook_disguise") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature){ }

            void OnControlVehicle(Unit* base, int8 /*seatId*/, bool apply)
            {
                if (!apply)
                {
                    if (Player* player = base->ToPlayer())
                        player->m_Events.AddEvent(new Kezan::PersonalPlayerUpdateMookEvent(player), player->m_Events.CalculateTime(1000), true, MOOK_EVENT_ID);

                    me->DespawnOrUnsummon();
                }
            }
        };
};

class spell_kezan_waltz_right_in_dummy_trigger : public SpellScriptLoader
{
    public:
        spell_kezan_waltz_right_in_dummy_trigger() : SpellScriptLoader("spell_kezan_waltz_right_in_dummy_trigger") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex /*effIndex*/)
            {
                static const uint32 MookBeamSpellEntry[5] =
                {
                    66999,
                    91234,
                    91235,
                    91236,
                    91237,
                };

                if (Unit* caster = GetCaster())
                    caster->CastSpell((Unit*)NULL, MookBeamSpellEntry[urand(0, 4)], true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

// Quests Liberate the Kaja'mite 14124
class go_kezan_kajamite_deposit : public GameObjectScript
{
    public:
        go_kezan_kajamite_deposit() : GameObjectScript("go_kezan_kajamite_deposit"){ }

    private:
        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            Position pos;

            for (int i = 0; i < 3; ++i)
            {
                go->GetRandomNearPosition(pos, 3.0f);
                go->SummonGameObject(195492, pos.m_positionX, pos.m_positionY, pos.m_positionZ, pos.m_orientation, 0, 0, 0, 0, 60000);
            }

            return false;
        }
};

// Quest 447 14125
enum
{
    NPC_OVERLOADED_GENERATOR = 37561,
    NPC_STOVE_LEAK = 37590,
    NPC_SMOLDERING_BED = 37594,
    NPC_KEZAN_447_GASBOT = 37598,

    SPELL_OVERLOADED_GENERATOR_VISUAL = 70226,
    SPELL_STOVE_LEAK_VISUAL = 70236,
    SPELL_KEZAN_447_AICAST_GASBOT_MASTER = 70251,
    SPELL_SMOLDERING_BED_VISUAL = 70250,

    CLAIMS_ADJUSTER_YELL_VICTIM = 1,
};

class go_kezan_447_event_gameobject : public GameObjectScript
{
    public:
        go_kezan_447_event_gameobject() : GameObjectScript("go_kezan_447_event_gameobject"){ }

    private:
        bool OnGossipHello(Player* player, GameObject* /*go*/)
        {
            if (!player->HasAura(PHASE_QUEST_ZONE_SPECIFIC_6))
                player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_6, false);

            return false;
        }
};

class npc_kezan_447_gasbot : public CreatureScript
{
    public:
        npc_kezan_447_gasbot() : CreatureScript("npc_kezan_447_gasbot") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kezan_447_gasbotAI(creature);
        }

        struct npc_kezan_447_gasbotAI : public ScriptedAI
        {
            npc_kezan_447_gasbotAI(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                ACTION_START_WALKING    = 1,
                ACTION_BOOM             = 2,
            };

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetPhaseMask(12288, true);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());

                for (int i = 0; i < 4; ++i)
                {
                    if (Creature* target = me->SummonCreature(37599, *me))
                    {
                        target->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                        target->EnterVehicle(me, i);
                    }
                }

                me->CastSpell((Unit*)NULL, 70256, true);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_START_WALKING), me->m_Events.CalculateTime(1000));
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_WALKING:
                        me->GetMotionMaster()->MoveSplinePath(1, false, true, 1.5f, false, false);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_BOOM), me->m_Events.CalculateTime(me->GetSplineDuration()));
                        break;
                    case ACTION_BOOM:
                        me->CastSpell((Unit*)NULL, 70259, true);
                        me->CastSpell((Unit*)NULL, 70260, true);
                        me->RemoveAllAuras();
                        me->SetDisplayId(11686);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->DespawnOrUnsummon(2000);
                        break;
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (!apply)
                    if (Creature* creature = who->ToCreature())
                        creature->DespawnOrUnsummon();
            }
        };
};

class npc_kezan_447_event_creature : public CreatureScript
{
    public:
        npc_kezan_447_event_creature(const char* scriptName, uint32 spellEntry)
            : CreatureScript(scriptName)
            , m_spellEntry(spellEntry)
        { }

    private:
        uint32 m_spellEntry;

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature, m_spellEntry);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature, uint32 spellEntry)
                : ScriptedAI(creature)
                , m_spellEntry(spellEntry)
            { }

            uint32 m_spellEntry;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->CastSpell(me, m_spellEntry, false);
            }
        };
};

class spell_kezan_447_master : public SpellScriptLoader
{
    public:
        spell_kezan_447_master(const char* scriptName, uint32 despawnSpellEntry, uint32 summonSpellEntry)
            : SpellScriptLoader(scriptName)
            , m_despawnSpellEntry(despawnSpellEntry)
            , m_summonSpellEntry(summonSpellEntry)
        { }

        uint32 m_despawnSpellEntry;
        uint32 m_summonSpellEntry;

    private:
        class aura_script_impl : public AuraScript
        {
            PrepareAuraScript(aura_script_impl);

        public:
            aura_script_impl(uint32 despawnSpellEntry, uint32 summonSpellEntry)
                : m_despawnSpellEntry(despawnSpellEntry)
                , m_summonSpellEntry(summonSpellEntry)
            { }

        private:
            uint32 m_despawnSpellEntry;
            uint32 m_summonSpellEntry;

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->CastSpell((Unit*)NULL, m_despawnSpellEntry, false);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->CastSpell((Unit*)NULL, m_summonSpellEntry, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(aura_script_impl::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(aura_script_impl::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new aura_script_impl(m_despawnSpellEntry, m_summonSpellEntry);
        }
};

class spell_kezan_447_aicast_gasbot_master : public SpellScriptLoader
{
    public:
        spell_kezan_447_aicast_gasbot_master() : SpellScriptLoader("spell_kezan_447_aicast_gasbot_master") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void Effect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    QuestStatusMap::iterator itr = player->getQuestStatusMap().find(QUEST_447);

                    if (itr == player->getQuestStatusMap().end())
                        return;

                    QuestStatusData& q_status = itr->second;

                    if (q_status.Status == QUEST_STATUS_INCOMPLETE)
                        for (int i = 0; i < 3; ++i)
                            if (player->GetQuestObjectiveCounter(QUEST_OBJECTIVE_OVERLOAD_DEFECTIVE_GEN + i) == 0)
                                return;

                    player->CastSpell(player, 70254, false);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::Effect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_447_gasbot_gas_stream : public SpellScriptLoader
{
    public:
        spell_kezan_447_gasbot_gas_stream() : SpellScriptLoader("spell_kezan_447_gasbot_gas_stream") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            class SummonerFilter
            {
                public:
                    SummonerFilter(uint64 summonerGUID)
                        : m_summonerGUID(summonerGUID)
                { }

                    bool operator()(WorldObject const *object) const
                    {
                        if (Creature const * creature = object->ToCreature())
                            if (creature->IsSummon())
                                return creature->ToTempSummon()->GetSummonerGUID() != m_summonerGUID;

                        return true;
                    }

                private:
                    uint64 m_summonerGUID;
            };

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (Unit* caster = GetCaster())
                    targets.remove_if(SummonerFilter(caster->GetGUID()));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_script_impl::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class spell_kezan_447_gasbot_scriptcast_to_character : public SpellScriptLoader
{
    public:
        spell_kezan_447_gasbot_scriptcast_to_character() : SpellScriptLoader("spell_kezan_447_gasbot_scriptcast_to_character") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            class AdjusterEvent : public BasicEvent
            {
                public:
                    AdjusterEvent(Player* player)
                        : m_player(player)
                    { }

                private:
                    bool Execute(uint64 /*time*/, uint32 /*diff*/)
                    {
                        enum
                        {
                            CLAIMS_ADJUSTER_YELL_VICTIM = 0,
                        };

                        if (Creature* adjuster = m_player->FindNearestCreature(37602, 50.f))
                            if (adjuster->IsAIEnabled)
                                adjuster->AI()->Talk(CLAIMS_ADJUSTER_YELL_VICTIM, m_player->GetGUID(), true);

                        return true;
                    }

                    Player* m_player;
            };

            void Effect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    player->m_Events.AddEvent(new AdjusterEvent(player), player->m_Events.CalculateTime(500));
                    player->RemoveAura(PHASE_QUEST_ZONE_SPECIFIC_6);
                    player->CastSpell(player, PHASE_QUEST_ZONE_SPECIFIC_7, false);
                    player->KilledMonsterCredit(NPC_KEZAN_447_GASBOT, 0);
                    player->SaveToDB();
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::Effect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class npc_kezan_kaja_cola_balloon : public CreatureScript
{
    public:
        npc_kezan_kaja_cola_balloon() : CreatureScript("npc_kezan_kaja_cola_balloon") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RAND_YELL = 1,
                RANDOM_YELL_ID  = 1,
            };

            EventMap events;

            void InitializeAI()
            {
                me->setActive(true);

                if (me->GetPhaseMask() == 3087)
                {
                    me->setActive(true);
                    me->GetMotionMaster()->MoveSplinePath(1, true, true, 3.5f, true);
                    events.ScheduleEvent(EVENT_RAND_YELL, urand(5000, 10000));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RAND_YELL)
                {
                    sCreatureTextMgr->SendChat(me, RANDOM_YELL_ID, 0, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_ZONE);
                    events.ScheduleEvent(EVENT_RAND_YELL, urand(30000, 60000));
                }
            }
        };
};

// Hobart Grapplehammer, Assistant Greely
enum
{
    // Mechachincken
    HOBART_YELL_PREPARE                     = 1,
    GREELY_SAY_SHEESH                       = 2,
    GREELY_SAY_ONE_MECHACHICKEN             = 3,
    HOBART_SAY_DEAR_GREELY                  = 4,
    GREELY_SIGH                             = 5,
    GREELY_SAY_YES_DOCTOR                   = 6,
    HOBART_SAY_EXCELLENT                    = 7,
    GREELY_SHAKES_HEAD                      = 8,
    HOBART_SAY_THANK_YOU                    = 9,
    HOBART_SAY_HORRIBLE_PROBLEM             = 10,
    HOBART_SAY_GREATEST_GOBLIN              = 11,
    HOBART_SAY_FLIP_THE_SWITCH              = 12,
    GREELY_COUGHS                           = 13,
    GREELY_SAY_AT_THE_CONTROLS              = 14,
    HOBART_SAY_QUITE_RIGHT                  = 15,
    HOBART_SAY_FLIPPING                     = 16,
    HOBART_SAY_CAN_YOU_FEEL                 = 17,
    HOBART_SAY_GROCERY_STORE                = 18,
    HOBART_SAY_FLIPPING_SECOND              = 19,
    HOBART_SAY_WAIT                         = 20,
    GREELY_SAY_YA_THINK                     = 21,
    HOBART_YELL_I_KNOW                      = 22,
    GREELY_YELL_FAR_RIGHT                   = 23,
    HOBART_YELL_I_ALWAYS_LOVED              = 24,
    GREELY_YELL_WHAT                        = 25,
    HOBART_YELL_FLIPPING_THE_OVERRIDE       = 26,
    HOBART_SAY_ARE_WE_STILL_ALIVE           = 27,
    GREELY_SAY_WERE_STILL_ALIVE             = 28,
    HOBART_SAY_WELL_OF_COURSE               = 29,
    GREELY_SAY_IS_THAT_EGG                  = 30,
    HOBART_OPEN_MOUTH                       = 31,
    GREELY_SAY_ALWAYS_LOVED                 = 32,
    HOBART_SAY_MISS_GREELY                  = 33,
    GREELY_BOTH_AGREE                       = 34,
    // Kajaro Erupt
    HOBART_SAY_SKY_IS_FALLING               = 35,
    GREELY_SAY_SKY_IS_FALLING               = 36,
    HOBART_SAY_DEATHWING                    = 37,
    GREELY_SAY_DEATHWING                    = 38,
    HOBART_SAY_PARTY                        = 39,
    GREELY_SAY_PARTY                        = 40,
    HOBART_SAY_SCHEMATICS                   = 41,
    GREELY_SAY_SCHEMATICS                   = 42,
    HOBART_SAY_INGENIOUS_CAP                = 43,
    GREELY_SAY_INGENIOUS_CAP                = 44,
    HOBART_SAY_GRAB_ONLY_THE_IMPORTANT      = 45,
    GREELY_SAY_GRAB_ONLY_THE_IMPORTANT      = 46,
    HOBART_SAY_GET_EVERYTHING_PACKED        = 47,
    GREELY_SAY_GET_EVERYTHING_PACKED        = 48,
    HOBART_SAY_SUBJECT_NINE                 = 49,
    GREELY_SAY_SUBJECT_NINE                 = 40,

    NPC_ASSISTANT_GREELY                    = 48496,
    NPC_HOBART_GRAPPLEHAMMER                = 48494,
    NPC_MICRO_MECHACHICKEN                  = 48519,
    NPC_ELM_GENERAL_PURPOSE_BUNNY           = 24021,

    SPELL_COSMETIC_POLYMORPH_IMPACT_VISUAL  = 65313,
    SPELL_LIGHTNING_IMPACT                  = 89139,
    SPELL_LIGHTNING_BEAM                    = 89138,
    SPELL_MECHACHICKEN_OVERLOAD             = 71423,
    SPELL_MICRO_MECHACHICKEN_GROW           = 89125,
    SPELL_STEALTH                           = 80264,
    SPELL_MECHACHICKEN_EXPLOSION            = 91390,
};

enum
{
    POINT_TESTING_PLATFORM                  = 1,
    POINT_BACK_OF_THE_DOCTOR_1              = 2,
    POINT_RUN_AWAY_FROM_CHICKEN             = 3,
    POINT_BACK_OF_THE_DICTOR_2              = 4,
};

struct KajaroEventType
{
    uint8 hobartTextId;
    uint32 timer;
    uint8 greelyTextId;
};

static const KajaroEventType KajaroEvent[8] =
{
    { HOBART_SAY_SKY_IS_FALLING,          4000, GREELY_SAY_SKY_IS_FALLING },
    { HOBART_SAY_GRAB_ONLY_THE_IMPORTANT, 5000, GREELY_SAY_GRAB_ONLY_THE_IMPORTANT },
    { HOBART_SAY_PARTY,                   4000, GREELY_SAY_PARTY },
    { HOBART_SAY_DEATHWING,               5000, GREELY_SAY_DEATHWING },
    { HOBART_SAY_GET_EVERYTHING_PACKED,   4000, GREELY_SAY_GET_EVERYTHING_PACKED },
    { HOBART_SAY_SUBJECT_NINE,            5000, GREELY_SAY_SUBJECT_NINE },
    { HOBART_SAY_SCHEMATICS,              4000, GREELY_SAY_SCHEMATICS },
    { HOBART_SAY_INGENIOUS_CAP,           5000, GREELY_SAY_INGENIOUS_CAP },
};

static const Position BunnySPL[7] =
{
    { -8411.01f, 1356.23f, 109.925f, 5.148721f },
    { -8410.72f, 1356.76f, 110.116f, 6.230825f },
    { -8410.48f, 1356.29f, 110.231f, 6.230825f },
    { -8411.18f, 1356.42f, 110.526f, 6.230825f },
    { -8411.56f, 1356.08f, 111.271f, 6.230825f },
    { -8411.06f, 1356.46f, 111.704f, 6.230825f },
    { -8411.21f, 1357.01f, 111.726f, 6.230825f },
};

static const Position BunnySPR[7] =
{
    { -8403.19f, 1356.28f, 109.492f, 6.230825f },
    { -8403.80f, 1356.15f, 109.954f, 3.246312f },
    { -8402.79f, 1355.90f, 110.156f, 6.230825f },
    { -8403.34f, 1356.62f, 110.337f, 6.230825f },
    { -8402.85f, 1356.43f, 110.739f, 6.230825f },
    { -8402.64f, 1356.01f, 111.359f, 6.230825f },
    { -8402.84f, 1356.28f, 111.426f, 6.230825f },
};

class npc_kezan_hobart_grapplehammer : public CreatureScript
{
    public:
        npc_kezan_hobart_grapplehammer() : CreatureScript("npc_kezan_hobart_grapplehammer") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            // TODO implement correct, check gossips
            if (creature->GetPhaseMask() == 1)
            {
                player->SEND_GOSSIP_MENU(17538, creature->GetGUID());
                return true;
            }
            else
            {
                player->SEND_GOSSIP_MENU(17554, creature->GetGUID());
                return true;
            }
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_KAJARO_HOBART     = 1,
                EVENT_KAJARO_GREELY     = 2,
                EVENT_KAJARO_PANIC      = 3,
                EVENT_BUNNY_BEAM_1      = 4,
                EVENT_BUNNY_BEAM_2      = 5,
                EVENT_MECHACHICKEN      = 6, // to EVENT_MECHACHICKEN + 47
            };

            EventMap events;
            uint64 bunnyLGUID[7];
            uint64 bunnyRGUID[7];
            uint64 mechachickenGUID;
            uint64 greelyGUID;
            uint8 kajaroEventId;

            void InitializeAI()
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->setActive(true);
                mechachickenGUID = 0;
                greelyGUID = 0;
                kajaroEventId = 0;
                memset(&bunnyLGUID, 0, sizeof(bunnyLGUID));
                memset(&bunnyRGUID, 0, sizeof(bunnyRGUID));

                switch (me->GetPhaseMask())
                {
                    case 3:
                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                        events.ScheduleEvent(EVENT_MECHACHICKEN, 7000);
                        break;
                    case 4:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        break;
                    default:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        events.ScheduleEvent(EVENT_KAJARO_HOBART, 7000);
                        events.ScheduleEvent(EVENT_KAJARO_PANIC, 250);
                        break;
                }

                if (Creature* greely = me->SummonCreature(NPC_ASSISTANT_GREELY, -8405.3f, 1360.25f, 104.021f, 3.61756f))
                {
                    greelyGUID = greely->GetGUID();
                    greely->SetWalk(true);
                }

                for (int i = 0; i < 7; ++i)
                {
                    if (Creature* bunnyL = me->SummonCreature(NPC_ELM_GENERAL_PURPOSE_BUNNY, BunnySPL[i]))
                        bunnyLGUID[i] = bunnyL->GetGUID();

                    if (Creature* bunnyR = me->SummonCreature(NPC_ELM_GENERAL_PURPOSE_BUNNY, BunnySPR[i]))
                        bunnyRGUID[i] = bunnyR->GetGUID();
                }
            }

            void BunnyBeam(uint8 l, uint8 r)
            {
                uint8 indexL[] = { 0, 1, 2, 3, 4, 5, 6 };
                uint8 indexR[] = { 0, 1, 2, 3, 4, 5, 6 };

                std::random_shuffle(indexL, indexL + 7);
                std::random_shuffle(indexR, indexR + 7);

                for (int i = 0; i < l; ++i)
                    if (Creature* bunny = Unit::GetCreature(*me, bunnyLGUID[indexL[i]]))
                        bunny->CastSpell(bunny, SPELL_LIGHTNING_IMPACT, false);

                for (int i = 0; i < r; ++i)
                    if (Creature* bunny = Unit::GetCreature(*me, bunnyRGUID[indexR[i]]))
                        bunny->CastSpell(bunny, SPELL_LIGHTNING_IMPACT, false);
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_KAJARO_HOBART:
                            Talk(KajaroEvent[kajaroEventId].hobartTextId);
                            events.ScheduleEvent(EVENT_KAJARO_GREELY, KajaroEvent[kajaroEventId].timer);
                            break;
                        case EVENT_KAJARO_GREELY:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(KajaroEvent[kajaroEventId].greelyTextId);

                                kajaroEventId = urand(0, 7);
                                events.ScheduleEvent(EVENT_KAJARO_HOBART, urand(21000, 35000));
                            }
                            break;
                        case EVENT_KAJARO_PANIC:
                            {
                                Position pos = me->GetHomePosition();
                                float x, y, z;
                                me->GetRandomPoint(pos, 7.5f, x, y, z);
                                me->GetMotionMaster()->MoveSplinePoint(x, y, z, 7.5f, false);
                                events.ScheduleEvent(EVENT_KAJARO_PANIC, me->GetSplineDuration());
                            }
                            break;
                        case EVENT_BUNNY_BEAM_1:
                            BunnyBeam(urand(3, 4), urand(3, 4));
                            events.ScheduleEvent(EVENT_BUNNY_BEAM_1, 1000);
                            break;
                        case EVENT_BUNNY_BEAM_2:
                            BunnyBeam(urand(1, 2), urand(1, 2));
                            events.ScheduleEvent(EVENT_BUNNY_BEAM_1, 1000);
                            break;
                        case EVENT_MECHACHICKEN:
                            {
                                Talk(HOBART_YELL_PREPARE);
                                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);

                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 1, 2500);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 1:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    greely->GetMotionMaster()->MoveSplinePoint(-8405.96f, 1357.84f, 104.71f, 2.f);
                                    events.ScheduleEvent(EVENT_MECHACHICKEN + 2, greely->GetSplineDuration());

                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_SHEESH);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 3, 3000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 2:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    greely->SetFacingTo(4.14084f);
                                    greely->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                                }
                            }
                            break;
                        case EVENT_MECHACHICKEN + 3:
                            {
                                if (Creature* mechachicken = me->SummonCreature(NPC_MICRO_MECHACHICKEN, -8406.926f, 1356.2f, 104.8625f, 1.53589f))
                                {
                                    mechachickenGUID = mechachicken->GetGUID();
                                    mechachicken->CastSpell(mechachicken, SPELL_COSMETIC_POLYMORPH_IMPACT_VISUAL, false);
                                }

                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 4, 4000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 4:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_ONE_MECHACHICKEN);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 5, 6000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 5:
                            Talk(HOBART_SAY_DEAR_GREELY);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 6, 8000);
                            break;
                        case EVENT_MECHACHICKEN + 6:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SIGH);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 7, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 7:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_YES_DOCTOR);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 8, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 8:
                            Talk(HOBART_SAY_EXCELLENT);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 9, 5000);
                            break;
                        case EVENT_MECHACHICKEN + 9:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    greely->GetMotionMaster()->MoveSplinePoint(-8405.3f, 1360.25f, 104.021f, 2.f);
                                    events.ScheduleEvent(EVENT_MECHACHICKEN + 10, greely->GetSplineDuration());
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 11, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 10:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    greely->SetFacingTo(greely->GetAngle(me));

                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SHAKES_HEAD);
                                }
                            }
                            break;
                        case EVENT_MECHACHICKEN + 11:
                            Talk(HOBART_SAY_THANK_YOU);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 12, 7000);
                            break;
                        case EVENT_MECHACHICKEN + 12:
                            Talk(HOBART_SAY_HORRIBLE_PROBLEM);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 13, 5000);
                            break;
                        case EVENT_MECHACHICKEN + 13:
                            Talk(HOBART_SAY_GREATEST_GOBLIN);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 14, 8000);
                            break;
                        case EVENT_MECHACHICKEN + 14:
                            Talk(HOBART_SAY_FLIP_THE_SWITCH);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 15, 1000);
                            break;
                        case EVENT_MECHACHICKEN + 15:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_COUGHS);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 16, 1000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 16:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_AT_THE_CONTROLS);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 17, 2500);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 17:
                            Talk(HOBART_SAY_QUITE_RIGHT);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 18, 4000);
                            break;
                        case EVENT_MECHACHICKEN + 18:
                            Talk(HOBART_SAY_FLIPPING);
                            events.ScheduleEvent(EVENT_BUNNY_BEAM_1, 3500);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 19, 8500);
                            break;
                        case EVENT_MECHACHICKEN + 19:
                            Talk(HOBART_SAY_CAN_YOU_FEEL);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 20, 6000);
                            break;
                        case EVENT_MECHACHICKEN + 20:
                            Talk(HOBART_SAY_GROCERY_STORE);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 21, 6000);
                            break;
                        case EVENT_MECHACHICKEN + 21:
                            Talk(HOBART_SAY_FLIPPING_SECOND);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 22, 7000);
                            break;
                        case EVENT_MECHACHICKEN + 22:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    if (Creature* bunnyL = Unit::GetCreature(*me, bunnyLGUID[0]))
                                        bunnyL->CastSpell(chicken, SPELL_LIGHTNING_BEAM, false);

                                    if (Creature* bunnyR = Unit::GetCreature(*me, bunnyRGUID[0]))
                                        bunnyR->CastSpell(chicken, SPELL_LIGHTNING_BEAM, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 23, 500);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 23:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->HandleEmoteCommand(EMOTE_ONESHOT_CUSTOM_SPELL_02);
                                    chicken->CastSpell(chicken, SPELL_MECHACHICKEN_OVERLOAD, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 24, 3000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 24:
                            {
                                Talk(HOBART_SAY_WAIT);

                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->CastSpell(chicken, SPELL_MICRO_MECHACHICKEN_GROW, false);
                                }

                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);

                                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                                events.ScheduleEvent(EVENT_MECHACHICKEN + 25, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 25:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    greely->CastSpell(greely, SPELL_STEALTH, false);
                                    greely->GetMotionMaster()->MoveSplinePoint(-8404.18f, 1364.28f, 104.021f, 2.5f);
                                    events.ScheduleEvent(EVENT_MECHACHICKEN + 26, greely->GetSplineDuration());
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 27, 1500);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 26:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->SetFacingTo(greely->GetAngle(me));
                            }
                            break;
                        case EVENT_MECHACHICKEN + 27:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_YA_THINK);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 28, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 28:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->CastSpell(chicken, SPELL_MICRO_MECHACHICKEN_GROW, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 29, 4000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 29:
                            Talk(HOBART_YELL_I_KNOW);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 30, 2000);
                            break;
                        case EVENT_MECHACHICKEN + 30:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->CastSpell(chicken, SPELL_MICRO_MECHACHICKEN_GROW, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 31, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 31:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_YELL_FAR_RIGHT);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 32, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 32:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->CastSpell(chicken, SPELL_MICRO_MECHACHICKEN_GROW, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 33, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 33:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->CastSpell(chicken, SPELL_MICRO_MECHACHICKEN_GROW, false);
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 34, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 34:
                            Talk(HOBART_YELL_I_ALWAYS_LOVED);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 35, 2000);
                            break;
                        case EVENT_MECHACHICKEN + 35:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_YELL_WHAT);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 36, 2000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 36:
                            Talk(HOBART_YELL_FLIPPING_THE_OVERRIDE);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 37, 5000);
                            break;
                        case EVENT_MECHACHICKEN + 37:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->PlayDirectSound(12205);
                                    chicken->RemoveAllAuras();
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 38, 3000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 38:
                            Talk(HOBART_SAY_ARE_WE_STILL_ALIVE);
                            events.CancelEvent(EVENT_BUNNY_BEAM_2);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 39, 4000);
                            break;
                        case EVENT_MECHACHICKEN + 39:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                {
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_WERE_STILL_ALIVE);

                                    greely->RemoveAllAuras();
                                    greely->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                                    greely->GetMotionMaster()->MoveSplinePoint(-8405.3f, 1360.25f, 104.021f, 2.5f);
                                    events.ScheduleEvent(EVENT_MECHACHICKEN + 40, greely->GetSplineDuration());
                                }

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 41, 3000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 40:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->SetFacingTo(greely->GetAngle(me));

                                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 41:
                            Talk(HOBART_SAY_WELL_OF_COURSE);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 42, 4000);
                            break;
                        case EVENT_MECHACHICKEN + 42:
                            {
                                if (Creature* chicken = Unit::GetCreature(*me, mechachickenGUID))
                                {
                                    chicken->CastSpell(chicken, SPELL_MECHACHICKEN_EXPLOSION, false);
                                    chicken->PlayDirectSound(12205);
                                    chicken->DespawnOrUnsummon(3000);
                                }

                                events.CancelEvent(EVENT_BUNNY_BEAM_2);
                                events.ScheduleEvent(EVENT_MECHACHICKEN + 43, 6000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 43:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_IS_THAT_EGG);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 44, 500);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 44:
                            Talk(HOBART_OPEN_MOUTH);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 45, 5000);
                            break;
                        case EVENT_MECHACHICKEN + 45:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_SAY_ALWAYS_LOVED);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 46, 5000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 46:
                            Talk(HOBART_SAY_MISS_GREELY);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                            events.ScheduleEvent(EVENT_MECHACHICKEN + 47, 3000);
                            break;
                        case EVENT_MECHACHICKEN + 47:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    if (greely->IsAIEnabled)
                                        greely->AI()->Talk(GREELY_BOTH_AGREE);

                                events.ScheduleEvent(EVENT_MECHACHICKEN + 48, 3000);
                            }
                            break;
                        case EVENT_MECHACHICKEN + 48:
                            {
                                if (Creature* greely = Unit::GetCreature(*me, greelyGUID))
                                    greely->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                events.ScheduleEvent(EVENT_MECHACHICKEN, 180000);
                            }
                            break;
                    }
                }
            }
        };
};

class npc_kezan_assistant_greely : public CreatureScript
{
    public:
        npc_kezan_assistant_greely() : CreatureScript("npc_kezan_assistant_greely") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            // TODO find gossipe
            if (creature->GetPhaseMask() == 1)
            {
                player->SEND_GOSSIP_MENU(17537, creature->GetGUID());
                return true;
            }
            else
            {
                player->SEND_GOSSIP_MENU(0, creature->GetGUID()); // 50006 N/A
                return true;
            }
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_FOLLOW    = 1,
            };

            EventMap events;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->setActive(true);

                switch (me->GetPhaseMask())
                {
                    case 3:
                        break;
                    case 4:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        break;
                    default:
                        me->AddUnitState(UNIT_STATE_ROOT);
                        me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                        events.ScheduleEvent(EVENT_FOLLOW, 500);
                        break;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_FOLLOW)
                {
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        me->SetFacingToObject(summoner);

                    events.ScheduleEvent(EVENT_FOLLOW, 250);
                }
            }
        };
};

static float MeteorTarget[402][3] =
{
    { -8037.68f, 1475.99f, 13.6223f }, { -8041.16f, 1483.95f, 25.0963f }, { -8041.91f, 1495.25f, 20.7194f },
    { -8032.24f, 1496.39f, 23.9126f }, { -8025.68f, 1485.01f, 25.8630f }, { -8041.24f, 1505.12f, 25.5332f },
    { -8076.59f, 1522.16f, 17.9709f }, { -8077.30f, 1513.77f, 8.99984f }, { -8053.48f, 1509.48f, 9.44403f },
    { -8055.35f, 1485.35f, 9.42139f }, { -8039.05f, 1464.38f, 9.29380f }, { -8067.47f, 1467.07f, 9.31727f },
    { -8086.85f, 1470.7f, 8.832340f }, { -8103.07f, 1481.57f, 10.1055f }, { -8112.70f, 1437.85f, 11.1506f },
    { -8099.88f, 1264.54f, 21.0841f }, { -8058.81f, 1141.94f, 2.76407f }, { -8096.91f, 1342.74f, 18.1227f },
    { -8068.48f, 1162.18f, 3.05742f }, { -8052.22f, 1173.28f, 2.91838f }, { -8036.89f, 1197.22f, 2.46190f },
    { -8062.27f, 1188.14f, 3.90544f }, { -8024.79f, 1205.59f, 1.37508f }, { -8029.19f, 1223.73f, 1.76494f },
    { -8053.10f, 1210.93f, 3.86019f }, { -8043.74f, 1229.99f, 2.52742f }, { -8047.74f, 1252.81f, 6.56697f },
    { -8037.87f, 1297.72f, 3.53944f }, { -8055.57f, 1278.24f, 5.53981f }, { -8026.04f, 1304.86f, 2.91297f },
    { -8045.09f, 1325.30f, 4.80808f }, { -8057.48f, 1338.18f, 6.98008f }, { -8044.74f, 1365.26f, 4.53430f },
    { -8046.55f, 1382.63f, 2.60187f }, { -8053.19f, 1401.32f, 3.15130f }, { -8075.15f, 1401.26f, 7.57897f },
    { -8093.07f, 1371.91f, 12.5679f }, { -8093.58f, 1391.20f, 12.5674f }, { -8120.85f, 1382.40f, 23.6426f },
    { -8124.57f, 1357.68f, 18.8603f }, { -8172.53f, 1341.48f, 27.9590f }, { -8161.24f, 1355.54f, 23.4237f },
    { -8174.19f, 1386.07f, 24.8344f }, { -8234.61f, 1408.73f, 36.9358f }, { -8242.37f, 1383.82f, 41.1568f },
    { -8212.09f, 1395.50f, 39.9162f }, { -8206.88f, 1369.10f, 34.6802f }, { -8233.45f, 1341.80f, 47.8119f },
    { -8261.95f, 1353.64f, 62.5433f }, { -8270.65f, 1374.68f, 63.6114f }, { -8311.16f, 1379.20f, 86.6267f },
    { -8352.93f, 1384.25f, 95.7099f }, { -8398.04f, 1360.53f, 129.112f }, { -8417.90f, 1356.72f, 134.570f },
    { -8429.48f, 1373.74f, 128.992f }, { -8407.17f, 1359.41f, 127.608f }, { -8421.11f, 1367.92f, 129.211f },
    { -8521.92f, 1375.69f, 108.413f }, { -8523.60f, 1299.74f, 114.588f }, { -8448.57f, 1346.65f, 102.444f },
    { -8447.05f, 1371.65f, 102.388f }, { -8462.35f, 1376.25f, 101.697f }, { -8484.00f, 1382.84f, 101.697f },
    { -8508.61f, 1377.18f, 101.716f }, { -8512.02f, 1349.75f, 101.697f }, { -8517.48f, 1314.72f, 101.863f },
    { -8485.11f, 1329.38f, 98.9211f }, { -8484.09f, 1310.34f, 101.697f }, { -8458.21f, 1303.35f, 101.947f },
    { -8425.03f, 1295.12f, 102.925f }, { -8420.98f, 1332.78f, 102.356f }, { -8385.83f, 1330.55f, 102.322f },
    { -8383.08f, 1363.67f, 102.067f }, { -8353.45f, 1343.85f, 95.5177f }, { -8324.33f, 1339.75f, 80.4592f },
    { -8306.44f, 1308.16f, 67.3110f }, { -8282.09f, 1292.87f, 56.9746f }, { -8250.65f, 1304.47f, 45.3597f },
    { -8184.25f, 1329.89f, 63.1769f }, { -8181.56f, 1322.03f, 55.0864f }, { -8159.35f, 1314.61f, 26.4618f },
    { -8189.84f, 1312.64f, 27.6195f }, { -8137.79f, 1308.98f, 19.8113f }, { -8111.47f, 1310.57f, 18.6071f },
    { -8104.93f, 1286.12f, 20.1409f }, { -8126.01f, 1251.00f, 19.6462f }, { -8111.52f, 1224.01f, 16.0268f },
    { -8121.25f, 1155.22f, 12.9709f }, { -8110.50f, 1181.40f, 14.4180f }, { -8149.94f, 1167.08f, 19.5562f },
    { -8137.99f, 1191.00f, 17.4234f }, { -8169.59f, 1200.18f, 18.7697f }, { -8188.52f, 1217.12f, 22.4706f },
    { -8161.76f, 1221.41f, 20.8543f }, { -8156.47f, 1241.08f, 21.6440f }, { -8154.94f, 1256.68f, 22.7579f },
    { -8150.27f, 1287.58f, 23.3850f }, { -8173.76f, 1278.06f, 25.5544f }, { -8179.01f, 1265.74f, 36.4265f },
    { -8192.40f, 1276.75f, 27.6607f }, { -8206.10f, 1250.43f, 60.1228f }, { -8209.18f, 1271.33f, 36.8474f },
    { -8204.77f, 1244.57f, 49.9996f }, { -8219.71f, 1242.81f, 45.1397f }, { -8217.20f, 1232.63f, 35.3453f },
    { -8225.51f, 1233.63f, 24.1994f }, { -8244.10f, 1257.35f, 27.9735f }, { -8248.97f, 1204.12f, 36.7716f },
    { -8268.35f, 1222.54f, 34.4648f }, { -8290.61f, 1244.50f, 39.1817f }, { -8306.43f, 1235.52f, 41.1522f },
    { -8330.18f, 1231.38f, 53.4531f }, { -8347.05f, 1227.46f, 54.3543f }, { -8357.28f, 1199.09f, 45.4824f },
    { -8389.13f, 1184.67f, 54.3850f }, { -8399.34f, 1213.46f, 57.4407f }, { -8411.57f, 1229.80f, 60.7457f },
    { -8394.02f, 1245.47f, 59.7155f }, { -8385.13f, 1261.33f, 60.6984f }, { -8393.19f, 1275.48f, 79.2300f },
    { -8428.73f, 1260.14f, 69.1703f }, { -8464.21f, 1244.84f, 54.3887f }, { -8508.75f, 1240.72f, 54.9423f },
    { -8452.64f, 1213.22f, 43.0954f }, { -8478.42f, 1213.83f, 42.0305f }, { -8505.35f, 1223.07f, 50.6053f },
    { -8513.14f, 1202.46f, 49.8505f }, { -8488.22f, 1167.01f, 41.9150f }, { -8487.33f, 1140.70f, 40.6198f },
    { -8478.69f, 1128.04f, 41.6854f }, { -8472.56f, 1163.18f, 41.0058f }, { -8459.93f, 1181.22f, 42.1854f },
    { -8443.70f, 1198.07f, 40.5342f }, { -8420.14f, 1196.56f, 41.3180f }, { -8424.33f, 1175.26f, 40.6914f },
    { -8448.33f, 1174.65f, 40.8060f }, { -8445.03f, 1157.14f, 39.9888f }, { -8451.10f, 1145.83f, 40.9183f },
    { -8443.84f, 1107.99f, 52.1924f }, { -8419.00f, 1126.36f, 49.2527f }, { -8028.87f, 1481.56f, 38.3273f },
    { -8028.99f, 1506.36f, 36.0386f }, { -8087.26f, 1496.92f, 22.6907f }, { -8100.74f, 1517.34f, 9.68134f },
    { -8123.84f, 1517.62f, 10.6082f }, { -8130.38f, 1492.14f, 12.9926f }, { -8145.67f, 1492.48f, 26.6957f },
    { -8146.08f, 1525.65f, 21.6292f }, { -8156.04f, 1545.47f, 25.7418f }, { -8164.30f, 1532.97f, 47.2374f },
    { -8173.93f, 1511.44f, 43.2488f }, { -8178.37f, 1486.72f, 41.5304f }, { -8189.10f, 1524.61f, 59.1192f },
    { -8194.75f, 1542.65f, 66.0870f }, { -8198.37f, 1547.58f, 31.9746f }, { -8116.75f, 1554.00f, 27.2984f },
    { -8122.01f, 1542.77f, 26.7214f }, { -8114.74f, 1529.92f, 25.8053f }, { -8113.16f, 1539.34f, 36.2071f },
    { -8102.46f, 1550.34f, 9.05301f }, { -8084.31f, 1536.76f, 9.17192f }, { -8059.48f, 1542.59f, 3.53651f },
    { -8028.07f, 1538.22f, 1.55586f }, { -7996.98f, 1502.57f, 2.39352f }, { -7991.51f, 1528.00f, 1.28052f },
    { -8004.85f, 1563.46f, 1.56339f }, { -7999.34f, 1594.35f, 2.17393f }, { -8006.75f, 1604.55f, 2.38489f },
    { -8050.17f, 1620.84f, 1.04762f }, { -8067.14f, 1602.28f, 7.81356f }, { -8096.68f, 1617.33f, 8.68595f },
    { -8087.12f, 1592.75f, 7.92499f }, { -8108.32f, 1592.50f, 8.59131f }, { -8090.40f, 1631.63f, 8.95684f },
    { -8072.92f, 1649.38f, 10.1871f }, { -8044.60f, 1653.57f, 4.37643f }, { -8021.95f, 1639.24f, 2.34828f },
    { -7996.61f, 1637.17f, 1.60131f }, { -7994.46f, 1655.70f, 2.44999f }, { -8010.08f, 1663.25f, 2.82048f },
    { -8002.64f, 1679.93f, 3.19247f }, { -7994.76f, 1695.15f, 2.22928f }, { -8014.16f, 1701.03f, 2.96222f },
    { -8005.91f, 1721.59f, 2.21401f }, { -8023.12f, 1732.57f, 1.31788f }, { -8012.69f, 1751.27f, 1.07758f },
    { -8031.88f, 1710.56f, 7.01437f }, { -8049.05f, 1745.71f, 2.03484f }, { -8044.88f, 1776.31f, 1.54140f },
    { -8022.54f, 1784.73f, 0.98204f }, { -8087.86f, 1773.94f, 25.6381f }, { -8037.12f, 1762.20f, 1.80717f },
    { -8082.06f, 1730.01f, 18.2666f }, { -8070.86f, 1707.03f, 16.5465f }, { -8044.80f, 1699.18f, 12.9628f },
    { -8073.86f, 1679.94f, 13.4186f }, { -8096.19f, 1675.74f, 13.3204f }, { -8098.53f, 1700.74f, 16.3298f },
    { -8109.20f, 1739.97f, 22.8146f }, { -8112.35f, 1774.00f, 39.7602f }, { -8094.99f, 1807.06f, 34.2375f },
    { -8067.89f, 1831.77f, 45.3007f }, { -8056.43f, 1816.78f, 41.9736f }, { -8025.39f, 1821.22f, 35.5957f },
    { -7998.59f, 1820.47f, 23.7669f }, { -7980.88f, 1806.43f, 13.3507f }, { -7971.68f, 1908.20f, 52.5324f },
    { -7996.62f, 1904.99f, 52.5176f }, { -8028.01f, 1902.80f, 49.6608f }, { -8023.44f, 1873.97f, 52.7744f },
    { -8004.30f, 1876.02f, 52.6784f }, { -8005.74f, 1861.77f, 65.9874f }, { -8031.11f, 1860.10f, 52.5216f },
    { -8048.75f, 1876.51f, 52.5164f }, { -8054.38f, 1859.08f, 52.3152f }, { -8064.52f, 1895.29f, 53.6651f },
    { -8054.42f, 1917.65f, 52.5129f }, { -8047.46f, 1911.33f, 52.5143f }, { -8047.32f, 1934.01f, 52.5890f },
    { -8055.51f, 1947.62f, 53.0907f }, { -8079.51f, 1952.64f, 53.9686f }, { -8046.28f, 1950.57f, 67.4519f },
    { -8079.02f, 1929.12f, 65.8922f }, { -8112.23f, 1929.90f, 55.6128f }, { -8118.68f, 1913.42f, 54.9076f },
    { -8092.71f, 1895.89f, 54.5085f }, { -8096.62f, 1874.26f, 56.0164f }, { -8114.35f, 1867.71f, 56.2004f },
    { -8139.16f, 1861.77f, 55.4215f }, { -8146.83f, 1887.72f, 81.0716f }, { -8154.03f, 1903.98f, 66.0807f },
    { -8143.70f, 1912.14f, 81.4387f }, { -8155.74f, 1896.17f, 86.3040f }, { -8154.48f, 1887.44f, 98.7238f },
    { -8136.74f, 1891.18f, 81.4883f }, { -8149.41f, 1848.57f, 33.8570f }, { -8159.65f, 1841.05f, 31.4248f },
    { -8143.59f, 1823.63f, 23.0160f }, { -8158.70f, 1778.53f, 25.2191f }, { -8185.56f, 1788.36f, 29.8838f },
    { -8176.88f, 1763.34f, 47.1109f }, { -8182.01f, 1779.40f, 45.6053f }, { -8174.42f, 1774.36f, 55.5011f },
    { -8184.51f, 1747.35f, 56.2979f }, { -8201.65f, 1762.05f, 43.2104f }, { -8221.98f, 1745.37f, 44.3920f },
    { -8239.13f, 1726.88f, 44.7975f }, { -8247.40f, 1724.67f, 44.6988f }, { -8236.96f, 1716.77f, 44.6888f },
    { -8235.27f, 1699.40f, 44.5862f }, { -8225.99f, 1708.32f, 55.2297f }, { -8210.29f, 1723.04f, 55.5713f },
    { -8205.04f, 1719.37f, 61.9990f }, { -8208.55f, 1702.31f, 57.2884f }, { -8207.53f, 1695.21f, 60.9719f },
    { -8206.98f, 1691.87f, 68.2909f }, { -8209.78f, 1678.74f, 49.7786f }, { -8210.34f, 1685.61f, 58.1599f },
    { -8181.90f, 1668.56f, 57.7743f }, { -8119.52f, 1602.52f, 28.6966f }, { -8121.59f, 1588.66f, 29.6093f },
    { -8135.98f, 1591.01f, 44.6268f }, { -8144.41f, 1595.12f, 44.8364f }, { -8144.46f, 1601.59f, 16.3018f },
    { -8157.13f, 1613.54f, 19.0649f }, { -8160.54f, 1645.76f, 20.6001f }, { -8175.91f, 1655.82f, 24.2878f },
    { -8188.97f, 1625.97f, 28.0432f }, { -8205.34f, 1633.55f, 31.1166f }, { -8218.12f, 1644.59f, 32.8152f },
    { -8226.97f, 1631.59f, 33.8053f }, { -8219.49f, 1604.67f, 33.2154f }, { -8229.99f, 1589.33f, 33.5585f },
    { -8208.79f, 1574.95f, 31.5433f }, { -8209.29f, 1555.51f, 31.8884f }, { -8179.93f, 1548.80f, 31.1706f },
    { -8169.80f, 1567.19f, 22.9115f }, { -8175.13f, 1588.15f, 25.3683f }, { -8144.05f, 1588.18f, 45.4832f },
    { -8171.52f, 1611.78f, 40.5640f }, { -8170.19f, 1612.04f, 39.8783f }, { -8169.57f, 1629.38f, 40.6756f },
    { -8174.49f, 1625.01f, 41.1788f }, { -8177.42f, 1616.89f, 40.3119f }, { -8200.22f, 1618.75f, 42.3867f },
    { -8194.98f, 1600.51f, 46.0721f }, { -8195.65f, 1582.67f, 45.7628f }, { -8194.36f, 1546.49f, 40.3620f },
    { -8243.48f, 1559.47f, 60.8475f }, { -8241.81f, 1580.22f, 62.2030f }, { -8242.42f, 1580.86f, 69.3832f },
    { -8297.73f, 1607.72f, 131.350f }, { -8317.24f, 1605.07f, 130.934f }, { -8317.45f, 1621.26f, 124.914f },
    { -8311.22f, 1614.64f, 129.569f }, { -8291.52f, 1612.08f, 130.917f }, { -8270.51f, 1614.94f, 129.910f },
    { -8263.07f, 1654.11f, 66.6103f }, { -8279.28f, 1658.81f, 67.4949f }, { -8257.62f, 1666.90f, 49.9469f },
    { -8240.17f, 1674.51f, 43.2782f }, { -8259.22f, 1692.26f, 48.4038f }, { -8274.26f, 1704.07f, 63.8722f },
    { -8275.31f, 1718.44f, 64.9682f }, { -8276.65f, 1726.24f, 71.4404f }, { -8301.52f, 1726.90f, 51.0400f },
    { -8318.98f, 1726.47f, 50.7467f }, { -8331.63f, 1748.07f, 50.7927f }, { -8330.70f, 1711.08f, 50.9302f },
    { -8319.73f, 1698.28f, 51.2294f }, { -8339.30f, 1700.00f, 51.1353f }, { -8349.15f, 1720.86f, 68.9031f },
    { -8354.30f, 1731.89f, 69.4192f }, { -8343.74f, 1732.48f, 69.2499f }, { -8342.35f, 1721.51f, 68.7857f },
    { -8389.17f, 1728.71f, 117.668f }, { -8396.05f, 1727.78f, 118.204f }, { -8413.08f, 1723.72f, 118.673f },
    { -8424.37f, 1723.40f, 120.330f }, { -8424.23f, 1728.65f, 117.853f }, { -8407.60f, 1734.04f, 117.950f },
    { -8400.43f, 1735.36f, 118.096f }, { -8468.31f, 1681.69f, 78.5300f }, { -8471.22f, 1666.39f, 74.6295f },
    { -8432.00f, 1664.70f, 48.0161f }, { -8416.58f, 1654.20f, 45.7974f }, { -8425.02f, 1638.11f, 43.6810f },
    { -8404.63f, 1630.90f, 43.6817f }, { -8384.50f, 1657.27f, 49.5437f }, { -8375.68f, 1640.21f, 49.5635f },
    { -8362.68f, 1623.83f, 72.9915f }, { -8379.60f, 1612.53f, 72.2692f }, { -8391.99f, 1609.98f, 82.0446f },
    { -8397.68f, 1589.56f, 72.3736f }, { -8389.79f, 1562.08f, 62.1636f }, { -8431.31f, 1520.08f, 69.3153f },
    { -8401.67f, 1535.71f, 50.3128f }, { -8397.27f, 1547.18f, 49.2079f }, { -8425.62f, 1541.02f, 48.5064f },
    { -8460.11f, 1539.01f, 50.7479f }, { -8456.83f, 1616.70f, 44.0009f }, { -8457.34f, 1631.80f, 45.7327f },
    { -8446.81f, 1615.38f, 42.3281f }, { -8490.66f, 1617.02f, 47.2390f }, { -8326.46f, 1658.76f, 78.2067f },
    { -8321.79f, 1641.24f, 81.3262f }, { -8325.36f, 1579.57f, 79.7855f }, { -8303.68f, 1577.49f, 74.7501f },
    { -8354.54f, 1549.24f, 75.7229f }, { -8354.94f, 1531.94f, 55.4800f }, { -8326.19f, 1532.43f, 47.2057f },
    { -8334.23f, 1547.00f, 81.8935f }, { -8310.97f, 1526.21f, 49.5073f }, { -8302.29f, 1542.42f, 47.6788f },
    { -8299.01f, 1555.11f, 76.2957f }, { -8275.83f, 1544.73f, 50.9328f }, { -8277.68f, 1563.14f, 51.9492f },
    { -8264.25f, 1541.97f, 40.8781f }, { -8254.31f, 1549.45f, 40.7780f }, { -8258.43f, 1557.47f, 55.9036f },
    { -8242.95f, 1545.69f, 46.5355f }, { -8237.21f, 1516.04f, 40.9409f }, { -8244.59f, 1537.00f, 40.4869f },
    { -8227.16f, 1502.12f, 40.6486f }, { -8205.39f, 1512.50f, 52.7608f }, { -8219.27f, 1496.78f, 40.6822f },
    { -8219.90f, 1479.77f, 39.6774f }, { -8234.84f, 1466.32f, 40.4804f }, { -8228.45f, 1447.73f, 39.6120f },
    { -8211.36f, 1441.88f, 36.1301f }, { -8194.97f, 1447.91f, 37.6865f }, { -8189.28f, 1417.96f, 25.2797f },
    { -8192.65f, 1404.33f, 26.2710f }, { -8220.00f, 1421.85f, 47.6745f }, { -8236.09f, 1433.07f, 39.3946f },
    { -8254.82f, 1437.24f, 40.2917f }, { -8254.91f, 1419.55f, 40.0054f }, { -8238.21f, 1421.00f, 51.9041f },
    { -8280.59f, 1418.48f, 52.9367f }, { -8283.64f, 1432.88f, 39.5929f }, { -8303.63f, 1445.15f, 41.7076f },
    { -8316.32f, 1429.48f, 44.5663f }, { -8336.59f, 1412.32f, 75.8575f }, { -8364.83f, 1410.11f, 89.0763f },
    { -8399.95f, 1435.71f, 80.6888f }, { -8349.31f, 1450.96f, 47.8875f }, { -8347.14f, 1477.55f, 47.3712f },
    { -8358.90f, 1481.39f, 63.7215f }, { -8360.44f, 1489.96f, 63.2215f }, { -8372.52f, 1488.14f, 63.8784f },
    { -8379.54f, 1481.10f, 64.1588f }, { -8389.03f, 1484.79f, 108.922f }, { -8393.46f, 1462.69f, 110.765f },
    { -8403.11f, 1444.06f, 112.509f }, { -8409.97f, 1461.63f, 109.751f }, { -8402.11f, 1492.30f, 112.804f },
    { -8458.92f, 1490.22f, 100.733f }, { -8452.01f, 1482.69f, 102.460f }, { -8459.09f, 1475.15f, 102.678f },
    { -8477.37f, 1478.84f, 87.2453f }, { -8477.35f, 1494.56f, 87.1643f }, { -8477.35f, 1494.56f, 87.1643f }
};

class npc_kezan_meteor_caster : public CreatureScript
{
    public:
        npc_kezan_meteor_caster() : CreatureScript("npc_kezan_meteor_caster") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_METEOR_CASTER = 1,
            };

            EventMap events;

            void InitializeAI()
            {
                me->setActive(true);
                events.ScheduleEvent(EVENT_METEOR_CASTER, 1000);
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_METEOR_CASTER)
                {
                    uint8 roll = urand(0, 401);
                    me->CastSpell(MeteorTarget[roll][0], MeteorTarget[roll][1], MeteorTarget[roll][2], 70097, false);
                    events.ScheduleEvent(EVENT_METEOR_CASTER, me->GetPhaseMask() == 3072 ? urand(15000, 30000) : urand(5000, 15000));
                }
            }
        };
};

const std::string PlayerSay[49] =
{
    "A big convention, see ? To show off all of our inventions.We call it GoblinCon.And we give away special pets!Except most people will probably sell them for profit on the auction house.",
    "A binary number system.It uses only two numbers, 6 and 11.",
    "A globe that shows the inside of the planet... on the outside.So you know where to dig!",
    "A truck that delivers ice - cream.With a catapult.",
    "Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!",
    "Bagel - holes!",
    "Chocolate - flavored vanilla!",
    "Clowns.Except instead of making you laugh, they're for beating.",
    "Distilling the juice out of Kaja'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...",
    "Dwarves.In.Space!",
    "Earwax.It's got to be good for SOMETHING.",
    "Edible beds.So you can have breakfast in bed.Beds... for breakfast!",
    "Electrical wires used to send messages over great distances... no, impractical.Giant rockets, with speakers attached...",
    "Fake food!Created by grinding up real food and pressing it into shapes of different food.With artificial flavoring!",
    "Feed pigs rubber, 'til they bounce. There's got to be an application for that.",
    "Flerberts.I'm not sure what they do, but I'd better lock down the name with a trademark.",
    "Games you can play with your face!",
    "Giant gnomes.No, wait... tiny giants!",
    "Gloves with built - in clappers, for hands - free clapping.",
    "Goblins with gills!",
    "Half man... half sharkalligator!",
    "Handheld one - way mirrors!",
    "Headshoes!",
    "Houses made of dirt!When you clean them... THEY'RE GONE.",
    "How about smiling monkey wallets ?",
    "How about this : Instant water!Just add... oh.",
    "Invisible bunnies!We'll put them all over the place, and they'll control everything!",
    "Invisible condiments.For an unobstructed view of your food.",
    "It's like bungie-jumping, right? But without a cord, see? And you start at the bottom. I guess it's just sorta like regular jumping.But with guns.",
    "I've got it: Squeezable rocks!",
    "Leashes... with pre - attached pets.",
    "Motorized gravy - boat.With laser lump vaporizer!",
    "Mouse - sized beartraps... no... Bear - sized mousetraps!!",
    "Murder permits!",
    "Nose - stenders.For smelling things in different rooms.",
    "Portable gasoline squirt - guns!",
    "Recycling!But, for stuff that's never been used before.",
    "Shoes with wheels on them.And gloves with wheels on them - for when you fall down.",
    "Soap on a rope!Attached to a chain!Mounted via a steel cable.To some soap.",
    "Spoon sharpeners!",
    "Stairways... for horizontal surfaces!",
    "State - sponsored healthcare!",
    "String - less kites!",
    "Tauren Paladins!",
    "Tether - footbomb!",
    "Thirteen - sided dice!",
    "Water - proof soap!For underwater use!",
    "We put a whole town... in a tiny little box!",
    "What if we were to ORGANIZE crime?",
};

class spell_kezan_kaja_kola : public SpellScriptLoader
{
    public:
        spell_kezan_kaja_kola() : SpellScriptLoader("spell_kezan_kaja_kola") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex /*effIndex*/)
            {
                Player* player = NULL;

                if (Player* player = GetHitPlayer())
                {
                    player->Yell(PlayerSay[urand(0, 48)], LANG_UNIVERSAL);
                    player->CastSpell(player, 70483, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class at_kezan_kajamine : public AreaTriggerScript
{
    public:
        at_kezan_kajamine() : AreaTriggerScript("at_kezan_kajamine") { }

    private:
        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            enum
            {
                TALK_TROLLS = 1,
            };

            if (player->GetPhaseMask() & 15)
                if (Creature* brute = player->FindNearestCreature(35304, 30.f))
                    if (brute->IsAIEnabled)
                        brute->AI()->Talk(TALK_TROLLS, player->GetGUID(), true);

            return true;
        }
};

class npc_kezan_dont_go_into_the_light_doc_zapnozzle : public CreatureScript
{
    public:
        npc_kezan_dont_go_into_the_light_doc_zapnozzle() : CreatureScript("npc_kezan_dont_go_into_the_light_doc_zapnozzle") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
        {
            if (quest->GetQuestId() == QUEST_DONT_GO_INTO_THE_LIGHT)
            {
                player->RemoveAura(69010);
                creature->CastSpell(player, 69013, false);
                player->SaveToDB();
            }

            return true;
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_SWIM              = 1,
                EVENT_JUMP              = 2,
                EVENT_TALK_GIZMO        = 3,
                EVENT_TALK_REASON       = 4,
                EVENT_TRIGGER_GIZMO     = 5,
                EVENT_TALK_RESUSCITATE  = 6,
                EVENT_CAST_RESUSCITATE  = 7,
                EVENT_TALK_CLEAR        = 8,
                EVENT_CAST_RESUSCITATE2 = 9,
                EVENT_TALK_DONT_GO      = 10,

                SAY_GIZMO               = 1,
                SAY_REASON              = 2,
                SAY_RESUSCITATE         = 3,
                SAY_CLEAR               = 4,
                SAY_DONT_GO             = 5,
            };

            EventMap events;

            void InitializeAI()
            {
                ASSERT(me->IsSummon());
                Reset();
                me->SetDisableGravity(true);
                me->SetSwim(true);
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* summoner)
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER, summoner->GetGUID());
                events.ScheduleEvent(EVENT_SWIM, 250);
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SWIM:
                            me->GetMotionMaster()->MoveSplinePoint(538.4896f, 3271.205f, -0.652259f, 0.f, false, true);
                            events.ScheduleEvent(EVENT_JUMP, me->GetSplineDuration());
                            break;
                        case EVENT_JUMP:
                            me->GetMotionMaster()->MoveJump(537.135f, 3272.25f, 0.18f, 5.f, 10.f);
                            events.ScheduleEvent(EVENT_TALK_GIZMO, 1000);
                            break;
                        case EVENT_TALK_GIZMO:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    me->SetFacingToObject(summoner);
                                    Talk(SAY_GIZMO, me->ToTempSummon()->GetSummonerGUID(), true);
                                }

                                events.ScheduleEvent(EVENT_TALK_REASON, 5000);
                            }
                            break;
                        case EVENT_TALK_REASON:
                            Talk(SAY_REASON, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_TRIGGER_GIZMO, 3000);
                            break;
                        case EVENT_TRIGGER_GIZMO:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    me->CastSpell(summoner, 69085, false);

                                events.ScheduleEvent(EVENT_TALK_RESUSCITATE, 6000);
                            }
                            break;
                        case EVENT_TALK_RESUSCITATE:
                            Talk(SAY_RESUSCITATE, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_CAST_RESUSCITATE, 6000);
                            break;
                        case EVENT_CAST_RESUSCITATE:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    me->CastSpell(summoner, 69022, false);

                                events.ScheduleEvent(EVENT_TALK_CLEAR, 5000);
                            }
                            break;
                        case EVENT_TALK_CLEAR:
                            Talk(SAY_CLEAR, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_CAST_RESUSCITATE2, 4000);
                            break;
                        case EVENT_CAST_RESUSCITATE2:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    me->CastSpell(summoner, 69022, false);

                                events.ScheduleEvent(EVENT_TALK_DONT_GO, 5000);
                            }
                            break;
                        case EVENT_TALK_DONT_GO:
                            {
                                if (Player* summoner = ObjectAccessor::GetPlayer(*me, me->ToTempSummon()->GetSummonerGUID()))
                                    summoner->CompleteQuest(QUEST_DONT_GO_INTO_THE_LIGHT);

                                Talk(SAY_DONT_GO, me->ToTempSummon()->GetSummonerGUID(), true);
                            }
                            break;
                    }
                }
            }
        };
};

class spell_kezan_dummy_to_geargrinder_fajardo : public SpellScriptLoader
{
    public:
        spell_kezan_dummy_to_geargrinder_fajardo() : SpellScriptLoader("spell_kezan_dummy_to_geargrinder_fajardo") { }

    private:
        class spell_script_impl : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                enum
                {
                    SAY_SORRY_DOC   = 1,
                };

                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Creature* target = GetHitCreature();

                if (caster && target && target->IsAIEnabled)
                    target->AI()->Talk(SAY_SORRY_DOC, caster->GetGUID(), true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_script_impl();
        }
};

class npc_kezan_goblin_supermodel : public CreatureScript
{
    public:
        npc_kezan_goblin_supermodel() : CreatureScript("npc_kezan_goblin_supermodel") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kezan_goblin_supermodelAI(creature);
        }

        struct npc_kezan_goblin_supermodelAI : public ScriptedAI
        {
            npc_kezan_goblin_supermodelAI(Creature* creature)
                : ScriptedAI(creature)
                , streamBunnyGUID(0)
            { }

            enum
            {
                EVENT_MOVE          = 1,
                ACTION_INIT         = 3,
                TYPE_FOLLOWER_GUID  = 1,
            };

            EventMap events;
            uint64 streamBunnyGUID;

            void InitializeAI()
            {
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_INIT), me->m_Events.CalculateTime(500));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_INIT)
                {
                    uint32 targetEntry = 0;

                    switch (me->GetEntry())
                    {
                        case 37054:
                            {
                                targetEntry = 37057;

                                if (Creature* bunny = me->SummonCreature(24021, -8067.288f, 1503.156f, 10.37352f, 0.f))
                                    bunny->CastSpell(me, 69821, true);
                            }
                            break;
                        case 37055:
                            {
                                targetEntry = 37056;

                                if (Creature* bunny = me->SummonCreature(24021, -8067.618f, 1494.582f, 10.49888f, 0.f))
                                    bunny->CastSpell(me, 69821, true);
                            }
                            break;
                        case 37056:
                            {
                                targetEntry = 37055;

                                if (Creature* bunny = me->SummonCreature(24021, -8067.885f, 1485.495f, 10.51868f, 0.f))
                                    bunny->CastSpell(me, 69821, true);
                            }
                            break;
                        case 37057:
                            {
                                targetEntry = 37054;

                                if (Creature* bunny = me->SummonCreature(24021, -8067.641f, 1494.582f, 10.52287f, 0.f))
                                    bunny->CastSpell(me, 69821, true);
                            }
                            break;
                    }

                    if (Creature* target = me->FindNearestCreature(targetEntry, 30.f))
                    {
                        float x, y, z, o;
                        target->GetPosition(x, y, z, o);

                        if (Creature* bunny = me->SummonCreature(37046, x, y, z, o))
                        {
                            if (target->IsAIEnabled)
                                target->AI()->SetGUID(bunny->GetGUID(), TYPE_FOLLOWER_GUID);

                            me->CastSpell(bunny, 69813, true);
                        }
                    }

                    events.ScheduleEvent(EVENT_MOVE, 250);
                }
            }

            void SetGUID(uint64 guid, int32 type) override
            {
                if (type == TYPE_FOLLOWER_GUID)
                    streamBunnyGUID = guid;
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_MOVE)
                {
                    Position pos = me->GetHomePosition();
                    float x, y, z;
                    me->GetRandomPoint(pos, 7.5f, x, y, z);
                    me->GetMotionMaster()->MoveSplinePoint(x, y, z, 7.5f, false);

                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, streamBunnyGUID))
                    {
                        bunny->GetMotionMaster()->MoveSplinePoint(x, y, z);
                        events.ScheduleEvent(EVENT_MOVE, bunny->GetSplineDuration());
                    }
                }
            }
        };
};

class npc_kezan_training_dummy : public CreatureScript
{
    public:
        npc_kezan_training_dummy() : CreatureScript("npc_kezan_training_dummy") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_CHARGE            = 100,
                SPELL_EVISCERATE        = 2098,
                SPELL_IMMOLATE          = 348,
                SPELL_STEADY_SHOT       = 56641,
                SPELL_ARCANE_MISSILES   = 5143,

                NPC_CLASS_QUEST_CREDIT  = 44175,
            };

            void InitializeAI()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell)
            {
                switch (spell->Id)
                {
                    case SPELL_CHARGE:
                    case SPELL_EVISCERATE:
                    case SPELL_IMMOLATE:
                    case SPELL_STEADY_SHOT:
                    case SPELL_ARCANE_MISSILES:
                        {
                            if (Player* player = caster->ToPlayer())
                                player->KilledMonsterCredit(NPC_CLASS_QUEST_CREDIT);
                        }
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage)
            {
                damage = 0;
            }

            void UpdateAI(uint32 const /*diff*/) { }
        };
};

class npc_kezan_injured_employee : public CreatureScript
{
    public:
        npc_kezan_injured_employee() : CreatureScript("npc_kezan_injured_employee") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_FLASH_HEAL        = 2061,
                NPC_CLASS_QUEST_CREDIT  = 44175,
            };

            void SpellHit(Unit* caster, const SpellInfo* spell)
            {
                if (spell->Id == SPELL_FLASH_HEAL)
                    if (Player* player = caster->ToPlayer())
                        player->KilledMonsterCredit(NPC_CLASS_QUEST_CREDIT);
            }

            void HealReceived(Unit* /*healer*/, uint32& heal)
            {
                if (me->GetHealthPct() > 50.f)
                    me->SetHealth(1);
            }
        };
};

void AddSC_kezan()
{
    new zone_kezan();

    new npc_kezan_sassy_sardwrench();
    new npc_kezan_life_savings_hot_rod();
    new npc_kezan_foreman_dampwick();
    new npc_kezan_sister_goldskimmer();
    new npc_kezan_maxx_avalanche();
    new npc_kezan_fizz_lighter();
    new npc_kezan_evol_fingers();
    new npc_kezan_bamm_megabomb();
    new npc_kezan_slinky_sharpshiv();
    new npc_kezan_warrior_matic_nx_01();
    new npc_kezan_megs_dreadshredder();
    new npc_kezan_hot_rod();
    new npc_kezan_homie_follower("npc_kezan_homie_ace", 0);
    new npc_kezan_homie_follower("npc_kezan_homie_gobber", 1);
    new npc_kezan_homie_follower("npc_kezan_homie_izzy", 2);
    new npc_kezan_citizen();
    new npc_kezan_citizen_immune();
    new npc_kezan_citizen_tribune();
    new npc_kezan_coach_crosscheck();
    new npc_kezan_bilgewater_buccaneer();
    new npc_kezan_steamwheedle_shark();
    new npc_kezan_bilgewater_buccaneer_goal();
    new npc_kezan_fourth_and_goal_target();
    new npc_kezan_deathwing_qfag();
    new npc_kezan_bruno_flameretardant();
    new npc_kezan_frankie_gearslipper();
    new npc_kezan_jack_the_hammer();
    new npc_kezan_sudsy_magee();
    new npc_kezan_chip_endale();
    new npc_kezan_candy_cane();
    new npc_kezan_fbok_bank_teller();
    new npc_kezan_szabo();
    new npc_kezan_gappy_silvertooth();
    new npc_kezan_missa_spekkies();
    new npc_kezan_partygoer();
    new npc_kezan_pirate_party_crasher();
    new npc_kezan_ktc_waiter();
    new npc_kezan_trade_prince_gallywix();
    new npc_kezan_first_bank_of_kezan_vault();
    new npc_kezan_hired_looter();
    new npc_kezan_villa_mook_disguise();
    new npc_kezan_447_event_creature("npc_kezan_447_overloaded_generator", SPELL_OVERLOADED_GENERATOR_VISUAL);
    new npc_kezan_447_event_creature("npc_kezan_447_stove_leak", SPELL_STOVE_LEAK_VISUAL);
    new npc_kezan_447_event_creature("npc_kezan_447_smoldering_bed", SPELL_SMOLDERING_BED_VISUAL);
    new npc_kezan_447_gasbot();
    new npc_kezan_kaja_cola_balloon();
    new npc_kezan_hobart_grapplehammer();
    new npc_kezan_assistant_greely();
    new npc_kezan_meteor_caster();
    new npc_kezan_dont_go_into_the_light_doc_zapnozzle();
    new npc_kezan_goblin_supermodel();
    new npc_kezan_socialite();
    new npc_kezan_training_dummy();
    new npc_kezan_injured_employee();

    new go_kezan_ls_rope_ladder();
    new go_kezan_yacht_boarding_mortar();
    new go_kezan_active_object();
    new go_kezan_first_bank_of_kezan_vault();
    new go_kezan_kajamite_deposit();
    new go_kezan_447_event_gameobject();

    new at_kezan_ktc();
    new at_kezan_rolling_with_my_homies();
    new at_kezan_kajamine();

    //new movie_kezan_life_savings();

    new spell_kezan_goblin_all_in_1_der_belt_shocker();
    new spell_kezan_punch_it_boost();
    new spell_kezan_rolling_with_my_homie_exit_spell();
    new spell_kezan_hot_rod_knockback();
    new spell_kezan_hot_rod_honk_horn();
    new spell_kezan_kick_footbomb();
    new spell_kezan_fourth_and_goal_signal_back_to_shredder();
    new spell_kezan_fourth_and_goal_deathwing_sound_4();
    new spell_kezan_throw_footbomb();
    new spell_kezan_despawn_event_creature();
    new spell_kezan_party_inform_ai("spell_kezan_bubbly", ACTION_BUBBLY);
    new spell_kezan_party_inform_ai("spell_kezan_bucket", ACTION_BUCKET);
    new spell_kezan_party_inform_ai("spell_kezan_dance", ACTION_DANCE);
    new spell_kezan_party_inform_ai("spell_kezan_fireworks", ACTION_FIREWORKS);
    new spell_kezan_party_inform_ai("spell_kezan_hors_doeuvres", ACTION_HORS_DOEUVRES);
    new spell_kezan_heist_vault_interact();
    new spell_kezan_heist_vehicle_exit_spell();
    new spell_kezan_heist_inform_ai("spell_kezan_heist_infinifold_lockpick", ACTION_INFINIFOLD_LOCKPICK);
    new spell_kezan_heist_inform_ai("spell_kezan_heist_blastcrackers", ACTION_BLASTCRACKERS);
    new spell_kezan_heist_inform_ai("spell_kezan_heist_kajamite_drill", ACTION_KAJAMITE_DRILL);
    new spell_kezan_heist_inform_ai("spell_kezan_heist_amazing_g_ray", ACTION_AMAZING_G_RAY);
    new spell_kezan_heist_inform_ai("spell_kezan_heist_ear_o_scope", ACTION_EAR_O_SCOPE);
    new spell_kezan_heist_timer();
    new spell_kezan_waltz_right_in_dummy_trigger();
    new spell_kezan_447_master("spell_kezan_447_stove_leak_master", 70241, 70240);
    new spell_kezan_447_master("spell_kezan_447_smoldering_bed_master", 70249, 70248);
    new spell_kezan_447_master("spell_kezan_447_overloaded_generator_master", 70220, 70198);
    new spell_kezan_447_master("spell_kezan_447_gasbot_master", 70255, 70252);
    new spell_kezan_447_aicast_gasbot_master();
    new spell_kezan_447_gasbot_gas_stream();
    new spell_kezan_447_gasbot_scriptcast_to_character();
    new spell_kezan_life_savings_hand_over_the_keys();
    new spell_kezan_kaja_kola();
    new spell_kezan_dummy_to_geargrinder_fajardo();
}
