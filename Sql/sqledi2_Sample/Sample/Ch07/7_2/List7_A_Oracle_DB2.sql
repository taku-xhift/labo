--OracleADB2
--DDLFe[uμ¬
CREATE TABLE Skills 
(skill VARCHAR(32),
 PRIMARY KEY(skill));

CREATE TABLE EmpSkills 
(emp   VARCHAR(32), 
 skill VARCHAR(32),
 PRIMARY KEY(emp, skill));

--DMLFf[^o^

INSERT INTO Skills VALUES('Oracle');
INSERT INTO Skills VALUES('UNIX');
INSERT INTO Skills VALUES('Java');

INSERT INTO EmpSkills VALUES('c', 'Oracle');
INSERT INTO EmpSkills VALUES('c', 'UNIX');
INSERT INTO EmpSkills VALUES('c', 'Java');
INSERT INTO EmpSkills VALUES('c', 'C#');
INSERT INTO EmpSkills VALUES('_θ', 'Oracle');
INSERT INTO EmpSkills VALUES('_θ', 'UNIX');
INSERT INTO EmpSkills VALUES('_θ', 'Java');
INSERT INTO EmpSkills VALUES('½δ', 'UNIX');
INSERT INTO EmpSkills VALUES('½δ', 'Oracle');
INSERT INTO EmpSkills VALUES('½δ', 'PHP');
INSERT INTO EmpSkills VALUES('½δ', 'Perl');
INSERT INTO EmpSkills VALUES('½δ', 'C++');
INSERT INTO EmpSkills VALUES('αc', 'Perl');
INSERT INTO EmpSkills VALUES('n', 'Oracle');

COMMIT;