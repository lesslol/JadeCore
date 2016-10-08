#include "CellImpl.h"
#include "GridNotifiers.h"
#include "SpellScript.h"
#include "Vehicle.h"
#include "CreatureTextMgr.h"
#include "ScriptedSmoothEscortAI.h"
#include "Language.h"
#include "MoveSpline.h"
#include "CombatAI.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "MoveSplineInit.h"

#include <array>

enum
{
    SPELL_ZONE_SPECIFIC_01                  = 59073,
    SPELL_ZONE_SPECIFIC_06                  = 68481,
    SPELL_ZONE_SPECIFIC_07                  = 68482,
    SPELL_ZONE_SPECIFIC_08                  = 68483,
    SPELL_ZONE_SPECIFIC_11                  = 69484,
    SPELL_ZONE_SPECIFIC_12                  = 69485,
    SPELL_ZONE_SPECIFIC_13                  = 69486,
    SPELL_ZONE_SPECIFIC_14                  = 70695,
    SPELL_ZONE_SPECIFIC_19                  = 74096,

    SPELL_WORGEN_BITE                       = 72870,
    SPELL_INFECTED_BITE                     = 72872,
    SPELL_HIDEOUS_BITE_WOUND                = 76642,

    SPELL_INVISIBILITY_DETECTION_1          = 49416,
    SPELL_INVISIBILITY_DETECTION_2          = 49417,
    SPELL_INVISIBILITY_DETECTION_3          = 60922,

    SPELL_GENERIC_QUEST_INVISIBILITY_2      = 49415,

    QUEST_LOCKDOWN                          = 14078,
    QUEST_SOMETHINGS_AMISS                  = 14091,
    QUEST_ROYAL_ORDERS                      = 14099,
    QUEST_STEADY_SHOT                       = 14276,
    QUEST_ARCANE_MISSILES                   = 14281,
    QUEST_CHARGE                            = 14266,
    QUEST_IMMOLATE                          = 14274,
    QUEST_EVISCERATE                        = 14272,
    QUEST_FLASH_HEAL                        = 14279,
    QUEST_A_REJUVENATING_TOUCH              = 14283,
    QUEST_OLD_DIVISIONS                     = 14157,
    QUEST_BY_THE_SKIN_OF_HIS_TEETH          = 14154,
    QUEST_THE_REBEL_LORD_ARSENAL            = 14159,
    QUEST_FROM_THE_SHADOWS                  = 14204,
    QUEST_SAVE_KRENNAN_ARANAS               = 14293,
    QUEST_TIME_TO_REGROUP                   = 14294,
    QUEST_LAST_STAND                        = 14222,
    QUEST_NEVER_SURRENDER                   = 14221,
    QUEST_LAST_CHANCE_AT_HUMANITY           = 14375,
    QUEST_IN_NEED_OF_INGR                   = 14320,
    QUEST_INVASION                          = 14321,
    QUEST_LEADER_OF_THE_PACK                = 14386,
    QUEST_TO_GREYMANE_MANOR                 = 14465,
    QUEST_THE_KINGS_OBSERVATORY             = 14466,
    QUEST_ALAS_GILNEAS                      = 14467,
    QUEST_EXODUS                            = 24438,
    QUEST_INTRODUCTIONS_ARE_IN_ORDER        = 24472,
    QUEST_LOSING_YOUR_TAIL                  = 24616,
    QUEST_AT_OUR_DOORSTEP                   = 24627,
    QUEST_TAKE_BACK_WHATS_OURS              = 24646,
    QUEST_NEITHER_HUMAN_NOR_BEAST           = 24593,
    QUEST_BETRAYAL_AT_TEMPESTS_REACH        = 24592,
    QUEST_THE_BATTLE_FOR_GILNEAS_CITY       = 24904,
    QUEST_THE_HUNT_FOR_SYLVANAS             = 24902,
};


enum
{
    MENU_MAIN                               = 17125,
    MENU_GATHERING_AND_MINING_PROFESSIONS   = 17126,
    MENU_CRAFTING_PROFESSIONS               = 17127,
    MENU_HERBALISM                          = 17128,
    MENU_MINING                             = 17129,
    MENU_SKINNING                           = 17130,
    MENU_ALCHEMY                            = 17131,
    MENU_BLACKSMITHING                      = 17132,
    MENU_ENCHANTING                         = 17133,
    MENU_ENGINERING                         = 17134,
    MENU_INSCRIPTION                        = 17135,
    MENU_JEWELCRAFTING                      = 17136,
    MENU_LEATHERWORKING                     = 17137,
    MENU_TAILORING                          = 17138,
};

#define    TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS    "Tell me about gathering professions."
#define    TELL_ME_ABOUT_CRAFTING_PROFESSIONS                "Tell me about production professions."
#define    TELL_ME_ABOUT_HERBALISM                           "Tell me about Herbalism."
#define    TELL_ME_ABOUT_MINING                              "Tell me about Mining."
#define    TELL_ME_ABOUT_SKINNING                            "Tell me about Skinning."
#define    TELL_ME_ABOUT_ALCHEMY                             "Tell me about Alchemy."
#define    TELL_ME_ABOUT_BLACKSMITHING                       "Tell me about Blacksmithing."
#define    TELL_ME_ABOUT_ENCHANTING                          "Tell me about Enchanting."
#define    TELL_ME_ABOUT_ENGINERING                          "Tell me about Engineering."
#define    TELL_ME_ABOUT_INSCRIPTION                         "Tell me about Inscription."
#define    TELL_ME_ABOUT_JEWELCRAFTING                       "Tell me about Jewelcrafting."
#define    TELL_ME_ABOUT_LEATHERWORKING                      "Tell me about Leatherworking."
#define    TELL_ME_ABOUT_TAILORING                           "Tell me about Tailoring."
#define    TRAIN_ME_ALCHEMY                                  "Train me in Alchemy."
#define    TRAIN_ME_HERBALISM                                "Train me in Herbalism."
#define    TRAIN_ME_INSCRIPTION                              "Train me in Inscription."
#define    TRAIN_ME_MINING                                   "Train me in Mining."
#define    TRAIN_ME_BLACKSMITHING                            "Train me in Blacksmithing."
#define    TRAIN_ME_SKINNING                                 "Train me in Skinning."
#define    TRAIN_ME_ENGINERING                               "Train me in Engineering."
#define    TRAIN_ME_JEWELCRAFTING                            "Train me in Jewelcrafting."
#define    TRAIN_ME_LEATHERWORKING                           "Train me in Leatherworking."
#define    TRAIN_ME_TAILORING                                "Train me in Tailoring."
#define    TRAIN_ME_ENCHANTING                               "Train me in Enchanting."

class npc_jack_derrington final : public CreatureScript
{
    public:
        npc_jack_derrington() : CreatureScript("npc_jack_derrington") { }

    private:
        void SendTrainerList(Player* player, Creature* creature, uint32 reqSkill, uint32 initialLearnSpellEntry)
        {
            std::string strTitle = player->GetSession()->GetTrinityString(LANG_NPCINFO_TRAINER);

            TrainerSpellData const* trainer_spells = creature->GetTrainerSpells();

            if (!trainer_spells)
                return;

            if (!player->GetFreePrimaryProfessionPoints())
                initialLearnSpellEntry = 0;

            WorldPacket data(SMSG_TRAINER_LIST, 8 + 4 + 4 + 4 + trainer_spells->spellList.size() * 38 + strTitle.size() + 1);
            data << creature->GetGUID();
            data << uint32(trainer_spells->trainerType);
            data << uint32(1);

            size_t count_pos = data.wpos();
            data << uint32(trainer_spells->spellList.size());

            uint32 count = 0;

            for (TrainerSpellMap::const_iterator itr = trainer_spells->spellList.begin(); itr != trainer_spells->spellList.end(); ++itr)
            {
                TrainerSpell const* tSpell = &itr->second;

                TrainerSpellState state = player->GetTrainerSpellState(tSpell);

                if (tSpell->spell != initialLearnSpellEntry && tSpell->reqSkill != reqSkill)
                    continue;

                data << uint32(tSpell->spell);
                data << uint8(state);
                data << uint32(tSpell->spellCost);

                data << uint8(tSpell->reqLevel);
                data << uint32(tSpell->reqSkill);
                data << uint32(tSpell->reqSkillValue);

                data << uint32(0);
                data << uint32(0);
                data << uint32(0);

                data << uint32(0);

                ++count;
            }

            data << strTitle;

            data.put<uint32>(count_pos,count);
            player->GetSession()->SendPacket(&data);
            return;
        }

        bool OnGossipHello(Player* player, Creature* creature) final
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(MENU_MAIN, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) final
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_GATHERING_AND_MINING_PROFESSIONS, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU(MENU_CRAFTING_PROFESSIONS, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_HERBALISM);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_HERBALISM, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 4:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_MINING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_MINING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 5:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_SKINNING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_SKINNING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 6:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ALCHEMY);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_ALCHEMY, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 7:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_BLACKSMITHING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_BLACKSMITHING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 8:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ENCHANTING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_ENCHANTING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 9:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ENGINEERING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_ENGINERING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 10:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_INSCRIPTION);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_INSCRIPTION, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 11:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_JEWELCRAFTING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_JEWELCRAFTING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 12:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_LEATHERWORKING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_LEATHERWORKING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + 13:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_TAILORING);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->SEND_GOSSIP_MENU(MENU_TAILORING, creature->GetGUID());
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_HERBALISM:
                    SendTrainerList(player, creature, SKILL_HERBALISM, 2372);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_ALCHEMY:
                    SendTrainerList(player, creature, SKILL_ALCHEMY, 2275);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_INSCRIPTION:
                    SendTrainerList(player, creature, SKILL_INSCRIPTION, 45375);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_MINING:
                    SendTrainerList(player, creature, SKILL_MINING, 2581);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_BLACKSMITHING:
                    SendTrainerList(player, creature, SKILL_BLACKSMITHING, 2020);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_SKINNING:
                    SendTrainerList(player, creature, SKILL_SKINNING, 8615);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_ENGINEERING:
                    SendTrainerList(player, creature, SKILL_ENGINEERING, 4039);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_JEWELCRAFTING:
                    SendTrainerList(player, creature, SKILL_JEWELCRAFTING, 25245);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_LEATHERWORKING:
                    SendTrainerList(player, creature, SKILL_LEATHERWORKING, 2155);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_TAILORING:
                    SendTrainerList(player, creature, SKILL_TAILORING, 3911);
                    break;
                case GOSSIP_ACTION_INFO_DEF + SKILL_ENCHANTING:
                    SendTrainerList(player, creature, SKILL_ENCHANTING, 25245);
                    break;
            }

            return true;
        }
};

class npc_gilneas_tremors_credit final : public CreatureScript
{
    public:
        npc_gilneas_tremors_credit() : CreatureScript("npc_gilneas_tremors_credit") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_TREMOR_1          = 1,
                EVENT_TREMOR_2          = 2,
                EVENT_TREMOR_3          = 3,

                SPELL_CATACLYSM_TYPE_1  = 80133,
                SPELL_CATACLYSM_TYPE_2  = 68953,
                SPELL_CATACLYSM_TYPE_3  = 80134,
            };

            EventMap events;

            void InitializeAI() final
            {
                Reset();
                me->setActive(true);
            }

            void Reset() final
            {
                events.Reset();
                events.ScheduleEvent(EVENT_TREMOR_1, urand(30000, 150000));
                events.ScheduleEvent(EVENT_TREMOR_2, urand(20000, 100000));
                events.ScheduleEvent(EVENT_TREMOR_3, urand(10000, 50000));
            }

            void Tremor(uint32 phaseMask, uint32 uiSpellId)
            {
                Map::PlayerList const &players = me->GetMap()->GetPlayers();

                for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                    if (Player* player = i->GetSource())
                        if (phaseMask & player->GetPhaseMask())
                            player->CastSpell(player, uiSpellId, false);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TREMOR_1:
                            Tremor(4096, SPELL_CATACLYSM_TYPE_1);
                            events.ScheduleEvent(EVENT_TREMOR_1, urand(30000, 150000));
                            break;
                        case EVENT_TREMOR_2:
                            Tremor(8192, SPELL_CATACLYSM_TYPE_2);
                            events.ScheduleEvent(EVENT_TREMOR_2, urand(20000, 100000));
                            break;
                        case EVENT_TREMOR_3:
                            Tremor(16384, SPELL_CATACLYSM_TYPE_3);
                            events.ScheduleEvent(EVENT_TREMOR_3, urand(10000, 50000));
                            break;
                    }
                }
            }
        };
};

struct Coord final
{
    float x;
    float y;
    float z;
};

struct CrowFlyPosition final
{
    Coord FirstCoord;
    Coord SecondCoord;
};

const CrowFlyPosition CrowFlyPos[12]=
{
    {{-1398.24f, 1455.26f, 39.6586f},{-1403.93f, 1464.87f, 47.7066f}},
    {{-1628.58f, 1320.29f, 27.7544f},{-1626.90f, 1306.58f, 34.9702f}},
    {{-1799.76f, 1564.33f, 34.9408f},{-1788.64f, 1561.74f, 38.4683f}},
    {{-1840.45f, 2299.17f, 50.2894f},{-1850.23f, 2302.62f, 52.4776f}},
    {{-1978.48f, 2319.58f, 36.5107f},{-1979.80f, 2329.24f, 38.8598f}},
    {{-1914.39f, 2406.48f, 37.4498f},{-1916.48f, 2416.10f, 39.2891f}},
    {{-1844.85f, 2328.28f, 47.8401f},{-1836.64f, 2327.05f, 50.0315f}},
    {{-1845.20f, 2502.86f, 6.67603f},{-1839.71f, 2508.70f, 9.67311f}},
    {{-2031.81f, 2280.29f, 28.7353f},{-2043.98f, 2286.43f, 32.0705f}},
    {{-2164.61f, 2213.12f, 27.4170f},{-2169.48f, 2224.64f, 29.1592f}},
    {{-1775.46f, 2380.44f, 51.9086f},{-1767.75f, 2385.99f, 55.8622f}},
    {{-1650.79f, 2507.28f, 109.893f},{-1645.28f, 2506.02f, 115.819f}},
};

class npc_gilnean_crow final : public CreatureScript
{
    public:
        npc_gilnean_crow() : CreatureScript("npc_gilnean_crow") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , flying(false)
            { }

            uint8 pointId;
            bool flying;

            void InitializeAI() final
            {
                FindFlyId();
            }

            void FindFlyId()
            {
                float dist = std::numeric_limits<float>::max();
                int i = 0;

                for (int j = 0; j < 12; ++j)
                {
                    float _dist = me->GetDistance2d(CrowFlyPos[j].FirstCoord.x, CrowFlyPos[j].FirstCoord.y);

                    if (dist > _dist)
                    {
                        dist = _dist;
                        i = j;
                    }
                }

                pointId = i;
            }

            void FlyAway()
            {
                flying = true;

                Movement::MoveSplineInit init(me);

                G3D::Vector3 vertice0(
                        CrowFlyPos[pointId].FirstCoord.x + irand(-4, 4),
                        CrowFlyPos[pointId].FirstCoord.y + irand(-4, 4),
                        CrowFlyPos[pointId].FirstCoord.z + irand(-4, 4));
                init.Path().push_back(vertice0);

                G3D::Vector3 vertice1(
                        CrowFlyPos[pointId].SecondCoord.x + irand(-4, 4),
                        CrowFlyPos[pointId].SecondCoord.y + irand(-4, 4),
                        CrowFlyPos[pointId].SecondCoord.z + irand(-4, 4));
                init.Path().push_back(vertice1);

                init.SetFly();
                init.SetSmooth();
                init.SetVelocity(7.5f);
                init.SetUncompressed();
                init.Launch();
                me->DespawnOrUnsummon(me->GetSplineDuration());
            }

            void JustRespawned() final
            {
                flying = false;
            }

            void MoveInLineOfSight(Unit* who) final
            {
                if (!flying && who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 15.0f))
                    FlyAway();
            }
        };
};

class npc_prince_liam_greymane_phase_1 final : public CreatureScript
{
    public:
        npc_prince_liam_greymane_phase_1() : CreatureScript("npc_prince_liam_greymane_phase_1") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            enum
            {
                NPC_PANICKED_CITIZEN            = 34851,
                CITIZEN_SAY_WHAT_AT_THE_ROOF    = 1,
            };

            if (quest->GetQuestId() == QUEST_LOCKDOWN)
                if (Creature* cinizen = creature->FindNearestCreature(NPC_PANICKED_CITIZEN, 30.0f))
                    if (cinizen->IsAIEnabled)
                        cinizen->AI()->Talk(CITIZEN_SAY_WHAT_AT_THE_ROOF, player->GetGUID(), true);

            return false;
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_SAY_INTRO_1   = 1,
                EVENT_SAY_INTRO_2   = 2,
                EVENT_SAY_INTRO_3   = 3,

                LIAM_TALK_INTRO_1    = 1,
                LIAM_TALK_INTRO_2    = 2,
                LIAM_TALK_INTRO_3    = 3,
            };

            EventMap events;

            void Reset() final
            {
                events.Reset();
                events.ScheduleEvent(EVENT_SAY_INTRO_1, 1000);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                {
                    events.Update(diff);

                    if (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_SAY_INTRO_1:
                                Talk(LIAM_TALK_INTRO_1);
                                events.ScheduleEvent(EVENT_SAY_INTRO_2, 21000);
                                break;
                            case EVENT_SAY_INTRO_2:
                                Talk(LIAM_TALK_INTRO_2);
                                events.ScheduleEvent(EVENT_SAY_INTRO_3, 20000);
                                break;
                            case EVENT_SAY_INTRO_3:
                                Talk(LIAM_TALK_INTRO_3);
                                events.ScheduleEvent(EVENT_SAY_INTRO_1, 22000);
                                break;
                        }
                    }

                    return;
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_gilneas_city_guard_gate final : public CreatureScript
{
    public:
        npc_gilneas_city_guard_gate() : CreatureScript("npc_gilneas_city_guard_gate") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_GUARD_TALK    = 1,
                EVENT_CITIZEN_TALK  = 2,

                GUARD_RANDOM_TEXT   = 1,
                CITIZEN_RANDOM_TEXT = 1,
            };

            EventMap events;

            void Reset() final
            {
                events.Reset();

                if (me->GetMountID())
                    events.ScheduleEvent(EVENT_GUARD_TALK, urand(10000, 20000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                {
                    events.Update(diff);

                    if (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_GUARD_TALK:
                                Talk(GUARD_RANDOM_TEXT);
                                events.ScheduleEvent(EVENT_CITIZEN_TALK, urand(10000, 20000));
                                break;
                            case EVENT_CITIZEN_TALK:
                                {
                                    std::list<Creature*> citizens;
                                    me->GetCreatureListWithEntryInGrid(citizens, 44086, 35.0f);

                                    if (!citizens.empty())
                                        if (Creature* citizen = Trinity::Containers::SelectRandomContainerElement(citizens))
                                            if (citizen->IsAIEnabled)
                                                citizen->AI()->Talk(CITIZEN_RANDOM_TEXT);

                                    events.ScheduleEvent(EVENT_GUARD_TALK, urand(20000, 40000));
                                }
                                break;
                        }
                    }

                    return;
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_panicked_citizen_gate final : public CreatureScript
{
    public:
        npc_panicked_citizen_gate() : CreatureScript("npc_panicked_citizen_gate") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RANDOM_EMOTE  = 1,
            };

            EventMap events;

            void Reset() final
            {
                events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(4000, 8000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                {
                    events.Update(diff);

                    if (events.ExecuteEvent() == EVENT_RANDOM_EMOTE)
                    {
                        const uint16 PanickedCitizenRandomEmote[5] =
                        {
                            EMOTE_ONESHOT_COWER,
                            EMOTE_ONESHOT_TALK,
                            EMOTE_ONESHOT_CRY,
                            EMOTE_ONESHOT_BEG,
                            EMOTE_ONESHOT_EXCLAMATION,
                        };

                        uint8 roll = urand(0, 4);
                        me->HandleEmoteCommand(PanickedCitizenRandomEmote[roll]);
                        events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(2000, 5000));
                    }

                    return;
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_lieutenant_walden final : public CreatureScript
{
    public:
        npc_lieutenant_walden() : CreatureScript("npc_lieutenant_walden") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_LOCKDOWN)
            {
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_01, false);
                player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_1, false);
                player->SaveToDB();
            }

            return false;
        }
};

class AggroEvent final : public BasicEvent
{
    public:
        AggroEvent(Creature* creature)
            : _creature(creature)
        { }

    private:
        bool Execute(uint64 /*time*/, uint32 /*diff*/) final
        {
            if (!_creature->IsInCombat())
                _creature->CastCustomSpell(43263, SPELLVALUE_MAX_TARGETS, 1);

            return true;
        }

        Creature* _creature;
};

class npc_gilneas_worgen final : public CreatureScript
{
    public:
        npc_gilneas_worgen() : CreatureScript("npc_gilneas_worgen") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_ENRAGE    = 8599,
            };

            bool enrage;

            void Reset() final
            {
                enrage = false;
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
                else
                {
                    if (!enrage && me->HealthBelowPctDamaged(30, damage))
                    {
                        enrage = true;
                        me->CastSpell(me, SPELL_ENRAGE, false);
                    }

                    if (Unit* victim = me->GetVictim())
                    {
                        if (victim->GetTypeId() == TYPEID_UNIT)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->getThreatManager().addThreat(attacker, std::numeric_limits<float>::max());
                            AttackStart(attacker);
                        }
                    }
                }
            }
        };
};

struct ShooterGuardAI final : public ScriptedAI
{
    ShooterGuardAI(Creature* creature, uint32 _shootSpellEntry, float _rangeDist = 30.f)
        : ScriptedAI(creature)
        , shootSpellEntry(_shootSpellEntry)
        , rangeDist(_rangeDist)
        , isActive(true)
    { }

    enum
    {
        EVENT_SHOOT = 1,
    };

    EventMap events;
    uint32 shootSpellEntry;
    float rangeDist;
    bool isActive;

    void Reset() final
    {
        events.Reset();
    }

    void SetActive(bool enable)
    {
        isActive = enable;
    }

    void EnterCombat(Unit* /*who*/) final
    {
        events.ScheduleEvent(EVENT_SHOOT, urand(500, 2000));
    }

    void DamageTaken(Unit* attacker, uint32 &damage) final
    {
        if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
        {
            if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
            {
                damage = 0;
                me->getThreatManager().addThreat(attacker, 0.f);
            }
        }
    }

    void AttackStart(Unit* who) final
    {
        bool melee = me->IsWithinMeleeRange(who);
        me->Attack(who, melee);
    }

    bool ShooterAIUpdateVictim()
    {
        if (!isActive)
            return false;

        if (!UpdateVictim())
            return false;

        if (Unit* victim = me->GetVictim())
            if (victim->GetTypeId() == TYPEID_PLAYER)
                if (me->GetDistance(victim) <= rangeDist)
                    return true;

        if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0))
        {
            if (me->GetDistance(target) > rangeDist)
            {
                EnterEvadeMode();
                return false;
            }
            else if (me->GetVictim() != target)
            {
                me->getThreatManager().resetAllAggro();
                me->getThreatManager().addThreat(target, std::numeric_limits<float>::max());
                AttackStart(target);
            }
        }

        return true;
    }

    bool UpdateShooterAI(uint32 diff)
    {
        if (!ShooterAIUpdateVictim())
            return false;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return true;

        if (events.ExecuteEvent() == EVENT_SHOOT)
        {
            if (Unit* victim = me->GetVictim())
            {
                if (!me->IsWithinMeleeRange(victim))
                {
                    if (me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->ClearUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStop(victim);
                    }

                    me->CastSpell(victim, shootSpellEntry, true);
                }
                else
                {
                    if (!me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->AddUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStart(victim);
                    }
                }
            }

            events.ScheduleEvent(EVENT_SHOOT, 2000);
        }

        DoMeleeAttackIfReady();
        return true;
    }
};

enum
{
    SPELL_GUARD_SHOOT_DEFAULT   = 20463,
    SPELL_GUARD_SHOOT_DEADLY    = 67595,
};

class npc_gilneas_city_guard final : public CreatureScript
{
    public:
        npc_gilneas_city_guard(const char* scriptName, uint32 shootSpellEntry)
            : CreatureScript(scriptName)
            , _shootSpellEntry(shootSpellEntry)
        { }

    private:
        uint32 _shootSpellEntry;

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature, _shootSpellEntry);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature, uint32 shootSpellEntry)
                : ScriptedAI(creature)
                , shooterAI(creature, shootSpellEntry)
            { }

            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
            }

            void UpdateAI(uint32 const diff) final
            {
                shooterAI.UpdateShooterAI(diff);
            }
        };
};

class npc_prince_liam_greymane_phase_2 final : public CreatureScript
{
    public:
        npc_prince_liam_greymane_phase_2() : CreatureScript("npc_prince_liam_greymane_phase_2") { }

    private:
        bool OnQuestAccept(Player* player, Creature* /*creature*/, const Quest* quest) final
        {
            if (quest->GetQuestId() == QUEST_ROYAL_ORDERS)
            {
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_1);
                player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
                player->SaveToDB();
            }

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT)
            { }

            enum
            {
                EVENT_TALK          = 1,
                LIAM_RANDOM_TEXT    = 1,

                SPELL_SHOOT         = 20463,
            };

            EventMap events;
            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
                events.ScheduleEvent(EVENT_TALK, 1000);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_TALK)
                {
                    Talk(LIAM_RANDOM_TEXT);
                    events.ScheduleEvent(EVENT_TALK, urand(30000, 90000));
                }
            }
        };
};

// Quest Evacuate the Merchant Square 14098
class npc_qems_citizen final : public CreatureScript
{
    public:
        npc_qems_citizen() : CreatureScript("npc_qems_citizen") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_FINISH_RUN        = 1,
                EVENT_RUN_AWAY          = 2,
                CITIZEN_RANDOM_TEXT     = 1,
                NPC_QEMS_KILL_CREDIT    = 35830,
            };

            EventMap events;

            void InitializeAI() final
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/) final
            {
                if (GameObject* go = me->FindNearestGameObject(195327, 10.f))
                {
                    float x, y, z;
                    me->GetPosition(x, y, z);
                    Movement::MoveSplineInit init(me);

                    G3D::Vector3 vertice0(x, y, z);
                    init.Path().push_back(vertice0);

                    go->GetNearPoint2D(x, y, 1.0f, go->GetOrientation() + M_PI);
                    G3D::Vector3 vertice1(x, y, z);
                    init.Path().push_back(vertice1);

                    go->GetNearPoint2D(x, y, 3.0f, go->GetOrientation());
                    G3D::Vector3 vertice2(x, y, z);
                    init.Path().push_back(vertice2);

                    init.SetUncompressed();
                    init.Launch();

                    events.ScheduleEvent(EVENT_FINISH_RUN, me->GetSplineDuration());
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FINISH_RUN:
                            {
                                if (me->IsSummon())
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                        if (Player* player = summoner->ToPlayer())
                                            player->KilledMonsterCredit(NPC_QEMS_KILL_CREDIT, 0);

                                Talk(CITIZEN_RANDOM_TEXT);
                                events.ScheduleEvent(EVENT_RUN_AWAY, 1000);
                            }
                            break;
                        case EVENT_RUN_AWAY:
                            {
                                float x, y;
                                me->GetNearPoint2D(x, y, 5.0f, me->GetOrientation() + frand(-M_PI / 4, M_PI / 4));
                                me->GetMotionMaster()->MovePoint(0, x, y, me->GetPositionZ());
                                me->DespawnOrUnsummon(me->GetSplineDuration());
                            }
                            break;
                    }
                }
            }
        };
};

class npc_qems_worgen final : public CreatureScript
{
    public:
        npc_qems_worgen() : CreatureScript("npc_qems_worgen") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_START_RUN     = 1,
                EVENT_FINISH_RUN    = 2,
            };

            EventMap events;

            void InitializeAI() final
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*summoner*/) final
            {
                events.ScheduleEvent(EVENT_START_RUN, 1500);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RUN:
                            {
                                if (GameObject* go = me->FindNearestGameObject(195327, 10.f))
                                {
                                    float x, y, z;
                                    me->GetPosition(x, y, z);
                                    Movement::MoveSplineInit init(me);

                                    G3D::Vector3 vertice0(x, y, z);
                                    init.Path().push_back(vertice0);

                                    go->GetNearPoint2D(x, y, 1.0f, go->GetOrientation() + M_PI);
                                    G3D::Vector3 vertice1(x, y, z);
                                    init.Path().push_back(vertice1);

                                    go->GetNearPoint2D(x, y, 3.0f, go->GetOrientation());
                                    G3D::Vector3 vertice2(x, y, z);
                                    init.Path().push_back(vertice2);

                                    init.SetUncompressed();
                                    init.Launch();

                                    events.ScheduleEvent(EVENT_FINISH_RUN, me->GetSplineDuration());
                                }
                            }
                            break;
                        case EVENT_FINISH_RUN:
                            {
                                if (me->IsSummon())
                                {
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    {
                                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                        me->SetReactState(REACT_AGGRESSIVE);
                                        AttackStart(summoner);
                                        me->AddThreat(summoner, std::numeric_limits<float>::max());
                                    }
                                }
                            }
                            break;
                    }
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_gilneas_knocking final : public SpellScriptLoader
{
    public:
        spell_gilneas_knocking() : SpellScriptLoader("spell_gilneas_knocking") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            Position doorPos;

            void FilterSingleTarget(WorldObject*& target)
            {
                doorPos.Relocate(target);
            }

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* caster = GetCaster())
                {
                    float x, y;
                    float angle = doorPos.GetOrientation() + M_PI * 0.75f;

                    x = doorPos.GetPositionX() + 3.f * std::cos(angle);
                    y = doorPos.GetPositionY() + 3.f * std::sin(angle);

                    uint8 effectId = urand(EFFECT_1, EFFECT_2);
                    caster->CastSpell(x, y, doorPos.GetPositionZ(), GetSpellInfo()->Effects[effectId].BasePoints, true);
                }
            }

            void Register() final
            {
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_script_impl::FilterSingleTarget, EFFECT_0, TARGET_GAMEOBJECT_TARGET);
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript * GetSpellScript() const final
        {
            return new spell_script_impl;
        }
};

// Class Trainers
enum
{
    TRAINER_SAY_QUEST_BEGIN     = 1,
    TRAINER_SAY_QUEST_DONE      = 2,
};

class npc_gilneas_class_trainer final : public CreatureScript
{
    public:
        npc_gilneas_class_trainer(const char* scriptName, uint32 questEntry)
            : CreatureScript(scriptName)
            , _questEntry(questEntry)
        { }

    private:
        uint32 _questEntry;

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == _questEntry)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_BEGIN, player->GetGUID(), true);

            return false;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == _questEntry)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_DONE, player->GetGUID(), true);

            return false;
        }
};

class npc_myriam_spellwaker final : public CreatureScript
{
    public:
        npc_myriam_spellwaker() : CreatureScript("npc_myriam_spellwaker") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_ARCANE_MISSILES)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_BEGIN, player->GetGUID(), true);

            return false;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_ARCANE_MISSILES)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_DONE, player->GetGUID(), true);

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_CAST_FROSTBOLT    = 1,

                SPELL_FROSTBOLT         = 11538,
            };

            EventMap events;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
            }

            void Reset() final
            {
                events.Reset();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void EnterCombat(Unit* /*who*/) final
            {
                events.ScheduleEvent(EVENT_CAST_FROSTBOLT, 250);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_CAST_FROSTBOLT)
                {
                    me->CastSpell(me->GetVictim(), SPELL_FROSTBOLT, false);
                    events.ScheduleEvent(EVENT_CAST_FROSTBOLT, 3000);
                }
            }
        };
};

class npc_sergeant_cleese final : public CreatureScript
{
    public:
        npc_sergeant_cleese() : CreatureScript("npc_sergeant_cleese") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_CHARGE)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_BEGIN, player->GetGUID(), true);

            return false;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_CHARGE)
                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TRAINER_SAY_QUEST_DONE, player->GetGUID(), true);

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void InitializeAI() final
            {
                me->m_ReactDistance = 20.0f;
                SetCombatMovement(false);
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }
        };
};

class npc_gilneas_worgen_class_quest final : public CreatureScript
{
    public:
        npc_gilneas_worgen_class_quest() : CreatureScript("npc_gilneas_worgen_class_quest") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_ENRAGE            = 8599,

                SPELL_CHARGE            = 100,
                SPELL_EVISCERATE        = 2098,
                SPELL_CORRUPTION        = 172,
                SPELL_STEADY_SHOT       = 56641,
                SPELL_FROST_NOVA        = 122,
                SPELL_MOONFIRE          = 8921,

                NPC_CLASS_QUEST_CREDIT  = 44175,
            };

            bool enrage;

            void Reset() final
            {
                enrage = false;
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                switch (spell->Id)
                {
                    case SPELL_CHARGE:
                    case SPELL_EVISCERATE:
                    case SPELL_CORRUPTION:
                    case SPELL_STEADY_SHOT:
                    case SPELL_FROST_NOVA:
                    case SPELL_MOONFIRE:
                        if (Player* player = caster->ToPlayer())
                            player->KilledMonsterCredit(NPC_CLASS_QUEST_CREDIT);
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
                else
                {
                    if (!enrage && me->HealthBelowPctDamaged(30, damage))
                    {
                        enrage = true;
                        me->CastSpell(me, SPELL_ENRAGE, false);
                    }

                    if (Unit* victim = me->GetVictim())
                    {
                        if (victim->GetTypeId() == TYPEID_UNIT)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->getThreatManager().addThreat(attacker, std::numeric_limits<float>::max());
                            AttackStart(attacker);
                        }
                    }
                }
            }
        };
};

class npc_wounded_guard_class_quest final : public CreatureScript
{
    public:
        npc_wounded_guard_class_quest() : CreatureScript("npc_wounded_guard_class_quest") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_FLASH_HEAL        = 2061,
                SPELL_REJUVENATION      = 774,

                NPC_CLASS_QUEST_CREDIT  = 44175,
            };

            bool enrage;

            void Reset() final
            {
                enrage = false;
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                switch (spell->Id)
                {
                    case SPELL_FLASH_HEAL:
                    case SPELL_REJUVENATION:
                        {
                            if (Player* player = caster->ToPlayer())
                                player->KilledMonsterCredit(NPC_CLASS_QUEST_CREDIT);
                        }
                        break;
                }
            }

            void HealReceived(Unit* /*healer*/, uint32& heal) final
            {
                if (me->GetHealthPct() > 50.f)
                    me->SetHealth(1);
            }
        };
};

// Quest Old Divisions 14157
class npc_king_genn_greymane_phase_2 final : public CreatureScript
{
    public:
        npc_king_genn_greymane_phase_2() : CreatureScript("npc_king_genn_greymane_phase_2") { }

    private:
        enum
        {
            NPC_LORD_GODFREY        = 35115,
            NPC_KING_GENN_GREYMANE  = 35112,

            LORD_GODFREY_TEXT       = 1,
            KING_GENN_GREYMANE_TEXT = 1,

            EVENT_UPDATE_PSC        = 1,

            TYPE_PSC_PLAYER_GUID    = 1,
        };

        class PersonalTalkEvent final : public BasicEvent
        {
            public:
                PersonalTalkEvent(Creature* source, uint64 playerGUID, uint8 textId)
                    : _source(source)
                    , _playerGUID(playerGUID)
                    , _textId(textId)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    if (_source->IsAIEnabled)
                        _source->AI()->Talk(_textId, _playerGUID, true);

                    return true;
                }

                Creature* _source;
                uint64 _playerGUID;
                uint8 _textId;
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_OLD_DIVISIONS)
            {
                if (Creature* godfrey = creature->FindNearestCreature(NPC_LORD_GODFREY, 20.0f))
                {
                    if (godfrey->IsAIEnabled)
                        godfrey->AI()->Talk(LORD_GODFREY_TEXT, player->GetGUID(), true);

                    creature->m_Events.AddEvent(new PersonalTalkEvent(creature, player->GetGUID(), KING_GENN_GREYMANE_TEXT), creature->m_Events.CalculateTime(5000));
                }
            }

            return false;
        }
};

// Quest By the Skin of His Teeth 14154
enum
{
    NPC_WORGEN_RUNT_L                       = 35456,
    NPC_WORGEN_ALPHA_L                      = 35170,
    NPC_WORGEN_RUNT_R                       = 35188,
    NPC_WORGEN_ALPHA_R                      = 35167,

    SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST = 66914,
    SPELL_GILNEAS_PRISON_PERIODIC_1         = 66894,
    SPELL_GILNEAS_PRISON_PERIODIC_2         = 68218,

    ACTION_QBSHT_SUMMON_WORGEN              = 3,
    TYPE_QBSHT_WORGEN_ID                    = 1,
};

struct WorgenPosQBSHTR final
{
    uint32 entry;
    Position summonPos;
    Position runPos;
    Position jumpPos;
};

