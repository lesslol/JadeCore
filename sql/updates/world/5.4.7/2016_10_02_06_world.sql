DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3871205,3871207,3871208,3871209,3871210,3871211,3871212,3871213,3871214,3871215,3871216,3871217,3871218,3871219,3871220,3871221,3871222,3871223,3871224,3871225,57005,57167,57168,57169,57175,57176,59838,101180,111790,111791,174740,987655,572870,572880,572890,483080,483090,484940,350750,350751,352220,361760,366150,371791,381110,383870,401850,411000,411001,411002,411003,485880,485890,485900,485920,504710,484960,15930,0,9935,40823,43499,46044,46045,46046,46047,75548,77555,341735,341737,341738,341739,341740,341741,341742,341743,341744,341745,412061,412062,412063,412064,412065,412066,412067,412068,412069,452610,452640,452660,452670,1449500,6000001,7000000,35999,7);

-- Alpine Chipmunk SAI
SET @GUID := -214569;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=49779;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,1,2,40,0,100,0,5,26645,0,0,54,20000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 5 - pause path"),
(@GUID,0,2,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 5 - STATE_USESTANDING"),
(@GUID,0,3,4,40,0,100,0,10,26645,0,0,54,23000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 10 - pause path"),
(@GUID,0,4,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 10 - STATE_WORK_MINING"),
(@GUID,0,5,6,40,0,100,0,18,26645,0,0,54,25000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 18 - pause path"),
(@GUID,0,6,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 18 - STATE_WORK_MINING"),
(@GUID,0,7,8,40,0,100,0,24,26645,0,0,54,25000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 24 - pause path"),
(@GUID,0,8,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fizzcrank Engineering Crew - Reach wp 24 - STATE_USESTANDING");

-- Reef Frenzy SAI
SET @GUID := -195495;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=2173;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,1,0,60,0,20,0,4000,5000,4000,5000,1,1,2000,0,0,0,0,1,0,0,0,0,0,0,0,"Panicked Citizen 1 - Every 4-5 Seconds, 20% Chance to Say Random Phrase");

-- Feero Ironhand SAI
SET @ENTRY := 4484;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,19,0,100,1,976,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Feero Ironhand - On Quest Accept (Supplies to Aubderdine) - Store Targetlist "),
(@ENTRY,0,1,2,61,0,100,1,0,0,0,0,2,774,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Quest Accept (Supplies to Aubderdine) - Set Faction"),
(@ENTRY,0,2,3,61,0,100,1,0,0,0,0,19,512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Quest Accept (Supplies to Aubderdine) - Remove Unit Flags"),
(@ENTRY,0,3,0,61,0,100,1,0,0,0,0,1,7,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Quest Accept (Supplies to Aubderdine) - Say Line 7"),
(@ENTRY,0,4,0,7,0,100,0,0,0,0,0,19,512,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Evade - Remove Unit Flags"),
(@ENTRY,0,5,6,40,0,100,1,18,4484,0,0,1,0,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP18 - Say Line 0"),
(@ENTRY,0,7,0,61,0,100,1,0,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP18 - Pause WP (2 Seconds)"),
(@ENTRY,0,8,0,40,0,100,1,19,4484,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP19 - Say Line 1"),
(@ENTRY,0,9,10,40,0,100,1,27,4484,0,0,1,2,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP27 - Say"),
(@ENTRY,0,11,0,61,0,100,1,0,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP27 - Pause WP (5 Seconds)"),
(@ENTRY,0,12,0,40,0,100,1,28,4484,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP28 - Say Line 3"),
(@ENTRY,0,13,14,40,0,100,1,41,4484,0,0,1,4,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP41 - Say Line 4"),
(@ENTRY,0,15,0,61,0,100,1,0,0,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP41 - Pause WP (10 Seconds)"),
(@ENTRY,0,16,17,40,0,100,1,43,4484,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP43 - Say Line 5"),
(@ENTRY,0,17,18,61,0,100,1,0,0,0,0,15,976,0,0,0,0,0,12,1,0,0,0,0,0,0,"Feero Ironhand - On Reached 43 - Call Areaexploredoreventhappens"),
(@ENTRY,0,18,19,61,0,100,1,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached 43 - Set Run"),
(@ENTRY,0,19,0,61,0,100,1,0,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP43 - Pause WP (5 Seconds)"),
(@ENTRY,0,20,0,40,0,100,1,45,4484,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Feero Ironhand - On Reached WP45 - Despawn"),
(@ENTRY,0,21,0,6,0,100,1,0,0,0,0,6,976,0,0,0,0,0,12,1,0,0,0,0,0,0,"Feero Ironhand - On Death - Fail Quest"),
(@ENTRY,0,22,0,52,0,100,1,2,4484,0,0,45,1,1,0,0,0,0,9,3893,0,100,0,0,0,0,"Feero Ironhand - On Text Over line 2 - Set Data Forsaken Scout"),
(@ENTRY,0,23,0,52,0,100,1,4,4484,0,0,1,0,5000,0,0,0,0,19,3899,0,0,0,0,0,0,"Feero Ironhand - On Text Over line 4 - Say Line 0 (Balizar the Umbrage)"),
(@ENTRY,0,27,0,52,0,100,1,0,4484,0,0,45,1,1,0,0,0,0,9,3879,0,100,0,0,0,0,"Feero Ironhand - On Text Over line 0 - Set Data Dark Strand assasin");

-- Mosshide Mystic SAI
SET @ENTRY := 1013;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,4,0,15,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - On Aggro - Say Line 0"),
(@ENTRY,0,1,0,0,0,100,0,0,0,3300,5100,11,9532,64,0,0,0,0,2,0,0,0,0,0,0,0,"Mosshide Mystic - In Combat CMC - Cast 'Lightning Bolt'"),
(@ENTRY,0,1,2,4,0,100,0,0,0,0,0,11,9532,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mosshide Mystic - On Aggro - Cast Lightning Bolt"),
(@ENTRY,0,2,0,0,0,30,1,14400,14400,0,0,11,11436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mosshide Mystic - In Combat - Cast 'Slow'"),
(@ENTRY,0,4,0,2,0,100,1,16,30,0,0,11,3288,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - Between 16-30% Health - Cast 'Moss Hide'"),
(@ENTRY,0,4,5,3,0,100,0,0,11,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 11% Mana - Allow Combat Movement"),
(@ENTRY,0,5,0,2,0,100,1,0,15,0,0,28,3288,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - Between 0-15% Health - Remove Aura 'Moss Hide'"),
(@ENTRY,0,6,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,7,0,9,0,100,0,0,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 0 - 15 Range - Allow Combat Movement"),
(@ENTRY,0,8,9,3,0,100,0,20,100,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 100% Mana - Allow Combat Movement"),
(@ENTRY,0,9,0,61,0,100,0,0,0,0,0,22,6,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 100% Mana - Set Phase 6"),
(@ENTRY,0,10,0,9,0,100,0,40,60,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 40 - 60 Range - Set Phase 1"),
(@ENTRY,0,11,0,9,0,100,0,0,5,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 0 - 5 Range - Set Phase 1"),
(@ENTRY,0,12,0,0,0,30,1,14400,14400,0,0,11,11436,0,0,0,0,0,2,0,0,0,0,0,0,0,"Mosshide Mystic - In Combat - Cast Slow"),
(@ENTRY,0,14,0,2,0,30,1,0,30,0,0,11,3288,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 30% HP - Cast Moss Hide"),
(@ENTRY,0,15,16,2,0,100,1,0,15,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 15% HP - Set Phase 1"),
(@ENTRY,0,16,0,61,0,100,1,0,0,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosshide Mystic - At 15% HP - Flee For Assist"),
(@ENTRY,0,17,0,61,0,100,0,0,15,0,0,28,3288,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosshide Mystic - At 15% HP - Remove Aura Moss Hide");

-- Bluegill Oracle SAI
SET @ENTRY := 1029;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,2,0,100,1,0,60,0,0,11,6274,0,0,0,0,0,1,0,0,0,0,0,0,0,"Bluegill Oracle - Between 0-60% Health - Cast 'Healing Ward' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Bluegill Oracle - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Frostmane Snowstrider SAI
SET @ENTRY := 1121;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,0,0,100,0,3000,3000,60000,60000,11,6950,0,0,0,0,0,2,0,0,0,0,0,0,0,"Frostmane Snowstrider - In Combat - Cast 'Faerie Fire' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Frostmane Snowstrider - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Scarlet Paladin SAI
SET @ENTRY := 1834;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,5000,8000,12000,11,14517,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Paladin - In Combat - Cast 'Crusader Strike' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,6000,8000,9000,14000,11,13953,0,0,0,0,0,2,0,0,0,0,0,0,0,"Scarlet Paladin - In Combat - Cast 'Holy Strike' (No Repeat)"),
(@ENTRY,0,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Scarlet Paladin - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Nightlash SAI
SET @ENTRY := 1983;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,9000,21000,25000,11,3485,0,0,0,0,0,2,0,0,0,0,0,0,0,"Nightlash - In Combat - Cast 'Wail of Nightlash'");

-- Gnarlpine Augur SAI
SET @ENTRY := 2011;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,2,0,100,1,0,30,0,0,11,5628,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cast Gnarlpine Vengeance at 30% HP");


-- Dun Garok Priest SAI
SET @ENTRY := 2346;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3400,4800,11,9734,64,0,0,0,0,2,0,0,0,0,0,0,0,"Dun Garok Priest - In Combat CMC - Cast 'Holy Smite'"),
(@ENTRY,0,0,1,1,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Out of Combat - Disable Combat Movement"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Out of Combat - Set Event Phase 0"),
(@ENTRY,0,2,0,2,0,100,1,0,30,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-30% Health - Flee For Assist"),
(@ENTRY,0,2,3,4,0,100,0,0,0,0,0,11,9734,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dun Garok Priest - On Aggro - Cast 'Holy Smite'"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - On Aggro - Increment Phase By 0"),
(@ENTRY,0,4,0,9,0,100,0,0,40,3400,4800,11,9734,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dun Garok Priest - Within 0-40 Range - Cast 'Holy Smite'"),
(@ENTRY,0,5,6,3,0,100,0,0,7,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-7% Mana - Enable Combat Movement"),
(@ENTRY,0,6,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-7% Mana - Increment Phase By 0"),
(@ENTRY,0,7,0,9,0,100,1,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Within 35-80 Range - Enable Combat Movement"),
(@ENTRY,0,8,0,9,0,100,1,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Within 5-15 Range - Disable Combat Movement"),
(@ENTRY,0,9,0,9,0,100,1,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Within 0-5 Range - Enable Combat Movement"),
(@ENTRY,0,10,0,3,0,100,0,15,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 15-100% Mana - Decrement Phase By 1"),
(@ENTRY,0,12,0,2,0,100,1,0,30,0,0,22,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-30% Health - Set Event Phase 3"),
(@ENTRY,0,13,14,2,0,100,0,0,30,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-30% Health - Enable Combat Movement"),
(@ENTRY,0,14,0,61,0,100,0,0,0,0,0,25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Dun Garok Priest - Between 0-30% Health - Flee For Assist");


-- Dark Iron Supplier SAI
SET @ENTRY := 2575;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,2300,1300,3800,11,744,32,0,0,0,0,2,0,0,0,0,0,0,0,"Dark Iron Supplier - In Combat - Cast 'Poison' (No Repeat)"),
(@ENTRY,0,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"Dark Iron Supplier - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Stonevault Seer SAI
SET @ENTRY := 2892;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Out of Combat - Disable Combat Movement"),
(@ENTRY,0,1,2,4,0,100,0,0,0,0,0,11,9532,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonevault Seer - On Aggro - Cast 'Lightning Bolt'"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - On Aggro - Increment Phase By 0"),
(@ENTRY,0,3,0,9,0,100,0,0,40,3600,4800,11,9532,0,0,0,0,0,2,0,0,0,0,0,0,0,"Stonevault Seer - Within 0-40 Range - Cast 'Lightning Bolt'"),
(@ENTRY,0,4,5,3,0,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Between 0-15% Mana - Enable Combat Movement"),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Between 0-15% Mana - Increment Phase By 0"),
(@ENTRY,0,6,0,9,0,100,1,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Within 35-80 Range - Enable Combat Movement"),
(@ENTRY,0,7,0,9,0,100,1,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Within 5-15 Range - Disable Combat Movement"),
(@ENTRY,0,8,0,9,0,100,1,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Within 0-5 Range - Enable Combat Movement"),
(@ENTRY,0,9,0,3,0,100,0,30,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Between 30-100% Mana - Decrement Phase By 1"),
(@ENTRY,0,11,0,2,0,100,1,0,15,0,0,22,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Between 0-15% Health - Set Event Phase 3"),
(@ENTRY,0,12,13,2,0,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Stonevault Seer - Between 0-15% Health - Enable Combat Movement"),
(@ENTRY,0,13,0,61,0,100,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Stonevault Seer - Between 0-15% Health - Flee For Assist");


-- Shadowfang Wolfguard SAI
SET @ENTRY := 3854;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,1000,1000,0,0,11,7107,0,0,0,0,0,1,0,0,0,0,0,0,0,"Shadowfang Wolfguard - Out of Combat - Cast 'Summon Wolfguard Worg'");
