#ifndef BATTLE_PET_H
#define BATTLE_PET_H

#include "BattlePetMgr.h"
#include "Common.h"
#include "Object.h"
#include "Player.h"
#include <ace/Singleton.h>

// -------------------------------------------------------------------------------
// Battle Pet
// -------------------------------------------------------------------------------

#define BATTLE_PET_MAX_LEVEL       25
#define BATTLE_PET_MAX_NAME_LENGTH 16
#define BATTLE_PET_MAX_ABILITIES   3

// 3-12:  Male
// 13-22: Female
#define BATTLE_PET_MAX_BREED       22

#define BATTLE_PET_MAX_STATES      163
#define BATTLE_PET_MAX_MAIN_STATES 3

// names from 'BattlePetState.db2'
enum BattlePetStates
{
    BATTLE_PET_STATE_IS_DEAD                            = 1,
    BATTLE_PET_STATE_STAT_POWER                         = 18,
    BATTLE_PET_STATE_STAT_STAMINA                       = 19,
    BATTLE_PET_STATE_STAT_SPEED                         = 20,
    BATTLE_PET_STATE_MECHANIC_POISONED                  = 21,
    BATTLE_PET_STATE_MECHANIC_STUNNED                   = 22,
    BATTLE_PET_STATE_MOD_DAMAGE_DEALT_PCT               = 23,
    BATTLE_PET_STATE_MOD_DAMAGE_TAKEN_PCT               = 24,
    BATTLE_PET_STATE_MOD_SPEED_PERCENT                  = 25,
    BATTLE_PET_STATE_RAMPING_DAMAGE_ID                  = 26,
    BATTLE_PET_STATE_RAMPING_DAMAGE_USES                = 27,
    BATTLE_PET_STATE_CONDITION_WAS_DAMAGED_THIS_ROUND   = 28,
    BATTLE_PET_STATE_UNTARGETABLE                       = 29,
    BATTLE_PET_STATE_UNDERGROUND                        = 30,
    BATTLE_PET_STATE_LAST_HIT_TAKEN                     = 31,
    BATTLE_PET_STATE_LAST_HIT_DEALT                     = 32,
    BATTLE_PET_STATE_MECHANIC_FLYING                    = 33,
    BATTLE_PET_STATE_MECHANIC_BURNING                   = 34,
    BATTLE_PET_STATE_TURN_LOCK                          = 35,
    BATTLE_PET_STATE_SWAP_OUT_LOCK                      = 36,
    BATTLE_PET_STATE_STAT_CRITICAL_CHANCE               = 40,
    BATTLE_PET_STATE_STAT_ACCURACY                      = 41,
    BATTLE_PET_STATE_PASSIVE_CRITTER                    = 42,
    BATTLE_PET_STATE_PASSIVE_BEAST                      = 43,
    BATTLE_PET_STATE_PASSIVE_HUMANOID                   = 44,
    BATTLE_PET_STATE_PASSIVE_FLYING                     = 45,
    BATTLE_PET_STATE_PASSIVE_DRAGON                     = 46,
    BATTLE_PET_STATE_PASSIVE_ELEMENTAL                  = 47,
    BATTLE_PET_STATE_PASSIVE_MECHANICAL                 = 48,
    BATTLE_PET_STATE_PASSIVE_MAGIC                      = 49,
    BATTLE_PET_STATE_PASSIVE_UNDEAD                     = 50,
    BATTLE_PET_STATE_PASSIVE_AQUATIC                    = 51,
    BATTLE_PET_STATE_MECHANIC_CHILLED                   = 52,
    BATTLE_PET_STATE_MECHANIC_WEBBED                    = 64,
    BATTLE_PET_STATE_MOD_HEALING_DEALT_PCT              = 65,
    BATTLE_PET_STATE_MOD_HEALING_TAKEN_PCT              = 66,
    BATTLE_PET_STATE_MECHANIC_INVISIBLE                 = 67,
    BATTLE_PET_STATE_UNKILLABLE                         = 68,
    BATTLE_PET_STATE_STAT_DODGE                         = 73,
    BATTLE_PET_STATE_MECHANIC_BLEEDING                  = 77,
    BATTLE_PET_STATE_MECHANIC_BLIND                     = 82,
    BATTLE_PET_STATE_MOD_PET_TYPE_ID                    = 89,
    BATTLE_PET_STATE_INTERNAL_CAPTURE_BOOST             = 90,
    BATTLE_PET_STATE_SWAP_IN_LOCK                       = 98,
    BATTLE_PET_STATE_CONDITION_DID_DAMAGE_THIS_ROUND    = 127,
    BATTLE_PET_STATE_MECHANIC_BOMB                      = 136,
    BATTLE_PET_STATE_RESILITANT                         = 149
};