const WorgenPosQBSHTR WorgenPosRight[5] =
{
    {NPC_WORGEN_ALPHA_R, {-1625.943f,1491.782f,73.729f,3.94f},{-1632.987f,1484.928f,75.025f,0.f},{-1673.199f,1447.334f,52.288f,0.f}},
    {NPC_WORGEN_RUNT_R,  {-1628.770f,1494.307f,71.109f,3.94f},{-1634.433f,1488.506f,72.055f,0.f},{-1674.365f,1450.231f,52.288f,0.f}},
    {NPC_WORGEN_RUNT_R,  {-1624.005f,1491.044f,72.355f,3.94f},{-1631.232f,1484.024f,73.520f,0.f},{-1670.050f,1446.465f,52.288f,0.f}},
    {NPC_WORGEN_RUNT_R,  {-1618.065f,1492.665f,70.195f,3.94f},{-1629.950f,1481.500f,71.044f,0.f},{-1669.042f,1443.998f,52.288f,0.f}},
    {NPC_WORGEN_RUNT_R,  {-1624.351f,1499.161f,70.931f,3.94f},{-1636.495f,1488.273f,70.838f,0.f},{-1676.181f,1450.732f,52.288f,0.f}},
};

struct WorgenPosQBSHTL final
{
    uint32 entry;
    Position summonPos;
};

const WorgenPosQBSHTL WorgenPosLeft[4] =
{
    {NPC_WORGEN_ALPHA_L, {-1721.048f, 1526.525f, 55.793f, 3.94f}},
    {NPC_WORGEN_RUNT_L,  {-1723.130f, 1526.399f, 55.681f, 3.94f}},
    {NPC_WORGEN_RUNT_L,  {-1725.533f, 1526.396f, 55.550f, 3.94f}},
    {NPC_WORGEN_RUNT_L,  {-1728.381f, 1526.393f, 55.445f, 3.94f}},
};

class npc_worgen_attacker_right final : public CreatureScript
{
    public:
        npc_worgen_attacker_right() : CreatureScript("npc_worgen_attacker_right") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_JUMP              = 1,
                EVENT_START_FIGHT       = 2,
                EVENT_HORRIFYING_HOWL   = 3,

                SPELL_ENRAGE            = 8599,
                SPELL_HORRIFYING_HOWL   = 75355,
            };

            EventMap events;
            uint8 worgenId;
            bool enrage;

            void InitializeAI() final
            {
                Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->setActive(true);
            }

            void Reset() final
            {
                enrage = false;
            }

            void SetData(uint32 type, uint32 data) final
            {
                if (type == TYPE_QBSHT_WORGEN_ID)
                {
                    worgenId = data;
                    me->GetMotionMaster()->MovePoint(0, WorgenPosRight[worgenId].runPos);
                    events.ScheduleEvent(EVENT_JUMP, me->GetSplineDuration());
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (!enrage && me->HealthBelowPctDamaged(30, damage))
                {
                    enrage = true;
                    me->CastSpell(me, SPELL_ENRAGE, false);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_JUMP:
                            me->SetHomePosition(WorgenPosRight[worgenId].jumpPos);
                            me->GetMotionMaster()->MoveJump(WorgenPosRight[worgenId].jumpPos, 20.f, 20.f);
                            events.ScheduleEvent(EVENT_START_FIGHT, me->GetSplineDuration() + 250);
                            break;
                        case EVENT_START_FIGHT:
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                            events.ScheduleEvent(EVENT_HORRIFYING_HOWL, urand(10000, 60000));
                            break;
                        case EVENT_HORRIFYING_HOWL:
                            me->CastSpell((Unit*)NULL, SPELL_HORRIFYING_HOWL, false);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

const Position JumpPosLeft = {-1701.914f, 1470.969f, 52.287f, 5.4f};

class npc_worgen_attacker_left final : public CreatureScript
{
    public:
        npc_worgen_attacker_left() : CreatureScript("npc_worgen_attacker_left") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_JUMP              = 1,
                EVENT_START_FIGHT       = 2,
                EVENT_HORRIFYING_HOWL   = 3,

                SPELL_ENRAGE            = 8599,
                SPELL_HORRIFYING_HOWL   = 75355,
            };

            EventMap events;
            uint8 worgenId;
            bool enrage;

            void InitializeAI() final
            {
                Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->setActive(true);
            }

            void Reset() final
            {
                enrage = false;
            }

            void IsSummonedBy(Unit* /*summoner*/) final
            {
                me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                events.ScheduleEvent(EVENT_JUMP, me->GetSplineDuration());
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (!enrage && me->HealthBelowPctDamaged(30, damage))
                {
                    enrage = true;
                    me->CastSpell(me, SPELL_ENRAGE, false);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_JUMP:
                            me->SetHomePosition(JumpPosLeft);
                            me->GetMotionMaster()->MoveJump(JumpPosLeft, 20.f, 10.f);
                            events.ScheduleEvent(EVENT_START_FIGHT, me->GetSplineDuration() + 250);
                            break;
                        case EVENT_START_FIGHT:
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                            events.ScheduleEvent(EVENT_HORRIFYING_HOWL, urand(20000, 60000));
                            break;
                        case EVENT_HORRIFYING_HOWL:
                            me->CastSpell((Unit*)NULL, SPELL_HORRIFYING_HOWL, false);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_lord_darius_crowley final : public CreatureScript
{
    public:
        npc_lord_darius_crowley() : CreatureScript("npc_lord_darius_crowley") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_BY_THE_SKIN_OF_HIS_TEETH)
                creature->CastSpell(player, SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST, true);

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* c)
                : ScriptedAI(c)
                , canSummon(true)
            { }

            enum
            {
                EVENT_RESET_SUMMON          = 1,
                EVENT_LEFT_HOOK             = 2,
                EVENT_SNAP_KICK             = 3,
                EVENT_DEMORALIZING_SHOUT    = 4,

                SPELL_DEMORALIZING_SHOUT    = 61044,
                SPELL_LEFT_HOOK             = 67825,
                SPELL_SNAP_KICK             = 67827
            };

            EventMap events;
            EventMap commonEvents;
            bool canSummon;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                Reset();
            }

            void Reset() final
            {
                events.Reset();
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_QBSHT_SUMMON_WORGEN && canSummon)
                {
                    if (urand(0, 1))
                    {
                        for (int i = 0; i < 5; ++i)
                            if (Creature* worgen = me->SummonCreature(WorgenPosRight[i].entry, WorgenPosRight[i].summonPos))
                                if (worgen->IsAIEnabled)
                                    worgen->GetAI()->SetData(TYPE_QBSHT_WORGEN_ID, i);
                    }
                    else
                    {
                        for (int i = 0; i < 4; ++i)
                            me->SummonCreature(WorgenPosLeft[i].entry, WorgenPosLeft[i].summonPos);
                    }

                    canSummon = false;
                    commonEvents.ScheduleEvent(EVENT_RESET_SUMMON, 20000);
                }
            }

            void JustSummoned(Creature* summoned) final
            {
                summoned->Attack(me, false);
            }

            void EnterCombat(Unit* /*who*/) final
            {
                events.ScheduleEvent(EVENT_LEFT_HOOK, urand(3500, 7000));
                events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, 3000);
            }

            void UpdateAI(uint32 const diff) final
            {
                commonEvents.Update(diff);

                if (commonEvents.ExecuteEvent() == EVENT_RESET_SUMMON)
                    canSummon = true;

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LEFT_HOOK:
                            me->CastSpell(me->GetVictim(), SPELL_LEFT_HOOK, false);
                            events.ScheduleEvent(EVENT_SNAP_KICK, urand(3500, 7000));
                            break;
                        case EVENT_SNAP_KICK:
                            me->CastSpell(me->GetVictim(), SPELL_SNAP_KICK, false);
                            events.ScheduleEvent(EVENT_LEFT_HOOK, urand(3500, 7000));
                            break;
                        case EVENT_DEMORALIZING_SHOUT:
                            me->CastSpell((Unit*)NULL, SPELL_DEMORALIZING_SHOUT, false);
                            events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, 15000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_gilneas_prison_periodic_dummy final : public SpellScriptLoader
{
    public:
        spell_gilneas_prison_periodic_dummy() : SpellScriptLoader("spell_gilneas_prison_periodic_dummy") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Unit* originalCaster = GetOriginalCaster();

                if (caster && originalCaster && caster->GetExactDistSq(originalCaster) < 900.f)
                {
                    if (originalCaster->IsAIEnabled)
                        originalCaster->GetAI()->DoAction(ACTION_QBSHT_SUMMON_WORGEN);

                    return;
                }

                if (caster)
                {
                    caster->RemoveAura(SPELL_GILNEAS_PRISON_PERIODIC_1);
                    caster->RemoveAura(SPELL_GILNEAS_PRISON_PERIODIC_2);

                    if (Player* player = caster->ToPlayer())
                        player->FailQuest(QUEST_BY_THE_SKIN_OF_HIS_TEETH);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest The Rebel Lord's Arsenal 14159
const Position JosiahJumpPos = {-1796.63f, 1427.73f, 12.4624f, 0.f};

class npc_josiah_avery_worgen final : public CreatureScript
{
    public:
        npc_josiah_avery_worgen() : CreatureScript("npc_josiah_avery_worgen") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_ATTACK_PLAYER             = 1,
                EVENT_JUMP                      = 2,
                EVENT_SHOOT                     = 3,

                SPELL_COSMETIC_COMBAT_ATTACK_1H = 42880,
                SPELL_PULL_TO                   = 67357,
                SPELL_DEADLY_SHOOT              = 67593,

                NPC_TRIGGER                     = 35374,
                NPC_LORNA_CROWLEY               = 35378,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetReactState(REACT_PASSIVE);
                me->SetPhaseMask(6, true);
            }

            void IsSummonedBy(Unit* /*summoner*/) final
            {
                events.ScheduleEvent(EVENT_ATTACK_PLAYER, 500);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ATTACK_PLAYER:
                            {
                                if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f))
                                {
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    {
                                        me->CastSpell(summoner, SPELL_COSMETIC_COMBAT_ATTACK_1H, false);

                                        if (Creature* trigger = lorna->FindNearestCreature(NPC_TRIGGER, 10.0f))
                                            trigger->CastSpell(summoner, SPELL_PULL_TO, false);
                                    }
                                }

                                events.ScheduleEvent(EVENT_JUMP, 1000);
                            }
                            break;
                        case EVENT_JUMP:
                            me->GetMotionMaster()->MoveJump(JosiahJumpPos, 20.f, 10.f);
                            events.ScheduleEvent(EVENT_SHOOT, 250);
                            break;
                        case EVENT_SHOOT:
                            {
                                if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f))
                                    lorna->CastSpell(me, SPELL_DEADLY_SHOOT, false);

                                me->DespawnOrUnsummon(5000);
                            }
                            break;
                    }
                }
            }
        };
};

class npc_josiah_event_trigger final : public CreatureScript
{
    public:
        npc_josiah_event_trigger() : CreatureScript("npc_josiah_event_trigger") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                TALK_WORGEN_BITE    = 1,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetPhaseMask(6, true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                Talk(TALK_WORGEN_BITE, summoner->GetGUID(), true);
            }
        };
};

class npc_josiah_avery_human final : public CreatureScript
{
    public:
        npc_josiah_avery_human() : CreatureScript("npc_josiah_avery_human") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_FORCE_CAST_SUMMON_JOSIAH  = 67352,
            };

            if (quest->GetQuestId() == QUEST_THE_REBEL_LORD_ARSENAL)
            {
                creature->CastSpell(player, SPELL_FORCE_CAST_SUMMON_JOSIAH, false);
                player->SaveToDB();
            }

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_YELL_HELP = 1,

                YELL_HELP_TEXT  = 1,
            };

            EventMap events;

            void Reset() final
            {
                events.Reset();
                events.ScheduleEvent(EVENT_YELL_HELP, 1000);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_YELL_HELP)
                {
                    sCreatureTextMgr->SendChat(me, YELL_HELP_TEXT, 0, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_CUSTOM, 0, TEAM_OTHER, false, NULL, false, 25.f);
                    events.ScheduleEvent(EVENT_YELL_HELP, urand(10000, 20000));
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_force_cast_summon_josiah final : public SpellScriptLoader
{
    public:
        spell_force_cast_summon_josiah() : SpellScriptLoader("spell_force_cast_summon_josiah") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void Function(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    player->RemoveAurasByType(SPELL_AURA_PHASE);
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
                    player->CastSpell(player, SPELL_WORGEN_BITE, true);
                    player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_1, true);
                    player->CastSpell((Unit*)NULL, GetSpellInfo()->Effects[effIndex].TriggerSpell, true);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::Function, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
            }
        };

        SpellScript * GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest From the Shadows 14204
class npc_lorna_crowley_phase_3 final : public CreatureScript
{
    public:
        npc_lorna_crowley_phase_3() : CreatureScript("npc_lorna_crowley_phase_3") { }

    private:
        enum
        {
            SAY_MASTIFF             = 1,
            SPELL_FORCECAST_MASTIFF = 68234,
            SPELL_FORCE_DISMISS_PET = 43511,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
            {
                creature->CastSpell(player, SPELL_FORCECAST_MASTIFF, false, NULL, NULL, player->GetGUID());

                if (creature->IsAIEnabled)
                    creature->AI()->Talk(SAY_MASTIFF, player->GetGUID(), true);
            }

            return false;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
                creature->CastSpell(player, SPELL_FORCE_DISMISS_PET, false, NULL, NULL, player->GetGUID());

            return false;
        }
};

class spell_quest_dismiss_plaguehound final : public SpellScriptLoader
{
    public:
        spell_quest_dismiss_plaguehound() : SpellScriptLoader("spell_quest_dismiss_plaguehound") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (Creature* creature = target->ToCreature())
                        creature->DespawnOrUnsummon();
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript * GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_bloodfang_lurker final : public CreatureScript
{
    public:
        npc_bloodfang_lurker() : CreatureScript("npc_bloodfang_lurker") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_SHADOWSTALKER_STEALTH = 5916,
                SPELL_UNDYING_FRENZY        = 80515,
                SPELL_ENRAGE                = 8599,
            };

            bool enrage;
            bool frenzy;

            void Reset() final
            {
                enrage = false;
                frenzy = false;
                me->SetReactState(REACT_PASSIVE);
                me->CastSpell(me, SPELL_SHADOWSTALKER_STEALTH, false);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (me->HasReactState(REACT_PASSIVE) && me->IsHostileTo(caster))
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    AttackStart(caster);
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (me->HasReactState(REACT_PASSIVE))
                    me->SetReactState(REACT_AGGRESSIVE);

                if (!frenzy)
                {
                    if (me->HealthBelowPctDamaged(45, damage))
                    {
                        frenzy = true;
                        me->CastSpell(me, SPELL_UNDYING_FRENZY, false);
                    }
                }
                else if (!enrage)
                {
                    if (me->HealthBelowPctDamaged(30, damage))
                    {
                        enrage = true;
                        me->CastSpell(me, SPELL_ENRAGE, false);
                    }
                }
            }
        };
};

// Quest Save Krennan Aranas 14293
class npc_king_genn_greymane_phase_3 final : public CreatureScript
{
    public:
        npc_king_genn_greymane_phase_3() : CreatureScript("npc_king_genn_greymane_phase_3") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            enum
            {
                SPELL_FORCECAST_SUMMON_GREYMANES_HORSE  = 68232,
            };

            if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
                creature->CastSpell(player, SPELL_FORCECAST_SUMMON_GREYMANES_HORSE, false, NULL, NULL, player->GetGUID());

            return false;
        }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RANDOM_SAY    = 1,

                RANDOM_TEXT_ID      = 1,
            };

            EventMap events;

            void Reset() final
            {
                events.Reset();
                events.ScheduleEvent(EVENT_RANDOM_SAY, 1000);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RANDOM_SAY)
                {
                    Talk(RANDOM_TEXT_ID);
                    events.ScheduleEvent(EVENT_RANDOM_SAY, urand(15000, 35000));
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

const Position GreymaneHorseJumpPos = {-1676.16f, 1346.19f, 15.1349f, 0.f};

class npc_vehicle_genn_horse final : public CreatureScript
{
    public:
        npc_vehicle_genn_horse() : CreatureScript("npc_vehicle_genn_horse") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_RIDE                            = 1,
                EVENT_JUMP                                  = 2,
                EVENT_TALK_SAVE_ARANAS                      = 3,
                EVENT_DONE                                  = 4,

                TEXT_SAVE_ARANAS                            = 1,
                TEXT_ARANAS_SAY_HELP                        = 1,

                NPC_ARANAS                                  = 35753,
                NPC_SAVED_ARANAS                            = 35907,

                SPELL_EJECT_ALL_PASSENGERS                  = 50630,
                SPELL_UPDATE_CATHEDRAL_AURAS_AND_SANCTUARY  = 78690,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetControlled(true, UNIT_STATE_ROOT);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                events.ScheduleEvent(EVENT_START_RIDE, 2000);
            }

            void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) final
            {
                if (apply)
                {
                    if (who->GetEntry() == NPC_SAVED_ARANAS)
                    {
                        me->GetMotionMaster()->MoveSplinePath(2);
                        events.ScheduleEvent(EVENT_DONE, me->GetSplineDuration());
                    }
                }
                else if (who->GetTypeId() == TYPEID_PLAYER)
                    me->CastSpell(who, SPELL_UPDATE_CATHEDRAL_AURAS_AND_SANCTUARY, false);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RIDE:
                            me->GetMotionMaster()->MoveSplinePath(1);
                            events.ScheduleEvent(EVENT_JUMP, me->GetSplineDuration());
                            break;
                        case EVENT_JUMP:
                            me->GetMotionMaster()->MoveJump(GreymaneHorseJumpPos, 20.f, 10.f);
                            events.ScheduleEvent(EVENT_TALK_SAVE_ARANAS, me->GetSplineDuration() - 500);
                            break;
                        case EVENT_TALK_SAVE_ARANAS:
                            {
                                Talk(TEXT_SAVE_ARANAS);

                                if (Creature* aranas = me->FindNearestCreature(NPC_ARANAS, 50.f))
                                    if (aranas->IsAIEnabled)
                                        aranas->AI()->Talk(TEXT_ARANAS_SAY_HELP, me->ToTempSummon()->GetSummonerGUID(), true);
                            }
                            break;
                        case EVENT_DONE:
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->DeleteThreatList();
                            me->CombatStop();
                            me->DespawnOrUnsummon(1000);
                            break;
                    }
                }
            }
        };
};

class npc_saved_aranas final : public CreatureScript
{
    public:
        npc_saved_aranas() : CreatureScript("npc_saved_aranas") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_RIDE_VEHILE       = 46598,
                SPELL_SUMMON_INITIALIZE = 67002,

                TEXT_THANKS             = 1,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER, summoner->GetGUID());
                me->SetVisible(false);

                if (Unit* horse = summoner->GetVehicleBase())
                {
                    me->CastSpell(horse, SPELL_RIDE_VEHILE, false);
                    me->CastSpell(me, SPELL_SUMMON_INITIALIZE, false);
                }
            }

            void OnExitVehicle(Unit* /*vehicle*/, uint32 /*seatId*/)
            {
                Talk(TEXT_THANKS, me->ToTempSummon()->GetSummonerGUID(), true);
                me->DespawnOrUnsummon(3000);
            }
        };
};

class npc_lord_godfrey_phase_3 final : public CreatureScript
{
    public:
        npc_lord_godfrey_phase_3() : CreatureScript("npc_lord_godfrey_phase_3") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_FORCECAST_CANNON_CAMERA   = 93555,
                TEXT_FIRE                       = 1,
            };

            if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
            {
                creature->CastSpell(player, SPELL_FORCECAST_CANNON_CAMERA, false);
                player->SaveToDB();

                if (creature->IsAIEnabled)
                    creature->AI()->Talk(TEXT_FIRE, player->GetGUID(), true);
            }

            return false;
        }
};

const Position WorgenSummonPosPhase4[13] =
{
    {-1715.219f, 1352.839f, 19.8645f, 2.72649f},
    {-1721.182f, 1350.429f, 19.8656f, 2.48614f},
    {-1746.523f, 1361.108f, 19.8681f, 1.85957f},
    {-1724.385f, 1348.462f, 19.6781f, 2.10692f},
    {-1734.542f, 1344.554f, 19.8769f, 1.65637f},
    {-1732.773f, 1367.837f, 19.9010f, 1.10063f},
    {-1744.358f, 1363.382f, 19.8996f, 2.06127f},
    {-1719.358f, 1357.512f, 19.7791f, 2.91488f},
    {-1728.276f, 1353.201f, 19.6823f, 2.25370f},
    {-1726.747f, 1364.599f, 19.9263f, 2.71766f},
    {-1737.693f, 1352.986f, 19.8711f, 1.96818f},
    {-1734.391f, 1359.887f, 19.9064f, 2.48052f},
    {-1730.286f, 1390.384f, 20.7707f, 4.35712f},
};

const float WorgenAttackCoord[3] = {-1751.874f, 1377.457f, 19.930f};

class npc_cannon_camera final : public CreatureScript
{
    public:
        npc_cannon_camera() : CreatureScript("npc_cannon_camera") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , summons(creature)
            { }

            enum
            {
                EVENT_SUMMON_WORGENS    = 1,
                EVENT_CANNON_SHOOT_1    = 2,
                EVENT_CANNON_SHOOT_2    = 3,

                SPELL_CANNON_FIRE       = 68235,

                NPC_COMMANDEERED_CANNON = 35914,
                NPC_BLOODFANG_RIPPER    = 35916,
            };

            EventMap events;
            SummonList summons;

            void CannonShoot()
            {
                if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                    cannon->CastSpell((Unit*)NULL, SPELL_CANNON_FIRE, false);
            }

            void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply) final
            {
                if (apply)
                    events.ScheduleEvent(EVENT_SUMMON_WORGENS, 1000);
                else
                {
                    CannonShoot();

                    for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
                        if (Creature * worgen = ObjectAccessor::GetCreature(*me, *itr))
                            if (worgen->IsAlive())
                                worgen->Kill(worgen);

                    summons.DespawnAll();
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON_WORGENS:
                            {
                                for (int i = 0; i < 13; ++i)
                                {
                                    if (Creature* worgen = me->SummonCreature(NPC_BLOODFANG_RIPPER, WorgenSummonPosPhase4[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                                    {
                                        summons.Summon(worgen);
                                        worgen->GetMotionMaster()->MovePoint(0, WorgenAttackCoord[0] + irand(-3, 3), WorgenAttackCoord[1] + irand(-3, 3), WorgenAttackCoord[2]);
                                    }
                                }

                                events.ScheduleEvent(EVENT_CANNON_SHOOT_1, 1500);
                            }
                            break;
                        case EVENT_CANNON_SHOOT_1:
                            CannonShoot();
                            events.ScheduleEvent(EVENT_CANNON_SHOOT_2, 2000);
                            break;
                        case EVENT_CANNON_SHOOT_2:
                            CannonShoot();
                            break;
                    }
                }
            }
        };
};

class spell_forcecast_cannon_camera final : public SpellScriptLoader
{
    public:
        spell_forcecast_cannon_camera() : SpellScriptLoader("spell_forcecast_cannon_camera") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void Function(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    player->RemoveAurasByType(SPELL_AURA_PHASE);
                    player->CastSpell(player, SPELL_INFECTED_BITE, true);
                    player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, true);
                    player->CastSpell((Unit*)NULL, GetSpellInfo()->Effects[effIndex].TriggerSpell, true);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::Function, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_gilneas_city_guard_phase_4 final : public CreatureScript
{
    public:
        npc_gilneas_city_guard_phase_4() : CreatureScript("npc_gilneas_city_guard_phase_4") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT)
            { }

            enum
            {
                EVENT_TALK          = 1,
                RANDOM_TEXT         = 1,

                SPELL_SHOOT         = 20463,
            };

            EventMap events;
            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
                events.ScheduleEvent(EVENT_TALK, urand(5000, 50000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_TALK)
                {
                    Talk(RANDOM_TEXT);
                    events.ScheduleEvent(EVENT_TALK, urand(30000, 90000));
                }
            }
        };
};

// Quest Time to Regroup 14294
enum
{
    QUEST_TIME_TO_REGROUP_EVENT_ID  = 10014294,
};

class npc_king_genn_greymane_phase_4 final : public CreatureScript
{
    public:
        npc_king_genn_greymane_phase_4() : CreatureScript("npc_king_genn_greymane_phase_4") { }

    private:
        enum
        {
            EVENT_GENN_SAY_IF           = 1,
            EVENT_CROWLEY_SAY_NEED      = 2,
            EVENT_LIAM_TALK_STAY         = 3,
            EVENT_CROWLEY_SAY_NO_CHANCE = 4,
            EVENT_CROWLEY_SAY_MY_MEN    = 5,
            EVENT_GENN_SAY_WE_FOOLS     = 6,

            GENN_SAY_IF                 = 1,
            CROWLEY_SAY_NEED            = 1,
            LIAM_TALK_STAY               = 1,
            CROWLEY_SAY_NO_CHANCE       = 2,
            CROWLEY_SAY_MY_MEN          = 3,
            GENN_SAY_WE_FOOLS           = 2,

            NPC_LORD_CROWLEY            = 35552,
            NPC_PRINCE_LIAM             = 35551,
            NPC_KING_GENN_GREYMANE      = 35911,
        };

        class PersonalTalkEvent final : public BasicEvent
        {
            public:
                PersonalTalkEvent(Player* player, uint8 eventId)
                    : _player(player)
                    , _eventId(eventId)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    switch (_eventId)
                    {
                        case EVENT_GENN_SAY_IF:
                            {
                                if (Creature* genn = _player->FindNearestCreature(NPC_KING_GENN_GREYMANE, 30.0f))
                                    if (genn->IsAIEnabled)
                                        genn->AI()->Talk(GENN_SAY_IF, _player->GetGUID(), true);

                                _player->m_Events.AddEvent(new PersonalTalkEvent(_player, EVENT_CROWLEY_SAY_NEED), _player->m_Events.CalculateTime(7000), true, QUEST_TIME_TO_REGROUP_EVENT_ID);
                            }
                            break;
                        case EVENT_CROWLEY_SAY_NEED:
                            {
                                if (Creature* crowley = _player->FindNearestCreature(NPC_LORD_CROWLEY, 30.0f))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_SAY_NEED, _player->GetGUID(), true);

                                _player->m_Events.AddEvent(new PersonalTalkEvent(_player, EVENT_LIAM_TALK_STAY), _player->m_Events.CalculateTime(7000), true, QUEST_TIME_TO_REGROUP_EVENT_ID);
                            }
                            break;
                        case EVENT_LIAM_TALK_STAY:
                            {
                                if (Creature* liam = _player->FindNearestCreature(NPC_PRINCE_LIAM, 30.0f))
                                    if (liam->IsAIEnabled)
                                        liam->AI()->Talk(LIAM_TALK_STAY, _player->GetGUID(), true);

                                _player->m_Events.AddEvent(new PersonalTalkEvent(_player, EVENT_CROWLEY_SAY_NO_CHANCE), _player->m_Events.CalculateTime(4000), true, QUEST_TIME_TO_REGROUP_EVENT_ID);
                            }
                            break;
                        case EVENT_CROWLEY_SAY_NO_CHANCE:
                            {
                                if (Creature* crowley = _player->FindNearestCreature(NPC_LORD_CROWLEY, 30.0f))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_SAY_NO_CHANCE, _player->GetGUID(), true);

                                _player->m_Events.AddEvent(new PersonalTalkEvent(_player, EVENT_CROWLEY_SAY_MY_MEN), _player->m_Events.CalculateTime(9000), true, QUEST_TIME_TO_REGROUP_EVENT_ID);
                            }
                            break;
                        case EVENT_CROWLEY_SAY_MY_MEN:
                            {
                                if (Creature* crowley = _player->FindNearestCreature(NPC_LORD_CROWLEY, 30.0f))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_SAY_MY_MEN, _player->GetGUID(), true);

                                _player->m_Events.AddEvent(new PersonalTalkEvent(_player, EVENT_GENN_SAY_WE_FOOLS), _player->m_Events.CalculateTime(9000), true, QUEST_TIME_TO_REGROUP_EVENT_ID);
                            }
                            break;
                        case EVENT_GENN_SAY_WE_FOOLS:
                            {
                                if (Creature* genn = _player->FindNearestCreature(NPC_KING_GENN_GREYMANE, 30.0f))
                                    if (genn->IsAIEnabled)
                                        genn->AI()->Talk(GENN_SAY_WE_FOOLS, _player->GetGUID(), true);
                            }
                            break;
                    }

                    return true;
                }

                Player* _player;
                uint8 _eventId;
        };

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_TIME_TO_REGROUP)
                player->m_Events.AddEvent(new PersonalTalkEvent(player, EVENT_GENN_SAY_IF), player->m_Events.CalculateTime(500), true, QUEST_TIME_TO_REGROUP_EVENT_ID);

            return false;
        }
};

// Quest Sacrifices 14212
class spell_forcecast_summon_crowleys_horse final : public SpellScriptLoader
{
    public:
        spell_forcecast_summon_crowleys_horse() : SpellScriptLoader("spell_forcecast_summon_crowleys_horse") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void Function(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Player* player = GetHitPlayer())
                {
                    player->m_Events.DeleteEventId(QUEST_TIME_TO_REGROUP_EVENT_ID);
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
                    player->CastSpell((Unit*)NULL, GetSpellInfo()->Effects[effIndex].TriggerSpell, true);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::Function, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

const Position JumpPoints[3]=
{
    {-1732.049f, 1657.609f, 20.73728f, 0.f},
    {-1714.762f, 1673.160f, 20.49182f, 0.f},
    {-1566.710f, 1708.040f, 20.48490f, 0.f},
};

class npc_crowley_horse_first_round final : public CreatureScript
{
    public:
        npc_crowley_horse_first_round() : CreatureScript("npc_crowley_horse_first_round") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_BEGIN                 = 1,
                EVENT_JUMP_1                = 2,
                EVENT_START_RUN             = 3,
                EVENT_JUMP_2                = 4,
                EVENT_RESUME_RUN            = 5,
                EVENT_CROWLEY_RANDOM_TEXT   = 6,
                EVENT_FINISH                = 7,

                CROWLEY_SAY_START           = 1,
                CROWLEY_SAY_RANDOM          = 2,

                NPC_CROWLEY                 = 35230,

                SPELL_EJECT_ALL_PASSENGERS  = 50630,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetReactState(REACT_PASSIVE);
                me->SetControlled(true, UNIT_STATE_ROOT);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                if (Creature* crowley = summoner->SummonCreature(NPC_CROWLEY, *me))
                {
                    crowley->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                    crowley->SetVisible(false);
                    crowley->EnterVehicle(me, 1);
                }

                events.ScheduleEvent(EVENT_BEGIN, 1000);
            }

            void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) final
            {
                if (!apply)
                    if (Creature* crowley = who->ToCreature())
                        crowley->DespawnOrUnsummon(1000);
            }

            void CrowleyTalkToPlayer(uint32 textId)
            {
                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(1))
                        if (Creature* crowley = passenger->ToCreature())
                            if (crowley->IsAIEnabled)
                                crowley->AI()->Talk(textId, me->ToTempSummon()->GetSummonerGUID(), true);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BEGIN:
                           me->GetMotionMaster()->MovePoint(0, JumpPoints[0]);
                            events.ScheduleEvent(EVENT_JUMP_1, me->GetSplineDuration());
                            break;
                        case EVENT_JUMP_1:
                            me->GetMotionMaster()->MoveJump(JumpPoints[1], 15.f, 15.f);
                            events.ScheduleEvent(EVENT_START_RUN, me->GetSplineDuration() + 500);
                            break;
                        case EVENT_START_RUN:
                            CrowleyTalkToPlayer(CROWLEY_SAY_START);
                            me->GetMotionMaster()->MoveSplinePath(1);
                            events.ScheduleEvent(EVENT_JUMP_2, me->GetSplineDuration());
                            events.ScheduleEvent(EVENT_CROWLEY_RANDOM_TEXT, urand(15000, 20000));
                            break;
                        case EVENT_JUMP_2:
                            me->GetMotionMaster()->MoveJump(JumpPoints[2], 15.f, 15.f);
                            events.ScheduleEvent(EVENT_RESUME_RUN, me->GetSplineDuration() + 500);
                            break;
                        case EVENT_RESUME_RUN:
                            me->GetMotionMaster()->MoveSplinePath(2);
                            events.ScheduleEvent(EVENT_FINISH, me->GetSplineDuration());
                            break;
                        case EVENT_CROWLEY_RANDOM_TEXT:
                            CrowleyTalkToPlayer(CROWLEY_SAY_RANDOM);
                            events.ScheduleEvent(EVENT_CROWLEY_RANDOM_TEXT, urand(10000, 20000));
                            break;
                        case EVENT_FINISH:
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                            me->DespawnOrUnsummon(1000);
                            break;
                    }
                }
            }
        };
};

class npc_crowley_horse_second_round final : public CreatureScript
{
    public:
        npc_crowley_horse_second_round() : CreatureScript("npc_crowley_horse_second_round") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_RUN             = 1,
                EVENT_FINISH                = 2,

                SPELL_EJECT_ALL_PASSENGERS  = 50630,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetReactState(REACT_PASSIVE);
                me->SetControlled(true, UNIT_STATE_ROOT);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                events.ScheduleEvent(EVENT_START_RUN, 1000);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RUN:
                            me->GetMotionMaster()->MoveSplinePath(1);
                            events.ScheduleEvent(EVENT_FINISH, me->GetSplineDuration());
                            break;
                        case EVENT_FINISH:
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                            me->DespawnOrUnsummon(1000);
                            break;
                    }
                }
            }
        };
};

class npc_bloodfang_stalker final : public CreatureScript
{
    public:
        npc_bloodfang_stalker() : CreatureScript("npc_bloodfang_stalker") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_ENTER_EVADE           = 1,
                EVENT_CHECK_CHASE_TARGET    = 2,

                SPELL_THROW_TORCH           = 67063,
                SPELL_ENRAGE                = 8599,

                NPC_QUEST_KILL_CREDIT       = 35582,
            };

            EventMap events;
            bool enrage;
            bool inFire;

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (!enrage && me->HealthBelowPctDamaged(30, damage))
                {
                    enrage = true;
                    me->CastSpell(me, SPELL_ENRAGE, false);
                }
            }

            void InitializeAI() final
            {
                Reset();
                me->m_ReactDistance = 10.0f;
            }

            void Reset() final
            {
                enrage = false;
                inFire = false;
                events.Reset();
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (!inFire && spell->Id == SPELL_THROW_TORCH)
                {
                    inFire = true;
                    events.ScheduleEvent(EVENT_ENTER_EVADE, 20000);
                    events.ScheduleEvent(EVENT_CHECK_CHASE_TARGET, 500);

                    if (Player* player = caster->ToPlayer())
                    {
                        player->KilledMonsterCredit(NPC_QUEST_KILL_CREDIT, 0);

                        if (Unit* target = player->GetVehicleBase())
                            AttackStart(target);
                    }
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_ENTER_EVADE)
                {
                    inFire = false;
                    EnterEvadeMode();
                    return;
                }

                if (inFire)
                    return;

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_rebel_cannon_phase_4 final : public CreatureScript
{
    public:
        npc_rebel_cannon_phase_4() : CreatureScript("npc_rebel_cannon_phase_4") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            void InitializeAI() final
            {
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->AddExtraUnitMovementFlag(MOVEMENTFLAG2_FULL_SPEED_PITCHING);
                me->AddExtraUnitMovementFlag(MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING);
            }
        };
};

// Quest Last Stand 14222 && Last Chance at Humanity 14375
class npc_lord_darius_crowley_phase_5 final : public CreatureScript
{
    public:
        npc_lord_darius_crowley_phase_5() : CreatureScript("npc_lord_darius_crowley_phase_5") { }

    private:
        enum
        {
            SPELL_PLAY_MOVIE            = 93477,
            SPELL_ALTERED_FORM_RACIAL   = 97709,
            SPELL_FORCE_WORGEN_FORM     = 98274,
            SPELL_CURSE_OF_THE_WORGEN   = 68630,
            SPELL_LAST_STAND_COMPLETE   = 72799,
        };

        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_LAST_STAND)
            {
                player->CastSpell(player, SPELL_PLAY_MOVIE, true);
                player->CastSpell(player, SPELL_ALTERED_FORM_RACIAL, true);
                player->CastSpell(player, SPELL_FORCE_WORGEN_FORM, true);
                player->CastSpell(player, SPELL_CURSE_OF_THE_WORGEN, true);
                player->CastSpell(player, SPELL_LAST_STAND_COMPLETE, true);
                player->SaveToDB();
            }
            else if (quest->GetQuestId() == QUEST_NEVER_SURRENDER)
            {
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_HIDEOUS_BITE_WOUND, true);
            }

            return false;
        }
};

