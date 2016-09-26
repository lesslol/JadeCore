REVOKE ALL PRIVILEGES ON * . * FROM 'jadecore'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'jadecore'@'localhost';

REVOKE GRANT OPTION ON `world` . * FROM 'jadecore'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'jadecore'@'localhost';

REVOKE GRANT OPTION ON `characters` . * FROM 'jadecore'@'localhost';

REVOKE ALL PRIVILEGES ON `auth` . * FROM 'jadecore'@'localhost';

REVOKE GRANT OPTION ON `auth` . * FROM 'jadecore'@'localhost';

DROP USER 'jadecore'@'localhost';

DROP DATABASE IF EXISTS `world`;

DROP DATABASE IF EXISTS `characters`;

DROP DATABASE IF EXISTS `auth`;
