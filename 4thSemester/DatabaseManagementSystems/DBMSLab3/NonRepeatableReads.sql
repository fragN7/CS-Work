-- T1 nonrepeatable reads 
-- just update a field
BEGIN TRAN
WAITFOR DELAY '00:00:07'
UPDATE ChessTitle SET title_name='Test' WHERE tid=1
COMMIT TRAN
GO

INSERT INTO ChessTitle (title_name) VALUES ('Normal')
select * from ChessTitle
DELETE FROM ChessTitle WHERE tid=4