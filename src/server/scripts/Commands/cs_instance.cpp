/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/* ScriptData
Name: instance_commandscript
%Complete: 100
Comment: All instance related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "Group.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "MapManager.h"
#include "World.h"

class instance_commandscript : public CommandScript
{
public:
    instance_commandscript() : CommandScript("instance_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand instanceCommandTable[] =
        {
            { "listbinds",          SEC_ADMINISTRATOR,  false,  &HandleInstanceListBindsCommand,    "", NULL },
            { "unbind",             SEC_ADMINISTRATOR,  false,  &HandleInstanceUnbindCommand,       "", NULL },
            { "dungeonclear",       SEC_ADMINISTRATOR, false,   &HandleDungeonClearnbindCommand, "", NULL },
            { "resetallencounters", SEC_ADMINISTRATOR, false,   &HandleResetAllEncountersbindCommand, "", NULL },
            { "stats",              SEC_ADMINISTRATOR,  true,   &HandleInstanceStatsCommand,        "", NULL },
            { "savedata",           SEC_ADMINISTRATOR,  false,  &HandleInstanceSaveDataCommand,     "", NULL },
            { NULL,             0,                  false,  NULL,                               "", NULL }
        };

        static ChatCommand ratesCommandTable[] =
        {
            { "info", SEC_ADMINISTRATOR, false, &HandleRateDataInfo, "", NULL },
            { "delete", SEC_ADMINISTRATOR, false, &HandleRateDataDelete, "", NULL },
            { "xp",     SEC_ADMINISTRATOR,     false, &HandleRateDataXp, "", NULL },
            { "gold", SEC_ADMINISTRATOR, false, &HandleRateDataGold, "", NULL },
            { "honor", SEC_ADMINISTRATOR, false, &HandleRateDataHonor, "", NULL },
            { NULL, 0, false, NULL, "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "instance",          SEC_ADMINISTRATOR,  true,   NULL,                               "", instanceCommandTable },
            { "rates",             SEC_PLAYER,  true,   NULL,                               "", ratesCommandTable },
            { NULL,             0,                     false,  NULL,                               "", NULL }
        };

        return commandTable;
    }

    static bool HandleRateDataInfo(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Create new values if there's no previous ones.
        PreparedStatement* stmt = NULL;
        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RATE_TEMPLATE);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = WorldDatabase.Query(stmt);
        if (result)
        {
            Field* field = result->Fetch();

            uint32 l_Guid =  field[0].GetInt32();
            uint32 l_Xp =    field[1].GetInt32();
            uint32 l_Honor = field[2].GetInt32();
            uint32 l_Gold =  field[3].GetInt32();

            handler->PSendSysMessage("Your current customized rates are: XP: %u, HONOR: %u, GOLD: %u ", l_Xp, l_Honor, l_Gold);
            return true;
        }
        else
        return false;

        return true;
    }

    static bool HandleRateDataDelete(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Create new values if there's no previous ones.
        PreparedStatement* stmt = NULL;
        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RATE_TEMPLATE);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = WorldDatabase.Query(stmt);
        if (result)
        {
            CharacterDatabase.PExecute("DELETE FROM personal_rates_table WHERE guid = %u", player->GetGUID());
            handler->PSendSysMessage("All your personal customized rate data has been removed and is now once again based on the server default rates.");
        }
        else
            handler->PSendSysMessage("There's no personal rates currently to remove, you're on server's default rates which are: XP: %f, HONOR: %f, GOLD: %f ", sWorld->getRate(RATE_XP_KILL), sWorld->getRate(RATE_HONOR), sWorld->getRate(RATE_DROP_MONEY));

        return true;
    }

    static bool HandleRateDataXp(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Create new values if there's no previous ones.
        PreparedStatement* stmt = NULL;
        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RATE_TEMPLATE);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = WorldDatabase.Query(stmt);
        if (!result)
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_RATE_TEMPLATE);
            stmt->setUInt32(0, player->GetGUIDLow());
            stmt->setUInt32(1, NULL);
            stmt->setUInt32(2, NULL);
            stmt->setUInt32(3, NULL);

            WorldDatabase.Execute(stmt);
            
            return true;
        }
        else
        {
            // Handle XP Rates
            char* l_XpRate = strtok((char*)args, " ");
            uint32 l_XpRateNum = atoi(l_XpRate);

            if (float(l_XpRateNum) > sWorld->getRate(RATE_XP_KILL))
            {
                handler->PSendSysMessage("Your personal rate cannot be any higher then server's static rates.");
                return false;
            }

            PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_XP_RATE_TEMPLATE);

            stmt->setUInt32(0, l_XpRateNum);
            stmt->setUInt32(1, player->GetGUIDLow());

            WorldDatabase.Execute(stmt);  

            return true;
        }
        return true;
    }

    static bool HandleRateDataHonor(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Create new values if there's no previous ones.
        PreparedStatement* stmt = NULL;
        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RATE_TEMPLATE);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = WorldDatabase.Query(stmt);
        if (!result)
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_RATE_TEMPLATE);
            stmt->setUInt32(0, player->GetGUIDLow());
            stmt->setUInt32(1, NULL);
            stmt->setUInt32(2, NULL);
            stmt->setUInt32(3, NULL);

            WorldDatabase.Execute(stmt);
            return true;
        }
        else
        {

            // Handle HONOR Rates
            char* l_HonorRate = strtok((char*)args, " ");
            uint32 l_HonorRateNum = atoi(l_HonorRate);

            if (float(l_HonorRateNum) > sWorld->getRate(RATE_HONOR))
            {
                handler->PSendSysMessage("Your personal rate cannot be any higher then server's static rates.");
                return false;
            }

            PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_HONOR_RATE_TEMPLATE);

            stmt->setUInt32(0, l_HonorRateNum);
            stmt->setUInt32(1, player->GetGUIDLow());

            WorldDatabase.Execute(stmt);
            return true;
        }
        return true;
    }

    // Handle Gold Rates
    static bool HandleRateDataGold(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        // Create new Gold if there's no previous ones.
        PreparedStatement* stmt = NULL;
        stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RATE_TEMPLATE);
        stmt->setUInt32(0, player->GetGUIDLow());
        PreparedQueryResult result = WorldDatabase.Query(stmt);
        if (!result)
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_INS_RATE_TEMPLATE);
            stmt->setUInt32(0, player->GetGUIDLow());
            stmt->setUInt32(1, NULL);
            stmt->setUInt32(2, NULL);
            stmt->setUInt32(3, NULL);

            WorldDatabase.Execute(stmt);
            return true;
        }
        else
        {

            // Handle Money Rates
            char* l_MoneyRate = strtok((char*)args, " ");
            uint32 l_MoneyRateNum = atoi(l_MoneyRate);

            if (float(l_MoneyRateNum) > sWorld->getRate(RATE_DROP_MONEY))
            {
                handler->PSendSysMessage("Your personal rate cannot be any higher then server's static rates.");
                return false;
            }

            PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(l_MoneyRateNum);

            stmt->setUInt32(0, l_MoneyRateNum);
            stmt->setUInt32(1, player->GetGUIDLow());

            WorldDatabase.Execute(stmt);
            return true;
        }
        return true;
    }

    // Instance
    static std::string GetTimeString(uint64 time)
    {
        uint64 days = time / DAY, hours = (time % DAY) / HOUR, minute = (time % HOUR) / MINUTE;
        std::ostringstream ss;
        if (days)
            ss << days << "d ";
        if (hours)
            ss << hours << "h ";
        ss << minute << 'm';
        return ss.str();
    }

    static bool HandleInstanceListBindsCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        uint32 counter = 0;
        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
        {
            Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
            for (Player::BoundInstancesMap::const_iterator itr = binds.begin(); itr != binds.end(); ++itr)
            {
                InstanceSave* save = itr->second.save;
                std::string timeleft = GetTimeString(save->GetResetTime() - time(NULL));
                handler->PSendSysMessage("map: %d inst: %d perm: %s diff: %d canReset: %s TTR: %s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no",  save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                counter++;
            }
        }
        handler->PSendSysMessage("player binds: %d", counter);

        counter = 0;
        if (Group* group = player->GetGroup())
        {
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Group::BoundInstancesMap &binds = group->GetBoundInstances(Difficulty(i));
                for (Group::BoundInstancesMap::const_iterator itr = binds.begin(); itr != binds.end(); ++itr)
                {
                    InstanceSave* save = itr->second.save;
                    std::string timeleft = GetTimeString(save->GetResetTime() - time(NULL));
                    handler->PSendSysMessage("map: %d inst: %d perm: %s diff: %d canReset: %s TTR: %s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no",  save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                    counter++;
                }
            }
        }
        handler->PSendSysMessage("group binds: %d", counter);

        return true;
    }

    static bool HandleInstanceUnbindCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* player = handler->getSelectedPlayer();
        if (!player)
            player = handler->GetSession()->GetPlayer();

        char* map = strtok((char*)args, " ");
        char* pDiff = strtok(NULL, " ");
        int8 diff = -1;
        if (pDiff)
            diff = atoi(pDiff);
        uint16 counter = 0;
        uint16 MapId = 0;

        if (strcmp(map, "all"))
        {
            MapId = uint16(atoi(map));
            if (!MapId)
                return false;
        }

        for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
        {
            Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
            for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
            {
                InstanceSave* save = itr->second.save;
                if (itr->first != player->GetMapId() && (!MapId || MapId == itr->first) && (diff == -1 || diff == save->GetDifficulty()))
                {
                    std::string timeleft = GetTimeString(save->GetResetTime() - time(NULL));
                    handler->PSendSysMessage("unbinding map: %d inst: %d perm: %s diff: %d canReset: %s TTR: %s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no", save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str());
                    player->UnbindInstance(itr, Difficulty(i));
                    counter++;
                }
                else
                    ++itr;
            }
        }
        handler->PSendSysMessage("instances unbound: %d", counter);

        return true;
    } 

    static bool HandleDungeonClearnbindCommand(ChatHandler* handler, char const* args)
    {     
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        CharacterDatabase.PExecute("DELETE FROM character_instance WHERE guid = %u AND permanent = 0", player->GetGUID());
  
        return true;
    }
    
    static bool HandleResetAllEncountersbindCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player)
            return false;

        CharacterDatabase.PExecute("DELETE FROM character_instance WHERE permanent = 0");
        return true;
    }

    static bool HandleInstanceStatsCommand(ChatHandler* handler, char const* /*args*/)
    {
        handler->PSendSysMessage("instances loaded: %d", sMapMgr->GetNumInstances());
        handler->PSendSysMessage("players in instances: %d", sMapMgr->GetNumPlayersInInstances());
        handler->PSendSysMessage("instance saves: %d", sInstanceSaveMgr->GetNumInstanceSaves());
        handler->PSendSysMessage("players bound: %d", sInstanceSaveMgr->GetNumBoundPlayersTotal());
        handler->PSendSysMessage("groups bound: %d", sInstanceSaveMgr->GetNumBoundGroupsTotal());

        return true;
    }

    static bool HandleInstanceSaveDataCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Map* map = player->GetMap();
        if (!map->IsDungeon())
        {
            handler->PSendSysMessage("Map is not a dungeon.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!((InstanceMap*)map)->GetInstanceScript())
        {
            handler->PSendSysMessage("Map has no instance data.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        ((InstanceMap*)map)->GetInstanceScript()->SaveToDB();

        return true;
    }
};

void AddSC_instance_commandscript()
{
    new instance_commandscript();
}
