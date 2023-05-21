--Dirty Reads T1
-- try to update and rollback after a 10s delay

BEGIN TRANSACTION
UPDATE ChessTitle SET title_name='TEST' WHERE tid=1
WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION
GO

UPDATE ChessTitle SET title_name='FIDE MASTER' WHERE tid=1
select * from ChessTitle