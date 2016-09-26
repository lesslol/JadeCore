/*
Navicat MySQL Data Transfer

Source Server         : JadeCore_5.x.x
Source Server Version : 50624
Source Host           : 127.0.0.1:3306
Source Database       : auth

Target Server Type    : MYSQL
Target Server Version : 50624
File Encoding         : 65001

Date: 2016-09-26 18:32:45
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
`id`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Identifier' ,
`username`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`sha_pass_hash`  varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`sessionkey`  varchar(80) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`v`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`s`  varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`token_key`  varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`email`  varchar(254) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`joindate`  timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ,
`last_ip`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '127.0.0.1' ,
`failed_logins`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`locked`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`last_login`  timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ,
`online`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`expansion`  tinyint(3) UNSIGNED NOT NULL DEFAULT 4 ,
`mutetime`  bigint(20) NOT NULL DEFAULT 0 ,
`locale`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`os`  varchar(3) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' ,
`recruiter`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`gmlevelo`  int(11) NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Account System'
AUTO_INCREMENT=13

;

-- ----------------------------
-- Records of account
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `account_access`
-- ----------------------------
DROP TABLE IF EXISTS `account_access`;
CREATE TABLE `account_access` (
`id`  int(10) UNSIGNED NOT NULL ,
`gmlevel`  tinyint(3) UNSIGNED NOT NULL ,
`RealmID`  int(11) NOT NULL DEFAULT '-1' ,
`comment`  text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
PRIMARY KEY (`id`, `RealmID`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of account_access
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `account_banned`
-- ----------------------------
DROP TABLE IF EXISTS `account_banned`;
CREATE TABLE `account_banned` (
`id`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Account id' ,
`bandate`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`unbandate`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`bannedby`  varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`banreason`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`active`  tinyint(3) UNSIGNED NOT NULL DEFAULT 1 ,
PRIMARY KEY (`id`, `bandate`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Ban List'

;

-- ----------------------------
-- Records of account_banned
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `account_log_ip`
-- ----------------------------
DROP TABLE IF EXISTS `account_log_ip`;
CREATE TABLE `account_log_ip` (
`accountid`  int(11) UNSIGNED NOT NULL ,
`ip`  varchar(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '0.0.0.0' ,
`date`  datetime NULL DEFAULT NULL ,
PRIMARY KEY (`accountid`, `ip`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of account_log_ip
-- ----------------------------
BEGIN;
INSERT INTO `account_log_ip` VALUES ('2', '127.0.0.1', '2014-11-03 00:58:29'), ('1', '127.0.0.1', '2014-11-03 01:10:28'), ('3', '127.0.0.1', '2014-11-20 01:07:10'), ('4', '127.0.0.1', '2015-01-22 05:22:02'), ('5', '127.0.0.1', '2015-01-22 05:23:20'), ('6', '127.0.0.1', '2015-06-13 10:52:56'), ('7', '25.12.37.204', '2016-04-17 19:37:40'), ('11', '127.0.0.1', '2016-07-17 19:09:50'), ('12', '127.0.0.1', '2016-07-22 18:13:35'), ('7', '127.0.0.1', '2016-07-22 18:14:44');
COMMIT;

-- ----------------------------
-- Table structure for `account_premium`
-- ----------------------------
DROP TABLE IF EXISTS `account_premium`;
CREATE TABLE `account_premium` (
`id`  int(11) NOT NULL DEFAULT 0 COMMENT 'Account id' ,
`setdate`  bigint(40) NOT NULL DEFAULT 0 ,
`unsetdate`  bigint(40) NOT NULL DEFAULT 0 ,
`premium_type`  tinyint(4) UNSIGNED NOT NULL DEFAULT 1 ,
`gm`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '0' ,
`active`  tinyint(4) NOT NULL DEFAULT 1 ,
PRIMARY KEY (`id`, `setdate`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of account_premium
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `account_spell`
-- ----------------------------
DROP TABLE IF EXISTS `account_spell`;
CREATE TABLE `account_spell` (
`accountId`  int(11) NOT NULL ,
`spell`  int(10) NOT NULL ,
`active`  tinyint(1) NULL DEFAULT NULL ,
`disabled`  tinyint(1) NULL DEFAULT NULL ,
PRIMARY KEY (`accountId`, `spell`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of account_spell
-- ----------------------------
BEGIN;
INSERT INTO `account_spell` VALUES ('1', '472', '1', '0'), ('7', '10688', '1', '0'), ('7', '10709', '1', '0'), ('7', '10714', '1', '0'), ('7', '36027', '1', '0'), ('7', '123212', '1', '0'), ('7', '127816', '1', '0'), ('11', '64977', '1', '0');
COMMIT;

-- ----------------------------
-- Table structure for `firewall_farms`
-- ----------------------------
DROP TABLE IF EXISTS `firewall_farms`;
CREATE TABLE `firewall_farms` (
`ip`  tinytext CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ,
`type`  tinyint(1) UNSIGNED NOT NULL DEFAULT 0 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of firewall_farms
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `ip_banned`
-- ----------------------------
DROP TABLE IF EXISTS `ip_banned`;
CREATE TABLE `ip_banned` (
`ip`  varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '127.0.0.1' ,
`bandate`  int(10) UNSIGNED NOT NULL ,
`unbandate`  int(10) UNSIGNED NOT NULL ,
`bannedby`  varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '[Console]' ,
`banreason`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'no reason' ,
PRIMARY KEY (`ip`, `bandate`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Banned IPs'

;

-- ----------------------------
-- Records of ip_banned
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `ip_to_country`
-- ----------------------------
DROP TABLE IF EXISTS `ip_to_country`;
CREATE TABLE `ip_to_country` (
`IP_FROM`  double NOT NULL ,
`IP_TO`  double NOT NULL ,
`COUNTRY_CODE`  char(2) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL ,
`COUNTRY_CODE_3`  char(3) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ,
`COUNTRY_NAME`  varchar(50) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL ,
PRIMARY KEY (`IP_FROM`, `IP_TO`)
)
ENGINE=MyISAM
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of ip_to_country
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `log_vote`
-- ----------------------------
DROP TABLE IF EXISTS `log_vote`;
CREATE TABLE `log_vote` (
`top_name`  varchar(15) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'top' ,
`ip`  varchar(15) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '0.0.0.0' ,
`date`  int(11) NOT NULL ,
PRIMARY KEY (`top_name`, `ip`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of log_vote
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `logs`
-- ----------------------------
DROP TABLE IF EXISTS `logs`;
CREATE TABLE `logs` (
`time`  int(10) UNSIGNED NOT NULL ,
`realm`  int(10) UNSIGNED NOT NULL ,
`type`  tinyint(3) UNSIGNED NOT NULL ,
`level`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`string`  text CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of logs
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `mails`
-- ----------------------------
DROP TABLE IF EXISTS `mails`;
CREATE TABLE `mails` (
`email`  varchar(254) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci

;

-- ----------------------------
-- Records of mails
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `realmcharacters`
-- ----------------------------
DROP TABLE IF EXISTS `realmcharacters`;
CREATE TABLE `realmcharacters` (
`realmid`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`acctid`  int(10) UNSIGNED NOT NULL ,
`numchars`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`realmid`, `acctid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Realm Character Tracker'

;

-- ----------------------------
-- Records of realmcharacters
-- ----------------------------
BEGIN;
INSERT INTO `realmcharacters` VALUES ('1', '1', '11'), ('1', '2', '11'), ('1', '3', '2'), ('1', '4', '1'), ('1', '5', '1'), ('1', '6', '1'), ('1', '7', '2'), ('1', '8', '0'), ('1', '9', '0'), ('1', '10', '0'), ('1', '11', '3'), ('1', '12', '1');
COMMIT;

-- ----------------------------
-- Table structure for `realmlist`
-- ----------------------------
DROP TABLE IF EXISTS `realmlist`;
CREATE TABLE `realmlist` (
`id`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
`name`  varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'JadeCore 5.x.x' ,
`address`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '127.0.0.1' ,
`port`  smallint(5) UNSIGNED NOT NULL DEFAULT 8085 ,
`icon`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`flag`  tinyint(3) UNSIGNED NOT NULL DEFAULT 2 ,
`timezone`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`allowedSecurityLevel`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`population`  float UNSIGNED NOT NULL DEFAULT 0 ,
`gamebuild`  int(10) UNSIGNED NOT NULL DEFAULT 18019 ,
`online`  int(10) NULL DEFAULT 0 ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Realm System'
AUTO_INCREMENT=2

;

-- ----------------------------
-- Records of realmlist
-- ----------------------------
BEGIN;
INSERT INTO `realmlist` VALUES ('1', 'JadeCore 5.x.x', '127.0.0.1', '8085', '0', '0', '1', '0', '0', '18019', '0');
COMMIT;

-- ----------------------------
-- Table structure for `transferts`
-- ----------------------------
DROP TABLE IF EXISTS `transferts`;
CREATE TABLE `transferts` (
`id`  int(11) NOT NULL AUTO_INCREMENT ,
`account`  int(11) NOT NULL ,
`perso_guid`  int(11) NOT NULL ,
`from`  int(11) NOT NULL ,
`to`  int(11) NOT NULL ,
`revision`  blob NOT NULL ,
`dump`  longtext CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ,
`last_error`  blob NOT NULL ,
`nb_attempt`  int(11) NOT NULL ,
`state`  int(10) NULL DEFAULT NULL ,
`error`  int(10) NULL DEFAULT NULL ,
PRIMARY KEY (`id`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci
AUTO_INCREMENT=1

;

-- ----------------------------
-- Records of transferts
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `transferts_logs`
-- ----------------------------
DROP TABLE IF EXISTS `transferts_logs`;
CREATE TABLE `transferts_logs` (
`id`  int(11) NULL DEFAULT NULL ,
`account`  int(11) NULL DEFAULT NULL ,
`perso_guid`  int(11) NULL DEFAULT NULL ,
`from`  int(2) NULL DEFAULT NULL ,
`to`  int(2) NULL DEFAULT NULL ,
`dump`  longtext CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL 
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=latin1 COLLATE=latin1_swedish_ci

;

-- ----------------------------
-- Records of transferts_logs
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for `uptime`
-- ----------------------------
DROP TABLE IF EXISTS `uptime`;
CREATE TABLE `uptime` (
`realmid`  int(10) UNSIGNED NOT NULL ,
`starttime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`uptime`  int(10) UNSIGNED NOT NULL DEFAULT 0 ,
`maxplayers`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 ,
`revision`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'JadeCore_5.x.x' ,
PRIMARY KEY (`realmid`, `starttime`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
COMMENT='Uptime system'

;

-- ----------------------------
-- Records of uptime
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Indexes structure for table account
-- ----------------------------
CREATE UNIQUE INDEX `idx_username` ON `account`(`username`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `account`
-- ----------------------------
ALTER TABLE `account` AUTO_INCREMENT=13;

-- ----------------------------
-- Indexes structure for table account_spell
-- ----------------------------
CREATE INDEX `account` ON `account_spell`(`accountId`) USING BTREE ;
CREATE INDEX `account_spell` ON `account_spell`(`accountId`, `spell`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table realmcharacters
-- ----------------------------
CREATE INDEX `acctid` ON `realmcharacters`(`acctid`) USING BTREE ;

-- ----------------------------
-- Indexes structure for table realmlist
-- ----------------------------
CREATE UNIQUE INDEX `idx_name` ON `realmlist`(`name`) USING BTREE ;

-- ----------------------------
-- Auto increment value for `realmlist`
-- ----------------------------
ALTER TABLE `realmlist` AUTO_INCREMENT=2;

-- ----------------------------
-- Auto increment value for `transferts`
-- ----------------------------
ALTER TABLE `transferts` AUTO_INCREMENT=1;