class npc_king_genn_greymane_last_stand final : public CreatureScript
{
    public:
        npc_king_genn_greymane_last_stand() : CreatureScript("npc_king_genn_greymane_last_stand") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_CURSE_OF_THE_WORGEN               = 68630,
                SPELL_ALTERED_FORM_RACIAL               = 97709,
                SPELL_FORCECAST_WORGEN_INTRO_COMPLETION = 68639,
                SPELL_LEARN_FORM                        = 1645,
            };

            if (quest->GetQuestId() == QUEST_LAST_CHANCE_AT_HUMANITY)
            {
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->RemoveAura(SPELL_CURSE_OF_THE_WORGEN);
                player->RemoveAura(SPELL_ALTERED_FORM_RACIAL);
                creature->CastSpell(player, SPELL_FORCECAST_WORGEN_INTRO_COMPLETION, false);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_06, true);
                player->SaveToDB();
            }

            return false;
        }
};

class spell_worgen_intro_completion final : public SpellScriptLoader
{
    struct SeerCheck final : public std::unary_function<WorldObject const *, bool>
    {
        explicit SeerCheck(uint64 guid)
            : casterGUID(guid)
        { }

        bool operator()(WorldObject const *object) const
        {
            if (Creature const* creature = object->ToCreature())
                return creature->GetSeerGUID() != casterGUID;

            return true;
        }

    private:
        uint64 casterGUID;
    };

    public:
        spell_worgen_intro_completion() : SpellScriptLoader("spell_worgen_intro_completion") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (Unit* caster = GetCaster())
                    targets.remove_if(SeerCheck(caster->GetGUID()));
            }

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Creature* target = GetHitCreature())
                    target->DespawnOrUnsummon();
            }

            void Register() final
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_script_impl::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class spell_curse_of_the_worgen_invis final : public SpellScriptLoader
{
    public:
        spell_curse_of_the_worgen_invis() : SpellScriptLoader("spell_curse_of_the_worgen_invis") { }

    private:
        class SummonAranasEvent final : public BasicEvent
        {
            public:
                SummonAranasEvent(Unit* unit)
                    : _unit(unit)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    enum
                    {
                        SPELL_SUMMON_ARANAS = 69123,
                    };

                    _unit->CastSpell((Unit*)NULL, SPELL_SUMMON_ARANAS, false);
                    return true;
                }

                Unit* _unit;
        };

        class aura_script_impl final : public AuraScript
        {
            PrepareAuraScript(aura_script_impl);

            void ExtraEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                    target->m_Events.AddEvent(new SummonAranasEvent(target), target->m_Events.CalculateTime(500));
            }

            void Register() final
            {
                AfterEffectApply += AuraEffectApplyFn(aura_script_impl::ExtraEffect, EFFECT_1, SPELL_AURA_LINKED, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const final
        {
            return new aura_script_impl();
        }
};

class npc_krennan_aranas_last_stand final : public CreatureScript
{
    public:
        npc_krennan_aranas_last_stand() : CreatureScript("npc_krennan_aranas_last_stand") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , godfreyGUID(0)
                , greymaneGUID(0)
            { }

            enum
            {
                EVENT_CHECK_PLAYER_ONLINE           = 1,
                EVENT_CHECK_PLAYER_MOVIE            = 2,
                EVENT_ARANAS_TALK_YOU_CAN_CONTROL   = 3,
                EVENT_SUMMON_GODFREY                = 4,
                EVENT_GODFREY_START_MOVING          = 5,
                EVENT_GODFREY_TALK_PUT_DOWN         = 6,
                EVENT_SUMMON_GREYMANE               = 7,
                EVENT_GREYMANE_START_MOVING         = 8,
                EVENT_GREYMANE_TALK_DIDNT_THINK_SO  = 9,
                EVENT_GREYMANE_ADD_QUESTGIVER_FLAG  = 10,
                EVENT_GREYMANE_FACING_ARANAS        = 11,

                MUSIC_ID                            = 23508,

                NPC_LORD_GODFREY                    = 36330,
                NPC_KING_GENN_GREYMANE              = 36332,

                ARANAS_SAY_YOU_CAN_CONTROL          = 1,
                GODFREY_SAY_PUT_DOWN                = 1,
                GREYMANE_SAY_TELL_ME_GODFREY        = 1,
                GREYMANE_SAY_DIDNT_THINK_SO         = 2,

                SPELL_FORCECAST_SUMMON_GODFREY      = 68635,
                SPELL_FORCECAST_SUMMON_GREYMANE     = 68636,
            };

            EventMap events;
            uint64 godfreyGUID;
            uint64 greymaneGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_SEER_CREATURE, summoner->GetGUID());
                events.ScheduleEvent(EVENT_CHECK_PLAYER_ONLINE, 500);
                events.ScheduleEvent(EVENT_CHECK_PLAYER_MOVIE, 500);
            }

            void JustSummoned(Creature* summoned) final
            {
                switch (summoned->GetEntry())
                {
                    case NPC_LORD_GODFREY:
                        godfreyGUID = summoned->GetGUID();
                        break;
                    case NPC_KING_GENN_GREYMANE:
                        summoned->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        greymaneGUID = summoned->GetGUID();
                        break;
                }

                summoned->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_SEER_CREATURE, me->ToTempSummon()->GetSummonerGUID());
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_PLAYER_ONLINE:
                            {
                                if (!me->ToTempSummon()->GetSummoner())
                                {
                                    if (Creature* godfrey = ObjectAccessor::GetCreature(*me, godfreyGUID))
                                        godfrey->DespawnOrUnsummon();

                                    if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                        greymane->DespawnOrUnsummon();

                                    me->DespawnOrUnsummon();
                                }
                                else
                                    events.ScheduleEvent(EVENT_CHECK_PLAYER_ONLINE, 500);
                            }
                            break;
                        case EVENT_CHECK_PLAYER_MOVIE:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    if (Player* player = summoner->ToPlayer())
                                    {
                                        if (!player->GetCurrentMovieId())
                                        {
                                            me->PlayMusic(MUSIC_ID, player);
                                            events.ScheduleEvent(EVENT_ARANAS_TALK_YOU_CAN_CONTROL, 5000);
                                            return;
                                        }
                                    }
                                }

                                events.ScheduleEvent(EVENT_CHECK_PLAYER_MOVIE, 500);
                            }
                            break;
                        case EVENT_ARANAS_TALK_YOU_CAN_CONTROL:
                            Talk(ARANAS_SAY_YOU_CAN_CONTROL, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_SUMMON_GODFREY, 5000);
                            break;
                        case EVENT_SUMMON_GODFREY:
                            me->CastSpell((Unit*)NULL, SPELL_FORCECAST_SUMMON_GODFREY, false);
                            events.ScheduleEvent(EVENT_GODFREY_START_MOVING, 1000);
                            events.ScheduleEvent(EVENT_SUMMON_GREYMANE, 8000);
                            events.ScheduleEvent(EVENT_GODFREY_TALK_PUT_DOWN, 10000);
                            break;
                        case EVENT_GODFREY_START_MOVING:
                            {
                                if (Creature* godfrey = ObjectAccessor::GetCreature(*me, godfreyGUID))
                                    godfrey->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                            }
                            break;
                        case EVENT_SUMMON_GREYMANE:
                            me->CastSpell((Unit*)NULL, SPELL_FORCECAST_SUMMON_GREYMANE, false);
                            events.ScheduleEvent(EVENT_GREYMANE_START_MOVING, 9000);
                            break;
                        case EVENT_GODFREY_TALK_PUT_DOWN:
                            {
                                if (Creature* godfrey = ObjectAccessor::GetCreature(*me, godfreyGUID))
                                {
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                        godfrey->SetFacingToObject(summoner);

                                    if (godfrey->IsAIEnabled)
                                        godfrey->AI()->Talk(GODFREY_SAY_PUT_DOWN, me->ToTempSummon()->GetSummonerGUID(), true);
                                }
                            }
                            break;
                        case EVENT_GREYMANE_START_MOVING:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                {
                                    Movement::MoveSplineInit init(greymane);
                                    init.MoveTo(-1821.09f, 2292.597f, 42.23363f);
                                    init.SetFacing(1.32645f);
                                    init.SetWalk(true);
                                    init.Launch();

                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GREYMANE_SAY_TELL_ME_GODFREY, me->ToTempSummon()->GetSummonerGUID(), true);
                                }

                                events.ScheduleEvent(EVENT_GREYMANE_TALK_DIDNT_THINK_SO, 10000);
                            }
                            break;
                        case EVENT_GREYMANE_TALK_DIDNT_THINK_SO:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GREYMANE_SAY_DIDNT_THINK_SO, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_GREYMANE_FACING_ARANAS, 2000);
                                events.ScheduleEvent(EVENT_GREYMANE_ADD_QUESTGIVER_FLAG, 10000);
                            }
                            break;
                        case EVENT_GREYMANE_FACING_ARANAS:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                    greymane->SetFacingToObject(me);
                            }
                            break;
                        case EVENT_GREYMANE_ADD_QUESTGIVER_FLAG:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                {
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                        greymane->SetFacingToObject(summoner);

                                    greymane->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                                }
                            }
                            break;
                    }
                }
            }
        };
};

// Quest In Need of Ingredients 14320
class go_crate_of_mandrake_essence final : public GameObjectScript
{
    public:
        go_crate_of_mandrake_essence() : GameObjectScript("go_crate_of_mandrake_essence") { }

    private:
        bool OnQuestReward(Player* player, GameObject* /*go*/, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                CINEMATIC_FORSAKEN      = 168,
            };

            if (quest->GetQuestId() == QUEST_IN_NEED_OF_INGR)
                player->SendCinematicStart(CINEMATIC_FORSAKEN);

            return false;
        }
};

// Quest Invasion 14321
class npc_slain_watchman final : public CreatureScript
{
    public:
        npc_slain_watchman() : CreatureScript("npc_slain_watchman") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            enum
            {
                SPELL_FORCECAST_SUMMON_FORSAKEN_ASSASSIN    = 68492,
            };

            if (quest->GetQuestId() == QUEST_INVASION)
                creature->CastSpell(player, SPELL_FORCECAST_SUMMON_FORSAKEN_ASSASSIN, false, NULL, NULL, player->GetGUID());

            return false;
        }
};

class npc_gwen_armstead_phase_6 final : public CreatureScript
{
    public:
        npc_gwen_armstead_phase_6() : CreatureScript("npc_gwen_armstead_phase_6") { }

    private:
        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_INVASION)
            {
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_07, false);
                player->SaveToDB();
            }

            return false;
        }
};

class npc_forsaken_assassin final : public CreatureScript
{
    public:
        npc_forsaken_assassin() : CreatureScript("npc_forsaken_assassin") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                FORSAKEN_ASSASSIN_SAY   = 1,
                SPELL_BACKSTAB          = 75360,
            };

            void IsSummonedBy(Unit* summoner) final
            {
                Talk(FORSAKEN_ASSASSIN_SAY, summoner->GetGUID(), true);
                AttackStart(summoner);
                me->CastSpell(summoner, SPELL_BACKSTAB, false);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

// Quest You Can't Take 'Em Alone 14348
const float LiamPosition[2] = {-1920.43f, 2308.94f};

class npc_horrid_abomination final : public CreatureScript
{
    public:
        npc_horrid_abomination() : CreatureScript("npc_horrid_abomination") { }

    private:
        class CreatureEntryCheck final
        {
            public:
                CreatureEntryCheck(uint32 entry) : _entry(entry) { }

                bool operator() (Unit const *unit) const
                {
                    return unit->GetEntry() == _entry;
                }

            private:
                uint32 _entry;
        };

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new npc_horrid_abominationAI (creature);
        }

        struct npc_horrid_abominationAI final : public ScriptedAI
        {
            npc_horrid_abominationAI(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_RESTITCHING                   = 1,

                ABOMINATION_TEXT_ID                 = 1,

                NPC_HORRID_ABOMINATION_KILL_CREDIT  = 36233,
                NPC_PRINCE_LIAM_GREYMANE            = 36140,

                SPELL_KEG_PLACED                    = 68555,
                SPELL_SHOOT                         = 68559,
                SPELL_RESTITCHING                   = 68864,
                SPELL_EXPLOSION                     = 68560,
            };

            EventMap events;
            uint64 playerGUID;

            void InitializeAI() final
            {
                me->m_ReactDistance = 10.0f;
                Reset();
            }

            void Reset() final
            {
                events.Reset();
                playerGUID = 0;
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                switch (spell->Id)
                {
                    case SPELL_KEG_PLACED:
                        {
                            playerGUID = caster->GetGUID();
                            Talk(ABOMINATION_TEXT_ID);

                            CellCoord pair(Trinity::ComputeCellCoord(LiamPosition[0], LiamPosition[1]));
                            Cell cell(pair);
                            cell.SetNoCreate();

                            Creature* creature = NULL;
                            CreatureEntryCheck checker(NPC_PRINCE_LIAM_GREYMANE);
                            Trinity::CreatureSearcher<CreatureEntryCheck> searcher(me, creature, checker);

                            cell.Visit(pair, Trinity::makeGridVisitor(searcher), *me->GetMap(), 5.f, LiamPosition[0], LiamPosition[1]);

                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();

                            if (creature)
                                creature->CastSpell(me, SPELL_SHOOT, false);
                            else
                                ShootEvent();
                        }
                        break;
                    case SPELL_SHOOT:
                        ShootEvent();
                        break;
                }
            }

            void ShootEvent()
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                    player->KilledMonsterCredit(NPC_HORRID_ABOMINATION_KILL_CREDIT, 0);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveAura(SPELL_KEG_PLACED);
                me->CastSpell(me, SPELL_EXPLOSION, false);
                me->DespawnOrUnsummon(2000);
            }

            void EnterCombat(Unit* /*who*/) final
            {
                events.ScheduleEvent(EVENT_RESTITCHING, 3000);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RESTITCHING)
                {
                    me->CastSpell(me, 68864, false);
                    events.ScheduleEvent(EVENT_RESTITCHING, 8000);
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_gilneas_horrid_abomination_explosion final : public SpellScriptLoader
{
    public:
        spell_gilneas_horrid_abomination_explosion() : SpellScriptLoader("spell_gilneas_horrid_abomination_explosion") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                enum
                {
                    SPELL_EXPLOSION_POISON          = 42266,
                    SPELL_EXPLOSION_BONE_TYPE_ONE   = 42267,
                    SPELL_EXPLOSION_BONE_TYPE_TWO   = 42274,
                };

                if (Unit* caster = GetCaster())
                {
                    for (int i = 0; i < 11; ++i)
                        caster->CastSpell(caster, SPELL_EXPLOSION_POISON, false);

                    for (int i = 0; i < 6; ++i)
                        caster->CastSpell(caster, SPELL_EXPLOSION_BONE_TYPE_ONE, false);

                    for (int i = 0; i < 4; ++i)
                        caster->CastSpell(caster, SPELL_EXPLOSION_BONE_TYPE_TWO, false);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

const Position InvaderSP[19]=
{
    {-1955.254f, 2317.037f, 34.241f, 5.801f},
    {-1949.527f, 2318.189f, 34.604f, 5.765f},
    {-1951.457f, 2323.875f, 34.064f, 5.730f},
    {-1946.009f, 2326.200f, 34.465f, 5.453f},
    {-1942.219f, 2322.254f, 34.900f, 5.549f},
    {-1939.469f, 2327.883f, 34.838f, 5.540f},
    {-1946.644f, 2333.507f, 33.945f, 5.899f},
    {-1948.542f, 2343.059f, 33.336f, 5.336f},
    {-1955.275f, 2341.054f, 33.402f, 5.992f},
    {-1945.168f, 2349.152f, 32.780f, 5.404f},
    {-1943.464f, 2356.645f, 31.673f, 5.627f},
    {-1939.296f, 2359.115f, 31.611f, 5.404f},
    {-1931.343f, 2360.742f, 31.775f, 5.361f},
    {-1925.613f, 2358.293f, 32.118f, 4.744f},
    {-1930.045f, 2351.567f, 33.169f, 4.799f},
    {-1934.659f, 2349.729f, 32.768f, 4.847f},
    {-1937.355f, 2342.858f, 33.417f, 5.114f},
    {-1941.122f, 2338.149f, 33.751f, 5.341f},
    {-1953.898f, 2349.607f, 31.305f, 5.483f},
};

class npc_prince_liam_greymane_phase_7 final : public CreatureScript
{
    public:
        npc_prince_liam_greymane_phase_7() : CreatureScript("npc_prince_liam_greymane_phase_7") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT)
            { }

            enum
            {
                SPELL_SHOOT             = 6660,

                NPC_FORSAKEN_INVADER    = 34511,
            };

            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
                me->setActive(true);

                for (int i = 0; i < 10; ++i)
                    SummonInvader();
            }

            void Reset() final
            {
                shooterAI.Reset();
            }

            void SummonInvader()
            {
                uint8 invaderId = urand(0, 18);

                if (Creature* invader = me->SummonCreature(NPC_FORSAKEN_INVADER, InvaderSP[invaderId], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                {
                    float angle = me->GetAngle(invader);
                    float x, y;
                    me->GetNearPoint2D(x, y, frand(10.f, 15.f), angle);
                    invader->GetMotionMaster()->MovePointSmooth(x, y);
                    invader->m_Events.AddEvent(new AggroEvent(invader), invader->m_Events.CalculateTime(invader->GetSplineDuration()));
                }
            }

            void SummonedCreatureDies(Creature* summoned, Unit* /*killer*/) final
            {
                SummonInvader();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
            }

            void UpdateAI(uint32 const diff) final
            {
                shooterAI.UpdateShooterAI(diff);
            }
        };
};

// Quest Save the Children! 14368
enum
{
    SPELL_SAVE_CYNTHIA  = 68597,
    SPELL_SAVE_ASHLEY   = 68598,
    SPELL_SAVE_JAMES    = 68596,

    PLAYER_SAY_CYNTHIA  = 0,
    PLAYER_SAY_ASHLEY   = 1,
    PLAYER_SAY_JAMES    = 2,
};

const std::string PlayerSay[3]=
{
    "It's not safe here.  Go to the Allens' basement.",
    "Join the others inside the basement next door.  Hurry!",
    "Your mother's in the basement next door.  Get to her now!",
};

class npc_gilneas_children_phase_7 final : public CreatureScript
{
    public:
        npc_gilneas_children_phase_7(const char* scriptName, uint32 spellId, uint8 playerSayId)
            : CreatureScript(scriptName)
            , _spellId(spellId)
            , _playerSayId(playerSayId)
        { }

    private:
        uint32 _spellId;
        uint8 _playerSayId;

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature, _spellId, _playerSayId);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature, uint32 spellId, uint8 playerSayId)
                : ScriptedAI(creature)
                , _spellId(spellId)
                , _playerSayId(playerSayId)
            { }

            enum
            {
                EVENT_TALK_TO_PLAYER    = 1,
                EVENT_START_RUN         = 2,
                EVENT_OPEN_DOOR         = 3,
                EVENT_RESUME_RUN        = 4,

                CHILDREN_TEXT_ID        = 1,

                GO_DOOR_TO_THE_BASEMENT = 196404,
            };

            EventMap events;
            uint64 playerGUID;
            uint32 _spellId;
            uint8 _playerSayId;
            bool activated;

            void Reset() final
            {
                events.Reset();
                playerGUID = 0;
                activated = false;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (!activated && spell->Id == _spellId)
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        activated = true;
                        playerGUID = player->GetGUID();
                        player->Say(PlayerSay[_playerSayId], LANG_UNIVERSAL);
                        player->KilledMonsterCredit(me->GetEntry(), 0);
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                        events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 3500);
                    }
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK_TO_PLAYER:
                            {
                                if (Player* player = ObjectAccessor::GetPlayer(*me, playerGUID))
                                    Talk(CHILDREN_TEXT_ID, playerGUID, true);

                                events.ScheduleEvent(EVENT_START_RUN, 5000);
                            }
                            break;
                        case EVENT_START_RUN:
                            me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_OPEN_DOOR, me->GetSplineDuration());
                            break;
                        case EVENT_OPEN_DOOR:
                            {
                                if (GameObject* door = me->FindNearestGameObject(GO_DOOR_TO_THE_BASEMENT, 10.0f))
                                {
                                    if (door->GetGoState() == GO_STATE_READY)
                                    {
                                        door->UseDoorOrButton();
                                        events.ScheduleEvent(EVENT_RESUME_RUN, 2000);
                                    }
                                    else
                                        events.ScheduleEvent(EVENT_RESUME_RUN, 0);
                                }
                            }
                            break;
                        case EVENT_RESUME_RUN:
                            me->GetMotionMaster()->MoveSplinePath(2, false, false, 0.f, false, false);
                            me->DespawnOrUnsummon(me->GetSplineDuration());
                            break;
                    }
                }
            }
        };
};

class npc_forsaken_invader final : public CreatureScript
{
    public:
        npc_forsaken_invader() : CreatureScript("npc_forsaken_invader") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void Reset() final
            {
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
                else
                {
                    if (Unit* victim = me->GetVictim())
                    {
                        if (victim->GetTypeId() == TYPEID_UNIT)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->getThreatManager().addThreat(attacker, std::numeric_limits<float>::max());
                            AttackStart(attacker);
                        }
                    }
                }
            }
        };
};

// Quest Two By Sea 14382
class npc_forsaken_catapult_phase_7 final : public CreatureScript
{
    public:
        npc_forsaken_catapult_phase_7() : CreatureScript("npc_forsaken_catapult_phase_7") { }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            void SetJumpPlayer(Position* pos, float speedXY, float speedZ)
            {
                _pos.Relocate(pos);
                _speedXY = speedXY;
                _speedZ = speedZ;
                events.ScheduleEvent(EVENT_JUMP, 1500);
            }

        private:
            enum
            {
                EVENT_RESPAWN   = 1,
                EVENT_JUMP      = 2,
                EVENT_BOULDER   = 3,

                SPELL_LAUNCH    = 66251,
                SPELL_BOULDER   = 68591,

                ACTION_DRIVER   = 1,
            };

            EventMap events;
            float _speedXY, _speedZ;
            Position _pos;

            void InitializeAI() final
            {
                Reset();
                me->setActive(true);
            }

            void Reset() final
            {
                events.Reset();
                events.ScheduleEvent(EVENT_BOULDER, urand(5000, 20000));
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_DRIVER), me->m_Events.CalculateTime(500));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_DRIVER)
                {
                    Position pos;
                    me->GetPosition(&pos);

                    if (Creature* driver = me->SummonCreature(36292, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                    {
                        driver->setActive(true);
                        driver->EnterVehicle(me, 2);
                    }
                }
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply) final
            {
                if (!apply)
                {
                    events.Reset();
                    events.ScheduleEvent(EVENT_RESPAWN, who->GetTypeId() == TYPEID_UNIT ? 30000 : 10000);
                }
                else
                    events.CancelEvent(EVENT_RESPAWN);
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                if (seatId == 1)
                {
                    passenger->m_movementInfo.t_pos.m_positionZ += 15.f;
                    enterPos.m_positionZ += 15.f;
                }
            }

            void SummonedCreatureDies(Creature * summon, Unit * /*killer*/) final
            {
                me->setFaction(35);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_RESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                        case EVENT_JUMP:
                            {
                                if (Vehicle* vehicle = me->GetVehicleKit())
                                {
                                    if (Unit* passenger = vehicle->GetPassenger(1))
                                    {
                                        if (Player* player = passenger->ToPlayer())
                                        {
                                            me->CastSpell(player, SPELL_LAUNCH, false);
                                            player->ExitVehicle();
                                            player->GetMotionMaster()->MoveJump(_pos, _speedXY, _speedZ);
                                        }
                                    }
                                }
                            }
                            break;
                        case EVENT_BOULDER:
                            {
                                float x, y, z;
                                me->GetNearPoint2D(x, y, urand(100, 150), me->GetOrientation());
                                z = me->GetMap()->GetHeight(me->GetPhaseMask(), x, y, MAX_HEIGHT);
                                me->CastSpell(x, y, z, SPELL_BOULDER, false);
                                events.ScheduleEvent(EVENT_BOULDER, urand(5000, 20000));
                            }
                            break;
                    }
                }
            }
        };
};

const float CheckSpellPos[16][3]=
{
    {-2119.36f, 2663.58f, 8.25703f},
    {-2132.94f, 2665.22f, 8.25549f},
    {-2135.20f, 2658.72f, 19.1616f},
    {-2113.73f, 2677.08f, 14.1064f},
    {-2124.71f, 2677.31f, 13.6799f},
    {-2128.56f, 2665.52f, 15.2329f},
    {-2115.82f, 2668.72f, 13.6927f},
    {-2106.92f, 2686.66f, 18.2360f},
    {-2098.44f, 2694.41f, 20.4828f},
    {-2197.74f, 2594.95f, 20.9434f},
    {-2206.71f, 2587.34f, 18.6410f},
    {-2229.45f, 2568.61f, 15.6442f},
    {-2236.70f, 2560.28f, 19.7311f},
    {-2215.77f, 2568.64f, 14.0592f},
    {-2224.96f, 2579.85f, 14.0884f},
    {-2216.07f, 2578.79f, 14.5102f},
};

typedef npc_forsaken_catapult_phase_7::creature_script_impl CatapultAI;

class spell_gilneas_forsaken_catapult_launch final : public SpellScriptLoader
{
    public:
        spell_gilneas_forsaken_catapult_launch() : SpellScriptLoader("spell_gilneas_forsaken_catapult_launch") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            SpellCastResult CheckCast()
            {
                float x, y, z;
                GetExplTargetDest()->GetPosition(x, y, z);

                for (int i = 0; i < 16; ++i)
                    if (sqrt(pow(x - CheckSpellPos[i][0], 2) + pow(y - CheckSpellPos[i][1], 2) + pow(z - CheckSpellPos[i][2], 2)) < 10.0f)
                        return SPELL_CAST_OK;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Function(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Vehicle* vehicle = caster->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(0))
                        {
                            if (passenger->GetTypeId() == TYPEID_PLAYER)
                            {
                                passenger->ChangeSeat(1);
                                Position pos;
                                float speedXY, speedZ;
                                GetTargetSpeedXYZ(speedXY, speedZ);
                                GetExplTargetDest()->GetPosition(&pos);

                                if (CatapultAI* catapult = dynamic_cast<CatapultAI*>(caster->GetAI()))
                                    catapult->SetJumpPlayer(&pos, speedXY, speedZ);
                            }
                        }
                    }
                }
            }

            void Register() final
            {
                OnCheckCast += SpellCheckCastFn(spell_script_impl::CheckCast);
                OnEffectHit += SpellEffectFn(spell_script_impl::Function, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_gilneas_forsaken_captain final : public CreatureScript
{
    public:
        npc_gilneas_forsaken_captain() : CreatureScript("npc_gilneas_forsaken_captain") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 45.f)
            { }

            enum
            {
                EVENT_RUSTY_RAPIER  = 1,

                SPELL_SHOOT         = 38372,
                SPELL_RUSTY_RAPIER  = 75363,
            };

            EventMap events;
            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 45.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
                events.ScheduleEvent(EVENT_RUSTY_RAPIER, urand(5000, 10000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_RUSTY_RAPIER)
                {
                    me->CastSpell(me->GetVictim(), SPELL_RUSTY_RAPIER, false);
                    events.ScheduleEvent(EVENT_RUSTY_RAPIER, urand(15000, 30000));
                }
            }
        };
};

// Quest Leader of the Pack 14386
class npc_dark_ranger_thyala final : public CreatureScript
{
    public:
        npc_dark_ranger_thyala() : CreatureScript("npc_dark_ranger_thyala") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT)
                , summons(creature)
            { }

            enum
            {
                EVENT_KNOCKBACK     = 1,

                SPELL_SHOOT         = 16100,
                SPELL_KNOCKBACK     = 68683,

                NPC_ATTACK_MASTIFF  = 36409,
            };

            EventMap events;
            SummonList summons;
            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 45.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();

                events.ScheduleEvent(EVENT_KNOCKBACK, urand(2500, 5000));
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (me->GetHealth() < damage)
                {
                    ThreatContainer::StorageType const& threatlist = me->getThreatManager().getThreatList();

                    for (ThreatContainer::StorageType::const_iterator i = threatlist.begin(); i != threatlist.end(); ++i)
                        if (Player* player = ObjectAccessor::GetPlayer((*me), (*i)->getUnitGuid()))
                            player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                }
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
            }

            void JustSummoned(Creature* summoned) final
            {
                summons.Summon(summoned);
            }

            void JustDied(Unit* /*who*/) final
            {
                summons.DespawnAll();
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_KNOCKBACK)
                {
                    me->CastSpell((Unit*)NULL, SPELL_KNOCKBACK, false);
                    events.ScheduleEvent(EVENT_KNOCKBACK, urand(7500, 15000));
                }
            }
        };
};

class npc_attack_mastiff final : public CreatureScript
{
    public:
        npc_attack_mastiff() : CreatureScript("npc_attack_mastiff") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_DEMORALIZING_ROAR = 1,
                EVENT_LEAP              = 2,
                EVENT_TAUNT             = 3,

                SPELL_DEMORALIZING_ROAR = 15971,
                SPELL_LEAP              = 68687,
                SPELL_TAUNT             = 26281,
            };

            EventMap events;

            void Reset() final
            {
                events.Reset();
            }

            void EnterCombat(Unit* who) final
            {
                events.ScheduleEvent(EVENT_DEMORALIZING_ROAR, urand(2500, 5000));
                events.ScheduleEvent(SPELL_TAUNT, urand(2500, 5000));
                events.ScheduleEvent(SPELL_LEAP, urand(5000, 10000));
            }

            void JustDied(Unit* /*killer*/) final
            {
                events.Reset();
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DEMORALIZING_ROAR:
                            me->CastSpell((Unit*)NULL, SPELL_DEMORALIZING_ROAR, false);
                            events.ScheduleEvent(EVENT_DEMORALIZING_ROAR, urand(5000, 15000));
                            break;
                        case SPELL_TAUNT:
                            me->CastSpell(me->GetVictim(), SPELL_TAUNT, false);
                            events.ScheduleEvent(SPELL_TAUNT, urand(5000, 10000));
                            break;
                        case SPELL_LEAP:
                            me->CastSpell(me->GetVictim(), SPELL_LEAP, false);
                            events.ScheduleEvent(SPELL_LEAP, urand(5000, 10000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_call_attack_mastiffs final : public SpellScriptLoader
{
    public:
        spell_call_attack_mastiffs() : SpellScriptLoader("spell_call_attack_mastiffs") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void SummonMastiffs(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                enum
                {
                    NPC_ATTACK_MASTIFF  = 36409,
                };

                Unit* caster = GetCaster();
                Creature* target = GetHitCreature();

                if (!(caster && target && target->IsAlive()))
                    return;

                float angle = target->GetHomePosition().GetOrientation();

                for (int i = 0; i < 12; ++i)
                {
                    float x, y;
                    float dist = urand(20.f, 40.f);
                    float angleOffset = frand(-M_PI / 4, M_PI / 4);
                    target->GetNearPoint2D( x, y, dist, angle + angleOffset);
                    float z = target->GetMap()->GetHeight(target->GetPhaseMask(), x, y, MAX_HEIGHT);
                    float summonAngle = target->GetAngle(x, y);

                    if (Creature* mastiff = target->SummonCreature(NPC_ATTACK_MASTIFF, x, y, z, M_PI + summonAngle, TEMPSUMMON_TIMED_DESPAWN, 60000))
                    {
                        mastiff->Attack(target, true);
                        mastiff->AddThreat(target, std::numeric_limits<float>::max());
                        mastiff->GetMotionMaster()->MoveChase(target);
                    }
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::SummonMastiffs, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_lord_godfrey_phase_7 final : public CreatureScript
{
    public:
        npc_lord_godfrey_phase_7() : CreatureScript("npc_lord_godfrey_phase_7") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_FORCECAST_CATACLYSM_I = 69027
            };

            if (quest->GetQuestId() == QUEST_LEADER_OF_THE_PACK)
            {
                creature->CastSpell(player, SPELL_FORCECAST_CATACLYSM_I, false);
                player->SaveToDB();
            }

            return false;
        }
};

class spell_gilneas_cataclysm_phase_7 final : public SpellScriptLoader
{
    public:
        spell_gilneas_cataclysm_phase_7() : SpellScriptLoader("spell_gilneas_cataclysm_phase_7") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                if (Player* player = GetHitPlayer())
                {
                    player->RemoveAurasByType(SPELL_AURA_PHASE);
                    player->CastSpell(player, SPELL_ZONE_SPECIFIC_08, true);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest Gasping for Breath 14395
class npc_drowning_watchman final : public CreatureScript
{
    public:
        npc_drowning_watchman() : CreatureScript("npc_drowning_watchman") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new npc_drowning_watchmanAI (creature);
        }

        struct npc_drowning_watchmanAI final : public ScriptedAI
        {
            npc_drowning_watchmanAI(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_SUMMON_SPARKLES           = 69253,
                SPELL_DROWNING                  = 68730,
                SPELL_RESCUE_DROWNING_WATCHMAN  = 68735,

                GO_SPARKLES                     = 197333,

                DROWNING_WATCHMAN_SAY           = 1,
            };

            void Reset() final
            {
                me->CastSpell(me, SPELL_DROWNING, false);
                me->CastSpell((Unit*)NULL, SPELL_SUMMON_SPARKLES, false);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (spell->Id == SPELL_RESCUE_DROWNING_WATCHMAN)
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    me->RemoveAura(SPELL_DROWNING);
                    me->EnterVehicle(caster);

                    if (GameObject* go = me->FindNearestGameObject(GO_SPARKLES, 10.0f))
                        go->Delete();
                }
            }

            void OnControlVehicle(Unit* base, int8 /*seatId*/, bool apply) final
            {
                if (!apply)
                {
                    if (me->IsInWater())
                        me->CastSpell(me, SPELL_DROWNING, false);
                    else
                        me->SetStandState(UNIT_STAND_STATE_KNEEL);

                    Talk(DROWNING_WATCHMAN_SAY, base->GetGUID(), true);
                    me->DespawnOrUnsummon(10000);
                }
            }
        };
};

class npc_duskhaven_watchman_rescuer_phase_8 final : public CreatureScript
{
    public:
        npc_duskhaven_watchman_rescuer_phase_8() : CreatureScript("npc_duskhaven_watchman_rescuer_phase_8") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature){ }

            enum
            {
                NPC_DROWNING_WATCHMAN_KREDIT    = 36450,

                SPELL_RESCUE_DROWNING_WATCHMAN  = 68735,
            };

            void MoveInLineOfSight(Unit* who) final
            {
                if (who->GetTypeId() == TYPEID_PLAYER && who->IsVehicle() && !who->IsInWater() && me->GetExactDistSq(who) < 25.0f)
                {
                    who->RemoveAura(SPELL_RESCUE_DROWNING_WATCHMAN);
                    who->ToPlayer()->KilledMonsterCredit(NPC_DROWNING_WATCHMAN_KREDIT, 0);
                }
            }
        };
};

// Quest The Hungry Ettin 14416
class npc_mountain_horse_vehicle final : public CreatureScript
{
    public:
        npc_mountain_horse_vehicle() : CreatureScript("npc_mountain_horse_vehicle") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature)
                : VehicleAI(creature)
                , summons(me)
            { }

            enum
            {
                SPELL_ROPE_IN_HORSE         = 68908,
                SPELL_MOUNTAIN_HORSE_CREDIT = 68917,
            };

            SummonList summons;

            void SpellHit(Unit* /*caster*/, const SpellInfo* spell) final
            {
                if (spell->Id == SPELL_ROPE_IN_HORSE)
                    me->DespawnOrUnsummon();
            }

            void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) final
            {
                if (!apply)
                {
                    static Position homePos = {-2059.701f, 2254.174f, 22.57308f, 1.361357f};

                    if (me->GetExactDist2dSq(&homePos) < 400.f)
                    {
                        me->CastSpell(who, SPELL_MOUNTAIN_HORSE_CREDIT, false);

                        for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
                            if (Creature* horse = sObjectAccessor->GetCreature(*me, *itr))
                                horse->CastSpell(who, SPELL_MOUNTAIN_HORSE_CREDIT, false);
                    }

                    me->DespawnOrUnsummon();
                    summons.DespawnAll();
                }
            }

            void JustSummoned(Creature* summoned) final
            {
                summons.Summon(summoned);
            }
        };
};

class npc_mountain_horse_follower final : public CreatureScript
{
    public:
        npc_mountain_horse_follower() : CreatureScript("npc_mountain_horse_follower") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_ROPE_CHANNEL  = 68940,
            };

            void IsSummonedBy(Unit* summoner) final
            {
                me->CastSpell(summoner, SPELL_ROPE_CHANNEL, false);
                me->GetMotionMaster()->MoveFollow(summoner, frand(2.5, 5.f), frand(-M_PI / 4, M_PI / 4));

                if (Creature* horse = summoner->GetVehicleCreatureBase())
                    if (horse->IsAIEnabled)
                        horse->AI()->JustSummoned(me);
            }
        };
};

class spell_round_up_horse final : public SpellScriptLoader
{
    public:
        spell_round_up_horse() : SpellScriptLoader("spell_round_up_horse") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            SpellCastResult CheckCast()
            {
                enum
                {
                    NPC_MOUNTAIN_HORSE_VEHICLE  = 36540,
                    SPELL_RIDE_VEHICLE          = 94654,
                };

                if (Unit* target = GetExplTargetUnit())
                    if (target->GetEntry() != NPC_MOUNTAIN_HORSE_VEHICLE || target->HasAura(SPELL_RIDE_VEHICLE))
                        return SPELL_FAILED_BAD_TARGETS;

                return SPELL_CAST_OK;
            }

