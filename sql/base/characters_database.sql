/*
Navicat MySQL Data Transfer

Source Server         : JadeCore_5.x.x
Source Server Version : 50624
Source Host           : 127.0.0.1:3306
Source Database       : characters

Target Server Type    : MYSQL
Target Server Version : 50624
File Encoding         : 65001

Date: 2016-09-26 18:33:14
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `account_achievement`
-- ----------------------------
DROP TABLE IF EXISTS `account_achievement`;
CREATE TABLE `account_achievement` (
`account`  int(10) UNSIGNED NOT NULL ,
`first_guid`  int(10) UNSIGNED NOT NULL ,
`achievement`  smallint(5) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL ,
PRIMARY KEY (`account`, `achievement`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of account_achievement
-- ----------------------------
BEGIN;
INSERT INTO `account_achievement` VALUES ('1', '2', '5544', '1440189666'), ('1', '3', '5676', '1440190568'), ('2', '6', '6', '1462212857'), ('2', '10', '7', '1462385114'), ('2', '10', '8', '1462385207'), ('2', '6', '503', '1462211595'), ('2', '15', '504', '1464979641'), ('2', '12', '545', '1462787615'), ('2', '15', '621', '1463676038'), ('2', '6', '5544', '1462202892'), ('2', '7', '5676', '1462378228'), ('2', '12', '5677', '1462785416'), ('2', '6', '5678', '1462204621'), ('2', '12', '5679', '1462786137'), ('2', '12', '5680', '1463468381'), ('2', '6', '5681', '1462204365'), ('2', '6', '5682', '1462204615'), ('2', '12', '5683', '1462786124'), ('2', '6', '5684', '1462207868'), ('2', '6', '5685', '1462209406'), ('2', '6', '5686', '1462209936'), ('2', '6', '5687', '1462211484'), ('2', '6', '5688', '1462212857'), ('7', '23', '6', '1472304293'), ('7', '23', '7', '1472304293'), ('7', '23', '8', '1472304293'), ('7', '23', '9', '1472304293'), ('7', '23', '889', '1472304293'), ('7', '23', '891', '1472304293'), ('11', '19', '6', '1469039618'), ('11', '19', '7', '1469621354'), ('11', '19', '131', '1471710092'), ('11', '19', '503', '1469044544'), ('11', '19', '504', '1469728611'), ('11', '19', '522', '1469202695'), ('11', '19', '630', '1469620036'), ('11', '19', '891', '1469625213'), ('11', '19', '4956', '1469631184'), ('11', '19', '5544', '1468777516'), ('11', '20', '5676', '1468782724'), ('11', '17', '5677', '1468775645'), ('11', '20', '5678', '1468785762'), ('11', '19', '5679', '1468778043'), ('11', '19', '5680', '1468778054'), ('11', '17', '5681', '1468775630'), ('11', '18', '5682', '1468777299'), ('11', '19', '5683', '1468777835'), ('11', '19', '5684', '1468778053'), ('11', '19', '5685', '1468779078'), ('11', '19', '5686', '1468952946'), ('11', '19', '5687', '1468954668'), ('11', '19', '5688', '1469040140');
COMMIT;

-- ----------------------------
-- Table structure for `account_achievement_progress`
-- ----------------------------
DROP TABLE IF EXISTS `account_achievement_progress`;
CREATE TABLE `account_achievement_progress` (
`account`  int(10) UNSIGNED NOT NULL ,
`criteria`  smallint(5) UNSIGNED NOT NULL ,
`counter`  int(10) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL ,
PRIMARY KEY (`account`, `criteria`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of account_achievement_progress
-- ----------------------------
BEGIN;
INSERT INTO `account_achievement_progress` VALUES ('1', '15688', '13', '1440190552'), ('2', '15688', '8710', '1466537165'), ('7', '7550', '2', '1472304293'), ('7', '7551', '2', '1472304293'), ('7', '7552', '2', '1472304293'), ('7', '9224', '2', '1472304293'), ('7', '15688', '1170', '1472307870'), ('11', '3941', '1', '1469620036'), ('11', '7550', '2', '1472242432'), ('11', '7551', '2', '1472242432'), ('11', '7552', '2', '1472242432'), ('11', '9224', '2', '1472242432'), ('11', '15688', '159620', '1472242166');
COMMIT;

-- ----------------------------
-- Table structure for `account_data`
-- ----------------------------
DROP TABLE IF EXISTS `account_data`;
CREATE TABLE `account_data` (
`accountId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Account Identifier' ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`data`  blob NOT NULL ,
PRIMARY KEY (`accountId`, `type`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of account_data
-- ----------------------------
BEGIN;
INSERT INTO `account_data` VALUES ('1', '0', '1440190442', 0x53455420666C61676765645475746F7269616C732022760123232423232523232D23232723232823232E23234523233823233C23235A220D0A5345542063616D65726144697374616E63654D6178466163746F72202231220D0A), ('2', '0', '1463468381', 0x53455420696E7465726163744F6E4C656674436C69636B202230220D0A53455420666C61676765645475746F7269616C732022760123232423232523232D23234523233023234B23233823232823235B23232923233B23232E23233F23232B23232C23233A23234023233C23232723235A23235D23233923234923234423233323234F23236023235E23234A23235623235923234123234223234623233D23234E232343220D0A534554206C6F636B416374696F6E42617273202230220D0A53455420656E61626C65436F6D62617454657874202230220D0A5345542063616D65726144697374616E63654D6178466163746F72202231220D0A5345542074616C656E744672616D6553686F776E202231220D0A), ('2', '4', '1462384851', 0x56455220332030303030303030303030303030303031202264656C2220225350454C4C5F464952455F5457494C4947485446495245220D0A2E6E70632064656C0D0A454E440D0A5645522033203030303030303030303030303030303220226C6F6C2220224162696C6974795F43726561747572655F4375727365645F3033220D0A2F6C6F6C0D0A454E440D0A), ('2', '2', '1462384850', 0x42494E44494E474D4F444520300D0A62696E642052204D554C5449414354494F4E42415231425554544F4E340D0A62696E642046204D554C5449414354494F4E42415231425554544F4E330D0A), ('11', '0', '1471634140', 0x53455420696E7465726163744F6E4C656674436C69636B202230220D0A53455420666C61676765645475746F7269616C732022760123232423232523232D23234523233023234B23233823232823235B23232923233B23232E23233F23232B23232C23233A23234023233C23232723235A23235D23233923234923234423233323234F23236023235E23234A23235623235923234123234223234623233D23234E23234323234C220D0A534554206C6F636B416374696F6E42617273202230220D0A53455420656E61626C65436F6D62617454657874202230220D0A5345542063616D65726144697374616E63654D6178466163746F72202231220D0A53455420736572766963655479706546696C746572202232220D0A5345542074616C656E744672616D6553686F776E202231220D0A), ('7', '0', '1472307504', 0x53455420666C61676765645475746F7269616C732022760123232423233A23233923234923234423234A23235623234B23236023235B23234123234223232923232823235923232B23232C23233B220D0A5345542063616D65726144697374616E63654D6178466163746F72202231220D0A5345542074616C656E744672616D6553686F776E202231220D0A);
COMMIT;

-- ----------------------------
-- Table structure for `account_instance_times`
-- ----------------------------
DROP TABLE IF EXISTS `account_instance_times`;
CREATE TABLE `account_instance_times` (
`accountId`  int(10) UNSIGNED NOT NULL ,
`instanceId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`releaseTime`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`accountId`, `instanceId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of account_instance_times
-- ----------------------------
BEGIN;
INSERT INTO `account_instance_times` VALUES ('2', '1', '1463507827'), ('7', '1', '1472308933'), ('7', '2', '1472310164'), ('11', '1', '1469631491');
COMMIT;

-- ----------------------------
-- Table structure for `account_tutorial`
-- ----------------------------
DROP TABLE IF EXISTS `account_tutorial`;
CREATE TABLE `account_tutorial` (
`accountId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Account Identifier' ,
`tut0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut4`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut5`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut6`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`tut7`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`accountId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of account_tutorial
-- ----------------------------
BEGIN;
INSERT INTO `account_tutorial` VALUES ('1', '17827355', '4194306', '0', '0', '0', '0', '0', '0'), ('2', '4226848699', '384044263', '0', '0', '0', '0', '0', '0'), ('7', '1625293233', '279183585', '0', '0', '0', '0', '0', '0'), ('11', '4226848699', '384044519', '0', '0', '0', '0', '0', '0'), ('12', '4194305', '0', '0', '0', '0', '0', '0', '0');
COMMIT;

-- ----------------------------
-- Table structure for `addons`
-- ----------------------------
DROP TABLE IF EXISTS `addons`;
CREATE TABLE `addons` (
`name`  varchar(120) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`crc`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`name`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Addons'

;

-- ----------------------------
-- Records of addons
-- ----------------------------
BEGIN;
INSERT INTO `addons` VALUES ('Blizzard_AchievementUI', '1276933997'), ('Blizzard_ArchaeologyUI', '1276933997'), ('Blizzard_ArenaUI', '1276933997'), ('Blizzard_AuctionUI', '1276933997'), ('Blizzard_AuthChallengeUI', '1276933997'), ('Blizzard_BarbershopUI', '1276933997'), ('Blizzard_BattlefieldMinimap', '1276933997'), ('Blizzard_BindingUI', '1276933997'), ('Blizzard_BlackMarketUI', '1276933997'), ('Blizzard_Calendar', '1276933997'), ('Blizzard_ChallengesUI', '1276933997'), ('Blizzard_ClientSavedVariables', '1276933997'), ('Blizzard_CombatLog', '1276933997'), ('Blizzard_CombatText', '1276933997'), ('Blizzard_CompactRaidFrames', '1276933997'), ('Blizzard_CUFProfiles', '1276933997'), ('Blizzard_DebugTools', '1276933997'), ('Blizzard_EncounterJournal', '1276933997'), ('Blizzard_GlyphUI', '1276933997'), ('Blizzard_GMChatUI', '1276933997'), ('Blizzard_GMSurveyUI', '1276933997'), ('Blizzard_GuildBankUI', '1276933997'), ('Blizzard_GuildControlUI', '1276933997'), ('Blizzard_GuildUI', '1276933997'), ('Blizzard_InspectUI', '1276933997'), ('Blizzard_ItemAlterationUI', '1276933997'), ('Blizzard_ItemSocketingUI', '1276933997'), ('Blizzard_ItemUpgradeUI', '1276933997'), ('Blizzard_LookingForGuildUI', '1276933997'), ('Blizzard_MacroUI', '1276933997'), ('Blizzard_MovePad', '1276933997'), ('Blizzard_PetBattleUI', '1276933997'), ('Blizzard_PetJournal', '1276933997'), ('Blizzard_PVPUI', '1276933997'), ('Blizzard_QuestChoice', '1276933997'), ('Blizzard_RaidUI', '1276933997'), ('Blizzard_ReforgingUI', '1276933997'), ('Blizzard_StoreUI', '1276933997'), ('Blizzard_TalentUI', '1276933997'), ('Blizzard_TimeManager', '1276933997'), ('Blizzard_TokenUI', '1276933997'), ('Blizzard_TradeSkillUI', '1276933997'), ('Blizzard_TrainerUI', '1276933997'), ('Blizzard_VoidStorageUI', '1276933997');
COMMIT;

-- ----------------------------
-- Table structure for `arena_team`
-- ----------------------------
DROP TABLE IF EXISTS `arena_team`;
CREATE TABLE `arena_team` (
`arenaTeamId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`name`  varchar(24) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`captainGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`rating`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonWins`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`weekGames`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`weekWins`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`rank`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`backgroundColor`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`emblemStyle`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`emblemColor`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`borderStyle`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`borderColor`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`arenaTeamId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of arena_team
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `arena_team_member`
-- ----------------------------
DROP TABLE IF EXISTS `arena_team_member`;
CREATE TABLE `arena_team_member` (
`arenaTeamId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`weekGames`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`weekWins`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonWins`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`personalRating`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`arenaTeamId`, `guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of arena_team_member
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `auctionhouse`
-- ----------------------------
DROP TABLE IF EXISTS `auctionhouse`;
CREATE TABLE `auctionhouse` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`auctioneerguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`itemguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`itemowner`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`buyoutprice`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`buyguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`lastbid`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`startbid`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`deposit`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of auctionhouse
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `autobroadcast`
-- ----------------------------
DROP TABLE IF EXISTS `autobroadcast`;
CREATE TABLE `autobroadcast` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`text`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
AUTO_INCREMENT=5

;

-- ----------------------------
-- Records of autobroadcast
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `blackmarket`
-- ----------------------------
DROP TABLE IF EXISTS `blackmarket`;
CREATE TABLE `blackmarket` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Identifier' ,
`templateId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Reference to world.blackmarket_template' ,
`startTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Start time of the bid' ,
`bid`  bigint(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Amount of the actual bid' ,
`bidder`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Player guid (highest bid)' ,
`bidderCount`  int(10) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of blackmarket
-- ----------------------------
BEGIN;
INSERT INTO `blackmarket` VALUES ('1', '36', '1472239745', '100000000', '0', '0'), ('2', '42', '1472239756', '100000000', '0', '0'), ('3', '47', '1472239738', '100000000', '0', '0'), ('4', '41', '1472239710', '100000000', '0', '0'), ('5', '35', '1472239825', '100000000', '0', '0'), ('6', '30', '1472239725', '100000000', '0', '0'), ('7', '38', '1472239814', '100000000', '0', '0'), ('8', '44', '1472239799', '100000000', '0', '0'), ('9', '27', '1472239767', '100000000', '0', '0'), ('10', '56', '1472239781', '100000000', '0', '0');
COMMIT;

-- ----------------------------
-- Table structure for `bugreport`
-- ----------------------------
DROP TABLE IF EXISTS `bugreport`;
CREATE TABLE `bugreport` (
`id`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Identifier' ,
`type`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`content`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Debug System'
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of bugreport
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `channels`
-- ----------------------------
DROP TABLE IF EXISTS `channels`;
CREATE TABLE `channels` (
`name`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`team`  int(10) UNSIGNED NOT NULL ,
`announce`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`ownership`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`password`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,
`bannedList`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`lastUsed`  int(10) UNSIGNED NOT NULL ,
PRIMARY KEY (`name`, `team`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Channel System'

;

-- ----------------------------
-- Records of channels
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_account_data`
-- ----------------------------
DROP TABLE IF EXISTS `character_account_data`;
CREATE TABLE `character_account_data` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`data`  blob NOT NULL ,
PRIMARY KEY (`guid`, `type`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_account_data
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_achievement`
-- ----------------------------
DROP TABLE IF EXISTS `character_achievement`;
CREATE TABLE `character_achievement` (
`guid`  int(10) UNSIGNED NOT NULL ,
`achievement`  smallint(5) UNSIGNED NOT NULL ,
PRIMARY KEY (`guid`, `achievement`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_achievement
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_achievement_count`
-- ----------------------------
DROP TABLE IF EXISTS `character_achievement_count`;
CREATE TABLE `character_achievement_count` (
`guid`  bigint(11) NOT NULL DEFAULT 0 ,
`count`  int(11) NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_achievement_count
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_achievement_progress`
-- ----------------------------
DROP TABLE IF EXISTS `character_achievement_progress`;
CREATE TABLE `character_achievement_progress` (
`guid`  int(10) UNSIGNED NOT NULL ,
`criteria`  smallint(5) UNSIGNED NOT NULL ,
`counter`  int(10) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `criteria`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_achievement_progress
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_action`
-- ----------------------------
DROP TABLE IF EXISTS `character_action`;
CREATE TABLE `character_action` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`spec`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`button`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`action`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spec`, `button`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_action
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_archaeology`
-- ----------------------------
DROP TABLE IF EXISTS `character_archaeology`;
CREATE TABLE `character_archaeology` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`sites0`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`sites1`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`sites2`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`sites3`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`counts`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`projects`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`completed`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_archaeology
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_arena_data`
-- ----------------------------
DROP TABLE IF EXISTS `character_arena_data`;
CREATE TABLE `character_arena_data` (
`guid`  int(11) NOT NULL ,
`rating0`  int(10) NULL DEFAULT 0 ,
`bestRatingOfWeek0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bestRatingOfSeason0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`matchMakerRating0`  int(10) NULL DEFAULT 0 ,
`weekGames0`  int(10) NULL DEFAULT 0 ,
`weekWins0`  int(10) NULL DEFAULT 0 ,
`prevWeekWins0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames0`  int(10) NULL DEFAULT 0 ,
`seasonWins0`  int(10) NULL DEFAULT 0 ,
`rating1`  int(10) NULL DEFAULT 0 ,
`bestRatingOfWeek1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bestRatingOfSeason1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`matchMakerRating1`  int(10) NULL DEFAULT 0 ,
`weekGames1`  int(10) NULL DEFAULT 0 ,
`weekWins1`  int(10) NULL DEFAULT 0 ,
`prevWeekWins1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames1`  int(10) NULL DEFAULT 0 ,
`seasonWins1`  int(10) NULL DEFAULT 0 ,
`rating2`  int(10) NULL DEFAULT 0 ,
`bestRatingOfWeek2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bestRatingOfSeason2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`matchMakerRating2`  int(10) NULL DEFAULT 0 ,
`weekGames2`  int(10) NULL DEFAULT 0 ,
`weekWins2`  int(10) NULL DEFAULT 0 ,
`prevWeekWins2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames2`  int(10) NULL DEFAULT 0 ,
`seasonWins2`  int(10) NULL DEFAULT 0 ,
`rating3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bestRatingOfWeek3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bestRatingOfSeason3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`matchMakerRating3`  int(10) NOT NULL DEFAULT 1500 ,
`weekGames3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`weekWins3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`prevWeekWins3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonGames3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`seasonWins3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_arena_data
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_arena_stats`
-- ----------------------------
DROP TABLE IF EXISTS `character_arena_stats`;
CREATE TABLE `character_arena_stats` (
`guid`  int(10) NOT NULL ,
`slot`  tinyint(3) NOT NULL ,
`matchMakerRating`  smallint(5) NOT NULL ,
PRIMARY KEY (`guid`, `slot`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_arena_stats
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_aura`
-- ----------------------------
DROP TABLE IF EXISTS `character_aura`;
CREATE TABLE `character_aura` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`caster_guid`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Full Global Unique Identifier' ,
`item_guid`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`effect_mask`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`recalculate_mask`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`stackcount`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`maxduration`  int(11) NOT NULL DEFAULT 0 ,
`remaintime`  int(11) NOT NULL DEFAULT 0 ,
`remaincharges`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `caster_guid`, `item_guid`, `spell`, `effect_mask`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_aura
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_aura_effect`
-- ----------------------------
DROP TABLE IF EXISTS `character_aura_effect`;
CREATE TABLE `character_aura_effect` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`effect`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`baseamount`  int(11) NOT NULL DEFAULT 0 ,
`amount`  int(11) NOT NULL ,
PRIMARY KEY (`guid`, `slot`, `effect`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of character_aura_effect
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_banned`
-- ----------------------------
DROP TABLE IF EXISTS `character_banned`;
CREATE TABLE `character_banned` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`bandate`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`unbandate`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bannedby`  varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`banreason`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`active`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
PRIMARY KEY (`guid`, `bandate`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Ban List'

;

-- ----------------------------
-- Records of character_banned
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_battleground_data`
-- ----------------------------
DROP TABLE IF EXISTS `character_battleground_data`;
CREATE TABLE `character_battleground_data` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`instanceId`  int(10) UNSIGNED NOT NULL COMMENT 'Instance Identifier' ,
`team`  smallint(5) UNSIGNED NOT NULL ,
`joinX`  float NOT NULL DEFAULT 0 ,
`joinY`  float NOT NULL DEFAULT 0 ,
`joinZ`  float NOT NULL DEFAULT 0 ,
`joinO`  float NOT NULL DEFAULT 0 ,
`joinMapId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Map Identifier' ,
`taxiStart`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxiEnd`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mountSpell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_battleground_data
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_battleground_random`
-- ----------------------------
DROP TABLE IF EXISTS `character_battleground_random`;
CREATE TABLE `character_battleground_random` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_battleground_random
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_currency`
-- ----------------------------
DROP TABLE IF EXISTS `character_currency`;
CREATE TABLE `character_currency` (
`guid`  int(11) UNSIGNED NOT NULL ,
`currency`  smallint(5) UNSIGNED NOT NULL ,
`total_count`  int(11) UNSIGNED NOT NULL ,
`week_count`  int(11) UNSIGNED NOT NULL ,
`season_total`  int(11) NULL DEFAULT 0 ,
`flags`  int(10) UNSIGNED NULL DEFAULT NULL ,
`weekCap`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`needResetCap`  tinyint(1) UNSIGNED NOT NULL DEFAULT 1 ,
PRIMARY KEY (`guid`, `currency`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_currency
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_declinedname`
-- ----------------------------
DROP TABLE IF EXISTS `character_declinedname`;
CREATE TABLE `character_declinedname` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`genitive`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`dative`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`accusative`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`instrumental`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`prepositional`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_declinedname
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_equipmentsets`
-- ----------------------------
DROP TABLE IF EXISTS `character_equipmentsets`;
CREATE TABLE `character_equipmentsets` (
`guid`  int(10) NOT NULL DEFAULT 0 ,
`setguid`  bigint(20) NOT NULL AUTO_INCREMENT ,
`setindex`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`name`  varchar(31) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`iconname`  varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`ignore_mask`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item0`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item1`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item2`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item3`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item4`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item5`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item6`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item7`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item8`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item9`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item10`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item11`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item12`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item13`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item14`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item15`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item16`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item17`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`item18`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`setguid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of character_equipmentsets
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_gifts`
-- ----------------------------
DROP TABLE IF EXISTS `character_gifts`;
CREATE TABLE `character_gifts` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`item_guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entry`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`flags`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`item_guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_gifts
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_glyphs`
-- ----------------------------
DROP TABLE IF EXISTS `character_glyphs`;
CREATE TABLE `character_glyphs` (
`guid`  int(10) UNSIGNED NOT NULL ,
`spec`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`glyph1`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`glyph2`  smallint(5) UNSIGNED NULL DEFAULT 0 ,
`glyph3`  smallint(5) UNSIGNED NULL DEFAULT 0 ,
`glyph4`  smallint(5) UNSIGNED NULL DEFAULT 0 ,
`glyph5`  smallint(5) UNSIGNED NULL DEFAULT 0 ,
`glyph6`  smallint(5) UNSIGNED NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spec`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_glyphs
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_homebind`
-- ----------------------------
DROP TABLE IF EXISTS `character_homebind`;
CREATE TABLE `character_homebind` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`mapId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Map Identifier' ,
`zoneId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Zone Identifier' ,
`posX`  float NOT NULL DEFAULT 0 ,
`posY`  float NOT NULL DEFAULT 0 ,
`posZ`  float NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_homebind
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_instance`
-- ----------------------------
DROP TABLE IF EXISTS `character_instance`;
CREATE TABLE `character_instance` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instance`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`permanent`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `instance`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_instance
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_inventory`
-- ----------------------------
DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`bag`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`item`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Item Global Unique Identifier' ,
PRIMARY KEY (`item`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_inventory
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_pet`
-- ----------------------------
DROP TABLE IF EXISTS `character_pet`;
CREATE TABLE `character_pet` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`entry`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`owner`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`modelid`  int(10) UNSIGNED NULL DEFAULT 0 ,
`CreatedBySpell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`PetType`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`level`  smallint(5) UNSIGNED NOT NULL DEFAULT 1 ,
`exp`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`Reactstate`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`name`  varchar(21) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'Pet' ,
`renamed`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`curhealth`  int(10) UNSIGNED NOT NULL DEFAULT 1 ,
`curmana`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`savetime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`abdata`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`specialization`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Pet System'

;

-- ----------------------------
-- Records of character_pet
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_pet_declinedname`
-- ----------------------------
DROP TABLE IF EXISTS `character_pet_declinedname`;
CREATE TABLE `character_pet_declinedname` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`owner`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`genitive`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`dative`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`accusative`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`instrumental`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`prepositional`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_pet_declinedname
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus`;
CREATE TABLE `character_queststatus` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
`status`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`explored`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`timer`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mobcount1`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`mobcount2`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`mobcount3`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`mobcount4`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`itemcount1`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`itemcount2`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`itemcount3`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`itemcount4`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`playercount`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus_daily`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus_daily`;
CREATE TABLE `character_queststatus_daily` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus_daily
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus_monthly`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus_monthly`;
CREATE TABLE `character_queststatus_monthly` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus_monthly
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus_rewarded`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus_rewarded`;
CREATE TABLE `character_queststatus_rewarded` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus_rewarded
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus_seasonal`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus_seasonal`;
CREATE TABLE `character_queststatus_seasonal` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
`event`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Event Identifier' ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus_seasonal
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_queststatus_weekly`
-- ----------------------------
DROP TABLE IF EXISTS `character_queststatus_weekly`;
CREATE TABLE `character_queststatus_weekly` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`quest`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Quest Identifier' ,
PRIMARY KEY (`guid`, `quest`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_queststatus_weekly
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_rates`
-- ----------------------------
DROP TABLE IF EXISTS `character_rates`;
CREATE TABLE `character_rates` (
`guid`  bigint(20) NOT NULL DEFAULT 0 ,
`rate`  tinyint(2) NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of character_rates
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_reputation`
-- ----------------------------
DROP TABLE IF EXISTS `character_reputation`;
CREATE TABLE `character_reputation` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`faction`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`standing`  int(11) NOT NULL DEFAULT 0 ,
`flags`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `faction`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_reputation
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_skills`
-- ----------------------------
DROP TABLE IF EXISTS `character_skills`;
CREATE TABLE `character_skills` (
`guid`  int(10) UNSIGNED NOT NULL COMMENT 'Global Unique Identifier' ,
`skill`  smallint(5) UNSIGNED NOT NULL ,
`value`  smallint(5) UNSIGNED NOT NULL ,
`max`  smallint(5) UNSIGNED NOT NULL ,
PRIMARY KEY (`guid`, `skill`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_skills
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_social`
-- ----------------------------
DROP TABLE IF EXISTS `character_social`;
CREATE TABLE `character_social` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Character Global Unique Identifier' ,
`friend`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Friend Global Unique Identifier' ,
`flags`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Friend Flags' ,
`note`  varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT 'Friend Note' ,
PRIMARY KEY (`guid`, `friend`, `flags`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_social
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_spell`
-- ----------------------------
DROP TABLE IF EXISTS `character_spell`;
CREATE TABLE `character_spell` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Spell Identifier' ,
`active`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`disabled`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of character_spell
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_spell_cooldown`
-- ----------------------------
DROP TABLE IF EXISTS `character_spell_cooldown`;
CREATE TABLE `character_spell_cooldown` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier, Low part' ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Spell Identifier' ,
`item`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Item Identifier' ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_spell_cooldown
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_stats`
-- ----------------------------
DROP TABLE IF EXISTS `character_stats`;
CREATE TABLE `character_stats` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier, Low part' ,
`maxhealth`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxpower1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxpower2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxpower3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxpower4`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxpower5`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`strength`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`agility`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`stamina`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`intellect`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`spirit`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`armor`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resHoly`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resFire`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resNature`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resFrost`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resShadow`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resArcane`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`blockPct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`dodgePct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`parryPct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`critPct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`rangedCritPct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`spellCritPct`  float UNSIGNED NOT NULL DEFAULT 0 ,
`attackPower`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`rangedAttackPower`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`spellPower`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resilience`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_stats
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_talent`
-- ----------------------------
DROP TABLE IF EXISTS `character_talent`;
CREATE TABLE `character_talent` (
`guid`  int(10) UNSIGNED NOT NULL ,
`spell`  mediumint(8) UNSIGNED NOT NULL ,
`spec`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`, `spec`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_talent
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `character_void_storage`
-- ----------------------------
DROP TABLE IF EXISTS `character_void_storage`;
CREATE TABLE `character_void_storage` (
`itemId`  bigint(20) UNSIGNED NOT NULL ,
`playerGuid`  int(10) UNSIGNED NOT NULL ,
`itemEntry`  mediumint(8) UNSIGNED NOT NULL ,
`slot`  tinyint(3) UNSIGNED NOT NULL ,
`creatorGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`randomProperty`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`suffixFactor`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`itemId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of character_void_storage
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `characters`
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`account`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Account Identifier' ,
`name`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`race`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`class`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`gender`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`level`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`xp`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`money`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`playerBytes`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`playerBytes2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`playerFlags`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`position_x`  float NOT NULL DEFAULT 0 ,
`position_y`  float NOT NULL DEFAULT 0 ,
`position_z`  float NOT NULL DEFAULT 0 ,
`map`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Map Identifier' ,
`instance_id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instance_mode_mask`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`orientation`  float NOT NULL DEFAULT 0 ,
`taximask`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`online`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`cinematic`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`totaltime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`leveltime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`logout_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`is_logout_resting`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`rest_bonus`  float NOT NULL DEFAULT 0 ,
`resettalents_cost`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resettalents_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`resetspecialization_cost`  int(10) NOT NULL DEFAULT 0 ,
`resetspecialization_time`  int(10) NOT NULL DEFAULT 0 ,
`talentTree`  varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '0 0' ,
`trans_x`  float NOT NULL DEFAULT 0 ,
`trans_y`  float NOT NULL DEFAULT 0 ,
`trans_z`  float NOT NULL DEFAULT 0 ,
`trans_o`  float NOT NULL DEFAULT 0 ,
`transguid`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`extra_flags`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`stable_slots`  tinyint(3) UNSIGNED NULL DEFAULT NULL ,
`at_login`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`zone`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`death_expire_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`taxi_path`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`totalKills`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`todayKills`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`yesterdayKills`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`chosenTitle`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`watchedFaction`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`drunk`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`health`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`power1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`power2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`power3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`power4`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`power5`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`latency`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`speccount`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`activespec`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`specialization1`  int(11) NOT NULL ,
`specialization2`  int(11) NOT NULL ,
`exploredZones`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`equipmentCache`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`knownTitles`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`actionBars`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`currentpetslot`  tinyint(3) UNSIGNED NULL DEFAULT NULL ,
`petslotused`  tinyint(3) UNSIGNED NULL DEFAULT NULL ,
`grantableLevels`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`guildId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`deleteInfos_Account`  int(10) UNSIGNED NULL DEFAULT NULL ,
`deleteInfos_Name`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,
`deleteDate`  int(10) UNSIGNED NULL DEFAULT NULL ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'

;

-- ----------------------------
-- Records of characters
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `corpse`
-- ----------------------------
DROP TABLE IF EXISTS `corpse`;
CREATE TABLE `corpse` (
`corpseGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Character Global Unique Identifier' ,
`posX`  float NOT NULL DEFAULT 0 ,
`posY`  float NOT NULL DEFAULT 0 ,
`posZ`  float NOT NULL DEFAULT 0 ,
`orientation`  float NOT NULL DEFAULT 0 ,
`mapId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Map Identifier' ,
`phaseMask`  smallint(5) UNSIGNED NOT NULL DEFAULT 1 ,
`displayId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`itemCache`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`bytes1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bytes2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`flags`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`dynFlags`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`corpseType`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`instanceId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Instance Identifier' ,
PRIMARY KEY (`corpseGuid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Death System'

;

-- ----------------------------
-- Records of corpse
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `creature_respawn`
-- ----------------------------
DROP TABLE IF EXISTS `creature_respawn`;
CREATE TABLE `creature_respawn` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`respawnTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mapId`  smallint(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instanceId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Instance Identifier' ,
PRIMARY KEY (`guid`, `instanceId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Grid Loading System'

;

-- ----------------------------
-- Records of creature_respawn
-- ----------------------------
BEGIN;
INSERT INTO `creature_respawn` VALUES ('26230', '1472315253', '43', '2'), ('26239', '1472315261', '43', '2'), ('26252', '1472315279', '43', '2'), ('27360', '1472315356', '43', '2'), ('27364', '1472315336', '43', '2'), ('27367', '1472315367', '43', '2'), ('30956', '1463430647', '0', '0'), ('138345', '1462388147', '1', '0'), ('140885', '1463675921', '1', '0'), ('140889', '1463675938', '1', '0'), ('140893', '1463675958', '1', '0'), ('141025', '1463503462', '1', '0'), ('141026', '1463503441', '1', '0'), ('141027', '1463503482', '1', '0'), ('141032', '1463503529', '1', '0'), ('141036', '1463503509', '1', '0'), ('141129', '1463502896', '1', '0'), ('141474', '1463675016', '1', '0'), ('141475', '1463675049', '1', '0'), ('141536', '1463675325', '1', '0'), ('141538', '1463675299', '1', '0'), ('141539', '1463675296', '1', '0'), ('141669', '1463499917', '1', '0'), ('141670', '1463499950', '1', '0'), ('141811', '1463499479', '1', '0'), ('141816', '1463499427', '1', '0'), ('141827', '1463499455', '1', '0'), ('141830', '1463499392', '1', '0'), ('141883', '1463497189', '1', '0'), ('141947', '1463497267', '1', '0'), ('141950', '1463497168', '1', '0'), ('141987', '1463496439', '1', '0'), ('142017', '1463496067', '1', '0'), ('142842', '1463497255', '1', '0'), ('142843', '1463497280', '1', '0'), ('142972', '1468777345', '1', '0'), ('142987', '1468777363', '1', '0'), ('142988', '1468777376', '1', '0'), ('142989', '1468777417', '1', '0'), ('142996', '1468777388', '1', '0'), ('143116', '1463502079', '1', '0'), ('143117', '1463502070', '1', '0'), ('143119', '1463502108', '1', '0'), ('143120', '1463502126', '1', '0'), ('143159', '1468777400', '1', '0'), ('143190', '1463497260', '1', '0'), ('143196', '1463496111', '1', '0'), ('143197', '1463496121', '1', '0'), ('143198', '1463496115', '1', '0'), ('143199', '1463497271', '1', '0'), ('143269', '1463502098', '1', '0'), ('143271', '1463502020', '1', '0'), ('143273', '1463502011', '1', '0'), ('143317', '1463501660', '1', '0'), ('143319', '1463501681', '1', '0'), ('143320', '1463501656', '1', '0'), ('143321', '1463501522', '1', '0'), ('147351', '1463675293', '1', '0'), ('149042', '1469603280', '1', '0'), ('149043', '1469603293', '1', '0'), ('149048', '1469603322', '1', '0'), ('149050', '1469603381', '1', '0'), ('149051', '1469603360', '1', '0'), ('149059', '1469603653', '1', '0'), ('149103', '1469603631', '1', '0'), ('149104', '1469603357', '1', '0'), ('149105', '1469603326', '1', '0'), ('149124', '1469603398', '1', '0'), ('162820', '1472242238', '0', '0'), ('162827', '1472242222', '0', '0'), ('162830', '1472242326', '0', '0'), ('162833', '1472242345', '0', '0'), ('163034', '1472240479', '0', '0'), ('163039', '1472240850', '0', '0'), ('163040', '1472240871', '0', '0'), ('163290', '1463677936', '1', '0'), ('163296', '1463778064', '1', '0'), ('163306', '1463677920', '1', '0'), ('163310', '1463677957', '1', '0'), ('163311', '1463677864', '1', '0'), ('163322', '1463677989', '1', '0'), ('163325', '1463677886', '1', '0'), ('163328', '1463678027', '1', '0'), ('163333', '1463678047', '1', '0'), ('163342', '1463678071', '1', '0'), ('163443', '1464885818', '1', '0'), ('163444', '1464885786', '1', '0'), ('163447', '1464885812', '1', '0'), ('163558', '1464709763', '1', '0'), ('163562', '1464709742', '1', '0'), ('163682', '1464886880', '1', '0'), ('163686', '1464886910', '1', '0'), ('163693', '1464886888', '1', '0'), ('163699', '1464886906', '1', '0'), ('163703', '1464886849', '1', '0'), ('163713', '1464886884', '1', '0'), ('163760', '1464886830', '1', '0'), ('163768', '1464886854', '1', '0'), ('163771', '1464886874', '1', '0'), ('163821', '1464887566', '1', '0');
INSERT INTO `creature_respawn` VALUES ('163823', '1464916494', '1', '0'), ('163941', '1464717523', '1', '0'), ('163975', '1464717416', '1', '0'), ('164016', '1464716388', '1', '0'), ('164017', '1464716319', '1', '0'), ('164018', '1464716379', '1', '0'), ('164020', '1464716297', '1', '0'), ('164258', '1464888417', '1', '0'), ('164318', '1464888007', '1', '0'), ('164779', '1466538284', '1', '0'), ('164784', '1466538265', '1', '0'), ('164788', '1466538313', '1', '0'), ('164807', '1466538235', '1', '0'), ('164836', '1466537287', '1', '0'), ('164838', '1466537342', '1', '0'), ('164840', '1466537314', '1', '0'), ('164849', '1466537271', '1', '0'), ('164868', '1466537229', '1', '0'), ('165209', '1464979700', '1', '0'), ('165210', '1464979692', '1', '0'), ('165234', '1464980707', '1', '0'), ('165307', '1464888282', '1', '0'), ('165427', '1464889345', '1', '0'), ('165464', '1464979851', '1', '0'), ('165468', '1464979800', '1', '0'), ('165495', '1464980940', '1', '0'), ('165496', '1464980969', '1', '0'), ('165497', '1464980960', '1', '0'), ('165504', '1464981029', '1', '0'), ('165521', '1464980676', '1', '0'), ('165525', '1464979756', '1', '0'), ('165526', '1464979744', '1', '0'), ('165532', '1464979777', '1', '0'), ('165594', '1464979839', '1', '0'), ('165595', '1464979810', '1', '0'), ('165599', '1464979847', '1', '0'), ('165604', '1464979810', '1', '0'), ('165607', '1464979632', '1', '0'), ('165622', '1464979661', '1', '0'), ('165623', '1464979644', '1', '0'), ('165625', '1464979633', '1', '0'), ('165626', '1464979690', '1', '0'), ('165627', '1464979708', '1', '0'), ('166565', '1463470013', '0', '0'), ('166687', '1463470446', '0', '0'), ('166688', '1463470443', '0', '0'), ('166742', '1463472891', '0', '0'), ('166743', '1463472986', '0', '0'), ('166744', '1463472949', '0', '0'), ('166746', '1463473009', '0', '0'), ('166748', '1468786064', '0', '0'), ('166803', '1463470357', '0', '0'), ('166812', '1463474653', '0', '0'), ('166837', '1463470244', '0', '0'), ('166845', '1463470281', '0', '0'), ('166846', '1463470232', '0', '0'), ('166849', '1463470266', '0', '0'), ('166850', '1463470357', '0', '0'), ('166851', '1463470374', '0', '0'), ('166860', '1463470398', '0', '0'), ('166861', '1463470414', '0', '0'), ('166863', '1463470328', '0', '0'), ('166875', '1463470380', '0', '0'), ('166876', '1463470405', '0', '0'), ('166878', '1463470386', '0', '0'), ('166880', '1463470430', '0', '0'), ('166886', '1463470422', '0', '0'), ('167033', '1463473787', '0', '0'), ('167034', '1463473768', '0', '0'), ('167039', '1463473830', '0', '0'), ('167042', '1463473814', '0', '0'), ('167050', '1463473876', '0', '0'), ('167155', '1463473952', '0', '0'), ('167159', '1463473933', '0', '0'), ('167160', '1463473932', '0', '0'), ('167252', '1463474612', '0', '0'), ('167307', '1463474581', '0', '0'), ('167313', '1463474655', '0', '0'), ('167321', '1463474652', '0', '0'), ('167335', '1463474504', '0', '0'), ('167347', '1463474438', '0', '0'), ('167349', '1463474421', '0', '0'), ('167350', '1463474400', '0', '0'), ('167351', '1463474464', '0', '0'), ('167603', '1463474742', '0', '0'), ('168093', '1463469687', '0', '0'), ('168095', '1463469735', '0', '0'), ('168099', '1463469696', '0', '0'), ('168110', '1463469665', '0', '0'), ('168112', '1463469714', '0', '0'), ('168124', '1463469589', '0', '0'), ('168129', '1463469607', '0', '0'), ('168136', '1463469610', '0', '0'), ('168251', '1468786140', '0', '0'), ('168284', '1468786032', '0', '0'), ('168286', '1468786036', '0', '0'), ('168287', '1468786039', '0', '0'), ('168364', '1468786039', '0', '0'), ('168367', '1468786102', '0', '0'), ('168368', '1468786086', '0', '0');
INSERT INTO `creature_respawn` VALUES ('168381', '1468786077', '0', '0'), ('168388', '1468786003', '0', '0'), ('168389', '1468786018', '0', '0'), ('168390', '1468786025', '0', '0'), ('168391', '1468786059', '0', '0'), ('168392', '1468786050', '0', '0'), ('168407', '1462786456', '0', '0'), ('168411', '1462786489', '0', '0'), ('168412', '1462786465', '0', '0'), ('168464', '1468785918', '0', '0'), ('168465', '1468785825', '0', '0'), ('168469', '1468785848', '0', '0'), ('168471', '1468785905', '0', '0'), ('168472', '1468785896', '0', '0'), ('168479', '1468785887', '0', '0'), ('168482', '1468785863', '0', '0'), ('168489', '1468785875', '0', '0'), ('191922', '1463468718', '0', '0'), ('195715', '1469213755', '0', '0'), ('195745', '1469213709', '0', '0'), ('195747', '1469213693', '0', '0'), ('195750', '1469213724', '0', '0'), ('195759', '1469213798', '0', '0'), ('195782', '1469213810', '0', '0'), ('195880', '1469465199', '0', '0'), ('196322', '1469202316', '0', '0'), ('196340', '1469601507', '0', '0'), ('196492', '1469202356', '0', '0'), ('196494', '1469202340', '0', '0'), ('196497', '1469202328', '0', '0'), ('196503', '1469202304', '0', '0'), ('196603', '1469199921', '0', '0'), ('196657', '1469206543', '0', '0'), ('196665', '1469204490', '0', '0'), ('196693', '1469204508', '0', '0'), ('196695', '1469233157', '0', '0'), ('196698', '1469204564', '0', '0'), ('196825', '1469204605', '0', '0'), ('196826', '1469204610', '0', '0'), ('196827', '1469204583', '0', '0'), ('196828', '1469204630', '0', '0'), ('196829', '1469204618', '0', '0'), ('196830', '1469204633', '0', '0'), ('196839', '1469204679', '0', '0'), ('196840', '1469204684', '0', '0'), ('196841', '1469204708', '0', '0'), ('196842', '1469204718', '0', '0'), ('196843', '1469204663', '0', '0'), ('196844', '1469204647', '0', '0'), ('196928', '1471708955', '0', '0'), ('196932', '1471709422', '0', '0'), ('196933', '1471709405', '0', '0'), ('196969', '1471709361', '0', '0'), ('196986', '1471709380', '0', '0'), ('197047', '1471708647', '0', '0'), ('197124', '1471637356', '0', '0'), ('197126', '1471666180', '0', '0'), ('197144', '1471637425', '0', '0'), ('197145', '1471637406', '0', '0'), ('197146', '1471637385', '0', '0'), ('197168', '1471637462', '0', '0'), ('197169', '1471637441', '0', '0'), ('197602', '1471636184', '0', '0'), ('197692', '1471643134', '0', '0'), ('197729', '1471706489', '0', '0'), ('197730', '1471706438', '0', '0'), ('197746', '1471643130', '0', '0'), ('197748', '1471707398', '0', '0'), ('197753', '1471636152', '0', '0'), ('197790', '1471636444', '0', '0'), ('197797', '1471636554', '0', '0'), ('197804', '1471636569', '0', '0'), ('197808', '1471643087', '0', '0'), ('197812', '1471643215', '0', '0'), ('197813', '1471643209', '0', '0'), ('197828', '1471706506', '0', '0'), ('197829', '1471706533', '0', '0'), ('197831', '1471706521', '0', '0'), ('197832', '1471706567', '0', '0'), ('197834', '1471643248', '0', '0'), ('197839', '1471643222', '0', '0'), ('197850', '1471634411', '0', '0'), ('197917', '1471634394', '0', '0'), ('197919', '1471634380', '0', '0'), ('197927', '1471643067', '0', '0'), ('197929', '1471643063', '0', '0'), ('197930', '1471643062', '0', '0'), ('197931', '1471643043', '0', '0'), ('197933', '1471643018', '0', '0'), ('197935', '1471643017', '0', '0'), ('197947', '1471642976', '0', '0'), ('197948', '1471642989', '0', '0'), ('197957', '1471735875', '0', '0'), ('197971', '1471707256', '0', '0'), ('197972', '1471707270', '0', '0'), ('197983', '1471706562', '0', '0'), ('198029', '1469756901', '0', '0'), ('198082', '1469728821', '0', '0'), ('198124', '1469730502', '0', '0'), ('198127', '1469730477', '0', '0');
INSERT INTO `creature_respawn` VALUES ('198128', '1469730524', '0', '0'), ('198129', '1471639511', '0', '0'), ('198171', '1471706592', '0', '0'), ('198230', '1471639517', '0', '0'), ('198231', '1471639587', '0', '0'), ('198235', '1471639615', '0', '0'), ('198259', '1471634370', '0', '0'), ('198290', '1471634363', '0', '0'), ('198294', '1469728819', '0', '0'), ('198321', '1469728715', '0', '0'), ('198326', '1469728763', '0', '0'), ('198429', '1471634303', '0', '0'), ('198431', '1471634299', '0', '0'), ('198433', '1471634346', '0', '0'), ('198446', '1469730485', '0', '0'), ('198451', '1469730476', '0', '0'), ('198452', '1469730501', '0', '0'), ('198454', '1469730502', '0', '0'), ('198457', '1471639608', '0', '0'), ('198570', '1469730551', '0', '0'), ('198571', '1469730559', '0', '0'), ('198578', '1471634302', '0', '0'), ('198633', '1469728781', '0', '0'), ('198730', '1471634285', '0', '0'), ('198731', '1471634361', '0', '0'), ('198747', '1469730541', '0', '0'), ('198749', '1469730501', '0', '0'), ('198864', '1471634332', '0', '0'), ('198865', '1471634272', '0', '0'), ('198871', '1471634281', '0', '0'), ('198999', '1469730447', '0', '0'), ('199007', '1469729860', '0', '0'), ('199019', '1471710453', '0', '0'), ('199034', '1469729941', '0', '0'), ('199045', '1471634247', '0', '0'), ('199052', '1469632287', '0', '0'), ('199053', '1469632305', '0', '0'), ('199054', '1469632305', '0', '0'), ('199055', '1469632305', '0', '0'), ('199056', '1469632305', '0', '0'), ('199057', '1469632305', '0', '0'), ('199058', '1469632305', '0', '0'), ('199059', '1469632305', '0', '0'), ('199060', '1469632305', '0', '0'), ('199061', '1469632339', '0', '0'), ('199062', '1469632346', '0', '0'), ('199063', '1469632346', '0', '0'), ('199064', '1469632346', '0', '0'), ('199065', '1469632346', '0', '0'), ('199066', '1469632346', '0', '0'), ('199067', '1469632346', '0', '0'), ('199068', '1469632346', '0', '0'), ('199069', '1469632346', '0', '0'), ('199263', '1472304866', '0', '0'), ('203790', '1469204673', '0', '0'), ('203816', '1468778968', '0', '0'), ('203818', '1468778958', '0', '0'), ('203819', '1468778934', '0', '0'), ('203831', '1468778895', '0', '0'), ('203832', '1468778903', '0', '0'), ('203833', '1468778911', '0', '0'), ('203834', '1468778924', '0', '0'), ('203835', '1468779001', '0', '0'), ('203836', '1468778887', '0', '0'), ('203860', '1468778879', '0', '0'), ('203865', '1468778909', '0', '0'), ('204013', '1468952865', '0', '0'), ('204015', '1468952877', '0', '0'), ('204029', '1468952742', '0', '0'), ('204030', '1468952754', '0', '0'), ('204031', '1468952775', '0', '0'), ('204032', '1468952699', '0', '0'), ('204033', '1468952716', '0', '0'), ('204034', '1468952706', '0', '0'), ('204049', '1468952687', '0', '0'), ('204063', '1468778164', '0', '0'), ('204225', '1468952866', '0', '0'), ('204253', '1468952870', '0', '0'), ('204264', '1468952890', '0', '0'), ('204268', '1468952931', '0', '0'), ('204272', '1468952588', '0', '0'), ('204275', '1468952563', '0', '0'), ('204276', '1468981472', '0', '0'), ('204277', '1468952494', '0', '0'), ('204278', '1468952542', '0', '0'), ('204279', '1468952503', '0', '0'), ('204352', '1468952445', '0', '0'), ('204353', '1468952418', '0', '0'), ('204373', '1468952400', '0', '0'), ('204374', '1468952418', '0', '0'), ('204375', '1468952405', '0', '0'), ('204384', '1468952936', '0', '0'), ('204385', '1468952940', '0', '0'), ('204386', '1468952938', '0', '0'), ('204401', '1468952932', '0', '0'), ('204410', '1468952384', '0', '0'), ('204497', '1468953156', '0', '0'), ('204537', '1469042281', '0', '0'), ('204542', '1469042246', '0', '0'), ('204544', '1469042229', '0', '0');
INSERT INTO `creature_respawn` VALUES ('204545', '1469042217', '0', '0'), ('204601', '1469042122', '0', '0'), ('204602', '1469042170', '0', '0'), ('204604', '1469042200', '0', '0'), ('204605', '1469042183', '0', '0'), ('204609', '1469042157', '0', '0'), ('204630', '1469042058', '0', '0'), ('204633', '1469042100', '0', '0'), ('204634', '1469042090', '0', '0'), ('204647', '1468952304', '0', '0'), ('204663', '1468954769', '0', '0'), ('204695', '1468954710', '0', '0'), ('204696', '1468954696', '0', '0'), ('204697', '1468954748', '0', '0'), ('204750', '1468953468', '0', '0'), ('204768', '1468954666', '0', '0'), ('204769', '1468954682', '0', '0'), ('204770', '1468954655', '0', '0'), ('204771', '1468954756', '0', '0'), ('204790', '1472308238', '0', '0'), ('204889', '1469039944', '0', '0'), ('204894', '1469039974', '0', '0'), ('204895', '1469039956', '0', '0'), ('204910', '1469040008', '0', '0'), ('204912', '1469040001', '0', '0'), ('204913', '1469040033', '0', '0'), ('204930', '1472308219', '0', '0'), ('204934', '1472308246', '0', '0'), ('205230', '1469041295', '0', '0'), ('205234', '1469041301', '0', '0'), ('205235', '1469041301', '0', '0'), ('205260', '1472308122', '0', '0'), ('205269', '1472308140', '0', '0'), ('205282', '1472308215', '0', '0'), ('205502', '1469041288', '0', '0'), ('205503', '1469041265', '0', '0'), ('205504', '1469041257', '0', '0'), ('205506', '1469041290', '0', '0'), ('205507', '1469041290', '0', '0'), ('205522', '1469040071', '0', '0'), ('205803', '1468957694', '0', '0'), ('205813', '1469040920', '0', '0'), ('205814', '1469040871', '0', '0'), ('205819', '1469040879', '0', '0'), ('205820', '1469040758', '0', '0'), ('205821', '1469040792', '0', '0'), ('205822', '1469040868', '0', '0'), ('205827', '1469040813', '0', '0'), ('205828', '1469040817', '0', '0'), ('205829', '1469040813', '0', '0'), ('205832', '1469040815', '0', '0'), ('205833', '1469040826', '0', '0'), ('205834', '1469040825', '0', '0'), ('205836', '1469040910', '0', '0'), ('205846', '1468957709', '0', '0'), ('205943', '1469040794', '0', '0'), ('205944', '1469040837', '0', '0'), ('205945', '1469040795', '0', '0'), ('205999', '1469040869', '0', '0'), ('206009', '1469040795', '0', '0'), ('206010', '1469040867', '0', '0'), ('206020', '1469040882', '0', '0'), ('206078', '1469040894', '0', '0'), ('206277', '1469134060', '0', '0'), ('206280', '1469134072', '0', '0'), ('206285', '1469133993', '0', '0'), ('206360', '1469134026', '0', '0'), ('206361', '1469134011', '0', '0'), ('206366', '1469134032', '0', '0'), ('206369', '1469134055', '0', '0'), ('206375', '1469134103', '0', '0'), ('206376', '1469134105', '0', '0'), ('206377', '1469134095', '0', '0'), ('206395', '1469133768', '0', '0'), ('206396', '1469133759', '0', '0'), ('206419', '1469132461', '0', '0'), ('206420', '1469132428', '0', '0'), ('206461', '1469133756', '0', '0'), ('206463', '1469133694', '0', '0'), ('206464', '1469133644', '0', '0'), ('206465', '1469133687', '0', '0'), ('206483', '1469132492', '0', '0'), ('206484', '1469132507', '0', '0'), ('206530', '1469132546', '0', '0'), ('206531', '1469132566', '0', '0'), ('206532', '1469132527', '0', '0'), ('206540', '1469132584', '0', '0'), ('206548', '1469132626', '0', '0'), ('206579', '1469132604', '0', '0'), ('206599', '1469132619', '0', '0'), ('334750', '1462211763', '655', '0'), ('334804', '1462211711', '655', '0'), ('334805', '1462211739', '655', '0'), ('334806', '1462211820', '655', '0'), ('404751', '1472308495', '0', '0'), ('405848', '1472351318', '43', '2'), ('407465', '1464886835', '1', '0'), ('407467', '1464981252', '1', '0'), ('792255', '1472308251', '0', '0'), ('792257', '1472308233', '0', '0');
INSERT INTO `creature_respawn` VALUES ('792357', '1472308266', '0', '0'), ('792358', '1472308223', '0', '0'), ('792362', '1472308241', '0', '0'), ('792444', '1469208447', '0', '0'), ('792445', '1469208441', '0', '0'), ('792446', '1469208445', '0', '0'), ('792447', '1469208441', '0', '0'), ('792448', '1469208436', '0', '0'), ('792450', '1469207732', '0', '0'), ('792451', '1472308233', '0', '0'), ('792452', '1472308233', '0', '0'), ('792453', '1472308238', '0', '0'), ('792454', '1469208443', '0', '0'), ('792456', '1469208439', '0', '0'), ('792457', '1469208435', '0', '0'), ('792458', '1462380397', '0', '0'), ('792459', '1462380283', '0', '0'), ('792460', '1469208644', '0', '0'), ('792463', '1472308248', '0', '0'), ('792464', '1472308229', '0', '0'), ('792466', '1472308250', '0', '0'), ('792467', '1472308221', '0', '0'), ('792469', '1472308235', '0', '0'), ('792470', '1472308243', '0', '0'), ('792471', '1472308233', '0', '0'), ('792478', '1472308242', '0', '0'), ('792519', '1472308230', '0', '0'), ('792520', '1462380470', '0', '0'), ('792572', '1472308244', '0', '0'), ('792583', '1472308233', '0', '0'), ('792584', '1472308230', '0', '0'), ('792600', '1469208437', '0', '0'), ('792659', '1469208498', '0', '0'), ('792678', '1469208491', '0', '0'), ('792682', '1469208503', '0', '0'), ('792683', '1469208498', '0', '0'), ('792690', '1469208488', '0', '0'), ('792711', '1469208483', '0', '0'), ('792712', '1469208481', '0', '0'), ('940813', '1440190930', '860', '0'), ('940818', '1440190917', '860', '0'), ('940832', '1440190969', '860', '0'), ('940834', '1440191001', '860', '0'), ('967943', '1462209849', '654', '0'), ('967956', '1462216798', '654', '0'), ('967962', '1462216684', '654', '0'), ('967963', '1462216702', '654', '0'), ('967967', '1462216732', '654', '0'), ('967974', '1462212185', '654', '0'), ('967992', '1462209820', '654', '0'), ('967993', '1462209829', '654', '0'), ('967994', '1462209792', '654', '0'), ('967995', '1462209784', '654', '0'), ('968115', '1462217160', '654', '0'), ('968131', '1462217557', '654', '0'), ('968254', '1462212983', '654', '0'), ('968255', '1462212999', '654', '0'), ('968256', '1462213014', '654', '0'), ('968257', '1462213028', '654', '0'), ('968258', '1462213034', '654', '0'), ('968259', '1462213065', '654', '0'), ('968260', '1462213058', '654', '0'), ('968261', '1462213045', '654', '0'), ('968262', '1462213094', '654', '0'), ('968263', '1462213103', '654', '0'), ('968265', '1462213148', '654', '0'), ('968266', '1462213140', '654', '0'), ('968269', '1462212970', '654', '0'), ('968274', '1462213279', '654', '0'), ('968275', '1462213271', '654', '0'), ('968276', '1462212954', '654', '0'), ('968331', '1462220685', '654', '0'), ('968371', '1462214263', '654', '0'), ('968372', '1462214271', '654', '0'), ('968373', '1462214280', '654', '0'), ('968374', '1462214303', '654', '0'), ('968375', '1462214309', '654', '0'), ('968376', '1462214331', '654', '0'), ('968377', '1462214323', '654', '0'), ('968380', '1462214299', '654', '0'), ('968381', '1462214313', '654', '0'), ('968382', '1462214286', '654', '0'), ('968383', '1462214056', '654', '0'), ('968384', '1462214076', '654', '0'), ('968385', '1462214086', '654', '0'), ('968386', '1462214101', '654', '0'), ('968387', '1462214113', '654', '0'), ('968388', '1462214124', '654', '0'), ('968390', '1462214067', '654', '0'), ('968396', '1462214134', '654', '0'), ('968401', '1462214236', '654', '0'), ('968419', '1462214353', '654', '0'), ('968436', '1462214685', '654', '0'), ('968632', '1462379529', '654', '0'), ('968633', '1462379502', '654', '0'), ('968634', '1462379507', '654', '0'), ('968635', '1462379484', '654', '0'), ('968640', '1462379462', '654', '0'), ('968641', '1462379354', '654', '0'), ('968642', '1462379340', '654', '0');
INSERT INTO `creature_respawn` VALUES ('968643', '1462379311', '654', '0'), ('968647', '1462379085', '654', '0'), ('968648', '1462379316', '654', '0'), ('968664', '1462380697', '654', '0'), ('968665', '1462380735', '654', '0'), ('968670', '1462380563', '654', '0'), ('968671', '1462380540', '654', '0'), ('968672', '1462380531', '654', '0'), ('968673', '1462380554', '654', '0'), ('968674', '1462380626', '654', '0'), ('968675', '1462380662', '654', '0'), ('968677', '1462380643', '654', '0'), ('968678', '1462380712', '654', '0'), ('968679', '1462380718', '654', '0'), ('968680', '1462380757', '654', '0'), ('968682', '1462380741', '654', '0'), ('968687', '1462380573', '654', '0'), ('968899', '1462381321', '654', '0'), ('968900', '1462381425', '654', '0'), ('968901', '1462381437', '654', '0'), ('968902', '1462381419', '654', '0'), ('968903', '1462381395', '654', '0'), ('968904', '1462381383', '654', '0'), ('968905', '1462381371', '654', '0'), ('968906', '1462381457', '654', '0'), ('968907', '1462381358', '654', '0'), ('968911', '1462381408', '654', '0'), ('968914', '1462381342', '654', '0'), ('968917', '1462381576', '654', '0'), ('968921', '1462381298', '654', '0'), ('968923', '1462381311', '654', '0'), ('968983', '1462389051', '654', '0'), ('968985', '1462389077', '654', '0'), ('968986', '1462389068', '654', '0'), ('968995', '1462389059', '654', '0'), ('968998', '1462382174', '654', '0'), ('968999', '1462382174', '654', '0'), ('969000', '1462382052', '654', '0'), ('969001', '1462382052', '654', '0'), ('969002', '1462382052', '654', '0'), ('969003', '1462382021', '654', '0'), ('969004', '1462382020', '654', '0'), ('969005', '1462382020', '654', '0'), ('969006', '1462382020', '654', '0'), ('969007', '1462382021', '654', '0'), ('969008', '1462382021', '654', '0'), ('969009', '1462382175', '654', '0'), ('969010', '1462382044', '654', '0'), ('969011', '1462382044', '654', '0'), ('969012', '1462382037', '654', '0'), ('969013', '1462382037', '654', '0'), ('969014', '1462382037', '654', '0'), ('969015', '1462382037', '654', '0'), ('969016', '1462382037', '654', '0'), ('969017', '1462382037', '654', '0'), ('969018', '1462382044', '654', '0'), ('969019', '1462382044', '654', '0'), ('969020', '1462382037', '654', '0'), ('969021', '1462382037', '654', '0'), ('969022', '1462382075', '654', '0'), ('969023', '1462382075', '654', '0'), ('969026', '1462382081', '654', '0'), ('969027', '1462382074', '654', '0'), ('969028', '1462382074', '654', '0'), ('969029', '1462382075', '654', '0'), ('969030', '1462382075', '654', '0'), ('969031', '1462382075', '654', '0'), ('969032', '1462382075', '654', '0'), ('969033', '1462382081', '654', '0'), ('969034', '1462382028', '654', '0'), ('969035', '1462382028', '654', '0'), ('969036', '1462382028', '654', '0'), ('969037', '1462382028', '654', '0'), ('969038', '1462382028', '654', '0'), ('969039', '1462382028', '654', '0'), ('969040', '1462382028', '654', '0'), ('969041', '1462382028', '654', '0'), ('969042', '1462382028', '654', '0'), ('969043', '1462382028', '654', '0'), ('969044', '1462382028', '654', '0'), ('969045', '1462382028', '654', '0'), ('969046', '1462382028', '654', '0'), ('969047', '1462382028', '654', '0'), ('969048', '1462382028', '654', '0'), ('969049', '1462382028', '654', '0'), ('969050', '1462382158', '654', '0'), ('969051', '1462382096', '654', '0'), ('969052', '1462382096', '654', '0'), ('969053', '1462382096', '654', '0'), ('969054', '1462382096', '654', '0'), ('969055', '1462382096', '654', '0'), ('969056', '1462382082', '654', '0'), ('969057', '1462382168', '654', '0'), ('969058', '1462382082', '654', '0'), ('969059', '1462382096', '654', '0'), ('969060', '1462382096', '654', '0'), ('969061', '1462382096', '654', '0'), ('969063', '1462382062', '654', '0'), ('969064', '1462382066', '654', '0'), ('969065', '1462382066', '654', '0');
INSERT INTO `creature_respawn` VALUES ('969066', '1462382066', '654', '0'), ('969067', '1462382066', '654', '0'), ('969068', '1462382062', '654', '0'), ('969070', '1462382066', '654', '0'), ('969071', '1462382066', '654', '0'), ('969072', '1462382066', '654', '0'), ('969073', '1462382066', '654', '0'), ('969074', '1462382066', '654', '0'), ('969075', '1462382066', '654', '0'), ('969076', '1462382066', '654', '0'), ('969128', '1462382096', '654', '0'), ('969129', '1462382096', '654', '0'), ('969130', '1462382096', '654', '0'), ('969131', '1462382096', '654', '0'), ('969132', '1462382104', '654', '0'), ('969133', '1462382104', '654', '0'), ('969134', '1462382096', '654', '0'), ('969135', '1462382096', '654', '0'), ('969136', '1462382104', '654', '0'), ('969137', '1462382092', '654', '0'), ('969138', '1462382092', '654', '0'), ('969139', '1462382104', '654', '0'), ('969142', '1462382112', '654', '0'), ('969143', '1462382111', '654', '0'), ('969153', '1462382137', '654', '0'), ('969154', '1462382136', '654', '0'), ('969158', '1462382119', '654', '0'), ('969159', '1462382119', '654', '0'), ('969160', '1462382119', '654', '0'), ('969161', '1462382125', '654', '0'), ('969162', '1462382132', '654', '0'), ('969165', '1462382130', '654', '0'), ('969168', '1462382128', '654', '0'), ('969250', '1462382062', '654', '0'), ('969251', '1462382077', '654', '0'), ('969252', '1462382037', '654', '0'), ('969253', '1462382020', '654', '0'), ('969254', '1462382082', '654', '0'), ('969255', '1462382092', '654', '0'), ('969257', '1462382125', '654', '0'), ('969258', '1462382136', '654', '0'), ('969260', '1462382130', '654', '0'), ('969268', '1462382028', '654', '0'), ('969398', '1462211705', '654', '0'), ('969475', '1462206876', '654', '0'), ('969584', '1462206634', '654', '0'), ('969585', '1462206892', '654', '0'), ('969600', '1462206652', '654', '0'), ('969618', '1462206883', '654', '0'), ('969619', '1462206658', '654', '0'), ('969622', '1462206873', '654', '0'), ('969623', '1462206646', '654', '0'), ('969634', '1462206670', '654', '0'), ('969636', '1462206668', '654', '0'), ('969637', '1462206663', '654', '0'), ('969639', '1462206645', '654', '0'), ('969640', '1462206890', '654', '0'), ('969641', '1462206668', '654', '0'), ('969642', '1462206651', '654', '0'), ('969643', '1462206677', '654', '0'), ('969647', '1462206654', '654', '0'), ('969648', '1462206880', '654', '0'), ('969650', '1462206627', '654', '0'), ('969654', '1462206656', '654', '0'), ('969660', '1462206669', '654', '0'), ('969663', '1462206661', '654', '0'), ('969664', '1462206672', '654', '0'), ('969673', '1462206677', '654', '0'), ('969686', '1462206654', '654', '0'), ('969687', '1462206678', '654', '0'), ('969689', '1462206673', '654', '0'), ('969690', '1462206645', '654', '0'), ('969691', '1462206677', '654', '0'), ('969693', '1462206661', '654', '0'), ('969694', '1462206645', '654', '0'), ('969695', '1462206660', '654', '0'), ('969696', '1462206678', '654', '0'), ('969699', '1462206654', '654', '0'), ('969715', '1462206673', '654', '0'), ('969716', '1462206657', '654', '0'), ('969717', '1462206645', '654', '0'), ('969725', '1462206632', '654', '0'), ('969727', '1462206672', '654', '0'), ('969732', '1462206666', '654', '0'), ('969737', '1462206634', '654', '0'), ('969738', '1462206617', '654', '0'), ('969754', '1462206680', '654', '0'), ('969755', '1462206629', '654', '0'), ('969762', '1462206644', '654', '0'), ('969763', '1462206631', '654', '0'), ('969764', '1462206674', '654', '0'), ('969765', '1462206670', '654', '0'), ('969766', '1462206656', '654', '0'), ('969767', '1462206659', '654', '0'), ('969768', '1462206676', '654', '0'), ('969769', '1462206668', '654', '0'), ('969808', '1462206669', '654', '0'), ('969809', '1462206625', '654', '0'), ('969810', '1462206643', '654', '0'), ('969811', '1462206664', '654', '0');
INSERT INTO `creature_respawn` VALUES ('969812', '1462206627', '654', '0'), ('969813', '1462206644', '654', '0'), ('969814', '1462206644', '654', '0'), ('969815', '1462206658', '654', '0'), ('969816', '1462206629', '654', '0'), ('969817', '1462206666', '654', '0'), ('969818', '1462206640', '654', '0'), ('969819', '1462206671', '654', '0'), ('969820', '1462206666', '654', '0'), ('969821', '1462206635', '654', '0'), ('969822', '1462206675', '654', '0'), ('969823', '1462206675', '654', '0'), ('969824', '1462206674', '654', '0'), ('969825', '1462206674', '654', '0'), ('969826', '1462206649', '654', '0'), ('969827', '1462206609', '654', '0'), ('969976', '1462204699', '654', '0'), ('970005', '1462204806', '654', '0'), ('970006', '1462204818', '654', '0'), ('970024', '1462206898', '654', '0'), ('970165', '1462204793', '654', '0'), ('970185', '1462204812', '654', '0'), ('970186', '1462206671', '654', '0'), ('970275', '1462381026', '654', '0'), ('970451', '1462207006', '654', '0'), ('970452', '1462207037', '654', '0'), ('970453', '1462207024', '654', '0'), ('970476', '1462207028', '654', '0'), ('970477', '1462207000', '654', '0'), ('970494', '1462379658', '654', '0'), ('970514', '1462204972', '654', '0'), ('970520', '1462207178', '654', '0'), ('970552', '1462204710', '654', '0'), ('970553', '1462379648', '654', '0'), ('970555', '1462379648', '654', '0'), ('970569', '1462206583', '654', '0'), ('970570', '1462206628', '654', '0'), ('970572', '1462207011', '654', '0'), ('970573', '1462207015', '654', '0'), ('970574', '1462207033', '654', '0'), ('970575', '1462207020', '654', '0'), ('970695', '1462214343', '654', '0'), ('970696', '1462214351', '654', '0'), ('970698', '1462214341', '654', '0'), ('970699', '1462214346', '654', '0'), ('970701', '1462214329', '654', '0'), ('970702', '1462214326', '654', '0'), ('970703', '1462214320', '654', '0'), ('970705', '1462214332', '654', '0'), ('970706', '1462214350', '654', '0'), ('970735', '1462209100', '654', '0'), ('970736', '1462208905', '654', '0'), ('970738', '1462209049', '654', '0'), ('970740', '1462209078', '654', '0'), ('970761', '1462208488', '654', '0'), ('970792', '1462206789', '654', '0'), ('970813', '1462207002', '654', '0'), ('970816', '1462206757', '654', '0'), ('970833', '1462206971', '654', '0'), ('970834', '1462206993', '654', '0'), ('970835', '1462206988', '654', '0'), ('970836', '1462206965', '654', '0'), ('970837', '1462206982', '654', '0'), ('970838', '1462206955', '654', '0'), ('970839', '1462206946', '654', '0'), ('970851', '1462381045', '654', '0'), ('970852', '1462381103', '654', '0'), ('970853', '1462381203', '654', '0'), ('970854', '1462381150', '654', '0'), ('970855', '1462381039', '654', '0'), ('970955', '1462208946', '654', '0'), ('970956', '1462208924', '654', '0'), ('970957', '1462208937', '654', '0'), ('970958', '1462208945', '654', '0'), ('970959', '1462208943', '654', '0'), ('970960', '1462208940', '654', '0'), ('970961', '1462208920', '654', '0'), ('970962', '1462208956', '654', '0'), ('970963', '1462208958', '654', '0'), ('971110', '1462381056', '654', '0'), ('971111', '1462381055', '654', '0'), ('971112', '1462381052', '654', '0'), ('971113', '1462381047', '654', '0'), ('971114', '1462381049', '654', '0'), ('971115', '1462381043', '654', '0'), ('971116', '1462381016', '654', '0'), ('971117', '1462381023', '654', '0'), ('971118', '1462381041', '654', '0'), ('971119', '1462381037', '654', '0'), ('971120', '1462381045', '654', '0'), ('971121', '1462381010', '654', '0'), ('971122', '1462381022', '654', '0'), ('971123', '1462381031', '654', '0'), ('971124', '1462381014', '654', '0'), ('971125', '1462381025', '654', '0'), ('971126', '1462381006', '654', '0'), ('971127', '1462381040', '654', '0'), ('971128', '1462381030', '654', '0'), ('971153', '1462381013', '654', '0'), ('971167', '1462381036', '654', '0');
INSERT INTO `creature_respawn` VALUES ('971168', '1462381035', '654', '0'), ('971218', '1462381018', '654', '0'), ('971219', '1462381023', '654', '0'), ('971220', '1462381022', '654', '0'), ('971221', '1462381025', '654', '0'), ('971222', '1462381007', '654', '0'), ('971223', '1462381020', '654', '0'), ('971224', '1462381005', '654', '0'), ('971296', '1462381105', '654', '0'), ('971300', '1462381059', '654', '0'), ('971301', '1462381046', '654', '0'), ('971304', '1462381042', '654', '0'), ('971307', '1462381043', '654', '0'), ('971309', '1462381068', '654', '0'), ('971311', '1462381031', '654', '0'), ('971315', '1462381043', '654', '0'), ('971318', '1462381018', '654', '0'), ('971324', '1462381056', '654', '0'), ('971339', '1462212214', '654', '0'), ('973498', '1469570658', '0', '0'), ('973499', '1469570661', '0', '0'), ('973526', '1469570666', '0', '0'), ('973537', '1469601801', '0', '0'), ('973583', '1469601972', '0', '0'), ('973588', '1469601987', '0', '0'), ('973592', '1469601778', '0', '0'), ('973596', '1469569989', '0', '0'), ('973605', '1469569981', '0', '0'), ('973609', '1469569992', '0', '0'), ('973616', '1469570025', '0', '0'), ('973633', '1469601873', '0', '0'), ('973634', '1469601908', '0', '0'), ('973636', '1469601818', '0', '0'), ('973644', '1469601830', '0', '0'), ('973651', '1469570074', '0', '0'), ('973655', '1469570050', '0', '0'), ('973659', '1469570007', '0', '0'), ('973666', '1469570022', '0', '0'), ('973674', '1469570087', '0', '0'), ('973677', '1469570058', '0', '0'), ('973722', '1469601786', '0', '0'), ('973726', '1469602003', '0', '0'), ('973728', '1469601987', '0', '0'), ('973729', '1469601822', '0', '0'), ('973730', '1469601820', '0', '0'), ('973731', '1469601837', '0', '0'), ('973765', '1469601983', '0', '0'), ('973768', '1469601839', '0', '0'), ('973798', '1469601999', '0', '0'), ('973800', '1469601989', '0', '0'), ('973805', '1469601834', '0', '0'), ('973809', '1469601826', '0', '0'), ('973824', '1469601843', '0', '0'), ('973825', '1469601837', '0', '0'), ('973827', '1469601839', '0', '0'), ('973849', '1469601636', '0', '0'), ('973911', '1469570901', '0', '0'), ('973920', '1469570928', '0', '0'), ('973921', '1469570908', '0', '0'), ('973932', '1469570892', '0', '0'), ('973933', '1469570952', '0', '0'), ('974061', '1469601795', '0', '0'), ('974064', '1469601791', '0', '0'), ('974069', '1469601637', '0', '0'), ('974100', '1469601781', '0', '0'), ('974107', '1469601808', '0', '0'), ('974108', '1469601814', '0', '0'), ('974110', '1469601814', '0', '0'), ('974113', '1469601812', '0', '0'), ('974115', '1469601817', '0', '0'), ('974121', '1469601810', '0', '0'), ('974126', '1469601845', '0', '0'), ('974127', '1469601823', '0', '0'), ('974128', '1469601813', '0', '0'), ('974129', '1469601830', '0', '0'), ('974132', '1469601823', '0', '0'), ('974133', '1469601829', '0', '0'), ('974135', '1469601824', '0', '0'), ('974138', '1469601813', '0', '0'), ('974139', '1469601842', '0', '0'), ('986637', '1463528186', '1', '0'), ('988242', '1468779354', '0', '0'), ('988243', '1468779306', '0', '0'), ('988244', '1468779324', '0', '0'), ('988246', '1468779349', '0', '0'), ('988251', '1468779333', '0', '0'), ('988254', '1468779316', '0', '0'), ('988262', '1468779339', '0', '0'), ('988267', '1468779378', '0', '0'), ('988268', '1468779567', '0', '0'), ('988270', '1469042676', '0', '0'), ('988271', '1469042647', '0', '0'), ('988272', '1469042525', '0', '0'), ('988275', '1469134363', '0', '0'), ('988276', '1469134222', '0', '0'), ('988277', '1469134346', '0', '0'), ('988278', '1469134380', '0', '0'), ('988279', '1469134415', '0', '0'), ('988283', '1469134354', '0', '0'), ('988284', '1469134450', '0', '0');
INSERT INTO `creature_respawn` VALUES ('988285', '1469134408', '0', '0'), ('988286', '1469134371', '0', '0'), ('988287', '1469134378', '0', '0'), ('988288', '1469134417', '0', '0'), ('988289', '1469134398', '0', '0'), ('988290', '1469134445', '0', '0'), ('988291', '1469134365', '0', '0'), ('988292', '1469134455', '0', '0'), ('988293', '1469134393', '0', '0'), ('988294', '1469134348', '0', '0'), ('988295', '1469134438', '0', '0'), ('988297', '1469133844', '0', '0'), ('988301', '1469134016', '0', '0'), ('988311', '1469132685', '0', '0'), ('988314', '1469132656', '0', '0'), ('988316', '1469132682', '0', '0'), ('988317', '1469132687', '0', '0'), ('988319', '1469133980', '0', '0'), ('988320', '1469134039', '0', '0'), ('988321', '1469134062', '0', '0'), ('988322', '1469134030', '0', '0'), ('988323', '1469134079', '0', '0'), ('988362', '1469206414', '0', '0'), ('988369', '1469206438', '0', '0'), ('988375', '1469199738', '0', '0'), ('989316', '1463505506', '0', '0'), ('989317', '1463505447', '0', '0'), ('989318', '1463505461', '0', '0'), ('989321', '1463505494', '0', '0'), ('989574', '1472313054', '389', '1'), ('989575', '1472314036', '389', '1'), ('989576', '1472313051', '389', '1'), ('989962', '1463497367', '1', '0'), ('990441', '1463497389', '1', '0'), ('990445', '1463497438', '1', '0'), ('990452', '1463497389', '1', '0'), ('997867', '1468786244', '0', '0'), ('997869', '1468786244', '0', '0'), ('997870', '1468786244', '0', '0'), ('997871', '1468786244', '0', '0'), ('997872', '1468786244', '0', '0'), ('997873', '1468786244', '0', '0'), ('997874', '1468786244', '0', '0'), ('997877', '1468786244', '0', '0'), ('997878', '1468786244', '0', '0'), ('997879', '1468786244', '0', '0'), ('1000687', '1462211607', '655', '0');
COMMIT;

-- ----------------------------
-- Table structure for `cuf_profile`
-- ----------------------------
DROP TABLE IF EXISTS `cuf_profile`;
CREATE TABLE `cuf_profile` (
`guid`  int(10) UNSIGNED NOT NULL ,
`name`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`data`  tinyblob NULL ,
PRIMARY KEY (`guid`, `name`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of cuf_profile
-- ----------------------------
BEGIN;
INSERT INTO `cuf_profile` VALUES ('1', 'Основной', 0x2190B22848002400000000000000000000C3), ('2', 'Основной', 0x2190B200480024), ('3', 'Основной', 0x2190B25E48002400000000000000000000F9), ('4', 'Основной', 0x2190B228480024), ('5', 'Основной', 0x2190B25E4800240000000000000000000037), ('6', 'Основной', 0x2190B20648002400000000000000000000C5), ('7', 'Основной', 0x2190B2004800240000000000000000000044), ('8', 'Основной', 0x2190B2D0480024), ('9', 'Основной', 0x2190B2D048002400000000000000000000BB), ('10', 'Основной', 0x2190B22848002400000000000000000000BB), ('11', 'Основной', 0x2190B2BC480024), ('12', 'Основной', 0x2190B22848002400000000000000000000BB), ('13', 'Основной', 0x2190B2204800240000000000000000000069), ('14', 'Основной', 0x2190B200480024), ('15', 'Основной', 0x2190B220480024), ('16', 'Основной', 0x2190B2204800240000000000000000000068), ('17', 'Основной', 0x2190B28248002400000000000000000000D0), ('18', 'Основной', 0x2190B22848002400000000000000000000C5), ('19', 'Основной', 0x2190B23048002400000000000000000000C5), ('20', 'Основной', 0x2190B230480024), ('21', 'Основной', 0x2190B274480024000000000000000000002C), ('22', 'Основной', 0x2190B2FA4800240000000000000000000043), ('23', 'Основной', 0x2190B2784800240000000000000000000061);
COMMIT;

-- ----------------------------
-- Table structure for `daily_players_reports`
-- ----------------------------
DROP TABLE IF EXISTS `daily_players_reports`;
CREATE TABLE `daily_players_reports` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`creation_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`average`  float NOT NULL DEFAULT 0 ,
`total_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`speed_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`fly_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`jump_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`waterwalk_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`teleportplane_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`climb_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of daily_players_reports
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `game_event_condition_save`
-- ----------------------------
DROP TABLE IF EXISTS `game_event_condition_save`;
CREATE TABLE `game_event_condition_save` (
`eventEntry`  tinyint(3) UNSIGNED NOT NULL ,
`condition_id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`done`  float NULL DEFAULT 0 ,
PRIMARY KEY (`eventEntry`, `condition_id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of game_event_condition_save
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `game_event_save`
-- ----------------------------
DROP TABLE IF EXISTS `game_event_save`;
CREATE TABLE `game_event_save` (
`eventEntry`  tinyint(3) UNSIGNED NOT NULL ,
`state`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`next_start`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`eventEntry`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of game_event_save
-- ----------------------------
BEGIN;
INSERT INTO `game_event_save` VALUES ('33', '2', '0'), ('34', '2', '0'), ('35', '2', '0'), ('36', '2', '0'), ('37', '2', '0'), ('38', '2', '0'), ('39', '2', '0'), ('40', '2', '0'), ('41', '2', '0'), ('42', '2', '0'), ('43', '2', '0'), ('44', '2', '0'), ('45', '2', '0'), ('46', '2', '0'), ('47', '2', '0');
COMMIT;

-- ----------------------------
-- Table structure for `gameobject_respawn`
-- ----------------------------
DROP TABLE IF EXISTS `gameobject_respawn`;
CREATE TABLE `gameobject_respawn` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`respawnTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mapId`  smallint(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instanceId`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Instance Identifier' ,
PRIMARY KEY (`guid`, `instanceId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Grid Loading System'

;

-- ----------------------------
-- Records of gameobject_respawn
-- ----------------------------
BEGIN;
INSERT INTO `gameobject_respawn` VALUES ('7174', '1463473780', '0', '0'), ('7175', '1463473122', '0', '0'), ('7177', '1463473842', '0', '0'), ('7181', '1463473952', '0', '0'), ('7212', '1463473904', '0', '0'), ('7216', '1463473877', '0', '0'), ('7217', '1463473919', '0', '0'), ('48450', '1463499059', '1', '0'), ('48451', '1463499046', '1', '0'), ('48457', '1463499108', '1', '0'), ('48458', '1463499113', '1', '0'), ('48467', '1463499164', '1', '0'), ('48471', '1463499120', '1', '0'), ('73998', '1464887569', '1', '0'), ('74078', '1464886830', '1', '0'), ('74472', '1466537300', '1', '0'), ('74477', '1466537194', '1', '0'), ('74504', '1464980725', '1', '0'), ('74505', '1464980606', '1', '0'), ('74506', '1464980591', '1', '0'), ('74606', '1464980834', '1', '0'), ('74608', '1464980829', '1', '0'), ('81485', '1469728181', '0', '0'), ('81488', '1469728179', '0', '0'), ('81489', '1469728109', '0', '0'), ('81491', '1469728090', '0', '0'), ('81492', '1469728093', '0', '0'), ('81771', '1468952405', '0', '0'), ('81772', '1468952409', '0', '0'), ('81782', '1468952421', '0', '0'), ('81784', '1468952418', '0', '0'), ('81790', '1468952056', '0', '0'), ('81818', '1468952075', '0', '0'), ('82032', '1469039676', '0', '0'), ('82035', '1469039561', '0', '0'), ('82036', '1469039566', '0', '0'), ('82038', '1469039534', '0', '0'), ('82039', '1469039655', '0', '0'), ('82040', '1469039520', '0', '0'), ('82058', '1469039585', '0', '0'), ('82059', '1469039634', '0', '0'), ('521184', '1463493828', '648', '0'), ('522180', '1462211359', '655', '0'), ('522247', '1462211326', '655', '0'), ('522409', '1462209553', '654', '0'), ('522428', '1462209471', '654', '0'), ('522430', '1462209491', '654', '0'), ('522434', '1462209516', '654', '0'), ('522445', '1462213293', '654', '0'), ('522449', '1462213216', '654', '0'), ('522450', '1462213224', '654', '0'), ('522461', '1462211657', '655', '0'), ('522462', '1462211684', '655', '0'), ('522463', '1462211707', '655', '0'), ('522479', '1462212931', '654', '0'), ('522481', '1462213239', '654', '0'), ('522482', '1462213245', '654', '0'), ('522486', '1462213266', '654', '0'), ('524905', '1463468965', '0', '0'), ('524910', '1468786048', '0', '0'), ('524931', '1463469005', '0', '0'), ('524948', '1463473356', '0', '0'), ('525045', '1463429566', '0', '0'), ('525050', '1463429527', '0', '0'), ('525053', '1463429570', '0', '0'), ('526858', '1463496797', '1', '0'), ('526895', '1463496853', '1', '0'), ('526907', '1463496825', '1', '0'), ('526908', '1463496829', '1', '0'), ('526909', '1463496821', '1', '0');
COMMIT;

-- ----------------------------
-- Table structure for `gm_subsurveys`
-- ----------------------------
DROP TABLE IF EXISTS `gm_subsurveys`;
CREATE TABLE `gm_subsurveys` (
`surveyId`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`subsurveyId`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`rank`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`comment`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`surveyId`, `subsurveyId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of gm_subsurveys
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `gm_surveys`
-- ----------------------------
DROP TABLE IF EXISTS `gm_surveys`;
CREATE TABLE `gm_surveys` (
`surveyId`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mainSurvey`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`overallComment`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`createTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`surveyId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of gm_surveys
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `gm_tickets`
-- ----------------------------
DROP TABLE IF EXISTS `gm_tickets`;
CREATE TABLE `gm_tickets` (
`ticketId`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier of ticket creator' ,
`name`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT 'Name of ticket creator' ,
`message`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`createTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`mapId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`posX`  float NOT NULL DEFAULT 0 ,
`posY`  float NOT NULL DEFAULT 0 ,
`posZ`  float NOT NULL DEFAULT 0 ,
`lastModifiedTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`closedBy`  int(10) NOT NULL DEFAULT 0 ,
`assignedTo`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'GUID of admin to whom ticket is assigned' ,
`comment`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`completed`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`escalated`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`viewed`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`haveTicket`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`ticketId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of gm_tickets
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `group_instance`
-- ----------------------------
DROP TABLE IF EXISTS `group_instance`;
CREATE TABLE `group_instance` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`instance`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`permanent`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `instance`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of group_instance
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `group_member`
-- ----------------------------
DROP TABLE IF EXISTS `group_member`;
CREATE TABLE `group_member` (
`guid`  int(10) UNSIGNED NOT NULL ,
`memberGuid`  int(10) UNSIGNED NOT NULL ,
`memberFlags`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`subgroup`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`roles`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`memberGuid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Groups'

;

-- ----------------------------
-- Records of group_member
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `groups`
-- ----------------------------
DROP TABLE IF EXISTS `groups`;
CREATE TABLE `groups` (
`guid`  int(10) UNSIGNED NOT NULL ,
`leaderGuid`  int(10) UNSIGNED NOT NULL ,
`lootMethod`  tinyint(3) UNSIGNED NOT NULL ,
`looterGuid`  int(10) UNSIGNED NOT NULL ,
`lootThreshold`  tinyint(3) UNSIGNED NOT NULL ,
`icon1`  int(10) UNSIGNED NOT NULL ,
`icon2`  int(10) UNSIGNED NOT NULL ,
`icon3`  int(10) UNSIGNED NOT NULL ,
`icon4`  int(10) UNSIGNED NOT NULL ,
`icon5`  int(10) UNSIGNED NOT NULL ,
`icon6`  int(10) UNSIGNED NOT NULL ,
`icon7`  int(10) UNSIGNED NOT NULL ,
`icon8`  int(10) UNSIGNED NOT NULL ,
`groupType`  tinyint(3) UNSIGNED NOT NULL ,
`difficulty`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`raiddifficulty`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Groups'

;

-- ----------------------------
-- Records of groups
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild`
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`name`  varchar(24) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`leaderguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`EmblemStyle`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`EmblemColor`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`BorderStyle`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`BorderColor`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`BackgroundColor`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`info`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`motd`  varchar(128) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`createdate`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankMoney`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`level`  int(10) UNSIGNED NULL DEFAULT 1 ,
`experience`  bigint(20) UNSIGNED NULL DEFAULT 0 ,
`todayExperience`  bigint(20) UNSIGNED NULL DEFAULT 0 ,
PRIMARY KEY (`guildid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild System'

;

-- ----------------------------
-- Records of guild
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_achievement`
-- ----------------------------
DROP TABLE IF EXISTS `guild_achievement`;
CREATE TABLE `guild_achievement` (
`guildId`  int(10) UNSIGNED NOT NULL ,
`achievement`  smallint(5) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`guids`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`guildId`, `achievement`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_achievement
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_achievement_progress`
-- ----------------------------
DROP TABLE IF EXISTS `guild_achievement_progress`;
CREATE TABLE `guild_achievement_progress` (
`guildId`  int(10) UNSIGNED NOT NULL ,
`criteria`  smallint(5) UNSIGNED NOT NULL ,
`counter`  int(10) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`completedGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guildId`, `criteria`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_achievement_progress
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_bank_eventlog`
-- ----------------------------
DROP TABLE IF EXISTS `guild_bank_eventlog`;
CREATE TABLE `guild_bank_eventlog` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Guild Identificator' ,
`LogGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Log record identificator - auxiliary column' ,
`TabId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Guild bank TabId' ,
`EventType`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Event type' ,
`PlayerGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`ItemOrMoney`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`ItemStackCount`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`DestTabId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Destination Tab Id' ,
`TimeStamp`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Event UNIX time' ,
PRIMARY KEY (`guildid`, `LogGuid`, `TabId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_bank_eventlog
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_bank_item`
-- ----------------------------
DROP TABLE IF EXISTS `guild_bank_item`;
CREATE TABLE `guild_bank_item` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`TabId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`SlotId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`item_guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guildid`, `TabId`, `SlotId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_bank_item
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_bank_right`
-- ----------------------------
DROP TABLE IF EXISTS `guild_bank_right`;
CREATE TABLE `guild_bank_right` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`TabId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`rid`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`gbright`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`SlotPerDay`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guildid`, `TabId`, `rid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_bank_right
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_bank_tab`
-- ----------------------------
DROP TABLE IF EXISTS `guild_bank_tab`;
CREATE TABLE `guild_bank_tab` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`TabId`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`TabName`  varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`TabIcon`  varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`TabText`  varchar(500) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,
PRIMARY KEY (`guildid`, `TabId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_bank_tab
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_eventlog`
-- ----------------------------
DROP TABLE IF EXISTS `guild_eventlog`;
CREATE TABLE `guild_eventlog` (
`guildid`  int(10) UNSIGNED NOT NULL COMMENT 'Guild Identificator' ,
`LogGuid`  int(10) UNSIGNED NOT NULL COMMENT 'Log record identificator - auxiliary column' ,
`EventType`  tinyint(3) UNSIGNED NOT NULL COMMENT 'Event type' ,
`PlayerGuid1`  int(10) UNSIGNED NOT NULL COMMENT 'Player 1' ,
`PlayerGuid2`  int(10) UNSIGNED NOT NULL COMMENT 'Player 2' ,
`NewRank`  tinyint(3) UNSIGNED NOT NULL COMMENT 'New rank(in case promotion/demotion)' ,
`TimeStamp`  int(10) UNSIGNED NOT NULL COMMENT 'Event UNIX time' ,
PRIMARY KEY (`guildid`, `LogGuid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild Eventlog'

;

-- ----------------------------
-- Records of guild_eventlog
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_finder_applicant`
-- ----------------------------
DROP TABLE IF EXISTS `guild_finder_applicant`;
CREATE TABLE `guild_finder_applicant` (
`guildId`  int(10) UNSIGNED NULL DEFAULT NULL ,
`playerGuid`  int(10) UNSIGNED NULL DEFAULT NULL ,
`availability`  tinyint(3) UNSIGNED NULL DEFAULT 0 ,
`classRole`  tinyint(3) UNSIGNED NULL DEFAULT 0 ,
`interests`  tinyint(3) UNSIGNED NULL DEFAULT 0 ,
`comment`  varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL ,
`submitTime`  int(10) UNSIGNED NULL DEFAULT NULL 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of guild_finder_applicant
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_finder_guild_settings`
-- ----------------------------
DROP TABLE IF EXISTS `guild_finder_guild_settings`;
CREATE TABLE `guild_finder_guild_settings` (
`guildId`  int(10) UNSIGNED NOT NULL ,
`availability`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`classRoles`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`interests`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`level`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`listed`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`comment`  varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL ,
PRIMARY KEY (`guildId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of guild_finder_guild_settings
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_member`
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member` (
`guildid`  int(10) UNSIGNED NOT NULL COMMENT 'Guild Identificator' ,
`guid`  int(10) UNSIGNED NOT NULL ,
`rank`  tinyint(3) UNSIGNED NOT NULL ,
`pnote`  varchar(31) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`offnote`  varchar(31) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`BankResetTimeMoney`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemMoney`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab0`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab1`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab2`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab3`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab4`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab4`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab5`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab5`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab6`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab6`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankResetTimeTab7`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`BankRemSlotsTab7`  int(10) UNSIGNED NOT NULL DEFAULT 0 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild System'

;

-- ----------------------------
-- Records of guild_member
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_news_log`
-- ----------------------------
DROP TABLE IF EXISTS `guild_news_log`;
CREATE TABLE `guild_news_log` (
`guild`  int(10) UNSIGNED NOT NULL ,
`id`  int(10) UNSIGNED NOT NULL ,
`eventType`  int(10) UNSIGNED NOT NULL ,
`playerGuid`  bigint(20) UNSIGNED NOT NULL ,
`data`  int(10) UNSIGNED NOT NULL ,
`flags`  int(10) UNSIGNED NOT NULL ,
`date`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guild`, `id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of guild_news_log
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `guild_rank`
-- ----------------------------
DROP TABLE IF EXISTS `guild_rank`;
CREATE TABLE `guild_rank` (
`guildid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`rid`  tinyint(3) UNSIGNED NOT NULL ,
`rname`  varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`rights`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`BankMoneyPerDay`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guildid`, `rid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild System'

;

-- ----------------------------
-- Records of guild_rank
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `instance`
-- ----------------------------
DROP TABLE IF EXISTS `instance`;
CREATE TABLE `instance` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`map`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`resettime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`difficulty`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`completedEncounters`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`data`  tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of instance
-- ----------------------------
BEGIN;
INSERT INTO `instance` VALUES ('1', '389', '1472321236', '1', '0', ''), ('2', '43', '1472358518', '1', '0', '0 0 0 0 0 0 0 0 0');
COMMIT;

-- ----------------------------
-- Table structure for `instance_reset`
-- ----------------------------
DROP TABLE IF EXISTS `instance_reset`;
CREATE TABLE `instance_reset` (
`mapid`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`difficulty`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`resettime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`mapid`, `difficulty`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of instance_reset
-- ----------------------------
BEGIN;
INSERT INTO `instance_reset` VALUES ('33', '2', '1472356800'), ('36', '2', '1472356800'), ('249', '3', '1472788800'), ('249', '4', '1472788800'), ('269', '2', '1472356800'), ('409', '9', '1472788800'), ('469', '9', '1472788800'), ('509', '3', '1472529600'), ('531', '9', '1472788800'), ('532', '3', '1472788800'), ('533', '3', '1472788800'), ('533', '4', '1472788800'), ('534', '4', '1472788800'), ('540', '2', '1472356800'), ('542', '2', '1472356800'), ('543', '2', '1472356800'), ('544', '4', '1472788800'), ('545', '2', '1472356800'), ('546', '2', '1472356800'), ('547', '2', '1472356800'), ('548', '4', '1472788800'), ('550', '4', '1472788800'), ('552', '2', '1472356800'), ('553', '2', '1472356800'), ('554', '2', '1472356800'), ('555', '2', '1472356800'), ('556', '2', '1472356800'), ('557', '2', '1472356800'), ('558', '2', '1472356800'), ('560', '2', '1472356800'), ('564', '4', '1472788800'), ('565', '4', '1472788800'), ('568', '2', '1472356800'), ('574', '2', '1472356800'), ('575', '2', '1472356800'), ('576', '2', '1472356800'), ('578', '2', '1472356800'), ('580', '4', '1472788800'), ('585', '2', '1472356800'), ('595', '2', '1472356800'), ('598', '2', '1472356800'), ('599', '2', '1472356800'), ('600', '2', '1472356800'), ('601', '2', '1472356800'), ('602', '2', '1472356800'), ('603', '3', '1472788800'), ('603', '4', '1472788800'), ('604', '2', '1472356800'), ('608', '2', '1472356800'), ('615', '3', '1472788800'), ('615', '4', '1472788800'), ('616', '3', '1472788800'), ('616', '4', '1472788800'), ('619', '2', '1472356800'), ('624', '3', '1472788800'), ('624', '4', '1472788800'), ('631', '3', '1472788800'), ('631', '4', '1472788800'), ('631', '5', '1472788800'), ('631', '6', '1472788800'), ('632', '2', '1472356800'), ('643', '2', '1472356800'), ('644', '2', '1472356800'), ('645', '2', '1472356800'), ('649', '3', '1472788800'), ('649', '4', '1472788800'), ('649', '5', '1472788800'), ('649', '6', '1472788800'), ('650', '2', '1472356800'), ('657', '2', '1472356800'), ('658', '2', '1472356800'), ('668', '2', '1472356800'), ('669', '3', '1472788800'), ('669', '4', '1472788800'), ('669', '5', '1472788800'), ('669', '6', '1472788800'), ('670', '2', '1472356800'), ('671', '3', '1472788800'), ('671', '4', '1472788800'), ('671', '5', '1472788800'), ('671', '6', '1472788800'), ('720', '3', '1472788800'), ('720', '4', '1472788800'), ('720', '5', '1472788800'), ('720', '6', '1472788800'), ('724', '3', '1472788800'), ('724', '4', '1472788800'), ('724', '5', '1472788800'), ('724', '6', '1472788800'), ('725', '2', '1472356800'), ('754', '3', '1472788800'), ('754', '4', '1472788800'), ('754', '5', '1472788800'), ('754', '6', '1472788800'), ('755', '2', '1472356800'), ('757', '3', '1472788800'), ('757', '4', '1472788800'), ('757', '5', '1472788800'), ('757', '6', '1472788800'), ('859', '2', '1472356800');
INSERT INTO `instance_reset` VALUES ('938', '2', '1472356800'), ('939', '2', '1472356800'), ('940', '2', '1472356800'), ('959', '2', '1472356800'), ('960', '2', '1472356800'), ('961', '2', '1472356800'), ('962', '2', '1472356800'), ('967', '3', '1472788800'), ('967', '4', '1472788800'), ('967', '5', '1472788800'), ('967', '6', '1472788800'), ('994', '2', '1472356800'), ('996', '3', '1472788800'), ('996', '4', '1472788800'), ('996', '5', '1472788800'), ('996', '6', '1472788800'), ('1001', '2', '1472356800'), ('1004', '2', '1472356800'), ('1007', '2', '1472356800'), ('1008', '3', '1472788800'), ('1008', '4', '1472788800'), ('1008', '5', '1472788800'), ('1008', '6', '1472788800'), ('1009', '3', '1472788800'), ('1009', '4', '1472788800'), ('1009', '5', '1472788800'), ('1009', '6', '1472788800'), ('1011', '2', '1472356800'), ('1098', '3', '1472788800'), ('1098', '4', '1472788800'), ('1098', '5', '1472788800'), ('1098', '6', '1472788800'), ('1136', '3', '1472788800'), ('1136', '4', '1472788800'), ('1136', '5', '1472788800'), ('1136', '6', '1472788800');
COMMIT;

-- ----------------------------
-- Table structure for `item_instance`
-- ----------------------------
DROP TABLE IF EXISTS `item_instance`;
CREATE TABLE `item_instance` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`itemEntry`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`owner_guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`creatorGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`giftCreatorGuid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`count`  int(10) UNSIGNED NOT NULL DEFAULT 1 ,
`duration`  int(10) NOT NULL DEFAULT 0 ,
`charges`  tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`flags`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`enchantments`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`randomPropertyId`  smallint(5) NOT NULL DEFAULT 0 ,
`reforgeId`  mediumint(8) NULL DEFAULT NULL ,
`transmogrifyId`  mediumint(8) NULL DEFAULT NULL ,
`upgradeId`  mediumint(8) NULL DEFAULT NULL ,
`durability`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`playedTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`text`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Item System'

;

-- ----------------------------
-- Records of item_instance
-- ----------------------------
BEGIN;
INSERT INTO `item_instance` VALUES ('4', '52', '1', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('6', '51', '1', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('10', '6948', '1', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('12', '62328', '1', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('16', '72019', '2', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('20', '77272', '2', '0', '0', '4', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('22', '6948', '2', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('24', '77526', '2', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '18', '0', ''), ('26', '73209', '2', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '36', '0', ''), ('28', '6140', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('30', '1395', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('32', '35', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('34', '55', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('36', '6948', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('39', '2646', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('40', '1415', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('41', '159', '3', '0', '0', '2', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('42', '4604', '3', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('43', '3275', '3', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('45', '52550', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('47', '52551', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('49', '6948', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('51', '52552', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('53', '36', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('55', '2362', '4', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('58', '20893', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('60', '20894', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('62', '20978', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('64', '20895', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('66', '6948', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('67', '20845', '5', '0', '0', '4', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('68', '20846', '5', '0', '0', '6', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('74', '20998', '5', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('82', '35', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('84', '6948', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('85', '117', '6', '0', '0', '5', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('87', '159', '6', '0', '0', '6', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('95', '805', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('100', '52040', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '196609', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('103', '5571', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('110', '4496', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('113', '55005', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '10', '0', ''), ('145', '54983', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '10', '0', ''), ('169', '55017', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('177', '55018', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('245', '2406', '6', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('249', '54996', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('251', '54999', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('253', '2589', '6', '0', '0', '20', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('254', '8181', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('255', '6506', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('263', '768', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('269', '1513', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '60', '0', ''), ('271', '2455', '6', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('277', '2140', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2155 0 0 0 0 0 0 0 0 0 0 0 ', '1875', '0', '0', '0', '35', '0', ''), ('278', '1179', '6', '0', '0', '2', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('279', '858', '6', '0', '0', '2', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('280', '1506', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('281', '4541', '6', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('282', '1501', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '80', '0', ''), ('283', '9746', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('285', '52942', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '29', '0', ''), ('288', '72019', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('290', '72020', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '36', '0', ''), ('292', '77526', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '18', '0', ''), ('294', '77509', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '18', '0', ''), ('296', '6948', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('297', '20846', '7', '0', '0', '8', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('298', '21015', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('301', '20845', '7', '0', '0', '4', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('304', '20998', '7', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('306', '20482', '7', '0', '0', '3', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('308', '52550', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('310', '52551', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('312', '6948', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('314', '52552', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('316', '36', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('318', '2362', '8', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('320', '159', '8', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('321', '117', '8', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('322', '58255', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('325', '56151', '6', '0', '0', '2', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('326', '56150', '6', '0', '0', '2', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('329', '67229', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('331', '2589', '6', '0', '0', '20', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('349', '1422', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('350', '54992', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('354', '2589', '6', '0', '0', '20', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('355', '2966', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('357', '2409', '6', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('366', '50334', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('367', '54988', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('369', '2589', '6', '0', '0', '18', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('377', '4577', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('381', '4605', '6', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('386', '1512', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '60', '0', ''), ('387', '4562', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 102 0 0 0 0 0 0 0 0 0 0 0 ', '96', '0', '0', '0', '55', '0', ''), ('389', '1506', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('393', '55013', '6', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '65', '0', ''), ('395', '58234', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', '');
INSERT INTO `item_instance` VALUES ('397', '47', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('399', '48', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('401', '25', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('403', '50055', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('405', '6948', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('406', '62328', '9', '0', '0', '6', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('409', '159', '9', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('413', '57254', '9', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('415', '6098', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('417', '52', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('419', '51', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('421', '35', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('423', '6948', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('424', '4085', '10', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('426', '49778', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('428', '58244', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('430', '6121', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('432', '6122', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('434', '6948', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('435', '4865', '11', '0', '0', '3', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('437', '7074', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('439', '6129', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('441', '1396', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('443', '59', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('445', '35', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('447', '6948', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('450', '1425', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '70', '0', ''), ('451', '1370', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('452', '3275', '11', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('458', '55', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('462', '6948', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('474', '159', '12', '0', '0', '12', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('476', '5571', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('478', '4496', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('483', '58233', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('485', '43', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('487', '44', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('489', '6948', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('491', '52557', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('492', '3300', '13', '0', '0', '2', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('493', '62328', '13', '0', '0', '4', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('498', '5572', '13', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('500', '57', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('502', '1396', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('504', '35', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('506', '59', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('508', '6948', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('517', '117', '14', '0', '0', '11', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('518', '159', '14', '0', '0', '2', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('520', '805', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('521', '5571', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('523', '828', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('526', '805', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('550', '57389', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('560', '58231', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('562', '39', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '36', '0', ''), ('564', '40', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('566', '49778', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '36', '0', ''), ('568', '6948', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('569', '11847', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('570', '11848', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '18', '0', ''), ('573', '4604', '15', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('574', '3274', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '27', '0', ''), ('575', '52059', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('576', '12737', '15', '0', '0', '2', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('577', '2846', '15', '0', '0', '3', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('578', '3335', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('582', '779', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('583', '2672', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('588', '1208', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('624', '14091', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 79 0 0 82 0 0 0 0 0 0 0 0 ', '754', '0', '0', '0', '75', '0', ''), ('633', '57400', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('645', '2589', '12', '0', '0', '15', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('647', '4536', '12', '0', '0', '3', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('664', '780', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('699', '4840', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('705', '1414', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('711', '1430', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('713', '3373', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('715', '1429', '12', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('727', '858', '12', '0', '0', '2', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('733', '6948', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('742', '5571', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('747', '5572', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('773', '4496', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('867', '2287', '15', '0', '0', '19', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('871', '2287', '15', '0', '0', '20', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('926', '49514', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('928', '49515', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '36', '0', ''), ('930', '49516', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '23', '0', ''), ('932', '36', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '32', '0', ''), ('934', '6948', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('936', '50055', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '23', '0', ''), ('939', '818', '16', '0', '0', '2', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('940', '2287', '16', '0', '0', '4', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('941', '1495', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('942', '4566', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2271 0 0 0 0 0 0 0 0 0 0 0 ', '1991', '0', '0', '0', '60', '0', ''), ('943', '1735', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '60', '0', ''), ('944', '15013', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('945', '1497', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', '');
INSERT INTO `item_instance` VALUES ('947', '4681', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('948', '15298', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 82 0 0 71 0 0 0 0 0 0 0 0 ', '1009', '0', '0', '0', '80', '0', ''), ('949', '14114', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 82 0 0 0 0 0 0 0 0 0 0 0 ', '16', '0', '0', '0', '40', '0', ''), ('950', '14116', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('953', '1497', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('954', '1495', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('957', '82880', '16', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('958', '82605', '16', '0', '0', '2', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('967', '5572', '14', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('969', '58233', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('971', '44', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('973', '43', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('975', '52557', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('977', '6948', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('978', '49743', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('979', '117', '17', '0', '0', '4', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('988', '64884', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1030', '53405', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '75', '0', ''), ('1112', '1510', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 5 2638714 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('1151', '15309', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 71 0 0 0 0 0 0 0 0 0 0 0 ', '15', '0', '0', '0', '0', '0', ''), ('1157', '53441', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('1179', '53404', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1196', '54213', '15', '0', '0', '2', '0', '-1 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1197', '53430', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('1244', '53433', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '65', '0', ''), ('1245', '53418', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '90', '0', ''), ('1247', '53399', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '35', '0', ''), ('1250', '49176', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1252', '49162', '15', '0', '0', '2', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1259', '49596', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1262', '2589', '15', '0', '0', '2', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1264', '1742', '15', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('1266', '20893', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('1268', '20894', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1270', '20978', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1272', '20895', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('1274', '6948', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1275', '20845', '17', '0', '0', '10', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1276', '20846', '17', '0', '0', '7', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1277', '21015', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1280', '21020', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '30', '0', ''), ('1287', '21015', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1290', '20998', '17', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1294', '58245', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('1296', '139', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1298', '140', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '24', '0', ''), ('1300', '6948', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1302', '12282', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1303', '117', '18', '0', '0', '8', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1304', '4865', '18', '0', '0', '9', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1305', '7098', '18', '0', '0', '6', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1306', '1416', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('1310', '1430', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('1322', '1377', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1323', '53378', '18', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1334', '6948', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1523', '52', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1527', '35', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('1529', '6948', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1536', '57253', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1537', '117', '20', '0', '0', '9', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1538', '5571', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1539', '4496', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1542', '828', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1543', '159', '20', '0', '0', '3', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1545', '57386', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '60', '0', ''), ('1551', '805', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1556', '57256', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('1557', '11192', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '20', '0', ''), ('1567', '118', '20', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1568', '2962', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('1569', '2775', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1570', '8177', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '50', '0', ''), ('1571', '4540', '20', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1572', '57247', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '196609', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1573', '11475', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('1574', '1159', '20', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '45', '0', ''), ('2238', '2092', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2240', '58234', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('2242', '48', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('2244', '47', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2246', '50055', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2248', '6948', '21', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('2250', '2092', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2252', '58234', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('2254', '48', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('2256', '47', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2258', '50055', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('2260', '6948', '22', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('2560', '14113', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2308 0 0 0 0 0 0 0 0 0 0 0 ', '2028', '0', '0', '0', '13', '0', ''), ('2594', '82880', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '22', '0', ''), ('2602', '82878', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '48', '0', ''), ('2776', '6461', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '29', '0', ''), ('2803', '11982', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 81 0 0 73 0 0 0 0 0 0 0 0 ', '845', '0', '0', '0', '0', '0', ''), ('2881', '12987', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('3231', '65715', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3302', '1772', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '23', '0', ''), ('3387', '65678', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '18', '0', ''), ('3390', '6149', '19', '0', '0', '3', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3391', '1205', '19', '0', '0', '20', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', '');
INSERT INTO `item_instance` VALUES ('3394', '3770', '19', '0', '0', '18', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3397', '4499', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3398', '4499', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3399', '4499', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3400', '4499', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '196608', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3511', '65731', '19', '0', '0', '12', '0', '-1 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3512', '65723', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3551', '1205', '19', '0', '0', '13', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3605', '65708', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('3701', '4036', '19', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '26', '0', ''), ('3996', '6451', '19', '0', '0', '7', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4009', '4495', '19', '0', '0', '10', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4045', '3827', '19', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4050', '7273', '19', '0', '0', '4', '0', '-1 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4059', '1710', '19', '0', '0', '5', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4061', '6129', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '55', '0', ''), ('4063', '1396', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('4065', '59', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '25', '0', ''), ('4067', '35', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '40', '0', ''), ('4069', '6948', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '1', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4070', '1210', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4071', '3180', '23', '0', '0', '3', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4072', '4292', '23', '0', '0', '1', '0', '-1 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4073', '5124', '23', '0', '0', '3', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4074', '6470', '23', '0', '0', '3', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4075', '9805', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 98 0 0 0 0 0 0 0 0 0 0 0 ', '95', '0', '0', '0', '0', '0', ''), ('4082', '3184', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 70 0 0 0 0 0 0 0 0 0 0 0 ', '24', '0', '0', '0', '45', '0', ''), ('4083', '5635', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '0', '0', ''), ('4084', '1406', '23', '0', '0', '1', '0', '0 0 0 0 0 ', '0', '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ', '0', '0', '0', '0', '75', '0', '');
COMMIT;

-- ----------------------------
-- Table structure for `item_refund_instance`
-- ----------------------------
DROP TABLE IF EXISTS `item_refund_instance`;
CREATE TABLE `item_refund_instance` (
`item_guid`  int(10) UNSIGNED NOT NULL COMMENT 'Item GUID' ,
`player_guid`  int(10) UNSIGNED NOT NULL COMMENT 'Player GUID' ,
`paidMoney`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`paidExtendedCost`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`item_guid`, `player_guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Item Refund System'

;

-- ----------------------------
-- Records of item_refund_instance
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `item_soulbound_trade_data`
-- ----------------------------
DROP TABLE IF EXISTS `item_soulbound_trade_data`;
CREATE TABLE `item_soulbound_trade_data` (
`itemGuid`  int(10) UNSIGNED NOT NULL COMMENT 'Item GUID' ,
`allowedPlayers`  text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT 'Space separated GUID list of players who can receive this item in trade' ,
PRIMARY KEY (`itemGuid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Item Refund System'

;

-- ----------------------------
-- Records of item_soulbound_trade_data
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `lag_reports`
-- ----------------------------
DROP TABLE IF EXISTS `lag_reports`;
CREATE TABLE `lag_reports` (
`reportId`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`lagType`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`mapId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`posX`  float NOT NULL DEFAULT 0 ,
`posY`  float NOT NULL DEFAULT 0 ,
`posZ`  float NOT NULL DEFAULT 0 ,
`latency`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`createTime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`reportId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player System'
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of lag_reports
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `lfg_data`
-- ----------------------------
DROP TABLE IF EXISTS `lfg_data`;
CREATE TABLE `lfg_data` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`dungeon`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`state`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='LFG Data'

;

-- ----------------------------
-- Records of lfg_data
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_arena`
-- ----------------------------
DROP TABLE IF EXISTS `log_arena`;
CREATE TABLE `log_arena` (
`id`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
`timestamp`  int(11) NULL DEFAULT NULL ,
`string`  blob NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of log_arena
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_faction_change`
-- ----------------------------
DROP TABLE IF EXISTS `log_faction_change`;
CREATE TABLE `log_faction_change` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`guid`  int(16) NOT NULL ,
`account`  int(11) NOT NULL ,
`OldRace`  int(11) NOT NULL ,
`NewRace`  int(11) NOT NULL ,
`date`  datetime NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=3711

;

-- ----------------------------
-- Records of log_faction_change
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_gm`
-- ----------------------------
DROP TABLE IF EXISTS `log_gm`;
CREATE TABLE `log_gm` (
`id`  bigint(20) NOT NULL AUTO_INCREMENT ,
`date`  datetime NOT NULL ,
`gm_account_id`  bigint(20) NOT NULL ,
`gm_account_name`  blob NOT NULL ,
`gm_character_id`  bigint(20) NOT NULL ,
`gm_character_name`  blob NOT NULL ,
`gm_last_ip`  tinytext CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL ,
`sc_account_id`  bigint(20) NOT NULL ,
`sc_account_name`  blob NOT NULL ,
`sc_character_id`  bigint(20) NOT NULL ,
`sc_character_name`  blob NOT NULL ,
`command`  blob NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=30

;

-- ----------------------------
-- Records of log_gm
-- ----------------------------
BEGIN;
INSERT INTO `log_gm` VALUES ('1', '2016-07-22 18:15:10', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E74656C652073696C76657270696E65666F72657374205B506C617965723A2046736420284163636F756E743A20372920583A20313639392E38343939373620593A20313730362E353630303539205A3A203133352E393237393934204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('2', '2016-07-22 18:15:19', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6D6F64696679207370656564203130205B506C617965723A2046736420284163636F756E743A20372920583A203837382E37333939393020593A20313335392E333239393536205A3A2035322E343437313531204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('3', '2016-07-22 18:16:11', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320616464203434333635205B506C617965723A2046736420284163636F756E743A20372920583A20313338322E34323236303720593A20313034312E333532323935205A3A2035342E333137313230204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('4', '2016-07-27 09:35:02', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6E205B506C617965723A2046736420284163636F756E743A20372920583A20313338302E30373038303120593A20313033382E303736393034205A3A2035322E393234393834204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('5', '2016-07-27 09:35:09', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6D6F64696679207370656564203130205B506C617965723A2046736420284163636F756E743A20372920583A20313338302E30373038303120593A20313033382E303736393034205A3A2035322E393234393834204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('6', '2016-07-27 09:37:01', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A2046736420284163636F756E743A20372920583A202D3932362E36383436333120593A20313633312E333036303330205A3A2036382E333737373534204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('7', '2016-07-27 09:37:15', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '7', 0x41444D494E, '22', 0x467364, 0x436F6D6D616E643A202E676D206F6666205B506C617965723A2046736420284163636F756E743A20372920583A202D3932362E36383436333120593A20313633312E333036303330205A3A2036382E333737373534204D61703A20302053656C65637465643A204673642028475549443A203232295D), ('8', '2016-07-27 09:37:26', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320616464203435333132205B506C617965723A2046736420284163636F756E743A20372920583A202D3930392E31353030323420593A20313631362E383135373936205A3A2036382E333232343732204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('9', '2016-07-27 09:37:38', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320616464203435333132205B506C617965723A2046736420284163636F756E743A20372920583A202D3930392E31373130383220593A20313631382E353838363233205A3A2036382E333233333634204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('10', '2016-07-27 09:38:52', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320616464203435333132205B506C617965723A2046736420284163636F756E743A20372920583A202D3930352E36353037353720593A20313632312E373632363935205A3A2036382E323837373831204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('11', '2016-07-27 09:39:03', '7', 0x41444D494E, '22', 0x467364, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320616464203435333132205B506C617965723A2046736420284163636F756E743A20372920583A202D3930352E36353037353720593A20313632312E373632363935205A3A2036382E323837373831204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('12', '2016-08-27 16:22:11', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6C6576656C203430205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A20313639392E38343939373620593A20313730362E353630303539205A3A203133352E393237393934204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('13', '2016-08-27 16:22:51', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A20313639392E39303639383220593A20313639382E393633383637205A3A203133352E333730313738204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('14', '2016-08-27 16:24:54', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6C6576656C203430205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A20313639392E38343939373620593A20313730362E353630303539205A3A203133352E393237393934204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('15', '2016-08-27 16:40:21', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E74656C65206F726772696D6D6172205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A20313730302E34363439363620593A20313730332E373837323331205A3A203133352E373032333332204D61703A20302053656C65637465643A204552524F522028475549443A2030295D), ('16', '2016-08-27 16:42:26', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D32322E34333737353720593A202D33392E393739323333205A3A202D32312E363837393232204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('17', '2016-08-27 16:45:51', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E646965205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35362E32323536373020593A202D33352E363333383233205A3A202D32302E303532323235204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('18', '2016-08-27 16:45:54', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E646965205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35362E32323536373020593A202D33352E363333383233205A3A202D32302E303532323235204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('19', '2016-08-27 16:46:08', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6E205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35332E35333838373220593A202D33342E333730343634205A3A202D32302E373030353438204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('20', '2016-08-27 16:58:01', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6666205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35332E35333838373220593A202D33342E333730343634205A3A202D32302E373030353438204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('21', '2016-08-27 16:58:48', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, 0x436F6D6D616E643A202E676D206F6E205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D36312E38313839353820593A202D34302E313433363432205A3A202D31382E333538303937204D61703A203338392053656C65637465643A20D091D180D0B8D181D1812028475549443A203233295D), ('22', '2016-08-27 17:01:02', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6666205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D36302E31383438313120593A202D33372E313137393538205A3A202D31382E383938343734204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('23', '2016-08-27 17:02:17', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E646965205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35392E35343930353720593A202D34302E313738303730205A3A202D31392E313036313231204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('24', '2016-08-27 17:02:25', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E74656C65207761696C696E672063617665726E73205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D35392E35343930353720593A202D34302E313738303730205A3A202D31392E313036313231204D61703A203338392053656C65637465643A204552524F522028475549443A2030295D), ('25', '2016-08-27 17:02:56', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D3132332E32313534353420593A203135302E303033303637205A3A202D37362E363039383438204D61703A2034332053656C65637465643A204552524F522028475549443A2030295D), ('26', '2016-08-27 17:18:39', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D3734302E30353930323120593A202D323231342E323239393830205A3A2031362E313337343030204D61703A20312053656C65637465643A204552524F522028475549443A2030295D), ('27', '2016-08-27 17:19:01', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E6E706320696E666F205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D3131342E31303735373420593A203135322E323133323131205A3A202D37392E393437393930204D61703A2034332053656C65637465643A204552524F522028475549443A2030295D), ('28', '2016-08-27 17:19:16', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6E205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D3131312E32303436353120593A203231342E303431393136205A3A202D38352E333535353630204D61703A2034332053656C65637465643A204552524F522028475549443A2030295D), ('29', '2016-08-27 17:19:56', '7', 0x41444D494E, '23', 0xD091D180D0B8D181D181, '127.0.0.1', '0', '', '0', 0x4552524F52, 0x436F6D6D616E643A202E676D206F6666205B506C617965723A20D091D180D0B8D181D18120284163636F756E743A20372920583A202D37302E39303831323720593A203238342E373930363830205A3A202D39302E363130383535204D61703A2034332053656C65637465643A204552524F522028475549443A2030295D);
COMMIT;

-- ----------------------------
-- Table structure for `log_gm_chat`
-- ----------------------------
DROP TABLE IF EXISTS `log_gm_chat`;
CREATE TABLE `log_gm_chat` (
`id`  bigint(20) NOT NULL AUTO_INCREMENT ,
`type`  int(11) NOT NULL ,
`date`  datetime NOT NULL ,
`from_account_id`  bigint(20) NOT NULL ,
`from_account_name`  blob NOT NULL ,
`from_character_id`  bigint(20) NOT NULL ,
`from_character_name`  blob NOT NULL ,
`to_account_id`  bigint(20) NOT NULL ,
`to_account_name`  blob NOT NULL ,
`to_character_id`  bigint(20) NOT NULL ,
`to_character_name`  blob NOT NULL ,
`message`  blob NOT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of log_gm_chat
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_mail`
-- ----------------------------
DROP TABLE IF EXISTS `log_mail`;
CREATE TABLE `log_mail` (
`id`  int(11) NULL DEFAULT NULL ,
`messageType`  tinyint(3) NULL DEFAULT NULL ,
`stationery`  tinyint(3) NULL DEFAULT NULL ,
`mailTemplateId`  mediumint(8) NULL DEFAULT NULL ,
`sender`  int(11) NULL DEFAULT NULL ,
`receiver`  int(11) NULL DEFAULT NULL ,
`subject`  blob NULL ,
`body`  blob NULL ,
`has_items`  tinyint(3) NULL DEFAULT NULL ,
`expire_time`  bigint(40) NULL DEFAULT NULL ,
`deliver_time`  bigint(40) NULL DEFAULT NULL ,
`money`  int(11) NULL DEFAULT NULL ,
`cod`  int(11) NULL DEFAULT NULL ,
`checked`  tinyint(3) NULL DEFAULT NULL 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of log_mail
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_rename`
-- ----------------------------
DROP TABLE IF EXISTS `log_rename`;
CREATE TABLE `log_rename` (
`guid`  int(11) UNSIGNED NOT NULL ,
`date`  datetime NOT NULL ,
`oldName`  tinytext CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ,
`newName`  tinytext CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of log_rename
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_store_gold`
-- ----------------------------
DROP TABLE IF EXISTS `log_store_gold`;
CREATE TABLE `log_store_gold` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`transaction`  int(11) NOT NULL DEFAULT 0 ,
`guid`  int(11) NOT NULL DEFAULT 0 ,
`gold`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of log_store_gold
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_store_item`
-- ----------------------------
DROP TABLE IF EXISTS `log_store_item`;
CREATE TABLE `log_store_item` (
`id`  int(11) NOT NULL DEFAULT 0 ,
`transaction`  int(11) NULL DEFAULT 0 ,
`guid`  int(11) NULL DEFAULT 0 ,
`itemid`  int(11) NULL DEFAULT 0 ,
`count`  int(5) NULL DEFAULT 1 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of log_store_item
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_trade`
-- ----------------------------
DROP TABLE IF EXISTS `log_trade`;
CREATE TABLE `log_trade` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`date`  datetime NOT NULL ,
`sc_accountid`  int(11) NULL DEFAULT NULL ,
`sc_guid`  int(11) NULL DEFAULT NULL ,
`sc_name`  text CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL ,
`tar_accountid`  int(11) NULL DEFAULT NULL ,
`tar_guid`  int(11) NULL DEFAULT NULL ,
`tar_name`  text CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL ,
`item_name`  tinytext CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL ,
`item_entry`  int(11) NULL DEFAULT NULL ,
`item_count`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of log_trade
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `mail`
-- ----------------------------
DROP TABLE IF EXISTS `mail`;
CREATE TABLE `mail` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Identifier' ,
`messageType`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`stationery`  tinyint(3) NOT NULL DEFAULT 41 ,
`mailTemplateId`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`sender`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Character Global Unique Identifier' ,
`receiver`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Character Global Unique Identifier' ,
`subject`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`body`  longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
`has_items`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`expire_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`deliver_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`money`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`cod`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`checked`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Mail System'

;

-- ----------------------------
-- Records of mail
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `mail_items`
-- ----------------------------
DROP TABLE IF EXISTS `mail_items`;
CREATE TABLE `mail_items` (
`mail_id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`item_guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`receiver`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Character Global Unique Identifier' ,
PRIMARY KEY (`item_guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of mail_items
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `pet_aura`
-- ----------------------------
DROP TABLE IF EXISTS `pet_aura`;
CREATE TABLE `pet_aura` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`caster_guid`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Full Global Unique Identifier' ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 ,
`effect_mask`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`recalculate_mask`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`stackcount`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
`maxduration`  int(11) NOT NULL DEFAULT 0 ,
`remaintime`  int(11) NOT NULL DEFAULT 0 ,
`remaincharges`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`, `effect_mask`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Pet System'

;

-- ----------------------------
-- Records of pet_aura
-- ----------------------------
BEGIN;
INSERT INTO `pet_aura` VALUES ('2', '0', '0', '32752', '1', '0', '1', '5000', '75', '0'), ('5', '0', '0', '32752', '1', '0', '1', '5000', '24', '0'), ('9', '0', '0', '32752', '1', '0', '1', '5000', '99', '0'), ('11', '0', '0', '115232', '3', '0', '1', '30000', '15751', '0'), ('14', '0', '0', '32752', '1', '0', '1', '5000', '76', '0');
COMMIT;

-- ----------------------------
-- Table structure for `pet_aura_effect`
-- ----------------------------
DROP TABLE IF EXISTS `pet_aura_effect`;
CREATE TABLE `pet_aura_effect` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`slot`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`effect`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`amount`  int(11) NOT NULL DEFAULT 0 ,
`baseamount`  int(11) NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `slot`, `effect`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of pet_aura_effect
-- ----------------------------
BEGIN;
INSERT INTO `pet_aura_effect` VALUES ('2', '0', '0', '1', '1'), ('5', '0', '0', '1', '1'), ('9', '0', '0', '1', '1'), ('11', '0', '0', '-20', '-20'), ('11', '0', '1', '0', '0'), ('14', '0', '0', '1', '1');
COMMIT;

-- ----------------------------
-- Table structure for `pet_spell`
-- ----------------------------
DROP TABLE IF EXISTS `pet_spell`;
CREATE TABLE `pet_spell` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Spell Identifier' ,
`active`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Pet System'

;

-- ----------------------------
-- Records of pet_spell
-- ----------------------------
BEGIN;
INSERT INTO `pet_spell` VALUES ('2', '3110', '193'), ('2', '32233', '1'), ('2', '115043', '1'), ('3', '3716', '193'), ('3', '17735', '129'), ('3', '32233', '1'), ('3', '115043', '1'), ('5', '3110', '193'), ('5', '32233', '1'), ('5', '101976', '1'), ('5', '115043', '1'), ('7', '3716', '193'), ('7', '17735', '193'), ('7', '32233', '1'), ('7', '101976', '1'), ('7', '115043', '1'), ('7', '118093', '1'), ('9', '6358', '193'), ('9', '7814', '193'), ('9', '32233', '1'), ('9', '101976', '1'), ('9', '115043', '1'), ('11', '3716', '193'), ('11', '17735', '193'), ('11', '32233', '1'), ('11', '101976', '1'), ('11', '115043', '1'), ('11', '115232', '193'), ('11', '118093', '1'), ('12', '6358', '129'), ('12', '7814', '129'), ('12', '7870', '129'), ('12', '32233', '1'), ('12', '101976', '1'), ('12', '115043', '1'), ('14', '19505', '129'), ('14', '32233', '1'), ('14', '54049', '129'), ('14', '101976', '1'), ('14', '115043', '1');
COMMIT;

-- ----------------------------
-- Table structure for `pet_spell_cooldown`
-- ----------------------------
DROP TABLE IF EXISTS `pet_spell_cooldown`;
CREATE TABLE `pet_spell_cooldown` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier, Low part' ,
`spell`  mediumint(8) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Spell Identifier' ,
`time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`, `spell`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of pet_spell_cooldown
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `petition`
-- ----------------------------
DROP TABLE IF EXISTS `petition`;
CREATE TABLE `petition` (
`ownerguid`  int(10) UNSIGNED NOT NULL ,
`petitionguid`  int(10) UNSIGNED NULL DEFAULT 0 ,
`name`  varchar(24) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`ownerguid`, `type`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild System'

;

-- ----------------------------
-- Records of petition
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `petition_sign`
-- ----------------------------
DROP TABLE IF EXISTS `petition_sign`;
CREATE TABLE `petition_sign` (
`ownerguid`  int(10) UNSIGNED NOT NULL ,
`petitionguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`playerguid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`player_account`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`type`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`petitionguid`, `playerguid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Guild System'

;

-- ----------------------------
-- Records of petition_sign
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `players_reports_status`
-- ----------------------------
DROP TABLE IF EXISTS `players_reports_status`;
CREATE TABLE `players_reports_status` (
`guid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`creation_time`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`average`  float NOT NULL DEFAULT 0 ,
`total_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`speed_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`fly_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`jump_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`waterwalk_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`teleportplane_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
`climb_reports`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of players_reports_status
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `pool_quest_save`
-- ----------------------------
DROP TABLE IF EXISTS `pool_quest_save`;
CREATE TABLE `pool_quest_save` (
`pool_id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`quest_id`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`pool_id`, `quest_id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of pool_quest_save
-- ----------------------------
BEGIN;
INSERT INTO `pool_quest_save` VALUES ('349', '14105'), ('350', '13889'), ('351', '13916'), ('352', '11377'), ('353', '11666'), ('354', '13424'), ('356', '11362'), ('357', '11364'), ('358', '25160'), ('359', '25156'), ('360', '29362'), ('361', '26226'), ('362', '29315'), ('363', '26153'), ('364', '29356'), ('365', '29313'), ('366', '26588'), ('367', '29349'), ('368', '29361'), ('369', '26536'), ('370', '29342'), ('371', '29323'), ('372', '28063'), ('372', '28065'), ('373', '27949'), ('373', '28046'), ('374', '27975'), ('374', '28275'), ('375', '27971'), ('375', '27972'), ('376', '28682'), ('376', '28686'), ('377', '28679'), ('377', '28684'), ('378', '28694'), ('378', '28696'), ('379', '28689'), ('379', '28693'), ('5662', '13675'), ('5663', '13762'), ('5664', '13769'), ('5665', '13773'), ('5666', '13779'), ('5667', '13785'), ('5668', '13666'), ('5669', '13603'), ('5670', '13743'), ('5671', '13748'), ('5672', '13758'), ('5673', '13754'), ('5674', '13101'), ('5675', '13116'), ('5676', '13833'), ('5677', '12960'), ('5678', '24586'), ('30333', '30337');
COMMIT;

-- ----------------------------
-- Table structure for `reserved_name`
-- ----------------------------
DROP TABLE IF EXISTS `reserved_name`;
CREATE TABLE `reserved_name` (
`name`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
PRIMARY KEY (`name`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Player Reserved Names'

;

-- ----------------------------
-- Records of reserved_name
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `store_gold`
-- ----------------------------
DROP TABLE IF EXISTS `store_gold`;
CREATE TABLE `store_gold` (
`guid`  int(11) UNSIGNED NOT NULL ,
`gold`  int(11) UNSIGNED NULL DEFAULT NULL ,
`transaction`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
PRIMARY KEY (`transaction`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of store_gold
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `store_item`
-- ----------------------------
DROP TABLE IF EXISTS `store_item`;
CREATE TABLE `store_item` (
`itemid`  int(11) NOT NULL DEFAULT 0 ,
`guid`  int(11) UNSIGNED NOT NULL ,
`count`  int(11) UNSIGNED NOT NULL ,
`transaction`  int(11) NOT NULL AUTO_INCREMENT ,
PRIMARY KEY (`transaction`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of store_item
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `store_level`
-- ----------------------------
DROP TABLE IF EXISTS `store_level`;
CREATE TABLE `store_level` (
`guid`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`level`  int(11) UNSIGNED NOT NULL DEFAULT 80 ,
`transaction`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
PRIMARY KEY (`transaction`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of store_level
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `store_metier`
-- ----------------------------
DROP TABLE IF EXISTS `store_metier`;
CREATE TABLE `store_metier` (
`guid`  int(11) UNSIGNED NOT NULL ,
`skill`  int(11) UNSIGNED NOT NULL ,
`value`  int(11) UNSIGNED NOT NULL ,
`transaction`  int(11) UNSIGNED NOT NULL AUTO_INCREMENT ,
PRIMARY KEY (`transaction`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of store_metier
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `time_diff_log`
-- ----------------------------
DROP TABLE IF EXISTS `time_diff_log`;
CREATE TABLE `time_diff_log` (
`id`  int(10) NOT NULL AUTO_INCREMENT ,
`time`  int(10) UNSIGNED NULL DEFAULT 0 ,
`average`  int(10) UNSIGNED NULL DEFAULT 0 ,
`max`  int(10) UNSIGNED NULL DEFAULT 0 ,
`players`  int(10) UNSIGNED NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
AUTO_INCREMENT=3020

;

-- ----------------------------
-- Records of time_diff_log
-- ----------------------------
BEGIN;
INSERT INTO `time_diff_log` VALUES ('1', '1440186820', '25', '75', '0'), ('2', '1440186880', '25', '125', '0'), ('3', '1440186940', '25', '577', '0'), ('4', '1440187000', '25', '484', '0'), ('5', '1440187060', '25', '84', '0'), ('6', '1440187120', '24', '44', '0'), ('7', '1440187180', '25', '48', '0'), ('8', '1440187240', '25', '391', '0'), ('9', '1440187300', '25', '47', '0'), ('10', '1440187360', '24', '42', '0'), ('11', '1440187420', '25', '46', '0'), ('12', '1440188930', '24', '58', '0'), ('13', '1440188990', '25', '78', '0'), ('14', '1440189050', '25', '449', '0'), ('15', '1440189241', '25', '143', '1'), ('16', '1440189301', '25', '1087', '1'), ('17', '1440189361', '25', '829', '1'), ('18', '1440189421', '25', '635', '1'), ('19', '1440189481', '25', '59', '1'), ('20', '1440189541', '25', '476', '1'), ('21', '1440189601', '25', '129', '1'), ('22', '1440189661', '25', '873', '1'), ('23', '1440189721', '25', '494', '1'), ('24', '1440189781', '25', '49', '1'), ('25', '1440189841', '25', '38', '1'), ('26', '1440189901', '24', '36', '1'), ('27', '1440189961', '25', '35', '1'), ('28', '1440190021', '25', '37', '1'), ('29', '1440190081', '25', '104', '1'), ('30', '1440190141', '25', '45', '1'), ('31', '1440190201', '25', '43', '1'), ('32', '1440190261', '25', '51', '1'), ('33', '1440190321', '25', '39', '1'), ('34', '1440190381', '24', '42', '1'), ('35', '1440190441', '25', '167', '1'), ('36', '1440190501', '25', '663', '1'), ('37', '1440190561', '25', '51', '1'), ('38', '1440190621', '25', '38', '1'), ('39', '1440190681', '25', '824', '1'), ('40', '1440190741', '25', '39', '1'), ('41', '1440190801', '25', '46', '1'), ('42', '1440190861', '25', '42', '1'), ('43', '1440190921', '24', '43', '1'), ('44', '1440190981', '25', '133', '1'), ('45', '1440191041', '25', '44', '1'), ('46', '1440191101', '25', '62', '1'), ('47', '1440191161', '25', '837', '1'), ('48', '1440191221', '24', '37', '1'), ('49', '1440191281', '24', '36', '1'), ('50', '1440191341', '25', '38', '0'), ('51', '1462202052', '25', '188', '0'), ('52', '1462202112', '25', '406', '0'), ('53', '1462202172', '25', '93', '0'), ('54', '1462202232', '25', '62', '0'), ('55', '1462202292', '25', '62', '0'), ('56', '1462202352', '25', '281', '0'), ('57', '1462202412', '25', '32', '0'), ('58', '1462202472', '25', '78', '0'), ('59', '1462202532', '25', '347', '0'), ('60', '1462202592', '25', '67', '1'), ('61', '1462202652', '25', '960', '1'), ('62', '1462202712', '25', '56', '1'), ('63', '1462202772', '25', '34', '1'), ('64', '1462202832', '25', '491', '1'), ('65', '1462202892', '25', '49', '1'), ('66', '1462202952', '24', '35', '1'), ('67', '1462203012', '25', '39', '1'), ('68', '1462203072', '25', '41', '1'), ('69', '1462203132', '25', '36', '1'), ('70', '1462203192', '25', '248', '1'), ('71', '1462203252', '25', '36', '1'), ('72', '1462203312', '25', '37', '1'), ('73', '1462203372', '24', '49', '1'), ('74', '1462203432', '25', '36', '1'), ('75', '1462203492', '25', '34', '1'), ('76', '1462203552', '24', '35', '1'), ('77', '1462203612', '25', '36', '1'), ('78', '1462203672', '25', '39', '1'), ('79', '1462203732', '25', '36', '1'), ('80', '1462203792', '25', '47', '1'), ('81', '1462203852', '25', '41', '1'), ('82', '1462203912', '25', '37', '1'), ('83', '1462203972', '25', '32', '1'), ('84', '1462204032', '24', '36', '1'), ('85', '1462204092', '25', '35', '1'), ('86', '1462204152', '25', '37', '1'), ('87', '1462204212', '25', '37', '1'), ('88', '1462204272', '25', '43', '1'), ('89', '1462204332', '25', '37', '1'), ('90', '1462204392', '24', '33', '1'), ('91', '1462204452', '25', '99', '1'), ('92', '1462204512', '25', '43', '1'), ('93', '1462204572', '25', '56', '1'), ('94', '1462204632', '25', '71', '1'), ('95', '1462204692', '24', '49', '1'), ('96', '1462204752', '25', '38', '1'), ('97', '1462204812', '25', '36', '1'), ('98', '1462204872', '24', '38', '1'), ('99', '1462204932', '25', '36', '1'), ('100', '1462204992', '25', '31', '1');
INSERT INTO `time_diff_log` VALUES ('101', '1462205052', '25', '49', '1'), ('102', '1462205112', '25', '40', '1'), ('103', '1462205172', '25', '47', '1'), ('104', '1462205232', '25', '44', '1'), ('105', '1462205292', '25', '36', '1'), ('106', '1462205352', '25', '39', '1'), ('107', '1462205412', '25', '35', '1'), ('108', '1462205473', '24', '38', '1'), ('109', '1462205533', '25', '37', '1'), ('110', '1462205593', '25', '51', '1'), ('111', '1462205653', '25', '39', '1'), ('112', '1462205713', '25', '36', '1'), ('113', '1462205773', '25', '35', '1'), ('114', '1462205833', '25', '38', '1'), ('115', '1462205893', '24', '39', '1'), ('116', '1462205953', '25', '41', '1'), ('117', '1462206013', '25', '52', '1'), ('118', '1462206073', '25', '35', '1'), ('119', '1462206133', '24', '36', '1'), ('120', '1462206193', '25', '35', '1'), ('121', '1462206253', '25', '39', '1'), ('122', '1462206313', '25', '40', '1'), ('123', '1462206373', '25', '36', '1'), ('124', '1462206433', '24', '34', '1'), ('125', '1462206493', '25', '50', '1'), ('126', '1462206553', '25', '557', '1'), ('127', '1462206613', '25', '292', '1'), ('128', '1462206673', '25', '34', '1'), ('129', '1462206733', '24', '37', '1'), ('130', '1462206793', '25', '338', '1'), ('131', '1462206853', '25', '83', '1'), ('132', '1462206913', '25', '48', '1'), ('133', '1462206973', '25', '34', '1'), ('134', '1462207033', '24', '36', '1'), ('135', '1462207093', '25', '34', '1'), ('136', '1462207153', '24', '36', '1'), ('137', '1462207213', '25', '36', '1'), ('138', '1462207273', '25', '39', '1'), ('139', '1462207333', '25', '37', '1'), ('140', '1462207393', '25', '47', '1'), ('141', '1462207453', '25', '37', '1'), ('142', '1462207513', '25', '34', '1'), ('143', '1462207573', '24', '40', '1'), ('144', '1462207633', '25', '37', '1'), ('145', '1462207693', '25', '38', '1'), ('146', '1462207753', '25', '37', '1'), ('147', '1462207813', '25', '48', '1'), ('148', '1462207873', '25', '105', '1'), ('149', '1462207933', '24', '37', '1'), ('150', '1462207993', '25', '34', '1'), ('151', '1462208053', '25', '36', '1'), ('152', '1462208113', '25', '37', '1'), ('153', '1462208173', '25', '36', '1'), ('154', '1462208233', '25', '38', '1'), ('155', '1462208293', '25', '49', '1'), ('156', '1462208353', '25', '46', '1'), ('157', '1462208413', '25', '48', '1'), ('158', '1462208473', '25', '45', '1'), ('159', '1462208533', '24', '44', '1'), ('160', '1462208593', '25', '44', '1'), ('161', '1462208653', '25', '46', '1'), ('162', '1462208713', '25', '137', '1'), ('163', '1462208773', '24', '36', '1'), ('164', '1462208833', '24', '38', '1'), ('165', '1462208893', '25', '574', '1'), ('166', '1462208953', '24', '38', '1'), ('167', '1462209013', '25', '39', '1'), ('168', '1462209073', '25', '45', '1'), ('169', '1462209133', '25', '35', '1'), ('170', '1462209193', '24', '50', '1'), ('171', '1462209253', '25', '47', '1'), ('172', '1462209313', '24', '35', '1'), ('173', '1462209373', '25', '38', '1'), ('174', '1462209433', '25', '41', '1'), ('175', '1462209493', '25', '118', '1'), ('176', '1462209553', '25', '54', '1'), ('177', '1462209613', '25', '46', '1'), ('178', '1462209673', '25', '62', '1'), ('179', '1462209733', '25', '35', '1'), ('180', '1462209793', '24', '36', '1'), ('181', '1462209853', '25', '36', '1'), ('182', '1462209913', '25', '30', '1'), ('183', '1462209973', '24', '37', '1'), ('184', '1462210033', '25', '47', '1'), ('185', '1462210093', '24', '32', '1'), ('186', '1462210153', '25', '173', '1'), ('187', '1462210213', '25', '39', '1'), ('188', '1462210273', '25', '33', '1'), ('189', '1462210333', '25', '35', '1'), ('190', '1462210393', '25', '35', '1'), ('191', '1462210453', '25', '38', '1'), ('192', '1462210513', '25', '47', '1'), ('193', '1462210573', '25', '37', '1'), ('194', '1462210633', '24', '35', '1'), ('195', '1462210693', '25', '33', '1'), ('196', '1462210753', '24', '37', '1'), ('197', '1462210813', '25', '37', '1'), ('198', '1462210873', '25', '83', '1'), ('199', '1462210933', '25', '47', '1'), ('200', '1462210993', '24', '36', '1');
INSERT INTO `time_diff_log` VALUES ('201', '1462211053', '25', '40', '1'), ('202', '1462211113', '24', '34', '1'), ('203', '1462211173', '24', '37', '1'), ('204', '1462211233', '25', '41', '1'), ('205', '1462211293', '25', '32', '1'), ('206', '1462211353', '25', '34', '1'), ('207', '1462211413', '25', '48', '1'), ('208', '1462211473', '24', '37', '1'), ('209', '1462211533', '25', '35', '1'), ('210', '1462211593', '25', '37', '1'), ('211', '1462211653', '25', '37', '1'), ('212', '1462211713', '25', '55', '1'), ('213', '1462211773', '25', '65', '1'), ('214', '1462211833', '25', '48', '1'), ('215', '1462211893', '25', '31', '1'), ('216', '1462211953', '25', '36', '1'), ('217', '1462212013', '25', '40', '1'), ('218', '1462212073', '25', '38', '1'), ('219', '1462212133', '25', '36', '1'), ('220', '1462212193', '25', '35', '1'), ('221', '1462212253', '24', '37', '1'), ('222', '1462212313', '25', '49', '1'), ('223', '1462212373', '25', '33', '1'), ('224', '1462212433', '24', '37', '1'), ('225', '1462212494', '25', '33', '1'), ('226', '1462212554', '24', '39', '1'), ('227', '1462212614', '25', '37', '1'), ('228', '1462212674', '25', '37', '1'), ('229', '1462212734', '25', '50', '1'), ('230', '1462212794', '25', '178', '1'), ('231', '1462212854', '25', '44', '1'), ('232', '1462212914', '24', '32', '1'), ('233', '1462212974', '25', '33', '1'), ('234', '1462213034', '25', '38', '1'), ('235', '1462213094', '25', '35', '1'), ('236', '1462213154', '25', '49', '1'), ('237', '1462213214', '25', '36', '1'), ('238', '1462213274', '25', '36', '1'), ('239', '1462213334', '24', '36', '1'), ('240', '1462213394', '25', '33', '1'), ('241', '1462213454', '25', '85', '1'), ('242', '1462213514', '25', '37', '1'), ('243', '1462213574', '25', '37', '1'), ('244', '1462213634', '25', '47', '1'), ('245', '1462213694', '25', '37', '1'), ('246', '1462213754', '25', '40', '1'), ('247', '1462213814', '25', '35', '1'), ('248', '1462213874', '24', '42', '1'), ('249', '1462213934', '25', '39', '1'), ('250', '1462213994', '25', '32', '1'), ('251', '1462214054', '25', '193', '1'), ('252', '1462214114', '25', '37', '1'), ('253', '1462214174', '24', '38', '1'), ('254', '1462214234', '24', '40', '1'), ('255', '1462214294', '25', '592', '1'), ('256', '1462214354', '25', '100', '1'), ('257', '1462214414', '25', '38', '1'), ('258', '1462214474', '25', '37', '1'), ('259', '1462214534', '25', '49', '1'), ('260', '1462214594', '24', '34', '1'), ('261', '1462214654', '25', '1085', '1'), ('262', '1462214714', '25', '121', '1'), ('263', '1462214774', '25', '138', '1'), ('264', '1462308563', '0', '0', '0'), ('265', '1462308623', '32', '6955', '1'), ('266', '1462308683', '25', '748', '1'), ('267', '1462308744', '25', '56', '1'), ('268', '1462308804', '25', '70', '1'), ('269', '1462308864', '25', '43', '1'), ('270', '1462308924', '24', '46', '1'), ('271', '1462308984', '25', '595', '1'), ('272', '1462309044', '26', '2336', '1'), ('273', '1462309104', '25', '33', '1'), ('274', '1462309164', '25', '865', '1'), ('275', '1462309224', '25', '32', '1'), ('276', '1462309284', '25', '614', '1'), ('277', '1462309344', '25', '68', '1'), ('278', '1462309404', '24', '47', '1'), ('279', '1462309464', '25', '41', '1'), ('280', '1462309524', '25', '52', '0'), ('281', '1462309584', '25', '46', '0'), ('282', '1462378098', '25', '194', '0'), ('283', '1462378158', '25', '370', '1'), ('284', '1462378218', '26', '1713', '1'), ('285', '1462378278', '26', '2658', '1'), ('286', '1462378338', '25', '84', '1'), ('287', '1462378398', '25', '312', '1'), ('288', '1462378458', '25', '55', '1'), ('289', '1462378518', '25', '1312', '1'), ('290', '1462378578', '25', '45', '1'), ('291', '1462378638', '25', '134', '1'), ('292', '1462378698', '25', '39', '1'), ('293', '1462378758', '24', '35', '1'), ('294', '1462378818', '25', '44', '1'), ('295', '1462378878', '24', '46', '1'), ('296', '1462378938', '25', '36', '1'), ('297', '1462378998', '25', '37', '1'), ('298', '1462379058', '25', '38', '1'), ('299', '1462379118', '25', '157', '1'), ('300', '1462379652', '0', '0', '0');
INSERT INTO `time_diff_log` VALUES ('301', '1462379850', '25', '782', '1'), ('302', '1462379910', '26', '2142', '1'), ('303', '1462379970', '25', '364', '1'), ('304', '1462380030', '25', '364', '1'), ('305', '1462380090', '25', '52', '1'), ('306', '1462380150', '25', '236', '1'), ('307', '1462380210', '25', '128', '1'), ('308', '1462380270', '25', '327', '1'), ('309', '1462380330', '25', '35', '1'), ('310', '1462380390', '24', '35', '1'), ('311', '1462380450', '25', '2197', '1'), ('312', '1462380510', '25', '57', '1'), ('313', '1462380570', '25', '36', '1'), ('314', '1462380630', '25', '39', '1'), ('315', '1462380690', '25', '48', '1'), ('316', '1462380750', '25', '44', '1'), ('317', '1462380810', '25', '38', '1'), ('318', '1462380870', '24', '38', '1'), ('319', '1462380930', '25', '39', '1'), ('320', '1462380990', '25', '49', '1'), ('321', '1462381050', '25', '39', '1'), ('322', '1462381110', '25', '35', '1'), ('323', '1462381170', '25', '170', '1'), ('324', '1462381230', '25', '37', '1'), ('325', '1462381290', '25', '35', '1'), ('326', '1462381350', '25', '39', '1'), ('327', '1462381410', '25', '322', '1'), ('328', '1462381470', '25', '329', '1'), ('329', '1462381530', '25', '40', '1'), ('330', '1462381590', '25', '178', '1'), ('331', '1462381650', '25', '39', '1'), ('332', '1462381710', '25', '743', '1'), ('333', '1462381770', '25', '36', '1'), ('334', '1462381830', '24', '40', '1'), ('335', '1462381890', '25', '39', '1'), ('336', '1462381950', '25', '41', '1'), ('337', '1462382010', '25', '38', '1'), ('338', '1462382070', '24', '48', '1'), ('339', '1462382130', '25', '38', '1'), ('340', '1462382190', '25', '728', '1'), ('341', '1462382250', '25', '67', '1'), ('342', '1462382310', '25', '35', '1'), ('343', '1462382370', '25', '35', '1'), ('344', '1462382430', '25', '35', '1'), ('345', '1462382490', '25', '46', '1'), ('346', '1462382550', '25', '36', '1'), ('347', '1462382610', '25', '32', '1'), ('348', '1462382670', '25', '36', '1'), ('349', '1462382730', '24', '35', '1'), ('350', '1462382790', '25', '32', '1'), ('351', '1462382850', '24', '36', '1'), ('352', '1462382910', '25', '36', '1'), ('353', '1462382970', '25', '47', '1'), ('354', '1462383030', '25', '37', '1'), ('355', '1462383090', '25', '36', '1'), ('356', '1462383150', '24', '40', '1'), ('357', '1462383210', '25', '33', '1'), ('358', '1462383270', '24', '37', '1'), ('359', '1462383330', '25', '35', '1'), ('360', '1462383390', '25', '47', '1'), ('361', '1462383450', '25', '36', '1'), ('362', '1462383510', '25', '36', '1'), ('363', '1462383570', '24', '32', '1'), ('364', '1462383630', '25', '39', '1'), ('365', '1462383690', '25', '36', '1'), ('366', '1462383750', '25', '36', '1'), ('367', '1462383810', '25', '487', '1'), ('368', '1462384400', '25', '63', '0'), ('369', '1462384460', '25', '118', '0'), ('370', '1462384520', '25', '47', '0'), ('371', '1462384580', '25', '109', '0'), ('372', '1462384640', '24', '49', '0'), ('373', '1462384700', '25', '34', '1'), ('374', '1462384760', '25', '41', '1'), ('375', '1462384820', '24', '47', '1'), ('376', '1462384880', '25', '57', '1'), ('377', '1462384940', '24', '36', '1'), ('378', '1462385000', '25', '84', '1'), ('379', '1462385060', '24', '33', '1'), ('380', '1462385120', '25', '521', '1'), ('381', '1462385180', '25', '38', '1'), ('382', '1462385240', '24', '46', '1'), ('383', '1462385300', '25', '51', '1'), ('384', '1462385360', '25', '883', '1'), ('385', '1462385420', '25', '41', '1'), ('386', '1462385480', '25', '41', '1'), ('387', '1462385540', '25', '1052', '1'), ('388', '1462385600', '24', '40', '1'), ('389', '1462385660', '25', '38', '1'), ('390', '1462385720', '25', '365', '1'), ('391', '1462385780', '25', '38', '1'), ('392', '1462385840', '24', '37', '1'), ('393', '1462385900', '25', '38', '1'), ('394', '1462385960', '25', '38', '1'), ('395', '1462386020', '24', '37', '1'), ('396', '1462386080', '25', '825', '1'), ('397', '1462386140', '25', '45', '1'), ('398', '1462386200', '25', '39', '1'), ('399', '1462386260', '25', '33', '1'), ('400', '1462386320', '25', '33', '1');
INSERT INTO `time_diff_log` VALUES ('401', '1462386380', '24', '36', '1'), ('402', '1462386440', '25', '35', '1'), ('403', '1462386500', '25', '36', '1'), ('404', '1462386560', '25', '35', '1'), ('405', '1462386620', '25', '42', '1'), ('406', '1462386680', '25', '36', '1'), ('407', '1462386740', '24', '32', '1'), ('408', '1462386800', '25', '39', '1'), ('409', '1462386860', '25', '35', '1'), ('410', '1462386920', '25', '54', '1'), ('411', '1462386980', '25', '37', '1'), ('412', '1462387040', '25', '46', '1'), ('413', '1462387100', '25', '37', '1'), ('414', '1462387160', '24', '37', '1'), ('415', '1462387220', '25', '323', '1'), ('416', '1462387280', '25', '52', '1'), ('417', '1462387340', '25', '30', '1'), ('418', '1462387400', '24', '35', '1'), ('419', '1462387460', '25', '37', '1'), ('420', '1462387520', '25', '46', '1'), ('421', '1462387580', '25', '42', '1'), ('422', '1462387640', '25', '39', '1'), ('423', '1462387700', '25', '37', '1'), ('424', '1462387760', '25', '33', '1'), ('425', '1462387820', '25', '36', '1'), ('426', '1462387880', '25', '36', '1'), ('427', '1462387940', '25', '50', '1'), ('428', '1462388448', '24', '62', '0'), ('429', '1462388508', '25', '89', '1'), ('430', '1462388568', '25', '58', '1'), ('431', '1462388628', '25', '40', '1'), ('432', '1462388688', '25', '49', '1'), ('433', '1462388748', '25', '35', '1'), ('434', '1462388808', '25', '37', '1'), ('435', '1462388868', '25', '73', '1'), ('436', '1462388928', '24', '37', '1'), ('437', '1462388988', '25', '37', '1'), ('438', '1462389048', '25', '39', '1'), ('439', '1462389108', '25', '35', '1'), ('440', '1462389168', '25', '156', '1'), ('441', '1462389228', '25', '388', '1'), ('442', '1462389288', '24', '50', '1'), ('443', '1462389348', '25', '48', '1'), ('444', '1462389408', '25', '40', '1'), ('445', '1462389468', '25', '40', '1'), ('446', '1462389528', '24', '41', '1'), ('447', '1462389588', '25', '35', '1'), ('448', '1462389648', '24', '40', '1'), ('449', '1462389708', '25', '67', '1'), ('450', '1462389768', '25', '46', '1'), ('451', '1462389828', '25', '66', '1'), ('452', '1462389888', '25', '59', '1'), ('453', '1462389948', '25', '42', '1'), ('454', '1462390008', '25', '44', '1'), ('455', '1462390068', '25', '36', '1'), ('456', '1462390128', '24', '40', '1'), ('457', '1462390188', '25', '48', '1'), ('458', '1462390248', '24', '39', '1'), ('459', '1462390308', '25', '37', '1'), ('460', '1462390368', '24', '35', '1'), ('461', '1462390428', '25', '40', '1'), ('462', '1462390488', '25', '1057', '1'), ('463', '1462390548', '25', '40', '1'), ('464', '1462390608', '25', '50', '1'), ('465', '1462390668', '25', '47', '1'), ('466', '1462390728', '24', '38', '1'), ('467', '1462390788', '25', '34', '1'), ('468', '1462390848', '25', '38', '1'), ('469', '1462390908', '24', '37', '1'), ('470', '1462390968', '25', '37', '1'), ('471', '1462391028', '24', '38', '1'), ('472', '1462391088', '25', '46', '1'), ('473', '1462391148', '24', '39', '1'), ('474', '1462391208', '25', '39', '1'), ('475', '1462391268', '25', '36', '1'), ('476', '1462391328', '25', '38', '1'), ('477', '1462391388', '25', '36', '1'), ('478', '1462391448', '25', '57', '1'), ('479', '1462785310', '0', '0', '0'), ('480', '1462785370', '33', '8558', '1'), ('481', '1462785430', '27', '2307', '1'), ('482', '1462785490', '25', '63', '1'), ('483', '1462785550', '25', '76', '1'), ('484', '1462785610', '25', '670', '1'), ('485', '1462785670', '24', '38', '1'), ('486', '1462785730', '25', '1123', '1'), ('487', '1462785790', '25', '70', '1'), ('488', '1462785850', '25', '157', '1'), ('489', '1462785910', '25', '424', '1'), ('490', '1462785970', '25', '359', '1'), ('491', '1462786030', '25', '36', '1'), ('492', '1462786090', '24', '38', '1'), ('493', '1462786150', '25', '166', '1'), ('494', '1462786210', '24', '52', '1'), ('495', '1462786270', '25', '38', '1'), ('496', '1462786330', '25', '650', '1'), ('497', '1462786390', '25', '37', '1'), ('498', '1462786450', '25', '480', '1'), ('499', '1462786510', '25', '40', '1'), ('500', '1462786570', '25', '37', '1');
INSERT INTO `time_diff_log` VALUES ('501', '1462786630', '24', '47', '1'), ('502', '1462786690', '25', '37', '1'), ('503', '1462786750', '24', '35', '1'), ('504', '1462786810', '25', '39', '1'), ('505', '1462786870', '25', '35', '1'), ('506', '1462786930', '25', '37', '1'), ('507', '1462786990', '25', '37', '1'), ('508', '1462787050', '25', '46', '1'), ('509', '1462787110', '25', '38', '1'), ('510', '1462787170', '25', '53', '1'), ('511', '1462787230', '25', '727', '1'), ('512', '1462787290', '25', '36', '1'), ('513', '1462787350', '25', '38', '1'), ('514', '1462787410', '25', '39', '1'), ('515', '1462787470', '25', '45', '1'), ('516', '1462787530', '25', '38', '1'), ('517', '1462787590', '25', '36', '1'), ('518', '1462787650', '25', '47', '1'), ('519', '1462787710', '25', '38', '1'), ('520', '1462787770', '24', '30', '1'), ('521', '1462787830', '25', '39', '1'), ('522', '1462787890', '25', '42', '1'), ('523', '1463422327', '0', '0', '0'), ('524', '1463422387', '28', '2863', '0'), ('525', '1463422447', '25', '1414', '1'), ('526', '1463422507', '26', '1408', '1'), ('527', '1463422567', '25', '67', '1'), ('528', '1463422627', '25', '38', '1'), ('529', '1463422687', '25', '601', '1'), ('530', '1463422747', '25', '488', '1'), ('531', '1463422807', '25', '50', '1'), ('532', '1463422867', '25', '52', '1'), ('533', '1463422927', '24', '50', '1'), ('534', '1463422987', '25', '37', '1'), ('535', '1463423047', '25', '525', '1'), ('536', '1463423107', '25', '51', '1'), ('537', '1463423167', '25', '161', '1'), ('538', '1463423227', '24', '44', '1'), ('539', '1463423287', '25', '43', '1'), ('540', '1463423347', '24', '48', '1'), ('541', '1463423407', '25', '49', '1'), ('542', '1463423467', '25', '45', '1'), ('543', '1463423527', '24', '43', '1'), ('544', '1463423587', '25', '60', '1'), ('545', '1463423647', '25', '48', '1'), ('546', '1463423707', '24', '45', '1'), ('547', '1463423767', '25', '42', '1'), ('548', '1463423827', '24', '46', '1'), ('549', '1463423887', '25', '45', '1'), ('550', '1463423947', '24', '43', '1'), ('551', '1463424007', '25', '37', '1'), ('552', '1463424067', '25', '60', '1'), ('553', '1463424127', '24', '48', '1'), ('554', '1463424187', '25', '43', '1'), ('555', '1463424247', '24', '43', '1'), ('556', '1463424307', '25', '46', '1'), ('557', '1463424367', '25', '50', '1'), ('558', '1463424427', '25', '44', '1'), ('559', '1463424487', '25', '220', '1'), ('560', '1463424547', '25', '49', '1'), ('561', '1463424607', '25', '44', '1'), ('562', '1463424667', '25', '42', '1'), ('563', '1463424727', '24', '46', '1'), ('564', '1463424787', '25', '35', '1'), ('565', '1463424847', '25', '44', '1'), ('566', '1463424907', '24', '44', '1'), ('567', '1463424967', '25', '54', '1'), ('568', '1463425027', '25', '46', '1'), ('569', '1463425087', '25', '58', '0'), ('570', '1463425687', '24', '37', '0'), ('571', '1463425747', '25', '1249', '0'), ('572', '1463425807', '25', '619', '0'), ('573', '1463425867', '25', '349', '0'), ('574', '1463425927', '25', '45', '0'), ('575', '1463425987', '24', '43', '0'), ('576', '1463426047', '25', '843', '0'), ('577', '1463426107', '25', '271', '0'), ('578', '1463426167', '25', '650', '0'), ('579', '1463426227', '24', '38', '0'), ('580', '1463426287', '25', '33', '0'), ('581', '1463426347', '24', '30', '0'), ('582', '1463426407', '25', '32', '0'), ('583', '1463426467', '25', '35', '0'), ('584', '1463426527', '25', '56', '0'), ('585', '1463426587', '25', '43', '0'), ('586', '1463426647', '24', '32', '0'), ('587', '1463426707', '25', '35', '0'), ('588', '1463426767', '25', '250', '0'), ('589', '1463426827', '25', '186', '0'), ('590', '1463426887', '25', '34', '0'), ('591', '1463426947', '25', '33', '0'), ('592', '1463427007', '25', '44', '0'), ('593', '1463427067', '25', '38', '0'), ('594', '1463427127', '24', '33', '0'), ('595', '1463427187', '25', '34', '0'), ('596', '1463427247', '25', '33', '0'), ('597', '1463427307', '24', '35', '0'), ('598', '1463427368', '25', '34', '0'), ('599', '1463427428', '25', '40', '0'), ('600', '1463427488', '25', '34', '0');
INSERT INTO `time_diff_log` VALUES ('601', '1463427548', '25', '38', '0'), ('602', '1463427608', '24', '30', '0'), ('603', '1463427668', '25', '36', '0'), ('604', '1463427728', '25', '34', '0'), ('605', '1463427788', '24', '34', '0'), ('606', '1463427848', '25', '33', '0'), ('607', '1463427908', '25', '156', '0'), ('608', '1463427968', '26', '2258', '1'), ('609', '1463428028', '25', '80', '1'), ('610', '1463428088', '24', '49', '1'), ('611', '1463428148', '25', '66', '1'), ('612', '1463428208', '25', '42', '1'), ('613', '1463428268', '24', '37', '1'), ('614', '1463428328', '25', '53', '1'), ('615', '1463428388', '24', '39', '1'), ('616', '1463428448', '25', '51', '1'), ('617', '1463428508', '25', '43', '1'), ('618', '1463428568', '25', '44', '1'), ('619', '1463428628', '25', '34', '1'), ('620', '1463428688', '25', '101', '1'), ('621', '1463428748', '24', '43', '1'), ('622', '1463429094', '25', '1071', '1'), ('623', '1463429154', '25', '164', '1'), ('624', '1463429214', '25', '85', '1'), ('625', '1463429274', '25', '51', '1'), ('626', '1463429334', '25', '67', '1'), ('627', '1463429394', '25', '53', '1'), ('628', '1463429454', '25', '148', '1'), ('629', '1463429514', '25', '305', '0'), ('630', '1463430199', '0', '0', '0'), ('631', '1463430259', '30', '3458', '1'), ('632', '1463430319', '28', '4424', '1'), ('633', '1463430379', '25', '660', '1'), ('634', '1463430439', '25', '61', '1'), ('635', '1463430499', '25', '51', '1'), ('636', '1463430559', '25', '1196', '1'), ('637', '1463468256', '25', '84', '0'), ('638', '1463468316', '25', '371', '0'), ('639', '1463468376', '25', '803', '1'), ('640', '1463468436', '25', '925', '1'), ('641', '1463468496', '25', '89', '1'), ('642', '1463468556', '25', '219', '1'), ('643', '1463468616', '25', '54', '1'), ('644', '1463468676', '25', '61', '1'), ('645', '1463468736', '25', '130', '1'), ('646', '1463468796', '25', '38', '1'), ('647', '1463468856', '25', '47', '1'), ('648', '1463468916', '25', '71', '1'), ('649', '1463468976', '25', '319', '1'), ('650', '1463469036', '25', '39', '1'), ('651', '1463469096', '24', '50', '1'), ('652', '1463469156', '25', '49', '1'), ('653', '1463469216', '24', '39', '1'), ('654', '1463469276', '24', '41', '1'), ('655', '1463469336', '25', '44', '1'), ('656', '1463469397', '24', '39', '1'), ('657', '1463469457', '25', '63', '1'), ('658', '1463469517', '25', '45', '1'), ('659', '1463469577', '25', '170', '1'), ('660', '1463469637', '25', '56', '1'), ('661', '1463469697', '25', '47', '1'), ('662', '1463469757', '25', '61', '1'), ('663', '1463469817', '25', '56', '1'), ('664', '1463469877', '25', '58', '1'), ('665', '1463469937', '25', '248', '1'), ('666', '1463469997', '25', '544', '1'), ('667', '1463470057', '25', '66', '1'), ('668', '1463470117', '25', '56', '1'), ('669', '1463470177', '25', '52', '1'), ('670', '1463470237', '25', '58', '1'), ('671', '1463470297', '25', '91', '1'), ('672', '1463470357', '25', '59', '1'), ('673', '1463470417', '25', '44', '1'), ('674', '1463470477', '25', '101', '1'), ('675', '1463470537', '25', '48', '1'), ('676', '1463470597', '25', '41', '1'), ('677', '1463470657', '25', '45', '1'), ('678', '1463470717', '25', '44', '1'), ('679', '1463470777', '25', '46', '1'), ('680', '1463470837', '25', '45', '1'), ('681', '1463470897', '25', '51', '1'), ('682', '1463470957', '25', '48', '1'), ('683', '1463471017', '25', '45', '1'), ('684', '1463471077', '25', '51', '1'), ('685', '1463471137', '25', '45', '1'), ('686', '1463471197', '24', '38', '1'), ('687', '1463471257', '25', '47', '1'), ('688', '1463471317', '25', '48', '1'), ('689', '1463471377', '25', '54', '1'), ('690', '1463471437', '25', '43', '1'), ('691', '1463471497', '25', '44', '1'), ('692', '1463471557', '25', '48', '1'), ('693', '1463471617', '24', '44', '1'), ('694', '1463471677', '25', '47', '1'), ('695', '1463471737', '25', '45', '1'), ('696', '1463471797', '25', '62', '1'), ('697', '1463471857', '25', '46', '1'), ('698', '1463471917', '25', '47', '1'), ('699', '1463471977', '24', '39', '1'), ('700', '1463472037', '25', '47', '1');
INSERT INTO `time_diff_log` VALUES ('701', '1463472097', '25', '47', '1'), ('702', '1463472157', '25', '46', '1'), ('703', '1463472217', '25', '67', '1'), ('704', '1463472277', '25', '44', '1'), ('705', '1463472337', '24', '48', '1'), ('706', '1463472397', '25', '42', '1'), ('707', '1463472457', '25', '45', '1'), ('708', '1463472517', '25', '238', '1'), ('709', '1463472577', '25', '49', '1'), ('710', '1463472637', '25', '172', '1'), ('711', '1463472697', '25', '50', '1'), ('712', '1463472757', '25', '43', '1'), ('713', '1463472817', '25', '53', '1'), ('714', '1463472877', '25', '67', '1'), ('715', '1463472937', '25', '58', '1'), ('716', '1463472997', '25', '46', '1'), ('717', '1463473057', '25', '60', '1'), ('718', '1463473117', '25', '63', '1'), ('719', '1463473177', '25', '54', '1'), ('720', '1463473237', '25', '51', '1'), ('721', '1463473297', '25', '164', '1'), ('722', '1463473357', '25', '61', '1'), ('723', '1463473417', '25', '67', '1'), ('724', '1463473477', '25', '56', '1'), ('725', '1463473537', '25', '50', '1'), ('726', '1463473597', '25', '57', '1'), ('727', '1463473657', '24', '49', '1'), ('728', '1463473717', '25', '56', '1'), ('729', '1463473777', '25', '49', '1'), ('730', '1463473837', '25', '65', '1'), ('731', '1463473897', '25', '50', '1'), ('732', '1463473957', '25', '45', '1'), ('733', '1463474017', '25', '113', '1'), ('734', '1463474077', '25', '46', '1'), ('735', '1463474138', '25', '65', '1'), ('736', '1463474198', '25', '51', '1'), ('737', '1463474258', '24', '51', '1'), ('738', '1463474318', '25', '52', '1'), ('739', '1463474378', '25', '62', '1'), ('740', '1463474438', '25', '53', '1'), ('741', '1463474498', '25', '71', '1'), ('742', '1463474558', '25', '61', '1'), ('743', '1463474618', '25', '65', '1'), ('744', '1463492526', '25', '193', '0'), ('745', '1463492586', '25', '353', '0'), ('746', '1463492646', '25', '484', '0'), ('747', '1463492706', '26', '3593', '0'), ('748', '1463492766', '25', '63', '0'), ('749', '1463492826', '25', '58', '1'), ('750', '1463492886', '24', '48', '1'), ('751', '1463492946', '25', '66', '1'), ('752', '1463493006', '25', '45', '1'), ('753', '1463493066', '25', '885', '1'), ('754', '1463493126', '25', '64', '1'), ('755', '1463493186', '25', '185', '1'), ('756', '1463493246', '25', '118', '1'), ('757', '1463493306', '25', '51', '1'), ('758', '1463493366', '25', '60', '1'), ('759', '1463493426', '25', '49', '1'), ('760', '1463493486', '25', '68', '1'), ('761', '1463493546', '25', '56', '1'), ('762', '1463493606', '25', '283', '1'), ('763', '1463493666', '25', '69', '1'), ('764', '1463493726', '25', '68', '1'), ('765', '1463493786', '25', '54', '1'), ('766', '1463493846', '25', '51', '1'), ('767', '1463493906', '25', '52', '1'), ('768', '1463493966', '25', '43', '1'), ('769', '1463494026', '25', '57', '1'), ('770', '1463494086', '25', '50', '1'), ('771', '1463494146', '25', '50', '1'), ('772', '1463494206', '24', '49', '1'), ('773', '1463494266', '25', '62', '1'), ('774', '1463494326', '25', '53', '1'), ('775', '1463494386', '25', '49', '1'), ('776', '1463494446', '25', '44', '1'), ('777', '1463494506', '25', '50', '1'), ('778', '1463494566', '25', '55', '1'), ('779', '1463494626', '25', '52', '1'), ('780', '1463494686', '25', '52', '1'), ('781', '1463494746', '25', '62', '1'), ('782', '1463494806', '25', '57', '1'), ('783', '1463494866', '24', '43', '1'), ('784', '1463494926', '25', '57', '1'), ('785', '1463494986', '25', '48', '1'), ('786', '1463495046', '25', '56', '1'), ('787', '1463495106', '25', '56', '1'), ('788', '1463495166', '25', '59', '1'), ('789', '1463495226', '25', '47', '1'), ('790', '1463495286', '25', '56', '1'), ('791', '1463495346', '25', '63', '1'), ('792', '1463495406', '25', '48', '1'), ('793', '1463495466', '25', '40', '1'), ('794', '1463495526', '25', '49', '1'), ('795', '1463495586', '25', '1719', '1'), ('796', '1463495646', '25', '66', '1'), ('797', '1463495706', '25', '74', '1'), ('798', '1463495766', '25', '54', '1'), ('799', '1463495826', '25', '66', '1'), ('800', '1463495886', '25', '55', '1');
INSERT INTO `time_diff_log` VALUES ('801', '1463495946', '25', '60', '1'), ('802', '1463496006', '25', '50', '1'), ('803', '1463496066', '25', '67', '1'), ('804', '1463496126', '25', '62', '1'), ('805', '1463496186', '25', '58', '1'), ('806', '1463496246', '25', '335', '1'), ('807', '1463496306', '25', '62', '1'), ('808', '1463496366', '25', '70', '1'), ('809', '1463496426', '25', '69', '1'), ('810', '1463496486', '24', '49', '1'), ('811', '1463496546', '25', '45', '1'), ('812', '1463496606', '25', '65', '1'), ('813', '1463496666', '25', '608', '1'), ('814', '1463496726', '25', '49', '1'), ('815', '1463496786', '25', '53', '1'), ('816', '1463496846', '25', '73', '1'), ('817', '1463496906', '25', '48', '1'), ('818', '1463496966', '25', '62', '1'), ('819', '1463497026', '25', '51', '1'), ('820', '1463497086', '25', '61', '1'), ('821', '1463497146', '25', '53', '1'), ('822', '1463497206', '25', '941', '1'), ('823', '1463497266', '25', '44', '1'), ('824', '1463497326', '25', '46', '1'), ('825', '1463497386', '25', '58', '1'), ('826', '1463497446', '25', '42', '1'), ('827', '1463497506', '25', '43', '1'), ('828', '1463497566', '24', '38', '1'), ('829', '1463497626', '24', '47', '1'), ('830', '1463497686', '25', '48', '1'), ('831', '1463497746', '25', '42', '1'), ('832', '1463497806', '24', '44', '1'), ('833', '1463497866', '25', '56', '1'), ('834', '1463497926', '25', '42', '1'), ('835', '1463497986', '25', '40', '1'), ('836', '1463498046', '24', '41', '1'), ('837', '1463498106', '25', '44', '1'), ('838', '1463498167', '24', '41', '1'), ('839', '1463498227', '24', '43', '1'), ('840', '1463498287', '25', '57', '1'), ('841', '1463498347', '25', '38', '1'), ('842', '1463498407', '25', '45', '1'), ('843', '1463498467', '24', '42', '1'), ('844', '1463498527', '25', '41', '1'), ('845', '1463498587', '25', '39', '1'), ('846', '1463498647', '25', '45', '1'), ('847', '1463498707', '25', '47', '1'), ('848', '1463498767', '25', '57', '1'), ('849', '1463498827', '25', '438', '1'), ('850', '1463498887', '25', '61', '1'), ('851', '1463498947', '25', '51', '1'), ('852', '1463499007', '25', '49', '1'), ('853', '1463499067', '25', '42', '1'), ('854', '1463499127', '25', '54', '1'), ('855', '1463499187', '24', '49', '1'), ('856', '1463499247', '25', '42', '1'), ('857', '1463499307', '25', '46', '1'), ('858', '1463499367', '25', '76', '1'), ('859', '1463499427', '25', '43', '1'), ('860', '1463499487', '25', '60', '1'), ('861', '1463499547', '25', '45', '1'), ('862', '1463499607', '25', '62', '1'), ('863', '1463499667', '25', '59', '1'), ('864', '1463499727', '25', '47', '1'), ('865', '1463499787', '25', '47', '1'), ('866', '1463499847', '25', '53', '1'), ('867', '1463499907', '25', '62', '1'), ('868', '1463499967', '25', '48', '1'), ('869', '1463500027', '25', '57', '1'), ('870', '1463500087', '25', '67', '1'), ('871', '1463500147', '25', '59', '1'), ('872', '1463500207', '25', '62', '1'), ('873', '1463500267', '25', '55', '1'), ('874', '1463500327', '25', '52', '1'), ('875', '1463500387', '25', '40', '1'), ('876', '1463500447', '25', '62', '1'), ('877', '1463500507', '25', '63', '1'), ('878', '1463500567', '24', '53', '1'), ('879', '1463500627', '25', '254', '1'), ('880', '1463500687', '25', '61', '1'), ('881', '1463500747', '25', '46', '1'), ('882', '1463500807', '25', '163', '1'), ('883', '1463500867', '25', '454', '1'), ('884', '1463500927', '25', '67', '1'), ('885', '1463500987', '25', '63', '1'), ('886', '1463501047', '24', '48', '1'), ('887', '1463501107', '24', '48', '1'), ('888', '1463501167', '25', '59', '1'), ('889', '1463501227', '25', '61', '1'), ('890', '1463501287', '24', '53', '1'), ('891', '1463501347', '25', '47', '1'), ('892', '1463501407', '25', '62', '1'), ('893', '1463501467', '25', '66', '1'), ('894', '1463501527', '25', '59', '1'), ('895', '1463501587', '25', '52', '1'), ('896', '1463501647', '25', '47', '1'), ('897', '1463501707', '25', '245', '1'), ('898', '1463501767', '25', '41', '1'), ('899', '1463501827', '25', '51', '1'), ('900', '1463501887', '25', '57', '1');
INSERT INTO `time_diff_log` VALUES ('901', '1463501947', '25', '58', '1'), ('902', '1463502007', '25', '74', '1'), ('903', '1463502067', '25', '42', '1'), ('904', '1463502127', '25', '42', '1'), ('905', '1463502187', '25', '39', '1'), ('906', '1463502248', '25', '319', '1'), ('907', '1463502308', '25', '62', '1'), ('908', '1463502368', '25', '47', '1'), ('909', '1463502428', '24', '40', '1'), ('910', '1463502488', '25', '53', '1'), ('911', '1463502548', '25', '57', '1'), ('912', '1463502608', '25', '65', '1'), ('913', '1463502668', '24', '45', '1'), ('914', '1463502728', '25', '95', '1'), ('915', '1463502788', '25', '60', '1'), ('916', '1463502848', '24', '36', '1'), ('917', '1463502908', '25', '52', '1'), ('918', '1463502968', '24', '50', '1'), ('919', '1463503028', '25', '50', '1'), ('920', '1463503088', '25', '52', '1'), ('921', '1463503148', '24', '47', '1'), ('922', '1463503208', '25', '57', '1'), ('923', '1463503268', '25', '71', '1'), ('924', '1463503328', '25', '59', '1'), ('925', '1463503388', '24', '45', '1'), ('926', '1463503448', '24', '43', '1'), ('927', '1463503508', '25', '55', '1'), ('928', '1463503568', '24', '43', '1'), ('929', '1463503628', '25', '53', '1'), ('930', '1463503688', '25', '83', '1'), ('931', '1463503748', '25', '48', '1'), ('932', '1463503808', '25', '48', '1'), ('933', '1463503868', '24', '41', '1'), ('934', '1463503928', '25', '40', '1'), ('935', '1463503988', '25', '50', '1'), ('936', '1463504048', '25', '64', '1'), ('937', '1463504108', '25', '64', '1'), ('938', '1463504168', '25', '47', '1'), ('939', '1463504228', '25', '328', '1'), ('940', '1463504288', '25', '66', '1'), ('941', '1463504348', '25', '69', '1'), ('942', '1463504408', '25', '50', '1'), ('943', '1463504468', '25', '45', '1'), ('944', '1463504528', '25', '172', '1'), ('945', '1463504588', '25', '55', '1'), ('946', '1463504648', '25', '68', '1'), ('947', '1463504708', '25', '43', '1'), ('948', '1463504768', '25', '51', '1'), ('949', '1463504828', '25', '53', '1'), ('950', '1463504888', '25', '653', '1'), ('951', '1463504948', '24', '41', '1'), ('952', '1463673616', '0', '0', '0'), ('953', '1463673676', '28', '4836', '1'), ('954', '1463673736', '27', '2351', '1'), ('955', '1463673796', '25', '629', '1'), ('956', '1463673856', '25', '73', '1'), ('957', '1463673916', '25', '63', '1'), ('958', '1463673976', '25', '50', '1'), ('959', '1463674036', '25', '611', '1'), ('960', '1463674096', '25', '52', '1'), ('961', '1463674156', '25', '165', '1'), ('962', '1463674216', '25', '94', '1'), ('963', '1463674276', '25', '43', '1'), ('964', '1463674336', '25', '55', '1'), ('965', '1463674396', '25', '66', '1'), ('966', '1463674456', '25', '62', '1'), ('967', '1463674516', '25', '51', '1'), ('968', '1463674576', '25', '50', '1'), ('969', '1463674636', '25', '63', '1'), ('970', '1463674696', '25', '52', '1'), ('971', '1463674756', '25', '310', '1'), ('972', '1463674816', '25', '50', '1'), ('973', '1463674876', '25', '64', '1'), ('974', '1463674936', '25', '66', '1'), ('975', '1463674996', '25', '50', '1'), ('976', '1463675056', '24', '49', '1'), ('977', '1463675116', '25', '66', '1'), ('978', '1463675176', '25', '193', '1'), ('979', '1463675236', '25', '62', '1'), ('980', '1463675296', '25', '59', '1'), ('981', '1463675356', '25', '125', '1'), ('982', '1463675416', '24', '44', '1'), ('983', '1463675476', '25', '56', '1'), ('984', '1463675536', '25', '49', '1'), ('985', '1463675596', '25', '769', '1'), ('986', '1463675656', '25', '66', '1'), ('987', '1463675716', '25', '60', '1'), ('988', '1463675776', '25', '51', '1'), ('989', '1463675836', '25', '58', '1'), ('990', '1463675896', '25', '197', '1'), ('991', '1463675956', '25', '48', '1'), ('992', '1463676016', '24', '42', '1'), ('993', '1463676076', '25', '41', '1'), ('994', '1463676136', '25', '45', '1'), ('995', '1463676196', '24', '39', '1'), ('996', '1463676256', '25', '58', '1'), ('997', '1463676316', '25', '36', '1'), ('998', '1463676376', '25', '45', '1'), ('999', '1463676436', '24', '53', '1'), ('1000', '1463676496', '25', '44', '1');
INSERT INTO `time_diff_log` VALUES ('1001', '1463676556', '24', '33', '1'), ('1002', '1463676616', '25', '38', '1'), ('1003', '1463676676', '25', '52', '1'), ('1004', '1463676736', '24', '40', '1'), ('1005', '1463676796', '25', '35', '1'), ('1006', '1463676856', '25', '40', '1'), ('1007', '1463676916', '25', '51', '1'), ('1008', '1463676976', '24', '43', '1'), ('1009', '1463677036', '25', '44', '1'), ('1010', '1463677096', '25', '36', '1'), ('1011', '1463677157', '25', '74', '1'), ('1012', '1463677217', '25', '40', '1'), ('1013', '1463677277', '24', '41', '1'), ('1014', '1463677337', '25', '41', '1'), ('1015', '1463677397', '25', '533', '1'), ('1016', '1463677457', '25', '47', '1'), ('1017', '1463677517', '25', '1014', '1'), ('1018', '1463677577', '25', '57', '1'), ('1019', '1463677637', '25', '36', '1'), ('1020', '1463677697', '25', '49', '1'), ('1021', '1463677757', '24', '44', '1'), ('1022', '1463677817', '25', '40', '1'), ('1023', '1463677877', '25', '42', '1'), ('1024', '1463677937', '25', '50', '1'), ('1025', '1463677997', '25', '42', '1'), ('1026', '1463678057', '25', '59', '1'), ('1027', '1463678117', '25', '38', '1'), ('1028', '1463678177', '25', '41', '1'), ('1029', '1463678237', '25', '83', '1'), ('1030', '1463678297', '25', '48', '1'), ('1031', '1463678357', '25', '34', '1'), ('1032', '1463678417', '24', '36', '1'), ('1033', '1463678477', '25', '53', '1'), ('1034', '1463678537', '24', '40', '1'), ('1035', '1463776638', '0', '0', '0'), ('1036', '1463776698', '27', '2804', '0'), ('1037', '1463776758', '25', '781', '0'), ('1038', '1463776818', '25', '437', '0'), ('1039', '1463776878', '25', '52', '0'), ('1040', '1463776938', '25', '36', '0'), ('1041', '1463776998', '25', '35', '0'), ('1042', '1463777058', '25', '158', '0'), ('1043', '1463777118', '25', '34', '0'), ('1044', '1463777178', '24', '36', '0'), ('1045', '1463777238', '25', '39', '0'), ('1046', '1463777298', '25', '129', '1'), ('1047', '1463777358', '26', '1622', '1'), ('1048', '1463777418', '25', '45', '1'), ('1049', '1463777478', '25', '198', '1'), ('1050', '1463777538', '25', '50', '1'), ('1051', '1463777598', '25', '64', '1'), ('1052', '1463777658', '25', '48', '1'), ('1053', '1463777718', '24', '47', '1'), ('1054', '1463777778', '24', '42', '1'), ('1055', '1463777838', '25', '109', '1'), ('1056', '1463777898', '25', '63', '1'), ('1057', '1463777958', '25', '56', '1'), ('1058', '1463778018', '25', '46', '1'), ('1059', '1463778078', '24', '41', '1'), ('1060', '1463778138', '25', '51', '1'), ('1061', '1463778198', '24', '49', '1'), ('1062', '1463778258', '24', '44', '1'), ('1063', '1463778318', '25', '426', '1'), ('1064', '1463778378', '25', '44', '1'), ('1065', '1464709114', '0', '0', '0'), ('1066', '1464709174', '27', '2465', '0'), ('1067', '1464709234', '25', '836', '0'), ('1068', '1464709294', '25', '1501', '1'), ('1069', '1464709354', '26', '2312', '1'), ('1070', '1464709414', '25', '47', '1'), ('1071', '1464709474', '25', '1505', '1'), ('1072', '1464709534', '25', '519', '1'), ('1073', '1464709594', '25', '53', '1'), ('1074', '1464709654', '25', '85', '1'), ('1075', '1464709714', '25', '41', '1'), ('1076', '1464709774', '24', '37', '1'), ('1077', '1464709834', '25', '55', '1'), ('1078', '1464709894', '25', '42', '1'), ('1079', '1464709954', '25', '55', '1'), ('1080', '1464710014', '24', '47', '1'), ('1081', '1464710074', '25', '37', '1'), ('1082', '1464710134', '25', '47', '1'), ('1083', '1464710194', '25', '49', '1'), ('1084', '1464710254', '25', '38', '1'), ('1085', '1464710314', '24', '39', '1'), ('1086', '1464710374', '25', '57', '1'), ('1087', '1464710434', '25', '52', '1'), ('1088', '1464710494', '25', '53', '1'), ('1089', '1464710554', '25', '40', '1'), ('1090', '1464710614', '25', '61', '1'), ('1091', '1464710674', '25', '52', '1'), ('1092', '1464710734', '25', '41', '1'), ('1093', '1464710794', '24', '40', '1'), ('1094', '1464710854', '25', '56', '1'), ('1095', '1464710914', '25', '45', '1'), ('1096', '1464710974', '25', '43', '1'), ('1097', '1464711034', '24', '43', '1'), ('1098', '1464711094', '25', '43', '1'), ('1099', '1464711154', '25', '38', '1'), ('1100', '1464711214', '24', '39', '1');
INSERT INTO `time_diff_log` VALUES ('1101', '1464711274', '25', '45', '1'), ('1102', '1464711334', '25', '37', '1'), ('1103', '1464711394', '25', '44', '1'), ('1104', '1464711454', '25', '36', '1'), ('1105', '1464711514', '25', '35', '1'), ('1106', '1464711574', '24', '32', '1'), ('1107', '1464711634', '25', '37', '1'), ('1108', '1464711695', '24', '37', '1'), ('1109', '1464711755', '25', '43', '1'), ('1110', '1464711815', '25', '37', '1'), ('1111', '1464711875', '24', '34', '1'), ('1112', '1464711935', '24', '35', '1'), ('1113', '1464711995', '25', '36', '1'), ('1114', '1464712055', '25', '33', '1'), ('1115', '1464712115', '25', '36', '1'), ('1116', '1464712175', '24', '46', '1'), ('1117', '1464712235', '25', '39', '1'), ('1118', '1464712295', '25', '39', '1'), ('1119', '1464712355', '25', '38', '1'), ('1120', '1464712415', '25', '39', '1'), ('1121', '1464712475', '24', '31', '1'), ('1122', '1464712535', '25', '33', '1'), ('1123', '1464712595', '25', '38', '1'), ('1124', '1464712655', '24', '46', '1'), ('1125', '1464712715', '24', '35', '1'), ('1126', '1464712775', '25', '33', '1'), ('1127', '1464712835', '24', '37', '1'), ('1128', '1464712895', '25', '36', '1'), ('1129', '1464712955', '24', '35', '1'), ('1130', '1464713015', '24', '33', '1'), ('1131', '1464713075', '25', '45', '1'), ('1132', '1464713135', '25', '35', '1'), ('1133', '1464713195', '25', '40', '1'), ('1134', '1464713255', '24', '35', '1'), ('1135', '1464713315', '25', '35', '1'), ('1136', '1464713375', '24', '36', '1'), ('1137', '1464713435', '25', '38', '1'), ('1138', '1464713495', '25', '42', '1'), ('1139', '1464713555', '25', '37', '1'), ('1140', '1464713615', '24', '38', '1'), ('1141', '1464713675', '25', '39', '1'), ('1142', '1464713735', '25', '35', '1'), ('1143', '1464713795', '24', '36', '1'), ('1144', '1464713855', '24', '33', '1'), ('1145', '1464713915', '25', '35', '1'), ('1146', '1464713975', '24', '44', '1'), ('1147', '1464714035', '24', '35', '1'), ('1148', '1464714095', '25', '58', '1'), ('1149', '1464714155', '25', '160', '1'), ('1150', '1464714215', '25', '56', '1'), ('1151', '1464714275', '25', '56', '1'), ('1152', '1464714335', '25', '50', '1'), ('1153', '1464714395', '25', '54', '1'), ('1154', '1464714455', '24', '43', '1'), ('1155', '1464714515', '25', '43', '1'), ('1156', '1464714575', '24', '46', '1'), ('1157', '1464714635', '25', '42', '1'), ('1158', '1464714695', '24', '42', '1'), ('1159', '1464714755', '25', '42', '1'), ('1160', '1464714815', '25', '42', '1'), ('1161', '1464714875', '25', '56', '1'), ('1162', '1464714935', '24', '44', '1'), ('1163', '1464714995', '25', '49', '1'), ('1164', '1464715055', '25', '56', '1'), ('1165', '1464715115', '24', '40', '1'), ('1166', '1464715175', '25', '60', '1'), ('1167', '1464715235', '25', '64', '1'), ('1168', '1464715295', '25', '65', '1'), ('1169', '1464715355', '25', '57', '1'), ('1170', '1464715415', '25', '55', '1'), ('1171', '1464715475', '25', '59', '1'), ('1172', '1464715535', '25', '46', '1'), ('1173', '1464715595', '25', '59', '1'), ('1174', '1464715655', '25', '50', '1'), ('1175', '1464715715', '25', '61', '1'), ('1176', '1464715775', '25', '64', '1'), ('1177', '1464715835', '25', '54', '1'), ('1178', '1464715895', '25', '46', '1'), ('1179', '1464715955', '25', '60', '1'), ('1180', '1464716015', '25', '48', '1'), ('1181', '1464716075', '25', '49', '1'), ('1182', '1464716135', '25', '54', '1'), ('1183', '1464716195', '25', '62', '1'), ('1184', '1464716255', '25', '65', '1'), ('1185', '1464716315', '25', '50', '1'), ('1186', '1464716375', '25', '40', '1'), ('1187', '1464716435', '25', '41', '1'), ('1188', '1464716495', '25', '44', '1'), ('1189', '1464716555', '25', '43', '1'), ('1190', '1464716615', '25', '47', '1'), ('1191', '1464716675', '25', '57', '1'), ('1192', '1464716735', '25', '60', '1'), ('1193', '1464716795', '25', '54', '1'), ('1194', '1464716855', '25', '60', '1'), ('1195', '1464716915', '25', '56', '1'), ('1196', '1464716975', '25', '72', '1'), ('1197', '1464717035', '25', '211', '1'), ('1198', '1464717095', '25', '68', '1'), ('1199', '1464717155', '25', '47', '1'), ('1200', '1464717215', '25', '50', '1');
INSERT INTO `time_diff_log` VALUES ('1201', '1464717275', '25', '67', '1'), ('1202', '1464717335', '25', '61', '1'), ('1203', '1464717395', '24', '47', '1'), ('1204', '1464717455', '24', '40', '1'), ('1205', '1464717515', '25', '56', '1'), ('1206', '1464717575', '25', '39', '1'), ('1207', '1464717635', '24', '51', '1'), ('1208', '1464717695', '25', '38', '1'), ('1209', '1464717755', '25', '43', '1'), ('1210', '1464717815', '25', '1023', '1'), ('1211', '1464717925', '24', '62', '1'), ('1212', '1464717985', '25', '669', '1'), ('1213', '1464718045', '25', '54', '1'), ('1214', '1464718105', '25', '144', '1'), ('1215', '1464718165', '25', '48', '1'), ('1216', '1464718225', '24', '42', '1'), ('1217', '1464718285', '25', '36', '1'), ('1218', '1464718345', '25', '58', '1'), ('1219', '1464718405', '25', '51', '1'), ('1220', '1464718465', '25', '38', '1'), ('1221', '1464718525', '24', '45', '1'), ('1222', '1464718585', '25', '38', '1'), ('1223', '1464718645', '24', '41', '1'), ('1224', '1464718705', '25', '44', '1'), ('1225', '1464718765', '25', '59', '1'), ('1226', '1464718825', '24', '49', '1'), ('1227', '1464718885', '25', '36', '1'), ('1228', '1464718945', '25', '72', '1'), ('1229', '1464719005', '25', '42', '0'), ('1230', '1464882329', '0', '0', '0'), ('1231', '1464882389', '27', '2823', '0'), ('1232', '1464882449', '25', '721', '0'), ('1233', '1464882509', '25', '1065', '0'), ('1234', '1464882569', '25', '576', '1'), ('1235', '1464882629', '26', '2479', '1'), ('1236', '1464882689', '25', '83', '1'), ('1237', '1464882749', '25', '743', '1'), ('1238', '1464884966', '25', '457', '1'), ('1239', '1464885026', '25', '519', '1'), ('1240', '1464885086', '25', '270', '1'), ('1241', '1464885146', '25', '66', '1'), ('1242', '1464885206', '25', '71', '1'), ('1243', '1464885266', '25', '358', '1'), ('1244', '1464885326', '25', '52', '1'), ('1245', '1464885386', '24', '57', '1'), ('1246', '1464885446', '25', '43', '1'), ('1247', '1464885581', '24', '53', '1'), ('1248', '1464885641', '25', '264', '1'), ('1249', '1464885701', '25', '94', '1'), ('1250', '1464885761', '25', '94', '1'), ('1251', '1464885821', '25', '75', '1'), ('1252', '1464885881', '25', '53', '1'), ('1253', '1464885941', '25', '82', '1'), ('1254', '1464886001', '25', '121', '1'), ('1255', '1464886061', '25', '66', '1'), ('1256', '1464886121', '25', '46', '1'), ('1257', '1464886181', '25', '99', '1'), ('1258', '1464886241', '25', '41', '1'), ('1259', '1464886301', '25', '55', '1'), ('1260', '1464886361', '25', '54', '1'), ('1261', '1464886421', '25', '54', '1'), ('1262', '1464886481', '25', '2181', '1'), ('1263', '1464886541', '25', '50', '1'), ('1264', '1464886601', '25', '53', '1'), ('1265', '1464886661', '25', '48', '1'), ('1266', '1464886721', '25', '47', '1'), ('1267', '1464886781', '25', '167', '1'), ('1268', '1464886841', '24', '46', '1'), ('1269', '1464886901', '25', '45', '1'), ('1270', '1464886961', '25', '40', '1'), ('1271', '1464887021', '25', '38', '1'), ('1272', '1464887081', '24', '35', '1'), ('1273', '1464887141', '24', '35', '1'), ('1274', '1464887201', '25', '35', '1'), ('1275', '1464887261', '24', '33', '1'), ('1276', '1464887321', '25', '152', '1'), ('1277', '1464887381', '25', '45', '1'), ('1278', '1464887441', '25', '234', '1'), ('1279', '1464887501', '25', '39', '1'), ('1280', '1464887561', '25', '48', '1'), ('1281', '1464887621', '25', '256', '1'), ('1282', '1464887681', '25', '50', '1'), ('1283', '1464887741', '25', '324', '1'), ('1284', '1464887801', '25', '53', '1'), ('1285', '1464887861', '25', '57', '1'), ('1286', '1464887921', '25', '35', '1'), ('1287', '1464887981', '25', '45', '1'), ('1288', '1464888041', '25', '40', '1'), ('1289', '1464888101', '25', '47', '1'), ('1290', '1464888161', '25', '40', '1'), ('1291', '1464888221', '24', '49', '1'), ('1292', '1464888281', '25', '91', '1'), ('1293', '1464888341', '25', '54', '1'), ('1294', '1464888401', '25', '544', '1'), ('1295', '1464888461', '25', '47', '1'), ('1296', '1464888521', '25', '39', '1'), ('1297', '1464888581', '24', '45', '1'), ('1298', '1464888641', '25', '59', '1'), ('1299', '1464888701', '25', '77', '1'), ('1300', '1464888761', '25', '73', '1');
INSERT INTO `time_diff_log` VALUES ('1301', '1464888821', '25', '59', '1'), ('1302', '1464888882', '25', '55', '1'), ('1303', '1464888942', '25', '44', '1'), ('1304', '1464889002', '25', '43', '1'), ('1305', '1464889062', '25', '42', '1'), ('1306', '1464889122', '25', '61', '1'), ('1307', '1464979235', '0', '0', '0'), ('1308', '1464979295', '33', '6089', '1'), ('1309', '1464979355', '27', '3360', '1'), ('1310', '1464979415', '25', '608', '1'), ('1311', '1464979475', '25', '467', '1'), ('1312', '1464979535', '25', '60', '1'), ('1313', '1464979595', '25', '646', '1'), ('1314', '1464979655', '25', '59', '1'), ('1315', '1464979715', '25', '1611', '1'), ('1316', '1464979775', '25', '128', '1'), ('1317', '1464979835', '24', '37', '1'), ('1318', '1464979895', '25', '34', '1'), ('1319', '1464979955', '25', '55', '1'), ('1320', '1464980015', '25', '42', '1'), ('1321', '1464980075', '25', '53', '1'), ('1322', '1464980135', '25', '37', '1'), ('1323', '1464980195', '25', '48', '1'), ('1324', '1464980255', '25', '46', '1'), ('1325', '1464980315', '25', '254', '1'), ('1326', '1464980375', '24', '39', '1'), ('1327', '1464980435', '25', '39', '1'), ('1328', '1464980495', '25', '54', '1'), ('1329', '1464980555', '25', '52', '1'), ('1330', '1464980615', '25', '70', '1'), ('1331', '1464980675', '24', '41', '1'), ('1332', '1464980735', '25', '44', '1'), ('1333', '1464980795', '25', '40', '1'), ('1334', '1464980855', '25', '43', '1'), ('1335', '1464980915', '25', '51', '1'), ('1336', '1464980975', '25', '1334', '1'), ('1337', '1464981035', '25', '34', '1'), ('1338', '1464981095', '25', '33', '1'), ('1339', '1464981155', '25', '34', '1'), ('1340', '1464981215', '25', '36', '1'), ('1341', '1464981275', '25', '37', '1'), ('1342', '1464981335', '25', '34', '1'), ('1343', '1464981395', '25', '41', '1'), ('1344', '1464981455', '24', '43', '1'), ('1345', '1464981515', '25', '44', '1'), ('1346', '1464981575', '24', '39', '1'), ('1347', '1464981635', '25', '39', '1'), ('1348', '1464981695', '25', '41', '1'), ('1349', '1464981755', '25', '60', '1'), ('1350', '1464981815', '25', '590', '1'), ('1351', '1464981875', '25', '58', '1'), ('1352', '1464981935', '25', '196', '1'), ('1353', '1464981995', '25', '34', '1'), ('1354', '1464982055', '25', '36', '1'), ('1355', '1464982115', '25', '34', '1'), ('1356', '1464982175', '25', '33', '1'), ('1357', '1464982235', '24', '35', '1'), ('1358', '1464982295', '25', '38', '1'), ('1359', '1464982356', '24', '36', '1'), ('1360', '1464982416', '25', '39', '1'), ('1361', '1464982476', '24', '33', '1'), ('1362', '1464982536', '25', '33', '1'), ('1363', '1464982596', '24', '34', '1'), ('1364', '1464982656', '25', '34', '1'), ('1365', '1464982716', '25', '40', '1'), ('1366', '1464982776', '24', '35', '1'), ('1367', '1464982836', '25', '34', '1'), ('1368', '1464982896', '25', '31', '1'), ('1369', '1464982956', '25', '35', '1'), ('1370', '1464983016', '24', '36', '1'), ('1371', '1464983076', '24', '36', '1'), ('1372', '1464983136', '25', '35', '1'), ('1373', '1464983196', '25', '49', '1'), ('1374', '1464983256', '25', '35', '1'), ('1375', '1464983316', '25', '32', '1'), ('1376', '1464983376', '25', '34', '1'), ('1377', '1464983436', '24', '33', '1'), ('1378', '1464983496', '25', '58', '1'), ('1379', '1466536777', '0', '0', '0'), ('1380', '1466536837', '27', '2602', '0'), ('1381', '1466536897', '25', '996', '1'), ('1382', '1466536957', '26', '1650', '1'), ('1383', '1466537017', '25', '84', '1'), ('1384', '1466537077', '25', '68', '1'), ('1385', '1466537137', '25', '542', '1'), ('1386', '1466537197', '25', '634', '1'), ('1387', '1466537257', '25', '54', '1'), ('1388', '1466537317', '25', '147', '1'), ('1389', '1466537377', '25', '291', '1'), ('1390', '1466537437', '24', '46', '1'), ('1391', '1466537497', '25', '85', '1'), ('1392', '1466537557', '25', '78', '1'), ('1393', '1466537617', '25', '70', '1'), ('1394', '1466537677', '25', '85', '1'), ('1395', '1466537737', '25', '70', '1'), ('1396', '1466537797', '25', '74', '1'), ('1397', '1466537857', '25', '61', '1'), ('1398', '1466537917', '25', '320', '1'), ('1399', '1466537977', '25', '74', '1'), ('1400', '1466538037', '25', '66', '1');
INSERT INTO `time_diff_log` VALUES ('1401', '1466538097', '25', '47', '1'), ('1402', '1466538157', '25', '93', '1'), ('1403', '1466539147', '24', '55', '0'), ('1404', '1466539207', '28', '4073', '0'), ('1405', '1468775266', '24', '59', '0'), ('1406', '1468775326', '26', '1313', '0'), ('1407', '1468775386', '26', '1511', '1'), ('1408', '1468775446', '25', '1469', '1'), ('1409', '1468775506', '25', '978', '1'), ('1410', '1468775566', '25', '108', '1'), ('1411', '1468775626', '25', '59', '1'), ('1412', '1468775686', '25', '793', '1'), ('1413', '1468775746', '24', '54', '1'), ('1414', '1468775806', '25', '47', '1'), ('1415', '1468775866', '24', '49', '1'), ('1416', '1468775926', '25', '45', '1'), ('1417', '1468775986', '24', '43', '1'), ('1418', '1468776046', '25', '1186', '1'), ('1419', '1468776106', '25', '61', '1'), ('1420', '1468776166', '25', '727', '1'), ('1421', '1468777071', '25', '904', '0'), ('1422', '1468777131', '25', '457', '1'), ('1423', '1468777191', '25', '455', '1'), ('1424', '1468777251', '25', '476', '1'), ('1425', '1468777311', '25', '80', '1'), ('1426', '1468777371', '25', '757', '1'), ('1427', '1468777431', '25', '263', '1'), ('1428', '1468777491', '25', '988', '1'), ('1429', '1468777551', '25', '90', '1'), ('1430', '1468777611', '25', '50', '1'), ('1431', '1468777672', '25', '67', '1'), ('1432', '1468777732', '25', '40', '1'), ('1433', '1468777792', '25', '39', '1'), ('1434', '1468777852', '24', '45', '1'), ('1435', '1468777912', '25', '147', '1'), ('1436', '1468777972', '25', '91', '1'), ('1437', '1468778032', '25', '46', '1'), ('1438', '1468778092', '25', '46', '0'), ('1439', '1468778363', '25', '86', '1'), ('1440', '1468778423', '25', '380', '1'), ('1441', '1468778483', '25', '83', '1'), ('1442', '1468778543', '25', '51', '1'), ('1443', '1468778603', '25', '72', '1'), ('1444', '1468778663', '25', '62', '1'), ('1445', '1468778723', '25', '115', '1'), ('1446', '1468778783', '25', '56', '1'), ('1447', '1468778843', '25', '44', '1'), ('1448', '1468778903', '24', '45', '1'), ('1449', '1468778963', '25', '50', '1'), ('1450', '1468779023', '24', '40', '1'), ('1451', '1468779083', '25', '56', '1'), ('1452', '1468779143', '25', '50', '1'), ('1453', '1468779203', '25', '60', '1'), ('1454', '1468779263', '25', '45', '1'), ('1455', '1468779323', '25', '45', '1'), ('1456', '1468779383', '25', '45', '1'), ('1457', '1468779443', '25', '61', '1'), ('1458', '1468779503', '25', '42', '1'), ('1459', '1468779563', '25', '50', '1'), ('1460', '1468779623', '25', '58', '1'), ('1461', '1468782411', '26', '388', '0'), ('1462', '1468782471', '26', '2389', '1'), ('1463', '1468782531', '25', '748', '1'), ('1464', '1468782591', '25', '771', '1'), ('1465', '1468782651', '25', '566', '1'), ('1466', '1468782711', '25', '64', '1'), ('1467', '1468782771', '25', '705', '1'), ('1468', '1468782831', '25', '683', '1'), ('1469', '1468782891', '25', '53', '1'), ('1470', '1468782951', '25', '54', '0'), ('1471', '1468783011', '25', '405', '0'), ('1472', '1468783071', '25', '37', '0'), ('1473', '1468783131', '24', '39', '0'), ('1474', '1468783191', '25', '45', '0'), ('1475', '1468783251', '25', '241', '0'), ('1476', '1468783311', '25', '44', '0'), ('1477', '1468783371', '24', '43', '0'), ('1478', '1468783431', '25', '46', '0'), ('1479', '1468783491', '24', '47', '0'), ('1480', '1468783551', '25', '43', '0'), ('1481', '1468783611', '24', '43', '0'), ('1482', '1468783671', '25', '41', '0'), ('1483', '1468783731', '25', '55', '0'), ('1484', '1468783791', '25', '45', '0'), ('1485', '1468783851', '25', '42', '0'), ('1486', '1468783911', '25', '45', '0'), ('1487', '1468783971', '25', '42', '0'), ('1488', '1468784031', '24', '42', '0'), ('1489', '1468784091', '25', '47', '0'), ('1490', '1468784151', '25', '57', '0'), ('1491', '1468784211', '25', '45', '0'), ('1492', '1468784271', '25', '40', '0'), ('1493', '1468784331', '24', '37', '0'), ('1494', '1468784391', '25', '45', '0'), ('1495', '1468784451', '25', '40', '0'), ('1496', '1468784511', '25', '47', '0'), ('1497', '1468784571', '25', '44', '0'), ('1498', '1468784631', '25', '53', '0'), ('1499', '1468784691', '25', '42', '0'), ('1500', '1468784751', '25', '37', '0');
INSERT INTO `time_diff_log` VALUES ('1501', '1468784811', '24', '44', '0'), ('1502', '1468784871', '25', '42', '0'), ('1503', '1468784931', '25', '42', '0'), ('1504', '1468784991', '24', '46', '0'), ('1505', '1468785051', '25', '61', '0'), ('1506', '1468785111', '25', '48', '0'), ('1507', '1468785171', '24', '41', '0'), ('1508', '1468785231', '25', '46', '0'), ('1509', '1468785291', '24', '46', '0'), ('1510', '1468785351', '25', '37', '0'), ('1511', '1468785411', '24', '45', '0'), ('1512', '1468785471', '24', '44', '0'), ('1513', '1468785531', '25', '45', '0'), ('1514', '1468785591', '25', '83', '1'), ('1515', '1468785652', '25', '93', '1'), ('1516', '1468785712', '25', '60', '1'), ('1517', '1468785772', '25', '52', '1'), ('1518', '1468785832', '25', '318', '1'), ('1519', '1468785892', '25', '55', '1'), ('1520', '1468785952', '25', '61', '1'), ('1521', '1468951739', '0', '0', '0'), ('1522', '1468951799', '31', '5093', '0'), ('1523', '1468951859', '26', '2307', '1'), ('1524', '1468951919', '25', '63', '1'), ('1525', '1468951979', '25', '380', '1'), ('1526', '1468952039', '25', '49', '1'), ('1527', '1468952099', '25', '617', '1'), ('1528', '1468952159', '25', '63', '1'), ('1529', '1468952219', '25', '149', '1'), ('1530', '1468952279', '25', '285', '1'), ('1531', '1468952339', '25', '140', '1'), ('1532', '1468952399', '25', '58', '1'), ('1533', '1468952459', '25', '190', '1'), ('1534', '1468952519', '25', '63', '1'), ('1535', '1468952579', '24', '46', '1'), ('1536', '1468952639', '25', '101', '1'), ('1537', '1468952699', '25', '68', '1'), ('1538', '1468952759', '25', '61', '1'), ('1539', '1468952819', '25', '47', '1'), ('1540', '1468952879', '25', '51', '1'), ('1541', '1468952939', '25', '57', '1'), ('1542', '1468952999', '25', '191', '1'), ('1543', '1468953059', '24', '48', '1'), ('1544', '1468953119', '25', '43', '1'), ('1545', '1468953179', '25', '53', '1'), ('1546', '1468953239', '25', '56', '1'), ('1547', '1468953299', '25', '61', '1'), ('1548', '1468953359', '24', '52', '1'), ('1549', '1468953419', '25', '58', '1'), ('1550', '1468953479', '25', '44', '1'), ('1551', '1468953539', '25', '48', '1'), ('1552', '1468953599', '25', '42', '1'), ('1553', '1468953659', '25', '44', '1'), ('1554', '1468953719', '25', '55', '1'), ('1555', '1468953779', '25', '43', '1'), ('1556', '1468953839', '25', '343', '1'), ('1557', '1468953899', '25', '52', '1'), ('1558', '1468953959', '25', '50', '1'), ('1559', '1468954019', '25', '45', '1'), ('1560', '1468954079', '25', '55', '1'), ('1561', '1468954139', '25', '42', '1'), ('1562', '1468954199', '24', '52', '1'), ('1563', '1468954259', '25', '49', '1'), ('1564', '1468954319', '25', '57', '1'), ('1565', '1468954379', '25', '49', '1'), ('1566', '1468954439', '25', '58', '1'), ('1567', '1468954499', '25', '52', '1'), ('1568', '1468954559', '25', '51', '1'), ('1569', '1468954619', '24', '41', '1'), ('1570', '1468954679', '24', '45', '1'), ('1571', '1468954739', '25', '53', '1'), ('1572', '1468954799', '25', '52', '1'), ('1573', '1468954859', '25', '52', '1'), ('1574', '1468954919', '25', '41', '1'), ('1575', '1468954979', '25', '121', '1'), ('1576', '1468955039', '25', '46', '1'), ('1577', '1468955099', '25', '50', '1'), ('1578', '1468955159', '24', '35', '1'), ('1579', '1468957237', '25', '1043', '1'), ('1580', '1468957297', '25', '607', '1'), ('1581', '1468957357', '25', '112', '1'), ('1582', '1468957417', '25', '164', '1'), ('1583', '1468957477', '25', '238', '1'), ('1584', '1468957537', '25', '55', '1'), ('1585', '1468957597', '25', '61', '1'), ('1586', '1468957657', '24', '53', '1'), ('1587', '1468957717', '25', '53', '1'), ('1588', '1469039117', '0', '0', '0'), ('1589', '1469039177', '31', '3676', '1'), ('1590', '1469039237', '26', '1686', '1'), ('1591', '1469039297', '25', '843', '1'), ('1592', '1469039357', '25', '73', '1'), ('1593', '1469039417', '25', '125', '1'), ('1594', '1469039477', '25', '511', '1'), ('1595', '1469039537', '25', '69', '1'), ('1596', '1469039597', '25', '685', '1'), ('1597', '1469039657', '25', '332', '1'), ('1598', '1469039717', '24', '50', '1'), ('1599', '1469039777', '25', '41', '1'), ('1600', '1469039837', '25', '56', '1');
INSERT INTO `time_diff_log` VALUES ('1601', '1469039897', '25', '50', '1'), ('1602', '1469039957', '25', '196', '1'), ('1603', '1469040017', '25', '53', '1'), ('1604', '1469040077', '25', '63', '1'), ('1605', '1469040137', '25', '71', '1'), ('1606', '1469040197', '25', '62', '1'), ('1607', '1469040257', '25', '65', '1'), ('1608', '1469040317', '25', '57', '1'), ('1609', '1469040377', '25', '63', '1'), ('1610', '1469040437', '25', '77', '1'), ('1611', '1469040497', '25', '59', '1'), ('1612', '1469040557', '25', '52', '1'), ('1613', '1469040617', '25', '65', '1'), ('1614', '1469040677', '25', '121', '1'), ('1615', '1469040737', '24', '52', '1'), ('1616', '1469040797', '25', '54', '1'), ('1617', '1469040857', '25', '64', '1'), ('1618', '1469040917', '25', '62', '1'), ('1619', '1469040977', '25', '62', '1'), ('1620', '1469041037', '25', '53', '1'), ('1621', '1469041097', '25', '56', '1'), ('1622', '1469041157', '25', '69', '1'), ('1623', '1469041217', '25', '58', '1'), ('1624', '1469041277', '25', '60', '1'), ('1625', '1469041337', '25', '54', '1'), ('1626', '1469041397', '25', '65', '1'), ('1627', '1469041457', '25', '51', '1'), ('1628', '1469041517', '25', '58', '1'), ('1629', '1469041577', '25', '62', '1'), ('1630', '1469041637', '25', '62', '1'), ('1631', '1469041697', '25', '54', '1'), ('1632', '1469041757', '25', '67', '1'), ('1633', '1469041817', '25', '54', '1'), ('1634', '1469041877', '24', '46', '1'), ('1635', '1469041937', '25', '60', '1'), ('1636', '1469041997', '25', '62', '1'), ('1637', '1469042057', '25', '49', '1'), ('1638', '1469042117', '25', '63', '1'), ('1639', '1469042177', '25', '213', '1'), ('1640', '1469042237', '24', '51', '1'), ('1641', '1469042297', '25', '45', '1'), ('1642', '1469042357', '25', '46', '1'), ('1643', '1469042417', '25', '54', '1'), ('1644', '1469042477', '25', '50', '1'), ('1645', '1469042537', '25', '53', '1'), ('1646', '1469042597', '25', '42', '1'), ('1647', '1469042657', '25', '64', '1'), ('1648', '1469042718', '25', '52', '1'), ('1649', '1469042778', '25', '47', '1'), ('1650', '1469042838', '25', '41', '1'), ('1651', '1469042898', '25', '54', '1'), ('1652', '1469042958', '25', '52', '1'), ('1653', '1469043018', '25', '49', '1'), ('1654', '1469043078', '25', '73', '1'), ('1655', '1469043138', '25', '45', '1'), ('1656', '1469043198', '25', '60', '1'), ('1657', '1469043258', '25', '47', '1'), ('1658', '1469043318', '25', '43', '1'), ('1659', '1469043378', '24', '44', '1'), ('1660', '1469043438', '25', '55', '1'), ('1661', '1469043498', '25', '43', '1'), ('1662', '1469043558', '25', '57', '1'), ('1663', '1469043618', '25', '49', '1'), ('1664', '1469043678', '25', '64', '1'), ('1665', '1469043738', '25', '63', '1'), ('1666', '1469043798', '25', '62', '1'), ('1667', '1469043858', '25', '49', '1'), ('1668', '1469043918', '25', '60', '1'), ('1669', '1469043978', '25', '74', '1'), ('1670', '1469044038', '25', '59', '1'), ('1671', '1469044098', '25', '54', '1'), ('1672', '1469044158', '25', '63', '1'), ('1673', '1469044218', '25', '65', '1'), ('1674', '1469044278', '25', '60', '1'), ('1675', '1469044338', '25', '64', '1'), ('1676', '1469044398', '25', '66', '1'), ('1677', '1469044458', '25', '76', '1'), ('1678', '1469044518', '25', '64', '1'), ('1679', '1469044578', '25', '62', '1'), ('1680', '1469044638', '25', '46', '1'), ('1681', '1469044698', '25', '50', '1'), ('1682', '1469044758', '25', '50', '1'), ('1683', '1469044818', '24', '46', '1'), ('1684', '1469044878', '25', '59', '1'), ('1685', '1469044938', '25', '39', '1'), ('1686', '1469044998', '25', '44', '1'), ('1687', '1469045058', '25', '2101', '1'), ('1688', '1469045118', '25', '103', '1'), ('1689', '1469045178', '25', '42', '1'), ('1690', '1469045238', '24', '42', '1'), ('1691', '1469045298', '25', '51', '1'), ('1692', '1469045358', '25', '45', '1'), ('1693', '1469045418', '25', '47', '1'), ('1694', '1469045478', '25', '168', '1'), ('1695', '1469045538', '25', '598', '1'), ('1696', '1469045598', '25', '63', '1'), ('1697', '1469045658', '25', '43', '1'), ('1698', '1469045718', '25', '55', '1'), ('1699', '1469045778', '25', '106', '1'), ('1700', '1469045838', '25', '52', '1');
INSERT INTO `time_diff_log` VALUES ('1701', '1469045898', '25', '47', '1'), ('1702', '1469045958', '25', '43', '1'), ('1703', '1469046018', '25', '161', '1'), ('1704', '1469046078', '25', '120', '0'), ('1705', '1469131325', '0', '0', '0'), ('1706', '1469131385', '32', '5149', '1'), ('1707', '1469131445', '27', '2131', '1'), ('1708', '1469131505', '25', '353', '1'), ('1709', '1469131565', '24', '45', '1'), ('1710', '1469131625', '25', '33', '1'), ('1711', '1469131685', '25', '307', '1'), ('1712', '1469131745', '25', '52', '1'), ('1713', '1469131805', '25', '710', '1'), ('1714', '1469132071', '24', '55', '0'), ('1715', '1469132131', '25', '84', '0'), ('1716', '1469132225', '25', '73', '1'), ('1717', '1469132285', '25', '291', '1'), ('1718', '1469132345', '25', '401', '1'), ('1719', '1469132405', '24', '49', '1'), ('1720', '1469132465', '25', '167', '1'), ('1721', '1469132525', '24', '49', '1'), ('1722', '1469132585', '25', '310', '1'), ('1723', '1469132645', '25', '47', '1'), ('1724', '1469132705', '24', '41', '1'), ('1725', '1469132765', '25', '32', '1'), ('1726', '1469132825', '25', '36', '1'), ('1727', '1469132885', '25', '33', '1'), ('1728', '1469132945', '24', '47', '1'), ('1729', '1469133005', '25', '36', '1'), ('1730', '1469133065', '24', '50', '1'), ('1731', '1469133125', '25', '34', '1'), ('1732', '1469133185', '24', '35', '1'), ('1733', '1469133245', '25', '41', '1'), ('1734', '1469133305', '24', '39', '1'), ('1735', '1469133365', '25', '37', '1'), ('1736', '1469133425', '25', '38', '1'), ('1737', '1469133485', '24', '39', '1'), ('1738', '1469133545', '25', '60', '1'), ('1739', '1469133606', '25', '41', '1'), ('1740', '1469133666', '25', '151', '1'), ('1741', '1469133726', '25', '45', '1'), ('1742', '1469133786', '25', '53', '1'), ('1743', '1469133846', '25', '56', '1'), ('1744', '1469133906', '25', '46', '1'), ('1745', '1469133966', '25', '53', '1'), ('1746', '1469134026', '25', '43', '1'), ('1747', '1469134086', '25', '38', '1'), ('1748', '1469134146', '25', '41', '1'), ('1749', '1469134206', '25', '1127', '1'), ('1750', '1469134266', '25', '198', '1'), ('1751', '1469134326', '25', '45', '1'), ('1752', '1469134386', '25', '39', '1'), ('1753', '1469134446', '25', '56', '1'), ('1754', '1469134506', '25', '42', '1'), ('1755', '1469134566', '24', '38', '1'), ('1756', '1469134626', '25', '48', '1'), ('1757', '1469134686', '25', '39', '1'), ('1758', '1469134746', '24', '43', '1'), ('1759', '1469134806', '24', '44', '1'), ('1760', '1469134866', '25', '47', '1'), ('1761', '1469134926', '24', '35', '1'), ('1762', '1469134986', '25', '32', '1'), ('1763', '1469135046', '24', '36', '1'), ('1764', '1469135106', '25', '34', '1'), ('1765', '1469135166', '24', '35', '1'), ('1766', '1469135226', '25', '36', '1'), ('1767', '1469135286', '25', '41', '1'), ('1768', '1469135346', '25', '53', '1'), ('1769', '1469135406', '25', '38', '1'), ('1770', '1469135466', '24', '39', '1'), ('1771', '1469135526', '25', '42', '1'), ('1772', '1469135586', '24', '41', '1'), ('1773', '1469135646', '25', '41', '1'), ('1774', '1469135706', '24', '41', '1'), ('1775', '1469135766', '25', '63', '1'), ('1776', '1469135826', '25', '49', '1'), ('1777', '1469135886', '25', '41', '1'), ('1778', '1469135946', '24', '34', '1'), ('1779', '1469136006', '25', '44', '1'), ('1780', '1469136066', '25', '104', '1'), ('1781', '1469136126', '25', '84', '1'), ('1782', '1469136186', '25', '62', '1'), ('1783', '1469136246', '25', '38', '1'), ('1784', '1469136306', '25', '42', '1'), ('1785', '1469136366', '25', '37', '1'), ('1786', '1469136426', '24', '42', '1'), ('1787', '1469136486', '25', '39', '1'), ('1788', '1469136546', '25', '40', '1'), ('1789', '1469136606', '25', '39', '1'), ('1790', '1469136666', '25', '54', '1'), ('1791', '1469136726', '25', '39', '1'), ('1792', '1469136786', '25', '39', '1'), ('1793', '1469136846', '25', '37', '1'), ('1794', '1469136906', '25', '41', '1'), ('1795', '1469136966', '25', '36', '1'), ('1796', '1469137026', '25', '37', '1'), ('1797', '1469137086', '24', '51', '1'), ('1798', '1469137146', '25', '36', '1'), ('1799', '1469137206', '25', '38', '1'), ('1800', '1469137266', '25', '37', '1');
INSERT INTO `time_diff_log` VALUES ('1801', '1469137326', '24', '39', '1'), ('1802', '1469137386', '25', '38', '1'), ('1803', '1469137446', '25', '502', '1'), ('1804', '1469137506', '24', '41', '1'), ('1805', '1469137566', '25', '63', '1'), ('1806', '1469137626', '25', '44', '1'), ('1807', '1469137686', '25', '41', '1'), ('1808', '1469137746', '25', '58', '1'), ('1809', '1469137806', '25', '46', '1'), ('1810', '1469198691', '24', '45', '0'), ('1811', '1469198751', '25', '83', '0'), ('1812', '1469198811', '25', '547', '0'), ('1813', '1469198871', '25', '146', '0'), ('1814', '1469198931', '25', '262', '1'), ('1815', '1469198991', '25', '53', '1'), ('1816', '1469199051', '25', '98', '1'), ('1817', '1469199111', '25', '186', '1'), ('1818', '1469199171', '25', '98', '1'), ('1819', '1469199231', '24', '36', '1'), ('1820', '1469199291', '25', '51', '1'), ('1821', '1469199351', '25', '36', '1'), ('1822', '1469199411', '24', '36', '1'), ('1823', '1469199471', '25', '52', '1'), ('1824', '1469199531', '25', '64', '1'), ('1825', '1469199591', '25', '93', '1'), ('1826', '1469199651', '24', '48', '1'), ('1827', '1469199711', '25', '53', '1'), ('1828', '1469199771', '24', '46', '1'), ('1829', '1469199831', '25', '42', '1'), ('1830', '1469199891', '25', '39', '1'), ('1831', '1469199951', '25', '44', '1'), ('1832', '1469200011', '25', '56', '1'), ('1833', '1469200071', '25', '57', '1'), ('1834', '1469200132', '24', '41', '1'), ('1835', '1469200192', '25', '38', '1'), ('1836', '1469200252', '25', '51', '1'), ('1837', '1469200312', '25', '46', '1'), ('1838', '1469200372', '25', '56', '0'), ('1839', '1469200432', '25', '343', '1'), ('1840', '1469200492', '25', '226', '1'), ('1841', '1469200552', '25', '823', '1'), ('1842', '1469200612', '25', '1716', '1'), ('1843', '1469200672', '25', '43', '1'), ('1844', '1469200732', '25', '69', '1'), ('1845', '1469200792', '25', '42', '1'), ('1846', '1469200852', '24', '43', '1'), ('1847', '1469200912', '25', '56', '1'), ('1848', '1469200972', '25', '46', '1'), ('1849', '1469201032', '25', '35', '1'), ('1850', '1469201092', '25', '396', '1'), ('1851', '1469201152', '24', '40', '1'), ('1852', '1469201212', '25', '259', '1'), ('1853', '1469201272', '25', '722', '1'), ('1854', '1469201332', '25', '52', '1'), ('1855', '1469201392', '25', '48', '1'), ('1856', '1469201452', '25', '79', '1'), ('1857', '1469201512', '25', '46', '1'), ('1858', '1469201572', '25', '46', '1'), ('1859', '1469201632', '25', '44', '1'), ('1860', '1469201692', '24', '40', '1'), ('1861', '1469201752', '25', '41', '1'), ('1862', '1469201812', '25', '55', '1'), ('1863', '1469201872', '25', '36', '1'), ('1864', '1469201932', '25', '37', '1'), ('1865', '1469201992', '25', '43', '1'), ('1866', '1469202052', '24', '41', '1'), ('1867', '1469202112', '25', '367', '1'), ('1868', '1469202172', '25', '43', '1'), ('1869', '1469202232', '25', '55', '1'), ('1870', '1469202292', '24', '49', '1'), ('1871', '1469202352', '25', '62', '1'), ('1872', '1469202412', '25', '38', '1'), ('1873', '1469202472', '25', '37', '1'), ('1874', '1469202532', '24', '39', '1'), ('1875', '1469202592', '25', '39', '1'), ('1876', '1469202652', '25', '54', '1'), ('1877', '1469202712', '25', '62', '1'), ('1878', '1469202772', '24', '40', '1'), ('1879', '1469202832', '25', '36', '1'), ('1880', '1469202892', '25', '42', '1'), ('1881', '1469202952', '25', '41', '1'), ('1882', '1469203012', '25', '42', '1'), ('1883', '1469203072', '25', '42', '1'), ('1884', '1469203132', '25', '52', '1'), ('1885', '1469203192', '24', '42', '1'), ('1886', '1469203252', '25', '42', '1'), ('1887', '1469203312', '25', '40', '1'), ('1888', '1469203372', '24', '45', '1'), ('1889', '1469203432', '25', '44', '1'), ('1890', '1469203492', '25', '45', '1'), ('1891', '1469203552', '25', '55', '1'), ('1892', '1469203612', '25', '54', '1'), ('1893', '1469203672', '25', '47', '1'), ('1894', '1469203732', '24', '46', '1'), ('1895', '1469203792', '25', '46', '1'), ('1896', '1469203852', '24', '44', '1'), ('1897', '1469203912', '25', '45', '1'), ('1898', '1469203972', '25', '43', '1'), ('1899', '1469204032', '25', '56', '1'), ('1900', '1469204092', '25', '42', '1');
INSERT INTO `time_diff_log` VALUES ('1901', '1469204152', '25', '50', '1'), ('1902', '1469204212', '24', '41', '1'), ('1903', '1469204272', '25', '46', '1'), ('1904', '1469204332', '25', '60', '1'), ('1905', '1469204392', '25', '46', '1'), ('1906', '1469204452', '25', '65', '1'), ('1907', '1469204512', '25', '36', '1'), ('1908', '1469204572', '24', '45', '1'), ('1909', '1469204632', '25', '39', '1'), ('1910', '1469204692', '25', '55', '1'), ('1911', '1469204752', '25', '40', '1'), ('1912', '1469204812', '25', '56', '1'), ('1913', '1469204872', '25', '47', '1'), ('1914', '1469204932', '25', '53', '1'), ('1915', '1469204992', '25', '41', '1'), ('1916', '1469205052', '24', '42', '1'), ('1917', '1469205112', '25', '40', '1'), ('1918', '1469205172', '24', '46', '1'), ('1919', '1469205232', '25', '48', '1'), ('1920', '1469205292', '25', '60', '1'), ('1921', '1469205352', '25', '61', '1'), ('1922', '1469205412', '25', '50', '1'), ('1923', '1469205472', '25', '41', '1'), ('1924', '1469205532', '25', '38', '1'), ('1925', '1469205592', '25', '66', '1'), ('1926', '1469205652', '25', '57', '1'), ('1927', '1469205712', '25', '43', '1'), ('1928', '1469205773', '25', '50', '1'), ('1929', '1469205833', '25', '68', '1'), ('1930', '1469205893', '24', '49', '1'), ('1931', '1469205953', '25', '46', '1'), ('1932', '1469206013', '25', '40', '1'), ('1933', '1469206073', '25', '36', '1'), ('1934', '1469206133', '24', '33', '1'), ('1935', '1469206193', '25', '479', '1'), ('1936', '1469206253', '25', '64', '1'), ('1937', '1469206313', '24', '44', '1'), ('1938', '1469206373', '25', '93', '1'), ('1939', '1469206433', '25', '259', '1'), ('1940', '1469206493', '25', '37', '1'), ('1941', '1469206553', '24', '42', '1'), ('1942', '1469206613', '25', '32', '1'), ('1943', '1469206673', '25', '38', '1'), ('1944', '1469206783', '25', '669', '0'), ('1945', '1469206843', '25', '415', '0'), ('1946', '1469206903', '25', '563', '0'), ('1947', '1469206963', '25', '37', '0'), ('1948', '1469207023', '25', '49', '0'), ('1949', '1469207083', '24', '40', '0'), ('1950', '1469207143', '25', '34', '0'), ('1951', '1469207203', '25', '44', '0'), ('1952', '1469207263', '24', '50', '0'), ('1953', '1469207323', '25', '32', '0'), ('1954', '1469207383', '25', '58', '0'), ('1955', '1469207443', '25', '31', '0'), ('1956', '1469207503', '25', '32', '0'), ('1957', '1469207563', '24', '33', '0'), ('1958', '1469207623', '25', '39', '0'), ('1959', '1469207683', '25', '34', '0'), ('1960', '1469207743', '25', '33', '0'), ('1961', '1469207803', '24', '35', '0'), ('1962', '1469207863', '25', '34', '0'), ('1963', '1469207923', '24', '34', '0'), ('1964', '1469207983', '24', '34', '0'), ('1965', '1469208043', '25', '33', '0'), ('1966', '1469208103', '25', '40', '0'), ('1967', '1469208163', '24', '34', '0'), ('1968', '1469208223', '25', '33', '0'), ('1969', '1469208302', '25', '88', '0'), ('1970', '1469208362', '25', '130', '0'), ('1971', '1469208423', '25', '60', '0'), ('1972', '1469208483', '25', '41', '0'), ('1973', '1469208543', '25', '53', '0'), ('1974', '1469208603', '25', '63', '0'), ('1975', '1469208663', '25', '36', '1'), ('1976', '1469208891', '25', '76', '0'), ('1977', '1469208951', '25', '89', '0'), ('1978', '1469209011', '25', '95', '1'), ('1979', '1469209071', '25', '57', '1'), ('1980', '1469209131', '25', '353', '1'), ('1981', '1469209191', '24', '49', '1'), ('1982', '1469209251', '25', '39', '1'), ('1983', '1469209311', '25', '58', '1'), ('1984', '1469209371', '25', '38', '1'), ('1985', '1469209431', '25', '64', '1'), ('1986', '1469209491', '25', '33', '1'), ('1987', '1469209551', '25', '30', '1'), ('1988', '1469209622', '25', '78', '0'), ('1989', '1469209683', '25', '85', '0'), ('1990', '1469209743', '25', '64', '0'), ('1991', '1469209803', '25', '41', '0'), ('1992', '1469209863', '25', '48', '0'), ('1993', '1469209923', '24', '41', '0'), ('1994', '1469209983', '25', '34', '0'), ('1995', '1469210043', '25', '41', '0'), ('1996', '1469210103', '25', '35', '0'), ('1997', '1469210163', '25', '31', '0'), ('1998', '1469210223', '25', '62', '0'), ('1999', '1469210283', '25', '32', '0'), ('2000', '1469210343', '25', '31', '0');
INSERT INTO `time_diff_log` VALUES ('2001', '1469210403', '25', '59', '0'), ('2002', '1469210463', '24', '46', '0'), ('2003', '1469210523', '25', '35', '0'), ('2004', '1469210583', '25', '32', '0'), ('2005', '1469210643', '25', '33', '0'), ('2006', '1469210703', '24', '35', '0'), ('2007', '1469210763', '25', '33', '0'), ('2008', '1469210823', '24', '35', '0'), ('2009', '1469210883', '24', '39', '0'), ('2010', '1469210943', '24', '41', '0'), ('2011', '1469211003', '25', '45', '1'), ('2012', '1469211063', '25', '119', '1'), ('2013', '1469211123', '25', '47', '1'), ('2014', '1469211183', '25', '58', '1'), ('2015', '1469211243', '25', '49', '1'), ('2016', '1469211303', '25', '51', '1'), ('2017', '1469211363', '25', '67', '1'), ('2018', '1469211423', '25', '57', '1'), ('2019', '1469211483', '25', '69', '1'), ('2020', '1469211543', '24', '46', '1'), ('2021', '1469211603', '24', '45', '1'), ('2022', '1469211663', '25', '74', '1'), ('2023', '1469211723', '24', '50', '1'), ('2024', '1469211783', '25', '414', '1'), ('2025', '1469211843', '25', '69', '1'), ('2026', '1469211903', '25', '74', '1'), ('2027', '1469211963', '24', '44', '1'), ('2028', '1469212023', '25', '72', '1'), ('2029', '1469212083', '25', '65', '1'), ('2030', '1469212143', '25', '79', '1'), ('2031', '1469212203', '25', '58', '1'), ('2032', '1469212263', '25', '63', '1'), ('2033', '1469212323', '25', '54', '1'), ('2034', '1469212383', '25', '67', '1'), ('2035', '1469212443', '25', '64', '1'), ('2036', '1469212503', '25', '45', '1'), ('2037', '1469212563', '24', '37', '1'), ('2038', '1469212623', '24', '49', '1'), ('2039', '1469212683', '25', '76', '1'), ('2040', '1469212743', '25', '69', '1'), ('2041', '1469212803', '25', '52', '1'), ('2042', '1469212863', '25', '52', '1'), ('2043', '1469212923', '25', '85', '1'), ('2044', '1469212983', '25', '540', '1'), ('2045', '1469213043', '25', '48', '1'), ('2046', '1469213103', '25', '42', '1'), ('2047', '1469213163', '25', '71', '1'), ('2048', '1469213224', '25', '48', '1'), ('2049', '1469213284', '25', '47', '1'), ('2050', '1469213344', '25', '35', '1'), ('2051', '1469213404', '25', '41', '1'), ('2052', '1469213464', '25', '64', '1'), ('2053', '1469213524', '24', '42', '1'), ('2054', '1469213584', '25', '56', '1'), ('2055', '1469213644', '25', '43', '1'), ('2056', '1469213704', '25', '60', '1'), ('2057', '1469213764', '25', '218', '0'), ('2058', '1469464554', '0', '0', '0'), ('2059', '1469464614', '27', '3126', '0'), ('2060', '1469464674', '26', '927', '0'), ('2061', '1469464734', '25', '703', '0'), ('2062', '1469464794', '25', '58', '0'), ('2063', '1469464854', '25', '40', '1'), ('2064', '1469464914', '26', '2894', '1'), ('2065', '1469464974', '25', '628', '1'), ('2066', '1469465034', '25', '161', '1'), ('2067', '1469465094', '25', '44', '1'), ('2068', '1469465154', '25', '239', '1'), ('2069', '1469465214', '25', '43', '1'), ('2070', '1469465274', '25', '44', '1'), ('2071', '1469465334', '25', '968', '1'), ('2072', '1469465394', '25', '431', '1'), ('2073', '1469465454', '25', '153', '1'), ('2074', '1469465514', '25', '60', '1'), ('2075', '1469465574', '25', '73', '1'), ('2076', '1469465634', '25', '67', '1'), ('2077', '1469465694', '25', '62', '1'), ('2078', '1469465754', '25', '55', '1'), ('2079', '1469465814', '25', '70', '1'), ('2080', '1469465874', '25', '76', '1'), ('2081', '1469465934', '25', '60', '1'), ('2082', '1469465994', '25', '51', '1'), ('2083', '1469466054', '25', '81', '1'), ('2084', '1469466114', '25', '139', '1'), ('2085', '1469466174', '25', '69', '1'), ('2086', '1469466234', '25', '52', '1'), ('2087', '1469466294', '25', '178', '1'), ('2088', '1469466354', '25', '68', '1'), ('2089', '1469466414', '25', '69', '1'), ('2090', '1469466474', '25', '50', '1'), ('2091', '1469466534', '25', '71', '1'), ('2092', '1469466594', '25', '69', '1'), ('2093', '1469466654', '25', '63', '1'), ('2094', '1469568570', '0', '0', '0'), ('2095', '1469568630', '28', '2693', '0'), ('2096', '1469568690', '25', '824', '0'), ('2097', '1469568750', '25', '728', '0'), ('2098', '1469568810', '25', '354', '0'), ('2099', '1469568871', '25', '46', '0'), ('2100', '1469568931', '24', '46', '0');
INSERT INTO `time_diff_log` VALUES ('2101', '1469568991', '25', '367', '0'), ('2102', '1469569051', '25', '42', '0'), ('2103', '1469569111', '25', '45', '0'), ('2104', '1469569171', '24', '47', '0'), ('2105', '1469569231', '25', '38', '0'), ('2106', '1469569291', '25', '46', '0'), ('2107', '1469569351', '25', '47', '0'), ('2108', '1469569411', '25', '60', '0'), ('2109', '1469569471', '25', '197', '1'), ('2110', '1469569531', '28', '3827', '1'), ('2111', '1469569591', '25', '59', '1'), ('2112', '1469569651', '25', '56', '1'), ('2113', '1469569711', '24', '50', '1'), ('2114', '1469569771', '25', '457', '1'), ('2115', '1469569831', '25', '43', '1'), ('2116', '1469569891', '25', '59', '1'), ('2117', '1469569951', '25', '44', '1'), ('2118', '1469570011', '25', '37', '1'), ('2119', '1469570071', '25', '73', '1'), ('2120', '1469570131', '25', '43', '1'), ('2121', '1469570191', '25', '43', '1'), ('2122', '1469570251', '25', '50', '1'), ('2123', '1469570311', '25', '65', '1'), ('2124', '1469570371', '24', '43', '1'), ('2125', '1469570431', '25', '46', '1'), ('2126', '1469570491', '25', '44', '1'), ('2127', '1469570551', '24', '51', '1'), ('2128', '1469570613', '25', '47', '1'), ('2129', '1469570673', '26', '3061', '1'), ('2130', '1469570733', '25', '1444', '1'), ('2131', '1469601148', '25', '78', '0'), ('2132', '1469601208', '25', '225', '1'), ('2133', '1469601268', '25', '336', '1'), ('2134', '1469601328', '25', '589', '1'), ('2135', '1469601388', '25', '114', '1'), ('2136', '1469601448', '25', '57', '1'), ('2137', '1469601508', '25', '60', '1'), ('2138', '1469601568', '25', '81', '1'), ('2139', '1469601628', '25', '65', '1'), ('2140', '1469601688', '24', '45', '1'), ('2141', '1469601748', '25', '666', '1'), ('2142', '1469601808', '25', '52', '1'), ('2143', '1469601868', '25', '71', '1'), ('2144', '1469601928', '25', '84', '1'), ('2145', '1469601988', '25', '63', '1'), ('2146', '1469602048', '25', '55', '1'), ('2147', '1469602108', '25', '41', '1'), ('2148', '1469602168', '25', '70', '1'), ('2149', '1469602228', '25', '56', '1'), ('2150', '1469602288', '25', '43', '1'), ('2151', '1469602348', '25', '47', '1'), ('2152', '1469602408', '25', '72', '1'), ('2153', '1469602468', '25', '65', '1'), ('2154', '1469602528', '25', '61', '1'), ('2155', '1469602588', '26', '2890', '1'), ('2156', '1469602648', '25', '76', '1'), ('2157', '1469602708', '25', '239', '1'), ('2158', '1469602768', '25', '53', '1'), ('2159', '1469602828', '25', '44', '1'), ('2160', '1469602888', '25', '58', '1'), ('2161', '1469602948', '25', '78', '1'), ('2162', '1469603008', '24', '47', '1'), ('2163', '1469603068', '25', '48', '1'), ('2164', '1469603128', '24', '49', '1'), ('2165', '1469603188', '25', '86', '1'), ('2166', '1469603248', '25', '356', '1'), ('2167', '1469603308', '25', '69', '1'), ('2168', '1469603368', '25', '173', '1'), ('2169', '1469603428', '25', '86', '1'), ('2170', '1469603488', '25', '53', '1'), ('2171', '1469603548', '25', '65', '1'), ('2172', '1469619463', '25', '81', '1'), ('2173', '1469619523', '25', '261', '1'), ('2174', '1469619583', '25', '345', '1'), ('2175', '1469619643', '25', '71', '1'), ('2176', '1469619703', '25', '79', '1'), ('2177', '1469619763', '25', '123', '1'), ('2178', '1469619823', '25', '46', '1'), ('2179', '1469619883', '25', '77', '1'), ('2180', '1469619943', '25', '54', '1'), ('2181', '1469620003', '25', '39', '1'), ('2182', '1469620063', '25', '47', '1'), ('2183', '1469620123', '25', '47', '1'), ('2184', '1469620183', '25', '52', '1'), ('2185', '1469620243', '25', '50', '1'), ('2186', '1469620303', '25', '73', '1'), ('2187', '1469620363', '25', '72', '1'), ('2188', '1469620423', '25', '48', '1'), ('2189', '1469620483', '25', '55', '1'), ('2190', '1469620543', '25', '56', '1'), ('2191', '1469620603', '25', '40', '1'), ('2192', '1469620663', '25', '43', '1'), ('2193', '1469620723', '25', '45', '1'), ('2194', '1469620783', '25', '73', '1'), ('2195', '1469620843', '25', '46', '1'), ('2196', '1469620903', '24', '43', '1'), ('2197', '1469620963', '25', '51', '1'), ('2198', '1469621023', '25', '49', '1'), ('2199', '1469621083', '25', '45', '1'), ('2200', '1469621143', '25', '45', '1');
INSERT INTO `time_diff_log` VALUES ('2201', '1469621203', '25', '55', '1'), ('2202', '1469621263', '25', '49', '1'), ('2203', '1469621323', '25', '40', '1'), ('2204', '1469621383', '24', '40', '1'), ('2205', '1469621443', '25', '43', '1'), ('2206', '1469621503', '25', '52', '1'), ('2207', '1469621563', '25', '45', '1'), ('2208', '1469621623', '25', '51', '1'), ('2209', '1469621683', '25', '53', '1'), ('2210', '1469621743', '25', '58', '1'), ('2211', '1469621803', '25', '52', '1'), ('2212', '1469621863', '25', '45', '1'), ('2213', '1469621923', '24', '36', '1'), ('2214', '1469621983', '25', '42', '1'), ('2215', '1469622043', '24', '44', '1'), ('2216', '1469622103', '25', '55', '1'), ('2217', '1469622163', '24', '39', '1'), ('2218', '1469622223', '25', '37', '1'), ('2219', '1469622283', '25', '45', '1'), ('2220', '1469622343', '24', '41', '1'), ('2221', '1469622403', '25', '34', '1'), ('2222', '1469622463', '24', '44', '1'), ('2223', '1469622523', '25', '45', '1'), ('2224', '1469622583', '25', '54', '1'), ('2225', '1469622643', '25', '42', '1'), ('2226', '1469622703', '25', '45', '1'), ('2227', '1469622763', '25', '47', '1'), ('2228', '1469622823', '24', '37', '1'), ('2229', '1469622883', '25', '43', '1'), ('2230', '1469622943', '25', '43', '1'), ('2231', '1469623003', '25', '172', '1'), ('2232', '1469623063', '25', '43', '1'), ('2233', '1469623123', '25', '43', '1'), ('2234', '1469623183', '25', '37', '1'), ('2235', '1469623243', '24', '44', '1'), ('2236', '1469623303', '25', '44', '1'), ('2237', '1469623363', '25', '45', '1'), ('2238', '1469623423', '25', '63', '1'), ('2239', '1469623483', '24', '40', '1'), ('2240', '1469623543', '25', '45', '1'), ('2241', '1469623603', '25', '36', '1'), ('2242', '1469623663', '25', '217', '1'), ('2243', '1469623723', '25', '44', '1'), ('2244', '1469623783', '24', '42', '1'), ('2245', '1469623843', '25', '38', '1'), ('2246', '1469623904', '25', '63', '1'), ('2247', '1469623964', '25', '44', '1'), ('2248', '1469624024', '24', '40', '1'), ('2249', '1469624084', '24', '39', '1'), ('2250', '1469624144', '25', '44', '1'), ('2251', '1469624204', '25', '34', '1'), ('2252', '1469624264', '25', '44', '1'), ('2253', '1469624324', '25', '54', '1'), ('2254', '1469624384', '25', '39', '1'), ('2255', '1469624444', '25', '45', '1'), ('2256', '1469624504', '24', '39', '1'), ('2257', '1469624564', '25', '44', '1'), ('2258', '1469624624', '25', '44', '1'), ('2259', '1469624684', '25', '44', '1'), ('2260', '1469624744', '25', '45', '1'), ('2261', '1469624804', '25', '59', '1'), ('2262', '1469624864', '25', '46', '1'), ('2263', '1469624924', '24', '41', '1'), ('2264', '1469624984', '25', '44', '1'), ('2265', '1469625044', '25', '39', '1'), ('2266', '1469625104', '24', '42', '1'), ('2267', '1469625164', '25', '45', '1'), ('2268', '1469625224', '25', '61', '1'), ('2269', '1469625284', '25', '40', '1'), ('2270', '1469625344', '25', '58', '1'), ('2271', '1469625404', '25', '43', '1'), ('2272', '1469625464', '24', '45', '1'), ('2273', '1469625524', '25', '44', '1'), ('2274', '1469625584', '25', '67', '1'), ('2275', '1469625644', '25', '47', '1'), ('2276', '1469625704', '25', '77', '1'), ('2277', '1469625764', '24', '48', '1'), ('2278', '1469625824', '25', '54', '1'), ('2279', '1469625884', '25', '51', '1'), ('2280', '1469625944', '25', '47', '1'), ('2281', '1469626004', '24', '44', '1'), ('2282', '1469626064', '25', '48', '1'), ('2283', '1469626124', '25', '61', '1'), ('2284', '1469626184', '25', '51', '1'), ('2285', '1469626244', '25', '50', '1'), ('2286', '1469626304', '24', '39', '1'), ('2287', '1469626364', '25', '53', '1'), ('2288', '1469626424', '24', '54', '1'), ('2289', '1469626484', '25', '43', '1'), ('2290', '1469626544', '25', '68', '1'), ('2291', '1469626604', '24', '53', '1'), ('2292', '1469626664', '25', '45', '1'), ('2293', '1469626724', '25', '215', '1'), ('2294', '1469626784', '24', '50', '1'), ('2295', '1469626844', '25', '55', '1'), ('2296', '1469626904', '24', '45', '1'), ('2297', '1469626964', '25', '44', '1'), ('2298', '1469627024', '25', '64', '1'), ('2299', '1469627084', '25', '42', '1'), ('2300', '1469627144', '25', '52', '1');
INSERT INTO `time_diff_log` VALUES ('2301', '1469627204', '25', '46', '1'), ('2302', '1469627264', '25', '45', '1'), ('2303', '1469627324', '25', '35', '1'), ('2304', '1469627384', '25', '49', '1'), ('2305', '1469627444', '25', '62', '1'), ('2306', '1469627504', '25', '42', '1'), ('2307', '1469627564', '25', '43', '1'), ('2308', '1469627624', '25', '51', '1'), ('2309', '1469627684', '25', '41', '1'), ('2310', '1469627744', '25', '41', '1'), ('2311', '1469627804', '25', '42', '1'), ('2312', '1469627864', '24', '46', '1'), ('2313', '1469627924', '25', '1652', '1'), ('2314', '1469627984', '25', '37', '1'), ('2315', '1469628044', '24', '39', '1'), ('2316', '1469628104', '24', '36', '1'), ('2317', '1469628164', '25', '37', '1'), ('2318', '1469628224', '25', '38', '1'), ('2319', '1469628284', '24', '37', '1'), ('2320', '1469628344', '25', '55', '1'), ('2321', '1469628404', '25', '37', '1'), ('2322', '1469628464', '24', '37', '1'), ('2323', '1469628524', '25', '34', '1'), ('2324', '1469628584', '25', '32', '1'), ('2325', '1469628644', '25', '48', '1'), ('2326', '1469628704', '25', '33', '1'), ('2327', '1469628764', '24', '36', '1'), ('2328', '1469628824', '25', '42', '1'), ('2329', '1469628884', '25', '37', '1'), ('2330', '1469628944', '25', '36', '1'), ('2331', '1469629004', '25', '36', '1'), ('2332', '1469629064', '24', '35', '1'), ('2333', '1469629124', '25', '32', '1'), ('2334', '1469629185', '24', '35', '1'), ('2335', '1469629245', '25', '47', '1'), ('2336', '1469629305', '25', '32', '1'), ('2337', '1469629365', '25', '34', '1'), ('2338', '1469629425', '25', '36', '1'), ('2339', '1469629485', '24', '35', '1'), ('2340', '1469629545', '25', '34', '1'), ('2341', '1469629605', '25', '34', '1'), ('2342', '1469629665', '25', '37', '1'), ('2343', '1469629725', '25', '178', '1'), ('2344', '1469629785', '25', '40', '1'), ('2345', '1469629845', '25', '42', '1'), ('2346', '1469629905', '24', '42', '1'), ('2347', '1469629965', '24', '40', '1'), ('2348', '1469630025', '25', '40', '1'), ('2349', '1469630085', '24', '39', '1'), ('2350', '1469630145', '25', '55', '1'), ('2351', '1469630205', '25', '40', '1'), ('2352', '1469630265', '25', '43', '1'), ('2353', '1469630325', '24', '35', '1'), ('2354', '1469630385', '25', '36', '1'), ('2355', '1469630445', '25', '39', '1'), ('2356', '1469630505', '25', '40', '1'), ('2357', '1469630565', '25', '54', '1'), ('2358', '1469630625', '24', '36', '1'), ('2359', '1469630685', '25', '42', '1'), ('2360', '1469630745', '25', '41', '1'), ('2361', '1469630805', '25', '38', '1'), ('2362', '1469630865', '25', '40', '1'), ('2363', '1469630925', '25', '40', '1'), ('2364', '1469630985', '25', '43', '1'), ('2365', '1469631045', '25', '58', '1'), ('2366', '1469631105', '25', '39', '1'), ('2367', '1469631165', '25', '61', '1'), ('2368', '1469631225', '25', '38', '1'), ('2369', '1469631285', '24', '49', '1'), ('2370', '1469631345', '26', '2566', '1'), ('2371', '1469631405', '25', '43', '1'), ('2372', '1469631465', '25', '66', '1'), ('2373', '1469631525', '25', '43', '1'), ('2374', '1469631585', '25', '520', '1'), ('2375', '1469631645', '25', '49', '1'), ('2376', '1469631705', '25', '61', '1'), ('2377', '1469631765', '25', '52', '1'), ('2378', '1469631825', '25', '50', '1'), ('2379', '1469631885', '24', '46', '1'), ('2380', '1469631945', '25', '55', '1'), ('2381', '1469632005', '25', '52', '1'), ('2382', '1469632065', '25', '53', '1'), ('2383', '1469632125', '25', '52', '1'), ('2384', '1469632185', '25', '47', '1'), ('2385', '1469632245', '24', '51', '1'), ('2386', '1469632305', '25', '47', '1'), ('2387', '1469632365', '25', '82', '1'), ('2388', '1469632425', '24', '49', '1'), ('2389', '1469632485', '25', '60', '1'), ('2390', '1469726881', '0', '0', '0'), ('2391', '1469726941', '27', '2636', '0'), ('2392', '1469727001', '25', '1836', '0'), ('2393', '1469727061', '25', '786', '0'), ('2394', '1469727121', '25', '756', '0'), ('2395', '1469727181', '25', '31', '0'), ('2396', '1469727241', '24', '34', '0'), ('2397', '1469727301', '25', '41', '0'), ('2398', '1469727361', '25', '626', '0'), ('2399', '1469727421', '25', '632', '0'), ('2400', '1469727481', '25', '94', '1');
INSERT INTO `time_diff_log` VALUES ('2401', '1469727541', '26', '2232', '1'), ('2402', '1469727601', '25', '55', '1'), ('2403', '1469727661', '25', '259', '1'), ('2404', '1469727721', '25', '56', '1'), ('2405', '1469727781', '25', '314', '1'), ('2406', '1469727841', '25', '44', '1'), ('2407', '1469727901', '25', '40', '1'), ('2408', '1469727961', '25', '41', '1'), ('2409', '1469728021', '25', '40', '1'), ('2410', '1469728081', '25', '40', '1'), ('2411', '1469728141', '25', '58', '1'), ('2412', '1469728201', '25', '46', '1'), ('2413', '1469728261', '25', '42', '1'), ('2414', '1469728321', '24', '40', '1'), ('2415', '1469728381', '25', '77', '1'), ('2416', '1469728441', '25', '66', '1'), ('2417', '1469728501', '25', '73', '1'), ('2418', '1469728561', '24', '41', '1'), ('2419', '1469728621', '25', '55', '1'), ('2420', '1469728681', '25', '76', '1'), ('2421', '1469728741', '25', '38', '1'), ('2422', '1469728801', '25', '236', '1'), ('2423', '1469728861', '25', '50', '1'), ('2424', '1469728921', '25', '46', '1'), ('2425', '1469728981', '25', '42', '1'), ('2426', '1469729041', '25', '51', '1'), ('2427', '1469729101', '25', '41', '1'), ('2428', '1469729161', '25', '44', '1'), ('2429', '1469729221', '24', '42', '1'), ('2430', '1469729281', '25', '41', '1'), ('2431', '1469729341', '25', '76', '1'), ('2432', '1469729401', '25', '58', '1'), ('2433', '1469729461', '25', '55', '1'), ('2434', '1469729521', '25', '122', '1'), ('2435', '1469729581', '24', '45', '1'), ('2436', '1469729641', '25', '61', '1'), ('2437', '1469729701', '25', '49', '1'), ('2438', '1469729761', '25', '66', '1'), ('2439', '1469729821', '25', '37', '1'), ('2440', '1469729881', '25', '53', '1'), ('2441', '1469729941', '25', '149', '1'), ('2442', '1469730001', '25', '46', '1'), ('2443', '1469730061', '25', '42', '1'), ('2444', '1469730121', '25', '44', '1'), ('2445', '1469730181', '25', '79', '1'), ('2446', '1469730241', '25', '44', '1'), ('2447', '1469730301', '25', '47', '1'), ('2448', '1469730361', '24', '43', '1'), ('2449', '1469730421', '25', '68', '1'), ('2450', '1469730481', '25', '591', '1'), ('2451', '1469730541', '25', '715', '1'), ('2452', '1469730601', '25', '61', '0'), ('2453', '1469730661', '25', '35', '0'), ('2454', '1469730721', '24', '46', '0'), ('2455', '1469730781', '25', '37', '0'), ('2456', '1469730841', '24', '41', '0'), ('2457', '1469730901', '25', '34', '0'), ('2458', '1469730961', '24', '34', '0'), ('2459', '1469731021', '25', '35', '0'), ('2460', '1469731081', '25', '32', '0'), ('2461', '1469731141', '24', '35', '0'), ('2462', '1469731201', '25', '35', '0'), ('2463', '1469731261', '24', '39', '0'), ('2464', '1469731321', '25', '34', '0'), ('2465', '1469731381', '24', '35', '0'), ('2466', '1469731441', '25', '35', '0'), ('2467', '1469731501', '25', '44', '0'), ('2468', '1469731561', '24', '37', '0'), ('2469', '1469731621', '25', '34', '0'), ('2470', '1469731681', '25', '35', '0'), ('2471', '1469731741', '24', '43', '0'), ('2472', '1469731801', '25', '39', '0'), ('2473', '1469731862', '25', '33', '0'), ('2474', '1469731922', '25', '34', '0'), ('2475', '1469731982', '25', '35', '0'), ('2476', '1469732042', '24', '32', '0'), ('2477', '1469732102', '25', '35', '0'), ('2478', '1469732162', '24', '43', '0'), ('2479', '1469732222', '25', '36', '0'), ('2480', '1469732282', '25', '31', '0'), ('2481', '1469732342', '25', '34', '0'), ('2482', '1469732402', '24', '34', '0'), ('2483', '1469732462', '25', '31', '0'), ('2484', '1469732522', '25', '32', '0'), ('2485', '1469732582', '25', '37', '0'), ('2486', '1469732642', '24', '41', '0'), ('2487', '1469732702', '25', '33', '0'), ('2488', '1469732762', '24', '33', '0'), ('2489', '1469732822', '24', '31', '0'), ('2490', '1469732882', '25', '34', '0'), ('2491', '1469732942', '25', '37', '0'), ('2492', '1469733002', '25', '33', '0'), ('2493', '1469733062', '24', '40', '0'), ('2494', '1469733122', '25', '33', '0'), ('2495', '1469733182', '25', '33', '0'), ('2496', '1469733242', '25', '36', '0'), ('2497', '1469733302', '25', '33', '0'), ('2498', '1469733362', '24', '33', '0'), ('2499', '1469733422', '25', '32', '0'), ('2500', '1469733482', '25', '33', '0');
INSERT INTO `time_diff_log` VALUES ('2501', '1469733542', '25', '45', '0'), ('2502', '1469733602', '24', '33', '0'), ('2503', '1469733662', '25', '31', '0'), ('2504', '1469733722', '25', '33', '0'), ('2505', '1469733782', '25', '34', '0'), ('2506', '1469733842', '25', '33', '0'), ('2507', '1469733902', '25', '305', '0'), ('2508', '1469733962', '25', '39', '0'), ('2509', '1469734022', '25', '32', '0'), ('2510', '1469734082', '25', '34', '0'), ('2511', '1469734142', '24', '34', '0'), ('2512', '1469734202', '25', '34', '0'), ('2513', '1469734262', '25', '33', '0'), ('2514', '1469734322', '25', '35', '0'), ('2515', '1469734382', '25', '35', '0'), ('2516', '1469734442', '24', '42', '0'), ('2517', '1469734502', '25', '33', '0'), ('2518', '1469734562', '25', '33', '0'), ('2519', '1469734622', '25', '34', '0'), ('2520', '1469734682', '25', '35', '0'), ('2521', '1469734742', '25', '32', '0'), ('2522', '1469734802', '24', '34', '0'), ('2523', '1469734862', '25', '42', '0'), ('2524', '1469734922', '25', '31', '0'), ('2525', '1469734982', '25', '33', '0'), ('2526', '1469735042', '25', '33', '0'), ('2527', '1469735102', '25', '32', '0'), ('2528', '1469735162', '24', '32', '0'), ('2529', '1469735222', '25', '33', '0'), ('2530', '1469735282', '25', '44', '0'), ('2531', '1469735342', '25', '35', '0'), ('2532', '1469735402', '25', '34', '0'), ('2533', '1469735462', '24', '32', '0'), ('2534', '1469735522', '25', '35', '0'), ('2535', '1469735582', '24', '34', '0'), ('2536', '1469735642', '25', '34', '0'), ('2537', '1469735702', '24', '34', '0'), ('2538', '1469735762', '25', '43', '0'), ('2539', '1469735822', '25', '33', '0'), ('2540', '1469735882', '24', '35', '0'), ('2541', '1469735942', '25', '32', '0'), ('2542', '1469736002', '24', '33', '0'), ('2543', '1469736062', '25', '33', '0'), ('2544', '1469736122', '25', '31', '0'), ('2545', '1469736182', '25', '38', '0'), ('2546', '1469736242', '24', '34', '0'), ('2547', '1469736302', '25', '35', '0'), ('2548', '1469736362', '25', '34', '0'), ('2549', '1469736422', '25', '33', '0'), ('2550', '1469736482', '25', '32', '0'), ('2551', '1469736542', '25', '33', '0'), ('2552', '1469736602', '24', '33', '0'), ('2553', '1469736662', '25', '42', '0'), ('2554', '1469736722', '25', '31', '0'), ('2555', '1469736782', '25', '34', '0'), ('2556', '1469736842', '24', '36', '0'), ('2557', '1469736902', '24', '33', '0'), ('2558', '1469736962', '25', '32', '0'), ('2559', '1469737022', '25', '34', '0'), ('2560', '1469737083', '24', '41', '0'), ('2561', '1469737143', '25', '31', '0'), ('2562', '1469737203', '25', '33', '0'), ('2563', '1469737263', '24', '34', '0'), ('2564', '1469737323', '25', '35', '0'), ('2565', '1469737383', '25', '32', '0'), ('2566', '1469737443', '25', '33', '0'), ('2567', '1469737503', '25', '35', '0'), ('2568', '1469737563', '24', '43', '0'), ('2569', '1469737623', '25', '37', '0'), ('2570', '1469737683', '24', '34', '0'), ('2571', '1469737743', '25', '31', '0'), ('2572', '1469737803', '25', '32', '0'), ('2573', '1469737863', '24', '33', '0'), ('2574', '1469737923', '25', '32', '0'), ('2575', '1469737983', '24', '43', '0'), ('2576', '1469738043', '25', '32', '0'), ('2577', '1469738103', '25', '33', '0'), ('2578', '1469738163', '25', '36', '0'), ('2579', '1469738223', '25', '33', '0'), ('2580', '1469738283', '24', '35', '0'), ('2581', '1469738343', '25', '36', '0'), ('2582', '1469738403', '25', '40', '0'), ('2583', '1469738463', '24', '34', '0'), ('2584', '1469738523', '25', '35', '0'), ('2585', '1469738583', '25', '33', '0'), ('2586', '1469738643', '24', '33', '0'), ('2587', '1469738703', '25', '35', '0'), ('2588', '1469738763', '24', '31', '0'), ('2589', '1469738823', '25', '38', '0'), ('2590', '1469738883', '25', '49', '0'), ('2591', '1471633508', '0', '0', '0'), ('2592', '1471633568', '29', '2992', '0'), ('2593', '1471633628', '25', '868', '0'), ('2594', '1471633688', '25', '639', '0'), ('2595', '1471633748', '25', '101', '0'), ('2596', '1471633808', '25', '33', '0'), ('2597', '1471633868', '25', '1325', '0'), ('2598', '1471633928', '25', '94', '0'), ('2599', '1471633988', '25', '36', '0'), ('2600', '1471634048', '25', '157', '1');
INSERT INTO `time_diff_log` VALUES ('2601', '1471634108', '27', '4540', '1'), ('2602', '1471634168', '25', '321', '1'), ('2603', '1471634228', '25', '48', '1'), ('2604', '1471634288', '25', '46', '1'), ('2605', '1471634348', '24', '44', '1'), ('2606', '1471634408', '25', '155', '1'), ('2607', '1471634468', '25', '280', '1'), ('2608', '1471634528', '25', '63', '1'), ('2609', '1471634588', '25', '847', '1'), ('2610', '1471634648', '25', '34', '1'), ('2611', '1471634708', '25', '34', '1'), ('2612', '1471634768', '25', '38', '1'), ('2613', '1471634828', '25', '33', '1'), ('2614', '1471634888', '25', '33', '1'), ('2615', '1471634948', '25', '36', '1'), ('2616', '1471635008', '25', '35', '1'), ('2617', '1471635068', '24', '35', '1'), ('2618', '1471635128', '24', '36', '1'), ('2619', '1471635188', '25', '44', '1'), ('2620', '1471635248', '24', '36', '1'), ('2621', '1471635308', '25', '37', '1'), ('2622', '1471635368', '25', '34', '1'), ('2623', '1471635428', '25', '39', '1'), ('2624', '1471635488', '25', '39', '1'), ('2625', '1471635548', '25', '41', '1'), ('2626', '1471635608', '24', '38', '1'), ('2627', '1471635668', '25', '47', '1'), ('2628', '1471635728', '25', '39', '1'), ('2629', '1471635788', '24', '35', '1'), ('2630', '1471635848', '25', '39', '1'), ('2631', '1471635908', '25', '39', '1'), ('2632', '1471635968', '24', '36', '1'), ('2633', '1471636028', '24', '39', '1'), ('2634', '1471636088', '25', '391', '1'), ('2635', '1471636148', '24', '39', '1'), ('2636', '1471636208', '25', '34', '1'), ('2637', '1471636268', '25', '40', '1'), ('2638', '1471636328', '25', '39', '1'), ('2639', '1471636388', '24', '35', '1'), ('2640', '1471636448', '25', '37', '1'), ('2641', '1471636508', '24', '40', '1'), ('2642', '1471636568', '25', '49', '1'), ('2643', '1471636628', '24', '38', '1'), ('2644', '1471636688', '25', '48', '1'), ('2645', '1471636748', '24', '40', '1'), ('2646', '1471636808', '25', '40', '1'), ('2647', '1471636868', '25', '134', '1'), ('2648', '1471636928', '25', '92', '1'), ('2649', '1471636989', '25', '276', '1'), ('2650', '1471637049', '25', '39', '1'), ('2651', '1471637109', '25', '40', '1'), ('2652', '1471637169', '24', '34', '1'), ('2653', '1471637229', '25', '918', '1'), ('2654', '1471637289', '25', '40', '1'), ('2655', '1471637349', '25', '99', '1'), ('2656', '1471637409', '25', '38', '1'), ('2657', '1471637469', '24', '45', '1'), ('2658', '1471637529', '25', '39', '1'), ('2659', '1471637589', '25', '33', '1'), ('2660', '1471637649', '24', '41', '1'), ('2661', '1471637709', '25', '39', '1'), ('2662', '1471637769', '24', '40', '1'), ('2663', '1471637829', '24', '34', '1'), ('2664', '1471637889', '25', '47', '1'), ('2665', '1471637949', '25', '40', '1'), ('2666', '1471638009', '25', '35', '1'), ('2667', '1471638069', '24', '37', '1'), ('2668', '1471638129', '25', '38', '1'), ('2669', '1471638189', '24', '35', '1'), ('2670', '1471638249', '25', '38', '1'), ('2671', '1471638309', '25', '929', '1'), ('2672', '1471638369', '25', '45', '1'), ('2673', '1471638429', '24', '41', '1'), ('2674', '1471638489', '24', '36', '1'), ('2675', '1471638549', '25', '54', '1'), ('2676', '1471638609', '25', '40', '1'), ('2677', '1471638669', '25', '58', '1'), ('2678', '1471638729', '25', '39', '1'), ('2679', '1471638789', '24', '48', '1'), ('2680', '1471638849', '25', '39', '1'), ('2681', '1471638909', '25', '37', '1'), ('2682', '1471638969', '25', '39', '1'), ('2683', '1471639029', '25', '39', '1'), ('2684', '1471639089', '25', '38', '1'), ('2685', '1471639149', '24', '49', '1'), ('2686', '1471639209', '25', '46', '1'), ('2687', '1471639269', '24', '35', '1'), ('2688', '1471639329', '25', '40', '1'), ('2689', '1471639389', '25', '38', '1'), ('2690', '1471639449', '24', '37', '1'), ('2691', '1471639509', '24', '39', '1'), ('2692', '1471639569', '25', '39', '1'), ('2693', '1471639629', '24', '38', '1'), ('2694', '1471639689', '25', '46', '1'), ('2695', '1471639749', '25', '75', '1'), ('2696', '1471639809', '25', '38', '1'), ('2697', '1471639869', '25', '39', '1'), ('2698', '1471639929', '24', '40', '1'), ('2699', '1471639989', '25', '40', '1'), ('2700', '1471640049', '25', '39', '1');
INSERT INTO `time_diff_log` VALUES ('2701', '1471640109', '25', '46', '1'), ('2702', '1471640169', '24', '38', '1'), ('2703', '1471640229', '25', '41', '1'), ('2704', '1471640289', '24', '33', '1'), ('2705', '1471640349', '25', '37', '1'), ('2706', '1471640409', '25', '39', '1'), ('2707', '1471640469', '24', '36', '1'), ('2708', '1471640529', '25', '35', '1'), ('2709', '1471640589', '25', '39', '1'), ('2710', '1471640649', '25', '34', '1'), ('2711', '1471640709', '25', '35', '1'), ('2712', '1471640769', '24', '35', '1'), ('2713', '1471640829', '25', '35', '1'), ('2714', '1471640889', '24', '35', '1'), ('2715', '1471640949', '24', '36', '1'), ('2716', '1471641009', '25', '40', '1'), ('2717', '1471641069', '25', '33', '1'), ('2718', '1471641129', '25', '35', '1'), ('2719', '1471641189', '25', '36', '1'), ('2720', '1471641249', '25', '35', '1'), ('2721', '1471641309', '25', '31', '1'), ('2722', '1471641369', '24', '35', '1'), ('2723', '1471641429', '24', '36', '1'), ('2724', '1471641489', '25', '42', '1'), ('2725', '1471641549', '24', '33', '1'), ('2726', '1471641609', '25', '35', '1'), ('2727', '1471641669', '25', '35', '1'), ('2728', '1471641729', '24', '34', '1'), ('2729', '1471641789', '25', '35', '1'), ('2730', '1471641849', '25', '36', '1'), ('2731', '1471641909', '25', '41', '1'), ('2732', '1471641969', '24', '34', '1'), ('2733', '1471642029', '24', '35', '1'), ('2734', '1471642089', '25', '31', '1'), ('2735', '1471642149', '24', '44', '1'), ('2736', '1471642209', '25', '39', '1'), ('2737', '1471642269', '25', '642', '1'), ('2738', '1471642329', '25', '304', '1'), ('2739', '1471642390', '24', '33', '1'), ('2740', '1471642450', '25', '34', '1'), ('2741', '1471642510', '24', '34', '1'), ('2742', '1471642570', '25', '604', '1'), ('2743', '1471642630', '25', '34', '1'), ('2744', '1471642690', '24', '33', '1'), ('2745', '1471642750', '25', '319', '1'), ('2746', '1471642810', '25', '40', '1'), ('2747', '1471642870', '25', '39', '1'), ('2748', '1471642930', '25', '37', '1'), ('2749', '1471642990', '25', '37', '1'), ('2750', '1471643050', '24', '39', '1'), ('2751', '1471643110', '25', '33', '1'), ('2752', '1471643170', '25', '36', '1'), ('2753', '1471643230', '24', '47', '1'), ('2754', '1471643290', '24', '39', '1'), ('2755', '1471643350', '25', '39', '1'), ('2756', '1471643410', '25', '36', '1'), ('2757', '1471643470', '25', '40', '1'), ('2758', '1471643530', '25', '37', '1'), ('2759', '1471643590', '25', '35', '1'), ('2760', '1471643650', '24', '37', '1'), ('2761', '1471643710', '25', '50', '1'), ('2762', '1471643770', '24', '35', '1'), ('2763', '1471643830', '25', '38', '1'), ('2764', '1471643890', '25', '37', '1'), ('2765', '1471643950', '24', '40', '1'), ('2766', '1471644010', '25', '37', '1'), ('2767', '1471644070', '25', '37', '1'), ('2768', '1471644130', '25', '46', '1'), ('2769', '1471644190', '24', '38', '1'), ('2770', '1471644250', '25', '41', '1'), ('2771', '1471644310', '24', '39', '1'), ('2772', '1471644370', '25', '34', '1'), ('2773', '1471644430', '24', '40', '1'), ('2774', '1471644490', '25', '38', '1'), ('2775', '1471644550', '25', '38', '1'), ('2776', '1471644610', '25', '50', '1'), ('2777', '1471644670', '24', '37', '1'), ('2778', '1471644730', '25', '38', '1'), ('2779', '1471644790', '25', '34', '1'), ('2780', '1471644850', '25', '35', '1'), ('2781', '1471644910', '25', '38', '1'), ('2782', '1471644970', '24', '35', '1'), ('2783', '1471645030', '25', '45', '1'), ('2784', '1471645090', '25', '39', '1'), ('2785', '1471645150', '24', '40', '1'), ('2786', '1471645210', '25', '48', '1'), ('2787', '1471645270', '24', '38', '1'), ('2788', '1471645330', '25', '40', '1'), ('2789', '1471645390', '25', '31', '1'), ('2790', '1471645450', '25', '39', '1'), ('2791', '1471645510', '25', '47', '1'), ('2792', '1471645570', '24', '38', '1'), ('2793', '1471705918', '0', '0', '0'), ('2794', '1471705978', '33', '5236', '1'), ('2795', '1471706038', '27', '3009', '1'), ('2796', '1471706098', '25', '473', '1'), ('2797', '1471706158', '25', '681', '1'), ('2798', '1471706218', '25', '56', '1'), ('2799', '1471706278', '25', '37', '1'), ('2800', '1471706338', '25', '44', '1');
INSERT INTO `time_diff_log` VALUES ('2801', '1471706398', '25', '36', '1'), ('2802', '1471706458', '25', '444', '1'), ('2803', '1471706518', '25', '44', '1'), ('2804', '1471706578', '25', '34', '1'), ('2805', '1471706638', '25', '40', '1'), ('2806', '1471706698', '25', '40', '1'), ('2807', '1471706758', '25', '50', '1'), ('2808', '1471706818', '24', '39', '1'), ('2809', '1471706878', '25', '148', '1'), ('2810', '1471706938', '25', '430', '1'), ('2811', '1471706998', '24', '43', '1'), ('2812', '1471707058', '25', '41', '1'), ('2813', '1471707118', '25', '38', '1'), ('2814', '1471707178', '24', '38', '1'), ('2815', '1471707238', '25', '136', '1'), ('2816', '1471707298', '25', '1208', '1'), ('2817', '1471707358', '25', '491', '1'), ('2818', '1471707418', '25', '43', '1'), ('2819', '1471707478', '24', '42', '1'), ('2820', '1471707538', '24', '39', '1'), ('2821', '1471707598', '25', '54', '1'), ('2822', '1471707658', '25', '630', '1'), ('2823', '1471707718', '25', '56', '1'), ('2824', '1471707778', '24', '37', '1'), ('2825', '1471707838', '25', '35', '1'), ('2826', '1471707898', '25', '41', '1'), ('2827', '1471707958', '25', '43', '1'), ('2828', '1471708018', '25', '53', '1'), ('2829', '1471708078', '24', '47', '1'), ('2830', '1471708138', '25', '40', '1'), ('2831', '1471708198', '25', '39', '1'), ('2832', '1471708258', '25', '92', '1'), ('2833', '1471708318', '25', '40', '1'), ('2834', '1471708378', '24', '31', '1'), ('2835', '1471708438', '25', '39', '1'), ('2836', '1471708498', '25', '38', '1'), ('2837', '1471708558', '25', '52', '1'), ('2838', '1471708618', '25', '39', '1'), ('2839', '1471708678', '25', '39', '1'), ('2840', '1471708738', '25', '42', '1'), ('2841', '1471708798', '25', '330', '1'), ('2842', '1471708858', '25', '83', '1'), ('2843', '1471708918', '25', '41', '1'), ('2844', '1471708978', '25', '48', '1'), ('2845', '1471709038', '24', '39', '1'), ('2846', '1471709098', '24', '48', '1'), ('2847', '1471709158', '25', '40', '1'), ('2848', '1471709218', '25', '40', '1'), ('2849', '1471709278', '25', '59', '1'), ('2850', '1471709338', '25', '57', '1'), ('2851', '1471709398', '25', '421', '1'), ('2852', '1471709458', '25', '46', '1'), ('2853', '1471709518', '25', '39', '1'), ('2854', '1471709578', '24', '42', '1'), ('2855', '1471709638', '24', '40', '1'), ('2856', '1471709698', '25', '41', '1'), ('2857', '1471709758', '25', '39', '1'), ('2858', '1471709818', '25', '40', '1'), ('2859', '1471709878', '24', '47', '1'), ('2860', '1471709938', '25', '38', '1'), ('2861', '1471709998', '25', '686', '1'), ('2862', '1471710058', '25', '40', '1'), ('2863', '1471710118', '25', '37', '1'), ('2864', '1471710178', '25', '40', '1'), ('2865', '1471710238', '24', '39', '1'), ('2866', '1471710298', '24', '37', '1'), ('2867', '1471984053', '0', '0', '0'), ('2868', '1471984113', '29', '3928', '0'), ('2869', '1471984173', '25', '987', '0'), ('2870', '1471984233', '25', '55', '0'), ('2871', '1471984293', '25', '72', '0'), ('2872', '1471984353', '25', '38', '0'), ('2873', '1471984413', '25', '42', '0'), ('2874', '1471984473', '25', '597', '0'), ('2875', '1471984533', '24', '41', '0'), ('2876', '1471984593', '25', '42', '0'), ('2877', '1471984653', '25', '45', '0'), ('2878', '1471984713', '25', '35', '0'), ('2879', '1471984773', '25', '43', '0'), ('2880', '1471984833', '25', '44', '0'), ('2881', '1471984893', '25', '62', '0'), ('2882', '1471984953', '25', '43', '0'), ('2883', '1471985013', '25', '45', '0'), ('2884', '1471985073', '25', '45', '0'), ('2885', '1471985133', '24', '48', '0'), ('2886', '1471985194', '25', '204', '0'), ('2887', '1471985254', '25', '320', '0'), ('2888', '1471985314', '25', '182', '0'), ('2889', '1471985374', '25', '42', '0'), ('2890', '1471985434', '24', '41', '0'), ('2891', '1471985494', '24', '38', '0'), ('2892', '1471985554', '25', '42', '0'), ('2893', '1471985614', '24', '43', '0'), ('2894', '1471985674', '25', '45', '0'), ('2895', '1471985734', '25', '40', '0'), ('2896', '1471985794', '25', '55', '0'), ('2897', '1471985854', '24', '45', '0'), ('2898', '1471985914', '25', '40', '0'), ('2899', '1471985974', '25', '40', '0'), ('2900', '1471986034', '25', '50', '0');
INSERT INTO `time_diff_log` VALUES ('2901', '1471986094', '25', '46', '0'), ('2902', '1471986154', '24', '46', '0'), ('2903', '1471986214', '25', '53', '0'), ('2904', '1471986274', '25', '44', '1'), ('2905', '1471986334', '25', '116', '1'), ('2906', '1471986394', '25', '34', '1'), ('2907', '1471986454', '25', '42', '1'), ('2908', '1471986514', '24', '32', '1'), ('2909', '1471986574', '24', '43', '1'), ('2910', '1471986634', '25', '44', '1'), ('2911', '1471986694', '25', '193', '1'), ('2912', '1471986754', '27', '2671', '1'), ('2913', '1471986814', '25', '34', '1'), ('2914', '1471986874', '24', '42', '1'), ('2915', '1471986934', '25', '36', '1'), ('2916', '1471986994', '25', '42', '1'), ('2917', '1471987054', '25', '53', '1'), ('2918', '1471987114', '25', '56', '1'), ('2919', '1471987174', '25', '54', '1'), ('2920', '1471987234', '25', '55', '1'), ('2921', '1472239560', '0', '0', '0'), ('2922', '1472239620', '32', '6637', '0'), ('2923', '1472239982', '0', '0', '0'), ('2924', '1472240042', '33', '5572', '0'), ('2925', '1472240102', '26', '1716', '0'), ('2926', '1472240210', '25', '624', '0'), ('2927', '1472240270', '25', '173', '1'), ('2928', '1472240330', '26', '2355', '1'), ('2929', '1472240390', '25', '281', '1'), ('2930', '1472240450', '24', '45', '1'), ('2931', '1472240510', '25', '34', '1'), ('2932', '1472240570', '25', '46', '1'), ('2933', '1472240630', '25', '610', '1'), ('2934', '1472240690', '25', '40', '1'), ('2935', '1472240750', '25', '951', '1'), ('2936', '1472240810', '26', '1724', '1'), ('2937', '1472240870', '24', '32', '1'), ('2938', '1472240930', '25', '34', '1'), ('2939', '1472240990', '24', '36', '1'), ('2940', '1472241050', '25', '1418', '1'), ('2941', '1472241110', '25', '308', '1'), ('2942', '1472241170', '25', '38', '1'), ('2943', '1472241230', '25', '39', '1'), ('2944', '1472241290', '25', '39', '1'), ('2945', '1472241350', '25', '38', '1'), ('2946', '1472241410', '25', '42', '1'), ('2947', '1472241470', '24', '39', '1'), ('2948', '1472241530', '26', '3004', '1'), ('2949', '1472241590', '25', '37', '1'), ('2950', '1472241650', '25', '35', '1'), ('2951', '1472241710', '25', '39', '1'), ('2952', '1472241770', '24', '38', '1'), ('2953', '1472241830', '25', '39', '1'), ('2954', '1472241890', '24', '37', '1'), ('2955', '1472241950', '25', '47', '1'), ('2956', '1472242010', '24', '40', '1'), ('2957', '1472242070', '25', '57', '1'), ('2958', '1472242130', '25', '33', '1'), ('2959', '1472242190', '25', '1718', '1'), ('2960', '1472242250', '25', '1002', '1'), ('2961', '1472242310', '25', '42', '1'), ('2962', '1472242370', '25', '40', '1'), ('2963', '1472242430', '25', '49', '1'), ('2964', '1472242490', '25', '38', '1'), ('2965', '1472242550', '24', '41', '0'), ('2966', '1472242610', '24', '43', '0'), ('2967', '1472303930', '0', '0', '0'), ('2968', '1472303990', '38', '10077', '0'), ('2969', '1472304050', '28', '2693', '1'), ('2970', '1472304110', '25', '377', '1'), ('2971', '1472304170', '25', '93', '1'), ('2972', '1472304297', '26', '2175', '1'), ('2973', '1472304444', '25', '533', '1'), ('2974', '1472304504', '25', '362', '1'), ('2975', '1472304564', '25', '781', '1'), ('2976', '1472304624', '25', '200', '1'), ('2977', '1472304684', '26', '2183', '1'), ('2978', '1472304744', '27', '3459', '1'), ('2979', '1472304804', '25', '1217', '1'), ('2980', '1472304864', '25', '780', '1'), ('2981', '1472304924', '24', '44', '1'), ('2982', '1472304984', '25', '696', '1'), ('2983', '1472305044', '24', '45', '1'), ('2984', '1472305104', '25', '40', '1'), ('2985', '1472305164', '25', '37', '1'), ('2986', '1472305224', '25', '87', '1'), ('2987', '1472305284', '25', '147', '1'), ('2988', '1472305344', '25', '576', '1'), ('2989', '1472305404', '24', '38', '1'), ('2990', '1472305498', '25', '88', '0'), ('2991', '1472305558', '25', '1298', '1'), ('2992', '1472305618', '25', '945', '1'), ('2993', '1472305678', '25', '453', '1'), ('2994', '1472305738', '25', '72', '1'), ('2995', '1472305798', '25', '64', '1'), ('2996', '1472305858', '25', '269', '1'), ('2997', '1472305918', '25', '193', '1'), ('2998', '1472305978', '25', '45', '1'), ('2999', '1472306038', '25', '39', '1'), ('3000', '1472306098', '25', '44', '1');
INSERT INTO `time_diff_log` VALUES ('3001', '1472306158', '24', '37', '1'), ('3002', '1472306276', '25', '86', '1'), ('3003', '1472306336', '25', '453', '1'), ('3004', '1472306452', '25', '65', '1'), ('3005', '1472306512', '25', '96', '1'), ('3006', '1472306572', '26', '2245', '1'), ('3007', '1472306971', '24', '69', '0'), ('3008', '1472307462', '24', '71', '0'), ('3009', '1472307522', '25', '291', '1'), ('3010', '1472307582', '25', '63', '1'), ('3011', '1472307642', '25', '190', '1'), ('3012', '1472307702', '25', '58', '1'), ('3013', '1472307762', '24', '44', '1'), ('3014', '1472307822', '25', '55', '1'), ('3015', '1472307882', '25', '386', '1'), ('3016', '1472307942', '24', '46', '0'), ('3017', '1472308002', '25', '174', '0'), ('3018', '1472308062', '25', '46', '0'), ('3019', '1472308122', '24', '34', '0');
COMMIT;

-- ----------------------------
-- Table structure for `warden_action`
-- ----------------------------
DROP TABLE IF EXISTS `warden_action`;
CREATE TABLE `warden_action` (
`wardenId`  smallint(5) UNSIGNED NOT NULL ,
`action`  tinyint(3) UNSIGNED NULL DEFAULT NULL ,
PRIMARY KEY (`wardenId`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of warden_action
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `worldstates`
-- ----------------------------
DROP TABLE IF EXISTS `worldstates`;
CREATE TABLE `worldstates` (
`entry`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`value`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`comment`  tinytext CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
PRIMARY KEY (`entry`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Variable Saves'

;

-- ----------------------------
-- Records of worldstates
-- ----------------------------
BEGIN;
INSERT INTO `worldstates` VALUES ('3781', '9000000', null), ('3801', '0', null), ('3802', '0', null), ('20002', '1472844360', null), ('20003', '1472353200', null), ('20004', '1472677200', null), ('20005', '1440118800', null);
COMMIT;

-- ----------------------------
-- Indexes structure for table account_achievement_progress
-- ----------------------------
CREATE INDEX `Account` ON `account_achievement_progress`(`account`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table arena_team
-- ----------------------------
CREATE INDEX `idx_type` ON `arena_team`(`type`) USING BTREE ;
CREATE INDEX `idx_rating` ON `arena_team`(`rating`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table arena_team_member
-- ----------------------------
CREATE INDEX `idx_guid` ON `arena_team_member`(`guid`) USING BTREE ;
CREATE INDEX `idx_arenaTeamId` ON `arena_team_member`(`arenaTeamId`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table auctionhouse
-- ----------------------------
CREATE UNIQUE INDEX `item_guid` ON `auctionhouse`(`itemguid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `autobroadcast`
-- ----------------------------
ALTER TABLE `autobroadcast` AUTO_INCREMENT=5;

-- ----------------------------
-- Auto increment value for `bugreport`
-- ----------------------------
ALTER TABLE `bugreport` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table character_equipmentsets
-- ----------------------------
CREATE UNIQUE INDEX `idx_set` ON `character_equipmentsets`(`guid`, `setguid`, `setindex`) USING BTREE ;
CREATE INDEX `Idx_setindex` ON `character_equipmentsets`(`setindex`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `character_equipmentsets`
-- ----------------------------
ALTER TABLE `character_equipmentsets` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table character_gifts
-- ----------------------------
CREATE INDEX `idx_guid` ON `character_gifts`(`guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_instance
-- ----------------------------
CREATE INDEX `instance` ON `character_instance`(`instance`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_inventory
-- ----------------------------
CREATE UNIQUE INDEX `guid` ON `character_inventory`(`guid`, `bag`, `slot`) USING BTREE ;
CREATE INDEX `idx_guid` ON `character_inventory`(`guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_pet
-- ----------------------------
CREATE INDEX `owner` ON `character_pet`(`owner`) USING BTREE ;
CREATE INDEX `idx_slot` ON `character_pet`(`slot`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_pet_declinedname
-- ----------------------------
CREATE INDEX `owner_key` ON `character_pet_declinedname`(`owner`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_queststatus_daily
-- ----------------------------
CREATE INDEX `idx_guid` ON `character_queststatus_daily`(`guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_queststatus_monthly
-- ----------------------------
CREATE INDEX `idx_guid` ON `character_queststatus_monthly`(`guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_queststatus_seasonal
-- ----------------------------
CREATE INDEX `idx_guid` ON `character_queststatus_seasonal`(`guid`) USING BTREE ;
CREATE INDEX `event` ON `character_queststatus_seasonal`(`event`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_queststatus_weekly
-- ----------------------------
CREATE INDEX `idx_guid` ON `character_queststatus_weekly`(`guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_social
-- ----------------------------
CREATE INDEX `friend` ON `character_social`(`friend`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table character_void_storage
-- ----------------------------
CREATE UNIQUE INDEX `idx_player_slot` ON `character_void_storage`(`playerGuid`, `slot`) USING BTREE ;
CREATE INDEX `idx_player` ON `character_void_storage`(`playerGuid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table characters
-- ----------------------------
CREATE INDEX `idx_account` ON `characters`(`account`) USING BTREE ;
CREATE INDEX `idx_online` ON `characters`(`online`) USING BTREE ;
CREATE INDEX `idx_name` ON `characters`(`name`) USING BTREE ;
CREATE INDEX `instance_id` ON `characters`(`instance_id`) USING BTREE ;
CREATE INDEX `idx_deleted` ON `characters`(`deleteInfos_Account`) USING BTREE ;
CREATE INDEX `logout` ON `characters`(`logout_time`) USING BTREE ;
CREATE INDEX `idx_totalKills` ON `characters`(`totalKills`) USING BTREE ;
CREATE INDEX `idx_totaltime` ON `characters`(`totaltime`) USING BTREE ;
CREATE INDEX `idx_money` ON `characters`(`money`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table corpse
-- ----------------------------
CREATE INDEX `idx_type` ON `corpse`(`corpseType`) USING BTREE ;
CREATE INDEX `idx_instance` ON `corpse`(`instanceId`) USING BTREE ;
CREATE INDEX `idx_player` ON `corpse`(`guid`) USING BTREE ;
CREATE INDEX `idx_time` ON `corpse`(`time`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table creature_respawn
-- ----------------------------
CREATE INDEX `idx_instance` ON `creature_respawn`(`instanceId`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table gameobject_respawn
-- ----------------------------
CREATE INDEX `idx_instance` ON `gameobject_respawn`(`instanceId`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `gm_subsurveys`
-- ----------------------------
ALTER TABLE `gm_subsurveys` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `gm_surveys`
-- ----------------------------
ALTER TABLE `gm_surveys` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `gm_tickets`
-- ----------------------------
ALTER TABLE `gm_tickets` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table group_instance
-- ----------------------------
CREATE INDEX `instance` ON `group_instance`(`instance`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table groups
-- ----------------------------
CREATE INDEX `leaderGuid` ON `groups`(`leaderGuid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_bank_eventlog
-- ----------------------------
CREATE INDEX `guildid_key` ON `guild_bank_eventlog`(`guildid`) USING BTREE ;
CREATE INDEX `Idx_PlayerGuid` ON `guild_bank_eventlog`(`PlayerGuid`) USING BTREE ;
CREATE INDEX `Idx_LogGuid` ON `guild_bank_eventlog`(`LogGuid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_bank_item
-- ----------------------------
CREATE INDEX `guildid_key` ON `guild_bank_item`(`guildid`) USING BTREE ;
CREATE INDEX `Idx_item_guid` ON `guild_bank_item`(`item_guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_bank_right
-- ----------------------------
CREATE INDEX `guildid_key` ON `guild_bank_right`(`guildid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_bank_tab
-- ----------------------------
CREATE INDEX `guildid_key` ON `guild_bank_tab`(`guildid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_eventlog
-- ----------------------------
CREATE INDEX `Idx_PlayerGuid1` ON `guild_eventlog`(`PlayerGuid1`) USING BTREE ;
CREATE INDEX `Idx_PlayerGuid2` ON `guild_eventlog`(`PlayerGuid2`) USING BTREE ;
CREATE INDEX `Idx_LogGuid` ON `guild_eventlog`(`LogGuid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_finder_applicant
-- ----------------------------
CREATE UNIQUE INDEX `guildId` ON `guild_finder_applicant`(`guildId`, `playerGuid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_member
-- ----------------------------
CREATE UNIQUE INDEX `guid_key` ON `guild_member`(`guid`) USING BTREE ;
CREATE INDEX `guildid_key` ON `guild_member`(`guildid`) USING BTREE ;
CREATE INDEX `guildid_rank_key` ON `guild_member`(`guildid`, `rank`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table guild_rank
-- ----------------------------
CREATE INDEX `Idx_rid` ON `guild_rank`(`rid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table instance
-- ----------------------------
CREATE INDEX `map` ON `instance`(`map`) USING BTREE ;
CREATE INDEX `resettime` ON `instance`(`resettime`) USING BTREE ;
CREATE INDEX `difficulty` ON `instance`(`difficulty`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table instance_reset
-- ----------------------------
CREATE INDEX `difficulty` ON `instance_reset`(`difficulty`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table item_instance
-- ----------------------------
CREATE INDEX `idx_owner_guid` ON `item_instance`(`owner_guid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `lag_reports`
-- ----------------------------
ALTER TABLE `lag_reports` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `log_arena`
-- ----------------------------
ALTER TABLE `log_arena` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `log_faction_change`
-- ----------------------------
ALTER TABLE `log_faction_change` AUTO_INCREMENT=3711;

-- ----------------------------
-- Auto increment value for `log_gm`
-- ----------------------------
ALTER TABLE `log_gm` AUTO_INCREMENT=30;

-- ----------------------------
-- Auto increment value for `log_gm_chat`
-- ----------------------------
ALTER TABLE `log_gm_chat` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `log_store_gold`
-- ----------------------------
ALTER TABLE `log_store_gold` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `log_trade`
-- ----------------------------
ALTER TABLE `log_trade` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table mail
-- ----------------------------
CREATE INDEX `idx_receiver` ON `mail`(`receiver`) USING BTREE ;
CREATE INDEX `exptime` ON `mail`(`expire_time`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table mail_items
-- ----------------------------
CREATE INDEX `idx_receiver` ON `mail_items`(`receiver`) USING BTREE ;
CREATE INDEX `idx_mail_id` ON `mail_items`(`mail_id`) USING BTREE ;
CREATE INDEX `findByItem` ON `mail_items`(`item_guid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table petition
-- ----------------------------
CREATE UNIQUE INDEX `index_ownerguid_petitionguid` ON `petition`(`ownerguid`, `petitionguid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table petition_sign
-- ----------------------------
CREATE INDEX `Idx_playerguid` ON `petition_sign`(`playerguid`) USING BTREE ;
CREATE INDEX `Idx_ownerguid` ON `petition_sign`(`ownerguid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table store_gold
-- ----------------------------
CREATE UNIQUE INDEX `transaction` ON `store_gold`(`transaction`) USING BTREE ;
CREATE INDEX `guid` ON `store_gold`(`guid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `store_gold`
-- ----------------------------
ALTER TABLE `store_gold` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table store_item
-- ----------------------------
CREATE UNIQUE INDEX `transaction` ON `store_item`(`transaction`) USING BTREE ;
CREATE INDEX `guid` ON `store_item`(`guid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `store_item`
-- ----------------------------
ALTER TABLE `store_item` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table store_level
-- ----------------------------
CREATE UNIQUE INDEX `transaction` ON `store_level`(`transaction`) USING BTREE ;
CREATE INDEX `guid` ON `store_level`(`guid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `store_level`
-- ----------------------------
ALTER TABLE `store_level` AUTO_INCREMENT=1;

-- ----------------------------
-- Indexes structure for table store_metier
-- ----------------------------
CREATE UNIQUE INDEX `NewIndex1` ON `store_metier`(`skill`, `guid`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `store_metier`
-- ----------------------------
ALTER TABLE `store_metier` AUTO_INCREMENT=1;

-- ----------------------------
-- Auto increment value for `time_diff_log`
-- ----------------------------
ALTER TABLE `time_diff_log` AUTO_INCREMENT=3020;
