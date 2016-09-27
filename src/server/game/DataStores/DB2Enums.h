/*
* Copyright (C) 2015-2016 JadeCore <https://github.com/JadeEmu/JadeCore_547>
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

#ifndef DB2_ENUMS_H
#define DB2_ENUMS_H

enum BattlePetSpeciesFlags
{
    BATTLE_PET_FLAG_NONE                        = 0x0000,
    BATTLE_PET_FLAG_LIMITED_ABILITIES           = 0x0001, // battle pets with less than 6 abilites have this flag
    BATTLE_PET_FLAG_NOT_TRADABLE                = 0x0002,
    BATTLE_PET_FLAG_NOT_ACCOUNT_BOUND           = 0x0004,
    BATTLE_PET_FLAG_RELEASABLE                  = 0x0008,
    BATTLE_PET_FLAG_NOT_CAGEABLE                = 0x0010,
    BATTLE_PET_FLAG_NOT_TAMEABLE                = 0x0020,
    BATTLE_PET_FLAG_UNIQUE                      = 0x0040,
    BATTLE_PET_FLAG_COMPANION                   = 0x0080,
    BATTLE_PET_FLAG_UNKNOWN_2                   = 0x0100,
    BATTLE_PET_FLAG_UNKNOWN_3                   = 0x0200,
    BATTLE_PET_FLAG_ELITE                       = 0x0400,
    BATTLE_PET_FLAG_UNKNOWN_4                   = 0x0800, // battle pets 89, 169 and 218, these also have not tradable flag but don't display message in game
    BATTLE_PET_FLAG_UNKNOWN_5                   = 0x1000  // only seen on battle pet 316 (Cenarion Hatchling)
};

enum BattlePetAbilityFlags
{
    BATTLE_PET_ABILITY_FLAG_NONE                = 0x00,
    BATTLE_PET_ABILITY_FLAG_APPLIED_ABILITY     = 0x01,   // ability is applied by another and can't be used directly
    BATTLE_PET_ABILITY_FLAG_UNKNOWN_2           = 0x02,
    BATTLE_PET_ABILITY_FLAG_UNKNOWN_3           = 0x04,   // traps and family passives have this flag
    BATTLE_PET_ABILITY_FLAG_UNKNOWN_4           = 0x08,   // abilities 240 and 763 have this flag
    BATTLE_PET_ABILITY_FLAG_UNKNOWN_5           = 0x10,   // abilities 763, 970 and 971 have this flag
};

#endif DB2_ENUMS_H