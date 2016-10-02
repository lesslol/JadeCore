DELETE FROM `spell_script_names` WHERE `ScriptName` = "spell_swirl_target";
DELETE FROM `spell_script_names` WHERE `ScriptName` = "spell_sha_erupting_damage";
DELETE FROM `spell_script_names` WHERE `ScriptName` = "immersius_spell_split";
DELETE FROM `spell_script_names` WHERE `ScriptName` = "immersius_spell_sha_bolt_missile";

UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "boss_immersus";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_trigger_sha_pool";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_trigger_sha_swirl_circular";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_trigger_swirl_circle";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_creature_contaminated_puddle";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_creature_sha_puddle";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_creature_sha_pool_heroic";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "immersus_creature_swelling_creature";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "siege_of_orgrimmar_lorewalker_cho";
UPDATE `creature_template` SET `ScriptName` = "" WHERE `ScriptName` = "siege_of_orgrimmar_trigger_bubble";