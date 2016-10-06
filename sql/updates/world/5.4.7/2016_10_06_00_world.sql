--Fix Only DK Worgen start with Viciousness spell
DELETE FROM playercreateinfo_spell WHERE race=22 AND Spell=68975
INSERT INTO playercreateinfo_spell(race, class, Spell, Note)VALUES
(22, 6, 68975, "Viciousness"),
(22, 1, 68975, "Viciousness"),
(22, 3, 68975, "Viciousness"),
(22, 4, 68975, "Viciousness"),
(22, 5, 68975, "Viciousness"),
(22, 8, 68975, "Viciousness"),
(22, 9, 68975, "Viciousness"),
(22, 11, 68975, "Viciousness");
