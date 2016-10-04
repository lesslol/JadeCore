#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "firelands.h"
#include "MiscPackets.h"

enum Texts
{
    //Ragnaros
    SAY_RAGNAROS_INTRO                      = 0,
    SAY_RAGNAROS_KILL                       = 1,
    SAY_RAGNAROS_SPLITTING_BLOW_SUBMERGE    = 2,
    SAY_RAGNAROS_WRATH_OF_RAGNAROS          = 3,
    SAY_RAGNAROS_SPLITTING_BLOW             = 4,
    SAY_RAGNAROS_SPLITTING_BLOW_EMERGE      = 5,
    SAY_RAGNAROS_NORMAL_SUBMERGE            = 6,
    SAY_RAGNAROS_HEROIC_SUBMERGE            = 7,
    SAY_RAGNAROS_HEROIC_INTRO_1             = 8,
    SAY_RAGNAROS_HEROIC_INTRO_2             = 9,
    SAY_RAGNAROS_HEROIC_DEATH               = 10,
    SAY_RAGNAROS_AGGRO                      = 11,
    SAY_RAGNAROS_RAGE_OF_RAGNAROS           = 12,

    EMOTE_ENGULFING_FLAMES                  = 13,
    EMOTE_SPLITTING_BLOW                    = 14,
    EMOTE_MAGMA_TRAP                        = 15,
    EMOTE_SULFURAS_SMASH                    = 16,
    EMOTE_WORLD_IN_FLAMES                   = 17,
    EMOTE_EMPOWER_SULFURAS                  = 18,
    EMOTE_BLAZING_HEAT                      = 19,
    EMOTE_MAGMA_GEYSER                      = 20,
    EMOTE_DREADFLAME                        = 21,
    EMOTE_RAGE_OF_RAGNAROS                  = 22,
    EMOTE_SPLITTING_BLOW_EMERGE             = 23,

    EMOTE_WHISPER_LAVA_SCION_BLAZING_HEAT    = 0,

    //Cenarius
    SAY_CENARIUS_HEROIC_INTRO               = 0,
    SAY_CENARIUS_HEROIC_OUTRO_1             = 1,
    SAY_CENARIUS_HEROIC_OUTRO_2             = 2,
    SAY_CENARIUS_HEROIC_OUTRO_3             = 3,

    //Malfurion Stormrage
    SAY_MALFURION_HEROIC_INTRO              = 0,
    SAY_MALFURION_HEROIC_OUTRO_1            = 1,
    SAY_MALFURION_HEROIC_OUTRO_2            = 2,

    //Arch Druid Hamuul Runetotem
    SAY_HAMUUL_HEROIC_OUTRO                 = 0,
};

enum Spells
{
    //Ragnaros
    SPELL_BASE_VISUAL                       = 98860,
    SPELL_BURNING_WOUNDS                    = 99401,
    SPELL_RAGE_OF_RAGNAROS                  = 101107,
    SPELL_MAGMA_BLAST                       = 98313,
    SPELL_WRATH_OF_RAGNAROS                 = 98259,
    SPELL_HAND_OF_RAGNAROS                  = 98237,

    SPELL_MAGMA_TRAP                        = 98159,
    SPELL_MAGMA_TRAP_VISUAL                 = 98179,
    SPELL_MAGMA_TRAP_ERUPTION               = 98175,
    SPELL_MAGMA_TRAP_PLAYER_TRIGGER         = 98172,
    SPELL_MAGMA_TRAP_TARGET_SEARCH          = 98171,
    SPELL_MAGMA_TRAP_VULNERABILITY          = 100238,

    SPELL_SULFURAS_SMASH                    = 98710,
    SPELL_SULFURAS_SMASH_DAMAGE             = 98708,
    SPELL_SULFURAS_SMASH_PLAYER_TRIGGER     = 98703,
    SPELL_SUMMON_SULFURAS_SMASH             = 98706,
    SPELL_SULFURAS_SMASH_LAVA_WAVE          = 98873,
    SPELL_SULFURAS_SMASH_LAVA_WAVE_N        = 98874,
    SPELL_SULFURAS_SMASH_LAVA_WAVE_W        = 98876,
    SPELL_SULFURAS_SMASH_LAVA_WAVE_E        = 98875,
    SPELL_SULFURAS_SMASH_LAVA_POOL          = 98712,
    SPELL_SCORCHED_GROUND                   = 98871,
    SPELL_LAVALOGGED                        = 101088,

    SPELL_SUBMERGE                          = 100051,
    SPELL_SUBMERGE_PERIODIC_AURA            = 98982,
    SPELL_SPLITTING_BLOW_WEST               = 98951,
    SPELL_SPLITTING_BLOW_MIDDLE             = 98952,
    SPELL_SPLITTING_BLOW_EAST               = 98953,
    SPELL_SPLITTING_BLOW_TRIGGERED          = 99012,
    SPELL_INVOKE_SONS_MISSLE                = 99050,
    SPELL_INVOKE_SONS                       = 99051,
    SPELL_SULFURAS                          = 100456,

    //Son of Flame
    SPELL_HIT_ME                            = 100446,
    SPELL_SON_OF_FLAME_INVIS_PRE_VISUAL     = 98983,
    SPELL_BURNING_SPEED                     = 99414,
    SPELL_BURNING_SPEED_CHECKER             = 98473,
    SPELL_SUPERNOVA                         = 99112,

    SPELL_ENGULFING_FLAMES                  = 99171,
    SPELL_ENGULFING_FLAMES_PERIODIC         = 99225,
    SPELL_WORLD_IN_FLAMES                   = 100171,
    SPELL_ENGULFING_FLAMES_NEAR             = 99172,
    SPELL_ENGULFING_FLAMES_NEAR_VISUAL      = 99216,
    SPELL_ENGULFING_FLAMES_MIDDLE           = 99235,
    SPELL_ENGULFING_FLAMES_MIDDLE_VISUAL    = 99217,
    SPELL_ENGULFING_FLAMES_FAR              = 99236,
    SPELL_ENGULFING_FLAMES_FAR_VISUAL       = 99218,

    SPELL_BLAZING_HEAT_TARGET_SEARCH        = 100459,
    SPELL_BLAZING_HEAT                      = 100460,
    SPELL_BLAZING_HEAT_SUMMON               = 99129,

    SPELL_MOLTEN_SEED_TARGET_SEARCH         = 98333,

    // Molten Elemental
    SPELL_MOLTEN_SEED_MISSILE_TARGET_SEARCH = 98497,
    SPELL_MOLTEN_SEED_MISSILE_HIT           = 98498,
    SPELL_MOLTEN_ELEMENTAL_INFERNO          = 98518,
    SPELL_MOLTEN_SEED_COUNTDOWN             = 98520,
    SPELL_MOLTEN_ELEMENTAL_AGGRO_SUMMONER   = 100142,
    SPELL_MOLTEN_ELEMENTAL_INVIS_PRE_VISUAL = 100153,
    SPELL_MOLTEN_ELEMENTAL_MOLTEN_POWER     = 100157,
    SPELL_MOLTEN_ELEMENTAL_DISABLE_CRIT     = 64481,

    // Living Meteor
    SPELL_LIVING_METEOR_DAMAGE_REDUCTION    = 100904,
    SPELL_LIVING_METEOR_COMBUSTIBLE         = 99296,
    SPELL_LIVING_METEOR_PROXIMITY_CHECK     = 99269,
    SPELL_LIVING_METEOR_SPEED_TRIGGER       = 100278,
    SPELL_LIVING_METEOR_FIXATE_VISUAL       = 99849,

    SPELL_AWARD_REPUTATION                  = 101620,
    SPELL_DEATH                             = 99430,
    SPELL_SUMMON_CHEST                      = 101095,
    SPELL_ACHIEVEMENT_CHECK                 = 101091,
    SPELL_HEART_OF_RAGNAROS_A               = 101252,
    SPELL_HEART_OF_RAGNAROS_H               = 101253,
    SPELL_RAGNAROS_KILL_CREDIT              = 102237,

    SPELL_LEGS_SUBMERGE                     = 100312,
    SPELL_LEGS_HEAL                         = 100346,
    SPELL_HEROIC_TRANSFORM                  = 100420,
    SPELL_MAGMA_KNOCKUP                     = 108773,

    SPELL_TRANSFORM_MALFURION               = 100310,
    SPELL_TRANSFORM_HAMUUL                  = 100311,
    SPELL_CENARIUS_DRAW_OUT_FIRELORD        = 100345,
    SPELL_HAMUUL_DRAW_OUT_FIRELORD          = 100344,
    SPELL_MALFURION_DRAW_OUT_FIRELORD       = 100342,

    SPELL_DELUGE_AURA                       = 100713,
    SPELL_DELUGE_EXTINGUISH_DREADFLAME      = 100757,
    SPELL_DELUGE_AURA_CANCEL                = 100771,

    SPELL_SUPERHEATED                       = 100593,
    SPELL_EMPOWER_SULFURAS                  = 100604,
    SPELL_EMPOWER_SULFURAS_VISUAL_MISSILE   = 100606,
    SPELL_DREADFLAME_DAMAGE                 = 100941,
    SPELL_DREADFLAME                        = 100679,
    SPELL_DREADFLAME_SPAWN                  = 100692,
    SPELL_SUMMON_DREADFLAME_SPAWN           = 100675,
    SPELL_DREADFLAME_SPAWN_AURA             = 100691,
    SPELL_BREADTH_OF_FROST_TRIGGER          = 100472,
    SPELL_ENTRAPPING_ROOTS_TRIGGER          = 100645,
    SPELL_BREADTH_OF_FROST                  = 100479,
    SPELL_BREADTH_OF_FROST_PLAYER_AURA      = 100503,
    SPELL_BREADTH_OF_FROST_METEOR_AURA      = 100567,
    SPELL_ENTRAPPING_ROOTS_TARGET_SEARCH    = 100653,
    SPELL_ENTRAPPING_ROOTS                  = 100646,
    SPELL_ENTRAPPING_ROOTS_PERIODIC         = 100647,
    SPELL_BREADTH_OF_FROST_TARGET_SEARCH    = 100478,
    SPELL_CLOUDBURST                        = 100751,
    SPELL_CLOUDBURST_VISUAL                 = 100758,

    SPELL_DREADFLAME_SPREAD_CONTROL_AURA    = 100695,
    SPELL_DREADFLAME_DELUGE_CONTROL_AURA    = 100696,
    SPELL_DREADFLAME_SPAWN_CONTROL_AURA     = 100905,
    SPELL_DREADFLAME_DAMAGE_CONTROL_AURA    = 100965,

    //Misc
    SPELL_MAGMA_PERIODIC                    = 99908,
};

#define DREADFLAME_BASE_CD 40
#define DREADFLAME_TICK 5

enum Events
{
    EVENT_NONE,
    EVENT_PHASE_CHECK,
    EVENT_BASE_VISUAL,
    EVENT_INTRO,
    EVENT_CAN_YELL,
    EVENT_RAGE_OF_RAGNAROS,
    EVENT_MAGMA_BLAST,
    EVENT_PHASE_INTERMISSION,
    EVENT_SON_OF_FLAME_LAUNCH,
    EVENT_SON_OF_FLAME_EXPLODE,
    EVENT_DESPAWN_SULFURAS,
    EVENT_RESUME_ATTACK,
    EVENT_SUMMON_LAVA_WAVE,
    EVENT_SELF_DIE,
    EVENT_SPLITTING_BLOW_SUBMERGE,
    EVENT_DISAPPEAR_AND_DIE,
    EVENT_LAVA_WAVE_MOVE,
    EVENT_SPLITTING_BLOW_EMERGE_WARNING,
    EVENT_SPLITTING_BLOW_EMERGE,
    EVENT_ENGULFING_FLAMES,
    EVENT_ARM_MAGMA_TRAP,
    EVENT_WRATH_OF_RAGNAROS,
    EVENT_MAGMA_TRAP,
    EVENT_HAND_OF_RAGNAROS,
    EVENT_SULFURAS_SMASH,
    EVENT_MOLTEN_SEEDS,
    EVENT_LIVING_METEOR,
    EVENT_MALFURION_LAND,
    EVENT_HAMUUL_LAND,
    EVENT_HEROIC_CENARIUS_1,
    EVENT_PREPARE_PHASE_FOUR,
    EVENT_PHASE_FOUR_EVENT_1,
    EVENT_PHASE_FOUR_EVENT_2,
    EVENT_PHASE_FOUR_EVENT_3,
    EVENT_SCHEDULE_PHASE_FOUR,
    EVENT_DRAW_OUT_FIRELORD,
    EVENT_HEROIC_MALFURION_1,
    EVENT_CLOUDBURST,
    EVENT_DREADFLAME,
    EVENT_BREADTH_OF_FROST,
    EVENT_ENTRAPPING_ROOTS,
    EVENT_EMPOWER_SULFURAS,
};

enum Actions
{
    ACTION_NONE,
    ACTION_RAGNAROS_EMERGE,
    ACTION_INTRO,
    ACTION_MOLTEN_ELEMENTAL_ACTIVATE,
    ACTION_RAGNAROS_HEROIC_SUBMERGE,
    ACTION_MALFURION_HEROIC_INTRO,
    ACTION_RAGNAROS_DREADFLAME,
    ACTION_EMPOWER_SULFURAS,
    ACTION_EMPOWER_SULFURAS_END,
};

enum AnimKits
{
    // Ragnaros
    ANIM_KIT_RESURFACE = 1465,
    ANIM_KIT_EMERGE     = 1467,
    ANIM_KIT_TAUNT      = 1468,
    ANIM_KIT_EMERGE_HC  = 1522,
    ANIM_KIT_STAND_UP   = 1486,
    //ANIM_KIT_SUBMERGE = 1522,

    // Malfurion
    ANIM_KIT_TALK     = 1523,

    // Son of Flame
    ANIM_KIT_UNK        = 1370,
};

enum GameObjectDisplayIds
{
    MODEL_PLATFORM_NORMAL       = 10620,
    MODEL_PLATFORM_DAMAGED      = 10622,
    MODEL_PLATFORM_DESTROYED    = 10703,
};

enum Phases
{
    PHASE_NONE,
    PHASE_ONE,
    PHASE_INTERMISSION,
    PHASE_TWO,
    PHASE_THREE,
    PHASE_SUBMERGE,
    PHASE_FOUR,

    PHASE_MASK_NONE             = 1 << PHASE_NONE,
    PHASE_MASK_ONE              = 1 << PHASE_ONE,
    PHASE_MASK_INTERMISSION     = 1 << PHASE_INTERMISSION,
    PHASE_MASK_TWO              = 1 << PHASE_TWO,
    PHASE_MASK_THREE            = 1 << PHASE_THREE,
    PHASE_MASK_SUBMERGE         = 1 << PHASE_SUBMERGE,
    PHASE_MASK_FOUR             = 1 << PHASE_FOUR,

    EVENT_GROUP_NONE            = 0,
    EVENT_GROUP_DELAYABLE       = 1,
};

enum CreatureGroups
{
    CG_MAGMA                    = 0,
    CG_SPLITTING_BLOW_WEST      = 1,
    CG_SPLITTING_BLOW_MIDDLE    = 2,
    CG_SPLITTING_BLOW_EAST      = 3,
    CG_ENGULFING_FLAMES_NEAR    = 4,
    CG_ENGULFING_FLAMES_MIDDLE  = 5,
    CG_ENGULFING_FLAMES_FAR     = 6,
    CG_LAVA_SCIONS              = 7,
    CG_PLAYER_HELPERS           = 8
};

enum RagnarosData
{
    DATA_ENGULFING_FLAMES_NULL      = 0,
    DATA_ENGULFING_FLAMES_NEAR      = 1,
    DATA_ENGULFING_FLAMES_MIDDLE    = 2,
    DATA_ENGULFING_FLAMES_FAR       = 3,

    ID_ENGULFING_FLAME_CAST         = 0,
    ID_ENGULFING_FLAME_VISUAL       = 1,

    DATA_ENGULFING_FLAMES_ID        = 0,
    DATA_NEW_ENGULFING_FLAME        = 1,
    DATA_PREVIOUS_ENGULFING_FLAME   = 2,

    DATA_SPLITTING_BLOW_WEST        = 1,
    DATA_SPLITTING_BLOW_MIDDLE      = 2,
    DATA_SPLITTING_BLOW_EAST        = 3,

    DATA_SULFURAS_SMASH             = 1,
    DATA_DELUGE_CHARGES             = 2,
    DATA_DREADFLAME                 = 3,

    DATA_IGNITED_METEORS            = 0,

    EQUIP_SULFURAS                  = 1,
    EQUIP_EMPOWERED_SULFURAS        = 2,
};

struct SlotInfo
{
    Position    TargetPosition;
    uint32      ExcludeId;

    std::list<Position> GetPositionsExceptId(SlotInfo slotInfo[], uint32 length, uint32 id)
    {
        std::list<Position> positions;
        for (uint32 i = 0; i < length; i++)
        {
            if (slotInfo[i].ExcludeId == id)
                continue;

            positions.push_back(slotInfo[i].TargetPosition);
        }
        return positions;
    }
};

#define SONS_OF_FLAME_COUNT 8

uint32 const NormalSonsOfFlameSize = 10;
SlotInfo NormalSonsOfFlame[NormalSonsOfFlameSize] =
{
    { { 1074.852f, -12.31597f, 55.42412f,  3.700098f } },
    { { 1059.132f, -110.408f,  55.43525f,  2.408554f } },
    { { 1074.866f, -100.7882f, 55.42414f,  2.600541f } },
    { { 1058.323f, -3.836806f, 55.43348f,  3.874631f } },

    { { 1034.168f, -15.93056f, 55.60827f,  4.049164f }, DATA_SPLITTING_BLOW_WEST },
    { { 1012.12f,  -26.89063f, 55.564f,    4.39823f  }, DATA_SPLITTING_BLOW_WEST },

    { { 997.1042f, -40.70486f, 55.48756f,  5.009095f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 996.7518f, -75.15278f, 55.54374f,  1.256637f }, DATA_SPLITTING_BLOW_MIDDLE },

    { { 1014.325f, -88.80209f, 55.52722f,  1.919862f }, DATA_SPLITTING_BLOW_EAST },
    { { 1035.049f, -98.75868f, 55.58205f,  2.234021f }, DATA_SPLITTING_BLOW_EAST },
};

uint32 const HeroicSonsOfFlameSize = 30;
SlotInfo HeroicSonsOfFlame[HeroicSonsOfFlameSize] =
{
    { { 1051.497f, -113.7292f, 55.44935f,  2.391101f } },
    { { 1051.76f,  0.1284722f, 55.44715f,  4.031711f } },
    { { 1055.332f, -105.0139f, 55.43525f,  2.408554f } },
    { { 1055.556f, -8.875f,    55.43348f,  3.874631f } },
    { { 1065.257f, -6.946181f, 55.56818f,  3.839724f } },
    { { 1065.372f, -108.8698f, 55.56829f,  2.373648f } },
    { { 1067.693f, -13.41146f, 55.53648f,  3.700098f } },
    { { 1068.151f, -101.3924f, 55.56828f,  2.565634f } },
    { { 1074.852f, -12.31597f, 55.42412f,  3.700098f } },
    { { 1074.866f, -100.7882f, 55.42414f,  2.600541f } },

    { { 1012.12f,  -26.89063f, 55.564f,    4.39823f  }, DATA_SPLITTING_BLOW_WEST },
    { { 1025.852f, -16.11285f, 55.62734f,  4.049164f }, DATA_SPLITTING_BLOW_WEST },
    { { 1030.372f, -23.63715f, 55.44154f,  4.049164f }, DATA_SPLITTING_BLOW_WEST },
    { { 1034.168f, -15.93056f, 55.60827f,  4.049164f }, DATA_SPLITTING_BLOW_WEST },
    { { 1038.873f, -23.16319f, 55.42576f,  4.049164f }, DATA_SPLITTING_BLOW_WEST },
    { { 1043.059f, 0.3524306f, 55.44697f,  4.118977f }, DATA_SPLITTING_BLOW_WEST },

    { { 998.8941f, -69.07639f,  55.55765f, 1.256637f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 999.533f,  -45.74826f,  55.56229f, 5.009095f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1013.458f, -68.08507f,  55.42097f, 2.513274f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1014.134f, -43.94445f,  55.42412f, 3.979351f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1059.384f, -0.8385417f, 55.4256f,  3.944444f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1060.281f, -113.4549f,  55.42583f, 2.303835f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1060.95f,  -98.13368f,  55.56828f, 2.513274f }, DATA_SPLITTING_BLOW_MIDDLE },
    { { 1061.34f,  -16.74132f,  55.56819f, 3.769911f }, DATA_SPLITTING_BLOW_MIDDLE },

    { { 1014.325f, -88.80209f, 55.52722f,  1.919862f }, DATA_SPLITTING_BLOW_EAST },
    { { 1024.845f, -97.67882f, 55.52884f,  2.234021f }, DATA_SPLITTING_BLOW_EAST },
    { { 1029.804f, -90.69097f, 55.57508f,  2.234021f }, DATA_SPLITTING_BLOW_EAST },
    { { 1035.049f, -98.75868f, 55.58205f,  2.234021f }, DATA_SPLITTING_BLOW_EAST },
    { { 1040.394f, -91.81944f, 55.42585f,  2.234021f }, DATA_SPLITTING_BLOW_EAST },
    { { 1042.033f, -114.9132f, 55.44709f,  1.919862f }, DATA_SPLITTING_BLOW_EAST }
};

uint32 const EngulfingFlames[4][2] =
{
    { { NULL },                             { NULL } },
    { { SPELL_ENGULFING_FLAMES_NEAR },      { SPELL_ENGULFING_FLAMES_NEAR_VISUAL } },
    { { SPELL_ENGULFING_FLAMES_MIDDLE },    { SPELL_ENGULFING_FLAMES_MIDDLE_VISUAL } },
    { { SPELL_ENGULFING_FLAMES_FAR },       { SPELL_ENGULFING_FLAMES_FAR_VISUAL } }
};

uint32 const CenariusPathSize = 13;
G3D::Vector3 const CenariusPath[CenariusPathSize] =
{
    { 786.0003f, -59.59131f, 86.39431f },
    { 786.9566f, -59.88368f, 86.39431f },
    { 791.1458f, -60.22743f, 85.66431f },
    { 821.7049f, -59.6007f,  71.56089f },
    { 841.1945f, -58.5816f,  71.56089f },
    { 869.1875f, -59.21181f, 54.77988f },
    { 882.4983f, -58.99826f, 53.73591f },
    { 890.9254f, -58.80903f, 49.19218f },
    { 939.6042f, -59.17708f, 48.96181f },
    { 963.4393f, -58.2309f,  49.18719f },
    { 977.7205f, -57.77951f, 55.43077f },
    { 984.1371f, -57.65625f, 55.36652f },
    { 984.1371f, -57.65625f, 55.36652f }
};

