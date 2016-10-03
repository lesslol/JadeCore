SET @SS_ENTRY := 37108;
SET @SR_ENTRY := 37173;
SET @SM_ENTRY := 37174;

UPDATE `quest_template` SET `PrevQuestId`=0, `NextQuestId`=24470, `NextQuestIdChain`=24470 WHERE `Id`=24469;
UPDATE `quest_template` SET `PrevQuestId`=24469, `NextQuestId`=24473, `NextQuestIdChain`=24473 WHERE `Id`=24470;
UPDATE `quest_template` SET `PrevQuestId`=24470, `NextQuestId`=0, `NextQuestIdChain`=0 WHERE `Id`=24473;
UPDATE `creature` SET `equipment_id`=37177 WHERE `id`=37177;
DELETE FROM `creature_equip_template` WHERE `entry`=37177;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(37177, 2023, 0, 2552);
DELETE FROM `creature` WHERE `guid`=145597;
UPDATE `creature` SET `MovementType`=0,`spawndist`=0 WHERE `id` IN (@SS_ENTRY, @SR_ENTRY, @SM_ENTRY);
UPDATE `creature_template` SET `faction_A`=35,`faction_H`=35 WHERE `entry` IN (@SS_ENTRY, @SR_ENTRY, @SM_ENTRY);
DELETE FROM `creature_text` WHERE `entry` IN (@SS_ENTRY, @SR_ENTRY, @SM_ENTRY);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@SS_ENTRY,0,0,"Da spirits be angry with us.",12,0,100,1,0,0,"Soothsayer Shi'kala"),
(@SS_ENTRY,1,0,"I don' know why the spirits be rejectin' us so.",12,0,100,1,0,0,"Soothsayer Shi'kala"),
(@SS_ENTRY,2,0,"Don' worry, child. Grik'nir gonna help us get through this.",12,0,100,1,0,0,"Soothsayer Shi'kala"),
(@SR_ENTRY,0,0,"What we gon' do now, you ask ? We wait.",12,0,100,1,0,0,"Soothsayer Rikkari"),
(@SR_ENTRY,1,0,"Grik'nir says he gon' talk to the elemental, get it to fight on our side.",12,0,100,1,0,0,"Soothsayer Rikkari"),
(@SR_ENTRY,2,0,"Soon enough we take over dis valley. Soon enough.",12,0,100,1,0,0,"Soothsayer Rikkari"),
(@SM_ENTRY,0,0,"Our land be a land of ice an' snow",12,0,100,1,0,0,"Soothsayer Mirim'koa"),
(@SM_ENTRY,1,0,"But beneath the earth, child, there always be fire.",12,0,100,1,0,0,"Soothsayer Mirim'koa"),
(@SM_ENTRY,2,0,"De spirit come from deep down to talk with Grik'nir.",12,0,100,1,0,0,"Soothsayer Mirim'koa");
UPDATE `creature_template` SET `AIName`="", `scriptname`="npc_quest_trolling_for_information" WHERE `entry` IN (@SS_ENTRY, @SR_ENTRY, @SM_ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SS_ENTRY, @SR_ENTRY, @SM_ENTRY) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@SS_ENTRY*100, @SR_ENTRY*100, @SM_ENTRY*100) AND `source_type`=9;