            void Register() final
            {
                OnCheckCast += SpellCheckCastFn(spell_script_impl::CheckCast);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest Grandma's Cat 14401
class npc_wahl final : public CreatureScript
{
    public:
        npc_wahl() : CreatureScript("npc_wahl") { }

    private:
        CreatureAI* GetAI(Creature* creature) const
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_TRANSFORM = 1,
                YELL_DONT_MESS  = 1,
                NPC_WAHL_WORGEN = 36852,
                SPELL_TRANSFORM = 81908,
            };

            EventMap events;

            void IsSummonedBy(Unit* /*summoner*/) final
            {
                Talk(YELL_DONT_MESS);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                events.ScheduleEvent(EVENT_TRANSFORM, me->GetSplineDuration());
            }

            void JustReachedHome() final
            {
                if (me->IsSummon())
                {
                    me->GetMotionMaster()->MoveSplinePath(2, false, false, 0.f, false, false);
                    me->DespawnOrUnsummon(me->GetSplineDuration());
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_TRANSFORM)
                {
                    if (me->IsSummon())
                    {
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        {
                            me->SetHomePosition(*me);
                            me->CastSpell(me, SPELL_TRANSFORM, false);
                            me->SetDisplayId(NPC_WAHL_WORGEN);
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                            AttackStart(summoner);
                        }
                    }
                }

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_lucius_the_cruel final : public CreatureScript
{
    public:
        npc_lucius_the_cruel() : CreatureScript("npc_lucius_the_cruel") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 45.f)
                , wahlGUID(0)
            { }

            enum
            {
                EVENT_CATCH_CHANCE_1    = 1,
                EVENT_CATCH_CHANCE_2    = 2,
                EVENT_SUMMON_WHAL       = 3,

                SAY_THIS_CAT_IS_MINE    = 1,

                SPELL_SHOOT             = 38372,
                NPC_WAHL                = 36458,
                NPC_CHANCE_THE_CAT      = 36459,
            };

            ShooterGuardAI shooterAI;
            EventMap events;
            uint64 wahlGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                SetCombatMovement(false);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                Talk(SAY_THIS_CAT_IS_MINE);
                me->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                events.ScheduleEvent(EVENT_CATCH_CHANCE_1, me->GetSplineDuration() + 500);
            }

            void Reset() final
            {
                shooterAI.Reset();
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
                events.ScheduleEvent(EVENT_SUMMON_WHAL, 2000);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CATCH_CHANCE_1:
                            if (Creature* chance = me->FindNearestCreature(NPC_CHANCE_THE_CAT, 20.f))
                            {
                                me->SetFacingToObject(chance);
                                me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
                                chance->DespawnOrUnsummon(1000);
                            }

                            me->SetHomePosition(*me);
                            events.ScheduleEvent(EVENT_CATCH_CHANCE_2, 2500);
                            break;
                        case EVENT_CATCH_CHANCE_2:
                            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            AttackStart(me->ToTempSummon()->GetSummoner());
                            break;
                        case EVENT_SUMMON_WHAL:
                            if (wahlGUID == 0)
                            {
                                Position const wahlSP = {-2100.673f, 2351.875f, 6.855009f, 3.227739f};
                                if (Creature* wahl = me->SummonCreature(NPC_WAHL, wahlSP))
                                    wahlGUID = wahl->GetGUID();
                            }
                            break;
                    }
                }

                shooterAI.UpdateShooterAI(diff);
            }
        };
};

class npc_chance_the_cat final : public CreatureScript
{
    public:
        npc_chance_the_cat() : CreatureScript("npc_chance_the_cat") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                NPC_LUCIUS_THE_CRUEL    = 36461,
                SPELL_CATCH_CAT         = 68743,
            };

            bool isEvent;

            void Reset() final
            {
                isEvent = false;
            }

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (!isEvent && spell->Id == SPELL_CATCH_CAT)
                {
                    isEvent = true;
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

                    static Position luciusSP = {-2112.473f, 2329.608f, 7.390349f, 0.1513071f};
                    caster->SummonCreature(NPC_LUCIUS_THE_CRUEL, luciusSP, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                }
            }
        };
};

static const Position HaywardInvaderSP[17]=
{
    {-2301.968f, 2256.245f, 0.749f, 1.743f},
    {-2306.780f, 2253.055f, 0.489f, 1.591f},
    {-2311.719f, 2255.334f, 0.563f, 1.236f},
    {-2320.660f, 2258.933f, 0.327f, 0.981f},
    {-2327.204f, 2259.341f, 0.533f, 0.675f},
    {-2330.231f, 2260.883f, 0.484f, 0.667f},
    {-2341.077f, 2261.813f, 0.329f, 0.670f},
    {-2344.812f, 2268.983f, 0.477f, 0.757f},
    {-2352.468f, 2280.472f, 0.326f, 0.152f},
    {-2356.115f, 2288.644f, 1.020f, 5.992f},
    {-2354.731f, 2293.812f, 0.754f, 5.849f},
    {-2348.310f, 2300.429f, 0.350f, 5.544f},
    {-2345.154f, 2305.551f, 0.382f, 5.552f},
    {-2337.912f, 2310.830f, 0.487f, 5.473f},
    {-2336.987f, 2319.975f, 1.412f, 5.230f},
    {-2325.889f, 2309.358f, 0.354f, 5.261f},
    {-2317.483f, 2316.027f, 0.329f, 4.943f},
};

class npc_hayward_brother final : public CreatureScript
{
    public:
        npc_hayward_brother() : CreatureScript("npc_hayward_brother") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                NPC_FORSAKEN_INVADER = 36488,
            };

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->m_ReactDistance = 10.0f;
                me->setActive(true);

                for (int i = 0; i < 2; ++i)
                    SummonInvader();
            }

            void SummonInvader()
            {
                uint8 invaderId = urand(0, 16);

                if (Creature* invader = me->SummonCreature(NPC_FORSAKEN_INVADER, HaywardInvaderSP[invaderId], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                {
                    float x, y;
                    invader->Attack(me, true);
                    invader->AddThreat(me, std::numeric_limits<float>::max());
                    me->GetNearPoint2D(x, y, 2.f, me->GetAngle(invader));
                    Movement::MoveSplineInit init(invader);
                    init.SetVelocity(10.f);
                    invader->GetMotionMaster()->MovePointSmooth(x, y, 5.f, true, &init);
                }
            }

            void SummonedCreatureDies(Creature* summoned, Unit* /*killer*/) final
            {
                SummonInvader();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

// Quest To Greymane Manor 14465
class npc_swift_mountain_horse final : public CreatureScript
{
    public:
        npc_swift_mountain_horse() : CreatureScript("npc_swift_mountain_horse") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_RIDE            = 1,
                EVENT_OPEN_GATE_1           = 2,
                EVENT_OPEN_GATE_2           = 3,
                EVENT_DONE_RIDE             = 4,

                GO_FIRST_GATE               = 196863,
                GO_SECOND_GATE              = 196864,

                SPELL_EJECT_ALL_PASSENGERS  = 50630,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                events.ScheduleEvent(EVENT_START_RIDE, 1500);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RIDE:
                            me->GetMotionMaster()->MoveSplinePath(1);
                            events.ScheduleEvent(EVENT_OPEN_GATE_1, me->GetSplineDuration() - 250);
                            break;
                        case EVENT_OPEN_GATE_1:
                            {
                                if (GameObject* gate = me->FindNearestGameObject(GO_FIRST_GATE, 30.0f))
                                    if (gate->GetGoState() == GO_STATE_READY)
                                        gate->UseDoorOrButton();

                                me->GetMotionMaster()->MoveSplinePath(2);
                                events.ScheduleEvent(EVENT_OPEN_GATE_2, me->GetSplineDuration() - 250);
                            }
                            break;
                        case EVENT_OPEN_GATE_2:
                            {
                                if (GameObject* gate = me->FindNearestGameObject(GO_SECOND_GATE, 30.0f))
                                    if (gate->GetGoState() == GO_STATE_READY)
                                        gate->UseDoorOrButton();

                                me->GetMotionMaster()->MoveSplinePath(3);
                                events.ScheduleEvent(EVENT_DONE_RIDE, me->GetSplineDuration());
                            }
                            break;
                        case EVENT_DONE_RIDE:
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                            break;
                    }
                }
            }
        };
};

class npc_gwen_armstead_phase_8 final : public CreatureScript
{
    public:
        npc_gwen_armstead_phase_8() : CreatureScript("npc_gwen_armstead_phase_8") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            enum
            {
                SPELL_FORCECAST_SUMMON_SWIFT_MOUNTAIN_HORSE = 69256,
            };

            if (quest->GetQuestId() == QUEST_TO_GREYMANE_MANOR)
                creature->CastSpell(player, SPELL_FORCECAST_SUMMON_SWIFT_MOUNTAIN_HORSE, false, NULL, NULL, player->GetGUID());

            return false;
        }
};

// Quest The King's Observatory 14466, Alas, Gilneas! 14467
class npc_king_genn_greymane_c3 final : public CreatureScript
{
    public:
        npc_king_genn_greymane_c3() : CreatureScript("npc_king_genn_greymane_c3") { }

    private:
        enum
        {
            SPELL_CATACLYSM                 = 80134,
            CINEMATIC_TELESCOPE             = 167,
        };

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_THE_KINGS_OBSERVATORY)
            {
                player->CastSpell(player, SPELL_CATACLYSM, false);
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_11, false);
                WorldLocation loc;
                loc.m_mapId = 654;
                loc.Relocate(player);
                player->SetHomebind(loc, 4817);
                player->SaveToDB();
            }
            else if (quest->GetQuestId() == QUEST_ALAS_GILNEAS)
                player->SendCinematicStart(CINEMATIC_TELESCOPE);

            return false;
        }

        bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_EXODUS)
            {
                player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
                player->SaveToDB();
            }

            return false;
        }
};

///////////
// Quest Exodus 24438
///////////

enum
{
    NPC_QE_MARIE_ALLEN              = 38853,
    NPC_QE_GWEN_ARMSTEAD            = 44460,
    NPC_QE_KRENNAN_ARANAS           = 36138,
    NPC_QE_DUSKHAVEN_WATCHMAN       = 43907,
    NPC_QE_DUSKHAVEN_WATCHMAN_GUN   = 37946,
    NPC_QE_LORNA_CROWLEY            = 51409,
};

struct CarriageAccessory final
{
    uint8 seatId;
    uint32 entry;
};

const CarriageAccessory carriageAccessories[6]=
{
    {1, NPC_QE_MARIE_ALLEN},
    {4, NPC_QE_GWEN_ARMSTEAD},
    {3, NPC_QE_KRENNAN_ARANAS},
    {2, NPC_QE_DUSKHAVEN_WATCHMAN},
    {5, NPC_QE_DUSKHAVEN_WATCHMAN_GUN},
    {6, NPC_QE_LORNA_CROWLEY},
};

class npc_stagecoach_harness_summoner final : public CreatureScript
{
    public:
        npc_stagecoach_harness_summoner() : CreatureScript("npc_stagecoach_harness_summoner") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            void InitializeAI() final
            {
                me->CastSpell(me, SPELL_GENERIC_QUEST_INVISIBILITY_2, false);
            }

            void JustSummoned(Creature* summoned) final
            {
                summoned->CastSpell(summoned, SPELL_GENERIC_QUEST_INVISIBILITY_2, false);
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                switch (seatId)
                {
                    case 0:
                        passenger->m_movementInfo.t_pos.Relocate(3.4765f, -0.7888f);
                        enterPos.Relocate(3.4765f, -0.7888f);
                        break;
                    case 1:
                        passenger->m_movementInfo.t_pos.Relocate(3.4765f, 0.7888f);
                        enterPos.Relocate(3.4765f, 0.7888f);
                        break;
                    case 2:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, 0.f, -0.0139f);
                        enterPos.Relocate(0.f, 0.f, -0.0139f);
                        break;
                }
            }
        };
};

class npc_stagecoach_carriage_summoner final : public CreatureScript
{
    public:
        npc_stagecoach_carriage_summoner() : CreatureScript("npc_stagecoach_carriage_summoner") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                ACTION_INSTALL_ACCESSORIES      = 1,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_INSTALL_ACCESSORIES), me->m_Events.CalculateTime(250), true);
            }

            void OnSpellClick(Unit* player, bool &/*result*/) final
            {
                player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);
                player->RemoveAurasByType(SPELL_AURA_MOD_INVISIBILITY_DETECT);
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_19, false);
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_INSTALL_ACCESSORIES)
                {
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        for (int i = 0; i < 6; ++i)
                            if (Creature* passenger = summoner->SummonCreature(carriageAccessories[i].entry, *me))
                                passenger->EnterVehicle(me, carriageAccessories[i].seatId);

                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                }
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                switch (seatId)
                {
                    case 1:
                        passenger->m_movementInfo.t_pos.Relocate(0.25f, 0.f, -0.4f);
                        enterPos.Relocate(0.25f, 0.f, -0.4f);
                        break;
                    case 2:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        break;
                    case 3:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        break;
                    case 4:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, -0.8f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, -0.8f, -0.4f, 3.141593f);
                        break;
                    case 5:
                        passenger->m_movementInfo.t_pos.Relocate(1.f, -1.8f, 3.1f);
                        enterPos.Relocate(1.f, -1.8f, 3.1f);
                        break;
                    case 6:
                        passenger->m_movementInfo.t_pos.Relocate(1.f, 0.4f, 3.f, 0.5235987f);
                        enterPos.Relocate(1.f, 0.4f, 3.f, 0.5235987f);
                        break;
                }
            }
        };
};

static const uint32 ropeSpellEntry[2]=
{
    84171,
    84167,
};

class npc_stagecoach_harness_escort final : public CreatureScript
{
    public:
        npc_stagecoach_harness_escort() : CreatureScript("npc_stagecoach_harness_escort") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature)
                : VehicleAI(creature)
                , summons(creature)
                , lornaGUID(0)
            { }

            enum
            {
                EVENT_START_RIDE            = 1,
                EVENT_OPEN_KING_GATE        = 2,
                EVENT_OGRES_ATTACK_1        = 3,
                EVENT_OGRES_ATTACK_2        = 4,
                EVENT_OGRES_ATTACK_3        = 5,
                EVENT_DONE_RIDE             = 6,
                EVENT_FINISH_DRIVE          = 7,
                EVENT_CHECK_SUMMONER_STATE  = 8,
                EVENT_ROPE                  = 9,

                NPC_QE_YOUNG_MASTIFF        = 42722,
                NPC_QE_OGRE_AMBUSHER        = 38762,

                GO_GREYMANE_GATE            = 196401,
                GO_KINGS_GATE               = 196412,

                SPELL_THROW_BOULDER         = 72768,

                EXODUS_PHASE_MASK           = 33685504,

                ACTION_INSTALL_ACCESSORIES  = 1,
                ACTION_DESPAWN              = 2,

                LORNA_YELL_CARRIAGE         = 1,
            };

            EventMap events;
            SummonList summons;
            uint64 lornaGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetPhaseMask(EXODUS_PHASE_MASK, true);
                me->setActive(true);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_INSTALL_ACCESSORIES:
                        {
                            static const uint32 accessoryEntry[3]=
                            {
                                43338,
                                43338,
                                43337,
                            };

                            for (int i = 0; i < 3; ++i)
                                if (Creature* passenger = me->SummonCreature(accessoryEntry[i], *me))
                                    passenger->EnterVehicle(me, i);
                        }
                        break;
                    case ACTION_DESPAWN:
                        summons.DespawnAll();
                        me->DespawnOrUnsummon();
                        break;
                }
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());

                if (Player* player = summoner->ToPlayer())
                    player->CompleteQuest(QUEST_EXODUS);

                events.ScheduleEvent(EVENT_ROPE, 2000);
                events.ScheduleEvent(EVENT_START_RIDE, 3000);
                events.ScheduleEvent(EVENT_CHECK_SUMMONER_STATE, 3000);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_INSTALL_ACCESSORIES), me->m_Events.CalculateTime(250), true);
            }

            void JustSummoned(Creature* summoned) final
            {
                summons.Summon(summoned);
                summoned->SetPhaseMask(EXODUS_PHASE_MASK, true);
                summoned->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, me->ToTempSummon()->GetSummonerGUID());
                summoned->setActive(true);

                if (summoned->GetEntry() == 51409)
                    lornaGUID = summoned->GetGUID();
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ROPE:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    if (Vehicle* vehicle = me->GetVehicleKit())
                                        for (int i = 0; i < 2; ++i)
                                            if (Unit* passenger = vehicle->GetPassenger(i))
                                                summoner->CastSpell(passenger, ropeSpellEntry[i], false);
                            }
                            break;
                        case EVENT_START_RIDE:
                            {
                                float x, y;
                                me->GetNearPoint2D(x, y, 5.f, M_PI - me->GetOrientation());

                                if (Creature* mastiff = me->SummonCreature(NPC_QE_YOUNG_MASTIFF, x, y, me->GetPositionZ(), me->GetOrientation()))
                                    mastiff->GetMotionMaster()->MoveFollow(me, 1.0f, M_PI / 2, MOTION_SLOT_CONTROLLED);

                                if (Creature* mastiff = me->SummonCreature(NPC_QE_YOUNG_MASTIFF, x, y, me->GetPositionZ(), me->GetOrientation()))
                                    mastiff->GetMotionMaster()->MoveFollow(me, 1.0f, -M_PI / 2, MOTION_SLOT_CONTROLLED);

                                if (GameObject* gate = me->FindNearestGameObject(GO_GREYMANE_GATE, 30.0f))
                                    if (gate->GetGoState() == GO_STATE_READY)
                                        gate->UseDoorOrButton();

                                me->GetMotionMaster()->MoveSplinePath(1);
                                events.ScheduleEvent(EVENT_OPEN_KING_GATE, me->GetSplineDuration() - 250);
                            }
                            break;
                        case EVENT_OPEN_KING_GATE:
                            {
                                if (GameObject* gate = me->FindNearestGameObject(GO_KINGS_GATE, 30.0f))
                                    if (gate->GetGoState() == GO_STATE_READY)
                                        gate->UseDoorOrButton();

                                me->GetMotionMaster()->MoveSplinePath(2);
                                events.ScheduleEvent(EVENT_OGRES_ATTACK_1, me->GetSplineDuration() - 250);
                            }
                            break;
                        case EVENT_OGRES_ATTACK_1:
                            {
                                if (Creature* lorna = ObjectAccessor::GetCreature(*me, lornaGUID))
                                    if (lorna->IsAIEnabled)
                                        lorna->AI()->Talk(LORNA_YELL_CARRIAGE, me->ToTempSummon()->GetSummonerGUID(), true);

                                me->GetMotionMaster()->MoveSplinePath(3);
                                events.ScheduleEvent(EVENT_OGRES_ATTACK_2, 250);
                                events.ScheduleEvent(EVENT_DONE_RIDE, me->GetSplineDuration() + 500);
                            }
                            break;
                        case EVENT_OGRES_ATTACK_2:
                            events.ScheduleEvent(EVENT_OGRES_ATTACK_3, 1000);
                        case EVENT_OGRES_ATTACK_3:
                            {
                                std::list<Creature*> ogreList;
                                GetCreatureListWithEntryInGrid(ogreList, me, NPC_QE_OGRE_AMBUSHER, 50.0f);

                                if (!ogreList.empty())
                                {
                                    if (Creature* ogre = Trinity::Containers::SelectRandomContainerElement(ogreList))
                                    {
                                        float x, y, z;
                                        me->GetPosition(x, y, z);
                                        ogre->CastSpell(x, y, z, SPELL_THROW_BOULDER, false);
                                    }
                                }
                            }
                            break;
                        case EVENT_DONE_RIDE:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    summoner->ExitVehicle();
                                    summoner->RemoveAurasByType(SPELL_AURA_PHASE);
                                    summoner->CastSpell(summoner, SPELL_ZONE_SPECIFIC_11, false);

                                    if (Vehicle* vehicle = me->GetVehicleKit())
                                        for (int i = 0; i < 2; ++i)
                                            if (Unit* passenger = vehicle->GetPassenger(i))
                                                passenger->RemoveAura(ropeSpellEntry[i]);

                                    if (Player* player = summoner->ToPlayer())
                                        player->SaveToDB();
                                }

                                events.ScheduleEvent(EVENT_FINISH_DRIVE, 1000);
                            }
                            break;
                        case EVENT_FINISH_DRIVE:
                            me->GetMotionMaster()->MoveSplinePath(4);
                            me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_DESPAWN), me->m_Events.CalculateTime(me->GetSplineDuration()), true);
                            break;
                        case EVENT_CHECK_SUMMONER_STATE:
                            {
                                if (!me->ToTempSummon()->GetSummoner())
                                {
                                    summons.DespawnAll();
                                    me->DespawnOrUnsummon();
                                    return;
                                }

                                events.ScheduleEvent(EVENT_CHECK_SUMMONER_STATE, 500);
                            }
                            break;
                    }
                }
            }
        };
};

class npc_stagecoach_carriage_escort final : public CreatureScript
{
    public:
        npc_stagecoach_carriage_escort() : CreatureScript("npc_stagecoach_carriage_escort") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                ACTION_INSTALL_ACCESSORIES      = 1,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_INSTALL_ACCESSORIES), me->m_Events.CalculateTime(250), true);
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_INSTALL_ACCESSORIES)
                {
                    Position pos;
                    me->GetPosition(&pos);

                    if (Creature* harness = me->ToTempSummon()->GetSummonerCreatureBase())
                    {
                        for (int i = 0; i < 6; ++i)
                            if (Creature* passenger = harness->SummonCreature(carriageAccessories[i].entry, pos))
                                passenger->EnterVehicle(me, carriageAccessories[i].seatId);

                        if (harness->IsSummon())
                            if (Unit* summoner = harness->ToTempSummon()->GetSummoner())
                                summoner->EnterVehicle(me, 0);
                    }
                }
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                switch (seatId)
                {
                    case 1:
                        passenger->m_movementInfo.t_pos.Relocate(0.25f, 0.f, -0.4f);
                        enterPos.Relocate(0.25f, 0.f, -0.4f);
                        break;
                    case 2:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        break;
                    case 3:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, 0.f, -0.4f, 3.141593f);
                        break;
                    case 4:
                        passenger->m_movementInfo.t_pos.Relocate(0.f, -0.8f, -0.4f, 3.141593f);
                        enterPos.Relocate(0.f, -0.8f, -0.4f, 3.141593f);
                        break;
                    case 5:
                        passenger->m_movementInfo.t_pos.Relocate(1.f, -1.8f, 3.1f);
                        enterPos.Relocate(1.f, -1.8f, 3.1f);
                        break;
                    case 6:
                        passenger->m_movementInfo.t_pos.Relocate(1.f, 0.4f, 3.f, 0.5235987f);
                        enterPos.Relocate(1.f, 0.4f, 3.f, 0.5235987f);
                        break;
                }
            }
        };
};

// Quest Stranded at the Marsh 24468
class npc_crash_survivor final : public CreatureScript
{
    public:
        npc_crash_survivor() : CreatureScript("npc_crash_survivor") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , canSummon(true)
            { }

            enum
            {
                NPC_SWAMP_CROCOLISK = 37078,
                SURVIVOR_RANDOM_SAY = 1,
            };

            bool canSummon;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                Reset();
            }

            void Reset() final
            {
                if (canSummon)
                {
                    canSummon = false;

                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                    float x, y;
                    me->GetNearPoint2D(x, y, 3.0f, me->GetOrientation());

                    if (Creature* crocolisk = me->SummonCreature(NPC_SWAMP_CROCOLISK, x, y, me->GetPositionZ()))
                    {
                        AttackStart(crocolisk);
                        me->getThreatManager().addThreat(crocolisk, std::numeric_limits<float>::max());
                        crocolisk->getThreatManager().addThreat(me, std::numeric_limits<float>::max());
                    }
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void SummonedCreatureDies(Creature* summoned, Unit* /*killer*/) final
            {
                Talk(SURVIVOR_RANDOM_SAY);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                EnterEvadeMode();
                canSummon = true;
                me->DespawnOrUnsummon(3500);
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_swamp_crocolisk final : public CreatureScript
{
    public:
        npc_swamp_crocolisk() : CreatureScript("npc_swamp_crocolisk") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
                else
                {
                    if (Unit* victim = me->GetVictim())
                    {
                        if (victim->GetTypeId() == TYPEID_UNIT)
                        {
                            me->getThreatManager().resetAllAggro();
                            me->getThreatManager().addThreat(attacker, std::numeric_limits<float>::max());
                            AttackStart(attacker);
                        }
                    }
                }
            }
        };
};

// Quest Introductions Are in Order 24472
enum
{
    ACTION_KOROTH_ATTACK    = 2,
};

const float AstherWP[18][3]=
{
    {-2129.99f, 1824.12f, 25.234f},{-2132.93f, 1822.23f, 23.984f},{-2135.81f, 1820.23f, 22.770f},
    {-2138.72f, 1818.29f, 21.595f},{-2141.77f, 1816.57f, 20.445f},{-2144.88f, 1814.96f, 19.380f},
    {-2147.19f, 1813.85f, 18.645f},{-2150.51f, 1812.73f, 17.760f},{-2153.88f, 1811.80f, 16.954f},
    {-2157.28f, 1810.95f, 16.194f},{-2160.69f, 1810.20f, 15.432f},{-2164.12f, 1809.46f, 14.688f},
    {-2167.55f, 1808.81f, 13.961f},{-2171.01f, 1808.27f, 13.316f},{-2174.32f, 1808.00f, 12.935f},
    {-2177.11f, 1807.75f, 12.717f},{-2179.79f, 1807.67f, 12.573f},{-2183.06f, 1807.59f, 12.504f},
};

class npc_koroth_the_hillbreaker_friend final : public CreatureScript
{
    public:
        npc_koroth_the_hillbreaker_friend() : CreatureScript("npc_koroth_the_hillbreaker_friend") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_CLEAVE                = 1,
                EVENT_DEMORALIZING_SHOUT    = 2,

                KOROTH_YELL_MY_BANNER       = 1,

                SPELL_CLEAVE                = 16044,
                SPELL_DEMORALIZING_SHOUT    = 16244,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                SetCombatMovement(false);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->GetMotionMaster()->MoveSplinePath(1);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_KOROTH_ATTACK), me->m_Events.CalculateTime(me->GetSplineDuration() - 500));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_KOROTH_ATTACK)
                {
                    me->SetHomePosition( -2159.564f, 1849.091f, 17.805f, 3.947f);

                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                    if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
                    {
                        if (summoner->IsAIEnabled)
                            summoner->GetAI()->DoAction(ACTION_KOROTH_ATTACK);

                        if (summoner->IsSummon())
                            Talk(KOROTH_YELL_MY_BANNER, summoner->ToTempSummon()->GetSummonerGUID(), true);
                    }

                    me->CastSpell((Unit*)NULL, 86112, false);
                }
            }

            void EnterCombat(Unit* /*who*/) final
            {
                events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, 1000);
                events.ScheduleEvent(EVENT_CLEAVE, urand(2500, 5000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CLEAVE:
                            me->CastSpell(me->GetVictim(), SPELL_CLEAVE, false);
                            events.ScheduleEvent(EVENT_CLEAVE, urand(5000, 15000));
                            break;
                        case EVENT_DEMORALIZING_SHOUT:
                            me->CastSpell((Unit*)NULL, SPELL_DEMORALIZING_SHOUT, false);
                            events.ScheduleEvent(EVENT_DEMORALIZING_SHOUT, 5000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_captain_asther_qiao final : public CreatureScript
{
    public:
        npc_captain_asther_qiao() : CreatureScript("npc_captain_asther_qiao") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public SmoothEscortAI
        {
            creature_script_impl(Creature* creature)
                : SmoothEscortAI(creature)
                , korothGUID(0)
            { }

            enum
            {
                NPC_KOROTH_THE_HILLBREAKER_FRIEND   = 37808,
                NPC_CAPTAIN_ASTHER                  = 37806,
                NPC_FORSAKEN_SOLDIER                = 37805,
                NPC_FORSAKEN_CATAPULT               = 37807,

                CAPITAN_YELL_WILL_ORDER             = 1,
            };

            struct Minion
            {
                uint64 minionGUID;
                float angle;
                float dist;
            };

            std::list<Minion> minions;
            uint64 korothGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_SEER_CREATURE, summoner->GetGUID());
                StartEvent();
            }

            void JustSummoned(Creature* summoned) final
            {
                summoned->SetReactState(REACT_PASSIVE);
                summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
                summoned->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_SEER_CREATURE, me->ToTempSummon()->GetSummonerGUID());
                summoned->setActive(true);
            }

            void StartMoveTo(float x, float y, float z) final
            {
                if (minions.empty())
                    return;

                float pathangle = atan2(me->GetPositionY() - y, me->GetPositionX() - x);

                for (std::list<Minion>::iterator itr = minions.begin(); itr != minions.end(); ++itr)
                {
                    if (Creature* member = ObjectAccessor::GetCreature(*me, itr->minionGUID))
                    {
                        if (!member->IsAlive() || member->IsInCombat())
                            continue;

                        float dx = x - cos(itr->angle + pathangle) * itr->dist;
                        float dy = y - sin(itr->angle + pathangle) * itr->dist;
                        float dz = member->GetBaseMap()->GetHeight(member->GetPhaseMask(), dx, dy, MAX_HEIGHT);

                        float dist = member->GetExactDist(dx, dy, dz);
                        float time = me->GetSplineDuration();

                        Movement::MoveSplineInit init(member);
                        init.MoveTo(dx, dy, dz);
                        init.SetVelocity(dist / time * IN_MILLISECONDS);
                        init.Launch();

                        member->SetHomePosition(dx, dy, dz, pathangle + M_PI);
                    }
                }
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_KOROTH_ATTACK)
                {
                    if (Creature* koroth = ObjectAccessor::GetCreature(*me, korothGUID))
                    {
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                        float x, y, z;
                        koroth->GetNearPoint(koroth, x, y, z, 0.0f, 2.0f, koroth->GetOrientation() + M_PI);
                        me->GetMotionMaster()->MoveCharge(x, y, z);

                        for (std::list<Minion>::iterator itr = minions.begin(); itr != minions.end(); ++itr)
                        {
                            if (Creature* minion = ObjectAccessor::GetCreature(*me, itr->minionGUID))
                            {
                                minion->SetReactState(REACT_AGGRESSIVE);
                                minion->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                                switch (minion->GetEntry())
                                {
                                    case NPC_FORSAKEN_SOLDIER:
                                        koroth->GetNearPoint(koroth, x, y, z, 0.0f, 2.0f, koroth->GetOrientation() + frand(-M_PI, M_PI));
                                        me->GetMotionMaster()->MoveCharge(x, y, z);
                                        minion->GetMotionMaster()->MoveCharge(x, y, z);
                                        break;
                                    case NPC_FORSAKEN_CATAPULT:
                                        koroth->AddThreat(minion, std::numeric_limits<float>::max());
                                        break;
                                }
                            }
                        }
                    }
                }
            }

            void SummonMinion(uint32 MinionEntry, float dist, float angle)
            {
                float x, y, z;
                me->GetNearPoint2D(x, y, dist, me->GetOrientation() + angle);
                z = me->GetBaseMap()->GetHeight(me->GetPhaseMask(), x, y, MAX_HEIGHT);

                if (Creature* minion = me->SummonCreature(MinionEntry, x, y, z, me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
                {
                    Minion newMinion;
                    newMinion.minionGUID = minion->GetGUID();
                    newMinion.angle = angle;
                    newMinion.dist = dist;
                    minions.push_back(newMinion);
                }
            }

            void StartEvent()
            {
                for (int i = 2; i < 5; ++i)
                {
                    SummonMinion(NPC_FORSAKEN_SOLDIER, i * 2, M_PI);
                    SummonMinion(NPC_FORSAKEN_SOLDIER, i * 2 + 2, M_PI -  M_PI / (2 * i));
                    SummonMinion(NPC_FORSAKEN_SOLDIER, i * 2 + 2, M_PI +  M_PI / (2 * i));
                }

                SummonMinion(NPC_FORSAKEN_CATAPULT, 15.f, M_PI);

                for (int i = 0; i < 18; ++i)
                    AddWaypoint(i, AstherWP[i][0], AstherWP[i][1], AstherWP[i][2]);

                SetTimeDiff(350);
                Start();
            }

            void WaypointReached(uint32 point) final
            {
                if (point == 15)
                {
                    if (Creature* koroth = me->SummonCreature(NPC_KOROTH_THE_HILLBREAKER_FRIEND, -2213.64f, 1863.51f, 15.404f, 5.43f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
                        korothGUID = koroth->GetGUID();

                    Talk(CAPITAN_YELL_WILL_ORDER, me->ToTempSummon()->GetSummonerGUID(), true);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_prince_liam_greymane_qiao final : public CreatureScript
{
    public:
        npc_prince_liam_greymane_qiao() : CreatureScript("npc_prince_liam_greymane_qiao") { }

    private:
        enum
        {
            NPC_CAPTAIN_ASTHER              = 37806,
            NPC_PRINCE_LIAM_GREYMANE        = 37065,

            SPELL_PUSH_BANNER               = 70511,

            EVENT_LIAM_TALK_HERE_FORSAKEN   = 1,
            EVENT_LIAM_YELL_YOU_CANT        = 2,
            EVENT_LIAM_PUSH_BANNER          = 3,

            LIAM_TALK_HERE_FORSAKEN         = 1,
            LIAM_YELL_YOU_CANT              = 2,
        };

        class PersonalTalkEvent final : public BasicEvent
        {
            public:
                PersonalTalkEvent(Creature* source, uint64 playerGUID, uint8 eventId)
                    : _source(source)
                    , _playerGUID(playerGUID)
                    , _eventId(eventId)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    switch (_eventId)
                    {
                        case EVENT_LIAM_TALK_HERE_FORSAKEN:
                            {
                                if (_source->IsAIEnabled)
                                    _source->AI()->Talk(LIAM_TALK_HERE_FORSAKEN, _playerGUID, true);

                                _source->m_Events.AddEvent(new PersonalTalkEvent(_source, _playerGUID, EVENT_LIAM_YELL_YOU_CANT), _source->m_Events.CalculateTime(12000));
                            }
                            break;
                        case EVENT_LIAM_YELL_YOU_CANT:
                            {
                                if (_source->IsAIEnabled)
                                    _source->AI()->Talk(LIAM_YELL_YOU_CANT, _playerGUID, true);

                                _source->m_Events.AddEvent(new PersonalTalkEvent(_source, _playerGUID, EVENT_LIAM_PUSH_BANNER), _source->m_Events.CalculateTime(8000));
                            }
                            break;
                        case EVENT_LIAM_PUSH_BANNER:
                            _source->CastSpell((Unit*)NULL, SPELL_PUSH_BANNER, false);
                            break;
                    }

                    return true;
                }

                Creature* _source;
                uint64 _playerGUID;
                uint8 _eventId;
        };

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            switch (quest->GetQuestId())
            {
                case QUEST_EXODUS:
                    player->CastSpell(player, 95679, false);
                    break;
                case QUEST_INTRODUCTIONS_ARE_IN_ORDER:
                    player->SummonCreature(NPC_CAPTAIN_ASTHER, -2120.19f, 1833.06f, 30.1510f,  3.87363f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    creature->m_Events.AddEvent(new PersonalTalkEvent(creature, player->GetGUID(), EVENT_LIAM_TALK_HERE_FORSAKEN), creature->m_Events.CalculateTime(250));
                    break;
            }

            return false;
        }
};

enum
{
    ACTION_START_EVENT  = 100,
};

class npc_koroth_the_hillbreaker final : public CreatureScript
{
    public:
        npc_koroth_the_hillbreaker() : CreatureScript("npc_koroth_the_hillbreaker") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                ACTION_TALK             = 1,
                ACTION_RETURN           = 2,

                YELL_WHO_STEAL_BANNER   = 1,
                YELL_FIND_YOU           = 2,
            };

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_EVENT:
                        Talk(YELL_WHO_STEAL_BANNER);
                        me->GetMotionMaster()->MovePointSmooth(-2284.237f, 1963.801f);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TALK), me->m_Events.CalculateTime(me->GetSplineDuration()));
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_RETURN), me->m_Events.CalculateTime(me->GetSplineDuration() + 3500));
                        break;
                    case ACTION_TALK:
                        Talk(YELL_FIND_YOU);
                        break;
                    case ACTION_RETURN:
                        me->GetMotionMaster()->MoveTargetedHome();
                        break;
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class go_koroth_banner final : public GameObjectScript
{
    public:
        go_koroth_banner() : GameObjectScript("go_koroth_banner") { }

    private:
        bool OnGossipHello(Player* player, GameObject* go) final
        {
            enum
            {
                NPC_KOROTH_THE_HILLBREAKER  = 36294,
            };

            if (Creature* koroth = go->FindNearestCreature(NPC_KOROTH_THE_HILLBREAKER, 30.0f))
                if (koroth->IsAIEnabled)
                    koroth->GetAI()->DoAction(ACTION_START_EVENT);

            return false;
        }
};

// Quest Losing Your Tail 24616
enum
{
    ACTION_PLAYER_IS_FREE       = 1,
};

class at_losing_your_tail final : public AreaTriggerScript
{
    public:
        at_losing_your_tail() : AreaTriggerScript("at_losing_your_tail") { }

    private:
        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/) final
        {
            enum
            {
                SPELL_DARK_SCOUT_TRACKER    = 95845,
                SPELL_FREEZING_TRAP_EFFECT  = 70794,

                NPC_TRIGGER                 = 35374,
            };

            if (player->GetQuestStatus(QUEST_LOSING_YOUR_TAIL) == QUEST_STATUS_INCOMPLETE && !player->HasAura(SPELL_DARK_SCOUT_TRACKER))
                if (Creature* trigger = player->FindNearestCreature(NPC_TRIGGER, 50.f))
                    trigger->CastSpell(player, SPELL_FREEZING_TRAP_EFFECT, false, NULL, NULL, player->GetGUID());

            return true;
        }
};

class npc_dark_scout final : public CreatureScript
{
    public:
        npc_dark_scout() : CreatureScript("npc_dark_scout") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new spell_script_impl (creature);
        }

        struct spell_script_impl final : public ScriptedAI
        {
            spell_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                NPC_DARK_SCOUT_SAY_CATCH    = 1,
                NPC_DARK_SCOUT_SAY_HOW      = 2,
                NPC_DARK_SCOUT_SAY_FREE     = 3,

                SPELL_AIMED_SHOT            = 70796,
            };

            void IsSummonedBy(Unit* summoner) final
            {
                Talk(NPC_DARK_SCOUT_SAY_CATCH);
                Talk(NPC_DARK_SCOUT_SAY_FREE, summoner->GetGUID(), true);
                AttackStart(summoner);
                me->CastSpell(summoner, SPELL_AIMED_SHOT, false);
            }

            void EnterEvadeMode() final
            {
                me->DespawnOrUnsummon();
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_PLAYER_IS_FREE)
                {
                    Talk(NPC_DARK_SCOUT_SAY_HOW);
                    me->CastStop();
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_belysras_talisman final : public SpellScriptLoader
{
    public:
        spell_belysras_talisman() : SpellScriptLoader("spell_belysras_talisman") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_PLAYER_IS_FREE);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest At Our Doorstep 24627
enum
{
    NPC_LYROS_SWIFTWIND     = 37870,
    NPC_VASSANDRA_STORMCLAW = 37873,
    NPC_TALRAN_OF_THE_WILD  = 36814,

    CROWLEY_YELL_LORNA      = 2,
    CROWLEY_YELL_FROG       = 3,
    CROWLEY_SAY_YES_GENN    = 4,
};

class npc_lord_darius_crowley_qaod final : public CreatureScript
{
    public:
        npc_lord_darius_crowley_qaod() : CreatureScript("npc_lord_darius_crowley_qaod") { }

    private:
        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_FORCECAST_SUMMON_TOBIAS   = 71042,
                SPELL_FORCECAST_TALDOREN_MASTER = 72829,
            };

            switch (quest->GetQuestId())
            {
                case QUEST_AT_OUR_DOORSTEP:
                    creature->CastSpell(player, SPELL_FORCECAST_SUMMON_TOBIAS, false, NULL, NULL, player->GetGUID());
                    break;
                case QUEST_NEITHER_HUMAN_NOR_BEAST:
                    creature->CastSpell(player, SPELL_FORCECAST_TALDOREN_MASTER, false, NULL, NULL, player->GetGUID());
                    break;
            }

            return false;
        }
};