enum BattlePetStateModifyTypes
{
    BATTLE_PET_STATE_MODIFY_TYPE_NONE   = 0,
    BATTLE_PET_STATE_MODIFY_TYPE_BOOL   = 1, // state value can only be 0 or 1
    BATTLE_PET_STATE_MODIFY_TYPE_INT    = 2, // state value can be any int value
};

static uint8 BattlePetStateModifyType[BATTLE_PET_MAX_STATES] =
{
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State001  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State002  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State003  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State004  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State017  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State018  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State019  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State020  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State021  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State022  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State023  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State024  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State025  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State026  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State027  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State028  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State029  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State030  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State031  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State032  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State033  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State034  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State035  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State036  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State040  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State041  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State042  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State043  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State044  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State045  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State046  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State047  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State048  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State049  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State050  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State051  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State052  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State053  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State054  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State055  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State056  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State057  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State058  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State059  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State060  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State061  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State062  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State063  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State064  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State065  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State066  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State067  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State068  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State069  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State070  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State071  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State072  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State073  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State074  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State075  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State077  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State078  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State082  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State084  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State085  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State087  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State088  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State089  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State090  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State091  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State093  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State098  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State099  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State100  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State101  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State102  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State103  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State104  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State105  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State106  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State107  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State108  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State113  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State114  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State117  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State118  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State119  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State120  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State121  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*  State122  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State123  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State124  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State126  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State127  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State128  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State129  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State136  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State141  */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State144  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*  State145  */ BATTLE_PET_STATE_MODIFY_TYPE_INT,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State149  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State153  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State158  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*   UNUSED   */ BATTLE_PET_STATE_MODIFY_TYPE_NONE,
    /*  State162  */ BATTLE_PET_STATE_MODIFY_TYPE_BOOL,
};

enum BattlePetFamily
{
    BATTLE_PET_FAMILY_HUMANOID         = 0,
    BATTLE_PET_FAMILY_DRAGONKIN        = 1,
    BATTLE_PET_FAMILY_FLYING           = 2,
    BATTLE_PET_FAMILY_UNDEAD           = 3,
    BATTLE_PET_FAMILY_CRITTER          = 4,
    BATTLE_PET_FAMILY_MAGIC            = 5,
    BATTLE_PET_FAMILY_ELEMENTAL        = 6,
    BATTLE_PET_FAMILY_BEAST            = 7,
    BATTLE_PET_FAMILY_AQUATIC          = 8,
    BATTLE_PET_FAMILY_MECHANICAL       = 9,
    BATTLE_PET_FAMILY_COUNT
};

enum BattlePetDbState
{
    BATTLE_PET_DB_STATE_NONE            = 0,
    BATTLE_PET_DB_STATE_DELETE          = 1,
    BATTLE_PET_DB_STATE_SAVE            = 2
};

enum BattlePetAchievements
{
    BATTLE_PET_ACHIEVEMENT_NEWBIE       = 7433,
    BATTLE_PET_ACHIEVEMENT_JUST_A_PUP   = 6566
};

struct BattlePetAbility
{
    uint32 AbilityId;
    bool OnCooldown;
    uint16 Cooldown;
    uint16 Lockdown;                                    // NYI
};

class PetBattleAura;

typedef std::list<PetBattleAura*> BattlePetAuraStore;
typedef std::vector<uint32> BattlePetStateStore;

class BattlePet
{
public:
    // new battle pet
    BattlePet(uint64 id, uint16 speciesId, uint8 family, uint8 level, uint8 quality, uint8 breedId, Player* owner = nullptr)
        : m_id(id), m_species(speciesId), m_family(family), m_breed(breedId), m_nickname(""), m_timestamp(0), m_level(level), m_xp(0), m_curHealth(0),
        m_maxHealth(0), m_quality(quality), m_flags(0), m_dbState(BATTLE_PET_DB_STATE_SAVE), m_globalIndex(0), m_teamIndex(0),
        m_owner(owner) { Initialise(true); }

