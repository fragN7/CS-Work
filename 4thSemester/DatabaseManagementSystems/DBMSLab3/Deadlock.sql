-- the two updates will cause the deadlock with the ones in T2 because essentially each one will be stuck waiting for the other to free the resource
BEGIN TRAN 
UPDATE ChessTitle SET title_name='GM trans 1' WHERE tid=1
WAITFOR DELAY '00:00:10'
UPDATE ChessClub SET club_name='The Queens trans 1' WHERE cid=1
COMMIT TRAN
GO


select * from ChessClub
select * from ChessTitle
UPDATE ChessTitle SET title_name='Normal' WHERE tid=1
UPDATE ChessClub SET club_name='Chess Club 1' WHERE cid=1
GO