class npc_tobias_mistmantle_qaod final : public CreatureScript
{
    public:
        npc_tobias_mistmantle_qaod() : CreatureScript("npc_tobias_mistmantle_qaod") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_SAY_FORSAKEN              = 1,
                EVENT_CROWLEY_SAY_IMMEDIATELY   = 2,
                EVENT_SAY_OK                    = 3,
                EVENT_GO_AWAY                   = 4,

                NPC_LORD_DARIUS_CROWLEY         = 37195,

                TOBIAS_SAY_FORSAKEN             = 1,
                CROWLEY_SAY_IMMEDIATELY         = 1,
                TOBIAS_SAY_OK                   = 2,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER, summoner->GetGUID());
                me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                events.ScheduleEvent(EVENT_SAY_FORSAKEN, me->GetSplineDuration());
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SAY_FORSAKEN:
                            Talk(TOBIAS_SAY_FORSAKEN, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_CROWLEY_SAY_IMMEDIATELY, 5000);
                            break;
                        case EVENT_CROWLEY_SAY_IMMEDIATELY:
                            {
                                if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY, 30.0f))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_SAY_IMMEDIATELY, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_SAY_OK, 7000);
                            }
                            break;
                        case EVENT_SAY_OK:
                            Talk(TOBIAS_SAY_OK, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_GO_AWAY, 3000);
                            break;
                        case EVENT_GO_AWAY:
                            me->GetMotionMaster()->MoveSplinePath(2, false, false, 0.f, false, false);
                            me->DespawnOrUnsummon(me->GetSplineDuration());
                            break;
                    }
                }
            }
        };
};

// Quest Take Back What's Ours 24646
enum
{
    ACTION_BACK                     = 100,
};

struct TrackerRetreatPOS final
{
    Position startPos;
    Position jumpPos;
};

static TrackerRetreatPOS const TrackerPOS[3]=
{
    { { -2111.665f, 1614.726f, -42.916f, 0.0f }, { -2094.177f, 1594.787f, -33.995f, 0.0f } },
    { { -2133.185f, 1612.644f, -43.593f, 0.0f }, { -2100.651f, 1568.200f, -30.421f, 0.0f } },
    { { -2147.640f, 1624.307f, -43.179f, 0.0f }, { -2178.477f, 1620.596f, -22.339f, 0.0f } },
};

class npc_taldoren_tracker final : public CreatureScript
{
    public:
        npc_taldoren_tracker() : CreatureScript("npc_taldoren_tracker") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , retreatId(0)
            { }

            enum
            {
                ATCTION_JUMP    = 1,

                SPELL_WAR_STOMP = 71019,
            };

            uint8 retreatId;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_BACK:
                        {
                            float dist = std::numeric_limits<float>::max();

                            for (int i = 0; i < 3; ++i)
                            {
                                float _dist = me->GetExactDist2dSq(&TrackerPOS[i].startPos);

                                if (dist > _dist)
                                {
                                    dist = _dist;
                                    retreatId = i;
                                }
                            }

                            me->CastSpell((Unit*)NULL, SPELL_WAR_STOMP, false);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetReactState(REACT_PASSIVE);
                            me->DeleteThreatList();
                            me->CombatStop();
                            me->GetMotionMaster()->MoveSplinePath(retreatId, false, false, 0.f, false, false);
                            me->m_Events.AddEvent(new DelayEventDoAction(me, ATCTION_JUMP), me->m_Events.CalculateTime(me->GetSplineDuration()));
                        }
                        break;
                    case ATCTION_JUMP:
                        me->GetMotionMaster()->MoveJump(TrackerPOS[retreatId].jumpPos, 20.f, 20.f);
                        me->DespawnOrUnsummon(me->GetSplineDuration() + 500);
                        break;
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_tobias_mistmantle_qtbwo final : public CreatureScript
{
    public:
        npc_tobias_mistmantle_qtbwo() : CreatureScript("npc_tobias_mistmantle_qtbwo") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , summons(creature)
            { }

            enum
            {
                ACTION_EVENT_DONE           = 1,

                TOBIAS_SAY_DISTRACT_RANGERS = 1,
                TOBIAS_SAY_FALL_BACK        = 2,
            };

            SummonList summons;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                Talk(TOBIAS_SAY_DISTRACT_RANGERS, me->ToTempSummon()->GetSummonerGUID(), true);
                me->CastSpell((Unit*)NULL, 71011, false);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_EVENT_DONE), me->m_Events.CalculateTime(25000));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_EVENT_DONE)
                {
                    Talk(TOBIAS_SAY_FALL_BACK, me->ToTempSummon()->GetSummonerGUID(), true);
                    me->CastSpell((Unit*)NULL, 71018, false);
                    me->DespawnOrUnsummon(2000);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_horn_of_taldoren final : public SpellScriptLoader
{
    public:
        spell_horn_of_taldoren() : SpellScriptLoader("spell_horn_of_taldoren") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            enum
            {
                NPC_TOBIAS_MISTMANTLE   = 38029,
            };

            SpellCastResult CanCast()
            {
                if (Unit * caster = GetCaster())
                    if (Player* player = caster->ToPlayer())
                        if (caster->GetExactDist2dSq(-2146.12f, 1583.35f) < 900.0f &&
                            !caster->FindNearestCreature(NPC_TOBIAS_MISTMANTLE, 40.0f) &&
                            player->GetQuestStatus(QUEST_TAKE_BACK_WHATS_OURS) == QUEST_STATUS_INCOMPLETE)
                            return SPELL_CAST_OK;

                return SPELL_FAILED_BAD_TARGETS;
            }

            void Register() final
            {
                OnCheckCast += SpellCheckCastFn(spell_script_impl::CanCast);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class spell_retreat_trackers final : public SpellScriptLoader
{
    public:
        spell_retreat_trackers() : SpellScriptLoader("spell_retreat_trackers") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* target = GetHitUnit())
                    if (target->IsAIEnabled)
                        target->GetAI()->DoAction(ACTION_BACK);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

// Quest Neither Human Nor Beast 24593
class go_qnhnb_well final : public GameObjectScript
{
    public:
        go_qnhnb_well(const char* scriptName, uint32 druidEntry, uint8 goId)
            : GameObjectScript(scriptName)
            , _druidEntryd(druidEntry)
            , _goId(goId)
        { }

    private:
        uint32 _druidEntryd;
        uint8 _goId;

    private:
        bool OnGossipHello(Player* player, GameObject* go) final
        {
            enum
            {
                DRUID_TEXT_ID                    = 1,
                SPELL_TALDOREN_WELL              = 71200,
                NPC_TRIGGER                      = 35374,
                QUEST_OBJECTIVE_USE_WELL_OF_FURY = 266553,
            };

            if (player->GetQuestStatus(QUEST_NEITHER_HUMAN_NOR_BEAST) == QUEST_STATUS_INCOMPLETE)
            {
                QuestStatusMap::iterator itr = player->getQuestStatusMap().find(QUEST_NEITHER_HUMAN_NOR_BEAST);

                if (itr == player->getQuestStatusMap().end() || player->GetQuestObjectiveCounter(QUEST_OBJECTIVE_USE_WELL_OF_FURY + _goId) > 0)
                    return true;

                float x, y, z;
                go->GetPosition(x, y, z);

                if (Creature* trigger = player->SummonCreature(NPC_TRIGGER, x, y, z, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 15000))
                {
                    trigger->SetCustomVisibility(CUSTOM_VISIBILITY_SEER, player->GetGUID());
                    trigger->AddAura(SPELL_TALDOREN_WELL, trigger);
                }

                if (Creature* druid = go->FindNearestCreature(_druidEntryd, 30.0f))
                    if (druid->IsAIEnabled)
                        druid->AI()->Talk(DRUID_TEXT_ID, player->GetGUID(), true);
            }

            return false;
        }
};

class npc_lord_godfrey_qnhnb final : public CreatureScript
{
    public:
        npc_lord_godfrey_qnhnb() : CreatureScript("npc_lord_godfrey_qnhnb") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                ACTION_FACING           = 1,
                ACTION_TALK_1           = 2,
                ACTION_CAST             = 3,
                ACTION_TALK_2           = 4,

                GODFREY_SAY_LOW         = 1,
                GODFREY_YELL_CANT_BE    = 2,

                NPC_LORD_DARIUS_CROWLEY = 37195,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->DespawnOrUnsummon(70000);
                me->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_FACING), me->m_Events.CalculateTime(me->GetSplineDuration() + 1000));
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TALK_1), me->m_Events.CalculateTime(15000));
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_FACING:
                        {
                            if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY, 30.0f))
                                me->SetFacingToObject(crowley);
                        }
                        break;
                    case ACTION_TALK_1:
                        Talk(GODFREY_SAY_LOW, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_CAST), me->m_Events.CalculateTime(13000));
                        break;
                    case ACTION_CAST:
                        me->CastSpell((Unit*)NULL, 72822, false);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TALK_2), me->m_Events.CalculateTime(15000));
                        break;
                    case ACTION_TALK_2:
                        Talk(GODFREY_YELL_CANT_BE, me->ToTempSummon()->GetSummonerGUID(), true);
                        break;
                }
            }
        };
};

class npc_lorna_crowley_qnhnb final : public CreatureScript
{
    public:
        npc_lorna_crowley_qnhnb() : CreatureScript("npc_lorna_crowley_qnhnb") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                ACTION_TALK         = 1,
                ACTION_RESUME       = 2,
                ACTION_CAST         = 3,

                LORNA_YELL_FATHER   = 1,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->DespawnOrUnsummon(70000);
                me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TALK), me->m_Events.CalculateTime(me->GetSplineDuration()));
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_TALK:
                        Talk(LORNA_YELL_FATHER, me->ToTempSummon()->GetSummonerGUID());
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_CAST), me->m_Events.CalculateTime(2000));
                        break;
                    case ACTION_CAST:
                        me->CastSpell((Unit*)NULL, 72820, false, NULL, NULL, me->ToTempSummon()->GetSummonerGUID());
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_RESUME), me->m_Events.CalculateTime(3000));
                        break;
                    case ACTION_RESUME:
                        me->GetMotionMaster()->MoveSplinePath(2, false, true, 0.f, false, false);
                        break;
                }
            }
        };
};

class npc_king_genn_greymane_qnhnb final : public CreatureScript
{
    public:
        npc_king_genn_greymane_qnhnb() : CreatureScript("npc_king_genn_greymane_qnhnb") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                ACTION_FACING                       = 1,
                ACTION_TRANSFORM                    = 2,
                ACTION_CAST                         = 3,
                ACTION_TALK                         = 4,

                GREYMANE_SAY_FRIEND                 = 1,
                GREYMANE_SAY_HELD                   = 2,

                NPC_LORD_DARIUS_CROWLEY             = 37195,

                SPELL_WORGEN_COMBAT_TRANSFORM_FX    = 81768,
                SPELL_WORGEN_TRANSFORM              = 81908,
            };

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->DespawnOrUnsummon(70000);
                me->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_FACING), me->m_Events.CalculateTime(me->GetSplineDuration() + 1000));
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TRANSFORM), me->m_Events.CalculateTime(35000));
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_FACING:
                        {
                            if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY, 30.0f))
                                me->SetFacingToObject(crowley);
                        }
                        break;
                    case ACTION_TRANSFORM:
                        me->CastSpell(me, SPELL_WORGEN_COMBAT_TRANSFORM_FX, false);
                        me->CastSpell(me, SPELL_WORGEN_TRANSFORM, false);
                        me->SetDisplayId(31177);
                        Talk(GREYMANE_SAY_FRIEND, me->ToTempSummon()->GetSummonerGUID(), true);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_CAST), me->m_Events.CalculateTime(10000));
                        break;
                    case ACTION_CAST:
                        me->CastSpell((Unit*)NULL, 72824, false);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_TALK), me->m_Events.CalculateTime(11000));
                        break;
                    case ACTION_TALK:
                        Talk(GREYMANE_SAY_HELD, me->ToTempSummon()->GetSummonerGUID(), true);
                        break;
                }
            }
        };
};

class spell_gilneas_pings_crowley final : public SpellScriptLoader
{
    public:
        spell_gilneas_pings_crowley(const char* scriptName, uint8 textid)
            : SpellScriptLoader(scriptName)
            , _textid(textid)
        { }

        uint8 _textid;

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl);

        public:
            spell_script_impl(uint8 textid)
                : _textid(textid) { }

        private:
            const uint8 _textid;

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Creature* target = GetHitCreature();

                if (!(caster && target))
                    return;

                if (target->IsAIEnabled)
                    target->AI()->Talk(_textid, caster->GetGUID(), true);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl(_textid);
        }
};

// Quest Betrayal at Tempest's Reach 24592
class npc_krennan_aranas_qbatr final : public CreatureScript
{
    public:
        npc_krennan_aranas_qbatr() : CreatureScript("npc_krennan_aranas_qbatr") { }

        bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_BETRAYAL_AT_TEMPESTS_REACH)
            {
                player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
                player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_3, false);
            }

            return false;
        }
};

class npc_king_genn_greymane_qbatr final : public CreatureScript
{
    public:
        npc_king_genn_greymane_qbatr() : CreatureScript("npc_king_genn_greymane_qbatr") { }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            enum
            {
                SPELL_AI_REACTION   = 61899,
                NPC_LORD_GODFREY    = 37875,
            };

            if (quest->GetQuestId() == QUEST_BETRAYAL_AT_TEMPESTS_REACH)
            {
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_3);
                player->CastSpell(player, SPELL_AI_REACTION, false);
                player->SaveToDB();

                if (Creature* godfrey = creature->FindNearestCreature(NPC_LORD_GODFREY, 30.0f))
                    if (godfrey->IsAIEnabled)
                        godfrey->GetAI()->DoAction(ACTION_START_EVENT);
            }

            return false;
        }
};

class npc_lord_godfrey_qbatr final : public CreatureScript
{
    public:
        npc_lord_godfrey_qbatr() : CreatureScript("npc_lord_godfrey_qbatr") { }

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new npc_lord_godfrey_qbatrAI(creature);
        }

        struct npc_lord_godfrey_qbatrAI final : public ScriptedAI
        {
            npc_lord_godfrey_qbatrAI(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                NPC_KING_GENN_GREYMANE  = 37876,

                ACTION_SAY_BETTER_DIED  = 1,
                ACTION_START_RUN        = 2,
                ACTION_JUMP             = 3,

                GENN_SAY_ALL_IS_DONE    = 1,
                GODFREY_SAY_BETTER_DIED = 1,
            };

            bool isEvent;

            void Reset() final
            {
                isEvent = false;
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_EVENT:
                        {
                            if (!isEvent)
                            {
                                isEvent = true;

                                if (Creature* greymane = me->FindNearestCreature(NPC_KING_GENN_GREYMANE, 30.0f))
                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GENN_SAY_ALL_IS_DONE);

                                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_SAY_BETTER_DIED), me->m_Events.CalculateTime(4000));
                            }
                        }
                        break;
                    case ACTION_SAY_BETTER_DIED:
                        Talk(GODFREY_SAY_BETTER_DIED);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_START_RUN), me->m_Events.CalculateTime(2000));
                        break;
                    case ACTION_START_RUN:
                        me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                        me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_JUMP), me->m_Events.CalculateTime(me->GetSplineDuration()));
                        break;
                    case ACTION_JUMP:
                        {
                            static const Position godfreyJP = {-2054.75f, 893.833f, 19.1086f, 0.f};
                            me->GetMotionMaster()->MoveJump(godfreyJP, 10.f, 25.f);
                            me->DespawnOrUnsummon(me->GetSplineDuration());
                        }
                        break;
                }
            }
        };
};

class npc_gilneas_betrayer_lord final : public CreatureScript
{
    public:
        npc_gilneas_betrayer_lord(const char* scriptName, uint32 auraEntry)
            : CreatureScript(scriptName)
            , _auraEntry(auraEntry)
        { }

    private:
        uint32 _auraEntry;

        class RemoveAuraEvent final : public BasicEvent
        {
            public:
                RemoveAuraEvent(Player* owner, uint32 auraEntry)
                    : _owner(owner)
                    , _auraEntry(auraEntry)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    _owner->RemoveAura(_auraEntry);
                    _owner->SaveToDB();
                    return true;
                }

                Player* _owner;
                uint32 _auraEntry;
        };

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature, _auraEntry);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature, uint32 auraEntry)
                : ScriptedAI(creature)
                , _auraEntry(auraEntry)
            { }

            uint32 _auraEntry;

            void JustDied(Unit* killer) final
            {
                if (Player* player = killer->ToPlayer())
                    player->m_Events.AddEvent(new RemoveAuraEvent(player, _auraEntry), player->m_Events.CalculateTime(10000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_lord_hewell final : public CreatureScript
{
    public:
        npc_lord_hewell() : CreatureScript("npc_lord_hewell") { }

    private:
        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) final
        {
            enum
            {
                ACTION_SUMMON_HORSE = 1,
            };

            if (action == ACTION_SUMMON_HORSE && !player->GetVehicle())
                creature->CastSpell(player, 72773, false, NULL, NULL, player->GetGUID());

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

class npc_stout_mountain_horse final : public CreatureScript
{
    public:
        npc_stout_mountain_horse() : CreatureScript("npc_stout_mountain_horse") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_RIDE            = 1,
                EVENT_DONE_RIDE             = 2,

                SPELL_EJECT_ALL_PASSENGERS  = 50630,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                events.ScheduleEvent(EVENT_START_RIDE, 1500);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RIDE:
                            me->GetMotionMaster()->MoveSplinePath(1);
                            events.ScheduleEvent(EVENT_DONE_RIDE, me->GetSplineDuration() + 500);
                            break;
                        case EVENT_DONE_RIDE:
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                            break;
                    }
                }
            }
        };
};

// Quest Liberation Day 24575
class spell_gilneas_rescue_enslaved_villager final : public SpellScriptLoader
{
    public:
        spell_gilneas_rescue_enslaved_villager() : SpellScriptLoader("spell_gilneas_rescue_enslaved_villager") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                enum
                {
                    VILLAGER_RANDOM_SAY = 1,
                };

                PreventHitDefaultEffect(effIndex);

                if (Creature* villager = GetHitCreature())
                {
                    if (villager->IsAIEnabled)
                        villager->AI()->Talk(VILLAGER_RANDOM_SAY);

                    villager->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                    villager->ForcedDespawn(3000);
                }
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_lorna_crowley_livery_outpost final : public CreatureScript
{
    public:
        npc_lorna_crowley_livery_outpost() : CreatureScript("npc_lorna_crowley_livery_outpost") { }

    private:
        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            enum
            {
                NPC_KRENNAN_ARANAS          = 38553,
                TALK_TIME_TO_START_BATTLE   = 1,
            };

            if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_GILNEAS_CITY)
            {
                if (Creature* aranas = creature->FindNearestCreature(NPC_KRENNAN_ARANAS, 35.0f))
                    if (aranas->IsAIEnabled)
                        aranas->AI()->Talk(TALK_TIME_TO_START_BATTLE, player->GetGUID(), true);

                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_12, false);
                player->SaveToDB();
            }

            return false;
        }
};

// Quest The Battle for Gilneas City
static float const FWaveWP[168][3] =
{
    {-1414.161f, 1281.892f, 36.428f},{-1416.068f, 1289.827f, 36.428f},{-1419.030f, 1301.834f, 36.428f},
    {-1421.962f, 1313.006f, 36.428f},{-1423.899f, 1321.179f, 34.881f},{-1426.428f, 1331.009f, 34.782f},
    {-1428.520f, 1339.743f, 35.194f},{-1430.603f, 1348.241f, 35.549f},{-1433.261f, 1358.650f, 35.556f},
    {-1441.738f, 1383.216f, 35.557f},{-1444.581f, 1387.770f, 35.557f},{-1449.143f, 1392.724f, 35.557f},
    {-1454.818f, 1395.053f, 35.557f},{-1461.179f, 1395.763f, 35.557f},{-1468.874f, 1396.029f, 35.557f},
    {-1475.616f, 1396.500f, 35.557f},{-1481.679f, 1397.634f, 35.553f},{-1487.380f, 1401.618f, 35.555f},
    {-1490.443f, 1407.044f, 35.475f},{-1493.564f, 1412.456f, 35.556f},{-1497.752f, 1415.732f, 35.556f},
    {-1502.697f, 1416.977f, 35.556f},{-1507.693f, 1417.449f, 35.125f},{-1511.642f, 1418.967f, 35.412f},
    {-1514.772f, 1420.533f, 35.528f},{-1521.377f, 1423.772f, 35.557f},{-1527.589f, 1425.745f, 35.557f},
    {-1535.279f, 1425.655f, 35.557f},{-1540.217f, 1424.824f, 35.557f},{-1546.273f, 1419.186f, 35.557f},
    {-1548.270f, 1413.834f, 35.557f},{-1548.741f, 1408.287f, 35.557f},{-1548.709f, 1401.642f, 35.557f},
    {-1550.410f, 1396.847f, 35.557f},{-1552.893f, 1392.348f, 35.565f},{-1553.996f, 1387.262f, 35.581f},
    {-1555.018f, 1368.041f, 35.647f},{-1555.499f, 1349.501f, 35.557f},{-1555.079f, 1338.309f, 35.557f},
    {-1556.351f, 1330.481f, 35.557f},{-1559.022f, 1326.059f, 35.557f},{-1563.137f, 1322.432f, 35.557f},
    {-1566.329f, 1320.146f, 35.557f},{-1572.237f, 1318.418f, 35.557f},{-1574.205f, 1318.105f, 35.556f},
    {-1575.974f, 1317.116f, 35.661f},{-1575.974f, 1317.116f, 35.661f},{-1602.739f, 1313.804f, 18.743f},
    {-1607.860f, 1312.722f, 18.115f},{-1614.083f, 1311.738f, 18.775f},{-1619.699f, 1310.664f, 19.785f},
    {-1626.181f, 1309.178f, 20.337f},{-1630.814f, 1308.004f, 19.663f},{-1635.943f, 1306.074f, 19.663f},
    {-1640.631f, 1304.673f, 19.663f},{-1645.236f, 1303.961f, 19.771f},{-1650.486f, 1303.696f, 19.781f},
    {-1656.425f, 1303.762f, 19.781f},{-1659.529f, 1304.286f, 19.781f},{-1665.834f, 1306.629f, 19.781f},
    {-1671.496f, 1309.391f, 19.781f},{-1674.472f, 1310.422f, 19.782f},{-1676.782f, 1311.474f, 20.292f},
    {-1679.668f, 1311.036f, 19.782f},{-1683.217f, 1310.367f, 19.782f},{-1687.748f, 1307.883f, 19.782f},
    {-1692.132f, 1306.753f, 19.782f},{-1697.004f, 1307.064f, 19.782f},{-1702.142f, 1308.120f, 19.782f},
    {-1706.736f, 1308.941f, 19.782f},{-1713.383f, 1310.688f, 19.782f},{-1720.454f, 1312.695f, 19.782f},
    {-1726.990f, 1314.842f, 19.782f},{-1732.075f, 1316.904f, 19.782f},{-1737.065f, 1319.167f, 19.782f},
    {-1741.334f, 1321.998f, 19.857f},{-1745.785f, 1326.290f, 19.726f},{-1746.906f, 1329.927f, 19.861f},
    {-1746.595f, 1332.002f, 19.791f},{-1745.430f, 1334.015f, 19.707f},{-1742.701f, 1335.548f, 19.778f},
    {-1739.318f, 1337.117f, 19.781f},{-1736.514f, 1339.923f, 19.765f},{-1734.523f, 1343.475f, 19.765f},
    {-1733.813f, 1349.004f, 19.785f},{-1734.524f, 1354.782f, 19.765f},{-1735.867f, 1360.700f, 19.717f},
    {-1737.980f, 1365.471f, 19.951f},{-1739.909f, 1370.104f, 19.910f},{-1741.481f, 1374.611f, 19.993f},
    {-1740.914f, 1379.288f, 19.715f},{-1736.822f, 1384.873f, 19.819f},{-1733.052f, 1388.695f, 20.031f},
    {-1723.975f, 1397.091f, 21.669f},{-1714.960f, 1406.906f, 21.668f},{-1724.302f, 1396.877f, 21.669f},
    {-1729.486f, 1391.510f, 20.952f},{-1734.534f, 1386.323f, 19.798f},{-1739.533f, 1381.429f, 19.773f},
    {-1750.598f, 1374.985f, 19.941f},{-1756.823f, 1370.869f, 19.685f},{-1764.050f, 1369.123f, 19.772f},
    {-1771.198f, 1368.026f, 19.854f},{-1778.163f, 1368.110f, 19.822f},{-1784.200f, 1370.549f, 19.854f},
    {-1788.680f, 1373.906f, 19.767f},{-1793.036f, 1376.149f, 19.683f},{-1795.940f, 1379.000f, 19.806f},
    {-1796.415f, 1383.992f, 19.806f},{-1796.665f, 1387.483f, 19.879f},{-1797.694f, 1394.274f, 19.731f},
    {-1799.521f, 1399.440f, 19.800f},{-1800.752f, 1404.543f, 19.659f},{-1802.038f, 1410.351f, 19.877f},
    {-1804.932f, 1416.711f, 19.924f},{-1806.214f, 1422.153f, 19.654f},{-1806.403f, 1428.672f, 19.667f},
    {-1806.443f, 1435.090f, 19.463f},{-1806.421f, 1442.089f, 19.142f},{-1805.689f, 1448.921f, 18.990f},
    {-1805.052f, 1454.251f, 18.928f},{-1804.705f, 1459.254f, 18.831f},{-1804.565f, 1465.202f, 19.021f},
    {-1804.568f, 1471.740f, 19.316f},{-1805.130f, 1476.725f, 19.393f},{-1805.817f, 1483.099f, 19.443f},
    {-1806.897f, 1491.759f, 19.627f},{-1807.824f, 1496.331f, 19.687f},{-1807.000f, 1503.017f, 19.778f},
    {-1804.972f, 1510.196f, 19.782f},{-1802.989f, 1518.223f, 19.782f},{-1801.057f, 1524.465f, 19.782f},
    {-1800.279f, 1530.471f, 20.479f},{-1799.865f, 1534.418f, 20.479f},{-1799.201f, 1540.200f, 21.924f},
    {-1798.666f, 1545.188f, 22.482f},{-1797.992f, 1550.986f, 22.734f},{-1797.332f, 1556.899f, 22.476f},
    {-1796.790f, 1562.121f, 21.717f},{-1796.364f, 1566.768f, 20.486f},{-1795.228f, 1571.534f, 20.491f},
    {-1793.634f, 1576.893f, 20.505f},{-1790.968f, 1583.361f, 20.505f},{-1788.026f, 1589.323f, 20.505f},
    {-1785.241f, 1594.708f, 20.505f},{-1782.106f, 1600.445f, 20.487f},{-1778.071f, 1607.141f, 20.484f},
    {-1775.218f, 1611.270f, 20.484f},{-1770.276f, 1618.208f, 20.461f},{-1765.033f, 1624.617f, 20.402f},
    {-1759.929f, 1630.540f, 20.433f},{-1755.177f, 1635.831f, 20.464f},{-1750.099f, 1641.469f, 20.474f},
    {-1744.623f, 1646.713f, 20.477f},{-1739.483f, 1648.703f, 20.480f},{-1735.023f, 1649.466f, 20.491f},
    {-1728.781f, 1648.171f, 20.500f},{-1724.372f, 1646.639f, 20.486f},{-1718.441f, 1643.662f, 20.486f},
    {-1713.951f, 1640.322f, 20.486f},{-1709.559f, 1637.461f, 20.487f},{-1706.859f, 1632.484f, 20.488f},
    {-1703.550f, 1627.512f, 20.488f},{-1701.395f, 1622.216f, 20.488f},{-1700.511f, 1617.112f, 20.488f},
    {-1697.858f, 1613.420f, 20.488f},{-1692.809f, 1611.844f, 20.488f},{-1688.960f, 1611.874f, 20.488f},
};

static float const SWaveWP[173][3] =
{
    {-1414.161f, 1281.892f, 36.428f},{-1416.068f, 1289.827f, 36.428f},{-1419.030f, 1301.834f, 36.428f},
    {-1421.962f, 1313.006f, 36.428f},{-1423.899f, 1321.179f, 34.881f},{-1426.428f, 1331.009f, 34.782f},
    {-1428.520f, 1339.743f, 35.194f},{-1430.603f, 1348.241f, 35.549f},{-1433.261f, 1358.650f, 35.556f},
    {-1430.095f, 1362.781f, 35.556f},{-1426.026f, 1365.056f, 35.556f},{-1420.784f, 1367.324f, 35.556f},
    {-1415.108f, 1369.769f, 35.556f},{-1412.807f, 1370.893f, 35.556f},{-1409.770f, 1373.888f, 35.556f},
    {-1406.652f, 1378.694f, 35.556f},{-1405.368f, 1383.402f, 35.556f},{-1404.802f, 1388.732f, 35.556f},
    {-1404.576f, 1395.255f, 35.556f},{-1404.779f, 1408.554f, 35.556f},{-1404.969f, 1412.749f, 35.556f},
    {-1406.445f, 1417.153f, 35.556f},{-1408.893f, 1419.420f, 35.556f},{-1412.420f, 1420.562f, 35.556f},
    {-1417.889f, 1420.796f, 35.556f},{-1427.620f, 1419.933f, 35.556f},{-1433.591f, 1419.549f, 35.556f},
    {-1437.470f, 1418.260f, 35.556f},{-1441.682f, 1416.889f, 35.556f},{-1444.456f, 1416.566f, 35.556f},
    {-1449.731f, 1417.944f, 35.556f},{-1454.538f, 1421.029f, 35.556f},{-1459.465f, 1423.118f, 35.556f},
    {-1463.966f, 1423.736f, 35.556f},{-1471.255f, 1423.160f, 35.556f},{-1476.065f, 1421.411f, 35.556f},
    {-1481.623f, 1418.689f, 35.556f},{-1486.361f, 1415.536f, 35.556f},{-1489.485f, 1412.077f, 35.556f},
    {-1492.216f, 1408.010f, 35.556f},{-1495.620f, 1401.759f, 35.556f},{-1501.709f, 1390.232f, 35.556f},
    {-1503.493f, 1384.578f, 35.556f},{-1503.927f, 1378.542f, 35.556f},{-1502.918f, 1353.155f, 35.556f},
    {-1503.032f, 1349.545f, 35.556f},{-1504.657f, 1344.369f, 35.556f},{-1507.340f, 1341.804f, 35.556f},
    {-1511.511f, 1339.709f, 35.556f},{-1518.679f, 1336.606f, 35.556f},{-1524.455f, 1334.388f, 35.556f},
    {-1537.569f, 1329.494f, 35.556f},{-1543.017f, 1327.394f, 35.556f},{-1548.510f, 1325.418f, 35.556f},
    {-1552.752f, 1324.243f, 35.556f},{-1575.974f, 1317.116f, 35.661f},{-1575.974f, 1317.116f, 35.661f},
    {-1602.739f, 1313.804f, 18.743f},{-1607.860f, 1312.722f, 18.115f},{-1614.083f, 1311.738f, 18.775f},
    {-1619.699f, 1310.664f, 19.785f},{-1626.181f, 1309.178f, 20.337f},{-1630.845f, 1311.021f, 19.749f},
    {-1633.337f, 1313.098f, 19.734f},{-1634.618f, 1315.434f, 19.713f},{-1635.239f, 1319.894f, 19.738f},
    {-1635.311f, 1324.905f, 19.857f},{-1635.387f, 1331.443f, 19.884f},{-1635.437f, 1335.737f, 19.848f},
    {-1638.660f, 1337.092f, 19.673f},{-1642.441f, 1337.759f, 19.853f},{-1645.818f, 1337.918f, 18.262f},
    {-1651.646f, 1337.726f, 15.146f},{-1655.955f, 1337.792f, 15.135f},{-1661.412f, 1338.355f, 15.135f},
    {-1667.882f, 1339.249f, 15.135f},{-1673.916f, 1339.888f, 15.135f},{-1678.713f, 1340.878f, 15.135f},
    {-1683.695f, 1342.105f, 15.114f},{-1689.998f, 1343.816f, 15.136f},{-1694.509f, 1345.000f, 15.405f},
    {-1698.006f, 1345.906f, 16.915f},{-1703.989f, 1347.458f, 19.495f},{-1708.500f, 1348.660f, 19.782f},
    {-1714.471f, 1350.664f, 19.776f},{-1719.061f, 1352.397f, 19.781f},{-1722.292f, 1354.002f, 19.808f},
    {-1727.602f, 1357.163f, 19.788f},{-1731.502f, 1359.926f, 19.797f},{-1734.196f, 1362.160f, 19.955f},
    {-1736.495f, 1364.644f, 20.019f},{-1739.200f, 1368.984f, 19.923f},{-1741.501f, 1374.218f, 19.988f},
    {-1740.914f, 1379.288f, 19.715f},{-1736.822f, 1384.873f, 19.819f},{-1733.052f, 1388.695f, 20.031f},
    {-1723.975f, 1397.091f, 21.669f},{-1719.407f, 1396.617f, 21.669f},{-1715.248f, 1394.803f, 21.669f},
    {-1710.467f, 1393.734f, 21.669f},{-1707.344f, 1393.382f, 21.669f},{-1702.519f, 1394.064f, 21.669f},
    {-1697.369f, 1397.636f, 21.669f},{-1724.302f, 1396.877f, 21.669f},{-1729.486f, 1391.510f, 20.952f},
    {-1734.534f, 1386.323f, 19.798f},{-1739.533f, 1381.429f, 19.773f},{-1750.598f, 1374.985f, 19.941f},
    {-1756.823f, 1370.869f, 19.685f},{-1764.050f, 1369.123f, 19.772f},{-1771.198f, 1368.026f, 19.854f},
    {-1778.163f, 1368.110f, 19.822f},{-1784.200f, 1370.549f, 19.854f},{-1788.680f, 1373.906f, 19.767f},
    {-1793.036f, 1376.149f, 19.683f},{-1795.940f, 1379.000f, 19.806f},{-1796.415f, 1383.992f, 19.806f},
    {-1796.665f, 1387.483f, 19.879f},{-1797.694f, 1394.274f, 19.731f},{-1799.521f, 1399.440f, 19.800f},
    {-1800.752f, 1404.543f, 19.659f},{-1802.038f, 1410.351f, 19.877f},{-1804.932f, 1416.711f, 19.924f},
    {-1806.214f, 1422.153f, 19.654f},{-1806.403f, 1428.672f, 19.667f},{-1806.443f, 1435.090f, 19.463f},
    {-1806.421f, 1442.089f, 19.142f},{-1805.689f, 1448.921f, 18.990f},{-1805.052f, 1454.251f, 18.928f},
    {-1804.705f, 1459.254f, 18.831f},{-1804.565f, 1465.202f, 19.021f},{-1804.568f, 1471.740f, 19.316f},
    {-1805.130f, 1476.725f, 19.393f},{-1805.817f, 1483.099f, 19.443f},{-1806.897f, 1491.759f, 19.627f},
    {-1807.824f, 1496.331f, 19.687f},{-1807.000f, 1503.017f, 19.778f},{-1804.972f, 1510.196f, 19.782f},
    {-1802.989f, 1518.223f, 19.782f},{-1801.057f, 1524.465f, 19.782f},{-1800.279f, 1530.471f, 20.479f},
    {-1799.865f, 1534.418f, 20.479f},{-1799.201f, 1540.200f, 21.924f},{-1798.666f, 1545.188f, 22.482f},
    {-1797.992f, 1550.986f, 22.734f},{-1797.332f, 1556.899f, 22.476f},{-1796.790f, 1562.121f, 21.717f},
    {-1796.364f, 1566.768f, 20.486f},{-1795.228f, 1571.534f, 20.491f},{-1793.634f, 1576.893f, 20.505f},
    {-1790.968f, 1583.361f, 20.505f},{-1788.026f, 1589.323f, 20.505f},{-1785.241f, 1594.708f, 20.505f},
    {-1782.106f, 1600.445f, 20.487f},{-1778.071f, 1607.141f, 20.484f},{-1775.218f, 1611.270f, 20.484f},
    {-1770.276f, 1618.208f, 20.461f},{-1765.033f, 1624.617f, 20.402f},{-1759.929f, 1630.540f, 20.433f},
    {-1755.177f, 1635.831f, 20.464f},{-1750.099f, 1641.469f, 20.474f},{-1744.623f, 1646.713f, 20.477f},
    {-1739.483f, 1648.703f, 20.480f},{-1735.023f, 1649.466f, 20.491f},{-1728.781f, 1648.171f, 20.500f},
    {-1724.372f, 1646.639f, 20.486f},{-1718.441f, 1643.662f, 20.486f},{-1713.951f, 1640.322f, 20.486f},
    {-1709.559f, 1637.461f, 20.487f},{-1700.422f, 1634.361f, 20.490f},{-1696.002f, 1634.187f, 20.490f},
    {-1688.187f, 1634.420f, 20.490f},{-1682.491f, 1634.150f, 20.493f}
};