    // load from database
    BattlePet(uint64 id, uint16 speciesId, uint8 family, std::string nickname, uint32 timestamp,
        uint8 level, uint16 xp, uint16 curHealth, uint8 quality, uint8 breedId, uint16 flags, Player* owner)
        : m_id(id), m_species(speciesId), m_family(family), m_nickname(nickname), m_timestamp(timestamp), m_level(level), m_xp(xp), m_curHealth(curHealth),
        m_maxHealth(0), m_quality(quality), m_breed(breedId), m_flags(flags), m_dbState(BATTLE_PET_DB_STATE_NONE), m_globalIndex(0),
        m_teamIndex(0), m_owner(owner) { Initialise(false); }

    void Initialise(bool newBattlePet);
    void InitialiseStates(bool newBattlePet);

    Player* GetOwner() const { return m_owner; }
    uint64 GetId() const { return m_id; }
    uint16 GetSpecies() const { return m_species; }
    uint8 GetFamilty() const { return m_family; }
    std::string GetNickname() const { return m_nickname; }
    uint32 GetTimestamp() const { return m_timestamp; }
    uint8 GetLevel() const { return m_level; }
    uint16 GetXp() const { return m_xp; }
    uint16 GetCurrentHealth() const { return m_curHealth; }
    uint16 GetMaxHealth() const { return m_maxHealth; }
    uint16 GetPower() const;
    uint16 GetSpeed() const;
    uint8 GetQuality() const { return m_quality; }
    uint8 GetBreed() const { return m_breed; }

    uint32 GetNpc() const { return m_npc; }
    uint32 GetDisplayId() const { return m_displayId; }

    void SetCurrentHealth(uint32 health);
    void SetNickname(std::string nickname);
    void SetTimestamp(uint32 timestamp) { m_timestamp = timestamp; }
    void SetXP(uint16 xpGain);
    void SetLevel(uint8 level);

    uint8 GetDbState() const { return m_dbState; }
    void SetDbState(uint8 state) { m_dbState = state; }

    uint8 GetFlags() const { return m_flags; }
    bool HasFlag(uint16 flag) const { return (m_flags & flag) != 0; }
    void SetFlag(uint16 flag);
    void UnSetFlag(uint16 flag);

// -------------------------------------------------------------------------------

    void InitialiseAbilities(bool wild);

    void SetBattleAbilities();
    void SetBattleInfo(uint8 teamIndex, uint8 globalPetId)
        { m_teamIndex = teamIndex; m_globalIndex = globalPetId; m_oldLevel = m_level; }

    uint8 GetGlobalIndex() { return m_globalIndex; }
    uint8 GetTeamIndex() { return m_teamIndex; }
    uint16 GetOldLevel() { return m_oldLevel; }
    PetBattleAura* GetAura(uint32 abilityId);

    void CalculateStats(bool currentHealth = false);
    bool IsMainStatState(uint32 state) { return state == BATTLE_PET_STATE_STAT_POWER || state == BATTLE_PET_STATE_STAT_STAMINA || state == BATTLE_PET_STATE_STAT_SPEED; }

    bool IsAlive() { return States[BATTLE_PET_STATE_IS_DEAD] == 0; }
    bool CanAttack() { return !States[BATTLE_PET_STATE_TURN_LOCK] && !States[BATTLE_PET_STATE_MECHANIC_STUNNED] && !States[BATTLE_PET_STATE_MECHANIC_WEBBED]; }
    bool IsTargetable() { return States[BATTLE_PET_STATE_UNTARGETABLE] == 0; }

    void ResetMechanicStates();

    uint32 AbilitiyIds[BATTLE_PET_MAX_ABILITIES];
    BattlePetAbility* Abilities[BATTLE_PET_MAX_ABILITIES];

    BattlePetAuraStore Auras;

    uint16 m_oldLevel;