uint32 const MalfurionPathSize = 7;
G3D::Vector3 const MalfurionPath[MalfurionPathSize] =
{
    { 786.3611f, -68.77084f, 93.93824f },
    { 787.3611f, -68.77084f, 93.93824f },
    { 788.3715f, -69.71528f, 98.04888f },
    { 881.5781f, -67.98959f, 79.69471f },
    { 961.5452f, -90.04861f, 72.05601f },
    { 984.2274f, -77.62153f, 61.69744f },
    { 984.2274f, -77.62153f, 61.69744f }
};

uint32 const HamuulPathSize = 8;
G3D::Vector3 const HamuulPath[HamuulPathSize] =
{
    { 787.2101f, -50.72396f, 93.77381f },
    { 788.2101f, -50.72396f, 93.77381f },
    { 789.7153f, -50.37674f, 97.14188f },
    { 842.7656f, -53.43576f, 88.88873f },
    { 884.75f,   -36.71354f, 60.77597f },
    { 951.0347f, -49.51215f, 60.77597f },
    { 982.9132f, -43.22049f, 59.49538f },
    { 982.9132f, -43.22049f, 59.49538f }
};

Position const RagnarosHeroicPosition = { 1072.38f, -57.4948f, 56.0f };

struct DreadflameInfo
{
    Position Position;
    ObjectGuid Owner;
    std::vector<DreadflameInfo*> NearbyDreadflames;
};

uint32 const DreadFlamesMax = 561;
Position ConstDreadflames[DreadFlamesMax] =
{
    { 1003.0f, -103.0f, 55.5f, 0.0f },
    { 1003.0f, -108.0f, 55.5f, 0.0f },
    { 1003.0f, -13.0f,  55.5f, 0.0f },
    { 1003.0f, -18.0f,  55.5f, 0.0f },
    { 1003.0f, -23.0f,  55.5f, 0.0f },
    { 1003.0f, -28.0f,  55.5f, 0.0f },
    { 1003.0f, -33.0f,  55.5f, 0.0f },
    { 1003.0f, -38.0f,  55.5f, 0.0f },
    { 1003.0f, -43.0f,  55.5f, 0.0f },
    { 1003.0f, -48.0f,  55.5f, 0.0f },
    { 1003.0f, -53.0f,  55.5f, 0.0f },
    { 1003.0f, -58.0f,  55.5f, 0.0f },
    { 1003.0f, -63.0f,  55.5f, 0.0f },
    { 1003.0f, -68.0f,  55.5f, 0.0f },
    { 1003.0f, -73.0f,  55.5f, 0.0f },
    { 1003.0f, -78.0f,  55.5f, 0.0f },
    { 1003.0f, -8.0f,   55.5f, 0.0f },
    { 1003.0f, -83.0f,  55.5f, 0.0f },
    { 1003.0f, -88.0f,  55.5f, 0.0f },
    { 1003.0f, -93.0f,  55.5f, 0.0f },
    { 1003.0f, -98.0f,  55.5f, 0.0f },
    { 1008.0f, -103.0f, 55.5f, 0.0f },
    { 1008.0f, -108.0f, 55.5f, 0.0f },
    { 1008.0f, -113.0f, 55.5f, 0.0f },
    { 1008.0f, -13.0f,  55.5f, 0.0f },
    { 1008.0f, -18.0f,  55.5f, 0.0f },
    { 1008.0f, -23.0f,  55.5f, 0.0f },
    { 1008.0f, -28.0f,  55.5f, 0.0f },
    { 1008.0f, -3.0f,   55.5f, 0.0f },
    { 1008.0f, -33.0f,  55.5f, 0.0f },
    { 1008.0f, -38.0f,  55.5f, 0.0f },
    { 1008.0f, -43.0f,  55.5f, 0.0f },
    { 1008.0f, -48.0f,  55.5f, 0.0f },
    { 1008.0f, -53.0f,  55.5f, 0.0f },
    { 1008.0f, -58.0f,  55.5f, 0.0f },
    { 1008.0f, -63.0f,  55.5f, 0.0f },
    { 1008.0f, -68.0f,  55.5f, 0.0f },
    { 1008.0f, -73.0f,  55.5f, 0.0f },
    { 1008.0f, -78.0f,  55.5f, 0.0f },
    { 1008.0f, -8.0f,   55.5f, 0.0f },
    { 1008.0f, -83.0f,  55.5f, 0.0f },
    { 1008.0f, -88.0f,  55.5f, 0.0f },
    { 1008.0f, -93.0f,  55.5f, 0.0f },
    { 1008.0f, -98.0f,  55.5f, 0.0f },
    { 1013.0f, -103.0f, 55.5f, 0.0f },
    { 1013.0f, -108.0f, 55.5f, 0.0f },
    { 1013.0f, -113.0f, 55.5f, 0.0f },
    { 1013.0f, -118.0f, 55.5f, 0.0f },
    { 1013.0f, -123.0f, 55.5f, 0.0f },
    { 1013.0f, -13.0f,  55.5f, 0.0f },
    { 1013.0f, -18.0f,  55.5f, 0.0f },
    { 1013.0f, -23.0f,  55.5f, 0.0f },
    { 1013.0f, -28.0f,  55.5f, 0.0f },
    { 1013.0f, -3.0f,   55.5f, 0.0f },
    { 1013.0f, -33.0f,  55.5f, 0.0f },
    { 1013.0f, -38.0f,  55.5f, 0.0f },
    { 1013.0f, -43.0f,  55.5f, 0.0f },
    { 1013.0f, -48.0f,  55.5f, 0.0f },
    { 1013.0f, -53.0f,  55.5f, 0.0f },
    { 1013.0f, -58.0f,  55.5f, 0.0f },
    { 1013.0f, -63.0f,  55.5f, 0.0f },
    { 1013.0f, -68.0f,  55.5f, 0.0f },
    { 1013.0f, -73.0f,  55.5f, 0.0f },
    { 1013.0f, -78.0f,  55.5f, 0.0f },
    { 1013.0f, -8.0f,   55.5f, 0.0f },
    { 1013.0f, -83.0f,  55.5f, 0.0f },
    { 1013.0f, -88.0f,  55.5f, 0.0f },
    { 1013.0f, -93.0f,  55.5f, 0.0f },
    { 1013.0f, -98.0f,  55.5f, 0.0f },
    { 1013.0f, 2.0f,    55.5f, 0.0f },
    { 1013.0f, 7.0f,    55.5f, 0.0f },
    { 1018.0f, -103.0f, 55.5f, 0.0f },
    { 1018.0f, -108.0f, 55.5f, 0.0f },
    { 1018.0f, -113.0f, 55.5f, 0.0f },
    { 1018.0f, -118.0f, 55.5f, 0.0f },
    { 1018.0f, -123.0f, 55.5f, 0.0f },
    { 1018.0f, -128.0f, 55.5f, 0.0f },
    { 1018.0f, -13.0f,  55.5f, 0.0f },
    { 1018.0f, -18.0f,  55.5f, 0.0f },
    { 1018.0f, -23.0f,  55.5f, 0.0f },
    { 1018.0f, -28.0f,  55.5f, 0.0f },
    { 1018.0f, -3.0f,   55.5f, 0.0f },
    { 1018.0f, -33.0f,  55.5f, 0.0f },
    { 1018.0f, -38.0f,  55.5f, 0.0f },
    { 1018.0f, -43.0f,  55.5f, 0.0f },
    { 1018.0f, -48.0f,  55.5f, 0.0f },
    { 1018.0f, -53.0f,  55.5f, 0.0f },
    { 1018.0f, -58.0f,  55.5f, 0.0f },
    { 1018.0f, -63.0f,  55.5f, 0.0f },
    { 1018.0f, -68.0f,  55.5f, 0.0f },
    { 1018.0f, -73.0f,  55.5f, 0.0f },
    { 1018.0f, -78.0f,  55.5f, 0.0f },
    { 1018.0f, -8.0f,   55.5f, 0.0f },
    { 1018.0f, -83.0f,  55.5f, 0.0f },
    { 1018.0f, -88.0f,  55.5f, 0.0f },
    { 1018.0f, -93.0f,  55.5f, 0.0f },
    { 1018.0f, -98.0f,  55.5f, 0.0f },
    { 1018.0f, 12.0f,   55.5f, 0.0f },
    { 1018.0f, 2.0f,    55.5f, 0.0f },
    { 1018.0f, 7.0f,    55.5f, 0.0f },
    { 1023.0f, -103.0f, 55.5f, 0.0f },
    { 1023.0f, -108.0f, 55.5f, 0.0f },
    { 1023.0f, -113.0f, 55.5f, 0.0f },
    { 1023.0f, -118.0f, 55.5f, 0.0f },
    { 1023.0f, -123.0f, 55.5f, 0.0f },
    { 1023.0f, -128.0f, 55.5f, 0.0f },
    { 1023.0f, -13.0f,  55.5f, 0.0f },
    { 1023.0f, -18.0f,  55.5f, 0.0f },
    { 1023.0f, -23.0f,  55.5f, 0.0f },
    { 1023.0f, -28.0f,  55.5f, 0.0f },
    { 1023.0f, -3.0f,   55.5f, 0.0f },
    { 1023.0f, -33.0f,  55.5f, 0.0f },
    { 1023.0f, -38.0f,  55.5f, 0.0f },
    { 1023.0f, -43.0f,  55.5f, 0.0f },
    { 1023.0f, -48.0f,  55.5f, 0.0f },
    { 1023.0f, -53.0f,  55.5f, 0.0f },
    { 1023.0f, -58.0f,  55.5f, 0.0f },
    { 1023.0f, -63.0f,  55.5f, 0.0f },
    { 1023.0f, -68.0f,  55.5f, 0.0f },
    { 1023.0f, -73.0f,  55.5f, 0.0f },
    { 1023.0f, -78.0f,  55.5f, 0.0f },
    { 1023.0f, -8.0f,   55.5f, 0.0f },
    { 1023.0f, -83.0f,  55.5f, 0.0f },
    { 1023.0f, -88.0f,  55.5f, 0.0f },
    { 1023.0f, -93.0f,  55.5f, 0.0f },
    { 1023.0f, -98.0f,  55.5f, 0.0f },
    { 1023.0f, 12.0f,   55.5f, 0.0f },
    { 1023.0f, 2.0f,    55.5f, 0.0f },
    { 1023.0f, 7.0f,    55.5f, 0.0f },
    { 1028.0f, -103.0f, 55.5f, 0.0f },
    { 1028.0f, -108.0f, 55.5f, 0.0f },
    { 1028.0f, -113.0f, 55.5f, 0.0f },
    { 1028.0f, -118.0f, 55.5f, 0.0f },
    { 1028.0f, -123.0f, 55.5f, 0.0f },
    { 1028.0f, -128.0f, 55.5f, 0.0f },
    { 1028.0f, -13.0f,  55.5f, 0.0f },
    { 1028.0f, -18.0f,  55.5f, 0.0f },
    { 1028.0f, -23.0f,  55.5f, 0.0f },
    { 1028.0f, -28.0f,  55.5f, 0.0f },
    { 1028.0f, -3.0f,   55.5f, 0.0f },
    { 1028.0f, -33.0f,  55.5f, 0.0f },
    { 1028.0f, -38.0f,  55.5f, 0.0f },
    { 1028.0f, -43.0f,  55.5f, 0.0f },
    { 1028.0f, -48.0f,  55.5f, 0.0f },
    { 1028.0f, -53.0f,  55.5f, 0.0f },
    { 1028.0f, -58.0f,  55.5f, 0.0f },
    { 1028.0f, -63.0f,  55.5f, 0.0f },
    { 1028.0f, -68.0f,  55.5f, 0.0f },
    { 1028.0f, -73.0f,  55.5f, 0.0f },
    { 1028.0f, -78.0f,  55.5f, 0.0f },
    { 1028.0f, -8.0f,   55.5f, 0.0f },
    { 1028.0f, -83.0f,  55.5f, 0.0f },
    { 1028.0f, -88.0f,  55.5f, 0.0f },
    { 1028.0f, -93.0f,  55.5f, 0.0f },
    { 1028.0f, -98.0f,  55.5f, 0.0f },
    { 1028.0f, 12.0f,   55.5f, 0.0f },
    { 1028.0f, 2.0f,    55.5f, 0.0f },
    { 1028.0f, 7.0f,    55.5f, 0.0f },
    { 1033.0f, -103.0f, 55.5f, 0.0f },
    { 1033.0f, -108.0f, 55.5f, 0.0f },
    { 1033.0f, -113.0f, 55.5f, 0.0f },
    { 1033.0f, -118.0f, 55.5f, 0.0f },
    { 1033.0f, -123.0f, 55.5f, 0.0f },
    { 1033.0f, -128.0f, 55.5f, 0.0f },
    { 1033.0f, -13.0f,  55.5f, 0.0f },
    { 1033.0f, -18.0f,  55.5f, 0.0f },
    { 1033.0f, -23.0f,  55.5f, 0.0f },
    { 1033.0f, -28.0f,  55.5f, 0.0f },
    { 1033.0f, -3.0f,   55.5f, 0.0f },
    { 1033.0f, -33.0f,  55.5f, 0.0f },
    { 1033.0f, -38.0f,  55.5f, 0.0f },
    { 1033.0f, -43.0f,  55.5f, 0.0f },
    { 1033.0f, -48.0f,  55.5f, 0.0f },
    { 1033.0f, -53.0f,  55.5f, 0.0f },
    { 1033.0f, -58.0f,  55.5f, 0.0f },
    { 1033.0f, -63.0f,  55.5f, 0.0f },
    { 1033.0f, -68.0f,  55.5f, 0.0f },
    { 1033.0f, -73.0f,  55.5f, 0.0f },
    { 1033.0f, -78.0f,  55.5f, 0.0f },
    { 1033.0f, -8.0f,   55.5f, 0.0f },
    { 1033.0f, -83.0f,  55.5f, 0.0f },
    { 1033.0f, -88.0f,  55.5f, 0.0f },
    { 1033.0f, -93.0f,  55.5f, 0.0f },
    { 1033.0f, -98.0f,  55.5f, 0.0f },
    { 1033.0f, 12.0f,   55.5f, 0.0f },
    { 1033.0f, 2.0f,    55.5f, 0.0f },
    { 1033.0f, 7.0f,    55.5f, 0.0f },
    { 1038.0f, -103.0f, 55.5f, 0.0f },
    { 1038.0f, -108.0f, 55.5f, 0.0f },
    { 1038.0f, -113.0f, 55.5f, 0.0f },
    { 1038.0f, -118.0f, 55.5f, 0.0f },
    { 1038.0f, -123.0f, 55.5f, 0.0f },
    { 1038.0f, -128.0f, 55.5f, 0.0f },
    { 1038.0f, -13.0f,  55.5f, 0.0f },
    { 1038.0f, -18.0f,  55.5f, 0.0f },
    { 1038.0f, -23.0f,  55.5f, 0.0f },
    { 1038.0f, -28.0f,  55.5f, 0.0f },
    { 1038.0f, -3.0f,   55.5f, 0.0f },
    { 1038.0f, -33.0f,  55.5f, 0.0f },
    { 1038.0f, -38.0f,  55.5f, 0.0f },
    { 1038.0f, -43.0f,  55.5f, 0.0f },
    { 1038.0f, -48.0f,  55.5f, 0.0f },
    { 1038.0f, -53.0f,  55.5f, 0.0f },
    { 1038.0f, -58.0f,  55.5f, 0.0f },
    { 1038.0f, -63.0f,  55.5f, 0.0f },
    { 1038.0f, -68.0f,  55.5f, 0.0f },
    { 1038.0f, -73.0f,  55.5f, 0.0f },
    { 1038.0f, -78.0f,  55.5f, 0.0f },
    { 1038.0f, -8.0f,   55.5f, 0.0f },
    { 1038.0f, -83.0f,  55.5f, 0.0f },
    { 1038.0f, -88.0f,  55.5f, 0.0f },
    { 1038.0f, -93.0f,  55.5f, 0.0f },
    { 1038.0f, -98.0f,  55.5f, 0.0f },
    { 1038.0f, 12.0f,   55.5f, 0.0f },
    { 1038.0f, 2.0f,    55.5f, 0.0f },
    { 1038.0f, 7.0f,    55.5f, 0.0f },
    { 1043.0f, -103.0f, 55.5f, 0.0f },
    { 1043.0f, -108.0f, 55.5f, 0.0f },
    { 1043.0f, -113.0f, 55.5f, 0.0f },
    { 1043.0f, -118.0f, 55.5f, 0.0f },
    { 1043.0f, -123.0f, 55.5f, 0.0f },
    { 1043.0f, -13.0f,  55.5f, 0.0f },
    { 1043.0f, -18.0f,  55.5f, 0.0f },
    { 1043.0f, -23.0f,  55.5f, 0.0f },
    { 1043.0f, -28.0f,  55.5f, 0.0f },
    { 1043.0f, -3.0f,   55.5f, 0.0f },
    { 1043.0f, -33.0f,  55.5f, 0.0f },
    { 1043.0f, -38.0f,  55.5f, 0.0f },
    { 1043.0f, -43.0f,  55.5f, 0.0f },
    { 1043.0f, -48.0f,  55.5f, 0.0f },
    { 1043.0f, -53.0f,  55.5f, 0.0f },
    { 1043.0f, -58.0f,  55.5f, 0.0f },
    { 1043.0f, -63.0f,  55.5f, 0.0f },
    { 1043.0f, -68.0f,  55.5f, 0.0f },
    { 1043.0f, -73.0f,  55.5f, 0.0f },
    { 1043.0f, -78.0f,  55.5f, 0.0f },
    { 1043.0f, -8.0f,   55.5f, 0.0f },
    { 1043.0f, -83.0f,  55.5f, 0.0f },
    { 1043.0f, -88.0f,  55.5f, 0.0f },
    { 1043.0f, -93.0f,  55.5f, 0.0f },
    { 1043.0f, -98.0f,  55.5f, 0.0f },
    { 1043.0f, 2.0f,    55.5f, 0.0f },
    { 1043.0f, 7.0f,    55.5f, 0.0f },
    { 1048.0f, -103.0f, 55.5f, 0.0f },
    { 1048.0f, -108.0f, 55.5f, 0.0f },
    { 1048.0f, -113.0f, 55.5f, 0.0f },
    { 1048.0f, -118.0f, 55.5f, 0.0f },
    { 1048.0f, -13.0f , 55.5f, 0.0f },
    { 1048.0f, -18.0f,  55.5f, 0.0f },
    { 1048.0f, -23.0f,  55.5f, 0.0f },
    { 1048.0f, -28.0f,  55.5f, 0.0f },
    { 1048.0f, -3.0f,   55.5f, 0.0f },
    { 1048.0f, -33.0f,  55.5f, 0.0f },
    { 1048.0f, -38.0f,  55.5f, 0.0f },
    { 1048.0f, -43.0f,  55.5f, 0.0f },
    { 1048.0f, -48.0f,  55.5f, 0.0f },
    { 1048.0f, -53.0f,  55.5f, 0.0f },
    { 1048.0f, -58.0f,  55.5f, 0.0f },
    { 1048.0f, -63.0f,  55.5f, 0.0f },
    { 1048.0f, -68.0f,  55.5f, 0.0f },
    { 1048.0f, -73.0f,  55.5f, 0.0f },
    { 1048.0f, -78.0f,  55.5f, 0.0f },
    { 1048.0f, -8.0f,   55.5f, 0.0f },
    { 1048.0f, -83.0f,  55.5f, 0.0f },
    { 1048.0f, -88.0f,  55.5f, 0.0f },
    { 1048.0f, -93.0f,  55.5f, 0.0f },
    { 1048.0f, -98.0f,  55.5f, 0.0f },
    { 1048.0f, 2.0f,    55.5f, 0.0f },
    { 1053.0f, -103.0f, 55.5f, 0.0f },
    { 1053.0f, -108.0f, 55.5f, 0.0f },
    { 1053.0f, -113.0f, 55.5f, 0.0f },
    { 1053.0f, -118.0f, 55.5f, 0.0f },
    { 1053.0f, -13.0f,  55.5f, 0.0f },
    { 1053.0f, -18.0f,  55.5f, 0.0f },
    { 1053.0f, -23.0f,  55.5f, 0.0f },
    { 1053.0f, -28.0f,  55.5f, 0.0f },
    { 1053.0f, -3.0f,   55.5f, 0.0f },
    { 1053.0f, -33.0f,  55.5f, 0.0f },
    { 1053.0f, -38.0f,  55.5f, 0.0f },
    { 1053.0f, -43.0f,  55.5f, 0.0f },
    { 1053.0f, -48.0f,  55.5f, 0.0f },
    { 1053.0f, -53.0f,  55.5f, 0.0f },
    { 1053.0f, -58.0f,  55.5f, 0.0f },
    { 1053.0f, -63.0f,  55.5f, 0.0f },
    { 1053.0f, -68.0f,  55.5f, 0.0f },
    { 1053.0f, -73.0f,  55.5f, 0.0f },
    { 1053.0f, -78.0f,  55.5f, 0.0f },
    { 1053.0f, -8.0f,   55.5f, 0.0f },
    { 1053.0f, -83.0f,  55.5f, 0.0f },
    { 1053.0f, -88.0f,  55.5f, 0.0f },
    { 1053.0f, -93.0f,  55.5f, 0.0f },
    { 1053.0f, -98.0f,  55.5f, 0.0f },
    { 1053.0f, 2.0f,    55.5f, 0.0f },
    { 1058.0f, -103.0f, 55.5f, 0.0f },
    { 1058.0f, -108.0f, 55.5f, 0.0f },
    { 1058.0f, -113.0f, 55.5f, 0.0f },
    { 1058.0f, -118.0f, 55.5f, 0.0f },
    { 1058.0f, -13.0f,  55.5f, 0.0f },
    { 1058.0f, -18.0f,  55.5f, 0.0f },
    { 1058.0f, -23.0f,  55.5f, 0.0f },
    { 1058.0f, -28.0f,  55.5f, 0.0f },
    { 1058.0f, -3.0f,   55.5f, 0.0f },
    { 1058.0f, -33.0f,  55.5f, 0.0f },
    { 1058.0f, -38.0f,  55.5f, 0.0f },
    { 1058.0f, -43.0f,  55.5f, 0.0f },
    { 1058.0f, -48.0f,  55.5f, 0.0f },
    { 1058.0f, -53.0f,  55.5f, 0.0f },
    { 1058.0f, -58.0f,  55.5f, 0.0f },
    { 1058.0f, -63.0f,  55.5f, 0.0f },
    { 1058.0f, -68.0f,  55.5f, 0.0f },
    { 1058.0f, -73.0f,  55.5f, 0.0f },
    { 1058.0f, -78.0f,  55.5f, 0.0f },
    { 1058.0f, -8.0f,   55.5f, 0.0f },
    { 1058.0f, -83.0f,  55.5f, 0.0f },
    { 1058.0f, -88.0f,  55.5f, 0.0f },
    { 1058.0f, -93.0f,  55.5f, 0.0f },
    { 1058.0f, -98.0f,  55.5f, 0.0f },
    { 1058.0f, 2.0f,    55.5f, 0.0f },
    { 1063.0f, -103.0f, 55.5f, 0.0f },
    { 1063.0f, -108.0f, 55.5f, 0.0f },
    { 1063.0f, -113.0f, 55.5f, 0.0f },
    { 1063.0f, -118.0f, 55.5f, 0.0f },
    { 1063.0f, -13.0f,  55.5f, 0.0f },
    { 1063.0f, -18.0f,  55.5f, 0.0f },
    { 1063.0f, -23.0f,  55.5f, 0.0f },
    { 1063.0f, -28.0f,  55.5f, 0.0f },
    { 1063.0f, -3.0f,   55.5f, 0.0f },
    { 1063.0f, -33.0f,  55.5f, 0.0f },
    { 1063.0f, -38.0f,  55.5f, 0.0f },
    { 1063.0f, -43.0f,  55.5f, 0.0f },
    { 1063.0f, -48.0f,  55.5f, 0.0f },
    { 1063.0f, -53.0f,  55.5f, 0.0f },
    { 1063.0f, -58.0f,  55.5f, 0.0f },
    { 1063.0f, -63.0f,  55.5f, 0.0f },
    { 1063.0f, -68.0f,  55.5f, 0.0f },
    { 1063.0f, -73.0f,  55.5f, 0.0f },
    { 1063.0f, -78.0f,  55.5f, 0.0f },
    { 1063.0f, -8.0f,   55.5f, 0.0f },
    { 1063.0f, -83.0f,  55.5f, 0.0f },
    { 1063.0f, -88.0f,  55.5f, 0.0f },
    { 1063.0f, -93.0f,  55.5f, 0.0f },
    { 1063.0f, -98.0f,  55.5f, 0.0f },
    { 1063.0f, 2.0f,    55.5f, 0.0f },
    { 1068.0f, -103.0f, 55.5f, 0.0f },
    { 1068.0f, -108.0f, 55.5f, 0.0f },
    { 1068.0f, -113.0f, 55.5f, 0.0f },
    { 1068.0f, -13.0f,  55.5f, 0.0f },
    { 1068.0f, -18.0f,  55.5f, 0.0f },
    { 1068.0f, -23.0f,  55.5f, 0.0f },
    { 1068.0f, -28.0f,  55.5f, 0.0f },
    { 1068.0f, -3.0f,   55.5f, 0.0f },
    { 1068.0f, -33.0f,  55.5f, 0.0f },
    { 1068.0f, -38.0f,  55.5f, 0.0f },
    { 1068.0f, -43.0f,  55.5f, 0.0f },
    { 1068.0f, -48.0f,  55.5f, 0.0f },
    { 1068.0f, -53.0f,  55.5f, 0.0f },
    { 1068.0f, -58.0f,  55.5f, 0.0f },
    { 1068.0f, -63.0f,  55.5f, 0.0f },
    { 1068.0f, -68.0f,  55.5f, 0.0f },
    { 1068.0f, -73.0f,  55.5f, 0.0f },
    { 1068.0f, -78.0f,  55.5f, 0.0f },
    { 1068.0f, -8.0f,   55.5f, 0.0f },
    { 1068.0f, -83.0f,  55.5f, 0.0f },
    { 1068.0f, -88.0f,  55.5f, 0.0f },
    { 1068.0f, -93.0f,  55.5f, 0.0f },
    { 1068.0f, -98.0f,  55.5f, 0.0f },
    { 1073.0f, -103.0f, 55.5f, 0.0f },
    { 1073.0f, -108.0f, 55.5f, 0.0f },
    { 1073.0f, -13.0f,  55.5f, 0.0f },
    { 1073.0f, -18.0f,  55.5f, 0.0f },
    { 1073.0f, -23.0f,  55.5f, 0.0f },
    { 1073.0f, -28.0f,  55.5f, 0.0f },
    { 1073.0f, -33.0f,  55.5f, 0.0f },
    { 1073.0f, -38.0f,  55.5f, 0.0f },
    { 1073.0f, -43.0f,  55.5f, 0.0f },
    { 1073.0f, -48.0f,  55.5f, 0.0f },
    { 1073.0f, -53.0f,  55.5f, 0.0f },
    { 1073.0f, -58.0f,  55.5f, 0.0f },
    { 1073.0f, -63.0f,  55.5f, 0.0f },
    { 1073.0f, -68.0f,  55.5f, 0.0f },
    { 1073.0f, -73.0f,  55.5f, 0.0f },
    { 1073.0f, -78.0f,  55.5f, 0.0f },
    { 1073.0f, -8.0f,   55.5f, 0.0f },
    { 1073.0f, -83.0f,  55.5f, 0.0f },
    { 1073.0f, -88.0f,  55.5f, 0.0f },
    { 1073.0f, -93.0f,  55.5f, 0.0f },
    { 1073.0f, -98.0f,  55.5f, 0.0f },
    { 1078.0f, -103.0f, 55.5f, 0.0f },
    { 1078.0f, -108.0f, 55.5f, 0.0f },
    { 1078.0f, -13.0f,  55.5f, 0.0f },
    { 1078.0f, -18.0f,  55.5f, 0.0f },
    { 1078.0f, -23.0f,  55.5f, 0.0f },
    { 1078.0f, -28.0f,  55.5f, 0.0f },
    { 1078.0f, -33.0f,  55.5f, 0.0f },
    { 1078.0f, -38.0f,  55.5f, 0.0f },
    { 1078.0f, -43.0f,  55.5f, 0.0f },
    { 1078.0f, -48.0f,  55.5f, 0.0f },
    { 1078.0f, -53.0f,  55.5f, 0.0f },
    { 1078.0f, -58.0f,  55.5f, 0.0f },
    { 1078.0f, -63.0f,  55.5f, 0.0f },
    { 1078.0f, -68.0f,  55.5f, 0.0f },
    { 1078.0f, -73.0f,  55.5f, 0.0f },
    { 1078.0f, -78.0f,  55.5f, 0.0f },
    { 1078.0f, -8.0f,   55.5f, 0.0f },
    { 1078.0f, -83.0f,  55.5f, 0.0f },
    { 1078.0f, -88.0f,  55.5f, 0.0f },
    { 1078.0f, -93.0f,  55.5f, 0.0f },
    { 1078.0f, -98.0f,  55.5f, 0.0f },
    { 1083.0f, -103.0f, 55.5f, 0.0f },
    { 1083.0f, -13.0f,  55.5f, 0.0f },
    { 1083.0f, -18.0f,  55.5f, 0.0f },
    { 1083.0f, -23.0f,  55.5f, 0.0f },
    { 1083.0f, -28.0f,  55.5f, 0.0f },
    { 1083.0f, -33.0f,  55.5f, 0.0f },
    { 1083.0f, -38.0f,  55.5f, 0.0f },
    { 1083.0f, -43.0f,  55.5f, 0.0f },
    { 1083.0f, -48.0f,  55.5f, 0.0f },
    { 1083.0f, -53.0f,  55.5f, 0.0f },
    { 1083.0f, -58.0f,  55.5f, 0.0f },
    { 1083.0f, -63.0f,  55.5f, 0.0f },
    { 1083.0f, -68.0f,  55.5f, 0.0f },
    { 1083.0f, -73.0f,  55.5f, 0.0f },
    { 1083.0f, -78.0f,  55.5f, 0.0f },
    { 1083.0f, -83.0f,  55.5f, 0.0f },
    { 1083.0f, -88.0f,  55.5f, 0.0f },
    { 1083.0f, -93.0f,  55.5f, 0.0f },
    { 1083.0f, -98.0f,  55.5f, 0.0f },
    { 1088.0f, -18.0f,  55.5f, 0.0f },
    { 1088.0f, -23.0f,  55.5f, 0.0f },
    { 1088.0f, -28.0f,  55.5f, 0.0f },
    { 1088.0f, -33.0f,  55.5f, 0.0f },
    { 1088.0f, -38.0f,  55.5f, 0.0f },
    { 1088.0f, -43.0f,  55.5f, 0.0f },
    { 1088.0f, -48.0f,  55.5f, 0.0f },
    { 1088.0f, -53.0f,  55.5f, 0.0f },
    { 1088.0f, -58.0f,  55.5f, 0.0f },
    { 1088.0f, -63.0f,  55.5f, 0.0f },
    { 1088.0f, -68.0f,  55.5f, 0.0f },
    { 1088.0f, -73.0f,  55.5f, 0.0f },
    { 1088.0f, -78.0f,  55.5f, 0.0f },
    { 1088.0f, -83.0f,  55.5f, 0.0f },
    { 1088.0f, -88.0f,  55.5f, 0.0f },
    { 1088.0f, -93.0f,  55.5f, 0.0f },
    { 1088.0f, -98.0f,  55.5f, 0.0f },
    { 1093.0f, -23.0f,  55.5f, 0.0f },
    { 1093.0f, -28.0f,  55.5f, 0.0f },
    { 1093.0f, -33.0f,  55.5f, 0.0f },
    { 1093.0f, -38.0f,  55.5f, 0.0f },
    { 1093.0f, -43.0f,  55.5f, 0.0f },
    { 1093.0f, -48.0f,  55.5f, 0.0f },
    { 1093.0f, -53.0f,  55.5f, 0.0f },
    { 1093.0f, -58.0f,  55.5f, 0.0f },
    { 1093.0f, -63.0f,  55.5f, 0.0f },
    { 1093.0f, -68.0f,  55.5f, 0.0f },
    { 1093.0f, -73.0f,  55.5f, 0.0f },
    { 1093.0f, -78.0f,  55.5f, 0.0f },
    { 1093.0f, -83.0f,  55.5f, 0.0f },
    { 1093.0f, -88.0f,  55.5f, 0.0f },
    { 1093.0f, -93.0f,  55.5f, 0.0f },
    { 1098.0f, -28.0f,  55.5f, 0.0f },
    { 1098.0f, -33.0f,  55.5f, 0.0f },
    { 1098.0f, -38.0f,  55.5f, 0.0f },
    { 1098.0f, -43.0f,  55.5f, 0.0f },
    { 1098.0f, -48.0f,  55.5f, 0.0f },
    { 1098.0f, -53.0f,  55.5f, 0.0f },
    { 1098.0f, -58.0f,  55.5f, 0.0f },
    { 1098.0f, -63.0f,  55.5f, 0.0f },
    { 1098.0f, -68.0f,  55.5f, 0.0f },
    { 1098.0f, -73.0f,  55.5f, 0.0f },
    { 1098.0f, -78.0f,  55.5f, 0.0f },
    { 1098.0f, -83.0f,  55.5f, 0.0f },
    { 1098.0f, -88.0f,  55.5f, 0.0f },
    { 1103.0f, -33.0f,  55.5f, 0.0f },
    { 1103.0f, -38.0f,  55.5f, 0.0f },
    { 1103.0f, -43.0f,  55.5f, 0.0f },
    { 1103.0f, -48.0f,  55.5f, 0.0f },
    { 1103.0f, -53.0f,  55.5f, 0.0f },
    { 1103.0f, -58.0f,  55.5f, 0.0f },
    { 1103.0f, -63.0f,  55.5f, 0.0f },
    { 1103.0f, -68.0f,  55.5f, 0.0f },
    { 1103.0f, -73.0f,  55.5f, 0.0f },
    { 1103.0f, -78.0f,  55.5f, 0.0f },
    { 1103.0f, -83.0f,  55.5f, 0.0f },
    { 1108.0f, -38.0f,  55.5f, 0.0f },
    { 1108.0f, -43.0f,  55.5f, 0.0f },
    { 1108.0f, -48.0f,  55.5f, 0.0f },
    { 1108.0f, -53.0f,  55.5f, 0.0f },
    { 1108.0f, -58.0f,  55.5f, 0.0f },
    { 1108.0f, -63.0f,  55.5f, 0.0f },
    { 1108.0f, -68.0f,  55.5f, 0.0f },
    { 1108.0f, -73.0f,  55.5f, 0.0f },
    { 1108.0f, -78.0f,  55.5f, 0.0f },
    { 1113.0f, -43.0f,  55.5f, 0.0f },
    { 1113.0f, -48.0f,  55.5f, 0.0f },
    { 1113.0f, -53.0f,  55.5f, 0.0f },
    { 1113.0f, -58.0f,  55.5f, 0.0f },
    { 1113.0f, -63.0f,  55.5f, 0.0f },
    { 1113.0f, -68.0f,  55.5f, 0.0f },
    { 1113.0f, -73.0f,  55.5f, 0.0f },
    { 983.0f,  -28.0f,  55.5f, 0.0f },
    { 983.0f,  -33.0f,  55.5f, 0.0f },
    { 983.0f,  -38.0f,  55.5f, 0.0f },
    { 983.0f,  -43.0f,  55.5f, 0.0f },
    { 983.0f,  -48.0f,  55.5f, 0.0f },
    { 983.0f,  -53.0f,  55.5f, 0.0f },
    { 983.0f,  -58.0f,  55.5f, 0.0f },
    { 983.0f,  -63.0f,  55.5f, 0.0f },
    { 983.0f,  -68.0f,  55.5f, 0.0f },
    { 983.0f,  -73.0f,  55.5f, 0.0f },
    { 983.0f,  -78.0f,  55.5f, 0.0f },
    { 983.0f,  -83.0f,  55.5f, 0.0f },
    { 983.0f,  -88.0f,  55.5f, 0.0f },
    { 988.0f,  -28.0f,  55.5f, 0.0f },
    { 988.0f,  -33.0f,  55.5f, 0.0f },
    { 988.0f,  -38.0f,  55.5f, 0.0f },
    { 988.0f,  -43.0f,  55.5f, 0.0f },
    { 988.0f,  -48.0f,  55.5f, 0.0f },
    { 988.0f,  -53.0f,  55.5f, 0.0f },
    { 988.0f,  -58.0f,  55.5f, 0.0f },
    { 988.0f,  -63.0f,  55.5f, 0.0f },
    { 988.0f,  -68.0f,  55.5f, 0.0f },
    { 988.0f,  -73.0f,  55.5f, 0.0f },
    { 988.0f,  -78.0f,  55.5f, 0.0f },
    { 988.0f,  -83.0f,  55.5f, 0.0f },
    { 988.0f,  -88.0f,  55.5f, 0.0f },
    { 993.0f,  -18.0f,  55.5f, 0.0f },
    { 993.0f,  -23.0f,  55.5f, 0.0f },
    { 993.0f,  -28.0f,  55.5f, 0.0f },
    { 993.0f,  -33.0f,  55.5f, 0.0f },
    { 993.0f,  -38.0f,  55.5f, 0.0f },
    { 993.0f,  -43.0f,  55.5f, 0.0f },
    { 993.0f,  -48.0f,  55.5f, 0.0f },
    { 993.0f,  -53.0f,  55.5f, 0.0f },
    { 993.0f,  -58.0f,  55.5f, 0.0f },
    { 993.0f,  -63.0f,  55.5f, 0.0f },
    { 993.0f,  -68.0f,  55.5f, 0.0f },
    { 993.0f,  -73.0f,  55.5f, 0.0f },
    { 993.0f,  -78.0f,  55.5f, 0.0f },
    { 993.0f,  -83.0f,  55.5f, 0.0f },
    { 993.0f,  -88.0f,  55.5f, 0.0f },
    { 993.0f,  -93.0f,  55.5f, 0.0f },
    { 993.0f,  -98.0f,  55.5f, 0.0f },
    { 998.0f,  -103.0f, 55.5f, 0.0f },
    { 998.0f,  -13.0f,  55.5f, 0.0f },
    { 998.0f,  -18.0f,  55.5f, 0.0f },
    { 998.0f,  -23.0f,  55.5f, 0.0f },
    { 998.0f,  -28.0f,  55.5f, 0.0f },
    { 998.0f,  -33.0f,  55.5f, 0.0f },
    { 998.0f,  -38.0f,  55.5f, 0.0f },
    { 998.0f,  -43.0f,  55.5f, 0.0f },
    { 998.0f,  -48.0f,  55.5f, 0.0f },
    { 998.0f,  -53.0f,  55.5f, 0.0f },
    { 998.0f,  -58.0f,  55.5f, 0.0f },
    { 998.0f,  -63.0f,  55.5f, 0.0f },
    { 998.0f,  -68.0f,  55.5f, 0.0f },
    { 998.0f,  -73.0f,  55.5f, 0.0f },
    { 998.0f,  -78.0f,  55.5f, 0.0f },
    { 998.0f,  -83.0f,  55.5f, 0.0f },
    { 998.0f,  -88.0f,  55.5f, 0.0f },
    { 998.0f,  -93.0f,  55.5f, 0.0f },
    { 998.0f,  -98.0f,  55.5f, 0.0f }
};