static float const TWaveWP[160][3] =
{
    {-1414.161f, 1281.892f, 36.428f},{-1416.068f, 1289.827f, 36.428f},{-1419.030f, 1301.834f, 36.428f},
    {-1421.962f, 1313.006f, 36.428f},{-1423.899f, 1321.179f, 34.881f},{-1426.428f, 1331.009f, 34.782f},
    {-1428.520f, 1339.743f, 35.194f},{-1430.603f, 1348.241f, 35.549f},{-1433.261f, 1358.650f, 35.556f},
    {-1438.465f, 1359.941f, 35.556f},{-1443.781f, 1360.492f, 35.556f},{-1448.416f, 1359.362f, 35.556f},
    {-1454.637f, 1357.020f, 35.556f},{-1461.389f, 1353.844f, 35.556f},{-1467.185f, 1351.380f, 35.556f},
    {-1473.962f, 1348.859f, 35.556f},{-1483.950f, 1345.621f, 35.556f},{-1491.751f, 1343.219f, 35.556f},
    {-1502.187f, 1340.255f, 35.556f},{-1513.418f, 1337.115f, 35.556f},{-1521.502f, 1334.432f, 35.556f},
    {-1531.487f, 1331.183f, 35.556f},{-1539.221f, 1328.533f, 35.556f},{-1547.092f, 1325.599f, 35.556f},
    {-1562.069f, 1321.145f, 35.556f},{-1575.974f, 1317.116f, 35.661f},{-1575.974f, 1317.116f, 35.661f},
    {-1602.739f, 1313.804f, 18.743f},{-1607.860f, 1312.722f, 18.115f},{-1614.083f, 1311.738f, 18.775f},
    {-1619.699f, 1310.664f, 19.785f},{-1626.181f, 1309.178f, 20.337f},{-1630.845f, 1311.021f, 19.749f},
    {-1633.337f, 1313.098f, 19.734f},{-1634.618f, 1315.434f, 19.713f},{-1635.239f, 1319.894f, 19.738f},
    {-1635.311f, 1324.905f, 19.857f},{-1635.387f, 1331.443f, 19.884f},{-1635.437f, 1335.737f, 19.848f},
    {-1634.936f, 1344.817f, 19.935f},{-1634.620f, 1350.402f, 19.919f},{-1634.372f, 1353.893f, 20.018f},
    {-1634.069f, 1358.433f, 20.033f},{-1633.786f, 1366.589f, 20.080f},{-1633.714f, 1371.138f, 19.990f},
    {-1633.601f, 1378.256f, 19.900f},{-1633.291f, 1384.150f, 20.018f},{-1634.149f, 1389.434f, 20.087f},
    {-1636.380f, 1394.077f, 20.006f},{-1639.688f, 1395.110f, 19.804f},{-1643.855f, 1394.779f, 19.675f},
    {-1646.959f, 1393.784f, 19.664f},{-1650.151f, 1392.084f, 19.772f},{-1657.146f, 1386.837f, 15.573f},
    {-1660.771f, 1381.076f, 15.135f},{-1662.798f, 1377.942f, 15.135f},{-1667.154f, 1372.462f, 15.155f},
    {-1671.145f, 1367.900f, 15.155f},{-1674.727f, 1363.901f, 15.135f},{-1678.151f, 1360.079f, 15.135f},
    {-1680.608f, 1357.422f, 15.135f},{-1683.673f, 1353.760f, 15.135f},{-1685.726f, 1350.648f, 15.135f},
    {-1686.963f, 1349.579f, 15.124f},{-1692.713f, 1346.806f, 15.134f},{-1696.026f, 1346.156f, 16.127f},
    {-1699.401f, 1346.282f, 17.518f},{-1704.848f, 1346.894f, 19.797f},{-1711.416f, 1348.497f, 19.768f},
    {-1717.155f, 1350.745f, 19.770f},{-1721.406f, 1353.174f, 19.781f},{-1724.301f, 1355.142f, 19.841f},
    {-1728.420f, 1358.009f, 19.787f},{-1732.119f, 1361.021f, 19.881f},{-1735.017f, 1364.518f, 20.037f},
    {-1738.111f, 1369.042f, 19.907f},{-1740.360f, 1372.446f, 19.910f},{-1741.615f, 1374.687f, 20.001f},
    {-1740.914f, 1379.288f, 19.715f},{-1736.822f, 1384.873f, 19.819f},{-1733.052f, 1388.695f, 20.031f},
    {-1723.975f, 1397.091f, 21.669f},{-1725.685f, 1402.780f, 21.668f},{-1727.408f, 1406.733f, 21.668f},
    {-1728.348f, 1411.525f, 21.668f},{-1728.553f, 1415.348f, 21.668f},{-1727.485f, 1418.545f, 21.668f},
    {-1724.977f, 1422.812f, 21.668f},{-1724.302f, 1396.877f, 21.669f},{-1729.486f, 1391.510f, 20.952f},
    {-1734.534f, 1386.323f, 19.798f},{-1739.533f, 1381.429f, 19.773f},{-1750.598f, 1374.985f, 19.941f},
    {-1756.823f, 1370.869f, 19.685f},{-1764.050f, 1369.123f, 19.772f},{-1771.198f, 1368.026f, 19.854f},
    {-1778.163f, 1368.110f, 19.822f},{-1784.200f, 1370.549f, 19.854f},{-1788.680f, 1373.906f, 19.767f},
    {-1793.036f, 1376.149f, 19.683f},{-1795.940f, 1379.000f, 19.806f},{-1796.415f, 1383.992f, 19.806f},
    {-1796.665f, 1387.483f, 19.879f},{-1797.694f, 1394.274f, 19.731f},{-1799.521f, 1399.440f, 19.800f},
    {-1800.752f, 1404.543f, 19.659f},{-1802.038f, 1410.351f, 19.877f},{-1804.932f, 1416.711f, 19.924f},
    {-1806.214f, 1422.153f, 19.654f},{-1806.403f, 1428.672f, 19.667f},{-1806.443f, 1435.090f, 19.463f},
    {-1806.421f, 1442.089f, 19.142f},{-1805.689f, 1448.921f, 18.990f},{-1805.052f, 1454.251f, 18.928f},
    {-1804.705f, 1459.254f, 18.831f},{-1804.565f, 1465.202f, 19.021f},{-1804.568f, 1471.740f, 19.316f},
    {-1805.130f, 1476.725f, 19.393f},{-1805.817f, 1483.099f, 19.443f},{-1806.897f, 1491.759f, 19.627f},
    {-1807.824f, 1496.331f, 19.687f},{-1807.000f, 1503.017f, 19.778f},{-1804.972f, 1510.196f, 19.782f},
    {-1802.989f, 1518.223f, 19.782f},{-1801.057f, 1524.465f, 19.782f},{-1800.279f, 1530.471f, 20.479f},
    {-1799.865f, 1534.418f, 20.479f},{-1799.201f, 1540.200f, 21.924f},{-1798.666f, 1545.188f, 22.482f},
    {-1797.992f, 1550.986f, 22.734f},{-1797.332f, 1556.899f, 22.476f},{-1796.790f, 1562.121f, 21.717f},
    {-1796.364f, 1566.768f, 20.486f},{-1795.228f, 1571.534f, 20.491f},{-1793.634f, 1576.893f, 20.505f},
    {-1790.968f, 1583.361f, 20.505f},{-1788.026f, 1589.323f, 20.505f},{-1785.241f, 1594.708f, 20.505f},
    {-1782.106f, 1600.445f, 20.487f},{-1778.071f, 1607.141f, 20.484f},{-1775.218f, 1611.270f, 20.484f},
    {-1770.276f, 1618.208f, 20.461f},{-1765.033f, 1624.617f, 20.402f},{-1759.929f, 1630.540f, 20.433f},
    {-1755.177f, 1635.831f, 20.464f},{-1750.099f, 1641.469f, 20.474f},{-1744.623f, 1646.713f, 20.477f},
    {-1739.483f, 1648.703f, 20.480f},{-1735.023f, 1649.466f, 20.491f},{-1728.781f, 1648.171f, 20.500f},
    {-1724.372f, 1646.639f, 20.486f},{-1718.441f, 1643.662f, 20.486f},{-1713.951f, 1640.322f, 20.486f},
    {-1709.559f, 1637.461f, 20.487f},{-1706.420f, 1632.687f, 20.490f},{-1704.464f, 1628.319f, 20.490f},
    {-1702.990f, 1623.903f, 20.490f},{-1702.554f, 1621.728f, 20.490f},{-1701.229f, 1614.269f, 20.487f},
    {-1699.046f, 1610.021f, 20.487f},
};

static float const LornaWP[78][3] =
{
    {-1551.90f,1284.75f,13.992f}, {-1561.35f,1282.32f,21.372f}, {-1581.19f,1277.05f,35.878f},
    {-1587.59f,1275.81f,35.880f}, {-1591.07f,1284.64f,35.878f}, {-1591.32f,1291.64f,35.981f},
    {-1579.00f,1296.02f,35.879f}, {-1569.90f,1303.33f,35.879f}, {-1568.92f,1315.40f,35.556f},
    {-1565.98f,1319.25f,35.556f}, {-1572.58f,1318.18f,35.556f}, {-1574.10f,1317.31f,35.556f},
    {-1581.09f,1316.72f,32.437f}, {-1589.80f,1315.95f,26.871f}, {-1601.94f,1314.38f,19.213f},
    {-1612.36f,1313.10f,18.449f}, {-1626.31f,1309.77f,20.337f}, {-1634.95f,1306.97f,19.663f},
    {-1645.84f,1304.63f,19.769f}, {-1657.72f,1304.68f,19.782f}, {-1666.91f,1306.79f,19.782f},
    {-1673.02f,1309.37f,19.782f}, {-1682.11f,1309.02f,19.782f}, {-1692.83f,1307.45f,19.782f},
    {-1702.07f,1308.50f,19.782f}, {-1710.78f,1310.87f,19.782f}, {-1720.07f,1313.75f,19.782f},
    {-1729.48f,1316.44f,19.782f}, {-1738.53f,1319.14f,19.782f}, {-1744.64f,1325.33f,19.791f},
    {-1743.33f,1332.14f,19.760f}, {-1739.08f,1339.84f,19.790f}, {-1735.41f,1346.33f,19.882f},
    {-1737.87f,1355.13f,19.783f}, {-1742.57f,1366.28f,19.736f}, {-1742.55f,1378.77f,19.763f},
    {-1738.08f,1383.00f,19.823f}, {-1731.88f,1389.21f,20.290f}, {-1725.81f,1395.97f,21.668f},
    {-1731.88f,1389.21f,20.290f}, {-1725.81f,1395.97f,21.668f}, {-1708.44f,1393.12f,21.668f},
    {-1725.65f,1396.38f,21.668f}, {-1731.76f,1389.38f,20.334f}, {-1739.26f,1381.20f,19.917f},
    {-1748.73f,1378.62f,19.857f}, {-1755.88f,1386.24f,19.892f}, {-1762.23f,1389.28f,19.899f},
    {-1771.95f,1385.38f,19.632f}, {-1783.07f,1381.10f,19.656f}, {-1789.69f,1378.86f,19.793f},
    {-1793.91f,1388.03f,19.870f}, {-1797.87f,1396.60f,19.902f}, {-1802.12f,1406.22f,19.838f},
    {-1803.79f,1416.60f,19.954f}, {-1803.84f,1428.15f,19.762f}, {-1803.67f,1436.52f,19.528f},
    {-1803.33f,1450.17f,18.978f}, {-1804.19f,1463.43f,18.945f}, {-1805.42f,1475.28f,19.364f},
    {-1804.10f,1489.54f,19.608f}, {-1802.48f,1506.96f,19.780f}, {-1801.51f,1517.42f,19.780f},
    {-1800.07f,1533.10f,20.370f}, {-1798.80f,1546.33f,22.601f}, {-1796.41f,1566.48f,20.604f},
    {-1791.83f,1578.21f,20.504f}, {-1785.51f,1590.68f,20.504f}, {-1778.93f,1601.81f,20.494f},
    {-1770.99f,1613.75f,20.480f}, {-1763.55f,1624.02f,20.454f}, {-1756.86f,1632.89f,20.457f},
    {-1749.70f,1642.31f,20.474f}, {-1741.83f,1650.73f,20.476f}, {-1729.43f,1649.46f,20.500f},
    {-1718.56f,1643.08f,20.485f}, {-1709.44f,1635.46f,20.486f}, {-1703.89f,1621.66f,20.488f},
};

static float const FWorgenWP[90][3] =
{
    {-1782.323f, 1330.417f, 19.986f},{-1777.212f, 1335.359f, 19.928f},{-1772.587f, 1340.136f, 19.866f},
    {-1768.117f, 1344.888f, 19.770f},{-1763.055f, 1349.358f, 19.410f},{-1756.953f, 1354.040f, 19.658f},
    {-1752.293f, 1357.719f, 19.868f},{-1748.332f, 1363.519f, 19.818f},{-1745.613f, 1369.708f, 19.952f},
    {-1743.513f, 1374.389f, 19.945f},{-1740.170f, 1380.246f, 19.748f},{-1736.963f, 1384.398f, 19.831f},
    {-1733.255f, 1388.425f, 19.960f},{-1723.975f, 1397.091f, 21.669f},{-1718.432f, 1403.235f, 21.668f},
    {-1713.175f, 1408.852f, 21.668f},{-1709.073f, 1413.494f, 21.669f},{-1704.466f, 1418.279f, 21.669f},
    {-1701.909f, 1420.877f, 21.669f},{-1724.302f, 1396.877f, 21.669f},{-1729.486f, 1391.510f, 20.952f},
    {-1734.534f, 1386.323f, 19.798f},{-1739.533f, 1381.429f, 19.773f},{-1750.598f, 1374.985f, 19.941f},
    {-1756.823f, 1370.869f, 19.685f},{-1764.050f, 1369.123f, 19.772f},{-1771.198f, 1368.026f, 19.854f},
    {-1778.163f, 1368.110f, 19.822f},{-1784.200f, 1370.549f, 19.854f},{-1788.680f, 1373.906f, 19.767f},
    {-1793.036f, 1376.149f, 19.683f},{-1795.940f, 1379.000f, 19.806f},{-1796.415f, 1383.992f, 19.806f},
    {-1796.665f, 1387.483f, 19.879f},{-1797.694f, 1394.274f, 19.731f},{-1799.521f, 1399.440f, 19.800f},
    {-1800.752f, 1404.543f, 19.659f},{-1802.038f, 1410.351f, 19.877f},{-1804.932f, 1416.711f, 19.924f},
    {-1806.214f, 1422.153f, 19.654f},{-1806.403f, 1428.672f, 19.667f},{-1806.443f, 1435.090f, 19.463f},
    {-1806.421f, 1442.089f, 19.142f},{-1805.689f, 1448.921f, 18.990f},{-1805.052f, 1454.251f, 18.928f},
    {-1804.705f, 1459.254f, 18.831f},{-1804.565f, 1465.202f, 19.021f},{-1804.568f, 1471.740f, 19.316f},
    {-1805.130f, 1476.725f, 19.393f},{-1805.817f, 1483.099f, 19.443f},{-1806.897f, 1491.759f, 19.627f},
    {-1807.824f, 1496.331f, 19.687f},{-1807.000f, 1503.017f, 19.778f},{-1804.972f, 1510.196f, 19.782f},
    {-1802.989f, 1518.223f, 19.782f},{-1801.057f, 1524.465f, 19.782f},{-1800.279f, 1530.471f, 20.479f},
    {-1799.865f, 1534.418f, 20.479f},{-1799.201f, 1540.200f, 21.924f},{-1798.666f, 1545.188f, 22.482f},
    {-1797.992f, 1550.986f, 22.734f},{-1797.332f, 1556.899f, 22.476f},{-1796.790f, 1562.121f, 21.717f},
    {-1796.364f, 1566.768f, 20.486f},{-1795.228f, 1571.534f, 20.491f},{-1793.634f, 1576.893f, 20.505f},
    {-1790.968f, 1583.361f, 20.505f},{-1788.026f, 1589.323f, 20.505f},{-1785.241f, 1594.708f, 20.505f},
    {-1782.106f, 1600.445f, 20.487f},{-1778.071f, 1607.141f, 20.484f},{-1775.218f, 1611.270f, 20.484f},
    {-1770.276f, 1618.208f, 20.461f},{-1765.033f, 1624.617f, 20.402f},{-1759.929f, 1630.540f, 20.433f},
    {-1755.177f, 1635.831f, 20.464f},{-1750.099f, 1641.469f, 20.474f},{-1744.623f, 1646.713f, 20.477f},
    {-1739.483f, 1648.703f, 20.480f},{-1735.023f, 1649.466f, 20.491f},{-1728.781f, 1648.171f, 20.500f},
    {-1724.372f, 1646.639f, 20.486f},{-1718.441f, 1643.662f, 20.486f},{-1713.951f, 1640.322f, 20.486f},
    {-1709.559f, 1637.461f, 20.487f},{-1700.548f, 1630.398f, 20.488f},{-1695.960f, 1627.846f, 20.488f},
    {-1690.876f, 1625.229f, 20.488f},{-1687.808f, 1622.724f, 20.488f},{-1683.897f, 1618.888f, 20.488f},
};

static float const GreymaneWP[16][3] =
{
    {-1763.038f, 1680.547f, 22.158f},{-1756.171f, 1674.759f, 22.158f},{-1750.765f, 1670.313f, 22.158f},
    {-1743.187f, 1664.099f, 20.481f},{-1734.999f, 1657.525f, 20.479f},{-1728.514f, 1652.187f, 20.500f},
    {-1721.872f, 1646.491f, 20.485f},{-1718.441f, 1643.662f, 20.486f},{-1713.951f, 1640.322f, 20.486f},
    {-1709.559f, 1637.461f, 20.487f},{-1703.985f, 1635.109f, 20.488f},{-1697.577f, 1633.860f, 20.488f},
    {-1694.136f, 1633.221f, 20.488f},{-1686.660f, 1631.111f, 20.488f},{-1683.073f, 1628.163f, 20.488f},
    {-1681.002f, 1623.270f, 20.488f},
};

const Position RangerSP[2]=
{
    {-1576.904f, 1316.06f, 35.138f, 0.f},
    {-1577.336f, 1320.35f, 35.114f, 0.f},
};

const Position CannonSP[3]=
{
    {-1543.822f, 1290.354f, 7.252f, 3.12f},
    {-1539.169f, 1288.024f, 4.381f, 3.12f},
    {-1534.256f, 1285.484f, 1.539f, 3.12f},
};

struct Militia final
{
    uint64 guid;
    float dist;
    float angle;
};

enum
{
    ACTION_GOREROT_FIGHT        = 8,
    ACTION_GOREROT_DIED         = 9,
    ACTION_BATTLE_COMPLETE      = 12,
    ACTION_LEADER_ON_POSITION   = 14,

    SPELL_BANSHEE_QUEENS_WAIL   = 72113,

    TYPE_DESPAWN_EVENT          = 1,
};

class npc_krennan_aranas_tbfgc final : public CreatureScript
{
    public:
        npc_krennan_aranas_tbfgc() : CreatureScript("npc_krennan_aranas_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        enum
        {
            NPC_PRINCE_LIAM_GREYMANE    = 38218,

            MENU_START_BATTLE           = 15377,

            TYPE_PLAYER_GUID            = 1,
        };

        bool OnGossipHello(Player* player, Creature* creature) final
        {
            if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
            {
                if (creature_script_impl* aranasAI = dynamic_cast<creature_script_impl*>(creature->GetAI()))
                {
                    if (!aranasAI->IsBattle())
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Start the Battle for Gilneas City!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    else
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want join to the Battle for Gilneas City!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                }

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Skip the Battle for Gilneas City!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }

            player->SEND_GOSSIP_MENU(MENU_START_BATTLE, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) final
        {
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();

            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    {
                        if (creature->IsAIEnabled)
                            creature->GetAI()->DoAction(ACTION_START_EVENT);
                    }
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
                    {
                        if (creature->IsAIEnabled)
                            creature->GetAI()->SetGUID(player->GetGUID(), TYPE_PLAYER_GUID);
                    }
                    break;
                case GOSSIP_ACTION_INFO_DEF + 3:
                    player->CompleteQuest(QUEST_THE_BATTLE_FOR_GILNEAS_CITY);
                    player->TeleportTo(654, -1663.051f, 1591.278f, 23.128f, 3.99f);
                    player->SaveToDB();
                    break;
            }

            return true;
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            uint64 liamGUID;
            bool battle;

            void InitializeAI() final
            {
                InitBattle();
                me->setActive(true);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_EVENT:
                        StartBattle();
                        break;
                    case ACTION_BATTLE_COMPLETE:
                        InitBattle();
                        break;
                }
            }

            bool IsBattle() const
            {
                return battle;
            }

            void InitBattle()
            {
                battle = false;
                liamGUID = 0;

                if (Creature* liam = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE, -1412.34f, 1274.66f, 36.4277f, 1.801f))
                    liamGUID = liam->GetGUID();
            }

            void StartBattle()
            {
                battle = true;

                if (Creature* liam = ObjectAccessor::GetCreature(*me, liamGUID))
                    if (liam->IsAIEnabled)
                        liam->GetAI()->DoAction(ACTION_START_EVENT);
            }

            void SetGUID(uint64 guid, int32 type) final
            {
                if (type == TYPE_PLAYER_GUID)
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
                    {
                        if (Creature* liam = ObjectAccessor::GetCreature(*me, liamGUID))
                        {
                            float x, y, z, o;
                            liam->GetPosition(x, y, z, o);
                            player->TeleportTo(liam->GetMapId(), x, y, z, o);
                        }
                    }
                }
            }
        };
};

struct BattleForGilneasLeaderAI : public SmoothEscortAI
{
    BattleForGilneasLeaderAI(Creature* creature)
        : SmoothEscortAI(creature)
        , isFinish(false)
    { }

    std::list<Militia> militias;
    bool isFinish;

    void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
        {
            isFinish = true;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->DeleteThreatList();
            me->CombatStop(true);
        }
    }

    void AddMilitia(uint64 guid, float dist, float angle)
    {
        Militia militia;
        militia.guid = guid;
        militia.dist = dist;
        militia.angle = angle;
        militias.push_back(militia);
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == TYPE_DESPAWN_EVENT)
        {
            for (std::list<Militia>::const_iterator itr = militias.begin(); itr != militias.end(); ++itr)
                if (Creature* militia = ObjectAccessor::GetCreature(*me, itr->guid))
                    militia->DespawnOrUnsummon(data);

            me->DespawnOrUnsummon(data);
        }
    }

    void StartMoveTo(float x, float y, float z) override
    {
        float pathangle = atan2(me->GetPositionY() - y, me->GetPositionX() - x);
        bool smooth = std::abs(me->GetPositionZ() - z) > 5.f;

        for (std::list<Militia>::const_iterator itr = militias.begin(); itr != militias.end(); ++itr)
        {
            if (Creature* militia = ObjectAccessor::GetCreature(*me, itr->guid))
            {
                if (!militia->IsAlive() || militia->GetVictim())
                    continue;

                float angle = itr->angle;
                float dist = itr->dist;

                float _x = x + std::cos(angle + pathangle) * dist;
                float _y = y + std::sin(angle + pathangle) * dist;
                float _z = z;

                Trinity::NormalizeMapCoord(_x);
                Trinity::NormalizeMapCoord(_y);

                militia->UpdateGroundPositionZ(_x, _y, _z);

                // member current position
                Movement::Location real_position(militia->GetPositionX(), militia->GetPositionY(), militia->GetPositionZMinusOffset(), militia->GetOrientation());

                // current position may differ if member is moving
                if (!militia->movespline->Finalized())
                    real_position = militia->movespline->ComputePosition();

                //float _dist = member->GetExactDist(dx, dy, dz);
                float dx = real_position.x - _x;
                float dy = real_position.y - _y;
                float dz = real_position.z - _z;

                float _dist = sqrt(dx * dx + dy * dy + dz * dz);
                float _time = me->GetSplineDuration();
                float speed = _dist / _time * IN_MILLISECONDS;

                if (speed > 2.f)
                {
                    if (speed > 10.f)
                        speed = 10.f;

                    Movement::MoveSplineInit init(militia);
                    init.SetVelocity(speed);

                    if (smooth)
                        militia->GetMotionMaster()->MovePointSmooth(_x, _y, 2.5f, false, &init);
                    else
                    {
                        init.MoveTo(_x, _y, _z);
                        init.Launch();
                    }
                }

                militia->SetHomePosition(_x, _y, _z, M_PI + pathangle);
            }
        }
    }

    void SummonMilitia(Unit* leader, uint32 entry, uint8 startIndex, uint8 finishIndex)
    {
        for (uint8 i = startIndex; i <= finishIndex; ++i)
        {
            float x, y;
            leader->GetNearPoint2D(x, y, i * 3, leader->GetOrientation() + M_PI, false);

            if (Creature* militia = me->SummonCreature(entry, x, y, leader->GetPositionZ(), leader->GetOrientation()))
            {
                uint8 militiaOffset = i - startIndex + 1;

                AddMilitia(militia->GetGUID(), militiaOffset * 2 + 2, 0.f);

                for (int j = 0; j < 2; ++j)
                {
                    militia->GetNearPoint2D(x, y, 3 * (j + 1), militia->GetOrientation() + M_PI / 2, false);

                    if (Creature* militia = me->SummonCreature(entry, x, y, leader->GetPositionZ(), leader->GetOrientation()))
                        AddMilitia(militia->GetGUID(), militiaOffset * 2 + 2, -M_PI / (2 * militiaOffset - j * 5 -((-1 + j) * militiaOffset) + 7));

                    militia->GetNearPoint2D(x, y, 3 * (j + 1), militia->GetOrientation() - M_PI / 2, false);

                    if (Creature* militia = me->SummonCreature(entry, x, y, leader->GetPositionZ(), leader->GetOrientation()))
                        AddMilitia(militia->GetGUID(), militiaOffset * 2 + 2, M_PI / (2 * militiaOffset - j * 5 -((-1 + j) * militiaOffset) + 7));
                }
            }
        }
    }

    void AttackStart(Unit* who) override
    {
        SmoothEscortAI::AttackStart(who);

        for (std::list<Militia>::const_iterator itr = militias.begin(); itr != militias.end(); ++itr)
        {
            if (Creature* militia = ObjectAccessor::GetCreature(*me, itr->guid))
            {
                if (!militia->IsAlive())
                    continue;

                if (militia->GetVictim())
                {
                    militia->CombatStart(who);
                    militia->AddThreat(who, 0.0f);
                }
                else
                {
                    bool melee = me->IsWithinMeleeRange(who);
                    militia->Attack(who, melee);
                }
            }
        }
    }

    void EnterEvadeMode() override
    {
        if (!isFinish)
        {
            for (std::list<Militia>::const_iterator itr = militias.begin(); itr != militias.end(); ++itr)
            {
                if (Creature* militia = ObjectAccessor::GetCreature(*me, itr->guid))
                {
                    if (!militia->IsAlive() || !militia->IsAIEnabled)
                        continue;

                    if (Unit* victim = militia->GetVictim())
                    {
                        AttackStart(victim);
                        return;
                    }
                }
            }

            SmoothEscortAI::EnterEvadeMode();
        }
    }
};