    int32 States[BATTLE_PET_MAX_STATES];

// -------------------------------------------------------------------------------

private:
    Player* m_owner;
    uint64 m_id;
    uint16 m_species;
    uint8 m_family;
    std::string m_nickname;
    uint32 m_timestamp;
    uint8 m_level;
    uint16 m_xp;
    uint16 m_curHealth;
    uint16 m_maxHealth;
    uint16 m_power;
    uint16 m_speed;
    uint8 m_quality;
    uint8 m_breed;
    uint16 m_flags;
    uint8 m_dbState;

    uint8 m_teamIndex;
    uint8 m_globalIndex;

    uint32 m_npc;
    uint32 m_displayId;

    int32 m_mainStates[BATTLE_PET_MAX_MAIN_STATES];     // used to calculate stats on levelup
};

// -------------------------------------------------------------------------------
// Pet Battle
// -------------------------------------------------------------------------------

class PetBattle;

#define PET_BATTLE_MAX_TEAMS        2
#define PET_BATTLE_MAX_TEAM_PETS    3

#define PET_BATTLE_CHALLANGER_TEAM  0
#define PET_BATTLE_OPPONENT_TEAM    1

#define PET_BATTLE_NULL_PET_INDEX  -1

// sent in SMSG_PET_BATTLE_REQUEST_FAILED
enum PetBattleRequestReason
{
    PET_BATTLE_REQUEST_FAILED                           = 0,
    PET_BATTLE_REQUEST_NOT_HERE                         = 1,
    PET_BATTLE_REQUEST_NOT_DURING_FLYING                = 2,
    PET_BATTLE_REQUEST_GROUND_NOT_ENOUGHT_SMOOTH        = 3,
    PET_BATTLE_REQUEST_AREA_NOT_CLEAR                   = 4,
    PET_BATTLE_REQUEST_ALREADY_IN_COMBAT                = 5,
    PET_BATTLE_REQUEST_DEAD                             = 6,
    PET_BATTLE_REQUEST_SEATED                           = 7,
    PET_BATTLE_REQUEST_NOT_VALID_TARGET                 = 8,
    PET_BATTLE_REQUEST_TOO_FAR                          = 9,
    PET_BATTLE_REQUEST_INVALID_TARGET                   = 10,
    PET_BATTLE_REQUEST_NEED_TO_BE_TRAINER               = 11,
    PET_BATTLE_REQUEST_DECLINED                         = 12,
    PET_BATTLE_REQUEST_ALREADY_IN_PETBATTLE             = 13,
    PET_BATTLE_REQUEST_NEED_PET_IN_SLOTS                = 14,
    PET_BATTLE_REQUEST_PET_ALL_DEAD                     = 15,
    PET_BATTLE_REQUEST_NEED_AT_LEAST_1_PET_IN_SLOT      = 16,
    PET_BATTLE_REQUEST_CODEX_LOCKED_BY_AN_ANOTHER_USER  = 17,
    PET_BATTLE_REQUEST_TARGET_IN_A_BATTLEPET            = 18
};

// names extracted from 'FrameXML/SharedPetBattleTemplates.lua'
enum PetBattleAbilityProcType
{
    PET_BATTLE_ABILITY_TURN0_PROC_ON_NONE               = -1,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_APPLY              = 0,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_TAKEN       = 1,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_DEALT       = 2,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_HEAL_TAKEN         = 3,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_HEAL_DEALT         = 4,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_AURA_REMOVED       = 5,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_ROUND_START        = 6,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_ROUND_END          = 7,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_TURN               = 8,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_ABILITY            = 9,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_SWAP_IN            = 10,
    PET_BATTLE_ABILITY_TURN0_PROC_ON_SWAP_OUT           = 11,
};

// -------------------------------------------------------------------------------

// used to calculate pet battle position
struct PetBattleRequest
{
    uint64 OpponentGuid;
    uint32 LocationResult;                              // name dumped from client, use unknown

    float BattleOrigin[3];
    float TeamPositions[PET_BATTLE_MAX_TEAMS][3];
    float BattleFacing;
};

// -------------------------------------------------------------------------------

// used to track abilities that last multiple turns
struct PetBattleActiveAbility
{
    uint32 AbilityId;
    uint8 TurnsPassed;
    uint8 TurnsTotal;
};

// -------------------------------------------------------------------------------

//              stateId  value
typedef std::map<uint32, int32> AuraStateStore;

