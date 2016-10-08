UPDATE `creature_template` SET `ScriptName` = "boss_immerseus" WHERE `entry` = 71543;
UPDATE `creature_template` SET `ScriptName` = "npc_sha_splash_bolt_immerseus" WHERE `entry` = 71544;
UPDATE `creature_template` SET `ScriptName` = "npc_swirl_immerseus" WHERE `entry` = 71548;
UPDATE `creature_template` SET `ScriptName` = "npc_swirl_target_immerseus" WHERE `entry` = 71550;
UPDATE `creature_template` SET `ScriptName` = "npc_sha_puddle_immerseus" WHERE `entry` = 71603;
UPDATE `creature_template` SET `ScriptName` = "npc_contaminated_puddle_immerseus" WHERE `entry` = 71604;

DELETE FROM `spell_script_names` WHERE `spell_id` = 143290;
DELETE FROM `spell_script_names` WHERE `spell_id` = 143020;
DELETE FROM `spell_script_names` WHERE `spell_id` = 143469;
DELETE FROM `spell_script_names` WHERE `spell_id` = 143538;

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (143290, "spell_immerseus_sha_bolt");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (143020, "spell_immerseus_split");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (143469, "spell_immerseus_reform");
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (143538, "spell_immerseus_congealing");