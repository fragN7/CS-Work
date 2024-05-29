-- T1 nonrepeatable reads 
-- just update a field
use Sports;

BEGIN TRAN
WAITFOR DELAY '00:00:07'
UPDATE Players SET FirstName='JOHN CENA' WHERE PlayerID=1
COMMIT TRAN
GO

UPDATE Players SET FirstName='Alen' WHERE PlayerID=1
select * from Players;