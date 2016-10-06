SET @BOT_START = 90000;
SET @BOT_END   = 91000;

UPDATE `creature_template` SET `subname` = '전사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 1;
UPDATE `creature_template` SET `subname` = '성기사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 2;
UPDATE `creature_template` SET `subname` = '사냥꾼 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 3;
UPDATE `creature_template` SET `subname` = '도적 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 4;
UPDATE `creature_template` SET `subname` = '사제 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 5;
UPDATE `creature_template` SET `subname` = '죽음의 기사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 6;
UPDATE `creature_template` SET `subname` = '주술사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 7;
UPDATE `creature_template` SET `subname` = '마법사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 8;
UPDATE `creature_template` SET `subname` = '흑마법사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 9;
UPDATE `creature_template` SET `subname` = '수도사 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 10;
UPDATE `creature_template` SET `subname` = '드루이드 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 11;
UPDATE `creature_template` SET `subname` = '검신 봇' WHERE (`entry` BETWEEN @BOT_START AND @BOT_END) AND `trainer_class` = 12;


-- I live only to serve the master.
UPDATE `npc_text` SET `text0_0` = '마스터를 따르는게 저의 삶입니다.' WHERE `ID` = @BOT_START+0001;
-- You need something?
UPDATE `npc_text` SET `text0_0` = '필요한게 있습니까?' WHERE `ID` = @BOT_START+0002;
-- Mortals... usually I kill wretches like you at sight
UPDATE `npc_text` SET `text0_0` = '필멸자.. 나는 눈앞의 당신처럼 가엾은 이들을 죽입니다.' WHERE `ID` = @BOT_START+0003;