class PetBattleAura
{
public:
    PetBattleAura(PetBattle* petBattle, uint32 id, uint32 ability, uint32 trigger, BattlePet* caster, BattlePet* target, int32 duration)
        : m_id(id), m_ability(ability), m_duration(duration), m_maxDuration(duration), m_caster(caster), m_target(target),
        m_petBattle(petBattle), m_turn(1), m_expired(false) { }

    uint32 GetId() { return m_id; }
    uint32 GetAbility() { return m_ability; }
    int32 GetDuration() { return m_duration; }
    int32 GetTurn() { return m_turn; }
    bool HasExpired() { return m_expired; }

    void OnApply();
    void OnExpire();
    void Process();
    void Expire();

private:
    uint32 m_id;
    uint32 m_ability;
    uint32 m_trigger;                                   // ability effect that trigger aura
    int32 m_turn;
    int32 m_duration;                                   // duration remaining
    int32 m_maxDuration;

    AuraStateStore m_auraStates;                        // contains states modified by the aura

    BattlePet* m_caster;
    BattlePet* m_target;
    PetBattle* m_petBattle;                             // parent pet battle
    bool m_expired;
};

// -------------------------------------------------------------------------------

#define PET_BATTLE_MOVE_TYPE_COUNT 5

enum PetBattleMoveType
{
    PET_BATTLE_MOVE_TYPE_REQUEST_LEAVE                  = 0,
    PET_BATTLE_MOVE_TYPE_CAST                           = 1,
    PET_BATTLE_MOVE_TYPE_SWAP_OR_PASS                   = 2,
    PET_BATTLE_MOVE_TYPE_CATCH                          = 3,
    PET_BATTLE_MOVE_TYPE_LEAVE_PETBATTLE                = 4,
};

struct PendingRoundMove
{
    uint8 MoveType;
    BattlePet* battlePet;
    uint32 AbilityId;
};

// -------------------------------------------------------------------------------

// TODO: check if there are anymore flags
enum PetBattleTeamInputFlags
{
    PET_BATTLE_TEAM_INPUT_FLAG_NONE                     = 0x00,
    PET_BATTLE_TEAM_INPUT_FLAG_LOCK_ABILITY_1           = 0x01,
    PET_BATTLE_TEAM_INPUT_FLAG_LOCK_ABILITY_2           = 0x02,
    PET_BATTLE_TEAM_INPUT_FLAG_LOCK_PET_SWAP            = 0x04,
    PET_BATTLE_TEAM_INPUT_FLAG_SELECT_NEW_PET           = 0x08
};

typedef std::vector<BattlePet*> BattlePetStore;
typedef std::set<BattlePet*> BattlePetSetStore;

class PetBattleTeam
{
public:
    PetBattleTeam(PetBattle* parent, uint8 teamIndex)
        : m_petBattle(parent), m_teamIndex(teamIndex), m_owner(nullptr), m_ownerGuid(0), m_wildBattlePet(nullptr),
        m_ready(false), m_activePet(nullptr) { }

    void Update();

    PetBattle* GetParentBattle() const { return m_petBattle; }
    Player* GetOwner() const { return m_owner; }
    uint64 GetOwnerGuid() const { return m_ownerGuid; }
    Creature* GetWildBattlePet() const { return m_wildBattlePet; }
    uint8 GetTeamIndex() const { return m_teamIndex; }

    uint8 ConvertToGlobalIndex(uint8 localPetIndex) const;
    uint8 ConvertToLocalIndex(uint8 globalPetIndex) const;

    BattlePet* GetActivePet() const { return m_activePet; }
    void SetActivePet(BattlePet* battlePet) { m_activePet = battlePet; }

    bool IsValidBattlePet(BattlePet* battlePet) const;

    void GetAvaliablePets(BattlePetStore &avaliablePets) const;
    bool CanSwap(BattlePet* battlePet = nullptr, bool ignoreAlive = false) const;

    bool HasMultipleTurnAbility() const;

    bool IsReady() const { return m_ready; }
    void IsReady(bool ready) { m_ready = ready; }

    void SetPendingMove(uint8 moveType, uint32 abilityId, BattlePet* newActivePet);
    PendingRoundMove GetPendingMove() { return m_pendingMove; }

