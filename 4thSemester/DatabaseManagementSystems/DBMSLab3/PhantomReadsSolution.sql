-- phantom problem T2 - initial iso level set to repeatable read
-- in the second select we will see the "phantom", i.e. the record which shouldn't be there
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:05'
SELECT * FROM ChessTitle
COMMIT TRAN

-- solution: iso level-> serializable
-- whereas because of the serializable level, here neither selects will show the inserted record from T1 
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
SELECT * FROM ChessTitle
WAITFOR DELAY '00:00:05'
SELECT * FROM ChessTitle
COMMIT TRAN