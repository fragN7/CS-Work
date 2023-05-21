--phantom problem T1
BEGIN TRAN 
WAITFOR DELAY '00:00:04'
INSERT INTO ChessTitle(title_name) VALUES ('Beginner')
COMMIT TRAN
GO

select * from ChessTitle;
DELETE FROM ChessTitle WHERE tid=9