    void ActivePetPrepareCast(uint32 abilityId);
    bool CanActivePetCast(uint32 abilityId) const;
    void DoCasts(int8 procType = PET_BATTLE_ABILITY_TURN0_PROC_ON_NONE);

    uint8 GetTrapStatus() const;

    void AddPlayer(Player* player);
    void AddWildBattlePet(Creature* creature);

    void ResetActiveAbility();

    void ProcessAuras();
    void RemoveExpiredAuras();

    uint8 GetInputStatusFlags() const;

    BattlePetStore BattlePets;
    BattlePetSetStore SeenAction;                       // contains battle pets that have contributed to the battle

    PetBattleActiveAbility ActiveAbility;

private:
    PetBattle* m_petBattle;

    Player* m_owner;
    uint64 m_ownerGuid;
    Creature* m_wildBattlePet;
    BattlePet* m_activePet;
    uint8 m_teamIndex;                                  // 0 = challanger team, 1 = opponent team

    bool m_ready;
    PendingRoundMove m_pendingMove;
};

// -------------------------------------------------------------------------------

// TODO: research remaining target types
enum PetBattleEffectTargetType
{
    PET_BATTLE_EFFECT_TARGET_UNK0           = 0,        // bit, uint32
    PET_BATTLE_EFFECT_TARGET_UNK1           = 1,        // bit, uint32
    PET_BATTLE_EFFECT_TARGET_ACTIVE_PET     = 2,
    PET_BATTLE_EFFECT_TARGET_UPDATE_HEALTH  = 3,
    PET_BATTLE_EFFECT_TARGET_UPDATE_STAT    = 4,
    PET_BATTLE_EFFECT_TARGET_UNK5           = 5,        // 3xbit, 3xuint32 (broadcast text related?)
    PET_BATTLE_EFFECT_TARGET_UPDATE_STATE   = 6,
    PET_BATTLE_EFFECT_TARGET_UPDATE_AURA    = 7
};

struct PetBattleEffectTarget
{
    uint8 Type;
    int8 Target;

    union
    {
        uint32 Health;
        uint32 StatValue;

        struct
        {
            uint32 AuraInstanceId;
            uint32 AbilityId;
            int32 RoundsRemaing;
            uint32 CurrentRound;
        } Aura;

        struct
        {
            uint32 StateId;
            uint32 Value;
        } State;
    };
};

// -------------------------------------------------------------------------------

typedef std::vector<PetBattleEffectTarget> PetBattleEffectTargetStore;

enum PetBattleEffectType
{
    PET_BATTLE_EFFECT_SET_HEALTH            = 0,
    PET_BATTLE_EFFECT_AURA_APPLY            = 1,
    PET_BATTLE_EFFECT_AURA_REMOVE           = 2,
    PET_BATTLE_EFFECT_AURA_CHANGE           = 3,
    PET_BATTLE_EFFECT_ACTIVE_PET            = 4,
    PET_BATTLE_EFFECT_CATCH                 = 5,
    PET_BATTLE_EFFECT_SET_STATE             = 6,
    PET_BATTLE_EFFECT_SET_MAX_HEALTH        = 7,
    PET_BATTLE_EFFECT_SET_SPEED             = 8,
    PET_BATTLE_EFFECT_SET_POWER             = 9,
    PET_BATTLE_EFFECT_TRIGGER_ABILITY       = 10,
    PET_BATTLE_EFFECT_ABILITY_CHANGE        = 11,
    PET_BATTLE_EFFECT_NPC_EMOTE             = 12,
    PET_BATTLE_EFFECT_AURA_PROCESSING_BEGIN = 13,
    PET_BATTLE_EFFECT_AURA_PROCESSING_END   = 14
};

enum PetBattleEffectFlags
{
    PET_BATTLE_EFFECT_FLAG_SKIP_TURN        = 0x00001,
    PET_BATTLE_EFFECT_FLAG_MISS             = 0x00002,
    PET_BATTLE_EFFECT_FLAG_CRITICAL         = 0x00004,
    PET_BATTLE_EFFECT_FLAG_BLOCKED          = 0x00008,
    PET_BATTLE_EFFECT_FLAG_DODGE            = 0x00010,
    PET_BATTLE_EFFECT_FLAG_HEAL             = 0x00020,
    PET_BATTLE_EFFECT_FLAG_REFLECT          = 0x00080,
    PET_BATTLE_EFFECT_FLAG_ABSORB           = 0x00100,
    PET_BATTLE_EFFECT_FLAG_IMMUNE           = 0x00200,
    PET_BATTLE_EFFECT_FLAG_STRONG           = 0x00400,
    PET_BATTLE_EFFECT_FLAG_WEAK             = 0x00800,
    PET_BATTLE_EFFECT_FLAG_KILL             = 0x01000,  // unknown
    PET_BATTLE_EFFECT_FLAG_PERIODIC         = 0x10000   // custom flag (better way of doing this?)
};

