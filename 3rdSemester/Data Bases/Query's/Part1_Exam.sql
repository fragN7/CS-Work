CREATE DATABASE parte1
GO
USE parte1
GO


create table S(
fk1 INT,
fk2 INT,
f1 Varchar(50),
f2 int,
f3 varchar(10),
f4 INT ,
CONSTRAINT PK_TABLE PRIMARY KEY(fk1,fk2),
)

SELECT * FROM S

INSERT INTO S VALUES(4,8,'Aileen Stewart',-81,'f',55)
INSERT INTO S VALUES(5,6,'Andrea Dunn',-26,'m',35)
INSERT INTO S VALUES(2,6,'Gilda Cameron',-95,'f',-10)
INSERT INTO S VALUES(7,6,'Ellis Norton',-44,'m',-27)
INSERT INTO S VALUES(4,3,'Tammy Blackwell',-39,'f',-89)
INSERT INTO S VALUES(7,1,'Tamera Smith',25,'f',87)
INSERT INTO S VALUES(7,9,'Herman Odom',-82,'m',54)
INSERT INTO S VALUES(3,8,'James Herrera',-6,'f',-97)
INSERT INTO S VALUES(4,4,'Rubin Peterson',70,'m',-66)
INSERT INTO S VALUES(6,3,'Danielle Leblanc',34,'f',-74)


select f3, sum(f2) as sumf2, avg(f4) as avgf4
from S
where (-1*f2) >= f4 and f2 <=f4
group by f3
having sum(-1*f4 + f2) <= 200
go

select * from
	(select fk1, fk2, f2*2 as doublef2
	from S where (-1*f2) >= f4) s1
right join
	(select fk1, fk2, f4/2 as halff4
	from S where (-1*f4) <= f2) s2 on s1.fk2 = s2.fk2
go


CREATE TRIGGER TrOnUpdate
ON S
FOR UPDATE AS
DECLARE @total INT = 0
SELECT @total = SUM(i.f4-d.f4)
FROM deleted d INNER JOIN inserted i ON d.fk1 = i.fk1 AND d.fk2 = i.fk2
WHERE i.f4%2 <> d.fk2%2
PRINT @total
GO

UPDATE S
SET f4=f2 * -1
WHERE fk1 <= fk2
go
