-- t2 update conflict
SET TRANSACTION ISOLATION LEVEL SNAPSHOT 
BEGIN TRAN
SELECT * FROM ChessTitle WHERE tid=11
-- here the value 'Retired' is returned because T1 has not yet reached the update because of the 10s delay
WAITFOR DELAY '00:00:10'
SELECT * FROM ChessTitle WHERE tid=11

-- now when trying to update the same resource that T1 has updated and obtained a lock on, =>
UPDATE ChessTitle SET title_name='Beginner' WHERE tid=11
-- process will block
-- error 3960 will be issued
COMMIT TRAN