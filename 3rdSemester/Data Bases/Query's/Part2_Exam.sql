CREATE DATABASE PART_2
GO
USE PART_2
GO


CREATE TABLE Contest_Type(
IDct INT PRIMARY KEY,
name varchar(50),
description varchar(50),
)
GO

INSERT INTO Contest_Type VALUES (1,'DD','EE')
INSERT INTO Contest_Type VALUES (2,'FF','AA')
INSERT INTO Contest_Type VALUES (3,'GG','SS')
SELECT * FROM Contest_Type
GO

CREATE TABLE City(
IDci INT PRIMARY KEY,
name varchar(50),
country varchar(50),
population INT,
)
GO

INSERT INTO Contest_Type VALUES (1,'DD','EE')
INSERT INTO Contest_Type VALUES (2,'FF','AA')
INSERT INTO Contest_Type VALUES (3,'GG','SS')
SELECT * FROM City
GO

CREATE TABLE Contest(
IDc INT PRIMARY KEY,
title varchar(50),
start_date dateTIME,
end_date dateTIME,
IDct INT FOREIGN KEY REFERENCES Contest_Type(IDct),
IDcI INT FOREIGN KEY REFERENCES City(IDci),
)
GO

INSERT INTO Contest VALUES (1,'DD',2008-10-29,2008-10-29,1,1)
INSERT INTO Contest VALUES (2,'FF',2008-10-29,2008-10-29,1,2)
INSERT INTO Contest VALUES (5,'GG',2008-10-29,2008-10-29,1,3)
INSERT INTO Contest VALUES (4,'HH',2008-10-29,2008-10-29,2,3)
INSERT INTO Contest VALUES (3,'JJ',2008-10-29,2008-10-29,3,3)
SELECT * FROM Contest
GO

CREATE TABLE Participant(
IDp INT PRIMARY KEY,
name varchar(50),
surname varchar(50),
date_of_birth dateTIME,
gendre varchar(50),
)
GO

INSERT INTO Participant VALUES (1,'G','D',2008-10-29,'F')
INSERT INTO Participant VALUES (2,'C','R',2008-10-29,'M')
INSERT INTO Participant VALUES (3,'V','T',2008-10-29,'M')
INSERT INTO Participant VALUES (4,'B','Y',2008-10-29,'M')
INSERT INTO Participant VALUES (5,'N','U',2008-10-29,'F')

SELECT * FROM Participant

CREATE TABLE Participation (
IDpa INT PRIMARY KEY IDENTITY,
IDc INT FOREIGN KEY REFERENCES Contest(IDc),
IDp INT FOREIGN KEY REFERENCES Participant(IDp),
participation_date DATETIME,
);
GO

INSERT INTO Participation VALUES (1,1,2008-10-29)
INSERT INTO Participation VALUES (2,1,2008-10-29)
INSERT INTO Participation VALUES (2,3,2008-10-29)
SELECT * FROM Participation
GO

CREATE PROCEDURE AddToParticipation @IDc INT , @IDp INT , @pd DATETIME
AS
	DECLARE @nr INT;
	SET @nr = 0;
	SELECT @nr =COUNT(*)FROM Participation WHERE IDc=@IDc and IDp = @IDp
	IF(@nr<>0)BEGIN
		UPDATE Participation
		SET participation_date = @pd
		WHERE IDc=@IDc and IDp = @IDp
	END
	ELSE BEGIN
		INSERT INTO Participation Values (@IDc , @IDp , @pd)
	END
GO

SELECT * FROM Participation
EXEC AddToParticipation 5,5,'2020-11-11 08:00:00'
GO

CREATE VIEW ViewParticipants
AS
SELECT Name
FROM Participant p INNER JOIN Contest c ON c.IDc=p.IDp
GROUP BY Name
HAVING COUNT(*) >=3
GO


SELECT * FROM ViewParticipants
GO

ALTER FUNCTION List(@p int)
RETURNS TABLE AS
RETURN
SELECT DISTINCT Title
FROM Contest c INNER JOIN Participant p ON c.IDc = p.IDp
GROUP BY Title
HAVING COUNT(Name)>=@p
GO


SELECT * FROM List(1)



