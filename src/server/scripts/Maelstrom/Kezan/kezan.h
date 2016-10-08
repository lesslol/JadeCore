/*
 * Copyright (C) 2016 JadeCore <https://www.jadecore.tk/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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

/*#include "ScriptMgr.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "ScriptedVehicleEscortAI.h"
#include "ObjectMgr.h"
#include "Creature.h"
#include "SpellScript.h"
#include "ScriptedCreature.h"
#include "Object.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "Vehicle.h"
#include "Unit.h"

#ifndef DEF_KEZAN_H
#define DEF_KEZAN_H

enum eQuests
{
    QUEST_TROUBLE_IN_THE_MINES                 = 14075,
    QUEST_TAKING_CARE_OF_BUSINESS              = 14138,
    QUEST_KAJA_COLA                            = 25473,
    QUEST_MEGS_IN_MARKETING                    = 28349,
    QUEST_DO_IT_YOURSELF                       = 14070,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND            = 14069, 
    QUEST_ROLLING_WITH_MY_HOMIES               = 14071,
    QUEST_THE_REPLACEMENTS                     = 24488,
    QUEST_NECESSARY_ROUGHNESS                  = 24502,
    QUEST_FOURTH_AND_GOAL                      = 28414, // todo
    QUEST_OFF_TO_THE_BANK_FEMALE               = 26711,
    QUEST_OFF_TO_THE_BANK_MALE                 = 26712,
    QUEST_THE_NEW_YOU_FEMALE                   = 14110,
    QUEST_THE_NEW_YOU_MALE                     = 14109,
    QUEST_LIFE_OF_THE_PARTY_MALE               = 14113,
    QUEST_LIFE_OF_THE_PARTY_FEMALE             = 14153, // todo
    QUEST_PIRATE_PARTY_CRASHERS                = 14115,
    QUEST_THE_UNINVITED_GUEST                  = 14116,
    QUEST_A_BAZILLION_MACAROONS                = 14120,
    QUEST_ROBBING_HOODS                        = 14121,
    QUEST_THE_GREAT_BANK_HEIST                 = 14122,
    QUEST_WALTZ_RIGHT_IN                       = 14123,
    QUEST_LIBERATE_THE_KAJAMITE                = 14124, // todo
    QUEST_STEADY_SHOT                          = 14007,
    QUEST_ARCANE_MISSILES                      = 14008,
    QUEST_FLASH_HEAL                           = 14009,
    QUEST_EVISCERATE                           = 14010,
    QUEST_PRIMAL_STRIKE                        = 14011,
    QUEST_IMMOLATE                             = 14012,
    QUEST_CHARGE                               = 14013,
    QUEST_447                                  = 14125,
    QUEST_LIFE_SAVINGS                         = 14126,
};

enum eCreatures
{
    NPC_KEZAN_CITIZEN                          = 35063,
    NPC_DEFIANT_TROLL                          = 34830,
    NPC_HOT_ROD                                = 34840,
    NPC_ACE                                    = 34957,
    NPC_GOBBER                                 = 34958,
    NPC_IZZY                                   = 34959,
    NPC_INVIS_ACE                              = 34892,
    NPC_INVIS_GOBBER                           = 34954,
    NPC_INVIS_IZZY                             = 34890,
    NPC_HOTROD_KILL_CREDIT                     = 48323,
    NPC_COACH_CROSSCHECK                       = 37106,
    NPC_STEAMWHEEDLE_SHARK                     = 37114,
    NPC_FOURTH_AND_GOAL_TARGET                 = 37203,
    NPC_DEATHWING_QFAG                         = 48572,
    NPC_FBOK_BANK_TELLER                       = 35120,
    NPC_KEZAN_PARTYGOER_MALE                   = 35175,
    NPC_KEZAN_PARTYGOER_FEMALE                 = 35186,
    NPC_FIZZ_LIGHTER                           = 34689,
    NPC_EVOL_FINGERS                           = 34696,
    NPC_TRAINING_DUMMY                         = 48304,
    NPC_PIRATE_PARTY_CRASHER                   = 35200,
    NPC_ASSISTANT_GREELY                       = 48496,
    NPC_HOBART_GRAPPLEHAMMER                   = 48494,
    NPC_MICRO_MECHACHICKEN                     = 48519,
    NPC_ELM_GENERAL_PURPOSE_BUNNY              = 24021,
    NPC_OVERLOADED_GENERATOR                   = 37561,
    NPC_STOVE_LEAK                             = 37590,
    NPC_SMOLDERING_BED                         = 37594,
    NPC_GASBOT                                 = 37598,
    NPC_HOT_ROD_LS                             = 37676,
    NPC_CHIP_ENDALE                            = 35054,
    NPC_CANDY_CANE                             = 35053,
    NPC_VILLA_MOOK                             = 49218,
    NPC_CLAIMS_ADJUSTER                        = 37602,
    NPC_GASBOT_GAS_TARGET                      = 37599,
    NPC_BRUTE_ENFORCER                         = 35304,
    NPC_GOBLIN_SUPERMODEL                      = 37057,
    NPC_GOBLIN_SUPERMODEL_2                    = 37054,
    NPC_GOBLIN_SUPERMODEL_3                    = 37055,
    NPC_GOBLIN_SUPERMODEl_4                    = 37056,
    NPC_A_BAZILLION_MACAROONS_FIERY_BOULDER_CASTER = 37748,
    NPC_SASSY_HARDWRENCH                       = 37680,
    NPC_MOOK_DISGUISE                          = 48925,
    NPC_ELM_GENERAL_PURPOSE_BUNNY_NOT_FLOATING = 37046,
};

enum eSpells
{
    SPELL_SASSYS_INCENTIVE                     = 82025,
    SPELL_BELT_SHOCKER                         = 66306,
    SPELL_ENRAGE_QGHIHTF                       = 45111,
    SPELL_KEYS_TO_THE_HOT_ROD                  = 91551,
    SPELL_HOT_ROD_HONK_HORN                    = 66298,
    SPELL_HOT_ROD_KNOCKBACK                    = 66301,
    SPELL_BOOM_INVIS_MODEL                     = 68560,
    SPELL_ROCKET                               = 36628,
    SPELL_COLA_CAN                             = 75133,
    SPELL_PANICKED_CITIZEN_INVIS               = 90636,
    SPELL_THROW_FOOTBOMB                       = 69993,
    SPELL_PERMANENT_FEIGN_DEATH                = 29266,
    SPELL_INCREASED_MOD_DETECTED_RANGE         = 76651,
    SPELL_KICK_FOOTBOMB                        = 70052,
    SPELL_DEATHWINGS_ATTACK                    = 66858,
    SPELL_CHARACTER_EARTHQUAKE                 = 90615,
    SPELL_XPLOSION                             = 91117,
    SPELL_MARK                                 = 42171,
    SPELL_THROW_GEARS                          = 75775,
    SPELL_KNOCKBACK                            = 75986,
    SPELL_BUBBLE_BLAST                         = 75761,
    SPELL_FROSTBOLT                            = 9672,
    SPELL_CREATE_HIP_NEW_OUTFIT                = 66781,
    SPELL_CREATE_COOL_SHADES                   = 66782,
    SPELL_CREATE_SHINY_BLING                   = 66780,
    SPELL_BUBBLY                               = 66909,
    SPELL_BUCKET                               = 66910,
    SPELL_DANCE                                = 66911,
    SPELL_FIREWORKS                            = 66912,
    SPELL_HORS_DOEUVRES                        = 66913,
    AURA_HAPPY_PARTYGOER                       = 66916,
    AURA_PARTYGOER_BUBBLY                      = 75042,
    AURA_PARTYGOER_BUCKET                      = 75044,
    AURA_DRUNKEN_STUN                          = 46957,
    AURA_DRUNKEN_INTOXICATION                  = 55664,
    AURA_PARTYGOER_DANCE                       = 75046,
    AURA_PARTYGOER_FIREWORKS                   = 75048,
    AURA_PARTYGOER_HORS_DOEUVRES               = 75050,
    SPELL_PARTYGOER_BUBBLY                     = 75122,
    SPELL_PARTYGOER_SUMMON_BUCKET              = 66931,
    SPELL_PARTYGOER_VOMIT                      = 43391,
    SPELL_PARTYGOER_SUMMON_DISCO_BALL          = 66930,
    SPELL_PARTYGOER_DANCE                      = 75123,
    SPELL_PARTYGOER_HORS_DOEUVRES              = 75124,
    SPELL_PARTYGOER_FIREWORKS_BLUE             = 66917,
    SPELL_PARTYGOER_FIREWORKS_GREEN            = 66918,
    SPELL_PARTYGOER_FIREWORKS_RED              = 66919,
    SPELL_TGBH_SUMMON_BUNNY_VEHICLE            = 67488,
    SPELL_TGBH_BUNNY_DRILL_AURA                = 67495,
    SPELL_TGBH_BUNNY_EXPLOSIVES_AURA           = 67496,
    SPELL_TGBH_BUNNY_LISTEN_AURA               = 67497,
    SPELL_TGBH_BUNNY_LOCKPICK_AURA             = 67498,
    SPELL_TGBH_BUNNY_G_RAY_AURA                = 67499,
    SPELL_TGBH_POWER_CORRECT                   = 67493,
    SPELL_TGBH_POWER_INCORRECT                 = 67494,
    SPELL_INFINIFOLD_LOCKPICK                  = 67525,
    SPELL_BLASTCRACKERS                        = 67508,
    SPELL_KAJAMITE_DRILL                       = 67522,
    SPELL_AMAZING_G_RAY                        = 67526,
    SPELL_EAR_O_SCOPE                          = 67524,
    SPELL_TIMER                                = 67502,
    SPELL_THROW_SUPER_SPLODY_COCKTAIL          = 67020,
    SPELL_CREATE_STOLEN_LOOT                   = 67041,
    SPELL_POWER_WORD_FORTITUDE                 = 74973,
    SPELL_LIGHTNING_BOLT_FOR_FIZZ              = 69630,
    SPELL_LIGHTNING_BOLT_FOR_EVOL              = 69626,
    SPELL_FIREBALL                             = 45595,
    SPELL_SHADOW_BOLT                          = 33335,
    SPELL_SHOOT_GUN                            = 65977,
    SPELL_AWESOME_PARTY_ENSEMBLE               = 66908,
    SPELL_LOTP_OUTFIT_SECONDARY                = 66985,
    SPELL_LOTP_OUTFIT_FEMALE                   = 66927,
    SPELL_LOTP_OUTFIT_MALE                     = 66928,
    SPELL_LOTP_PAPARAZZI                       = 66929,
    SPELL_SUMMON_HOT_ROD                       = 66393,
    SPELL_SLEEP                                = 62248,
    SPELL_COSMETIC_POLYMORPH_IMPACT_VISUAL     = 65313,
    SPELL_LIGHTNING_IMPACT                     = 89139,
    SPELL_LIGHTNING_BEAM                       = 89138,
    SPELL_MECHACHICKEN_OVERLOAD                = 71423,
    SPELL_MICRO_MECHACHICKEN_GROW              = 89125,
    SPELL_STEALTH                              = 80264,
    SPELL_MECHACHICKEN_EXPLOSION               = 91390,
    SPELL_OVERLOADED_GENERATOR_VISUAL          = 70226,
    SPELL_STOVE_LEAK_VISUAL                    = 70236,
    SPELL_SMOLDERING_BED_PRECAST_MASTER        = 70251,
    SPELL_SMOLDERING_BED_VISUAL                = 70250,
    SPELL_LS_HOT_ROD_KNOCKBACK                 = 70330,
    SPELL_HOT_ROD_SKID                         = 70325,
    SPELL_LAST_CHANCE_YACHT_BOARDING_MORTAR    = 92633,
    SPELL_GASBOT_GAS_STREAM                    = 70256,
    SPELL_KAJA_COLA                            = 70483,
    SPELL_GAS_FIGHTER_GAS_STREAM               = 69813,
    SPELL_GAS_FIGHTER_GAS_HOSE                 = 69821,
    SPELL_PERMAMENT_FEIGN_DEATH                = 70112,
    SPELL_LIFE_SAVINGS_QUEST_COMPLETE          = 91847,
    SPELL_A_BAZILLION_MACAROONS_FIERY_BOULDER  = 70472,
    SPELL_DEATHWING_ATACK_LOOMING              = 94656,
    SPELL_VISUAL_START_FIRE_ROCKET_1           = 7071,
    SPELL_VISUAL_START_FIRE_ROCKET_2           = 12032,
    SPELL_DOWN_IN_THE_DEEPS_SPEEDBARAGE        = 88480,
    SPELL_COSMETIC_WATER_STEAM_IMPACT          = 73839,
    SPELL_WATER_EXPLOSION                      = 84376,
    SPELL_DUSTY_EXPLOSION                      = 84509,
    SPELL_VISUAL_BOOS_1                        = 1168,
    SPELL_VISUAL_BOOS_2                        = 6695,
    SPELL_VISUAL_CATS_MARK                     = 15652,
    SPELL_SWASHBUCKLING_SLICE                  = 75361,
    SPELL_GASBOT_EXPLOSION                     = 70259,
    SPELL_HONARTS_INGENIOUS_CAPOFMOOK_FOOLERY  = 67435,
    SPELL_FIERY_BOULDER                        = 70097,
    SPELL_FaG_SUMMON_BILGEWATER_BUCCANEER      = 70075,
    SPELL_NR_SUMMON_BILGEWATER_BUCCANEER       = 70015,
    SPELL_RADIO                                = 23406,

    PHASE_QUEST_ZONE_SPECIFIC_1                = 59073,
    PHASE_QUEST_ZONE_SPECIFIC_2                = 59074,
    PHASE_QUEST_ZONE_SPECIFIC_3                = 59087,
    PHASE_QUEST_ZONE_SPECIFIC_4                = 67789,
    PHASE_QUEST_ZONE_SPECIFIC_5                = 68480,
    PHASE_QUEST_ZONE_SPECIFIC_6                = 68481,
    PHASE_QUEST_ZONE_SPECIFIC_7                = 68482,
    PHASE_QUEST_ZONE_SPECIFIC_8                = 68483,

    SPELL_QUEST_INVISIBILITY_DETECTION_1       = 60922,
    SPELL_QUEST_INVISIBILITY_DETECTION_2       = 49417,
    SPELL_QUEST_INVISIBILITY_DETECTION_3       = 49416,
    SPELL_QUEST_INVISIBILITY_DETECTION_4       = 80818,
    SPELL_QUEST_INVISIBILITY_DETECTION_5       = 94704,
    SPELL_QUEST_INVISIBILITY_DETECTION_6       = 94567,

};

enum Data
{
    DATA_KNOCKBACK                             = 0,
    DATA_KNOCKBACK_NONE                        = 1,
    DATA_KNOCKBACK_KNOCKBACK                   = 2,
    DATA_KNOCKBACK_ALARM                       = 3,
    DATA_KNOCKBACK_IMMUNE                      = 4,

    ACTION_FAIL_NECESSARY_ROUGHNESS            = 1,
    TYPE_SEAT_CHANGE                           = 2,
    DATA_NONE                                  = 3,
    DATA_SEAT_IN_CHANGE                        = 4,
};

const uint32 Homies[3] =
{
    NPC_ACE,
    NPC_GOBBER,
    NPC_IZZY
};

const uint32 InvisHomies[3] =
{
    NPC_INVIS_ACE,
    NPC_INVIS_GOBBER,
    NPC_INVIS_IZZY
};

const uint64 DetectSpells[3] =
{
    SPELL_QUEST_INVISIBILITY_DETECTION_1,
    SPELL_QUEST_INVISIBILITY_DETECTION_2,
    SPELL_QUEST_INVISIBILITY_DETECTION_3
};

const uint16 RollingEmote[7] =
{
    EMOTE_ONESHOT_ROAR,
    EMOTE_ONESHOT_BATTLE_ROAR,
    EMOTE_ONESHOT_POINT,
    EMOTE_ONESHOT_RUDE,
    EMOTE_ONESHOT_LAUGH,
    EMOTE_ONESHOT_CRY,
    EMOTE_ONESHOT_COWER
};

const uint16 RollingEmoteState[7] =
{
    EMOTE_ONESHOT_CRY,
    EMOTE_STATE_STUN,
    EMOTE_STATE_DEAD,
    EMOTE_STATE_KNEEL,
    EMOTE_STATE_FALL,
    EMOTE_STATE_COWER,
    EMOTE_ONESHOT_KNOCKDOWN
};

static float CitizenAtTribune[8][3] =
{
    {-8259.96f, 1468.21f, 43.67f},
    {-8258.11f, 1499.26f, 43.61f},
    {-8265.65f, 1499.59f, 44.16f},
    {-8278.00f, 1499.43f, 44.89f},
    {-8285.91f, 1499.94f, 45.37f},
    {-8284.19f, 1468.88f, 44.88f},
    {-8277.95f, 1468.16f, 44.67f},
    {-8267.49f, 1467.81f, 44.14f},
};

static float CitizenInBank[12][3] =
{
    {-8373.08f, 1728.13f, 39.9428f},
    {-8369.11f, 1727.94f, 39.9818f},
    {-8364.33f, 1727.73f, 39.9517f},
    {-8360.16f, 1725.19f, 39.9468f},
    {-8356.08f, 1725.18f, 42.3415f},
    {-8346.05f, 1725.22f, 49.9416f},
    {-8351.53f, 1725.34f, 45.7875f},
    {-8339.41f, 1725.17f, 50.7469f},
    {-8362.91f, 1723.26f, 39.9479f},
    {-8368.51f, 1722.14f, 39.9835f},
    {-8373.52f, 1722.16f, 39.9445f},
    {-8331.84f, 1725.48f, 50.7286f},
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
    EMOTE_ONESHOT_EAT_NO_SHEATHE,
    EMOTE_ONESHOT_RUDE,
    EMOTE_ONESHOT_LAUGH,
    EMOTE_ONESHOT_YES,
    EMOTE_ONESHOT_WAVE,
    EMOTE_ONESHOT_SPELL_CAST_OMNI,
};

enum Sounds
{
    SOUND_BEEP                                 = 22491,
    SOUND_WOW_1                                = 17466,
    SOUND_WOW_2                                = 17467,
    DEATHWING_SOUND_1                          = 23227,
    DEATHWING_SOUND_2                          = 23229,
    DEATHWING_SOUND_3                          = 23230,
    SOUND_MECHANICAL_CHICKEN_SOUNDS            = 12205,
};

enum Menu
{
    SZABO_MENU_ID_1 = 14700,
    SZABO_MENU_ID_2 = 14701,
    MISSA_MENU_ID_1 = 14702,
    MISSA_MENU_ID_2 = 14703,
    GAPPY_MENU_ID_1 = 14704,
    GAPPY_MENU_ID_2 = 14705,
};

enum eItems
{
    ITEM_STOLEN_LOOT                           = 47530,
    ITEM_PERSONAL_RICHES                       = 46858,
    ITEM_HOTROAD_KEY                           = 46856,
    ITEM_NEW_OUTFIT                            = 47046,
    ITEM_COOL_SHADES                           = 47047,
    ITEM_SHINY_BLING                           = 47045,
};

enum objects
{
    GO_KAJAMITE_CHUNK                          = 195492,
};

enum eScriptTexts
{
    SASSY_SAY_LOL                              = -1987000,
    DAMPWICK_SAY_NICE                          = -1987001,
    DAMPWICK_YELL_OUCH                         = -1987002,
    DAMPWICK_SAY_OK                            = -1987003,
    DEFIANT_TROLL_RANDOM_SAY                   = -1987004,    // -1987004 to -19870011
    DAMPWICK_SAY_BOSS                          = -1987012,
    SASSY_SAY_LATER                            = -1987013,
    DREADSHREDDER_SAY_USE_KEYS                 = -1987014,
    PLAYER_RANDOM_YELL                         = -1987015,    // -1987015 to -1987034
    HOMIES_RANDOM_SAY                          = -1987035,    // -1987035 to -1987045
    HOMIES_RANDOM_ALARM                        = -1987046,    // -1987046 to -1987051
    CITIZEN_RANDOM_SAY                         = -1987052,    // -1987052 to -1987065
    CITIZEN_RANDOM_ALARM                       = -1987066,    // -1987066 to -1987070
    DREADSHREDDER_SAY_YOU_LIKE_IT              = -1987071,
    DREADSHREDDER_SAY_FINISH                   = -1987072,
    COACH_SAY_GOTTA_HURRY                      = -1987073,
    COACH_SAY_SHREDDER                         = -1987074,
    BUCCANEER_SAY_FOOTBOMBS                    = -1987075,
    BUCCANEER_SAY_FOOTBOMB                     = -1987076,
    DEATHWING_YELL                             = -1987077,
    COACH_NOT_AT_MY_FIELD                      = -1987078,
    PLAYER_SAY_WHAT_IS_THIS                    = -1987079,
    ACE_SAY_WHAT_IS_THIS                       = -1987080,
    IZZY_SAY_WHAT_IS_THIS                      = -1987081,
    COACH_SAY_GOOD_WORK                        = -1987082,
    NPC_BRUNO_SAY_1                            = -1987083,
    NPC_BRUNO_SAY_2                            = -1987084,
    NPC_FRANKIE_SAY_1                          = -1987085,
    NPC_FRANKIE_SAY_2                          = -1987086,
    NPC_JACK_SAY                               = -1987087,
    NPC_SUDSY_SAY_1                            = -1987088,
    NPC_SUDSY_SAY_2                            = -1987089,
    SASSY_SAY_HELP_HIM                         = -1987090,
    HOMIES_RANDOM_ATTACK_YELL                  = -1987091,    // -1987091 to -1987097
    CHIP_ENDALE_SAY_START                      = -1987098,
    CANDY_CANE_SAY_START                       = -1987099,
    FBOK_BANK_TELLER_SAY_NEXT                  = -1987100,
    FBOK_BANK_TELLER_SAY_COOL                  = -1987101,
    CITIZEN_SAY_SZABO_SO_COOL                  = -1987102,
    VAULT_SAY_BREAKING                         = -1987103,
    VAULT_SAY_USE_GOBLIN_ALL_IN_1_DER_BELT     = -1987104,
    VAULT_SAY_VAULT_WILL_BE_CRACKED            = -1987105,
    VAULT_SAY_GOOD_LUCK                        = -1987106,
    VAULT_SAY_USE_INFINIFOLD_LOCKPICK          = -1987107,
    VAULT_SAY_USE_BLASTCRACKERS                = -1987108,
    VAULT_SAY_USE_KAJAMITE_DRILL               = -1987109,
    VAULT_SAY_USE_AMAZING_G_RAY                = -1987110,
    VAULT_SAY_USE_EAR_O_SCOPE                  = -1987111,
    VAULT_SAY_SUCCESS                          = -1987112,
    VAULT_SAY_CORRECT                          = -1987113,
    VAULT_SAY_INCORRECT                        = -1987114,
    VAULT_SAY_EMPTY_TEXT                       = -1987115,
    VAULT_SAY_IS_NO_TIME                       = -1987116,
    SASSY_SAY_BREAK_YOUR_MOOLAH                = -1987117,
    BAMM_MEGABOMB_QUEST_ACCEPT                 = -1987118,
    FIZZ_LIGHTER_QUEST_ACCEPT                  = -1987119,
    SLINKY_SHARPSHIV_QUEST_ACCEPT              = -1987120,
    MAXX_AVALANCHE_QUEST_ACCEPT                = -1987121,
    EVOL_FINGERS_QUEST_ACCEPT                  = -1987122,
    WARRIOR_MATIC_NX_01_QUEST_ACCEPT           = -1987123,
    SISTER_GOLDSKIMMER_QUEST_ACCEPT            = -1987124,
    SISTER_GOLDSKIMMER_RANDOM_SPEACH           = -1987125,    // -1987125 to -1987131
    MAXX_AVALANCHE_RANDOM_SPEACH               = -1987132,    // -1987132 to -1987138
    CANDY_CANE_SAY_GO_TO_THE_PARTY             = -1987139,
    CANDY_CANE_EMOTE_GO                        = -1987140,
    CHIP_ENDALE_SAY_GO_TO_THE_PARTY            = -1987141,
    CHIP_ENDALE_EMOTE_GO                       = -1987142,
    PARTYGOER_RANDOM_SAY_NEED_HORS_DOEUVRES    = -1987143,    // -1987143 to -1987144
    PARTYGOER_RANDOM_SAY_NEED_BUBBLY           = -1987145,    // -1987145 to -1987146
    PARTYGOER_RANDOM_SAY_NEED_FIREWORKS        = -1987147,    // -1987147 to -1987148
    PARTYGOER_RANDOM_SAY_NEED_BUCKET           = -1987149,    // -1987149 to -1987150
    PARTYGOER_RANDOM_SAY_NEED_DANCE            = -1987151,    // -1987151 to -1987152
    PARTYGOER_RANDOM_SAY_OK_HORS_DOEUVRES      = -1987153,    // -1987153 to -1987155
    PARTYGOER_RANDOM_SAY_OK_BUBBLY             = -1987156,    // -1987156 to -1987158
    PARTYGOER_RANDOM_SAY_OK_FIREWORKS          = -1987159,    // -1987159 to -1987161
    PARTYGOER_RANDOM_SAY_OK_BUCKET             = -1987162,    // -1987162 to -1987165
    PARTYGOER_RANDOM_SAY_OK_DANCE              = -1987166,    // -1987166 to -1987168
    PIRATE_PARTY_CRASHER_RANDOM_SAY            = -1987169,    // -1987169 to -1987176
    HOBART_YELL_PREPARE                        = -1987177,
    GREELY_SAY_SHEESH                          = -1987178,
    GREELY_SAY_ONE_MECHACHICKEN                = -1987179,
    HOBART_SAY_DEAR_GREELY                     = -1987180,
    GREELY_SIGH                                = -1987181,
    GREELY_SAY_YES_DOCTOR                      = -1987182,
    HOBART_SAY_EXCELLENT                       = -1987183,
    GREELY_SHAKES_HEAD                         = -1987184,
    HOBART_SAY_THANK_YOU                       = -1987185,
    HOBART_SAY_HORRIBLE_PROBLEM                = -1987186,
    HOBART_SAY_GREATEST_GOBLIN                 = -1987187,
    HOBART_SAY_FLIP_THE_SWITCH                 = -1987188,
    GREELY_COUGHS                              = -1987189,
    GREELY_SAY_AT_THE_CONTROLS                 = -1987190,
    HOBART_SAY_QUITE_RIGHT                     = -1987191,
    HOBART_SAY_FLIPPING                        = -1987192,
    HOBART_SAY_CAN_YOU_FEEL                    = -1987193,
    HOBART_SAY_GROCERY_STORE                   = -1987194,
    HOBART_SAY_FLIPPING_SECOND                 = -1987195,
    HOBART_SAY_WAIT                            = -1987196,
    GREELY_SAY_YA_THINK                        = -1987197,
    HOBART_YELL_I_KNOW                         = -1987198,
    GREELY_YELL_FAR_RIGHT                      = -1987199,
    HOBART_YELL_I_ALWAYS_LOVED                 = -1987200,
    GREELY_YELL_WHAT                           = -1987201,
    HOBART_YELL_FLIPPING_THE_OVERRIDE          = -1987202,
    HOBART_SAY_ARE_WE_STILL_ALIVE              = -1987203,
    GREELY_SAY_WERE_STILL_ALIVE                = -1987204,
    HOBART_SAY_WELL_OF_COURSE                  = -1987205,
    GREELY_SAY_IS_THAT_EGG                     = -1987206,
    HOBART_OPEN_MOUTH                          = -1987207,
    GREELY_SAY_ALWAYS_LOVED                    = -1987208,
    HOBART_SAY_MISS_GREELY                     = -1987209,
    GREELY_BOTH_AGREE                          = -1987210,
    HOBART_SAY_SKY_IS_FALLING                  = -1987211,
    GREELY_SAY_SKY_IS_FALLING                  = -1987212,
    HOBART_SAY_GRAB_ONLY_THE_IMPORTANT         = -1987213,
    GREELY_SAY_GRAB_ONLY_THE_IMPORTANT         = -1987214,
    HOBART_SAY_PARTY                           = -1987215,
    GREELY_SAY_PARTY                           = -1987216,
    HOBART_SAY_DEATHWING                       = -1987217,
    GREELY_SAY_DEATHWING                       = -1987218,
    HOBART_SAY_GET_EVERYTHING_PACKED           = -1987219,
    GREELY_SAY_GET_EVERYTHING_PACKED           = -1987220,
    HOBART_SAY_SUBJECT_NINE                    = -1987221,
    GREELY_SAY_SUBJECT_NINE                    = -1987222,
    HOBART_SAY_SCHEMATICS                      = -1987223,
    GREELY_SAY_SCHEMATICS                      = -1987224,
    HOBART_SAY_INGENIOUS_CAP                   = -1987225,
    GREELY_SAY_INGENIOUS_CAP                   = -1987226,
    VINNY_SLAPCHOP_RANDOM_SAY                  = -1987227,    // -1987227 to -1987234
    KAJA_COLA_BALLOON_RANDOM_YELL              = -1987235,    // -1987235 to -1987242
    FOREMAN_DAMPWICK_RANDOM_YELL               = -1987243,    // -1987243 to -1987250
    GALLYWIX_RANDOM_YELL_FIRST_PHASE           = -1987251,    // -1987251 to -1987258
    GALLYWIX_RANDOM_YELL_SECOND_PHASE          = -1987259,    // -1987259 to -1987264
    KAJA_COLA_RANDOM_IDEA                      = -1987265,    // -1987265 to -1987323
    BRUTE_ENFORCER_FIRST_RANDOM_SAY            = -1987324,    // -1987324 to -1987327
    BRUTE_ENFORCER_SECOND_RANDOM_SAY           = -1987328,    // -1987328 to -1987331
    SASSY_SAY_CANT_LOOK                        = -1987332,
    CLAIMS_ADJUSTER_YELL_VICTIM                = -1987333,
    SASSY_SAY_GO_TO_THE_GALLYWIX_BOAT          = -1987334,
    SASSY_SAY_GO_AROUND                        = -1987335,
    SASSY_YELL_OUT_OF_THE_WAY                  = -1987336,
    SASSY_SAY_OH_NO                            = -1987337,
    CANDY_CANE_SAY_GAME_OVER                   = -1987338,
    CHIP_ENDALE_SAY_GAME_OVER                  = -1987339,
    JACK_THE_HAMMER_SAY_HAMMER                 = -1987340,
};

enum eFactions
{
    ORIGINAL_FACTION                           = 2159,
    AGGRESSIVE_FACTION                         = 14,
};

enum eArea
{
    AREA_KAJAMITE_MINE                         = 4766,
};

enum eMask
{
    CAN_SAY = 0x01,
    SAID = 0x02,
};

struct Psc_t
{
    uint64 uiPlayerGUID;
    uint32 uiEventTimer;
    uint8 uiEventMask;
};

struct Psc
{
    uint64 uiPlayerGUID;
    uint32 uiEventTimer;
    uint32 uiPhase;
};

struct Psc_ls
{
    uint64 uiPlayerGUID;
    uint32 uiPersonalTimer;
};

struct QFAG
{
    uint64 uiPlayerGUID;
    uint64 uiDeathwingGUID;
};

enum misc
{
    TYPE_BUBBLY                                 = 1,
    TYPE_BUCKET                                 = 2,
    TYPE_DANCE                                  = 3,
    TYPE_FIREWORKS                              = 4,
    TYPE_HORS_DOEUVRES                          = 5,

    VIRTUAL_ITEM_BUBBLY                         = 2718,
    VIRTUAL_ITEM_HORS_DOEUVRES                  = 2202,
    VIRTUAL_ITEM_FIREWORKS                      = 9701,

    ROLL_INFINIFOLD_LOCKPICK                    = 1,
    ROLL_BLASTCRACKERS                          = 2,
    ROLL_KAJAMITE_DRILL                         = 3,
    ROLL_AMAZING_G_RAY                          = 4,
    ROLL_EAR_O_SCOPE                            = 5,

    POINT_TESTING_PLATFORM                      = 1,
    POINT_BACK_OF_THE_DOCTOR_1                  = 2,
    POINT_RUN_AWAY_FROM_CHICKEN                 = 3,
    POINT_BACK_OF_THE_DICTOR_2                  = 4,
};

const uint16 LooterRandomEmote[6] =
{
    EMOTE_ONESHOT_APPLAUD,
    EMOTE_ONESHOT_DANCE,
    EMOTE_ONESHOT_RUDE,
    EMOTE_ONESHOT_ROAR,
    EMOTE_ONESHOT_CHEER,
    EMOTE_ONESHOT_LAUGH,
};

const uint16 TrollRandomEmoteState[4] =
{
    EMOTE_STATE_READY_UNARMED,
    EMOTE_STATE_DANCESPECIAL,
    EMOTE_STATE_ROAR,
};

static float SharkSummonPos[8][4] =
{
    {-8288.62f, 1479.97f, 43.97413f, 0.1134f},
    {-8273.75f, 1484.46f, 43.02283f, 6.2744f},
    {-8288.08f, 1487.72f, 43.92963f, 6.1902f},
    {-8281.04f, 1477.49f, 43.38793f, 0.2214f},
    {-8281.33f, 1490.41f, 43.55893f, 6.0833f},
    {-8295.10f, 1484.91f, 44.40643f, 6.2684f},
    {-8294.66f, 1474.68f, 44.37793f, 0.2158f},
    {-8294.61f, 1493.67f, 44.70723f, 6.0708f},
};

static float MeteorTarget[402][3] =
{
    {-8037.68f, 1475.99f, 13.6223f}, {-8041.16f, 1483.95f, 25.0963f}, {-8041.91f, 1495.25f, 20.7194f},
    {-8032.24f, 1496.39f, 23.9126f}, {-8025.68f, 1485.01f, 25.8630f}, {-8041.24f, 1505.12f, 25.5332f},
    {-8076.59f, 1522.16f, 17.9709f}, {-8077.30f, 1513.77f, 8.99984f}, {-8053.48f, 1509.48f, 9.44403f},
    {-8055.35f, 1485.35f, 9.42139f}, {-8039.05f, 1464.38f, 9.29380f}, {-8067.47f, 1467.07f, 9.31727f},
    {-8086.85f, 1470.7f,  8.83234f}, {-8103.07f, 1481.57f, 10.1055f}, {-8112.70f, 1437.85f, 11.1506f},
    {-8099.88f, 1264.54f, 21.0841f}, {-8058.81f, 1141.94f, 2.76407f}, {-8096.91f, 1342.74f, 18.1227f},
    {-8068.48f, 1162.18f, 3.05742f}, {-8052.22f, 1173.28f, 2.91838f}, {-8036.89f, 1197.22f, 2.46190f},
    {-8062.27f, 1188.14f, 3.90544f}, {-8024.79f, 1205.59f, 1.37508f}, {-8029.19f, 1223.73f, 1.76494f},
    {-8053.10f, 1210.93f, 3.86019f}, {-8043.74f, 1229.99f, 2.52742f}, {-8047.74f, 1252.81f, 6.56697f},
    {-8037.87f, 1297.72f, 3.53944f}, {-8055.57f, 1278.24f, 5.53981f}, {-8026.04f, 1304.86f, 2.91297f},
    {-8045.09f, 1325.30f, 4.80808f}, {-8057.48f, 1338.18f, 6.98008f}, {-8044.74f, 1365.26f, 4.53430f},
    {-8046.55f, 1382.63f, 2.60187f}, {-8053.19f, 1401.32f, 3.15130f}, {-8075.15f, 1401.26f, 7.57897f},
    {-8093.07f, 1371.91f, 12.5679f}, {-8093.58f, 1391.20f, 12.5674f}, {-8120.85f, 1382.40f, 23.6426f},
    {-8124.57f, 1357.68f, 18.8603f}, {-8172.53f, 1341.48f, 27.9590f}, {-8161.24f, 1355.54f, 23.4237f},
    {-8174.19f, 1386.07f, 24.8344f}, {-8234.61f, 1408.73f, 36.9358f}, {-8242.37f, 1383.82f, 41.1568f},
    {-8212.09f, 1395.50f, 39.9162f}, {-8206.88f, 1369.10f, 34.6802f}, {-8233.45f, 1341.80f, 47.8119f},
    {-8261.95f, 1353.64f, 62.5433f}, {-8270.65f, 1374.68f, 63.6114f}, {-8311.16f, 1379.20f, 86.6267f},
    {-8352.93f, 1384.25f, 95.7099f}, {-8398.04f, 1360.53f, 129.112f}, {-8417.90f, 1356.72f, 134.570f},
    {-8429.48f, 1373.74f, 128.992f}, {-8407.17f, 1359.41f, 127.608f}, {-8421.11f, 1367.92f, 129.211f},
    {-8521.92f, 1375.69f, 108.413f}, {-8523.60f, 1299.74f, 114.588f}, {-8448.57f, 1346.65f, 102.444f},
    {-8447.05f, 1371.65f, 102.388f}, {-8462.35f, 1376.25f, 101.697f}, {-8484.00f, 1382.84f, 101.697f},
    {-8508.61f, 1377.18f, 101.716f}, {-8512.02f, 1349.75f, 101.697f}, {-8517.48f, 1314.72f, 101.863f},
    {-8485.11f, 1329.38f, 98.9211f}, {-8484.09f, 1310.34f, 101.697f}, {-8458.21f, 1303.35f, 101.947f},
    {-8425.03f, 1295.12f, 102.925f}, {-8420.98f, 1332.78f, 102.356f}, {-8385.83f, 1330.55f, 102.322f},
    {-8383.08f, 1363.67f, 102.067f}, {-8353.45f, 1343.85f, 95.5177f}, {-8324.33f, 1339.75f, 80.4592f},
    {-8306.44f, 1308.16f, 67.3110f}, {-8282.09f, 1292.87f, 56.9746f}, {-8250.65f, 1304.47f, 45.3597f},
    {-8184.25f, 1329.89f, 63.1769f}, {-8181.56f, 1322.03f, 55.0864f}, {-8159.35f, 1314.61f, 26.4618f},
    {-8189.84f, 1312.64f, 27.6195f}, {-8137.79f, 1308.98f, 19.8113f}, {-8111.47f, 1310.57f, 18.6071f},
    {-8104.93f, 1286.12f, 20.1409f}, {-8126.01f, 1251.00f, 19.6462f}, {-8111.52f, 1224.01f, 16.0268f},
    {-8121.25f, 1155.22f, 12.9709f}, {-8110.50f, 1181.40f, 14.4180f}, {-8149.94f, 1167.08f, 19.5562f},
    {-8137.99f, 1191.00f, 17.4234f}, {-8169.59f, 1200.18f, 18.7697f}, {-8188.52f, 1217.12f, 22.4706f},
    {-8161.76f, 1221.41f, 20.8543f}, {-8156.47f, 1241.08f, 21.6440f}, {-8154.94f, 1256.68f, 22.7579f},
    {-8150.27f, 1287.58f, 23.3850f}, {-8173.76f, 1278.06f, 25.5544f}, {-8179.01f, 1265.74f, 36.4265f},
    {-8192.40f, 1276.75f, 27.6607f}, {-8206.10f, 1250.43f, 60.1228f}, {-8209.18f, 1271.33f, 36.8474f},
    {-8204.77f, 1244.57f, 49.9996f}, {-8219.71f, 1242.81f, 45.1397f}, {-8217.20f, 1232.63f, 35.3453f},
    {-8225.51f, 1233.63f, 24.1994f}, {-8244.10f, 1257.35f, 27.9735f}, {-8248.97f, 1204.12f, 36.7716f},
    {-8268.35f, 1222.54f, 34.4648f}, {-8290.61f, 1244.50f, 39.1817f}, {-8306.43f, 1235.52f, 41.1522f},
    {-8330.18f, 1231.38f, 53.4531f}, {-8347.05f, 1227.46f, 54.3543f}, {-8357.28f, 1199.09f, 45.4824f},
    {-8389.13f, 1184.67f, 54.3850f}, {-8399.34f, 1213.46f, 57.4407f}, {-8411.57f, 1229.80f, 60.7457f},
    {-8394.02f, 1245.47f, 59.7155f}, {-8385.13f, 1261.33f, 60.6984f}, {-8393.19f, 1275.48f, 79.2300f},
    {-8428.73f, 1260.14f, 69.1703f}, {-8464.21f, 1244.84f, 54.3887f}, {-8508.75f, 1240.72f, 54.9423f},
    {-8452.64f, 1213.22f, 43.0954f}, {-8478.42f, 1213.83f, 42.0305f}, {-8505.35f, 1223.07f, 50.6053f},
    {-8513.14f, 1202.46f, 49.8505f}, {-8488.22f, 1167.01f, 41.9150f}, {-8487.33f, 1140.70f, 40.6198f},
    {-8478.69f, 1128.04f, 41.6854f}, {-8472.56f, 1163.18f, 41.0058f}, {-8459.93f, 1181.22f, 42.1854f},
    {-8443.70f, 1198.07f, 40.5342f}, {-8420.14f, 1196.56f, 41.3180f}, {-8424.33f, 1175.26f, 40.6914f},
    {-8448.33f, 1174.65f, 40.8060f}, {-8445.03f, 1157.14f, 39.9888f}, {-8451.10f, 1145.83f, 40.9183f},
    {-8443.84f, 1107.99f, 52.1924f}, {-8419.00f, 1126.36f, 49.2527f}, {-8028.87f, 1481.56f, 38.3273f},
    {-8028.99f, 1506.36f, 36.0386f}, {-8087.26f, 1496.92f, 22.6907f}, {-8100.74f, 1517.34f, 9.68134f},
    {-8123.84f, 1517.62f, 10.6082f}, {-8130.38f, 1492.14f, 12.9926f}, {-8145.67f, 1492.48f, 26.6957f},
    {-8146.08f, 1525.65f, 21.6292f}, {-8156.04f, 1545.47f, 25.7418f}, {-8164.30f, 1532.97f, 47.2374f},
    {-8173.93f, 1511.44f, 43.2488f}, {-8178.37f, 1486.72f, 41.5304f}, {-8189.10f, 1524.61f, 59.1192f},
    {-8194.75f, 1542.65f, 66.0870f}, {-8198.37f, 1547.58f, 31.9746f}, {-8116.75f, 1554.00f, 27.2984f},
    {-8122.01f, 1542.77f, 26.7214f}, {-8114.74f, 1529.92f, 25.8053f}, {-8113.16f, 1539.34f, 36.2071f},
    {-8102.46f, 1550.34f, 9.05301f}, {-8084.31f, 1536.76f, 9.17192f}, {-8059.48f, 1542.59f, 3.53651f},
    {-8028.07f, 1538.22f, 1.55586f}, {-7996.98f, 1502.57f, 2.39352f}, {-7991.51f, 1528.00f, 1.28052f},
    {-8004.85f, 1563.46f, 1.56339f}, {-7999.34f, 1594.35f, 2.17393f}, {-8006.75f, 1604.55f, 2.38489f},
    {-8050.17f, 1620.84f, 1.04762f}, {-8067.14f, 1602.28f, 7.81356f}, {-8096.68f, 1617.33f, 8.68595f},
    {-8087.12f, 1592.75f, 7.92499f}, {-8108.32f, 1592.50f, 8.59131f}, {-8090.40f, 1631.63f, 8.95684f},
    {-8072.92f, 1649.38f, 10.1871f}, {-8044.60f, 1653.57f, 4.37643f}, {-8021.95f, 1639.24f, 2.34828f},
    {-7996.61f, 1637.17f, 1.60131f}, {-7994.46f, 1655.70f, 2.44999f}, {-8010.08f, 1663.25f, 2.82048f},
    {-8002.64f, 1679.93f, 3.19247f}, {-7994.76f, 1695.15f, 2.22928f}, {-8014.16f, 1701.03f, 2.96222f},
    {-8005.91f, 1721.59f, 2.21401f}, {-8023.12f, 1732.57f, 1.31788f}, {-8012.69f, 1751.27f, 1.07758f},
    {-8031.88f, 1710.56f, 7.01437f}, {-8049.05f, 1745.71f, 2.03484f}, {-8044.88f, 1776.31f, 1.54140f},
    {-8022.54f, 1784.73f, 0.98204f}, {-8087.86f, 1773.94f, 25.6381f}, {-8037.12f, 1762.20f, 1.80717f},
    {-8082.06f, 1730.01f, 18.2666f}, {-8070.86f, 1707.03f, 16.5465f}, {-8044.80f, 1699.18f, 12.9628f},
    {-8073.86f, 1679.94f, 13.4186f}, {-8096.19f, 1675.74f, 13.3204f}, {-8098.53f, 1700.74f, 16.3298f},
    {-8109.20f, 1739.97f, 22.8146f}, {-8112.35f, 1774.00f, 39.7602f}, {-8094.99f, 1807.06f, 34.2375f},
    {-8067.89f, 1831.77f, 45.3007f}, {-8056.43f, 1816.78f, 41.9736f}, {-8025.39f, 1821.22f, 35.5957f},
    {-7998.59f, 1820.47f, 23.7669f}, {-7980.88f, 1806.43f, 13.3507f}, {-7971.68f, 1908.20f, 52.5324f},
    {-7996.62f, 1904.99f, 52.5176f}, {-8028.01f, 1902.80f, 49.6608f}, {-8023.44f, 1873.97f, 52.7744f},
    {-8004.30f, 1876.02f, 52.6784f}, {-8005.74f, 1861.77f, 65.9874f}, {-8031.11f, 1860.10f, 52.5216f},
    {-8048.75f, 1876.51f, 52.5164f}, {-8054.38f, 1859.08f, 52.3152f}, {-8064.52f, 1895.29f, 53.6651f},
    {-8054.42f, 1917.65f, 52.5129f}, {-8047.46f, 1911.33f, 52.5143f}, {-8047.32f, 1934.01f, 52.5890f},
    {-8055.51f, 1947.62f, 53.0907f}, {-8079.51f, 1952.64f, 53.9686f}, {-8046.28f, 1950.57f, 67.4519f},
    {-8079.02f, 1929.12f, 65.8922f}, {-8112.23f, 1929.90f, 55.6128f}, {-8118.68f, 1913.42f, 54.9076f},
    {-8092.71f, 1895.89f, 54.5085f}, {-8096.62f, 1874.26f, 56.0164f}, {-8114.35f, 1867.71f, 56.2004f},
    {-8139.16f, 1861.77f, 55.4215f}, {-8146.83f, 1887.72f, 81.0716f}, {-8154.03f, 1903.98f, 66.0807f},
    {-8143.70f, 1912.14f, 81.4387f}, {-8155.74f, 1896.17f, 86.3040f}, {-8154.48f, 1887.44f, 98.7238f},
    {-8136.74f, 1891.18f, 81.4883f}, {-8149.41f, 1848.57f, 33.8570f}, {-8159.65f, 1841.05f, 31.4248f},
    {-8143.59f, 1823.63f, 23.0160f}, {-8158.70f, 1778.53f, 25.2191f}, {-8185.56f, 1788.36f, 29.8838f},
    {-8176.88f, 1763.34f, 47.1109f}, {-8182.01f, 1779.40f, 45.6053f}, {-8174.42f, 1774.36f, 55.5011f},
    {-8184.51f, 1747.35f, 56.2979f}, {-8201.65f, 1762.05f, 43.2104f}, {-8221.98f, 1745.37f, 44.3920f},
    {-8239.13f, 1726.88f, 44.7975f}, {-8247.40f, 1724.67f, 44.6988f}, {-8236.96f, 1716.77f, 44.6888f},
    {-8235.27f, 1699.40f, 44.5862f}, {-8225.99f, 1708.32f, 55.2297f}, {-8210.29f, 1723.04f, 55.5713f},
    {-8205.04f, 1719.37f, 61.9990f}, {-8208.55f, 1702.31f, 57.2884f}, {-8207.53f, 1695.21f, 60.9719f},
    {-8206.98f, 1691.87f, 68.2909f}, {-8209.78f, 1678.74f, 49.7786f}, {-8210.34f, 1685.61f, 58.1599f},
    {-8181.90f, 1668.56f, 57.7743f}, {-8119.52f, 1602.52f, 28.6966f}, {-8121.59f, 1588.66f, 29.6093f},
    {-8135.98f, 1591.01f, 44.6268f}, {-8144.41f, 1595.12f, 44.8364f}, {-8144.46f, 1601.59f, 16.3018f},
    {-8157.13f, 1613.54f, 19.0649f}, {-8160.54f, 1645.76f, 20.6001f}, {-8175.91f, 1655.82f, 24.2878f},
    {-8188.97f, 1625.97f, 28.0432f}, {-8205.34f, 1633.55f, 31.1166f}, {-8218.12f, 1644.59f, 32.8152f},
    {-8226.97f, 1631.59f, 33.8053f}, {-8219.49f, 1604.67f, 33.2154f}, {-8229.99f, 1589.33f, 33.5585f},
    {-8208.79f, 1574.95f, 31.5433f}, {-8209.29f, 1555.51f, 31.8884f}, {-8179.93f, 1548.80f, 31.1706f},
    {-8169.80f, 1567.19f, 22.9115f}, {-8175.13f, 1588.15f, 25.3683f}, {-8144.05f, 1588.18f, 45.4832f},
    {-8171.52f, 1611.78f, 40.5640f}, {-8170.19f, 1612.04f, 39.8783f}, {-8169.57f, 1629.38f, 40.6756f},
    {-8174.49f, 1625.01f, 41.1788f}, {-8177.42f, 1616.89f, 40.3119f}, {-8200.22f, 1618.75f, 42.3867f},
    {-8194.98f, 1600.51f, 46.0721f}, {-8195.65f, 1582.67f, 45.7628f}, {-8194.36f, 1546.49f, 40.3620f},
    {-8243.48f, 1559.47f, 60.8475f}, {-8241.81f, 1580.22f, 62.2030f}, {-8242.42f, 1580.86f, 69.3832f},
    {-8297.73f, 1607.72f, 131.350f}, {-8317.24f, 1605.07f, 130.934f}, {-8317.45f, 1621.26f, 124.914f},
    {-8311.22f, 1614.64f, 129.569f}, {-8291.52f, 1612.08f, 130.917f}, {-8270.51f, 1614.94f, 129.910f},
    {-8263.07f, 1654.11f, 66.6103f}, {-8279.28f, 1658.81f, 67.4949f}, {-8257.62f, 1666.90f, 49.9469f},
    {-8240.17f, 1674.51f, 43.2782f}, {-8259.22f, 1692.26f, 48.4038f}, {-8274.26f, 1704.07f, 63.8722f},
    {-8275.31f, 1718.44f, 64.9682f}, {-8276.65f, 1726.24f, 71.4404f}, {-8301.52f, 1726.90f, 51.0400f},
    {-8318.98f, 1726.47f, 50.7467f}, {-8331.63f, 1748.07f, 50.7927f}, {-8330.70f, 1711.08f, 50.9302f},
    {-8319.73f, 1698.28f, 51.2294f}, {-8339.30f, 1700.00f, 51.1353f}, {-8349.15f, 1720.86f, 68.9031f},
    {-8354.30f, 1731.89f, 69.4192f}, {-8343.74f, 1732.48f, 69.2499f}, {-8342.35f, 1721.51f, 68.7857f},
    {-8389.17f, 1728.71f, 117.668f}, {-8396.05f, 1727.78f, 118.204f}, {-8413.08f, 1723.72f, 118.673f},
    {-8424.37f, 1723.40f, 120.330f}, {-8424.23f, 1728.65f, 117.853f}, {-8407.60f, 1734.04f, 117.950f},
    {-8400.43f, 1735.36f, 118.096f}, {-8468.31f, 1681.69f, 78.5300f}, {-8471.22f, 1666.39f, 74.6295f},
    {-8432.00f, 1664.70f, 48.0161f}, {-8416.58f, 1654.20f, 45.7974f}, {-8425.02f, 1638.11f, 43.6810f},
    {-8404.63f, 1630.90f, 43.6817f}, {-8384.50f, 1657.27f, 49.5437f}, {-8375.68f, 1640.21f, 49.5635f},
    {-8362.68f, 1623.83f, 72.9915f}, {-8379.60f, 1612.53f, 72.2692f}, {-8391.99f, 1609.98f, 82.0446f},
    {-8397.68f, 1589.56f, 72.3736f}, {-8389.79f, 1562.08f, 62.1636f}, {-8431.31f, 1520.08f, 69.3153f},
    {-8401.67f, 1535.71f, 50.3128f}, {-8397.27f, 1547.18f, 49.2079f}, {-8425.62f, 1541.02f, 48.5064f},
    {-8460.11f, 1539.01f, 50.7479f}, {-8456.83f, 1616.70f, 44.0009f}, {-8457.34f, 1631.80f, 45.7327f},
    {-8446.81f, 1615.38f, 42.3281f}, {-8490.66f, 1617.02f, 47.2390f}, {-8326.46f, 1658.76f, 78.2067f},
    {-8321.79f, 1641.24f, 81.3262f}, {-8325.36f, 1579.57f, 79.7855f}, {-8303.68f, 1577.49f, 74.7501f},
    {-8354.54f, 1549.24f, 75.7229f}, {-8354.94f, 1531.94f, 55.4800f}, {-8326.19f, 1532.43f, 47.2057f},
    {-8334.23f, 1547.00f, 81.8935f}, {-8310.97f, 1526.21f, 49.5073f}, {-8302.29f, 1542.42f, 47.6788f},
    {-8299.01f, 1555.11f, 76.2957f}, {-8275.83f, 1544.73f, 50.9328f}, {-8277.68f, 1563.14f, 51.9492f},
    {-8264.25f, 1541.97f, 40.8781f}, {-8254.31f, 1549.45f, 40.7780f}, {-8258.43f, 1557.47f, 55.9036f},
    {-8242.95f, 1545.69f, 46.5355f}, {-8237.21f, 1516.04f, 40.9409f}, {-8244.59f, 1537.00f, 40.4869f},
    {-8227.16f, 1502.12f, 40.6486f}, {-8205.39f, 1512.50f, 52.7608f}, {-8219.27f, 1496.78f, 40.6822f},
    {-8219.90f, 1479.77f, 39.6774f}, {-8234.84f, 1466.32f, 40.4804f}, {-8228.45f, 1447.73f, 39.6120f},
    {-8211.36f, 1441.88f, 36.1301f}, {-8194.97f, 1447.91f, 37.6865f}, {-8189.28f, 1417.96f, 25.2797f},
    {-8192.65f, 1404.33f, 26.2710f}, {-8220.00f, 1421.85f, 47.6745f}, {-8236.09f, 1433.07f, 39.3946f},
    {-8254.82f, 1437.24f, 40.2917f}, {-8254.91f, 1419.55f, 40.0054f}, {-8238.21f, 1421.00f, 51.9041f},
    {-8280.59f, 1418.48f, 52.9367f}, {-8283.64f, 1432.88f, 39.5929f}, {-8303.63f, 1445.15f, 41.7076f},
    {-8316.32f, 1429.48f, 44.5663f}, {-8336.59f, 1412.32f, 75.8575f}, {-8364.83f, 1410.11f, 89.0763f},
    {-8399.95f, 1435.71f, 80.6888f}, {-8349.31f, 1450.96f, 47.8875f}, {-8347.14f, 1477.55f, 47.3712f},
    {-8358.9f, 1481.390f, 63.7215f}, {-8360.44f, 1489.96f, 63.2215f}, {-8372.52f, 1488.14f, 63.8784f},
    {-8379.54f, 1481.10f, 64.1588f}, {-8389.03f, 1484.79f, 108.922f}, {-8393.46f, 1462.69f, 110.765f},
    {-8403.11f, 1444.06f, 112.509f}, {-8409.97f, 1461.63f, 109.751f}, {-8402.11f, 1492.30f, 112.804f},
    {-8458.92f, 1490.22f, 100.733f}, {-8452.01f, 1482.69f, 102.460f}, {-8459.09f, 1475.15f, 102.678f},
    {-8477.37f, 1478.84f, 87.2453f}, {-8477.35f, 1494.56f, 87.1643f}, {-8477.35f, 1494.56f, 87.1643f}
};

struct KajaroEvent
{
    uint32 uiHobartTextId;
    uint32 uiHobartTimer;
    uint32 uiGreelyTextId;
};

const KajaroEvent KajaroType[8] =
{
    {HOBART_SAY_SKY_IS_FALLING,             4000, GREELY_SAY_SKY_IS_FALLING},
    {HOBART_SAY_GRAB_ONLY_THE_IMPORTANT,    5000, GREELY_SAY_GRAB_ONLY_THE_IMPORTANT},
    {HOBART_SAY_PARTY,                      4000, GREELY_SAY_PARTY},
    {HOBART_SAY_DEATHWING,                  5000, GREELY_SAY_DEATHWING},
    {HOBART_SAY_GET_EVERYTHING_PACKED,      4000, GREELY_SAY_GET_EVERYTHING_PACKED},
    {HOBART_SAY_SUBJECT_NINE,               5000, GREELY_SAY_SUBJECT_NINE},
    {HOBART_SAY_SCHEMATICS,                 4000, GREELY_SAY_SCHEMATICS},
    {HOBART_SAY_INGENIOUS_CAP,              5000, GREELY_SAY_INGENIOUS_CAP},
};

static float LeftBunnySummPos[7][4] =
{
    {-8411.01f, 1356.23f, 109.925f, 5.148721f},
    {-8410.72f, 1356.76f, 110.116f, 6.230825f},
    {-8410.48f, 1356.29f, 110.231f, 6.230825f},
    {-8411.18f, 1356.42f, 110.526f, 6.230825f},
    {-8411.56f, 1356.08f, 111.271f, 6.230825f},
    {-8411.06f, 1356.46f, 111.704f, 6.230825f},
    {-8411.21f, 1357.01f, 111.726f, 6.230825f},
};

static float RightBunnySummPos[7][4] =
{
    {-8403.19f, 1356.28f, 109.492f, 6.230825f},
    {-8403.80f, 1356.15f, 109.954f, 3.246312f},
    {-8402.79f, 1355.90f, 110.156f, 6.230825f},
    {-8403.34f, 1356.62f, 110.337f, 6.230825f},
    {-8402.85f, 1356.43f, 110.739f, 6.230825f},
    {-8402.64f, 1356.01f, 111.359f, 6.230825f},
    {-8402.84f, 1356.28f, 111.426f, 6.230825f},
};

#define    VINNY_VENDOR           "Winnie, I need to get at least one souvenir from the place of disaster!"
#define    GOSSIP_GO_TO_THE_BOAT  "Well, Sassy, I'm ready. You can go."
#define    NEW_OUTFIT             "Sabo, I want to throw a party, and I need a new fashionable suit"
#define    COOL_SHADES            "I need fashion sunglasses. What can you buy for these two bundles of wood?"
#define    SHINY_BLING            "Sell me the coolest, most colorful sequins!"
#define    LOST_ISLES             648
#endif*/