class PetBattleEffect
{
public:
    PetBattleEffect(uint8 type, int8 source = PET_BATTLE_NULL_PET_INDEX, uint16 flags = 0, uint32 abilityEffect = 0,
        uint16 turnInstance = 0, uint16 auraInstance = 0, uint8 stackDepth = 0)
        : m_type(type), m_source(source), m_flags(flags), m_abilityEffect(abilityEffect), m_turnInstance(turnInstance),
        m_auraInstance(auraInstance), m_stackDepth(stackDepth) { }

    uint8 GetType() const { return m_type; }
    uint8 GetSource() const { return m_source; }
    uint16 GetFlags() const { return m_flags; }
    uint32 GetAbilityEffect() const { return m_abilityEffect; }
    uint16 GetTurnInstance() const { return m_turnInstance; }
    uint16 GetAuraInstance() const { return m_auraInstance; }
    uint8 GetStackDepth() const { return m_stackDepth; }

    void TargetActivePet(int8 target = PET_BATTLE_NULL_PET_INDEX);
    void TargetUpdateHealth(int8 target, uint32 health);
    void TargetUpdateState(int8 target, uint32 state, uint32 value);
    void TargetUpdateAura(int8 targetPet, uint32 auraInstance, uint32 ability, int32 duration, uint32 turn);
    void TargetUpdateStat(int8 targetPet, uint32 value);

    PetBattleEffectTargetStore Targets;

private:
    uint8 m_type;
    uint16 m_flags;
    int8 m_source;
    uint32 m_abilityEffect;
    uint16 m_turnInstance;
    uint16 m_auraInstance;
    uint8 m_stackDepth;
};

// -------------------------------------------------------------------------------

enum PetBattleType
{
    PET_BATTLE_TYPE_PVE                     = 0,
    PET_BATTLE_TYPE_PVP_DUEL                = 1,
    PET_BATTLE_TYPE_PVP_MATCHMAKING         = 2
};

// internal values used to track battle phase
enum PetBattlePhase
{
    PET_BATTLE_PHASE_SETUP                  = 0,
    PET_BATTLE_PHASE_IN_PROGRESS            = 1,
    PET_BATTLE_PHASE_FINISHED               = 2
};

enum PetBattleRoundResult
{
    PET_BATTLE_ROUND_RESULT_NONE            = 0,
    PET_BATTLE_ROUND_RESULT_INITIALISE      = 1,
    PET_BATTLE_ROUND_RESULT_NORMAL          = 2,
    PET_BATTLE_ROUND_RESULT_CATCH_OR_KILL   = 3
};

enum PetBattleTrapStatus
{
    PET_BATTLE_TRAP_STATUS_DISABLED             = 0,
    PET_BATTLE_TRAP_STATUS_ENABLED              = 1,
    PET_BATTLE_TRAP_STATUS_CANT_TRAP_DEAD_PET   = 3,
    PET_BATTLE_TRAP_STATUS_HEALTH_TOO_HIGH      = 4,
    PET_BATTLE_TRAP_STATUS_TOO_MANY_PETs        = 5,
    PET_BATTLE_TRAP_STATUS_NOT_CAPTURABLE       = 6,
    PET_BATTLE_TRAP_STATUS_CANT_TRAP_NPC_PET    = 7,
    PET_BATTLE_TRAP_STATUS_ALREADY_TRAPPED      = 8
};

typedef std::vector<PetBattleEffect> PetBattleEffectStore;
typedef std::vector<PetBattleTeam*> PetBattleTeamStore;