class RagnarosAuraRemovePredicate
{
    public:
        RagnarosAuraRemovePredicate(WorldObject const* refObj) : _refObj(refObj) { }

        bool operator()(uint32 spellId) const
        {
            switch (spellId)
            {
                case SPELL_BASE_VISUAL:
                case SPELL_BURNING_WOUNDS:
                    return false;
                default:
                    return true;
            }
        }

    private:
        WorldObject const* _refObj;
};

class HeartOfFlameCheck : public std::unary_function<Player*, bool>
{
    public:
        HeartOfFlameCheck() : _questId(0) { }
        HeartOfFlameCheck(uint32 questId) : _questId(questId) { }

        bool operator()(Player* player) const
        {
            // Get faction specific legendary quest and check if it's in progress
            Quest const* quest = sObjectMgr->GetQuestTemplate(_questId != 0 ? _questId : player->GetTeam() == ALLIANCE ? QUEST_HEART_OF_FLAME_A : player->GetTeam() == HORDE ? QUEST_HEART_OF_FLAME_H : 0);
            if (!quest || player->GetQuestStatus(quest->ID) != QUEST_STATUS_INCOMPLETE)
                return true;

            // Ensure the quest criterias we're looking for are met, in this case player should have collected all the smouldering essences and does not possess the heart of flame already
            for (QuestObjective const& obj : quest->GetObjectives())
                if (obj.ObjectID == ITEM_HEART_OF_FLAME && player->HasItemCount(ITEM_HEART_OF_FLAME, obj.Amount) ||
                    obj.ObjectID == NPC_SMOULDERING_ESSENCE_CREDIT && player->GetReqKillOrCastCurrentCount(quest->ID, NPC_SMOULDERING_ESSENCE_CREDIT) != obj.Amount)
                    return true;

            return false;
        }

    private:
        uint32 _questId;
};

class DelayedDisappearAndDieEvent : public BasicEvent
{
    public:
        DelayedDisappearAndDieEvent(Creature* owner) : _owner(owner) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/) override
        {
            _owner->DisappearAndDie();
            return true;
        }

    private:
        Creature* _owner;
};

// http://www.wowhead.com/npc=54127/dreadflame
class npc_ragnaros_dreadflame : public CreatureScript
{
    public:
        npc_ragnaros_dreadflame() : CreatureScript("npc_ragnaros_dreadflame") {}

    struct npc_ragnaros_dreadflameAI : public PassiveAI
    {
        npc_ragnaros_dreadflameAI(Creature* creature) : PassiveAI(creature) {}

        void EnterEvadeMode(EvadeReason reason) override { }

        void Reset() override
        {
            Dreadflames.clear();
            for (int i = 0; i < DreadFlamesMax; i++)
            {
                DreadflameInfo* dreadflame = new DreadflameInfo();
                dreadflame->Position = ConstDreadflames[i];
                dreadflame->Owner = ObjectGuid::Empty;
                Dreadflames.push_back(dreadflame);
            }

            for (auto sourceDreadflame : Dreadflames)
                for (auto targetDreadflame : Dreadflames)
                    if (sourceDreadflame != targetDreadflame && sourceDreadflame->Position.IsInDist2d(targetDreadflame->Position.GetPositionX(), targetDreadflame->Position.GetPositionY(), 5.1f))
                        sourceDreadflame->NearbyDreadflames.push_back(targetDreadflame);

            me->CastSpell(me, SPELL_DREADFLAME_SPREAD_CONTROL_AURA, true);
            me->CastSpell(me, SPELL_DREADFLAME_DELUGE_CONTROL_AURA, true);
            //me->CastSpell(me, SPELL_DREADFLAME_SPAWN_CONTROL_AURA, true);
            me->CastSpell(me, SPELL_DREADFLAME_DAMAGE_CONTROL_AURA, true);
        }

        void JustRegisteredDynObject(DynamicObject* dynObj) override
        {
            RegisterDreadflame(dynObj);
        }

        void JustUnregisteredDynObject(DynamicObject* dynObj) override
        {
            UnregisterDreadflame(dynObj);
        }

        void RegisterDreadflame(DynamicObject* dynObj)
        {
            for (int i = 0; i < DreadFlamesMax; i++)
            {
                if (std::sqrt(dynObj->GetExactDist2dSq(Dreadflames[i]->Position.GetPositionX(), Dreadflames[i]->Position.GetPositionY()) < 3.0f))
                {
                    Dreadflames[i]->Owner = dynObj->GetGUID();
                    break;
                }
            }
        }

        void UnregisterDreadflame(DynamicObject* dynObj)
        {
            for (int i = 0; i < DreadFlamesMax; i++)
            {
                if (Dreadflames[i]->Owner == dynObj->GetGUID())
                {
                    Dreadflames[i]->Owner = ObjectGuid::Empty;
                    break;
                }
            }
        }

        std::list<Position> GetDreadflameSpreadPositions() const
        {
            std::vector<DreadflameInfo*> litDreadflames;
            for (auto dreadflame : Dreadflames)
                if (!dreadflame->Owner.IsEmpty())
                    litDreadflames.push_back(dreadflame);

            std::list<Position> spreadPositions;
            for (auto dreadflame : litDreadflames)
            {
                std::vector<DreadflameInfo*> unlitNearbyDreadflames;
                for (auto nearbyDreadflame : dreadflame->NearbyDreadflames)
                    if (nearbyDreadflame->Owner.IsEmpty())
                        unlitNearbyDreadflames.push_back(nearbyDreadflame);

                if (!unlitNearbyDreadflames.empty())
                    spreadPositions.push_back(Trinity::Containers::SelectRandomContainerElement(unlitNearbyDreadflames)->Position);
            }
            std::vector<DynamicObject*> dreadflames = me->GetDynObjects(SPELL_DREADFLAME_SPAWN);
            if (spreadPositions.size() > me->GetMap()->Is25ManRaid() ? 6 : 2)
                Trinity::Containers::RandomResizeList(spreadPositions, std::max<uint32>(me->GetMap()->Is25ManRaid() ? 6 : 2, ceil(spreadPositions.size() * 0.5))); // 0.75

            return spreadPositions;
        }

        std::list<Position> GetVacantDreadflamePositions()
        {
            std::list<Position> positions;
            for (auto dreadflame : Dreadflames)
                if (dreadflame->Owner.IsEmpty())
                    positions.push_back(dreadflame->Position);

            return positions;
        }

        std::list<Position> GetRandomVacantDreadflamePositions(uint32 size)
        {
            std::list<Position> positions = GetVacantDreadflamePositions();
            Trinity::Containers::RandomResizeList(positions, size);

            return positions;
        }

