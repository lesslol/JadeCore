/*
* Copyright (C) 2008-20XX JadeCore <http://www.pandashan.com>
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#ifndef THRONE_OF_THUNDER_H_
#define THRONE_OF_THUNDER_H_

#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"
#include "CreatureAIImpl.h"

enum eData
{
    DATA_JINKORH,
    DATA_HORRIDON,

    DATA_FARA_DOOR,
    DATA_GURU_DOOR,
    DATA_DRAK_DOOR,
    DATA_AMANI_DOOR,

    DATA_GARAJAL,
    DATA_MALAK,
    DATA_KARAZJIN,
    DATA_HIGH_PRIESTSESS,
    DATA_SAND_CRAWLER,

    DATA_JINROKH_DOOR,
    DATA_JINROKH_HORRIDON_DOOR,
    DATA_HORRIDON_DOOR,
    DATA_HORRIDON_COUNCIL_DOOR,
    DATA_COUNCIL_TORTOS_DOOR,

    DATA_JI_KUN,

    DATA_TORTOS,
    DATA_MEGAERA,
    DATA_DURUMU,
};
enum eActions
{ //617299803
};
enum eCreatures
{
    BOSS_JINROKH = 69465,
    BOSS_HORRIDON = 68476,

    BOSS_MALAK = 69131,
    BOSS_KAZARJIN = 69134,
    BOSS_MARLI = 69132,
    BOSS_SUL = 69078,
    CREATURE_GARJAL = 70056,

    BOSS_TORTOS = 67977,
    BOSS_MEGAERA = 68065,
    BOSS_JI_KUN = 69712,

    CREATURE_HEAD_FIRE = 70212,
    CREATURE_HEAD_FROST = 70235,
    CREATURE_HEAD_VENOM = 70247,
};

enum eGameObjects
{
    // GAME_OBJECT_MOGU_STATUE = ,
    OBJECT_GURUBASHI_DOOR = 218670,
    OBJECT_DRAKKARI_DOOR = 218671,
    OBJECT_FARAKKI_DOOR = 218672,
    OBJECT_AMANI_DOOR = 218673,
    // DOORS
    OBJECT_JINROKH_ENTRANCE = 444555,
    OBJECT_JINROKH_HORRIDON = 444556,
    OBJECT_HORRIDON_ENTRACE = 444557,
    OBJECT_HORRIDON_COUNCIL = 444558,
    OBJECT_COUNCIL_TORTOS = 444559,
};
enum ePhases
{
};
enum eWeapons
{
};


#endif // THRONE_OF_THUNDER_H_
