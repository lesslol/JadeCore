DELETE FROM `spell_group` WHERE `spell_id` IN (155522, 160073, 52109);

DELETE FROM `spell_proc_event` WHERE `entry` IN (145378, 144317, 146198);

DELETE FROM `disables` WHERE `sourceType` = 0 AND `entry` IN (0, 163668);

DELETE FROM `item_script_names` WHERE `Id` = 0;