        Position GetPreOptimizedNearbyDreadflamePosition(DreadflameInfo* dreadflame)
        {
            std::list<DreadflameInfo*> unlitDreadflames;
            for (auto _dreadflame : dreadflame->NearbyDreadflames)
                if (dreadflame->Owner.IsEmpty())
                    unlitDreadflames.push_back(dreadflame);

            if (unlitDreadflames.size() > 1)
            {
                DreadflameInfo* _dreadFlame = Trinity::Containers::SelectRandomContainerElement(dreadflame->NearbyDreadflames);
                if (_dreadFlame->Owner.IsEmpty())
                    return _dreadFlame->Position;
            }
            else if (unlitDreadflames.size() == 1)
                return unlitDreadflames.front()->Position;

        }

        Position GetUnoptimizedNearbyDreadflamePosition(WorldObject* source, float distance)
        {
            std::list<DreadflameInfo*> randomNearbyDreadflames;
            for (auto dreadflame : Dreadflames)
                if (distance > source->GetDistance2d(dreadflame->Position.GetPositionX(), dreadflame->Position.GetPositionY()))
                    randomNearbyDreadflames.push_back(dreadflame);

            std::list<DreadflameInfo*> unlitDreadflames;
            for (auto dreadflame : randomNearbyDreadflames)
                if (dreadflame->Owner.IsEmpty())
                    unlitDreadflames.push_back(dreadflame);

            if (unlitDreadflames.size() > 1)
            {
                DreadflameInfo* dreadflame = Trinity::Containers::SelectRandomContainerElement(randomNearbyDreadflames);
                if (dreadflame->Owner.IsEmpty())
                    return dreadflame->Position;
            }
            else if (unlitDreadflames.size() == 1)
                return unlitDreadflames.front()->Position;

            return static_cast<Position>(NULL);
        }

        bool IsNearbyDreadflame(WorldObject* source, float distance) const
        {
            std::vector<DynamicObject*> dreadflames = me->GetDynObjects(SPELL_DREADFLAME_SPAWN);
            for (auto dreadflame : dreadflames)
                if (source->IsInDist2d(dreadflame, distance))
                    return true;

            return false;
        }

        DynamicObject* GetNearestLitDreadflameDynamicObject(WorldObject* source) const
        {
            std::vector<DynamicObject*> dreadflamesVector = me->GetDynObjects(SPELL_DREADFLAME_SPAWN);
            std::list<DynamicObject*> dreadflames(dreadflamesVector.begin(), dreadflamesVector.end());
            if (dreadflames.empty())
                return nullptr;

            dreadflames.sort(Trinity::ObjectDistanceOrderPred(source));
            return dreadflames.front();
        }

        private:
            std::vector<DreadflameInfo*> Dreadflames;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetFirelandsAI<npc_ragnaros_dreadflameAI>(creature);
    }
};

typedef npc_ragnaros_dreadflame::npc_ragnaros_dreadflameAI DreadflameAI;

// http://www.wowhead.com/npc=52409/ragnaros
class boss_ragnaros_firelands : public CreatureScript
{
    public:
        boss_ragnaros_firelands() : CreatureScript("boss_ragnaros_firelands") { }

        struct boss_ragnaros_firelandsAI : public BossAI
        {
            boss_ragnaros_firelandsAI(Creature* creature) : BossAI(creature, DATA_RAGNAROS) { me->setActive(true); }

            void Reset() override
            {
                ResetVariables();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetDisableGravity(true);
                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);

                SetCombatMovement(false);
                PrepareEncounterArea();
                me->LoadEquipment(EQUIP_SULFURAS);
                me->SetReactState(REACT_DEFENSIVE);

                //WorldPackets::Misc::PlayOneShotAnimKit data;
                //data.Unit = me->GetGUID();
                //data.AnimKitID = ANIM_KIT_EMERGE;
                //me->GetMap()->SendToPlayers(data.Write());

                //me->PlayOneShotAnimKitId(ANIM_KIT_EMERGE);
                events.ScheduleEvent(EVENT_BASE_VISUAL, 1.2 * IN_MILLISECONDS);
                if (instance && instance->GetData(DATA_RAGNAROS_FIRST_EMERGE) == 0)
                {
                    instance->SetData(DATA_RAGNAROS_FIRST_EMERGE, 1);
                    events.ScheduleEvent(EVENT_INTRO, 6 * IN_MILLISECONDS, EVENT_GROUP_NONE);
                }
            }

            void ResetVariables()
            {
                _inSulfurasSmash = false;
                _canDie = false;
                _newPhase = PHASE_NONE;
                _canYell = true;
                _dreadflameCnt = 0;
                _dreadflameCountdown = DREADFLAME_BASE_CD;
                _lastEngulfingFlame = 0;
                _engulfedPositions.clear();
            }

            void JustReachedHome() override { }

            void JustRespawned() override
            {
                Reset();
                BossAI::JustRespawned();
            }

            void KilledUnit(Unit* who) override
            {
                if (who->GetTypeId() != TYPEID_PLAYER || !_canYell)
                    return;

                Talk(SAY_RAGNAROS_KILL);
                _canYell = false;
                events.ScheduleEvent(EVENT_CAN_YELL, 8 * IN_MILLISECONDS);
            }

            void EnterCombat(Unit* /*who*/) override
            {
                _EnterCombat();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                Talk(SAY_RAGNAROS_AGGRO);

                events.CancelEvent(EVENT_INTRO);
                PreparePhase(PHASE_ONE);
            }

            void JustDied(Unit* killer) override
            {
                events.Reset();
                scheduler.CancelAll();
                if (instance)
                {
                    instance->SetBossState(DATA_RAGNAROS, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                }

                Talk(SAY_RAGNAROS_HEROIC_DEATH);
                CombatCleanup(false);
                DoCastAOE(SPELL_ACHIEVEMENT_CHECK, true);
                DoCastAOE(SPELL_HEART_OF_RAGNAROS_A, true);
                DoCastAOE(SPELL_HEART_OF_RAGNAROS_H, true);
                DoCastAOE(SPELL_AWARD_REPUTATION, true);
            }

            void EnterEvadeMode(EvadeReason why) override
            {
                if (events.IsInPhase(PHASE_SUBMERGE) && !me->GetMap()->IsHeroic())
                    return;

                if (!_EnterEvadeModeRagnaros(why))
                    return;

                _resetDueToEvade = true;
                events.Reset();
                CombatCleanup();
                PreparePhase(PHASE_NONE);

                if (instance)
                {
                    instance->SetBossState(DATA_RAGNAROS, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    if (GameObject* platform = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(GO_RAGNAROS_PLATFORM)))
                        platform->SetDestructibleState(GO_DESTRUCTIBLE_INTACT);
                }

                me->DespawnOrUnsummon();
            }

            bool _EnterEvadeModeRagnaros(EvadeReason /*why*/)
            {
                if (!me->IsAlive())
                    return false;

                //me->RemoveAurasOnEvade();
                RemoveAuras(RagnarosAuraRemovePredicate(me));

                // sometimes bosses stuck in combat?
                me->DeleteThreatList();
                me->CombatStop(true);
                me->LoadCreaturesAddon();
                me->SetLootRecipient(nullptr);
                me->ResetPlayerDamageReq();
                me->SetLastDamagedTime(0);

                if (me->IsInEvadeMode())
                    return false;

                return true;
            }

            template <class Predicate>
            void RemoveAuras(Predicate& predicate)
            {
                for (std::multimap<uint32, AuraApplication*>::iterator iter = me->GetAppliedAuras().begin(); iter != me->GetAppliedAuras().end();)
                {
                    SpellInfo const* spell = iter->second->GetBase()->GetSpellInfo();
                    if (predicate(spell->Id))
                        me->RemoveAura(iter);
                    else
                        ++iter;
                }
            }

            void CombatCleanup(bool wipe = true)
            {
                if (me->GetMap()->IsHeroic() && wipe)
                {
                    summons.DespawnEntry(NPC_CENARIUS);
                    summons.DespawnEntry(NPC_HAMUUL_RUNETOTEM);
                    summons.DespawnEntry(NPC_MALFURION_STORMRAGE);
                }

                summons.DespawnEntry(NPC_CLOUDBURST);
                summons.DespawnEntry(NPC_BREADTH_OF_FROST);
                summons.DespawnEntry(NPC_ENTRAPPING_ROOTS);
                summons.DespawnEntry(NPC_DREADFLAME);

                summons.DespawnEntry(NPC_RAGNAROS_MAGMA);
                summons.DespawnEntry(NPC_MAGMA_TRAP);
                summons.DespawnEntry(NPC_ENGULFING_FLAMES);
                summons.DespawnEntry(NPC_SULFURAS);
                summons.DespawnEntry(NPC_SON_OF_FLAME);
                summons.DespawnEntry(NPC_LAVA_SCION);
                summons.DespawnEntry(NPC_SPLITTING_BLOW);
                summons.DespawnEntry(NPC_MOLTEN_ELEMENTAL);

                if (me->GetMap()->IsHeroic())
                    DoCastAOE(SPELL_DELUGE_AURA_CANCEL, true);
            }

            void DamageTaken(Unit* /*who*/, uint32& damage) override
            {
                if (damage >= me->GetHealth() && !_canDie)
                    damage = me->GetHealth() - 1;

                if (me->HealthBelowPctDamaged(11, damage) && events.IsInPhase(PHASE_THREE))
                    _newPhase = PHASE_SUBMERGE;
                else if (((me->HealthBelowPctDamaged(71, damage) && events.IsInPhase(PHASE_ONE)) || (me->HealthBelowPctDamaged(41, damage) && events.IsInPhase(PHASE_TWO))) && _newPhase != PHASE_INTERMISSION)
                    _newPhase = PHASE_INTERMISSION;
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
                DoZoneInCombat(summon, SIZE_OF_GRIDS);

                switch (summon->GetEntry())
                {
                    case NPC_SULFURAS_SMASH_TRIGGER:
                        _inSulfurasSmash = true;
                        me->CastStop();
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFacingToObject(summon);
                        me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetAngle(summon));
                        DoCastAOE(SPELL_SULFURAS_SMASH);
                        DoCastAOE(SPELL_SUMMON_SULFURAS_SMASH, true);
                        Talk(EMOTE_SULFURAS_SMASH);
                        events.DelayEvents(6 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE);
                        events.ScheduleEvent(EVENT_RESUME_ATTACK, 5.6 * IN_MILLISECONDS);
                        break;
                    case NPC_LAVA_SCION:
                        if (instance)
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, summon);
                        break;
                    case NPC_CENARIUS:
                    case NPC_HAMUUL_RUNETOTEM:
                    case NPC_MALFURION_STORMRAGE:
                        summon->setActive(true);
                        instance->instance->LoadGrid(summon->GetPositionX(), summon->GetPositionY());
                        break;
                    default:
                        break;
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                switch (summon->GetEntry())
                {
                    case NPC_SON_OF_FLAME:
                        summons.Despawn(summon);
                        if (events.IsInPhase(PHASE_INTERMISSION) && !summons.HasEntry(NPC_SON_OF_FLAME))
                            PreparePhase(_previousPhase == PHASE_ONE ? PHASE_TWO : PHASE_THREE);
                        break;
                    case NPC_LAVA_SCION:
                        if (instance)
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, summon);
                        break;
                    default:
                        break;
                }
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                switch (summon->GetEntry())
                {
                    case NPC_LAVA_SCION:
                        if (instance)
                            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, summon);
                        break;
                    default:
                        break;
                }

                if (summon->IsAIEnabled)
                    summon->AI()->EnterEvadeMode();

                BossAI::SummonedCreatureDespawn(summon);
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case ACTION_RAGNAROS_HEROIC_SUBMERGE:
                        Talk(SAY_RAGNAROS_HEROIC_SUBMERGE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->CastSpell(me, SPELL_LEGS_SUBMERGE, true);
                        me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        events.ScheduleEvent(EVENT_HEROIC_CENARIUS_1, 3.2 * IN_MILLISECONDS);
                        events.ScheduleEvent(EVENT_PREPARE_PHASE_FOUR, 5.2 * IN_MILLISECONDS);
                        break;
                    case ACTION_RAGNAROS_DREADFLAME:
                        _dreadflameCountdown -= std::min(_dreadflameCountdown, uint32(DREADFLAME_TICK));
                        if (_dreadflameCountdown != 0 && _dreadflameCnt > 0)
                            break;

                        _dreadflameCountdown = DREADFLAME_BASE_CD - (_dreadflameCnt * DREADFLAME_TICK);
                        ++_dreadflameCnt;
                        if (Creature* dreadflame = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_DREADFLAME)))
                        {
                            DreadflameAI* ai = CAST_AI(DreadflameAI, dreadflame->GetAI());
                            if (ai)
                            {
                                std::list<Position> positions = ai->GetRandomVacantDreadflamePositions(me->GetMap()->Is25ManRaid() ? 6 : 2);
                                if (!positions.empty())
                                {
                                    Talk(EMOTE_DREADFLAME);
                                    for (auto position : positions)
                                        me->CastSpell(position.GetPositionX(), position.GetPositionY(), position.GetPositionZ(), SPELL_SUMMON_DREADFLAME_SPAWN, true);
                                }
                            }
                        }
                        break;
                    case ACTION_EMPOWER_SULFURAS:
                        me->LoadEquipment(EQUIP_EMPOWERED_SULFURAS, true);
                        break;
                    case ACTION_EMPOWER_SULFURAS_END:
                        me->LoadEquipment(EQUIP_SULFURAS, true);
                        break;
                    default:
                        break;
                }
            }

            void SetData(uint32 id, uint32 entry)
            {
                if (id != DATA_PREVIOUS_ENGULFING_FLAME)
                    return;

                _lastEngulfingFlame = entry;
                _engulfedPositions.push_front(entry);
                while (_engulfedPositions.size() > 3)
                    _engulfedPositions.pop_back();
            }

            uint32 GetData(uint32 type) const override
            {
                switch (type)
                {
                    case DATA_NEW_ENGULFING_FLAME:
                    {
                        uint32 NearCount = 0;
                        uint32 MiddleCount = 0;
                        uint32 FarCount = 0;
                        for (auto _entry : _engulfedPositions)
                        {
                            if (_entry == DATA_ENGULFING_FLAMES_NEAR)
                                ++NearCount;
                            else if (_entry == DATA_ENGULFING_FLAMES_MIDDLE)
                                ++MiddleCount;
                            else if (_entry == DATA_ENGULFING_FLAMES_FAR)
                                ++FarCount;
                        }

                        if (NearCount == 2 || MiddleCount == 2 || FarCount == 2)
                        {
                            if (NearCount == 0)
                                return DATA_ENGULFING_FLAMES_NEAR;
                            if (MiddleCount == 0)
                                return DATA_ENGULFING_FLAMES_MIDDLE;
                            if (FarCount == 0)
                                return DATA_ENGULFING_FLAMES_FAR;
                        }
                        else if (NearCount == 1 && MiddleCount == 1 && FarCount == 0)
                        {
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_NEAR)
                                return RAND(DATA_ENGULFING_FLAMES_MIDDLE, DATA_ENGULFING_FLAMES_FAR);
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_MIDDLE)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_FAR);
                        }
                        else if (MiddleCount == 1 && FarCount == 1 && NearCount == 0)
                        {
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_MIDDLE)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_FAR);
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_FAR)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_MIDDLE);
                        }
                        else if (NearCount == 1 && FarCount == 1 && MiddleCount == 0)
                        {
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_FAR)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_MIDDLE);
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_NEAR)
                                return RAND(DATA_ENGULFING_FLAMES_FAR, DATA_ENGULFING_FLAMES_MIDDLE);
                        }
                        else
                        {
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_NEAR)
                                return RAND(DATA_ENGULFING_FLAMES_MIDDLE, DATA_ENGULFING_FLAMES_FAR);
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_MIDDLE)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_FAR);
                            if (_lastEngulfingFlame == DATA_ENGULFING_FLAMES_FAR)
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_MIDDLE);
                            else
                                return RAND(DATA_ENGULFING_FLAMES_NEAR, DATA_ENGULFING_FLAMES_MIDDLE, DATA_ENGULFING_FLAMES_FAR);
                        }
                        break;
                    }
                    case DATA_IGNITED_METEORS:
                    {
                        uint32 count = 0;
                        for (auto guid : summons)
                            if (Creature* summon = ObjectAccessor::GetCreature(*me, guid))
                                if (summon->GetEntry() == NPC_RAGNAROS_LIVING_METEOR && summon->HasAura(SPELL_LAVALOGGED))
                                    count++;

                        return count;
                    }
                }

                return 0;
            }

            ObjectGuid GetGUID(int32 type) const override
            {
                switch (type)
                {
                    case DATA_SPLITTING_BLOW_WEST:
                        return _splittingBlowWest;
                    case DATA_SPLITTING_BLOW_MIDDLE:
                        return _splittingBlowMiddle;
                    case DATA_SPLITTING_BLOW_EAST:
                        return _splittingBlowEast;
                    default:
                        break;
                }

                return ObjectGuid::Empty;
            }

            void PreparePhase(Phases phase, Phases previousPhase = PHASE_NONE)
            {
                events.SetPhase(phase);

                if (previousPhase != PHASE_NONE)
                    _previousPhase = previousPhase;

                switch (phase)
                {
                    case PHASE_ONE:
                        me->CastSpell(me, SPELL_BURNING_WOUNDS);
                        if (!me->GetMap()->IsHeroic())
                            events.ScheduleEvent(EVENT_RAGE_OF_RAGNAROS, 5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_ONE);

                        events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 6 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                        events.ScheduleEvent(EVENT_MAGMA_TRAP, 16 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                        events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 26 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 32 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                        break;
                    case PHASE_INTERMISSION:
                    {
                        _newPhase = PHASE_NONE;
                        events.CancelEvent(EVENT_MAGMA_BLAST);
                        uint32 splittingBlow = RAND(SPELL_SPLITTING_BLOW_WEST, SPELL_SPLITTING_BLOW_MIDDLE, SPELL_SPLITTING_BLOW_EAST);
                        Creature* target;
                        if (splittingBlow == SPELL_SPLITTING_BLOW_WEST)
                        {
                            SummonSonsOfFlame(DATA_SPLITTING_BLOW_WEST);
                            target = ObjectAccessor::GetCreature(*me, _splittingBlowWest);
                        }
                        else if (splittingBlow == SPELL_SPLITTING_BLOW_MIDDLE)
                        {
                            SummonSonsOfFlame(DATA_SPLITTING_BLOW_MIDDLE);
                            target = ObjectAccessor::GetCreature(*me, _splittingBlowMiddle);
                        }
                        else if (splittingBlow == SPELL_SPLITTING_BLOW_EAST)
                        {
                            SummonSonsOfFlame(DATA_SPLITTING_BLOW_EAST);
                            target = ObjectAccessor::GetCreature(*me, _splittingBlowEast);
                        }

                        if (!target)
                            EnterEvadeMode(EVADE_REASON_OTHER);

                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFacingToObject(target);
                        me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetAngle(target));
                        me->CastSpell(me, SPELL_SUBMERGE, true);
                        me->CastSpell(target, splittingBlow);
                        Talk(SAY_RAGNAROS_SPLITTING_BLOW);
                        Talk(EMOTE_SPLITTING_BLOW);
                        events.ScheduleEvent(EVENT_SPLITTING_BLOW_SUBMERGE, 9.5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_INTERMISSION);
                        break;
                    }
                    case PHASE_TWO:
                        events.CancelEvent(EVENT_SPLITTING_BLOW_EMERGE);
                        events.CancelEvent(EVENT_SPLITTING_BLOW_EMERGE_WARNING);

                        Talk(SAY_RAGNAROS_SPLITTING_BLOW_EMERGE);
                        me->CastSpell(me, SPELL_BASE_VISUAL, true);
                        me->PlayOneShotAnimKitId(ANIM_KIT_RESURFACE);
                        me->RemoveAurasDueToSpell(SPELL_SUBMERGE_PERIODIC_AURA);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_DESPAWN_SULFURAS, 4 * IN_MILLISECONDS);
                        events.ScheduleEvent(EVENT_RESUME_ATTACK, 5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_TWO);
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, (me->GetMap()->IsHeroic() ? urand(5, 6) : 16) * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_TWO);
                        events.ScheduleEvent(EVENT_MOLTEN_SEEDS, (me->GetMap()->IsHeroic() ? 16 : 22) * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_TWO);
                        events.ScheduleEvent(EVENT_ENGULFING_FLAMES, 40 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_TWO);
                        break;
                    case PHASE_THREE:
                        events.CancelEvent(EVENT_SPLITTING_BLOW_EMERGE);
                        events.CancelEvent(EVENT_SPLITTING_BLOW_EMERGE_WARNING);

                        Talk(SAY_RAGNAROS_SPLITTING_BLOW_EMERGE);
                        me->CastSpell(me, SPELL_BASE_VISUAL, true);
                        me->PlayOneShotAnimKitId(ANIM_KIT_RESURFACE);
                        me->RemoveAurasDueToSpell(SPELL_SUBMERGE_PERIODIC_AURA);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        events.ScheduleEvent(EVENT_DESPAWN_SULFURAS, 4 * IN_MILLISECONDS);
                        events.ScheduleEvent(EVENT_RESUME_ATTACK, 5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_THREE);
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 15 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_THREE);
                        events.ScheduleEvent(EVENT_ENGULFING_FLAMES, 31 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_THREE);
                        events.ScheduleEvent(EVENT_LIVING_METEOR, 45.5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_THREE);
                        break;
                    case PHASE_SUBMERGE:
                        _newPhase = PHASE_NONE;
                        if (me->GetMap()->IsHeroic())
                            me->SummonCreatureGroup(CG_PLAYER_HELPERS);
                        else
                        {
                            _JustDied();
                            Talk(SAY_RAGNAROS_NORMAL_SUBMERGE);
                            me->RemoveAllAurasOnDeath();
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->AttackStop();
                            me->SetReactState(REACT_PASSIVE);
                            me->DeleteThreatList();
                            me->CombatStop();
                            CombatCleanup();
                            me->SetFacingTo(me->GetHomePosition().GetOrientation());
                            me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetHomePosition().GetOrientation());
                            DoCastAOE(SPELL_RAGNAROS_KILL_CREDIT, true);
                            DoCastAOE(SPELL_AWARD_REPUTATION, true);
                            me->CastSpell(me, SPELL_DEATH, true);
                            DoCastAOE(SPELL_SUMMON_CHEST, true);
                            DoCastAOE(SPELL_ACHIEVEMENT_CHECK, true);
                            DoCastAOE(SPELL_HEART_OF_RAGNAROS_A, true);
                            DoCastAOE(SPELL_HEART_OF_RAGNAROS_H, true);
                            me->m_Events.AddEvent(new DelayedDisappearAndDieEvent(me), me->m_Events.CalculateTime(3.6 * IN_MILLISECONDS));
                        }
                        break;
                    case PHASE_FOUR:
                        _canDie = true;
                        events.SetPhase(PHASE_FOUR);
                        me->SetReactState(REACT_AGGRESSIVE);

                        DoCastAOE(SPELL_DREADFLAME_SPAWN_AURA, true);
                        DoCastAOE(SPELL_BREADTH_OF_FROST_TRIGGER, true);

                        events.ScheduleEvent(EVENT_ENTRAPPING_ROOTS, (50 - urand(4, 14)) * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                        events.ScheduleEvent(EVENT_EMPOWER_SULFURAS, 50 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                        events.ScheduleEvent(EVENT_BREADTH_OF_FROST, 45 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                        break;
                    default:
                        break;
                }
            }

            void SummonSonsOfFlame(uint32 side)
            {
                std::list<Position> spawnPoints;
                if (me->GetMap()->IsHeroic())
                    spawnPoints = HeroicSonsOfFlame->GetPositionsExceptId(HeroicSonsOfFlame, HeroicSonsOfFlameSize, side);
                else
                    spawnPoints = NormalSonsOfFlame->GetPositionsExceptId(NormalSonsOfFlame, NormalSonsOfFlameSize, side);

                if (spawnPoints.empty())
                    return;

                Trinity::Containers::RandomResizeList(spawnPoints, SONS_OF_FLAME_COUNT);
                for (auto pos : spawnPoints)
                    me->SummonCreature(NPC_SON_OF_FLAME, pos);
            }

            void CheckForNewPhase(Phases newPhase)
            {
                if (!me->IsInCombat() || me->HasUnitState(UNIT_STATE_CASTING) || me->HasReactState(REACT_PASSIVE))
                    return;

                switch (newPhase)
                {
                    case PHASE_INTERMISSION:
                        if (events.IsInPhase(PHASE_ONE))
                            PreparePhase(PHASE_INTERMISSION, PHASE_ONE);
                        else if(events.IsInPhase(PHASE_TWO))
                            PreparePhase(PHASE_INTERMISSION, PHASE_TWO);
                        break;
                    case PHASE_SUBMERGE:
                        PreparePhase(PHASE_SUBMERGE);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                UpdateVictim();

                events.Update(diff);
                scheduler.Update(diff);

                CheckForNewPhase(_newPhase);

                if (me->HasUnitState(UNIT_STATE_STUNNED) || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                /*if (events.IsInPhase(PHASE_FOUR) && !_firstEmpowerSulfuras && (me->GetHealthPct() < (_phase4HealthPct - 10)))*/

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BASE_VISUAL:
                            me->CastSpell(me, SPELL_BASE_VISUAL, true);
                            break;
                        case EVENT_INTRO:
                            me->PlayOneShotAnimKitId(ANIM_KIT_TAUNT);
                            Talk(SAY_RAGNAROS_INTRO);
                            break;
                        case EVENT_CAN_YELL:
                            _canYell = true;
                            break;
                        case EVENT_MAGMA_BLAST:
                        {
                            Unit* victim = me->GetVictim();
                            if (victim && !me->IsWithinMeleeRange(victim))
                                DoCastVictim(SPELL_MAGMA_BLAST);

                            events.ScheduleEvent(EVENT_MAGMA_BLAST, 3 * IN_MILLISECONDS);
                            break;
                        }
                        case EVENT_WRATH_OF_RAGNAROS:
                            if (urand(1, 3) == 1)
                                Talk(SAY_RAGNAROS_WRATH_OF_RAGNAROS);
                            DoCastAOE(SPELL_WRATH_OF_RAGNAROS);
                            events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, 25 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                            break;
                        case EVENT_MAGMA_TRAP:
                            Talk(EMOTE_MAGMA_TRAP);
                            DoCastAOE(SPELL_MAGMA_TRAP);
                            events.ScheduleEvent(EVENT_MAGMA_TRAP, 25 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                            break;
                        case EVENT_HAND_OF_RAGNAROS:
                            DoCastAOE(SPELL_HAND_OF_RAGNAROS);
                            events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 25 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, PHASE_ONE);
                            break;
                        case EVENT_SULFURAS_SMASH:
                            DoCastAOE(SPELL_SULFURAS_SMASH_PLAYER_TRIGGER);
                            events.ScheduleEvent(EVENT_SULFURAS_SMASH, 31 * IN_MILLISECONDS, EVENT_GROUP_DELAYABLE, events.IsInPhase(PHASE_THREE) ? PHASE_THREE : events.IsInPhase(PHASE_TWO) ? PHASE_TWO : PHASE_ONE);
                            break;
                        case EVENT_DESPAWN_SULFURAS:
                            summons.DespawnEntry(NPC_SULFURAS);
                            break;
                        case EVENT_RESUME_ATTACK:
                            _inSulfurasSmash = false;
                            me->resetAttackTimer(); // Do not auto attack straight away
                            me->SetReactState(REACT_AGGRESSIVE);
                            if (me->HealthBelowPct(11) && events.IsInPhase(PHASE_THREE))
                                _newPhase = PHASE_SUBMERGE;
                            else if (me->HealthBelowPct(41) && events.IsInPhase(PHASE_TWO))
                                _newPhase = PHASE_INTERMISSION;
                            break;
                        case EVENT_SPLITTING_BLOW_SUBMERGE:
                            Talk(SAY_RAGNAROS_SPLITTING_BLOW_SUBMERGE);
                            events.ScheduleEvent(EVENT_SPLITTING_BLOW_EMERGE_WARNING, 40 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_INTERMISSION);
                            me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                            if (_previousPhase == PHASE_TWO)
                                me->SummonCreatureGroup(CG_LAVA_SCIONS);
                            break;
                        case EVENT_SPLITTING_BLOW_EMERGE_WARNING:
                            Talk(EMOTE_SPLITTING_BLOW_EMERGE);
                            events.ScheduleEvent(EVENT_SPLITTING_BLOW_EMERGE, 4.5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_INTERMISSION);
                            break;
                        case EVENT_SPLITTING_BLOW_EMERGE:
                            if (events.IsInPhase(PHASE_INTERMISSION))
                                PreparePhase(_previousPhase == PHASE_ONE ? PHASE_TWO : PHASE_THREE);
                            break;
                        case EVENT_ENGULFING_FLAMES:
                            if (me->GetMap()->IsHeroic())
                            {
                                Talk(EMOTE_WORLD_IN_FLAMES);
                                me->AddAura(SPELL_WORLD_IN_FLAMES, me);
                            }
                            else
                            {
                                Talk(EMOTE_ENGULFING_FLAMES);
                                DoCastAOE(SPELL_ENGULFING_FLAMES);
                            }
                            if (events.IsInPhase(PHASE_TWO))
                                events.ScheduleEvent(EVENT_ENGULFING_FLAMES, (me->GetMap()->IsHeroic() ? 1 * MINUTE : 40) * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_TWO);
                            else
                                events.ScheduleEvent(EVENT_ENGULFING_FLAMES, 30 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_THREE);
                            break;
                        case EVENT_DISAPPEAR_AND_DIE:
                            me->DisappearAndDie();
                            break;
                        case EVENT_PREPARE_PHASE_FOUR:
                            me->CastSpell(me, SPELL_LEGS_HEAL, true);
                            me->CastSpell(me, SPELL_HEROIC_TRANSFORM, true);
                            me->NearTeleportTo(RagnarosHeroicPosition.GetPositionX(), RagnarosHeroicPosition.GetPositionY(), RagnarosHeroicPosition.GetPositionZ(), me->GetOrientation());
                            events.ScheduleEvent(EVENT_PHASE_FOUR_EVENT_1, 8.5 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_SUBMERGE);
                            break;
                        case EVENT_PHASE_FOUR_EVENT_1:
                            if (GameObject* platform = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(GO_RAGNAROS_PLATFORM)))
                                platform->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED);
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            {
                                me->SetFacingToObject(target);
                                me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetAngle(target));
                            }
                            if (Creature* magma = me->FindNearestCreature(NPC_RAGNAROS_MAGMA, 25.0f))
                                magma->CastSpell(static_cast<Unit*>(NULL), SPELL_MAGMA_KNOCKUP, true);
                            SetCombatMovement(true);
                            me->PlayOneShotAnimKitId(ANIM_KIT_EMERGE_HC);
                            me->RemoveAurasDueToSpell(SPELL_LEGS_SUBMERGE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                            events.ScheduleEvent(EVENT_PHASE_FOUR_EVENT_2, 3.55 * IN_MILLISECONDS);
                            break;
                        case EVENT_PHASE_FOUR_EVENT_2:
                            Talk(SAY_RAGNAROS_HEROIC_INTRO_1);
                            me->PlayOneShotAnimKitId(ANIM_KIT_TAUNT);
                            me->RemoveAurasDueToSpell(SPELL_CENARIUS_DRAW_OUT_FIRELORD);
                            me->RemoveAurasDueToSpell(SPELL_HAMUUL_DRAW_OUT_FIRELORD);
                            me->RemoveAurasDueToSpell(SPELL_MALFURION_DRAW_OUT_FIRELORD);
                            if (Creature* malfurion = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_MALFURION_STORMRAGE)))
                                if (malfurion->IsAIEnabled)
                                    malfurion->AI()->DoAction(ACTION_MALFURION_HEROIC_INTRO);

                            events.ScheduleEvent(EVENT_PHASE_FOUR_EVENT_3, 9.7 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_SUBMERGE);
                            break;
                        case EVENT_PHASE_FOUR_EVENT_3:
                            Talk(SAY_RAGNAROS_HEROIC_INTRO_2);
                            me->PlayOneShotAnimKitId(ANIM_KIT_STAND_UP);
                            me->SetDisableGravity(false);
                            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                            me->CastSpell(me, SPELL_DREADFLAME, true);
                            if (GameObject* platform = ObjectAccessor::GetGameObject(*me, instance->GetGuidData(GO_RAGNAROS_PLATFORM)))
                                platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);

                            scheduler.Schedule(Milliseconds(1200), [this](TaskContext)
                            {
                                DoCast(SPELL_SUPERHEATED);
                            });

                            events.ScheduleEvent(EVENT_SCHEDULE_PHASE_FOUR, 6 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_SUBMERGE);
                            break;
                        case EVENT_SCHEDULE_PHASE_FOUR:
                            PreparePhase(PHASE_FOUR);
                            break;
                        case EVENT_BREADTH_OF_FROST:
                            DoCastAOE(SPELL_BREADTH_OF_FROST_TRIGGER, true);
                            events.ScheduleEvent(EVENT_BREADTH_OF_FROST, 46.1 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                            break;
                        case EVENT_ENTRAPPING_ROOTS:
                            DoCastAOE(SPELL_ENTRAPPING_ROOTS_TRIGGER, true);
                            break;
                        case EVENT_EMPOWER_SULFURAS:
                            Talk(EMOTE_EMPOWER_SULFURAS);
                            DoCastAOE(SPELL_EMPOWER_SULFURAS);
                            events.ScheduleEvent(EVENT_ENTRAPPING_ROOTS, (56 - urand(4, 14)) * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                            events.ScheduleEvent(EVENT_EMPOWER_SULFURAS, 56 * IN_MILLISECONDS, EVENT_GROUP_NONE, PHASE_FOUR);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void DoMeleeAttackIfReady()
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                Unit* victim = me->GetVictim();

                if (!victim)
                    return;
                else if (!me->IsWithinMeleeRange(victim))
                {
                    if (!HasScheduledEvent(EVENT_MAGMA_BLAST) && !events.IsInPhase(PHASE_FOUR))
                        events.ScheduleEvent(EVENT_MAGMA_BLAST, 1 * IN_MILLISECONDS);
                    return;
                }

                //Make sure our attack is ready and we aren't currently casting before checking distance
                if (me->isAttackReady())
                {
                    me->AttackerStateUpdate(victim);
                    me->resetAttackTimer();
                }

                if (me->haveOffhandWeapon() && me->isAttackReady(OFF_ATTACK))
                {
                    me->AttackerStateUpdate(victim, OFF_ATTACK);
                    me->resetAttackTimer(OFF_ATTACK);
                }
            }

            private:
                bool _resetDueToEvade;
                bool _inSulfurasSmash;
                TaskScheduler scheduler;
                bool _canDie;
                ObjectGuid _splittingBlowWest, _splittingBlowMiddle, _splittingBlowEast;
                Phases _newPhase;
                Phases _currentPhase;
                Phases _previousPhase;
                bool _canYell;
                uint32 _tempEngulfingFlameId;
                uint32 _lastEngulfingFlame;
                std::list<uint32> _engulfedPositions;
                uint32 _dreadflameCnt;
                uint32 _dreadflameCountdown;
                bool HasScheduledEvent(uint32 eventId)
                {
                    return events.GetTimeUntilEvent(eventId) != std::numeric_limits<uint32>::max();
                }

                void PrepareEncounterArea()
                {
                    me->SummonCreatureGroup(CG_MAGMA);

                    std::list<TempSummon*> summonGroup;
                    me->SummonCreatureGroup(CG_SPLITTING_BLOW_WEST, &summonGroup);
                    if (TempSummon* temp = summonGroup.front())
                        _splittingBlowWest = summonGroup.front()->GetGUID();

                    summonGroup.clear();
                    me->SummonCreatureGroup(CG_SPLITTING_BLOW_MIDDLE, &summonGroup);
                    if (TempSummon* temp = summonGroup.front())
                        _splittingBlowMiddle = summonGroup.front()->GetGUID();

                    summonGroup.clear();
                    me->SummonCreatureGroup(CG_SPLITTING_BLOW_EAST, &summonGroup);
                    if (TempSummon* temp = summonGroup.front())
                        _splittingBlowEast = summonGroup.front()->GetGUID();

                    std::list<TempSummon*> engulfingFlames;
                    me->SummonCreatureGroup(CG_ENGULFING_FLAMES_NEAR, &engulfingFlames);
                    for (auto flame : engulfingFlames)
                        if (flame->IsAIEnabled)
                            flame->AI()->SetData(DATA_ENGULFING_FLAMES_ID, DATA_ENGULFING_FLAMES_NEAR);

                    engulfingFlames.clear();
                    me->SummonCreatureGroup(CG_ENGULFING_FLAMES_MIDDLE, &engulfingFlames);
                    for (auto flame : engulfingFlames)
                        if (flame->IsAIEnabled)
                            flame->AI()->SetData(DATA_ENGULFING_FLAMES_ID, DATA_ENGULFING_FLAMES_MIDDLE);

                    engulfingFlames.clear();
                    me->SummonCreatureGroup(CG_ENGULFING_FLAMES_FAR, &engulfingFlames);
                    for (auto flame : engulfingFlames)
                        if (flame->IsAIEnabled)
                            flame->AI()->SetData(DATA_ENGULFING_FLAMES_ID, DATA_ENGULFING_FLAMES_FAR);
                }
        };

		CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<boss_ragnaros_firelandsAI>(creature);
        }
};

