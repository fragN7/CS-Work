-- T2 non repeatable reads
-- here we would see a different result in the two selects
SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:15'
SELECT * FROM ChessTitle
COMMIT TRAN
GO

-- solution: iso level -> repeatable read ; whereas here we would have only the final result in both selects
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:15'
SELECT * FROM ChessTitle
COMMIT TRAN