class npc_prince_liam_greymane_tbfgc final : public CreatureScript
{
    public:
        npc_prince_liam_greymane_tbfgc() : CreatureScript("npc_prince_liam_greymane_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public BattleForGilneasLeaderAI
        {
            creature_script_impl(Creature* creature)
                : BattleForGilneasLeaderAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 100.f)
                , sylvanasGUID(0)
                , battleState(0)
                , battlePhase(PHASE_NONE)
                , isBattle(false)
                , leaderGUID()
            { }

            enum
            {
                EVENT_LIAM_BATTLE_SPEACH        = 1,
                EVENT_START_BATTLE              = 7,
                EVENT_TALK_MILITARY_DISTRICT    = 8,
                EVENT_ATTACK_MILITARY_DISTRICT  = 9,
                EVENT_LIAM_TALK_LORNA           = 10,
                EVENT_CROWLEY_TALK_GOREROT      = 11,
                EVENT_CROWLEY_TALK_GOREROT_DIED = 12,
                EVENT_SYLVANAS_KILL_LIAM_1      = 13,
                EVENT_SYLVANAS_KILL_LIAM_2      = 14,
                EVENT_SYLVANAS_KILL_LIAM_3      = 15,
                EVENT_SYLVANAS_KILL_LIAM_4      = 16,
                EVENT_SYLVANAS_KILL_LIAM_5      = 17,
                EVENT_SYLVANAS_KILL_LIAM_6      = 18,

                EVENT_LIAM_BATTLE_YELL          = 1,
                EVENT_MULTI_SHOT                = 2,
                EVENT_CHALLENGING_SHOUT         = 3,

                LIAM_TALK_BATTLE_SPEACH         = 1,
                LIAM_TALK_BATTLE_FOR_GILNEAS    = 7,
                LIAM_TALK_MILITARY_DISTRICT     = 8,
                LIAM_TALK_LORNA                 = 9,
                LIAM_TALK_CROWLEY               = 10,
                LIAM_TALK_BATTLE                = 11,
                LIAM_YELL_FATHER                = 12,
                LIAM_TALK_FINISH_1              = 13,
                LIAM_TALK_FINISH_2              = 14,
                CROWLEY_TALK_GOREROT            = 1,
                CROWLEY_TALK_GOREROT_DIED       = 2,
                SYLVANAS_YELL_KILL_LIAM         = 2,
                GREYMANE_YELL_LIAM              = 2,

                ACTION_DESPAWN                  = 20,

                TYPE_MYRIAM                     = 0,
                TYPE_ALMYRA                     = 1,
                TYPE_LORNA                      = 2,
                TYPE_CROWLEY                    = 3,
                TYPE_GREYMANE                   = 4,

                PHASE_NONE                      = 0,
                PHASE_INTRO                     = 1,
                PHASE_MERCHANT_SQUARE           = 2,
                PHASE_MILITARY_DISTRICT         = 3,
                PHASE_GREYMANE_COURT            = 4,

                SPELL_SHOOT                     = 22121,
                SPELL_CHALLENGING_SHOUT         = 1161,
                SPELL_MULTI_SHOT                = 31942,
                SPELL_GREYMANE_JUMP             = 72107,
                SPELL_SHOOT_LIAM                = 72116,
                SPELL_BFGC_COMPLETE             = 72349,

                NPC_LORD_DARIUS_CROWLEY         = 38415,
                NPC_GOREROT                     = 38331,
                NPC_SISTER_ALMYRA               = 38466,
                NPC_LORNA_CROWLEY               = 38426,
                NPC_GILNEAN_MILITIA             = 38221,
                NPC_KING_GENN_GREYMANE          = 38470,
                NPC_LADY_SYLVANAS_WINDRUNNER    = 38469,
                NPC_MYRIAM_SPELLWAKER           = 38465,
                NPC_EMBERSTONE_CANNON           = 38424,
            };

            ShooterGuardAI shooterAI;
            EventMap commonEvents;
            EventMap events;
            std::array<uint64, 5> leaderGUID;
            uint64 sylvanasGUID;
            uint8 battleState;
            uint8 battlePhase;
            bool isBattle;

            void InitializeAI() final
            {
                Reset();
                SummonEventCreatures();
                SetCombatMovement(false);
                me->SetPhaseMask(262144, true);
                me->m_ReactDistance = 40.f;
                me->setActive(true);
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell) final
            {
                BattleForGilneasLeaderAI::SpellHit(caster, spell);

                if (spell->Id == SPELL_SHOOT_LIAM)
                {
                    me->SetHealth(1);
                    me->SetStandState(UNIT_STAND_STATE_DEAD);
                }
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_GOREROT_DIED:
                        {
                            if (Creature* crowley = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_CROWLEY]))
                                if (crowley->IsAIEnabled)
                                    crowley->AI()->DoAction(ACTION_GOREROT_DIED);

                            battlePhase = PHASE_GREYMANE_COURT;
                            BreakEscortPaused();
                            commonEvents.ScheduleEvent(EVENT_CROWLEY_TALK_GOREROT_DIED, 7000);
                        }
                        break;
                    case ACTION_START_EVENT:
                        StartEvent();
                        break;
                    case ACTION_DESPAWN:
                        DespawnEvent(0);
                        break;
                    case ACTION_LEADER_ON_POSITION:
                        UpdateBattleState();
                        break;
                    case ACTION_BATTLE_COMPLETE:
                        shooterAI.SetActive(false);
                        events.Reset();
                        commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_1, 3000);
                        break;
                }
            }

            void UpdateBattleState()
            {
                --battleState;

                if (!battleState)
                {
                    switch (battlePhase)
                    {
                        case PHASE_MERCHANT_SQUARE:
                            {
                                for (uint8 i = 0; i < 3; ++i)
                                    if (Creature* cannon = me->SummonCreature(NPC_EMBERSTONE_CANNON, CannonSP[i], TEMPSUMMON_TIMED_DESPAWN, 180000))
                                        cannon->GetMotionMaster()->MoveSplinePath(i, false, false, 0.f, false, false);

                                battleState = 5;
                                battlePhase = PHASE_MILITARY_DISTRICT;
                                me->SummonCreature(NPC_LORNA_CROWLEY, -1551.90f, 1284.75f, 13.992f, 3.12f);
                                commonEvents.ScheduleEvent(EVENT_TALK_MILITARY_DISTRICT, 2000);
                            }
                            break;
                        case PHASE_MILITARY_DISTRICT:
                            {
                                if (Creature* crowley = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_CROWLEY]))
                                    crowley->AI()->DoAction(ACTION_GOREROT_FIGHT);

                                me->SummonCreature(NPC_GOREROT, -1671.78f, 1449.64f, 52.287f, 3.37f);
                                commonEvents.ScheduleEvent(EVENT_CROWLEY_TALK_GOREROT, 12000);
                            }
                            break;
                    }
                }
            }

            void StartEvent()
            {
                if (!isBattle)
                {
                    isBattle = true;
                    battlePhase = PHASE_INTRO;
                    commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 0, 5000);
                    me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_DESPAWN), me->m_Events.CalculateTime(1200000));
                }
            }

            void StartBattle()
            {
                for (uint8 i = TYPE_MYRIAM; i <= TYPE_ALMYRA; ++i)
                    if (Creature* leader = ObjectAccessor::GetCreature(*me, leaderGUID[i]))
                        if (leader->IsAIEnabled)
                            leader->AI()->DoAction(ACTION_START_EVENT);

                for (int i = 0; i < 168; ++i)
                    AddWaypoint(i, FWaveWP[i][0], FWaveWP[i][1], FWaveWP[i][2]);

                Start(true);
                battleState = 3;
                battlePhase = PHASE_MERCHANT_SQUARE;
            }

            void JustSummoned(Creature* summoned) final
            {
                switch (summoned->GetEntry())
                {
                    case NPC_MYRIAM_SPELLWAKER:
                        leaderGUID[TYPE_MYRIAM] = summoned->GetGUID();
                        break;
                    case NPC_SISTER_ALMYRA:
                        leaderGUID[TYPE_ALMYRA] = summoned->GetGUID();
                        break;
                    case NPC_LORNA_CROWLEY:
                        leaderGUID[TYPE_LORNA] = summoned->GetGUID();
                        break;
                    case NPC_LORD_DARIUS_CROWLEY:
                        leaderGUID[TYPE_CROWLEY] = summoned->GetGUID();
                        break;
                    case NPC_KING_GENN_GREYMANE:
                        leaderGUID[TYPE_GREYMANE] = summoned->GetGUID();
                        break;
                    case NPC_LADY_SYLVANAS_WINDRUNNER:
                        sylvanasGUID = summoned->GetGUID();
                        break;
                }
            }

            void SummonEventCreatures()
            {
                me->SummonCreature(NPC_MYRIAM_SPELLWAKER, -1410.645f, 1261.467f, 36.428f, 1.801f);
                me->SummonCreature(NPC_SISTER_ALMYRA, -1408.634f, 1252.606f, 36.428f, 1.801f);
                SummonMilitia(me, NPC_GILNEAN_MILITIA, 1, 4);
            }

            void DespawnEvent(uint32 timeToDespawn)
            {
                for (uint8 i = TYPE_MYRIAM; i <= TYPE_GREYMANE; ++i)
                    if (Creature* leader = ObjectAccessor::GetCreature(*me, leaderGUID[i]))
                        if (leader->IsAIEnabled)
                            leader->GetAI()->SetData(TYPE_DESPAWN_EVENT, timeToDespawn);

                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                    sylvanas->DespawnOrUnsummon(timeToDespawn);

                SetData(TYPE_DESPAWN_EVENT, timeToDespawn);
            }

            void BreakEscortPaused()
            {
                SetEscortPaused(false);

                for (uint8 i = TYPE_MYRIAM; i <= TYPE_CROWLEY; ++i)
                    if (Creature* leader = ObjectAccessor::GetCreature(*me, leaderGUID[i]))
                        if (leader->IsAIEnabled)
                            if (SmoothEscortAI* escort = dynamic_cast<SmoothEscortAI*>(leader->AI()))
                                escort->SetEscortPaused(false);
            }

            void WaypointReached(uint32 point) final
            {
                switch (point)
                {
                    case 45:
                        SetEscortPaused(true);
                        UpdateBattleState();
                        break;
                    case 75:
                        Talk(LIAM_TALK_CROWLEY);
                        me->SummonCreature(NPC_LORD_DARIUS_CROWLEY, -1791.19f, 1323.6f, 19.8029f);
                        break;
                    case 94:
                        SetEscortPaused(true);
                        UpdateBattleState();
                        break;
                    case 145:
                        me->SummonCreature(NPC_LADY_SYLVANAS_WINDRUNNER, -1684.79f, 1616.47f, 20.4894f, 2.50855f);
                        me->SummonCreature(NPC_KING_GENN_GREYMANE, -1770.961f, 1687.437f, 22.158f, 5.565678f);
                        break;
                    case 167:
                        {
                            if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                            {
                                sylvanas->SetReactState(REACT_AGGRESSIVE);
                                sylvanas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                CustomSpellValues values;
                                values.AddSpellMod(SPELLVALUE_RADIUS_MOD, 100.f);
                                sylvanas->CastCustomSpell(43263, values, (Unit*)NULL, true);
                            }
                        }
                        break;
                }
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
                CustomSpellValues values;
                values.AddSpellMod(SPELLVALUE_RADIUS_MOD, 40.f);
                me->CastCustomSpell(43263, values, (Unit*)NULL, true);
                events.ScheduleEvent(EVENT_MULTI_SHOT, urand(2500, 5000));
                events.ScheduleEvent(EVENT_CHALLENGING_SHOUT, urand(3000, 7000));
                events.ScheduleEvent(EVENT_LIAM_BATTLE_YELL, urand(3000, 7000));
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                commonEvents.Update(diff);

                if (uint32 eventId = commonEvents.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LIAM_BATTLE_SPEACH + 0:
                            Talk(LIAM_TALK_BATTLE_SPEACH);
                            commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 1, 7500);
                            break;
                        case EVENT_LIAM_BATTLE_SPEACH + 1:
                            Talk(LIAM_TALK_BATTLE_SPEACH + 1);
                            commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 2, 8500);
                            break;
                        case EVENT_LIAM_BATTLE_SPEACH + 2:
                            Talk(LIAM_TALK_BATTLE_SPEACH + 2);
                            commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 3, 10500);
                            break;
                        case EVENT_LIAM_BATTLE_SPEACH + 3:
                            Talk(LIAM_TALK_BATTLE_SPEACH + 3);
                            commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 4, 8500);
                            break;
                        case EVENT_LIAM_BATTLE_SPEACH + 4:
                            Talk(LIAM_TALK_BATTLE_SPEACH + 4);
                            commonEvents.ScheduleEvent(EVENT_LIAM_BATTLE_SPEACH + 5, 10500);
                            break;
                        case EVENT_LIAM_BATTLE_SPEACH + 5:
                            Talk(LIAM_TALK_BATTLE_SPEACH + 5);
                            commonEvents.ScheduleEvent(EVENT_START_BATTLE, 4500);
                            break;
                        case EVENT_START_BATTLE:
                            Talk(LIAM_TALK_BATTLE_FOR_GILNEAS);
                            battlePhase = PHASE_MERCHANT_SQUARE;
                            StartBattle();
                            break;
                        case EVENT_TALK_MILITARY_DISTRICT:
                            Talk(LIAM_TALK_MILITARY_DISTRICT);
                            commonEvents.ScheduleEvent(EVENT_ATTACK_MILITARY_DISTRICT, 6500);
                            break;
                        case EVENT_ATTACK_MILITARY_DISTRICT:
                            BreakEscortPaused();
                            commonEvents.ScheduleEvent(EVENT_LIAM_TALK_LORNA, 9000);
                            break;
                        case EVENT_LIAM_TALK_LORNA:
                            Talk(LIAM_TALK_LORNA);
                            break;
                        case EVENT_CROWLEY_TALK_GOREROT:
                            {
                                if (Creature* crowley = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_CROWLEY]))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_TALK_GOREROT);
                            }
                            break;
                        case EVENT_CROWLEY_TALK_GOREROT_DIED:
                            {
                                if (Creature* crowley = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_CROWLEY]))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_TALK_GOREROT_DIED);
                            }
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_1:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    if (sylvanas->IsAIEnabled)
                                        sylvanas->AI()->Talk(SYLVANAS_YELL_KILL_LIAM);

                                me->RemoveAllAuras();
                                commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_2, 3000);
                            }
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_2:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_GREYMANE]))
                                {
                                    Talk(LIAM_YELL_FATHER);
                                    me->Dismount();
                                    me->SetWalk(false);

                                    if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    {
                                        float x, y;
                                        greymane->GetNearPoint2D(x, y, 0.5f, greymane->GetAngle(sylvanas));
                                        me->GetMotionMaster()->MovePoint(0, x, y, greymane->GetPositionZ());
                                    }
                                }

                                commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_3, me->GetSplineDuration() + 250);
                            }
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_3:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                {
                                    sylvanas->CastSpell(me, SPELL_SHOOT_LIAM, false);
                                    sylvanas->CastSpell((Unit*)NULL, SPELL_BFGC_COMPLETE, false);
                                    sylvanas->GetMotionMaster()->MovePoint(0, -1628.85f, 1626.61f, 20.4884f);
                                    sylvanas->ForcedDespawn(2000);

                                    if (Creature* greymane = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_GREYMANE]))
                                        if (greymane->IsAIEnabled)
                                            greymane->AI()->Talk(GREYMANE_YELL_LIAM);

                                    if (me->IsSummon())
                                        if (Creature* krennan = me->ToTempSummon()->GetSummonerCreatureBase())
                                            if (krennan->IsAIEnabled)
                                                krennan->AI()->DoAction(ACTION_BATTLE_COMPLETE);
                                }

                                commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_4, 3000);
                            }
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_4:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, leaderGUID[TYPE_GREYMANE]))
                                {
                                    greymane->RemoveAllAuras();
                                    greymane->SetStandState(UNIT_STAND_STATE_KNEEL);
                                    greymane->SetFacingToObject(me);
                                }

                                commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_5, 5000);
                            }
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_5:
                            Talk(LIAM_TALK_FINISH_1);
                            commonEvents.ScheduleEvent(EVENT_SYLVANAS_KILL_LIAM_6, 3000);
                            break;
                        case EVENT_SYLVANAS_KILL_LIAM_6:
                            Talk(LIAM_TALK_FINISH_2);
                            DespawnEvent(30000);
                            break;
                    }
                }

                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MULTI_SHOT:
                            me->CastSpell(me->GetVictim(), SPELL_MULTI_SHOT, false);
                            events.ScheduleEvent(EVENT_MULTI_SHOT, urand(2500, 5000));
                            break;
                        case EVENT_LIAM_BATTLE_YELL:
                            Talk(LIAM_TALK_BATTLE);
                            events.ScheduleEvent(EVENT_LIAM_BATTLE_YELL, urand(15000, 30000));
                            break;
                        case EVENT_CHALLENGING_SHOUT:
                            me->CastSpell((Unit*)NULL, SPELL_CHALLENGING_SHOUT, false);
                            events.ScheduleEvent(EVENT_CHALLENGING_SHOUT, urand(10000, 20000));
                            break;
                    }
                }
            }
        };
};

class npc_myriam_spellwaker_tbfgc final : public CreatureScript
{
    public:
        npc_myriam_spellwaker_tbfgc() : CreatureScript("npc_myriam_spellwaker_tbfgc"){ }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public BattleForGilneasLeaderAI
        {
            creature_script_impl(Creature* creature) : BattleForGilneasLeaderAI(creature) { }

            enum
            {
                EVENT_BLIZZARD      = 1,
                EVENT_FIRE_BLAST    = 2,
                EVENT_FROSTBOLT     = 3,

                SPELL_BLIZZARD      = 33418,
                SPELL_FIRE_BLAST    = 20795,
                SPELL_FROSTBOLT     = 20792,

                NPC_GILNEAN_MILITIA = 38221,
            };

            EventMap events;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->setActive(true);
            }

            void Reset() final
            {
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) final
            {
                SummonMilitia(summoner, NPC_GILNEAN_MILITIA, 5, 7);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_EVENT:
                        {
                            for (int i = 0; i < 173; ++i)
                                AddWaypoint(i, SWaveWP[i][0], SWaveWP[i][1], SWaveWP[i][2]);

                            Start(true);
                        }
                        break;
                }
            }

            void WaypointReached(uint32 point) final
            {
                switch (point)
                {
                    case 54:
                    case 102:
                        {
                            if (me->IsSummon())
                                if (Creature* liam = me->ToTempSummon()->GetSummonerCreatureBase())
                                    if (liam->IsAIEnabled)
                                        liam->GetAI()->DoAction(ACTION_LEADER_ON_POSITION);

                            SetEscortPaused(true);
                        }
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void EnterCombat(Unit* who) final
            {
                CustomSpellValues values;
                values.AddSpellMod(SPELLVALUE_RADIUS_MOD, 40.f);
                me->CastCustomSpell(43263, values, (Unit*)NULL, true);
                events.ScheduleEvent(EVENT_FIRE_BLAST, urand(3000, 5000));
                events.ScheduleEvent(EVENT_FROSTBOLT, urand(3000, 5000));
                events.ScheduleEvent(EVENT_BLIZZARD, urand(5000, 15000));
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FIRE_BLAST:
                            me->CastSpell(me->GetVictim(), SPELL_FIRE_BLAST, false);
                            events.ScheduleEvent(EVENT_FIRE_BLAST, urand(3500, 7000));
                            break;
                        case EVENT_FROSTBOLT:
                            me->CastSpell(me->GetVictim(), SPELL_FROSTBOLT, false);
                            events.ScheduleEvent(EVENT_FROSTBOLT, 3000);
                            break;
                        case EVENT_BLIZZARD:
                            me->CastSpell(me->GetVictim(), SPELL_BLIZZARD, false);
                            events.ScheduleEvent(EVENT_BLIZZARD, urand(10000, 20000));
                            break;
                    }
                }
            }
        };
};

class npc_sister_almyra_tbfgc final : public CreatureScript
{
    public:
        npc_sister_almyra_tbfgc() : CreatureScript("npc_sister_almyra_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public BattleForGilneasLeaderAI
        {
            creature_script_impl(Creature* creature) : BattleForGilneasLeaderAI(creature) { }

            enum
            {
                EVENT_FLASH_HEAL        = 1,
                EVENT_HOLY_NOVA         = 2,

                SPELL_FLASH_HEAL        = 17843,
                SPELL_HOLY_NOVA         = 85965,

                NPC_GILNEAN_MILITIA     = 38221,
                NPC_DARK_RANGER_ELITE   = 38464,
            };

            EventMap events;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->setActive(true);
            }

            void Reset() final
            {
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) final
            {
                SummonMilitia(summoner, NPC_GILNEAN_MILITIA, 8, 10);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_START_EVENT:
                        {
                            for (int i = 0; i < 160; ++i)
                                AddWaypoint(i, TWaveWP[i][0], TWaveWP[i][1], TWaveWP[i][2]);

                            Start(true);
                        }
                        break;
                }
            }

            void WaypointReached(uint32 point) final
            {
                switch (point)
                {
                    case 17:
                        {
                            for (uint8 i = 0; i < 2; ++i)
                                if (Creature* ranger = me->SummonCreature(NPC_DARK_RANGER_ELITE, RangerSP[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 15000))
                                    ranger->GetMotionMaster()->MoveSplinePath(i);
                        }
                        break;
                    case 24:
                    case 87:
                        {
                            if (me->IsSummon())
                                if (Creature* liam = me->ToTempSummon()->GetSummonerCreatureBase())
                                    if (liam->IsAIEnabled)
                                        liam->GetAI()->DoAction(ACTION_LEADER_ON_POSITION);

                            SetEscortPaused(true);
                        }
                        break;
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void EnterCombat(Unit* who) final
            {
                CustomSpellValues values;
                values.AddSpellMod(SPELLVALUE_RADIUS_MOD, 40.f);
                me->CastCustomSpell(43263, values, (Unit*)NULL, true);
                events.ScheduleEvent(EVENT_FLASH_HEAL, urand(1500, 3000));
                events.ScheduleEvent(EVENT_HOLY_NOVA, urand(3000, 5000));
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FLASH_HEAL:
                            {
                                if (Unit* target = DoSelectLowestHpFriendly(35.f, 1))
                                    DoCast(target, SPELL_FLASH_HEAL);

                                events.ScheduleEvent(EVENT_FLASH_HEAL, urand(1500, 3000));
                            }
                            break;
                        case EVENT_HOLY_NOVA:
                            me->CastSpell((Unit*)NULL, SPELL_HOLY_NOVA, false);
                            events.ScheduleEvent(EVENT_HOLY_NOVA, urand(3000, 5000));
                            break;
                    }
                }
            }
        };
};

class npc_gilnean_militia_tbfgc final : public CreatureScript
{
    public:
        npc_gilnean_militia_tbfgc() : CreatureScript("npc_gilnean_militia_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 100.f)
            { }

            enum
            {
                EVENT_WING_CLIP             = 1,
                EVENT_SUNDER_ARMOR          = 2,

                SPELL_SHOOT                 = 22121,
                SPELL_IMPROVED_WING_CLIP    = 47168,
                SPELL_SUNDER_ARMOR          = 15572,
            };

            ShooterGuardAI shooterAI;
            EventMap events;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->setActive(true);
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();
                me->SetWalk(false);
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterEvadeMode() final
            {
                if (me->IsSummon())
                {
                    if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
                    {
                        if (summoner->GetVictim())
                            AttackStart(summoner->GetVictim());

                        if (summoner->IsInCombat())
                            return;
                    }
                }

                ScriptedAI::EnterEvadeMode();
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell) final
            {
                if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
                {
                    shooterAI.SetActive(false);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    me->DeleteThreatList();
                    me->CombatStop(true);
                }
            }

            void AttackStart(Unit* who) final
            {
                shooterAI.AttackStart(who);

                if (me->IsSummon())
                {
                    if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
                    {
                        if (!summoner->GetVictim())
                        {
                            if (summoner->IsAIEnabled)
                                summoner->AI()->AttackStart(who);
                        }
                        else
                        {
                            who->SetInCombatWith(summoner);
                            summoner->AddThreat(who, 0.0f);
                        }
                    }
                }
            }

            void EnterCombat(Unit* who) final
            {
                if (me->isMoving())
                    me->StopMoving();

                shooterAI.EnterCombat(who);
                CustomSpellValues values;
                values.AddSpellMod(SPELLVALUE_RADIUS_MOD, 40.f);
                me->CastCustomSpell(43263, values, (Unit*)NULL, true);
                events.ScheduleEvent(EVENT_WING_CLIP, urand(5000, 15000));
                events.ScheduleEvent(EVENT_SUNDER_ARMOR, urand(3000, 5000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WING_CLIP:
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 2.f))
                                    me->CastSpell(target, SPELL_IMPROVED_WING_CLIP, false);

                                events.ScheduleEvent(EVENT_WING_CLIP, urand(5000, 15000));
                            }
                            break;
                        case EVENT_SUNDER_ARMOR:
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 2.f))
                                    me->CastSpell(target, SPELL_SUNDER_ARMOR, false);

                                events.ScheduleEvent(EVENT_SUNDER_ARMOR, urand(3000, 5000));
                            }
                            break;
                    }
                }
            }
        };
};

class npc_dark_ranger_elite_tbfgc final : public CreatureScript
{
    public:
        npc_dark_ranger_elite_tbfgc() : CreatureScript("npc_dark_ranger_elite_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 80.f)
            { }

            enum
            {
                EVENT_KNOCKBACK = 1,

                SPELL_SHOOT     = 22121,
                SPELL_KNOCKBACK = 68683,
            };

            ShooterGuardAI shooterAI;
            EventMap events;

            void InitializeAI() final
            {
                Reset();
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
                events.Reset();
                me->m_Events.AddEvent(new AggroEvent(me), me->m_Events.CalculateTime(500));
            }

            void AttackStart(Unit* who) final
            {
                shooterAI.AttackStart(who);
            }

            void EnterCombat(Unit* who) final
            {
                me->StopMoving();
                me->SetHomePosition(*me);
                shooterAI.EnterCombat(who);
                events.ScheduleEvent(EVENT_KNOCKBACK, urand(5000, 10000));
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!shooterAI.UpdateShooterAI(diff))
                    return;

                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_KNOCKBACK)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 5.f))
                        me->CastSpell(target, SPELL_KNOCKBACK, false);

                    events.ScheduleEvent(EVENT_KNOCKBACK, urand(7500, 15000));
                }
            }
        };
};

class npc_lorna_crowley_tbfgc final : public CreatureScript
{
    public:
        npc_lorna_crowley_tbfgc() : CreatureScript("npc_lorna_crowley_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public SmoothEscortAI
        {
            creature_script_impl(Creature* creature)
                : SmoothEscortAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 80.f)
            { }

            enum
            {
                SPELL_SHOOT         = 22411,

                TEXT_LORNA_BATTLE   = 1,
            };

            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
                me->setActive(true);
                Reset();
            }

            void Reset() final
            {
                shooterAI.Reset();
            }

            void IsSummonedBy(Unit* summoner) final
            {
                for (int i = 0; i < 78; ++i)
                    AddWaypoint(i, LornaWP[i][0], LornaWP[i][1], LornaWP[i][2]);

                Start(true);
            }

            void SetData(uint32 type, uint32 data) final
            {
                if (type == TYPE_DESPAWN_EVENT)
                    me->DespawnOrUnsummon(data);
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell) final
            {
                if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
                {
                    shooterAI.SetActive(false);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    me->DeleteThreatList();
                    me->CombatStop(true);
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                shooterAI.DamageTaken(attacker, damage);
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
            }

            void WaypointReached(uint32 point) final
            {
                switch (point)
                {
                    case 8:
                        Talk(TEXT_LORNA_BATTLE);
                        break;
                    case 41:
                        {
                            if (me->IsSummon())
                                if (Creature* liam = me->ToTempSummon()->GetSummonerCreatureBase())
                                    if (liam->IsAIEnabled)
                                        liam->GetAI()->DoAction(ACTION_LEADER_ON_POSITION);

                            SetEscortPaused(true);
                        }
                        break;
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                shooterAI.UpdateShooterAI(diff);
            }
        };
};

class npc_emberstone_cannon_tbfgc final : public CreatureScript
{
    public:
        npc_emberstone_cannon_tbfgc() : CreatureScript("npc_emberstone_cannon_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                ACTION_MOVE_DONE                = 1,
                ACTION_INITIALIZE               = 2,
                ACTION_REMOVE_VILLAGER          = 3,

                SPELL_EJECT_ALL_PASSENGERS      = 50630,

                NPC_FREED_EMBERSTONE_VILLAGER   = 38425,
            };

            void InitializeAI() final
            {
                me->AddExtraUnitMovementFlag(MOVEMENTFLAG2_FULL_SPEED_PITCHING);
                me->AddExtraUnitMovementFlag(MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING);
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_INITIALIZE), me->m_Events.CalculateTime(250));
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_INITIALIZE:
                        {
                            if (Creature* villager = me->SummonCreature(NPC_FREED_EMBERSTONE_VILLAGER, *me, TEMPSUMMON_TIMED_DESPAWN, me->GetSplineDuration() + 25000))
                                villager->EnterVehicle(me);

                            me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_REMOVE_VILLAGER), me->m_Events.CalculateTime(me->GetSplineDuration() -  250));
                            me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_MOVE_DONE), me->m_Events.CalculateTime(me->GetSplineDuration()));
                        }
                        break;
                    case ACTION_REMOVE_VILLAGER:
                        me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, false);
                        break;
                    case ACTION_MOVE_DONE:
                        me->SetFacingTo(3.193953f);
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        break;
                }
            }
        };
};

class npc_gilneas_forsaken_crossbowman_tbfgc final : public CreatureScript
{
    public:
        npc_gilneas_forsaken_crossbowman_tbfgc() : CreatureScript("npc_gilneas_forsaken_crossbowman_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT)
            { }

            enum
            {
                SPELL_SHOOT = 22411,
            };

            ShooterGuardAI shooterAI;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->m_ReactDistance = 30.0f;
            }

            void Reset() final
            {
                shooterAI.Reset();
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);
            }

            void UpdateAI(uint32 const diff) final
            {
                shooterAI.UpdateShooterAI(diff);
            }
        };
};