// http://www.wowhead.com/npc=53266/sulfuras-smash
class npc_sulfuras_smash_trigger : public CreatureScript
{
    public:
        npc_sulfuras_smash_trigger() : CreatureScript("npc_sulfuras_smash_trigger") { }

        struct npc_sulfuras_smash_triggerAI : public PassiveAI
        {
            npc_sulfuras_smash_triggerAI(Creature* creature) : PassiveAI(creature) { }

            void EnterEvadeMode(EvadeReason reason) override { }

            void IsSummonedBy(Unit* summoner) override
            {
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = me->GetMap()->GetCreature(instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->JustSummoned(me);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_sulfuras_smash_triggerAI>(creature);
        }
};

// http://www.wowhead.com/npc=53952/platform-stalker
class npc_fl_ragnaros_platform_stalker : public CreatureScript
{
    public:
        npc_fl_ragnaros_platform_stalker() : CreatureScript("npc_fl_ragnaros_platform_stalker") { }

        struct npc_fl_ragnaros_platform_stalkerAI : public PassiveAI
        {
            npc_fl_ragnaros_platform_stalkerAI(Creature* creature) : PassiveAI(creature) { }

            void JustSummoned(Creature* summon) override
            {
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->JustSummoned(summon);
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->SummonedCreatureDespawn(summon);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_fl_ragnaros_platform_stalkerAI>(creature);
        }
};

// http://www.wowhead.com/npc=53268/sulfuras-smash
class npc_ragnaros_sulfuras_smash : public CreatureScript
{
    public:
        npc_ragnaros_sulfuras_smash() : CreatureScript("npc_ragnaros_sulfuras_smash") { }

        struct npc_ragnaros_sulfuras_smashAI : public PassiveAI
        {
            npc_ragnaros_sulfuras_smashAI(Creature* creature) : PassiveAI(creature) { }

            void EnterEvadeMode(EvadeReason why) override { }

            void SpellHit(Unit* caster, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_SULFURAS_SMASH_DAMAGE)
                    return;

                me->RemoveAurasDueToSpell(SPELL_SULFURAS_SMASH_LAVA_POOL);
                me->CastSpell(me, SPELL_SCORCHED_GROUND, true);

                _events.ScheduleEvent(EVENT_SELF_DIE, 7.5 * IN_MILLISECONDS);
            }

            void JustSummoned(Creature* summon) override
            {
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->JustSummoned(summon);
            }

            void IsSummonedBy(Unit* /*summoner*/) override
            {
                _events.ScheduleEvent(EVENT_SUMMON_LAVA_WAVE, 0.4 * IN_MILLISECONDS);
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUMMON_LAVA_WAVE:
                            me->CastSpell((Unit*)NULL, SPELL_SULFURAS_SMASH_LAVA_WAVE_N, true);
                            me->CastSpell((Unit*)NULL, SPELL_SULFURAS_SMASH_LAVA_WAVE_W, true);
                            me->CastSpell((Unit*)NULL, SPELL_SULFURAS_SMASH_LAVA_WAVE_E, true);
                            me->CastSpell(me, SPELL_SULFURAS_SMASH_LAVA_POOL, true);
                            break;
                        case EVENT_SELF_DIE:
                            me->Kill(me);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_sulfuras_smashAI>(creature);
        }
};

// http://www.wowhead.com/npc=53363/lava-wave
class npc_ragnaros_lava_wave : public CreatureScript
{
    public:
        npc_ragnaros_lava_wave() : CreatureScript("npc_ragnaros_lava_wave") { }

        struct npc_ragnaros_lava_waveAI : public NullCreatureAI
        {
            npc_ragnaros_lava_waveAI(Creature* creature) : NullCreatureAI(creature) { }

            void IsSummonedBy(Unit* summoner) override
            {
                float x, y;
                me->GetNearPoint2D(x, y, 80.0f, summoner->GetAngle(me));
                movePos = { x, y, me->GetPositionZ() };
            }

            void SpellHit(Unit* caster, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_SULFURAS_SMASH_DAMAGE)
                    return;

                me->CastSpell(me, SPELL_SULFURAS_SMASH_LAVA_WAVE, true);
                _events.ScheduleEvent(EVENT_LAVA_WAVE_MOVE, 0.5 * IN_MILLISECONDS);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LAVA_WAVE_MOVE:
                            me->GetMotionMaster()->MovePoint(0, movePos);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
            Position movePos;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_lava_waveAI>(creature);
        }
};

// http://www.wowhead.com/npc=53420/sulfuras-hand-of-ragnaros
class npc_ragnaros_sulfuras : public CreatureScript
{
    public:
        npc_ragnaros_sulfuras() : CreatureScript("npc_ragnaros_sulfuras") { }

        struct npc_ragnaros_sulfurasAI : public PassiveAI
        {
            npc_ragnaros_sulfurasAI(Creature* creature) : PassiveAI(creature) { }

            void EnterEvadeMode(EvadeReason why) override { }

            void IsSummonedBy(Unit* /*summoner*/) override
            {
                me->CastSpell(me, SPELL_SULFURAS, true);
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->JustSummoned(me);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_sulfurasAI>(creature);
        }
};

// http://www.wowhead.com/npc=53140/son-of-flame
class npc_ragnaros_son_of_flame : public CreatureScript
{
    public:
        npc_ragnaros_son_of_flame() : CreatureScript("npc_ragnaros_son_of_flame") { }

        struct npc_ragnaros_son_of_flameAI : public PassiveAI
        {
            npc_ragnaros_son_of_flameAI(Creature* creature) : PassiveAI(creature) { _canWalk = false; }

            void InitializeAI() override
            {
                if (!me->IsAlive())
                    return;

                JustRespawned();
            }

            void JustRespawned() override
            {
                _canWalk = false;
                me->CastSpell(me, SPELL_HIT_ME, true);
                me->CastSpell(me, SPELL_SON_OF_FLAME_INVIS_PRE_VISUAL, true);
            }

            void JustDied(Unit* killer) override
            {
                me->DespawnOrUnsummon(3 * IN_MILLISECONDS);
            }

            void EnterEvadeMode(EvadeReason why) override { }

            void SpellHit(Unit* caster, const SpellInfo* spell) override
            {
                if (spell->Id != SPELL_INVOKE_SONS)
                    return;

                if (InstanceScript* instance = me->GetInstanceScript())
                    chaseTarget = instance->GetGuidData(NPC_SULFURAS);

                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->PlayOneShotAnimKitId(ANIM_KIT_UNK);
                me->RemoveAurasDueToSpell(SPELL_SON_OF_FLAME_INVIS_PRE_VISUAL);
                me->CastSpell(me, SPELL_BURNING_SPEED_CHECKER, true);
                events.ScheduleEvent(EVENT_SON_OF_FLAME_LAUNCH, 2.6 * IN_MILLISECONDS);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != FOLLOW_MOTION_TYPE)
                    return;

                DoCastAOE(SPELL_SUPERNOVA, true);
                me->Kill(me);
            }

            void UpdateAI(uint32 diff) override
            {
                UpdateVictim();

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SON_OF_FLAME_LAUNCH:
                            _canWalk = true;
                            break;
                        case EVENT_SON_OF_FLAME_EXPLODE:
                            DoCastAOE(SPELL_SUPERNOVA, true);
                            me->Kill(me);
                            break;
                    }
                }

                if (me->isDead() || !_canWalk)
                    return;

                if (Unit* target = ObjectAccessor::GetUnit(*me, chaseTarget))
                {
                    if (me->IsWithinMeleeRange(target) && !HasScheduledEvent(EVENT_SON_OF_FLAME_EXPLODE))
                        events.ScheduleEvent(EVENT_SON_OF_FLAME_EXPLODE, 0);
                    else if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE && me->CanFreeMove())
                        me->GetMotionMaster()->MoveFollow(target, 0.0f, 0.0f);
                }
                else if (!HasScheduledEvent(EVENT_SON_OF_FLAME_EXPLODE))
                {
                    me->GetMotionMaster()->Clear(false);
                    me->StopMoving();
                    events.ScheduleEvent(EVENT_SON_OF_FLAME_EXPLODE, 2.6 * IN_MILLISECONDS);
                }
            }

        private:
            bool _canWalk;
            EventMap events;
            ObjectGuid chaseTarget;
            bool HasScheduledEvent(uint32 eventId)
            {
                return events.GetTimeUntilEvent(eventId) != std::numeric_limits<uint32>::max();
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_son_of_flameAI>(creature);
        }
};

// http://www.wowhead.com/npc=53485/engulfing-flames
class npc_ragnaros_engulfing_flames : public CreatureScript
{
    public:
        npc_ragnaros_engulfing_flames() : CreatureScript("npc_ragnaros_engulfing_flames") { }

