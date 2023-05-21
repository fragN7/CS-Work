-- the two updates will cause the deadlock with the ones in T1
BEGIN TRAN 
UPDATE ChessClub SET club_name='The Queens trans 2' WHERE cid=1
WAITFOR DELAY '00:00:10'
UPDATE ChessTitle SET title_name='GM trans 2' WHERE tid=1
COMMIT TRAN
GO


-- solution : choose T1 as the victim by increasing T2's priority
SET DEADLOCK_PRIORITY HIGH
BEGIN TRAN 
UPDATE ChessClub SET club_name='The Queens trans 2' WHERE cid=1
WAITFOR DELAY '00:00:10'
UPDATE ChessTitle SET title_name='GM trans 2' WHERE tid=1
COMMIT TRAN