class PetBattle
{
public:
    PetBattle(uint32 battleId, uint32 timestamp, uint8 type)
        : m_battleId(battleId), m_timestamp(timestamp), m_type(type), m_phase(PET_BATTLE_PHASE_SETUP), m_round(0), TurnInstance(0),
        m_winningTeam(nullptr), m_roundResult(PET_BATTLE_ROUND_RESULT_NONE), m_cagedPet(nullptr), m_timeSinceLastRound(0), m_nextRoundTimer(0) { }

    ~PetBattle();

    void StartBattle();
    void FinishBattle(PetBattleTeam* team, bool forfeit = false);
    void HandleRound();
    void Update(uint32 diff);

    bool Cast(BattlePet* caster, uint32 abilityId, uint8 turn, int8 procType);

    void SwapActivePet(BattlePet* battlePet);
    void UpdatePetState(BattlePet* source, BattlePet* target, uint32 abilityEffect, uint32 state, int32 value, uint16 flags = 0);
    void AddAura(BattlePet* source, BattlePet* target, uint32 ability, uint32 abilityEffect, int32 duration, uint16 flags = 0, uint8 maxAllowed = 0);
    void Kill(BattlePet* killer, BattlePet* victim, uint32 abilityEffect, uint16 flags);
    void Catch(BattlePet* source, BattlePet* target, uint32 abilityEffect);

    uint8 GetFirstAttackingTeam();
    PetBattleTeam* GetWinningTeam() { return m_winningTeam; }

    uint32 GetId() const { return m_battleId; }
    uint8 GetType() const { return m_type; }
    uint32 GetRound() const { return m_round; }
    uint8 GetPhase() const { return m_phase; }
    uint8 GetRoundResult() const { return m_roundResult; }
    BattlePet* GetCagedPet() const { return m_cagedPet; }

    PetBattleTeam* GetTeam(uint64 guid) const;
    uint8 GetTeamIndex(uint8 globalPetId) { return globalPetId < PET_BATTLE_MAX_TEAM_PETS ? PET_BATTLE_CHALLANGER_TEAM : PET_BATTLE_OPPONENT_TEAM; }

    uint32 TurnInstance;                                // dictates the order of spells and effects each round
    PetBattleTeamStore Teams;                           // teams participating in the battle
    PetBattleEffectStore Effects;                       // current round effects

private:
    uint32 m_battleId;                                  // global id of the pet battle
    uint32 m_timestamp;                                 // timestamp when pet battle started

    uint8 m_type;
    uint8 m_phase;
    uint32 m_round;
    uint8 m_roundResult;
    BattlePet* m_cagedPet;

    // different from team timers
    uint32 m_timeSinceLastRound;
    uint32 m_nextRoundTimer;                            // minimum time before the next round will be processed by server

    PetBattleTeam* m_winningTeam;
};

// -------------------------------------------------------------------------------

#define PET_BATTLE_SYSTEM_UPDATE_BATTLE_TIMER 200       // update pet battles every 200 miliseconds
#define PET_BATTLE_SYSTEM_REMOVE_BATTLE_TIMER 1000      // remove old pet battles every second

//          petBattleId
typedef std::map<uint32, PetBattle*> PetBattleStore;
//           playerGuid  petBattleId
typedef std::map<uint64, uint32> PlayerPetBattleStore;

typedef std::set<PetBattle*> PetBattleRemoveStore;

class PetBattleSystem
{
public:
    PetBattleSystem()
        : m_globalPetBattleId(0), m_updatePetBattlesTimer(0), m_removePetBattlesTimer(0) { }

    void Update(uint32 diff);

    PetBattle* Create(WorldObject* challenger, WorldObject* opponent, uint8 type);
    void Remove(PetBattle* petBattle);

    void ForfietBattle(uint64 guid);
    void ForfietBattle(PetBattle* petBattle, PetBattleTeam* team);

    PetBattle* GetPlayerPetBattle(uint64 guid);

private:
    uint32 m_globalPetBattleId;
    PetBattleStore m_petBattles;                        // contains battle ids to pet battle instances
    PlayerPetBattleStore m_playerPetBattles;            // contains player GUIDs to battle ids

    uint32 m_updatePetBattlesTimer;
    uint32 m_removePetBattlesTimer;
    PetBattleRemoveStore m_petBattlesToRemove;
};

#define sPetBattleSystem (ACE_Singleton<PetBattleSystem, ACE_Null_Mutex>::instance())

#endif