        struct npc_ragnaros_engulfing_flamesAI : public PassiveAI
        {
            npc_ragnaros_engulfing_flamesAI(Creature* creature) : PassiveAI(creature) { _engulfingId = DATA_ENGULFING_FLAMES_NULL; }

            void EnterEvadeMode(EvadeReason why) override { }

            void SpellHitTarget(Unit* target, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_ENGULFING_FLAMES_PERIODIC || !me->GetMap()->IsHeroic())
                    return;

                // Hack
                if (Aura* aura = me->GetAura(SPELL_ENGULFING_FLAMES_PERIODIC, me->GetGUID()))
                    aura->SetDuration(1000);
            }

            void SetData(uint32 type, uint32 data) override
            {
                if (type != DATA_ENGULFING_FLAMES_ID)
                    return;

                _engulfingId = data;
            }

            uint32 GetData(uint32 type) const override
            {
                if (type == DATA_ENGULFING_FLAMES_ID)
                    return _engulfingId;

                return 0;
            }

        private:
            uint32 _engulfingId;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_engulfing_flamesAI>(creature);
        }
};

// http://www.wowhead.com/npc=53086/magma-trap
class npc_ragnaros_magma_trap : public CreatureScript
{
    public:
        npc_ragnaros_magma_trap() : CreatureScript("npc_ragnaros_magma_trap") { }

        struct npc_ragnaros_magma_trapAI : public PassiveAI
        {
            npc_ragnaros_magma_trapAI(Creature* creature) : PassiveAI(creature) { }

            void EnterEvadeMode(EvadeReason why) override { }

            void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_MAGMA_TRAP_TARGET_SEARCH)
                    return;

                me->Yell("Explosion disabled to due bug in core!", LANG_UNIVERSAL);
                //DoCastAOE(SPELL_MAGMA_TRAP_ERUPTION, true);
                me->RemoveAurasDueToSpell(SPELL_MAGMA_TRAP_VISUAL);
                me->RemoveAurasDueToSpell(SPELL_MAGMA_TRAP_PLAYER_TRIGGER);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                me->CastSpell(me, SPELL_MAGMA_TRAP_VISUAL, true);
                scheduler.Schedule(Milliseconds(1200), [this](TaskContext)
                {
                    me->CastSpell(me, SPELL_MAGMA_TRAP_PLAYER_TRIGGER, true);
                });
            }

            void UpdateAI(uint32 diff) override
            {
                scheduler.Update(diff);
            }

        private:
            TaskScheduler scheduler;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_magma_trapAI>(creature);
        }
};

// http://www.wowhead.com/npc=53189/molten-elemental
class npc_fl_ragnaros_molten_elemental : public CreatureScript
{
    public:
        npc_fl_ragnaros_molten_elemental() : CreatureScript("npc_fl_ragnaros_molten_elemental") { }

        struct npc_fl_ragnaros_molten_elementalAI : public ScriptedAI
        {
            npc_fl_ragnaros_molten_elementalAI(Creature* creature) : ScriptedAI(creature) { me->SetReactState(REACT_PASSIVE); }

            void EnterCombat(Unit* who) override
            {
                DoCast(SPELL_MOLTEN_ELEMENTAL_DISABLE_CRIT);
            }

            void DoAction(int32 action) override
            {
                if (action != ACTION_MOLTEN_ELEMENTAL_ACTIVATE)
                    return;

                me->Say("BOOM!", LANG_UNIVERSAL);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoCastAOE(SPELL_MOLTEN_ELEMENTAL_INFERNO);
                scheduler.Schedule(Milliseconds(600), [this](TaskContext)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoCastAOE(SPELL_MOLTEN_ELEMENTAL_AGGRO_SUMMONER);
                });
            }

            void IsSummonedBy(Unit* /*summoner*/) override
            {
                if (InstanceScript* instance = me->GetInstanceScript())
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->JustSummoned(me);

                me->Say("Shit, i just got summoned", LANG_UNIVERSAL);
                DoCastAOE(SPELL_MOLTEN_SEED_MISSILE_TARGET_SEARCH);
                me->AddAura(SPELL_MOLTEN_ELEMENTAL_INVIS_PRE_VISUAL, me);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_MOLTEN_SEED_MISSILE_HIT || caster->GetGUID() != SeedCasterGUID)
                    return;

                me->Say("APPEAR!", LANG_UNIVERSAL);
                me->RemoveAurasDueToSpell(SPELL_MOLTEN_ELEMENTAL_INVIS_PRE_VISUAL);
                DoCast(SPELL_MOLTEN_SEED_COUNTDOWN);

                if (!me->GetMap()->IsHeroic())
                    return;

                scheduler.Schedule(Milliseconds(8200), [this](TaskContext)
                {
                    DoCast(SPELL_MOLTEN_ELEMENTAL_MOLTEN_POWER);
                });
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_MOLTEN_SEED_MISSILE_TARGET_SEARCH)
                    return;

                SeedCasterGUID = target->GetGUID();
            }

            void UpdateAI(uint32 diff) override
            {
                ScriptedAI::UpdateAI(diff);
                scheduler.Update(diff);
            }

        private:
            ObjectGuid SeedCasterGUID;
            TaskScheduler scheduler;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_fl_ragnaros_molten_elementalAI>(creature);
        }
};

// http://www.wowhead.com/npc=53231/lava-scion
class npc_ragnaros_lava_scion : public CreatureScript
{
    public:
        npc_ragnaros_lava_scion() : CreatureScript("npc_ragnaros_lava_scion") { }

        struct npc_ragnaros_lava_scionAI : public CreatureAI
        {
            npc_ragnaros_lava_scionAI(Creature* creature) : CreatureAI(creature) { }

            void SpellHitTarget(Unit* target, SpellInfo const* spell) override
            {
                if (spell->Id != SPELL_BLAZING_HEAT)
                    return;

                Talk(EMOTE_WHISPER_LAVA_SCION_BLAZING_HEAT, target);
            }

            void EnterCombat(Unit* /*who*/) override
            {
                scheduler.Schedule(Seconds(12), Seconds(15), [this](TaskContext context)
                {
                    DoCastAOE(SPELL_BLAZING_HEAT_TARGET_SEARCH);
                    context.Repeat(Seconds(20), Seconds(23));
                });
            }

            void UpdateAI(uint32 diff) override
            {
                scheduler.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                DoMeleeAttackIfReady();
            }

        private:
            TaskScheduler scheduler;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_lava_scionAI>(creature);
        }
};

// http://www.wowhead.com/npc=53872/cenarius
class npc_ragnaros_cenarius : public CreatureScript
{
    public:
        npc_ragnaros_cenarius() : CreatureScript("npc_ragnaros_cenarius") { }

        struct npc_ragnaros_cenariusAI : public PassiveAI
        {
            npc_ragnaros_cenariusAI(Creature* creature) : PassiveAI(creature), _summons(creature) { }

            void InitializeAI() override
            {
                if (!me->IsAlive())
                    return;

                JustRespawned();
            }

            void JustRespawned() override
            {
                Movement::PointsArray path(CenariusPath, CenariusPath + CenariusPathSize);
                me->GetMotionMaster()->MovePoint(1, CenariusPath[CenariusPathSize - 1].x, CenariusPath[CenariusPathSize - 1].y, CenariusPath[CenariusPathSize - 1].z);

                Movement::MoveSplineInit init(me);
                init.MovebyPath(path);
                init.SetVelocity(24.0f);
                init.SetWalk(true);
                init.SetSmooth();
                init.SetFacing(me->GetOrientation());
                init.Launch();
            }

            void JustSummoned(Creature* summon) override
            {
                _summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                _summons.Despawn(summon);
            }

            void EnterEvadeMode(EvadeReason /*why*/) override
            {
                _summons.DespawnAll();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (InstanceScript* instance = me->GetInstanceScript())
                {
                    if (Creature* ragnaros = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_RAGNAROS)))
                        if (ragnaros->IsAIEnabled)
                            ragnaros->AI()->DoAction(ACTION_RAGNAROS_HEROIC_SUBMERGE);
                    if (Creature* hamuul = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_HAMUUL_RUNETOTEM)))
                        if (hamuul->IsAIEnabled)
                            hamuul->AI()->DoAction(ACTION_RAGNAROS_HEROIC_SUBMERGE);
                    if (Creature* malfurion = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_MALFURION_STORMRAGE)))
                        if (malfurion->IsAIEnabled)
                            malfurion->AI()->DoAction(ACTION_RAGNAROS_HEROIC_SUBMERGE);
                }

                _events.ScheduleEvent(EVENT_HEROIC_CENARIUS_1, 3.25 * IN_MILLISECONDS);
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HEROIC_CENARIUS_1:
                            Talk(SAY_CENARIUS_HEROIC_INTRO);
                            _events.ScheduleEvent(EVENT_DRAW_OUT_FIRELORD, 6 * IN_MILLISECONDS);
                            break;
                        case EVENT_DRAW_OUT_FIRELORD:
                            DoCastAOE(SPELL_CENARIUS_DRAW_OUT_FIRELORD, true);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
            SummonList _summons;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_cenariusAI>(creature);
        }
};

// http://www.wowhead.com/npc=53875/malfurion-stormrage
class npc_ragnaros_malfurion_stormrage : public CreatureScript
{
    public:
        npc_ragnaros_malfurion_stormrage() : CreatureScript("npc_ragnaros_malfurion_stormrage") { }

        struct npc_ragnaros_malfurion_stormrageAI : public PassiveAI
        {
            npc_ragnaros_malfurion_stormrageAI(Creature* creature) : PassiveAI(creature), _summons(creature) { }

            void InitializeAI() override
            {
                if (!me->IsAlive())
                    return;

                JustRespawned();
            }

            void JustRespawned() override
            {
                Movement::PointsArray path(MalfurionPath, MalfurionPath + MalfurionPathSize);
                me->GetMotionMaster()->MovePoint(1, MalfurionPath[MalfurionPathSize - 1].x, MalfurionPath[MalfurionPathSize - 1].y, MalfurionPath[MalfurionPathSize - 1].z);
                
                Movement::MoveSplineInit init(me);
                init.MovebyPath(path);
                init.SetVelocity(24.0f);
                init.SetFly();
                init.SetSmooth();
                init.SetFacing(0.0f);
                init.Launch();
            }

            void JustSummoned(Creature* summon) override
            {
                _summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                _summons.Despawn(summon);
            }

            void EnterEvadeMode(EvadeReason /*why*/) override
            {
                _summons.DespawnAll();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                    return;

                if (id == 1)
                    _events.ScheduleEvent(EVENT_MALFURION_LAND, 0);
                else if (id == 2)
                {
                    me->SetDisableGravity(false);
                    me->CastSpell(me, SPELL_TRANSFORM_MALFURION, true);
                }
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case ACTION_RAGNAROS_HEROIC_SUBMERGE:
                        _events.ScheduleEvent(EVENT_DRAW_OUT_FIRELORD, 8 * IN_MILLISECONDS);
                        break;
                    case ACTION_MALFURION_HEROIC_INTRO:
                        _events.ScheduleEvent(EVENT_HEROIC_MALFURION_1, 5.2 * IN_MILLISECONDS);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MALFURION_LAND:
                        {
                            Position pos = { me->GetPositionZ(), me->GetPositionY(), me->GetMap()->GetHeight(me->GetPhaseMask(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()) };
                            me->GetMotionMaster()->MoveLand(2, pos);
                            break;
                        }
                        case EVENT_DRAW_OUT_FIRELORD:
                            DoCastAOE(SPELL_MALFURION_DRAW_OUT_FIRELORD, true);
                            break;
                        case EVENT_HEROIC_MALFURION_1:
                            Talk(SAY_MALFURION_HEROIC_INTRO);
                            me->PlayOneShotAnimKitId(ANIM_KIT_TALK);
                            _events.ScheduleEvent(EVENT_CLOUDBURST, 18 * IN_MILLISECONDS);
                            break;
                        case EVENT_CLOUDBURST:
                            DoCastAOE(SPELL_CLOUDBURST, true);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
            SummonList _summons;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_malfurion_stormrageAI>(creature);
        }
};

// http://www.wowhead.com/npc=53876/arch-druid-hamuul-runetotem
class npc_ragnaros_hamuul_runetotem : public CreatureScript
{
    public:
        npc_ragnaros_hamuul_runetotem() : CreatureScript("npc_ragnaros_hamuul_runetotem") { }

        struct npc_ragnaros_hamuul_runetotemAI : public PassiveAI
        {
            npc_ragnaros_hamuul_runetotemAI(Creature* creature) : PassiveAI(creature), _summons(creature) { }

            void InitializeAI() override
            {
                if (!me->IsAlive())
                    return;

                JustRespawned();
            }

            void JustRespawned() override
            {
                Movement::PointsArray path(HamuulPath, HamuulPath + HamuulPathSize);
                me->GetMotionMaster()->MovePoint(1, HamuulPath[HamuulPathSize - 1].x, HamuulPath[HamuulPathSize - 1].y, HamuulPath[HamuulPathSize - 1].z);
                
                Movement::MoveSplineInit init(me);
                init.MovebyPath(path);
                init.SetVelocity(24.0f);
                init.SetFly();
                init.SetSmooth();
                init.SetFacing(0.0f);
                init.Launch();
            }

            void JustSummoned(Creature* summon) override
            {
                _summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon) override
            {
                _summons.Despawn(summon);
            }

            void EnterEvadeMode(EvadeReason /*why*/) override
            {
                _summons.DespawnAll();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
                    return;

                if (id == 1)
                    _events.ScheduleEvent(EVENT_HAMUUL_LAND, 0);
                else if (id == 2)
                {
                    me->SetDisableGravity(false);
                    me->CastSpell(me, SPELL_TRANSFORM_HAMUUL, true);
                }
            }

            void DoAction(int32 action) override
            {
                switch (action)
                {
                    case ACTION_RAGNAROS_HEROIC_SUBMERGE:
                        _events.ScheduleEvent(EVENT_DRAW_OUT_FIRELORD, 7 * IN_MILLISECONDS);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HAMUUL_LAND:
                        {
                            Position pos = { me->GetPositionZ(), me->GetPositionY(), me->GetMap()->GetHeight(me->GetPhaseMask(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()) };
                            me->GetMotionMaster()->MoveLand(2, pos);
                            break;
                        }
                        case EVENT_DRAW_OUT_FIRELORD:
                            DoCastAOE(SPELL_HAMUUL_DRAW_OUT_FIRELORD, true);
                            break;
                        default:
                            break;
                    }
                }
            }

        private:
            EventMap _events;
            SummonList _summons;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_hamuul_runetotemAI>(creature);
        }
};

// http://www.wowhead.com/npc=54203/dreadflame-spawn
class npc_ragnaros_dreadflame_spawn : public CreatureScript
{
    public:
        npc_ragnaros_dreadflame_spawn() : CreatureScript("npc_ragnaros_dreadflame_spawn") { }

        struct npc_ragnaros_dreadflame_spawnAI : public PassiveAI
        {
            npc_ragnaros_dreadflame_spawnAI(Creature* creature) : PassiveAI(creature) { }

            void IsSummonedBy(Unit* /*summoner*/) override
            {
                if (Player* player = me->SelectNearestPlayer(3.0f))
                    if (!player->HasAura(SPELL_DELUGE_AURA))
                        return;

                InstanceScript* instance = me->GetInstanceScript();
                if (!instance)
                    return;

                Creature* dreadflame = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_DREADFLAME));
                if (!dreadflame)
                    return;

                dreadflame->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), SPELL_DREADFLAME_SPAWN, true);
            }
            
            void EnterEvadeMode(EvadeReason why) override { }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_ragnaros_dreadflame_spawnAI>(creature);
        }
};

// http://www.wowhead.com/npc=53953/breadth-of-frost
class npc_ragnaros_breadth_of_frost : public CreatureScript
{
    public:
    npc_ragnaros_breadth_of_frost() : CreatureScript("npc_ragnaros_breadth_of_frost") {}

    struct npc_ragnaros_breadth_of_frostAI : public PassiveAI
    {
        npc_ragnaros_breadth_of_frostAI(Creature* creature) : PassiveAI(creature) { }

        void EnterEvadeMode(EvadeReason /*why*/) override {}

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        {
            if (spell->Id != SPELL_BREADTH_OF_FROST_METEOR_AURA)
                return;

            me->RemoveAurasDueToSpell(SPELL_BREADTH_OF_FROST_TARGET_SEARCH);
        }

        void IsSummonedBy(Unit* /*summoner*/) override
        {
            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* cenarius = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_CENARIUS)))
                    cenarius->CastSpell(me, SPELL_BREADTH_OF_FROST);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetFirelandsAI<npc_ragnaros_breadth_of_frostAI>(creature);
    }
};

// http://www.wowhead.com/npc=54074/entrapping-roots
class npc_ragnaros_entrapping_roots : public CreatureScript
{
    public:
    npc_ragnaros_entrapping_roots() : CreatureScript("npc_ragnaros_entrapping_roots") {}

    struct npc_ragnaros_entrapping_rootsAI : public PassiveAI
    {
        npc_ragnaros_entrapping_rootsAI(Creature* creature) : PassiveAI(creature) {}

        void EnterEvadeMode(EvadeReason /*why*/) override { }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        {
            if (spell->Id != SPELL_ENTRAPPING_ROOTS_TARGET_SEARCH)
                return;

            me->RemoveAurasDueToSpell(SPELL_ENTRAPPING_ROOTS_PERIODIC);
        }

        void IsSummonedBy(Unit* /*summoner*/) override
        {
            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* hamuul = ObjectAccessor::GetCreature(*me, instance->GetGuidData(NPC_HAMUUL_RUNETOTEM)))
                    hamuul->CastSpell(me, SPELL_ENTRAPPING_ROOTS);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetFirelandsAI<npc_ragnaros_entrapping_rootsAI>(creature);
    }
};

// http://www.wowhead.com/npc=54147/cloudburst
class npc_ragnaros_cloudburst : public CreatureScript
{
    public:
    npc_ragnaros_cloudburst() : CreatureScript("npc_ragnaros_cloudburst") {}

    struct npc_ragnaros_cloudburstAI : public PassiveAI
    {
        npc_ragnaros_cloudburstAI(Creature* creature) : PassiveAI(creature) {}

        void EnterEvadeMode(EvadeReason why) override {}

        void IsSummonedBy(Unit* summoner) override
        {
            charges = me->GetMap()->Is25ManRaid() ? 3 : 1;
            me->CastSpell(me, SPELL_CLOUDBURST_VISUAL, true);
        }

        void OnSpellClick(Unit* clicker, bool& result) override
        {
            if (!result || charges == 0 || clicker->HasAura(SPELL_DELUGE_AURA))
                return;

            /*clicker->CastSpell(clicker, SPELL_DELUGE_AURA, true);*/
            --charges;
            if (charges == 0)
            {
                result = false;
                me->DespawnOrUnsummon();
            }
        }

        void UpdateAI(uint32 /*diff*/) override {}

        private:
        uint32 charges;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetFirelandsAI<npc_ragnaros_cloudburstAI>(creature);
    }
};


// Spawn
// 1.2 seconds, choose target (apply threat only, 100 000 000)
// 1.2 seconds, cast combustible (99296), cast proximity check (99269), start moving to target, apply speed boost trigger(100278)
// 1.2 seconds, cast fixate (99849) and repeat every 1.2 seconds for some reason
// http://www.wowhead.com/npc=53500/living-meteor
class npc_fl_ragnaros_living_meteor : public CreatureScript
{
    public:
        npc_fl_ragnaros_living_meteor() : CreatureScript("npc_fl_ragnaros_living_meteor") {}

        struct npc_fl_ragnaros_living_meteorAI : public PassiveAI
        {
            npc_fl_ragnaros_living_meteorAI(Creature* creature) : PassiveAI(creature) {}

            void Reset() override
            {
                DoCast(SPELL_LIVING_METEOR_DAMAGE_REDUCTION);
                scheduler.Schedule(Milliseconds(1200), [this](TaskContext context)
                {
                    Unit* target = GetRandomFocusTarget(200.0f, CurrentTarget);
                    if (!target)
                    {
                        context.Repeat();
                        return;
                    }

                    me->AddThreat(target, 100000000);
                    context.Schedule(Milliseconds(1200), [this, target](TaskContext context)
                    {
                        DoCast(SPELL_LIVING_METEOR_COMBUSTIBLE);
                        DoCast(SPELL_LIVING_METEOR_PROXIMITY_CHECK);
                        me->GetMotionMaster()->MoveChase(target);
                        me->AddAura(SPELL_LIVING_METEOR_SPEED_TRIGGER, me);
                        context.Schedule(Milliseconds(1200), [this](TaskContext context)
                        {
                            DoCast(SPELL_LIVING_METEOR_FIXATE_VISUAL);
                            context.Repeat();
                        });
                    });
                });
            }

            void UpdateAI(uint32 diff) override
            {
                PassiveAI::UpdateAI(diff);
                scheduler.Update(diff);
            }

        private:
            ObjectGuid CurrentTarget;
            TaskScheduler scheduler;
            Unit* GetRandomFocusTarget(float distance, ObjectGuid ignore = ObjectGuid::Empty)
            {
                std::list<Player*> players;
                Trinity::AnyPlayerInObjectRangeCheck checker(me, distance);
                Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
                me->VisitNearbyWorldObject(distance, searcher);

                players.remove_if([](Player* player)
                {
                    return player->IsGameMaster();
                });

                if (Player* player = ObjectAccessor::GetPlayer(*me, CurrentTarget))
                    players.remove(player);

                return Trinity::Containers::SelectRandomContainerElement(players);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetFirelandsAI<npc_fl_ragnaros_living_meteorAI>(creature);
        }
};

// http://www.wowhead.com/spell=98951/splitting-blow
// http://www.wowhead.com/spell=98952/splitting-blow
// http://www.wowhead.com/spell=98953/splitting-blow
class spell_ragnaros_splitting_blow : public SpellScriptLoader
{
    public:
        spell_ragnaros_splitting_blow() : SpellScriptLoader("spell_ragnaros_splitting_blow") {}

        class spell_ragnaros_splitting_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_splitting_blow_SpellScript);

            void SelectTarget(WorldObject*& target)
            {
                target = static_cast<WorldObject*>(NULL);
                Creature* ragnaros = GetCaster()->ToCreature();
                if (!ragnaros || !ragnaros->IsAIEnabled)
                    return;

                switch (GetSpellInfo()->Id)
                {
                    case SPELL_SPLITTING_BLOW_WEST:
                        target = ObjectAccessor::GetCreature(*ragnaros, ragnaros->AI()->GetGUID(DATA_SPLITTING_BLOW_WEST));
                        break;
                    case SPELL_SPLITTING_BLOW_MIDDLE:
                        target = ObjectAccessor::GetCreature(*ragnaros, ragnaros->AI()->GetGUID(DATA_SPLITTING_BLOW_MIDDLE));
                        break;
                    case SPELL_SPLITTING_BLOW_EAST:
                        target = ObjectAccessor::GetCreature(*ragnaros, ragnaros->AI()->GetGUID(DATA_SPLITTING_BLOW_EAST));
                        break;
                    default:
                        break;
                }
            }
            void Register() override
            {
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_ragnaros_splitting_blow_SpellScript::SelectTarget, EFFECT_0, TARGET_DEST_NEARBY_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_splitting_blow_SpellScript();
        }
};