class npc_lord_darius_crowley_tbfgc final : public CreatureScript
{
    public:
        npc_lord_darius_crowley_tbfgc() : CreatureScript("npc_lord_darius_crowley_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public BattleForGilneasLeaderAI
        {
            creature_script_impl(Creature* creature) : BattleForGilneasLeaderAI(creature) { }

            enum
            {
                EVENT_SLICE_AND_DICE    = 1,
                EVENT_TAUNT             = 2,
                EVENT_FERAL_LEAP        = 3,
                EVENT_JUMP              = 4,
                EVENT_JUMP_DONE         = 5,

                SPELL_SLICE_AND_DICE    = 6434,
                SPELL_TAUNT             = 37548,
                SPELL_FERAL_LEAP        = 71921,
                SPELL_INTERCEPT         = 58769,

                NPC_WORGEN_WARRIOR      = 38348,
            };

            EventMap events;
            bool gorerot;

            void InitializeAI() final
            {
                SummonMilitia(me, NPC_WORGEN_WARRIOR, 1, 4);
                Reset();
                me->setActive(true);
            }

            void Reset() final
            {
                gorerot = false;
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) final
            {
                for (int j = 0; j < 90; ++j)
                    AddWaypoint(j, FWorgenWP[j][0], FWorgenWP[j][1], FWorgenWP[j][2]);

                Start(true, true);
            }

            void DoAction(int32 const action) final
            {
                switch (action)
                {
                    case ACTION_GOREROT_FIGHT:
                        gorerot = true;
                        break;
                    case ACTION_GOREROT_DIED:
                        gorerot = false;
                        me->GetMotionMaster()->MoveJump(-1715.62f, 1403.78f, 21.6688f, 10.0f, 10.0f);
                        break;
                }
            }

            void WaypointReached(uint32 point) final
            {
                if (point == 18)
                {
                    if (me->IsSummon())
                        if (Creature* liam = me->ToTempSummon()->GetSummonerCreatureBase())
                            if (liam->IsAIEnabled)
                                liam->GetAI()->DoAction(ACTION_LEADER_ON_POSITION);

                    SetEscortPaused(true);
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void EnterCombat(Unit* who) final
            {
                me->CastSpell(who, SPELL_INTERCEPT, false);
                events.ScheduleEvent(EVENT_TAUNT, 1000);
                events.ScheduleEvent(EVENT_SLICE_AND_DICE, 2000);

                if (gorerot)
                    events.ScheduleEvent(EVENT_JUMP, 12000);
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_JUMP:
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->StopMoving();
                            me->GetMotionMaster()->MoveJump(-1692.618f, 1428.863f, 42.7f, 15.0f, 20.0f);
                            events.Reset();
                            events.ScheduleEvent(EVENT_FERAL_LEAP, me->GetSplineDuration());
                            break;
                        case EVENT_FERAL_LEAP:
                            me->CastSpell((Unit*)NULL, SPELL_FERAL_LEAP, false);
                            events.ScheduleEvent(EVENT_JUMP_DONE, me->GetSplineDuration() + 500);
                            break;
                        case EVENT_JUMP_DONE:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            events.ScheduleEvent(EVENT_TAUNT, 1000);
                            events.ScheduleEvent(EVENT_SLICE_AND_DICE, 5000);
                            events.ScheduleEvent(EVENT_JUMP, urand(10000, 20000));
                            break;
                        case EVENT_TAUNT:
                            me->CastSpell(me->GetVictim(), SPELL_TAUNT, false);
                            events.ScheduleEvent(EVENT_TAUNT, 7000);
                            break;
                        case EVENT_SLICE_AND_DICE:
                            me->CastSpell(me, SPELL_SLICE_AND_DICE, false);
                            events.ScheduleEvent(EVENT_SLICE_AND_DICE, urand(10000, 20000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_worgen_warrior_tbfgc final : public CreatureScript
{
    public:
        npc_worgen_warrior_tbfgc() : CreatureScript("npc_worgen_warrior_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell) final
            {
                if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
                {
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    me->DeleteThreatList();
                    me->CombatStop(true);
                }
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void EnterEvadeMode() final
            {
                if (me->IsSummon())
                {
                    if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
                    {
                        if (summoner->GetVictim())
                            AttackStart(summoner->GetVictim());

                        if (summoner->IsInCombat())
                            return;
                    }
                }

                ScriptedAI::EnterEvadeMode();
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_gorerot_tbfgc final : public CreatureScript
{
    public:
        npc_gorerot_tbfgc() : CreatureScript("npc_gorerot_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_THUNDERCLAP       = 1,
                EVENT_SMASH             = 2,
                EVENT_APPLY_WORGENS     = 3,

                ACTION_START_COMBAT     = 1,

                GOREROT_YELL_CRUSH      = 1,

                SPELL_THUNDERCLAP       = 8078,
                SPELL_SMASH             = 71774,

                NPC_WORGEN_WARRIOR      = 38348,
            };

            EventMap events;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->setActive(true);
                Reset();
            }

            void Reset() final
            {
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                static Position gorerotJP = {-1710.47f, 1407.91f, 21.752f, 3.37f};
                me->GetMotionMaster()->MoveJump(gorerotJP, 20.f, 30.f);
                me->SetHomePosition(gorerotJP);
                me->m_Events.AddEvent(new DelayEventDoAction(me, ACTION_START_COMBAT), me->m_Events.CalculateTime(me->GetSplineDuration() + 250));
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_START_COMBAT)
                {
                    Talk(GOREROT_YELL_CRUSH);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->CastSpell((Unit*)NULL, SPELL_THUNDERCLAP, false);
                }
            }

            void JustDied(Unit* /*killer*/) final
            {
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* liam = summoner->ToTempSummon())
                            liam->AI()->DoAction(ACTION_GOREROT_DIED);
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                switch (seatId)
                {
                    case 0:
                    case 1:
                        passenger->m_movementInfo.t_pos.m_orientation = M_PI;
                        enterPos.m_orientation = M_PI;
                        break;
                }
            }

            void EnterCombat(Unit* who) final
            {
                events.ScheduleEvent(EVENT_APPLY_WORGENS, 1000);
                events.ScheduleEvent(EVENT_SMASH, urand(5000, 10000));
                events.ScheduleEvent(EVENT_THUNDERCLAP, urand(7000, 14000));

                if (Aura* aura = me->AddAura(64748, me))
                {
                    aura->SetDuration(std::numeric_limits<int>::max());

                    if (AuraEffect* effect = aura->GetEffect(EFFECT_0))
                        effect->ChangeAmount(-90);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_APPLY_WORGENS:
                            {
                                uint8 seatId = 0;
                                std::list<Creature*> worgenList;
                                Vehicle* vehicle = me->GetVehicleKit();
                                me->GetCreatureListWithEntryInGrid(worgenList, NPC_WORGEN_WARRIOR, 10.0f);

                                if (!vehicle || worgenList.empty())
                                    return;

                                std::list<Creature*>::const_iterator itr = worgenList.begin();

                                while (seatId < 4 && itr != worgenList.end())
                                {
                                    if (vehicle->HasEmptySeat(seatId))
                                    {
                                        while (itr != worgenList.end())
                                        {
                                            if (Creature* worgen = *itr)
                                            {
                                                if (!worgen->GetVehicle() && worgen->IsAlive())
                                                {
                                                    worgen->EnterVehicle(me, seatId);
                                                    ++seatId;
                                                    ++itr;
                                                    break;
                                                }
                                            }

                                            ++itr;
                                        }
                                    }
                                    else
                                        ++seatId;
                                }
                            }
                            break;
                        case EVENT_THUNDERCLAP:
                            {
                                if (Vehicle* vehicle = me->GetVehicleKit())
                                    vehicle->RemoveAllPassengers();

                                me->CastSpell((Unit*)NULL, SPELL_THUNDERCLAP, false);
                                events.RescheduleEvent(EVENT_APPLY_WORGENS, 2000);
                                events.ScheduleEvent(EVENT_THUNDERCLAP, urand(10000, 20000));
                            }
                            break;
                        case EVENT_SMASH:
                            {
                                uint8 roll = urand(0, 4);

                                if (Vehicle* vehicle = me->GetVehicleKit())
                                {
                                    if (Unit* passenger = vehicle->GetPassenger(roll))
                                    {
                                        passenger->ExitVehicle();
                                        me->CastSpell(passenger, SPELL_SMASH, false);
                                        events.RescheduleEvent(EVENT_APPLY_WORGENS, 2000);
                                    }
                                }

                                events.ScheduleEvent(EVENT_SMASH, urand(5000, 10000));
                            }
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_damaged_catapult_tbfgc final : public CreatureScript
{
    public:
        npc_damaged_catapult_tbfgc() : CreatureScript("npc_damaged_catapult_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                SPELL_SOLDIER_OF_TBFGC  = 72069,
                SPELL_BURNING           = 72839,
            };

            void InitializeAI() final
            {
                me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SOLDIER_OF_TBFGC, true);
            }

            void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply) final
            {
                if (apply)
                    me->AddAura(SPELL_BURNING, me);
                else
                    me->RemoveAura(SPELL_BURNING);
            }
        };
};

class npc_king_genn_greymane_tbfgc final : public CreatureScript
{
    public:
        npc_king_genn_greymane_tbfgc() : CreatureScript("npc_king_genn_greymane_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public BattleForGilneasLeaderAI
        {
            creature_script_impl(Creature* creature) : BattleForGilneasLeaderAI(creature) { }

            enum
            {
                NPC_GILNEAN_MILITIA         = 38221,

                SPELL_GREYMANE_TRANSFORM    = 86141,
                TALK_SYLVANAS               = 2,
                TALK_BLOCK                  = 1,

            };

            void InitializeAI() final
            {
                me->setActive(true);
                SummonMilitia(me, NPC_GILNEAN_MILITIA, 1, 4);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                for (int i = 0; i < 16; ++i)
                    AddWaypoint(i, GreymaneWP[i][0], GreymaneWP[i][1], GreymaneWP[i][2]);

                Start(true);
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void WaypointReached(uint32 point) final
            {
                switch (point)
                {
                    case 4:
                        Talk(TALK_BLOCK);
                        break;
                    case 6:
                        Talk(TALK_SYLVANAS);
                        me->CastSpell(me, SPELL_GREYMANE_TRANSFORM, false);
                        break;
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                SmoothEscortAI::UpdateAI(diff);

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_lady_sylvanas_windrunner_tbfgc final : public CreatureScript
{
    public:
        npc_lady_sylvanas_windrunner_tbfgc() : CreatureScript("npc_lady_sylvanas_windrunner_tbfgc") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature)
                : ScriptedAI(creature)
                , shooterAI(creature, SPELL_SHOOT, 100.f)
            { }

            enum
            {
                SPELL_SHOOT                 = 22121,

                SYLVANAS_YELL_ENOUGH        = 1,
            };

            ShooterGuardAI shooterAI;
            bool enrage;

            void InitializeAI() final
            {
                SetCombatMovement(false);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->setActive(true);
            }

            void Reset() final
            {
                enrage = false;
                shooterAI.Reset();
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (!enrage && me->HealthBelowPctDamaged(20, damage))
                {
                    damage = 0;
                    enrage = true;
                    shooterAI.SetActive(false);
                    Talk(SYLVANAS_YELL_ENOUGH);
                    me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->CastSpell((Unit*)NULL, SPELL_BANSHEE_QUEENS_WAIL, false);

                    if (me->IsSummon())
                        if (Creature* liam = me->ToTempSummon()->GetSummonerCreatureBase())
                            if (liam->IsAIEnabled)
                                liam->AI()->DoAction(ACTION_BATTLE_COMPLETE);
                }
            }

            void EnterCombat(Unit* who) final
            {
                shooterAI.EnterCombat(who);

                if (Aura* aura = me->AddAura(64748, me))
                {
                    aura->SetDuration(std::numeric_limits<int>::max());

                    if (AuraEffect* effect = aura->GetEffect(EFFECT_0))
                        effect->ChangeAmount(-99);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                shooterAI.UpdateShooterAI(diff);
            }
        };
};

// Quest The Hunt For Sylvanas 24902
class npc_lorna_crowley_qthfs final : public CreatureScript
{
    public:
        npc_lorna_crowley_qthfs() : CreatureScript("npc_lorna_crowley_qthfs") { }

    private:
        enum
        {
            SPELL_SUMMON_TOBIAS = 72471,
        };

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) final
        {
            if (quest->GetQuestId() == QUEST_THE_HUNT_FOR_SYLVANAS)
                creature->CastSpell(player, SPELL_SUMMON_TOBIAS, false, NULL, NULL, player->GetGUID());

            return false;
        }

        bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_GILNEAS_CITY)
            {
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->CastSpell(player, SPELL_ZONE_SPECIFIC_13, false);
                player->SaveToDB();
            }

            return false;
        }
};

class npc_tobias_mistmantle_qthfs final : public CreatureScript
{
    public:
        npc_tobias_mistmantle_qthfs() : CreatureScript("npc_tobias_mistmantle_qthfs") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                EVENT_START_HUNT                    = 1,
                EVENT_TALK_NOT_SEEN                 = 2,
                EVENT_JUMP_1                        = 3,
                EVENT_RESUME_HUNT_1                 = 4,
                EVENT_JUMP_2                        = 5,
                EVENT_RESUME_HUNT_2                 = 6,
                EVENT_GENERAL_SAY                   = 9,
                EVENT_TALK_DID_YOU_HEAR             = 10,
                EVENT_JUMP_IN_WATER                 = 11,
                EVENT_FINISH_HUNT                   = 12,
                EVENT_SUMMON_SYLVANAS               = 13,
                EVENT_CHECK_PLAYER_POSITION         = 14,
                EVENT_SYLVANAS_ON_POISITON          = 15,
                EVENT_WARHOWL_TALK_LOSING           = 16,
                EVENT_SYLVANAS_TALK_ASSURE          = 17,
                EVENT_WARHOWL_TALK_PLAGUE           = 18,
                EVENT_SYLVANAS_TALK_TONE            = 19,
                EVENT_WARHOWL_TALK_GOOD_BY          = 20,
                EVENT_SYLVANAS_TALK_GO_WITH_HONOR   = 21,
                EVENT_CRENSHAW_WALK_TO_SYLVANAS     = 22,
                EVENT_CRENSHAW_TALK_ORDER           = 23,
                EVENT_SYLVANAS_TALK_WHAT_QUESTION   = 24,
                EVENT_CRENSHAW_TALK_AS_YOU_WISH     = 25,
                EVENT_CRENSHAW_WALK_AWAY            = 26,

                TOBIAS_SAY_LETS_GO                  = 1,
                TOBIAS_EMOTE_LETS_GO                = 2,
                TOBIAS_SAY_NOT_SEEN                 = 3,
                TOBIAS_SAY_DID_YOU_HEAR             = 4,
                TOBIAS_SAY_HIDE                     = 5,
                GENERAL_SYLVANAS                    = 1,
                WARHOWL_SAY_LOSING                  = 1,
                WARHOWL_SAY_PLAGUE                  = 2,
                WARHOWL_SAY_GOOD_BY                 = 3,
                SYLVANAS_SAY_ASSURE                 = 1,
                SYLVANAS_SAY_TONE                   = 2,
                SYLVANAS_SAY_GO_WITH_HONOR          = 3,
                SYLVANAS_SAY_WHAT_QUESTION          = 4,
                CRENSHAW_SAY_ORDER                  = 1,
                CRENSHAW_AS_YOU_WISH                = 2,

                NPC_FORSAKEN_GENERAL                = 38617,
                NPC_LADY_SYLVANAS                   = 38530,
                NPC_GENERAL_WARHOWL                 = 38533,
                NPC_HIGH_EXECUTOR_CRENSHAW          = 38537,

                SPELL_SHOOT                         = 48424,
            };

            EventMap events;
            uint64 sylvanasGUID;
            uint64 warhowlGUID;
            uint64 crenshawGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                Talk(TOBIAS_SAY_LETS_GO, me->ToTempSummon()->GetSummonerGUID(), true);
                events.ScheduleEvent(EVENT_START_HUNT, 5000);
            }

            void JustSummoned(Creature* summoned) final
            {
                summoned->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, me->ToTempSummon()->GetSummonerGUID());
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_HUNT:
                            Talk(TOBIAS_EMOTE_LETS_GO, me->ToTempSummon()->GetSummonerGUID(), true);
                            me->GetMotionMaster()->MoveSplinePath(1, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_TALK_NOT_SEEN, me->GetSplineDuration() + 250);
                            break;
                        case EVENT_TALK_NOT_SEEN:
                            Talk(TOBIAS_SAY_NOT_SEEN, me->ToTempSummon()->GetSummonerGUID(), true);
                            events.ScheduleEvent(EVENT_JUMP_1, 2500);
                            break;
                        case EVENT_JUMP_1:
                            me->GetMotionMaster()->MoveJump(-1599.64f, 1607.60f, 21.5590f, 20.f, 15.f);
                            events.ScheduleEvent(EVENT_RESUME_HUNT_1, me->GetSplineDuration() + 2500);
                            break;
                        case EVENT_RESUME_HUNT_1:
                            me->GetMotionMaster()->MoveSplinePath(2, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_JUMP_2, me->GetSplineDuration());
                            break;
                        case EVENT_JUMP_2:
                            me->GetMotionMaster()->MoveJump(-1582.17f, 1626.81f, 20.5150f, 15.f, 15.f);
                            events.ScheduleEvent(EVENT_RESUME_HUNT_2, me->GetSplineDuration() + 1000);
                            break;
                        case EVENT_RESUME_HUNT_2:
                            me->GetMotionMaster()->MoveSplinePath(3, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_GENERAL_SAY, me->GetSplineDuration());
                            break;
                        case EVENT_GENERAL_SAY:
                            {
                                if (Creature* general = me->FindNearestCreature(NPC_FORSAKEN_GENERAL, 20.0f))
                                    if (general->IsAIEnabled)
                                        general->AI()->Talk(GENERAL_SYLVANAS, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_TALK_DID_YOU_HEAR, 8000);
                            }
                            break;
                        case EVENT_TALK_DID_YOU_HEAR:
                            Talk(TOBIAS_SAY_DID_YOU_HEAR, me->ToTempSummon()->GetSummonerGUID(), true);
                            me->GetMotionMaster()->MoveSplinePath(4, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_JUMP_IN_WATER, me->GetSplineDuration());
                            break;
                        case EVENT_JUMP_IN_WATER:
                            Talk(TOBIAS_SAY_HIDE, me->ToTempSummon()->GetSummonerGUID(), true);
                            me->GetMotionMaster()->MoveJump(-1617.92f, 1532.31f, 23.6932f, 15.f, 10.f);
                            events.ScheduleEvent(EVENT_FINISH_HUNT, me->GetSplineDuration());
                            break;
                        case EVENT_FINISH_HUNT:
                            me->SetSwim(true);
                            me->SetDisableGravity(true);
                            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0x3000000);
                            me->GetMotionMaster()->MoveSplinePath(5, false, false, 0.f, false, false);
                            events.ScheduleEvent(EVENT_SUMMON_SYLVANAS, me->GetSplineDuration() + 500);
                            break;
                        case EVENT_SUMMON_SYLVANAS:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    if (!summoner->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
                                    {
                                        events.ScheduleEvent(EVENT_SUMMON_SYLVANAS, 1000);
                                        return;
                                    }
                                }
                                else
                                    me->DespawnOrUnsummon();

                                if (Creature* sylvanas = me->SummonCreature(NPC_LADY_SYLVANAS, -1566.409f, 1554.511f, 29.32553f, 3.94f, TEMPSUMMON_TIMED_DESPAWN, 300000))
                                {
                                    sylvanasGUID = sylvanas->GetGUID();
                                    sylvanas->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                                    events.ScheduleEvent(EVENT_SYLVANAS_ON_POISITON, sylvanas->GetSplineDuration() + 250);
                                }

                                if (Creature* warhowl = me->SummonCreature(NPC_GENERAL_WARHOWL, -1564.498f, 1555.956f, 29.32091f, 3.94f, TEMPSUMMON_TIMED_DESPAWN, 300000))
                                {
                                    warhowlGUID = warhowl->GetGUID();
                                    warhowl->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                                }

                                if (Creature* crenshaw = me->SummonCreature(NPC_HIGH_EXECUTOR_CRENSHAW, -1566.795f, 1555.3f, 29.36808f, 3.94f, TEMPSUMMON_TIMED_DESPAWN, 300000))
                                {
                                    crenshawGUID = crenshaw->GetGUID();
                                    crenshaw->GetMotionMaster()->MoveSplinePath(1, false, true, 0.f, false, false);
                                }

                                events.ScheduleEvent(EVENT_CHECK_PLAYER_POSITION, 3500);
                            }
                            break;
                        case EVENT_CHECK_PLAYER_POSITION:
                            {
                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                {
                                    if (Player* player = summoner->ToPlayer())
                                    {
                                        if (!player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
                                        {
                                            if (player->GetQuestStatus(QUEST_THE_HUNT_FOR_SYLVANAS) == QUEST_STATUS_INCOMPLETE)
                                                player->FailQuest(QUEST_THE_HUNT_FOR_SYLVANAS);

                                            if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                            {
                                                sylvanas->CastSpell(player, SPELL_SHOOT, false);
                                                sylvanas->DespawnOrUnsummon(5000);
                                            }

                                            if (Creature* warhowl = ObjectAccessor::GetCreature(*me, warhowlGUID))
                                                warhowl->DespawnOrUnsummon(5000);

                                            if (Creature* crenshaw = ObjectAccessor::GetCreature(*me, crenshawGUID))
                                                crenshaw->DespawnOrUnsummon(5000);

                                            me->DespawnOrUnsummon(5000);
                                            events.Reset();
                                            return;
                                        }
                                    }
                                }

                                events.ScheduleEvent(EVENT_CHECK_PLAYER_POSITION, 250);
                            }
                            break;
                        case EVENT_SYLVANAS_ON_POISITON:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    sylvanas->SetFacingTo(0.8028514f);

                                events.ScheduleEvent(EVENT_WARHOWL_TALK_LOSING, 1500);
                            }
                            break;
                        case EVENT_WARHOWL_TALK_LOSING:
                            {
                                if (Creature* warhowl = ObjectAccessor::GetCreature(*me, warhowlGUID))
                                    if (warhowl->IsAIEnabled)
                                        warhowl->AI()->Talk(WARHOWL_SAY_LOSING, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_SYLVANAS_TALK_ASSURE, 8000);
                            }
                            break;
                        case EVENT_SYLVANAS_TALK_ASSURE:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    if (sylvanas->IsAIEnabled)
                                        sylvanas->AI()->Talk(SYLVANAS_SAY_ASSURE, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_WARHOWL_TALK_PLAGUE, 6000);
                            }
                            break;
                        case EVENT_WARHOWL_TALK_PLAGUE:
                            {
                                if (Creature* warhowl = ObjectAccessor::GetCreature(*me, warhowlGUID))
                                    if (warhowl->IsAIEnabled)
                                        warhowl->AI()->Talk(WARHOWL_SAY_PLAGUE, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_SYLVANAS_TALK_TONE, 10000);
                            }
                            break;
                        case EVENT_SYLVANAS_TALK_TONE:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    if (sylvanas->IsAIEnabled)
                                        sylvanas->AI()->Talk(SYLVANAS_SAY_TONE, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_WARHOWL_TALK_GOOD_BY, 12000);
                            }
                            break;
                        case EVENT_WARHOWL_TALK_GOOD_BY:
                            {
                                if (Creature* warhowl = ObjectAccessor::GetCreature(*me, warhowlGUID))
                                    if (warhowl->IsAIEnabled)
                                        warhowl->AI()->Talk(WARHOWL_SAY_GOOD_BY, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_SYLVANAS_TALK_GO_WITH_HONOR, 12000);
                            }
                            break;
                        case EVENT_SYLVANAS_TALK_GO_WITH_HONOR:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    if (sylvanas->IsAIEnabled)
                                        sylvanas->AI()->Talk(SYLVANAS_SAY_GO_WITH_HONOR, me->ToTempSummon()->GetSummonerGUID(), true);

                                if (Creature* warhowl = ObjectAccessor::GetCreature(*me, warhowlGUID))
                                {
                                    warhowl->GetMotionMaster()->MoveSplinePath(2, false, true, 0.f, false, false);
                                    warhowl->DespawnOrUnsummon(warhowl->GetSplineDuration());
                                }

                                events.ScheduleEvent(EVENT_CRENSHAW_WALK_TO_SYLVANAS, 3500);
                            }
                            break;
                        case EVENT_CRENSHAW_WALK_TO_SYLVANAS:
                            {
                                if (Creature* crenshaw = ObjectAccessor::GetCreature(*me, crenshawGUID))
                                {
                                    crenshaw->GetMotionMaster()->MoveSplinePath(2, false, true, 0.f, false, false);
                                    events.ScheduleEvent(EVENT_CRENSHAW_TALK_ORDER, crenshaw->GetSplineDuration() + 250);
                                }
                            }
                            break;
                        case EVENT_CRENSHAW_TALK_ORDER:
                            {
                                if (Creature* crenshaw = ObjectAccessor::GetCreature(*me, crenshawGUID))
                                    if (crenshaw->IsAIEnabled)
                                        crenshaw->AI()->Talk(CRENSHAW_SAY_ORDER, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_SYLVANAS_TALK_WHAT_QUESTION, 9000);
                            }
                            break;
                        case EVENT_SYLVANAS_TALK_WHAT_QUESTION:
                            {
                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                    if (sylvanas->IsAIEnabled)
                                        sylvanas->AI()->Talk(SYLVANAS_SAY_WHAT_QUESTION, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_CRENSHAW_TALK_AS_YOU_WISH, 12000);
                            }
                            break;
                        case EVENT_CRENSHAW_TALK_AS_YOU_WISH:
                            {
                                if (Creature* crenshaw = ObjectAccessor::GetCreature(*me, crenshawGUID))
                                    if (crenshaw->IsAIEnabled)
                                        crenshaw->AI()->Talk(CRENSHAW_AS_YOU_WISH, me->ToTempSummon()->GetSummonerGUID(), true);

                                if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, sylvanasGUID))
                                {
                                    sylvanas->GetMotionMaster()->MoveSplinePath(2, false, true, 0.f, false, false);
                                    sylvanas->DespawnOrUnsummon(sylvanas->GetSplineDuration());
                                }

                                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                    if (Player* player = summoner->ToPlayer())
                                        player->CompleteQuest(QUEST_THE_HUNT_FOR_SYLVANAS);

                                events.ScheduleEvent(EVENT_CRENSHAW_WALK_AWAY, 7000);
                            }
                            break;
                        case EVENT_CRENSHAW_WALK_AWAY:
                            {
                                if (Creature* crenshaw = ObjectAccessor::GetCreature(*me, crenshawGUID))
                                {
                                    crenshaw->GetMotionMaster()->MoveSplinePath(3, false, true, 0.f, false, false);
                                    crenshaw->DespawnOrUnsummon(crenshaw->GetSplineDuration());
                                }

                                me->DespawnOrUnsummon(10000);
                            }
                            break;
                    }
                }
            }
        };
};

// Quest Slowing the Inevitable 24920
enum
{
    ACTION_FLY_BACK = 1,
};

class npc_captured_riding_bat final : public CreatureScript
{
    public:
        npc_captured_riding_bat() : CreatureScript("npc_captured_riding_bat") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                EVENT_START_RIDE    = 1,
                EVENT_MOVE_CYCLE    = 2,
                EVENT_FLY_BACK      = 3,
            };

            EventMap events;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->setActive(true);
            }

            void IsSummonedBy(Unit* summoner) final
            {
                events.ScheduleEvent(EVENT_START_RIDE, 1000);
            }

            void DoAction(int32 const action) final
            {
                if (action == ACTION_FLY_BACK)
                {
                    me->StopMoving();
                    float x, y;
                    me->GetNearPoint2D(x, y, 5.f, me->GetOrientation());
                    me->GetMotionMaster()->MovePoint(0, x, y, 165.f);
                    events.Reset();
                    events.ScheduleEvent(EVENT_FLY_BACK, me->GetSplineDuration() + 250);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_RIDE:
                            me->GetMotionMaster()->MoveSplinePath(1, true, true, 20.f);
                            events.ScheduleEvent(EVENT_MOVE_CYCLE, me->GetSplineDuration() - 250);
                            break;
                        case EVENT_MOVE_CYCLE:
                            me->GetMotionMaster()->MoveSplinePath(2, true, true, 20.f);
                            events.ScheduleEvent(EVENT_MOVE_CYCLE, me->GetSplineDuration() - 250);
                            break;
                        case EVENT_FLY_BACK:
                            me->GetMotionMaster()->MoveSplinePath(3, true, true, 20.f);
                            me->DespawnOrUnsummon(me->GetSplineDuration() + 250);
                            break;
                    }
                }
            }
        };
};

class spell_gilneas_bat_fly_back final : public SpellScriptLoader
{
    public:
        spell_gilneas_bat_fly_back() : SpellScriptLoader("spell_gilneas_bat_fly_back") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ExtraEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Creature* creature = GetHitCreature())
                    if (creature->IsAIEnabled)
                        creature->GetAI()->DoAction(ACTION_FLY_BACK);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ExtraEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

const float CatapultCheckPos[5][2]=
{
    {-1274.92f, 1632.53f},
    {-1260.25f, 1580.49f},
    {-1256.74f, 1683.23f},
    {-1285.08f, 1708.93f},
    {-1291.34f, 1721.51f},
};

class npc_forsaken_catapult_sti final : public CreatureScript
{
    public:
        npc_forsaken_catapult_sti() : CreatureScript("npc_forsaken_catapult_sti") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                SPELL_PLAGUE_BARREL_LAUNCH  = 71804,

                EVENT_CAST_BARREL           = 1,
            };

            EventMap events;

            void InitializeAI() final
            {
                for (int i = 0; i < 5; ++i)
                {
                    if (me->GetExactDist2dSq(CatapultCheckPos[i][0], CatapultCheckPos[i][1]) < 500.f)
                    {
                        me->setActive(true);
                        events.ScheduleEvent(EVENT_CAST_BARREL, urand(2500, 7500));
                        return;
                    }
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_CAST_BARREL)
                {
                    float x, y, z;
                    me->GetNearPoint2D(x, y, frand(120.f, 140.f), me->GetOrientation());
                    z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                    me->CastSpell(x, y, z, SPELL_PLAGUE_BARREL_LAUNCH, false);
                    events.ScheduleEvent(EVENT_CAST_BARREL, urand(2500, 7500));
                }
            }
        };
};

// Quest Knee-Deep 24678
class npc_knee_deep_attacker final : public CreatureScript
{
    public:
        npc_knee_deep_attacker() : CreatureScript("npc_knee_deep_attacker") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            enum
            {
                SPELL_SWING_TORCH   = 70631,

                EVENT_UNFEAR        = 1,
            };

            EventMap events;

            void SpellHit(Unit* caster, const SpellInfo* spell) final
            {
                if (spell->Id == SPELL_SWING_TORCH)
                {
                    EnterEvadeMode();
                    me->SetReactState(REACT_PASSIVE);
                    events.RescheduleEvent(EVENT_UNFEAR, 7000);
                }
            }

            void EnterCombat(Unit* /*who*/) final
            {
                me->setAttackTimer(BASE_ATTACK, 5000);
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (events.ExecuteEvent() == EVENT_UNFEAR)
                    me->SetReactState(REACT_AGGRESSIVE);

                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

// Quest Patriarch's Blessing 24679
enum qPB
{
    SPELL_FADE_TO_BLACK            = 89404,
    SPELL_MIRROR_IMAGE             = 45204,

    GREYMANE_SAY_QPB_1             = -1977147,
    GREYMANE_SAY_QPB_2             = -1977148,
    GREYMANE_SAY_QPB_3             = -1977149,
    LORNA_SAY_QPB                  = -1977150,
    CROWLEY_SAY_QPB                = -1977151,

    GO_OFFERINGS                   = 202319,
};

class npc_gilneas_funeral_camera final : public CreatureScript
{
    public:
        npc_gilneas_funeral_camera() : CreatureScript("npc_gilneas_funeral_camera") { }

    private:
        class TeleportEvent final : public BasicEvent
        {
            public:
                TeleportEvent(Unit* unit)
                    : _unit(unit)
                { }

            private:
                bool Execute(uint64 /*time*/, uint32 /*diff*/) final
                {
                    _unit->NearTeleportTo(-1724.116f, 1871.721f, 17.787f, 3.125f);
                    return true;
                }

                Unit* _unit;
        };

        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl(creature);
        }

        struct creature_script_impl final : public VehicleAI
        {
            creature_script_impl(Creature* creature) : VehicleAI(creature) { }

            enum
            {
                NPC_GILNEAS_FUNERAL_CAMERA  = 51083,
                NPC_KING_GENN_GREYMANE      = 50893,
                NPC_LORD_DARIUS_CROWLEY     = 50902,
                NPC_LORNA_CROWLEY           = 50881,
                NPC_CLONE                   = 51146,

                EVENT_START_CAMERA      = 1,
                EVENT_GREYMANE_SAY_1    = 2,
                EVENT_GREYMANE_SAY_2    = 3,
                EVENT_LORNA_SAY         = 4,
                EVENT_CROWLEY_SAY       = 5,
                EVENT_GREYMANE_SAY_3    = 6,
                EVENT_DONE              = 7,

                GREYMANE_SAY_1          = 1,
                GREYMANE_SAY_2          = 2,
                GREYMANE_SAY_3          = 3,
                LORNA_SAY               = 1,
                CROWLEY_SAY             = 1,
            };

            EventMap events;
            uint64 greymaneGUID;
            uint64 lornaGUID;
            uint64 crowleyGUID;
            uint64 cloneGUID;

            void InitializeAI() final
            {
                ASSERT(me->IsSummon());
            }

            void IsSummonedBy(Unit* summoner) final
            {
                me->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, summoner->GetGUID());
                me->SetPhaseMask(540672, true);
                events.ScheduleEvent(EVENT_START_CAMERA, 2000);
            }

            void JustSummoned(Creature* summoned) final
            {
                summoned->SetCustomVisibility(CUSTOM_VISIBILITY_SEER | CUSTOM_VISIBILITY_CREATURE, me->ToTempSummon()->GetSummonerGUID());

                switch (summoned->GetEntry())
                {
                    case NPC_CLONE:
                        {
                            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                summoned->CastSpell(summoner, 93995, false);

                            cloneGUID = summoned->GetGUID();
                        }
                        break;
                    case NPC_KING_GENN_GREYMANE:
                        greymaneGUID = summoned->GetGUID();
                        break;
                    case NPC_LORD_DARIUS_CROWLEY:
                        crowleyGUID = summoned->GetGUID();
                        break;
                    case NPC_LORNA_CROWLEY:
                        lornaGUID = summoned->GetGUID();
                        break;
                }
            }

            void PassengerWillBoard(Unit* passenger, Position& enterPos, int8 seatId) final
            {
                passenger->m_movementInfo.t_pos.Relocate(2.009521f, 1.367432f, -0.03686714f);
                enterPos.Relocate(2.009521f, 1.367432f, -0.03686714f);
            }

            void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) final
            {
                if (!apply)
                {
                    events.Reset();
                    who->CastSpell(who, SPELL_FADE_TO_BLACK, false);
                    who->RemoveAurasByType(SPELL_AURA_PHASE);
                    who->CastSpell(who, SPELL_ZONE_SPECIFIC_14, false);
                    who->m_Events.AddEvent(new TeleportEvent(who), who->m_Events.CalculateTime(250));

                    if (Player* player = who->ToPlayer())
                        player->SaveToDB();

                    if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                        greymane->DespawnOrUnsummon();

                    if (Creature* crowley = ObjectAccessor::GetCreature(*me, crowleyGUID))
                        crowley->DespawnOrUnsummon();

                    if (Creature* lorna = ObjectAccessor::GetCreature(*me, lornaGUID))
                        lorna->DespawnOrUnsummon();

                    if (Creature* clone = ObjectAccessor::GetCreature(*me, cloneGUID))
                        clone->DespawnOrUnsummon();

                    me->ForcedDespawn(500);
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                events.Update(diff);

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_CAMERA:
                            me->CastSpell((Unit*)NULL, 94251, false);
                            me->CastSpell((Unit*)NULL, 94253, false, NULL, NULL, me->GetGUID());
                            me->CastSpell((Unit*)NULL, 94255, false, NULL, NULL, me->GetGUID());
                            me->CastSpell((Unit*)NULL, 94257, false, NULL, NULL, me->GetGUID());
                            me->CastSpell((Unit*)NULL, 94247, false, NULL, NULL, me->GetGUID());
                            events.ScheduleEvent(EVENT_GREYMANE_SAY_1, 7000);
                            break;
                        case EVENT_GREYMANE_SAY_1:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GREYMANE_SAY_1, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_GREYMANE_SAY_2, 9000);
                            }
                            break;
                        case EVENT_GREYMANE_SAY_2:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GREYMANE_SAY_2, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_LORNA_SAY, 7000);
                            }
                            break;
                        case EVENT_LORNA_SAY:
                            {
                                if (Creature* lorna = ObjectAccessor::GetCreature(*me, lornaGUID))
                                    if (lorna->IsAIEnabled)
                                        lorna->AI()->Talk(LORNA_SAY, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_CROWLEY_SAY, 9000);
                            }
                            break;
                        case EVENT_CROWLEY_SAY:
                            {
                                if (Creature* crowley = ObjectAccessor::GetCreature(*me, crowleyGUID))
                                    if (crowley->IsAIEnabled)
                                        crowley->AI()->Talk(CROWLEY_SAY, me->ToTempSummon()->GetSummonerGUID(), true);

                                if (Creature* clone = ObjectAccessor::GetCreature(*me, cloneGUID))
                                    clone->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);

                                events.ScheduleEvent(EVENT_GREYMANE_SAY_3, 5000);
                            }
                            break;
                        case EVENT_GREYMANE_SAY_3:
                            {
                                if (Creature* greymane = ObjectAccessor::GetCreature(*me, greymaneGUID))
                                    if (greymane->IsAIEnabled)
                                        greymane->AI()->Talk(GREYMANE_SAY_3, me->ToTempSummon()->GetSummonerGUID(), true);

                                events.ScheduleEvent(EVENT_DONE, 7000);
                            }
                            break;
                        case EVENT_DONE:
                            {
                                if (Vehicle* vehicle = me->GetVehicleKit())
                                    vehicle->RemoveAllPassengers();
                            }
                            break;
                    }
                }
            }
        };
};

class spell_place_blessed_offerings final : public SpellScriptLoader
{
    public:
        spell_place_blessed_offerings() : SpellScriptLoader("spell_place_blessed_offerings") { }

    private:
        class spell_place_blessed_offerings_SpellScript final : public SpellScript
        {
            PrepareSpellScript(spell_place_blessed_offerings_SpellScript)

            void SummonOfferings(SpellEffIndex effIndex)
            {
                enum
                {
                    SPELL_SUMMON_FUNERAL_EVENT_CAMERA   = 94244,
                };

                if (Unit* caster = GetCaster())
                    caster->CastSpell(caster, SPELL_SUMMON_FUNERAL_EVENT_CAMERA, true);
            }

            void Register() final
            {
                OnEffectLaunch += SpellEffectFn(spell_place_blessed_offerings_SpellScript::SummonOfferings, EFFECT_0, SPELL_EFFECT_TRANS_DOOR);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_place_blessed_offerings_SpellScript();
        }
};

class spell_reverse_cast_mirror_image final : public SpellScriptLoader
{
    public:
        spell_reverse_cast_mirror_image() : SpellScriptLoader("spell_reverse_cast_mirror_image") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!(caster && target))
                    return;

                target->CastSpell(caster, GetSpellInfo()->Effects[effIndex].BasePoints, false);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class spell_gilneas_mirror_image final : public SpellScriptLoader
{
    public:
        spell_gilneas_mirror_image() : SpellScriptLoader("spell_gilneas_mirror_image") { }

    private:
        class spell_script_impl final : public SpellScript
        {
            PrepareSpellScript(spell_script_impl)

            void ScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Unit* caster = GetCaster();
                Unit* target = GetHitUnit();

                if (!(caster && target))
                    return;

                target->CastSpell(caster, GetSpellInfo()->Effects[effIndex].BasePoints, false);
            }

            void Register() final
            {
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
                OnEffectHitTarget += SpellEffectFn(spell_script_impl::ScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const final
        {
            return new spell_script_impl();
        }
};

class npc_gilneas_towering_ancient final : public CreatureScript
{
    public:
        npc_gilneas_towering_ancient() : CreatureScript("npc_gilneas_towering_ancient") { }

    private:
        CreatureAI* GetAI(Creature* creature) const final
        {
            return new creature_script_impl (creature);
        }

        struct creature_script_impl final : public ScriptedAI
        {
            creature_script_impl(Creature* creature) : ScriptedAI(creature) { }

            void InitializeAI() final
            {
                SetCombatMovement(false);
            }

            void DamageTaken(Unit* attacker, uint32 &damage) final
            {
                if (attacker->GetTypeId() == TYPEID_UNIT && !attacker->isPet())
                {
                    if (me->GetHealth() < me->GetMaxHealth() || me->GetHealth() <= damage)
                    {
                        damage = 0;
                        me->getThreatManager().addThreat(attacker, 0.f);
                    }
                }
            }

            void UpdateAI(uint32 const diff) final
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_admiral_nightwind final : public CreatureScript
{
    public:
        npc_admiral_nightwind() : CreatureScript("npc_admiral_nightwind") { }

    private:
        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) final
        {
            if (quest->GetQuestId() == 14434)
            {
                player->RemoveAurasByType(SPELL_AURA_PHASE);
                player->RemoveAurasByType(SPELL_AURA_MOD_INVISIBILITY_DETECT);
                WorldLocation loc;
                loc.m_mapId = 1;
                loc.m_positionX = 8181.06f;
                loc.m_positionY = 1001.92f;
                loc.m_positionZ = 7.0589f;
                player->TeleportTo(loc);
                player->SetHomebind(loc, 702);
                player->SaveToDB();
            }

            return false;
        }
};

void AddSC_gilneas()
{
    new npc_jack_derrington();
    new npc_gilneas_tremors_credit();
    new npc_gilnean_crow();
    new npc_prince_liam_greymane_phase_1();
    new npc_gilneas_city_guard_gate();
    new npc_panicked_citizen_gate();
    new npc_lieutenant_walden();
    new npc_gilneas_worgen();
    new npc_gilneas_city_guard("npc_gilneas_city_guard_default", SPELL_GUARD_SHOOT_DEFAULT);
    new npc_gilneas_city_guard("npc_gilneas_city_guard_deadly", SPELL_GUARD_SHOOT_DEADLY);
    new npc_prince_liam_greymane_phase_2();
    new npc_qems_citizen();
    new npc_qems_worgen();
    new npc_gilneas_class_trainer("npc_huntsman_blake", QUEST_STEADY_SHOT);
    new npc_gilneas_class_trainer("npc_vitus_darkwalker", QUEST_IMMOLATE);
    new npc_gilneas_class_trainer("npc_loren_the_fence", QUEST_EVISCERATE);
    new npc_gilneas_class_trainer("npc_sister_almyra", QUEST_FLASH_HEAL);
    new npc_gilneas_class_trainer("npc_celestine_of_the_harves", QUEST_A_REJUVENATING_TOUCH);
    new npc_myriam_spellwaker();
    new npc_sergeant_cleese();
    new npc_gilneas_worgen_class_quest();
    new npc_wounded_guard_class_quest();
    new npc_king_genn_greymane_phase_2();
    new npc_worgen_attacker_right();
    new npc_worgen_attacker_left();
    new npc_lord_darius_crowley();
    new npc_josiah_avery_worgen();
    new npc_josiah_event_trigger();
    new npc_josiah_avery_human();
    new npc_lorna_crowley_phase_3();
    new npc_bloodfang_lurker();
    new npc_king_genn_greymane_phase_3();
    new npc_vehicle_genn_horse();
    new npc_saved_aranas();
    new npc_lord_godfrey_phase_3();
    new npc_cannon_camera();
    new npc_gilneas_city_guard_phase_4();
    new npc_king_genn_greymane_phase_4();
    new npc_crowley_horse_first_round();
    new npc_crowley_horse_second_round();
    new npc_bloodfang_stalker();
    new npc_rebel_cannon_phase_4();
    new npc_lord_darius_crowley_phase_5();
    new npc_krennan_aranas_last_stand();
    new npc_king_genn_greymane_last_stand();
    new npc_slain_watchman();
    new npc_gwen_armstead_phase_6();
    new npc_forsaken_assassin();
    new npc_horrid_abomination();
    new npc_prince_liam_greymane_phase_7();
    new npc_gilneas_children_phase_7("npc_james", SPELL_SAVE_JAMES, PLAYER_SAY_JAMES);
    new npc_gilneas_children_phase_7("npc_ashley", SPELL_SAVE_ASHLEY, PLAYER_SAY_ASHLEY);
    new npc_gilneas_children_phase_7("npc_cynthia", SPELL_SAVE_CYNTHIA, PLAYER_SAY_CYNTHIA);
    new npc_forsaken_invader();
    new npc_forsaken_catapult_phase_7();
    new npc_gilneas_forsaken_captain();
    new npc_dark_ranger_thyala();
    new npc_attack_mastiff();
    new npc_lord_godfrey_phase_7();
    new npc_drowning_watchman();
    new npc_duskhaven_watchman_rescuer_phase_8();
    new npc_mountain_horse_vehicle();
    new npc_mountain_horse_follower();
    new npc_wahl();
    new npc_lucius_the_cruel();
    new npc_chance_the_cat();
    new npc_hayward_brother();
    new npc_swift_mountain_horse();
    new npc_gwen_armstead_phase_8();
    new npc_king_genn_greymane_c3() ;
    new npc_stagecoach_harness_summoner();
    new npc_stagecoach_carriage_summoner();
    new npc_stagecoach_harness_escort();
    new npc_stagecoach_carriage_escort();
    new npc_crash_survivor();
    new npc_swamp_crocolisk();
    new npc_prince_liam_greymane_qiao();
    new npc_koroth_the_hillbreaker_friend();
    new npc_captain_asther_qiao();
    new npc_koroth_the_hillbreaker();
    new npc_dark_scout();
    new npc_lord_darius_crowley_qaod();
    new npc_tobias_mistmantle_qaod();
    new npc_taldoren_tracker();
    new npc_tobias_mistmantle_qtbwo();
    new npc_lord_godfrey_qnhnb();
    new npc_lorna_crowley_qnhnb();
    new npc_king_genn_greymane_qnhnb();
    new npc_krennan_aranas_qbatr();
    new npc_king_genn_greymane_qbatr();
    new npc_lord_godfrey_qbatr();
    new npc_gilneas_betrayer_lord("npc_gilneas_betrayer_lord_walden",SPELL_INVISIBILITY_DETECTION_2);
    new npc_gilneas_betrayer_lord("npc_gilneas_betrayer_baron_ashbury",SPELL_INVISIBILITY_DETECTION_3);
    new npc_lord_hewell();
    new npc_stout_mountain_horse();
    new npc_lorna_crowley_livery_outpost();
    new npc_krennan_aranas_tbfgc();
    new npc_prince_liam_greymane_tbfgc();
    new npc_myriam_spellwaker_tbfgc();
    new npc_sister_almyra_tbfgc();
    new npc_gilnean_militia_tbfgc();
    new npc_dark_ranger_elite_tbfgc();
    new npc_lorna_crowley_tbfgc();
    new npc_emberstone_cannon_tbfgc();
    new npc_gilneas_forsaken_crossbowman_tbfgc();
    new npc_lord_darius_crowley_tbfgc();
    new npc_worgen_warrior_tbfgc();
    new npc_gorerot_tbfgc();
    new npc_damaged_catapult_tbfgc();
    new npc_king_genn_greymane_tbfgc();
    new npc_lady_sylvanas_windrunner_tbfgc();
    new npc_lorna_crowley_qthfs();
    new npc_tobias_mistmantle_qthfs();
    new npc_captured_riding_bat();
    new npc_forsaken_catapult_sti();
    new npc_knee_deep_attacker();
    new npc_gilneas_funeral_camera();
    new npc_gilneas_towering_ancient();
    new npc_admiral_nightwind();

    new go_crate_of_mandrake_essence();
    new go_koroth_banner();
    new go_qnhnb_well("go_well_of_fury", NPC_LYROS_SWIFTWIND, 0);
    new go_qnhnb_well("go_well_of_tranquility", NPC_VASSANDRA_STORMCLAW, 1);
    new go_qnhnb_well("go_well_of_balance", NPC_TALRAN_OF_THE_WILD, 2);

    new at_losing_your_tail();

    new spell_gilneas_knocking();
    new spell_gilneas_prison_periodic_dummy();
    new spell_force_cast_summon_josiah();
    new spell_quest_dismiss_plaguehound();
    new spell_forcecast_cannon_camera();
    new spell_forcecast_summon_crowleys_horse();
    new spell_worgen_intro_completion();
    new spell_curse_of_the_worgen_invis();
    new spell_gilneas_horrid_abomination_explosion();
    new spell_gilneas_forsaken_catapult_launch();
    new spell_call_attack_mastiffs();
    new spell_gilneas_cataclysm_phase_7();
    new spell_round_up_horse();
    new spell_belysras_talisman();
    new spell_horn_of_taldoren();
    new spell_retreat_trackers();
    new spell_gilneas_pings_crowley("spell_greymane_lorna_crowley", CROWLEY_YELL_LORNA);
    new spell_gilneas_pings_crowley("spell_greymane_godfrey_crowley", CROWLEY_YELL_FROG);
    new spell_gilneas_pings_crowley("spell_greymane_pings_crowley", CROWLEY_SAY_YES_GENN);
    new spell_gilneas_rescue_enslaved_villager();
    new spell_gilneas_bat_fly_back();
    new spell_place_blessed_offerings();
    new spell_reverse_cast_mirror_image();
    new spell_gilneas_mirror_image();
}
