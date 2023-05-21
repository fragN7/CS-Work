-- here the dirty read will happen because we can read uncommitted changes
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:15'
SELECT * FROM ChessTitle
COMMIT TRAN

--Solution: iso level=read committed, so we can't read "dirty" anymore
SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:15'
SELECT * FROM ChessTitle
COMMIT TRAN