// http://www.wowhead.com/spell=99012/splitting-blow
class spell_ragnaros_splitting_blow_dummy : public SpellScriptLoader
{
    public:
        spell_ragnaros_splitting_blow_dummy() : SpellScriptLoader("spell_ragnaros_splitting_blow_dummy") { }

        class spell_ragnaros_splitting_blow_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_splitting_blow_dummy_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SPLITTING_BLOW_TRIGGERED))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* target = GetHitCreature();
                if (!target)
                    return;

                target->CastSpell(target, (uint32)GetEffectValue(), true);
                target->CastSpell(target, GetSpellInfo()->GetEffect(EFFECT_1)->BasePoints, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_SPLITTING_BLOW;
                });
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_splitting_blow_dummy_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_splitting_blow_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_splitting_blow_dummy_SpellScript();
        }
};

// http://www.wowhead.com/spell=99054/invoke-sons
class spell_ragnaros_invoke_sons : public SpellScriptLoader
{
    public:
        spell_ragnaros_invoke_sons() : SpellScriptLoader("spell_ragnaros_invoke_sons") { }

        class spell_ragnaros_invoke_sons_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_invoke_sons_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SPLITTING_BLOW_TRIGGERED))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_INVOKE_SONS_MISSLE, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_SON_OF_FLAME;
                });
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_invoke_sons_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_invoke_sons_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_invoke_sons_SpellScript();
        }
};

// http://www.wowhead.com/spell=101107/rage-of-ragnaros
class spell_rage_of_ragnaros_dummy : public SpellScriptLoader
{
    public:
        spell_rage_of_ragnaros_dummy() : SpellScriptLoader("spell_rage_of_ragnaros_dummy") { }

        class spell_rage_of_ragnaros_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rage_of_ragnaros_dummy_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_RAGE_OF_RAGNAROS))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Creature* caster = GetCaster()->ToCreature();
                Player* player = GetHitPlayer();
                if (!caster || !caster->IsAIEnabled || !player)
                    return;

                caster->CastSpell(player, uint32(GetEffectValue()), true);
                caster->AI()->Talk(SAY_RAGNAROS_RAGE_OF_RAGNAROS, player);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(HeartOfFlameCheck());
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_rage_of_ragnaros_dummy_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rage_of_ragnaros_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_rage_of_ragnaros_dummy_SpellScript();
        }
};

// http://www.wowhead.com/spell=101110/rage-of-ragnaros
class spell_rage_of_ragnaros : public SpellScriptLoader
{
    public:
        spell_rage_of_ragnaros() : SpellScriptLoader("spell_rage_of_ragnaros") { }

        class spell_rage_of_ragnaros_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rage_of_ragnaros_AuraScript);

            bool Load() override
            {
                return GetCaster()->GetTypeId() == TYPEID_UNIT && GetTarget()->GetTypeId() == TYPEID_PLAYER;
            }

            void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                Creature* creature = caster->ToCreature();
                if (!creature || !creature->IsAIEnabled)
                    return;

                creature->AI()->Talk(EMOTE_RAGE_OF_RAGNAROS, GetTarget());
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_rage_of_ragnaros_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rage_of_ragnaros_AuraScript();
        }
};

// http://www.wowhead.com/spell=99216/engulfing-flames-near-visual
// http://www.wowhead.com/spell=99217/engulfing-flames-middle-visual
// http://www.wowhead.com/spell=99218/engulfing-flames-far-visual

// http://www.wowhead.com/spell=99172/engulfing-flames
// http://www.wowhead.com/spell=100175/engulfing-flames
// http://www.wowhead.com/spell=100176/engulfing-flames
// http://www.wowhead.com/spell=100177/engulfing-flames

// http://www.wowhead.com/spell=99235/engulfing-flames
// http://www.wowhead.com/spell=100178/engulfing-flames
// http://www.wowhead.com/spell=100179/engulfing-flames
// http://www.wowhead.com/spell=100180/engulfing-flames

// http://www.wowhead.com/spell=99236/engulfing-flames
// http://www.wowhead.com/spell=100181/engulfing-flames
// http://www.wowhead.com/spell=100182/engulfing-flames
// http://www.wowhead.com/spell=100183/engulfing-flames
class spell_engulfing_flames : public SpellScriptLoader
{
    public:
        spell_engulfing_flames() : SpellScriptLoader("spell_engulfing_flames") { }

        class spell_engulfing_flames_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_engulfing_flames_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                uint32 spellId = GetSpellInfo()->Id;

                targets.remove_if([spellId](WorldObject* target)
                {
                    Creature* _target = target->ToCreature();
                    if (!_target || !_target->IsAIEnabled || target->GetEntry() != NPC_ENGULFING_FLAMES)
                        return true;

                    uint32 engulfingId = _target->AI()->GetData(DATA_ENGULFING_FLAMES_ID);
                    switch (spellId)
                    {
                        case SPELL_ENGULFING_FLAMES_NEAR:
                        case SPELL_ENGULFING_FLAMES_NEAR_VISUAL:
                            return engulfingId != DATA_ENGULFING_FLAMES_NEAR;
                        case SPELL_ENGULFING_FLAMES_MIDDLE:
                        case SPELL_ENGULFING_FLAMES_MIDDLE_VISUAL:
                            return engulfingId != DATA_ENGULFING_FLAMES_MIDDLE;
                        case SPELL_ENGULFING_FLAMES_FAR:
                        case SPELL_ENGULFING_FLAMES_FAR_VISUAL:
                            return engulfingId != DATA_ENGULFING_FLAMES_FAR;
                        default:
                            break;
                    }

                    return true;
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_engulfing_flames_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_engulfing_flames_SpellScript();
        }
};

// http://www.wowhead.com/spell=99171/engulfing-flames
class spell_world_in_flames : public SpellScriptLoader
{
    public:
        spell_world_in_flames() : SpellScriptLoader("spell_world_in_flames") { }

        class spell_world_in_flames_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_world_in_flames_SpellScript);

            bool Load() override
            {
                return GetCaster()->GetTypeId() == TYPEID_UNIT;
            }

            void HandleEngulfingNear(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* ragnaros = GetCaster()->ToCreature();
                if (!ragnaros || !ragnaros->IsAIEnabled)
                    return;

                uint32 engulfing = ragnaros->AI()->GetData(DATA_NEW_ENGULFING_FLAME);
                ragnaros->AI()->SetData(DATA_PREVIOUS_ENGULFING_FLAME, engulfing);
                
                uint32 visual = EngulfingFlames[engulfing][ID_ENGULFING_FLAME_VISUAL];
                uint32 cast = EngulfingFlames[engulfing][ID_ENGULFING_FLAME_CAST];
                ragnaros->CastSpell(static_cast<Unit*>(nullptr), visual, true);
                ragnaros->CastSpell(static_cast<Unit*>(nullptr), cast);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_world_in_flames_SpellScript::HandleEngulfingNear, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_world_in_flames_SpellScript();
        }
};

// http://www.wowhead.com/spell=98982/submerge
// http://www.wowhead.com/spell=100295/submerge
// http://www.wowhead.com/spell=100296/submerge
// http://www.wowhead.com/spell=100297/submerge
class spell_ragnaros_submerge : public SpellScriptLoader
{
    public:
        spell_ragnaros_submerge() : SpellScriptLoader("spell_ragnaros_submerge") { }

        class spell_ragnaros_submerge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_submerge_SpellScript);

            bool Load() override
            {
                return GetCaster()->GetTypeId() == TYPEID_UNIT;
            }

            void HandleEngulfingNear(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* ragnaros = GetHitCreature();
                if (!ragnaros)
                    return;

                ragnaros->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_submerge_SpellScript::HandleEngulfingNear, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_submerge_SpellScript();
        }
};

// http://www.wowhead.com/spell=98703/sulfuras-smash
class spell_sulfuras_smash_player_trigger : public SpellScriptLoader
{
    public:
        spell_sulfuras_smash_player_trigger() : SpellScriptLoader("spell_sulfuras_smash_player_trigger") { }

        class spell_sulfuras_smash_player_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sulfuras_smash_player_trigger_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
                if (targets.empty())
                    return;

                Trinity::Containers::RandomResizeList(targets, 1);
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sulfuras_smash_player_trigger_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_sulfuras_smash_player_trigger_SpellScript();
        }
};

// http://www.wowhead.com/spell=98710/sulfuras-smash
// http://www.wowhead.com/spell=100890/sulfuras-smash
// http://www.wowhead.com/spell=100891/sulfuras-smash
// http://www.wowhead.com/spell=100892/sulfuras-smash
class spell_ragnaros_sulfuras_smash : public SpellScriptLoader
{
    public:
        spell_ragnaros_sulfuras_smash() : SpellScriptLoader("spell_ragnaros_sulfuras_smash") { }

        class spell_ragnaros_sulfuras_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_sulfuras_smash_SpellScript);

            bool Load() override
            {
                return GetCaster()->GetInstanceScript() != nullptr;
            }

            void SelectTransport(WorldObject*& target)
            {
                if (Creature* sulfurasSmash = GetCaster()->FindNearestCreature(NPC_SULFURAS_SMASH, 50.0f))
                    target = sulfurasSmash;
                else
                    FinishCast(SPELL_FAILED_NO_VALID_TARGETS);
                /*if (InstanceScript* instance = target->GetInstanceScript())
                    target = HashMapHolder<GameObject>::Find(instance->GetGuidData(DATA_ICECROWN_GUNSHIP_BATTLE));*/
            }

            //void RelocateDest(SpellEffIndex /*effIndex*/)
            //{
            //    if (GetCaster()->GetInstanceScript()->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
            //        GetHitDest()->RelocateOffset({ 0.0f, 0.0f, 36.0f, 0.0f });
            //    else
            //        GetHitDest()->RelocateOffset({ 0.0f, 0.0f, 21.0f, 0.0f });
            //}

            void Register() override
            {
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_ragnaros_sulfuras_smash_SpellScript::SelectTransport, EFFECT_0, TARGET_DEST_NEARBY_ENTRY);
                /*OnEffectLaunch += SpellEffectFn(spell_ragnaros_sulfuras_smash_SpellScript::RelocateDest, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);*/
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_sulfuras_smash_SpellScript();
        }
};

// http://www.wowhead.com/spell=98708/sulfuras-smash
class spell_ragnaros_sulfuras_smash_damage : public SpellScriptLoader
{
    public:
        spell_ragnaros_sulfuras_smash_damage() : SpellScriptLoader("spell_ragnaros_sulfuras_smash_damage") { }

        class spell_ragnaros_sulfuras_smash_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_sulfuras_smash_damage_SpellScript);

            void SelectSulfurasSmash(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetEntry() != NPC_SULFURAS_SMASH;
                });
            }

            void SelectLavaWaves(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetEntry() != NPC_LAVA_WAVE;
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_sulfuras_smash_damage_SpellScript::SelectSulfurasSmash, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_sulfuras_smash_damage_SpellScript::SelectLavaWaves, EFFECT_2, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_sulfuras_smash_damage_SpellScript();
        }
};

// http://www.wowhead.com/spell=101088/lavalogged
// http://www.wowhead.com/spell=101102/lavalogged
class spell_ragnaros_lavalogged : public SpellScriptLoader
{
    public:
        spell_ragnaros_lavalogged() : SpellScriptLoader("spell_ragnaros_lavalogged") { }

        class spell_ragnaros_lavalogged_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_lavalogged_SpellScript);

            void SelectLavaWaves(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR && target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR_25N &&
                        target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR_10H && target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR_25H;
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_lavalogged_SpellScript::SelectLavaWaves, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_lavalogged_SpellScript();
        }
};

// http://www.wowhead.com/spell=98928/lava-wave
class spell_ragnaros_lava_wave : public SpellScriptLoader
{
    public:
        spell_ragnaros_lava_wave() : SpellScriptLoader("spell_ragnaros_lava_wave") {}

        class spell_ragnaros_lava_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_lava_wave_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetCaster()->Say("I should have knocked back", LANG_UNIVERSAL);
                GetHitUnit()->Say("I should have been knocked back", LANG_UNIVERSAL);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([this](WorldObject* target)
                {
                    return target->GetTypeId() != TYPEID_PLAYER || target->ToUnit()->HasAura(GetSpellInfo()->Id);
                });
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_lava_wave_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_LEAP_BACK);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_lava_wave_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_lava_wave_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_lava_wave_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_lava_wave_SpellScript();
        }
};

// http://www.wowhead.com/spell=98473/burning-speed
class spell_ragnaros_burning_speed : public SpellScriptLoader
{
    public:
        spell_ragnaros_burning_speed() : SpellScriptLoader("spell_ragnaros_burning_speed") { }

        class spell_ragnaros_burning_speed_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ragnaros_burning_speed_AuraScript);

            void HandleDummyTick(AuraEffect const* aurEff)
            {
                int32 stacks = GetTarget()->GetHealthPct() - 50;
                stacks /= 5;
                if (stacks > 0)
                    GetTarget()->SetAuraStack(SPELL_BURNING_SPEED, GetTarget(), stacks);
                else
                    GetTarget()->RemoveAura(SPELL_BURNING_SPEED);
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_ragnaros_burning_speed_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_ragnaros_burning_speed_AuraScript();
        }
};

// http://www.wowhead.com/spell=98159/magma-trap
class spell_ragnaros_magma_trap : public SpellScriptLoader
{
    public:
        spell_ragnaros_magma_trap() : SpellScriptLoader("spell_ragnaros_magma_trap") {}

        class spell_ragnaros_magma_trap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_magma_trap_SpellScript);

            void HitTarget(SpellEffIndex effIndex)
            {
                GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()));
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target)
                {
                    return target->GetTypeId() != TYPEID_PLAYER;
                });

                if (!targets.empty())
                    Trinity::Containers::RandomResizeList(targets, 1);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_magma_trap_SpellScript::HitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_magma_trap_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_magma_trap_SpellScript();
        }
};

// http://www.wowhead.com/spell=98171/magma-trap
class spell_ragnaros_magma_trap_dummy : public SpellScriptLoader
{
    public:
        spell_ragnaros_magma_trap_dummy() : SpellScriptLoader("spell_ragnaros_magma_trap_dummy") {}

        class spell_ragnaros_magma_trap_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_magma_trap_dummy_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target)
                {
                    return target->GetTypeId() != TYPEID_PLAYER;
                });

                if (targets.size() > 1)
                {
                    targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));
                    targets.resize(1);
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_magma_trap_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_magma_trap_dummy_SpellScript();
        }
};

// http://www.wowhead.com/spell=98175/magma-trap-eruption
class spell_ragnaros_magma_trap_eruption : public SpellScriptLoader
{
    public:
        spell_ragnaros_magma_trap_eruption() : SpellScriptLoader("spell_ragnaros_magma_trap_eruption") { }

        class spell_ragnaros_magma_trap_eruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_magma_trap_eruption_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGMA_TRAP_VULNERABILITY))
                    return false;
                return true;
            }

            void ChangeDamage()
            {
                //if (Aura* vulnerability = GetHitUnit()->GetAura(SPELL_MAGMA_TRAP_VULNERABILITY))
                //    SetHitDamage(GetHitDamage() * CalculatePct(1.0f, vulnerability->GetEffect(EFFECT_0)->GetAmount()));
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_ragnaros_magma_trap_eruption_SpellScript::ChangeDamage);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_magma_trap_eruption_SpellScript();
        }
};

// http://www.wowhead.com/spell=98259/wrath-of-ragnaros
// http://www.wowhead.com/spell=98260/wrath-of-ragnaros
// http://www.wowhead.com/spell=100110/wrath-of-ragnaros
// http://www.wowhead.com/spell=100111/wrath-of-ragnaros
class spell_ragnaros_wrath_of_ragnaros : public SpellScriptLoader
{
    public:
        spell_ragnaros_wrath_of_ragnaros() : SpellScriptLoader("spell_ragnaros_wrath_of_ragnaros") {}

        class spell_ragnaros_wrath_of_ragnaros_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ragnaros_wrath_of_ragnaros_SpellScript);

            void HitTarget(SpellEffIndex effIndex)
            {
                GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 3 : 1);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_ragnaros_wrath_of_ragnaros_SpellScript::HitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_wrath_of_ragnaros_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_ragnaros_wrath_of_ragnaros_SpellScript();
        }
};

// http://www.wowhead.com/spell=100823/dreadflame-control-aura
class spell_dreadflame_deluge_control_aura : public SpellScriptLoader
{
    public:
        spell_dreadflame_deluge_control_aura() : SpellScriptLoader("spell_dreadflame_deluge_control_aura") { }

        class spell_dreadflame_deluge_control_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dreadflame_deluge_control_aura_SpellScript);

            bool Load() override
            {
                dreadflamesRemoveList.clear();
                return true;
            }

            void HandleDeluge()
            {
                for (auto guid : dreadflamesRemoveList)
                {
                    DynamicObject* dreadflame = ObjectAccessor::GetDynamicObject(*GetCaster(), guid);
                    if (!dreadflame)
                        continue;

                    GetCaster()->CastSpell(dreadflame->GetPositionX(), dreadflame->GetPositionY(), dreadflame->GetPositionZ(), SPELL_DELUGE_EXTINGUISH_DREADFLAME, true);
                    dreadflame->Remove();
                }
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
                if (targets.empty())
                    return;

                targets.remove_if([](WorldObject* target)
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        return !target->ToPlayer()->HasAura(SPELL_DELUGE_AURA);

                    return true;
                });

                for (auto target : targets)
                    if (DreadflameAI* ai = CAST_AI(DreadflameAI, GetCaster()->GetAI()))
                        if (DynamicObject* dreadflame = ai->GetNearestLitDreadflameDynamicObject(target))
                            if (target->IsWithinDistInMap(dreadflame, 3.0f))
                                dreadflamesRemoveList.push_back(dreadflame->GetGUID());

                targets.clear();
                dreadflamesRemoveList.sort();
                dreadflamesRemoveList.unique();
            }

            void Register() override
            {
                OnCast += SpellCastFn(spell_dreadflame_deluge_control_aura_SpellScript::HandleDeluge);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dreadflame_deluge_control_aura_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }

            std::list<ObjectGuid> dreadflamesRemoveList;
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dreadflame_deluge_control_aura_SpellScript();
        }
};

// http://www.wowhead.com/spell=100966/dreadflame-control-aura
class spell_dreadflame_damage_control_aura : public SpellScriptLoader
{
    public:
        spell_dreadflame_damage_control_aura() : SpellScriptLoader("spell_dreadflame_damage_control_aura") { }

        class spell_dreadflame_damage_control_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dreadflame_damage_control_aura_SpellScript);

            void OnSpellHit(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_DREADFLAME_DAMAGE, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
                if (targets.empty())
                    return;

                targets.remove_if([](WorldObject* target)
                {
                    if (Player* player = target->ToPlayer())
                        return player->HasAura(SPELL_DELUGE_AURA);

                    return false;
                });

                DreadflameAI* ai = CAST_AI(DreadflameAI, GetCaster()->GetAI());
                std::list<WorldObject*> targetList;
                for (auto target : targets)
                    if (ai->IsNearbyDreadflame(target, 4.0f))
                        targetList.push_back(target);

                targets = targetList;
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dreadflame_damage_control_aura_SpellScript::OnSpellHit, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dreadflame_damage_control_aura_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dreadflame_damage_control_aura_SpellScript();
        }
};

// http://www.wowhead.com/spell=100906/dreadflame-control-aura
class spell_dreadflame_spawn_control_aura : public SpellScriptLoader
{
    public:
        spell_dreadflame_spawn_control_aura() : SpellScriptLoader("spell_dreadflame_spawn_control_aura") { }

        class spell_dreadflame_spawn_control_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dreadflame_spawn_control_aura_SpellScript);

            void OnSpellHit(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit()->GetPositionX(), GetHitUnit()->GetPositionY(), GetHitUnit()->GetPositionZ(), SPELL_DREADFLAME_SPAWN, true);
                if (Creature* creature = GetHitCreature())
                    creature->DespawnOrUnsummon();
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target)
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_DREADFLAME_SPAWN;
                });
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dreadflame_spawn_control_aura_SpellScript::OnSpellHit, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dreadflame_spawn_control_aura_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dreadflame_spawn_control_aura_SpellScript();
        }
};

// http://www.wowhead.com/spell=100695/dreadflame-control-aura
// http://www.wowhead.com/spell=100952/dreadflame-control-aura
class spell_dreadflame_spread_control_aura : public SpellScriptLoader
{
    public:
        spell_dreadflame_spread_control_aura() : SpellScriptLoader("spell_dreadflame_spread_control_aura") { }

        class spell_dreadflame_spread_control_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dreadflame_spread_control_aura_AuraScript);

            void HandlePeriodic(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                DreadflameAI* ai = CAST_AI(DreadflameAI, GetCaster()->GetAI());
                if (!ai)
                    return;

                std::list<Position> dreadflames = ai->GetDreadflameSpreadPositions();
                for (auto dreadFlame : dreadflames)
                    GetCaster()->CastSpell(dreadFlame.GetPositionX(), dreadFlame.GetPositionY(), dreadFlame.GetPositionZ(), SPELL_DREADFLAME_SPAWN, true);
            }


            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dreadflame_spread_control_aura_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dreadflame_spread_control_aura_AuraScript();
        }
};

// http://www.wowhead.com/spell=100342/draw-out-firelord
// http://www.wowhead.com/spell=100344/draw-out-firelord
// http://www.wowhead.com/spell=100345/draw-out-firelord
class spell_draw_out_firelord : public SpellScriptLoader
{
    public:
        spell_draw_out_firelord() : SpellScriptLoader("spell_draw_out_firelord") {}

    class spell_draw_out_firelord_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_draw_out_firelord_SpellScript);

        void TargetFirelord(WorldObject*& target)
        {
            target = nullptr;
            if (InstanceScript* instance = GetCaster()->GetInstanceScript())
                if (Creature* ragnaros = ObjectAccessor::GetCreature(*GetCaster(), instance->GetGuidData(NPC_RAGNAROS)))
                    target = ragnaros;
        }

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_draw_out_firelord_SpellScript::TargetFirelord, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_draw_out_firelord_SpellScript();
    }
};

// http://www.wowhead.com/spell=100907/freeze
class spell_cenarius_meteor_freeze : public SpellScriptLoader
{
    public:
        spell_cenarius_meteor_freeze() : SpellScriptLoader("spell_cenarius_meteor_freeze") {}

    class spell_cenarius_meteor_freeze_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cenarius_meteor_freeze_SpellScript);

        void TargetFirelord(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* target)
            {
                return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR;
            });
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_cenarius_meteor_freeze_SpellScript::TargetFirelord, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_cenarius_meteor_freeze_SpellScript();
    }
};

// http://www.wowhead.com/spell=100472/breadth-of-frost-trigger
class spell_ragnaros_breadth_of_frost_trigger : public SpellScriptLoader
{
    public:
    spell_ragnaros_breadth_of_frost_trigger() : SpellScriptLoader("spell_ragnaros_breadth_of_frost_trigger") {}

