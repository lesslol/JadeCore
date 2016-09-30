/*
* Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

/**
* @file cs_mmaps.cpp
* @brief .mmap related commands
*
* This file contains the CommandScripts for all
* mmap sub-commands
*/

#include "ScriptMgr.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "PointMovementGenerator.h"
#include "PathGenerator.h"
#include "MMapFactory.h"
#include "Map.h"
#include "TargetedMovementGenerator.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

class mmaps_commandscript : public CommandScript
{
public:
	mmaps_commandscript() : CommandScript("mmaps_commandscript") { }

	ChatCommand* GetCommands() const override
	{
		static ChatCommand mmapCommandTable[] =
		{
			{ NULL, 0, false, NULL, "", NULL }
		};

		static ChatCommand commandTable[] =
		{
			{ "mmap", SEC_ADMINISTRATOR, true, NULL, "", mmapCommandTable },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return commandTable;
	}


};

void AddSC_mmaps_commandscript()
{
	new mmaps_commandscript();
}