    class spell_ragnaros_breadth_of_frost_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_breadth_of_frost_trigger_SpellScript);

        void OnSpellHit(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
        }

        void TargetStalker(WorldObject*& target)
        {
            target = nullptr;
            std::list<Creature*> triggers;
            GetCaster()->GetCreatureListWithEntryInGrid(triggers, NPC_PLATFORM_STALKER, SIZE_OF_GRIDS);
            if (triggers.empty())
                return;

            Trinity::Containers::RandomResizeList(triggers, 1);
            target = triggers.front();
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ragnaros_breadth_of_frost_trigger_SpellScript::OnSpellHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_ragnaros_breadth_of_frost_trigger_SpellScript::TargetStalker, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_breadth_of_frost_trigger_SpellScript();
    }
};

// http://www.wowhead.com/spell=100476/breadth-of-frost-summon
// http://www.wowhead.com/spell=100644/entrapping-roots-summon
// http://www.wowhead.com/spell=100756/cloudburst
class spell_fl_ragnaros_npc_helper_summon : public SpellScriptLoader
{
public:
    spell_fl_ragnaros_npc_helper_summon() : SpellScriptLoader("spell_fl_ragnaros_npc_helper_summon") { }

    class spell_fl_ragnaros_npc_helper_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fl_ragnaros_npc_helper_summon_SpellScript);

        void RelocateHeight(SpellEffIndex /*effIndex*/)
        {
            float height = GetCaster()->GetMap()->GetHeight(GetCaster()->GetPhaseMask(), GetHitDest()->GetPositionX(), GetHitDest()->GetPositionY(), GetHitDest()->GetPositionZ());
            GetCaster()->Yell("Relocate Z to: " + std::to_string(height), LANG_UNIVERSAL);
            GetHitDest()->Relocate(GetHitDest()->GetPositionX(), GetHitDest()->GetPositionY(), height);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_fl_ragnaros_npc_helper_summon_SpellScript::RelocateHeight, EFFECT_0, SPELL_EFFECT_SUMMON);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_fl_ragnaros_npc_helper_summon_SpellScript();
    }
};

// http://www.wowhead.com/spell=100645/enrapping-roots
class spell_ragnaros_entrapping_roots_trigger : public SpellScriptLoader
{
    public:
    spell_ragnaros_entrapping_roots_trigger() : SpellScriptLoader("spell_ragnaros_entrapping_roots_trigger") {}

    class spell_ragnaros_entrapping_roots_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_entrapping_roots_trigger_SpellScript);

        void OnSpellHit(SpellEffIndex /*effIndex*/)
        {
            GetHitUnit()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
        }

        void TargetStalker(WorldObject*& target)
        {
            std::list<Creature*> triggers;
            GetCaster()->GetCreatureListWithEntryInGrid(triggers, NPC_PLATFORM_STALKER, SIZE_OF_GRIDS);
            if (triggers.empty())
                return;

            Trinity::Containers::RandomResizeList(triggers, 1);
            target = triggers.front();
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ragnaros_entrapping_roots_trigger_SpellScript::OnSpellHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_ragnaros_entrapping_roots_trigger_SpellScript::TargetStalker, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_entrapping_roots_trigger_SpellScript();
    }
};

// http://www.wowhead.com/spell=100653/entrapping-roots
// http://www.wowhead.com/spell=101237/entrapping-roots
class spell_ragnaros_entrapping_roots : public SpellScriptLoader
{
    public:
    spell_ragnaros_entrapping_roots() : SpellScriptLoader("spell_ragnaros_entrapping_roots") {}

    class spell_ragnaros_entrapping_roots_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_entrapping_roots_SpellScript);

        void TargetRagnaros(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* target)
            {
                return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_RAGNAROS;
            });

            if (targets.empty())
                FinishCast(SPELL_FAILED_DONT_REPORT);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_entrapping_roots_SpellScript::TargetRagnaros, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_entrapping_roots_SpellScript::TargetRagnaros, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_entrapping_roots_SpellScript();
    }
};

// http://www.wowhead.com/spell=100503/breadth-of-frost
class spell_breadth_of_frost_player_aura : public SpellScriptLoader
{
    public:
    spell_breadth_of_frost_player_aura() : SpellScriptLoader("spell_breadth_of_frost_player_aura") {}

    class spell_breadth_of_frost_player_aura_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_breadth_of_frost_player_aura_SpellScript);

        void OnSpellHit(SpellEffIndex effIndex)
        {
            GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->GetEffect(effIndex)->BasePoints);
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(PlayerCheck());
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_breadth_of_frost_player_aura_SpellScript::OnSpellHit, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breadth_of_frost_player_aura_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breadth_of_frost_player_aura_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_breadth_of_frost_player_aura_SpellScript();
    }
};

// http://www.wowhead.com/spell=100567/breadth-of-frost
class spell_breadth_of_frost_meteor_aura : public SpellScriptLoader
{
    public:
    spell_breadth_of_frost_meteor_aura() : SpellScriptLoader("spell_breadth_of_frost_meteor_aura") {}

    class spell_breadth_of_frost_meteor_aura_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_breadth_of_frost_meteor_aura_SpellScript);

        void FilterMeteors(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* target)
            {
                return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_RAGNAROS_LIVING_METEOR;
            });

            if (targets.empty())
                return;

            targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));
            
            WorldObject* target = targets.front();
            targets.clear();
            targets.push_back(target);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breadth_of_frost_meteor_aura_SpellScript::FilterMeteors, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breadth_of_frost_meteor_aura_SpellScript::FilterMeteors, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_breadth_of_frost_meteor_aura_SpellScript::FilterMeteors, EFFECT_2, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_breadth_of_frost_meteor_aura_SpellScript();
    }
};

// http://www.wowhead.com/spell=100751/cloudburst
class spell_ragnaros_cloudburst : public SpellScriptLoader
{
    public:
    spell_ragnaros_cloudburst() : SpellScriptLoader("spell_ragnaros_cloudburst") {}

    class spell_ragnaros_cloudburst_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_cloudburst_SpellScript);

        void OnSpellHit(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()));
        }

        void TargetStalker(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* target)
            {
                return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_PLATFORM_STALKER;
            });
            
            if (targets.empty())
                return;

            Trinity::Containers::RandomResizeList(targets, 1);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ragnaros_cloudburst_SpellScript::OnSpellHit, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_cloudburst_SpellScript::TargetStalker, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_cloudburst_SpellScript();
    }
};

// http://www.wowhead.com/spell=108773/magma
class spell_ragnaros_magma_knockup : public SpellScriptLoader
{
    public:
    spell_ragnaros_magma_knockup() : SpellScriptLoader("spell_ragnaros_magma_knockup") {}

    class spell_ragnaros_magma_knockup_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_magma_knockup_SpellScript);

        void FilterShortKnockup(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            targets.remove_if([caster](WorldObject* target)
            {
                return caster->IsWithinLOSInMap(target);
            });
        }

        void FilterHighKnockup(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            targets.remove_if([caster](WorldObject* target)
            {
                return !caster->IsWithinLOSInMap(target);
            });
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_magma_knockup_SpellScript::FilterShortKnockup, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_magma_knockup_SpellScript::FilterHighKnockup, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_magma_knockup_SpellScript();
    }
};

// http://www.wowhead.com/spell=100691/dreadflame
// http://www.wowhead.com/spell=101016/dreadflame
class spell_ragnaros_dreadflame_dummy : public SpellScriptLoader
{
    public:
    spell_ragnaros_dreadflame_dummy() : SpellScriptLoader("spell_ragnaros_dreadflame_dummy") {}

    class spell_ragnaros_dreadflame_dummy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ragnaros_dreadflame_dummy_AuraScript);

        void HandleDummyTick(AuraEffect const* aurEff)
        {
            Creature* ragnaros = GetCaster()->ToCreature();
            if (!ragnaros || !ragnaros->IsAIEnabled)
                return;

            ragnaros->AI()->DoAction(ACTION_RAGNAROS_DREADFLAME);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ragnaros_dreadflame_dummy_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_ragnaros_dreadflame_dummy_AuraScript();
    }
};

// http://www.wowhead.com/spell=100606/empower-sulfuras-visual-missile
class spell_empower_sulfuras_visual_missile : public SpellScriptLoader
{
    public:
    spell_empower_sulfuras_visual_missile() : SpellScriptLoader("spell_empower_sulfuras_visual_missile") {}

    class spell_empower_sulfuras_visual_missile_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_empower_sulfuras_visual_missile_SpellScript);

        void TargetFirelord(WorldObject*& target)
        {
            if (InstanceScript* instance = GetCaster()->GetInstanceScript())
                if (Creature* ragnaros = ObjectAccessor::GetCreature(*GetCaster(), instance->GetGuidData(NPC_RAGNAROS)))
                    target = ragnaros;
        }

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_empower_sulfuras_visual_missile_SpellScript::TargetFirelord, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_empower_sulfuras_visual_missile_SpellScript();
    }
};

// http://www.wowhead.com/spell=100604/empower-sulfuras
// http://www.wowhead.com/spell=100997/empower-sulfuras
class spell_ragnaros_empower_sulfuras : public SpellScriptLoader
{
    public:
    spell_ragnaros_empower_sulfuras() : SpellScriptLoader("spell_ragnaros_empower_sulfuras") {}

    class spell_ragnaros_empower_sulfuras_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ragnaros_empower_sulfuras_SpellScript);

        void OnSpellHit(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->AddAura((uint32)GetEffectValue(), GetHitUnit());
        }

        void FilterSeedCasters(std::list<WorldObject*>& targets)
        {
            targets.remove_if([](WorldObject* target)
            {
                return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_MOLTEN_SEED_CASTER;
            });
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ragnaros_empower_sulfuras_SpellScript::OnSpellHit, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ragnaros_empower_sulfuras_SpellScript::FilterSeedCasters, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ragnaros_empower_sulfuras_SpellScript();
    }
};

// http://www.wowhead.com/spell=100605/empower-sulfuras
class spell_ragnaros_empower_sulfuras_aura_dummy : public SpellScriptLoader
{
    public:
    spell_ragnaros_empower_sulfuras_aura_dummy() : SpellScriptLoader("spell_ragnaros_empower_sulfuras_aura_dummy") {}

    class spell_ragnaros_empower_sulfuras_aura_dummy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ragnaros_empower_sulfuras_aura_dummy_AuraScript);

        void HandleDummyTick(AuraEffect const* aurEff)
        {
            if (urand(0, 2) == 0)
                GetTarget()->CastSpell((Unit*)NULL, SPELL_EMPOWER_SULFURAS_VISUAL_MISSILE, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ragnaros_empower_sulfuras_aura_dummy_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_ragnaros_empower_sulfuras_aura_dummy_AuraScript();
    }
};

// http://www.wowhead.com/spell=100628/empowered-sulfuras
class spell_ragnaros_empower_sulfuras_aura : public SpellScriptLoader
{
    public:
    spell_ragnaros_empower_sulfuras_aura() : SpellScriptLoader("spell_ragnaros_empower_sulfuras_aura") {}

    class spell_ragnaros_empower_sulfuras_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ragnaros_empower_sulfuras_aura_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Creature* ragnaros = GetCaster()->ToCreature();
            if (!ragnaros || !ragnaros->IsAIEnabled)
                return;

            ragnaros->AI()->DoAction(ACTION_EMPOWER_SULFURAS);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Creature* ragnaros = GetCaster()->ToCreature();
            if (!ragnaros || !ragnaros->IsAIEnabled)
                return;

            ragnaros->AI()->DoAction(ACTION_EMPOWER_SULFURAS_END);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_ragnaros_empower_sulfuras_aura_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_ragnaros_empower_sulfuras_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_ragnaros_empower_sulfuras_aura_AuraScript();
    }
};

// http://www.wowhead.com/spell=100594/superheated
class spell_fl_ragnaros_superheated : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_superheated() : SpellScriptLoader("spell_fl_ragnaros_superheated") { }

        class spell_fl_ragnaros_superheated_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_superheated_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
                targets.remove_if([](WorldObject* target)
                {
                    return target->ToUnit()->HasAura(SPELL_DELUGE_AURA) || target->ToUnit()->HasAura(SPELL_BREADTH_OF_FROST_PLAYER_AURA);
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_superheated_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_superheated_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }

            std::list<ObjectGuid> dreadflamesRemoveList;
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_superheated_SpellScript();
        }
};

// http://www.wowhead.com/spell=100459/blazing-heat
class spell_fl_ragnaros_blazing_heat_target_search : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_blazing_heat_target_search() : SpellScriptLoader("spell_fl_ragnaros_blazing_heat_target_search") { }

        class spell_fl_ragnaros_blazing_heat_target_search_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_blazing_heat_target_search_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_fl_ragnaros_blazing_heat_target_search_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_blazing_heat_target_search_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_blazing_heat_target_search_SpellScript();
        }
};

// http://www.wowhead.com/spell=99125/blazing-heat
class spell_fl_ragnaros_blazing_heat_spawn : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_blazing_heat_spawn() : SpellScriptLoader("spell_fl_ragnaros_blazing_heat_spawn") { }

        class spell_fl_ragnaros_blazing_heat_spawn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_blazing_heat_spawn_SpellScript);

            void OnCastSpell()
            {
                GetCaster()->CastSpell(static_cast<Unit*>(nullptr), SPELL_BLAZING_HEAT_SUMMON, true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_BLAZING_HEAT;
                });

                if (!targets.empty())
                    FinishCast(SPELL_FAILED_DONT_REPORT);
            }

            void Register() override
            {
                OnCast += SpellCastFn(spell_fl_ragnaros_blazing_heat_spawn_SpellScript::OnCastSpell);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_blazing_heat_spawn_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_blazing_heat_spawn_SpellScript();
        }
};

// http://www.wowhead.com/spell=100771/deluge-aura-cancel
class spell_fl_ragnaros_deluge_aura_cancel : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_deluge_aura_cancel() : SpellScriptLoader("spell_fl_ragnaros_deluge_aura_cancel") { }

        class spell_fl_ragnaros_deluge_aura_cancel_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_deluge_aura_cancel_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DELUGE_AURA_CANCEL))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                GetHitUnit()->RemoveAurasDueToSpell((uint32)GetEffectValue());
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(PlayerCheck());
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_fl_ragnaros_deluge_aura_cancel_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_deluge_aura_cancel_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_deluge_aura_cancel_SpellScript();
        }
};

// http://www.wowhead.com/spell=99907/magma
class spell_fl_ragnaros_magma : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_magma() : SpellScriptLoader("spell_fl_ragnaros_magma") {}

        class spell_fl_ragnaros_magma_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_magma_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([this](WorldObject* target)
                {
                    return target->GetPositionZ() > 54.0f;
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_magma_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_magma_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_magma_SpellScript();
        }
};

// http://www.wowhead.com/spell=98497/molten-seed
class spell_fl_ragnaros_molten_seed_missile_target_search : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_molten_seed_missile_target_search() : SpellScriptLoader("spell_fl_ragnaros_molten_seed_missile_target_search") { }

        class spell_fl_ragnaros_molten_seed_missile_target_search_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_molten_seed_missile_target_search_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MOLTEN_SEED_MISSILE_TARGET_SEARCH))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                GetHitUnit()->CastSpell(GetCaster(), uint32(GetEffectValue()), true);
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, [](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_MOLTEN_SEED_CASTER;
                }, 1);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_fl_ragnaros_molten_seed_missile_target_search_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_molten_seed_missile_target_search_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_molten_seed_missile_target_search_SpellScript();
        }
};

// http://www.wowhead.com/spell=98520/molten-seed
class spell_fl_ragnaros_molten_seed_grow : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_molten_seed_grow() : SpellScriptLoader("spell_fl_ragnaros_molten_seed_grow") { }

        class spell_fl_ragnaros_molten_seed_grow_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_fl_ragnaros_molten_seed_grow_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* owner = GetUnitOwner())
                    if (Creature* creature = owner->ToCreature())
                        if (creature->IsAIEnabled)
                            creature->AI()->DoAction(ACTION_MOLTEN_ELEMENTAL_ACTIVATE);
            }

            void Register() override
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_fl_ragnaros_molten_seed_grow_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_fl_ragnaros_molten_seed_grow_AuraScript();
        }
};

// http://www.wowhead.com/spell=100158/molten-power
class spell_fl_ragnaros_molten_power : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_molten_power() : SpellScriptLoader("spell_fl_ragnaros_molten_power") { }

        class spell_fl_ragnaros_molten_power_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_molten_power_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if([](WorldObject* target) -> bool
                {
                    return target->GetTypeId() != TYPEID_UNIT || target->GetEntry() != NPC_MOLTEN_ELEMENTAL;
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_molten_power_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_molten_power_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_molten_power_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_molten_power_SpellScript();
        }
};

// http://www.wowhead.com/spell=98333/molten-seed
class spell_fl_ragnaros_molten_seed_target_search : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_molten_seed_target_search() : SpellScriptLoader("spell_fl_ragnaros_molten_seed_target_search") { }

        class spell_fl_ragnaros_molten_seed_target_search_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_molten_seed_target_search_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 20 : 10);
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_molten_seed_target_search_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_molten_seed_target_search_SpellScript();
        }
};

// http://www.wowhead.com/spell=98518/molten-inferno
class spell_fl_ragnaros_molten_inferno : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_molten_inferno() : SpellScriptLoader("spell_fl_ragnaros_molten_inferno") { }

        class spell_fl_ragnaros_molten_inferno_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_molten_inferno_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MOLTEN_ELEMENTAL_INFERNO))
                    return false;
                return true;
            }

            void ChangeDamage()
            {
                float maxRange = GetSpellInfo()->GetEffect(EFFECT_0)->CalcRadius();
                float actualRange = GetCaster()->GetDistance2d(GetHitUnit());
                SetHitDamage(GetHitDamage()*pow(0.8, uint32((actualRange / maxRange) * 100)));
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_fl_ragnaros_molten_inferno_SpellScript::ChangeDamage);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_molten_inferno_SpellScript();
        }
};

// http://www.wowhead.com/spell=101252/heart-of-ragnaros
class spell_fl_ragnaros_heart_of_ragnaros : public SpellScriptLoader
{
    public:
        spell_fl_ragnaros_heart_of_ragnaros() : SpellScriptLoader("spell_fl_ragnaros_heart_of_ragnaros") { }

        class spell_fl_ragnaros_heart_of_ragnaros_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fl_ragnaros_heart_of_ragnaros_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(HeartOfFlameCheck(m_scriptSpellId == SPELL_HEART_OF_RAGNAROS_A ? QUEST_HEART_OF_FLAME_A : m_scriptSpellId == SPELL_HEART_OF_RAGNAROS_H ? QUEST_HEART_OF_FLAME_H : 0));
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fl_ragnaros_heart_of_ragnaros_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fl_ragnaros_heart_of_ragnaros_SpellScript();
        }
};

class at_sulfuron_keep : public AreaTriggerScript
{
    public:
        at_sulfuron_keep() : AreaTriggerScript("at_sulfuron_keep") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/, bool /*entered*/) override
    {
        if (InstanceScript* instance = player->GetInstanceScript())
            if (instance->GetData(DATA_RAGNAROS_EMERGED) == 0)
                instance->SetData(DATA_RAGNAROS_EMERGED, 1);

        return true;
    }
};

class achievement_ragnar_os : public AchievementCriteriaScript
{
    public:
        achievement_ragnar_os() : AchievementCriteriaScript("achievement_ragnar_os") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            if (!target)
                return false;

            return target->GetAI()->GetData(DATA_IGNITED_METEORS) >= 3;
        }
};

void AddSC_boss_ragnaros_firelands_WiP()
{
    new boss_ragnaros_firelands();
    new npc_ragnaros_son_of_flame();
    new npc_ragnaros_sulfuras();
    new npc_ragnaros_engulfing_flames();
    new npc_sulfuras_smash_trigger();
    new npc_fl_ragnaros_platform_stalker();
    new npc_ragnaros_sulfuras_smash();
    new npc_ragnaros_lava_wave();
    new npc_ragnaros_magma_trap();
    new npc_ragnaros_lava_scion();
    new npc_ragnaros_cenarius();
    new npc_ragnaros_malfurion_stormrage();
    new npc_ragnaros_hamuul_runetotem();
    new npc_ragnaros_dreadflame();
    new npc_ragnaros_dreadflame_spawn();
    new npc_ragnaros_breadth_of_frost();
    new npc_ragnaros_entrapping_roots();
    new npc_ragnaros_cloudburst();
    new npc_fl_ragnaros_molten_elemental();

    new spell_ragnaros_splitting_blow();
    new spell_ragnaros_splitting_blow_dummy();
    new spell_ragnaros_invoke_sons();
    new spell_rage_of_ragnaros_dummy();
    new spell_rage_of_ragnaros();
    new spell_engulfing_flames();
    new spell_world_in_flames();
    new spell_ragnaros_submerge();
    new spell_sulfuras_smash_player_trigger();
    new spell_ragnaros_sulfuras_smash();
    new spell_ragnaros_sulfuras_smash_damage();
    new spell_ragnaros_lavalogged();
    new spell_ragnaros_lava_wave();
    new spell_ragnaros_burning_speed();
    new spell_ragnaros_magma_trap();
    new spell_ragnaros_magma_trap_dummy();
    new spell_ragnaros_magma_trap_eruption();
    new spell_ragnaros_wrath_of_ragnaros();
    new spell_dreadflame_deluge_control_aura();
    new spell_dreadflame_damage_control_aura();
    new spell_dreadflame_spawn_control_aura();
    new spell_dreadflame_spread_control_aura();
    new spell_draw_out_firelord();
    new spell_cenarius_meteor_freeze();
    new spell_ragnaros_breadth_of_frost_trigger();
    new spell_ragnaros_entrapping_roots_trigger();
    new spell_fl_ragnaros_npc_helper_summon();
    new spell_ragnaros_entrapping_roots();
    new spell_breadth_of_frost_player_aura();
    new spell_breadth_of_frost_meteor_aura();
    new spell_ragnaros_cloudburst();
    new spell_ragnaros_magma_knockup();
    new spell_ragnaros_dreadflame_dummy();
    new spell_empower_sulfuras_visual_missile();
    new spell_ragnaros_empower_sulfuras();
    new spell_ragnaros_empower_sulfuras_aura_dummy();
    new spell_ragnaros_empower_sulfuras_aura();
    new spell_fl_ragnaros_superheated();
    new spell_fl_ragnaros_blazing_heat_target_search();
    new spell_fl_ragnaros_blazing_heat_spawn();
    new spell_fl_ragnaros_deluge_aura_cancel();
    new spell_fl_ragnaros_magma();
    new spell_fl_ragnaros_molten_seed_missile_target_search();
    new spell_fl_ragnaros_molten_seed_grow();
    new spell_fl_ragnaros_molten_power();
    new spell_fl_ragnaros_molten_seed_target_search();
    new spell_fl_ragnaros_molten_inferno();

    new at_sulfuron_keep();

    new achievement_ragnar_os();
};
