USE ChessDB;
GO

CREATE OR ALTER PROCEDURE uspAddTacticTransactional (@tactic_name VARCHAR(30))
AS
	SET NOCOUNT ON;
	BEGIN TRAN 
		BEGIN TRY
			IF EXISTS (SELECT * FROM Tactic WHERE tactic_name=@tactic_name)
			BEGIN 
				RAISERROR('Tactic already exists',14,1)
			END
			INSERT INTO Tactic VALUES (@tactic_name)
			INSERT INTO LogTable VALUES('add','tactic',GETDATE())
			COMMIT TRAN
		END TRY 
	BEGIN CATCH 
		ROLLBACK TRAN
		print 'Transaction rollbacked'
	END CATCH
GO


CREATE OR ALTER PROCEDURE uspAddPlayerTransactional (@player_name VARCHAR(100),  @player_rating INT, @title_id TINYINT, @club_id TINYINT)
AS
	SET NOCOUNT ON;
	BEGIN TRAN 
		BEGIN TRY 
			IF(dbo.uf_ValidateRating(@player_rating) <> 1)
			BEGIN
				RAISERROR('Rating should be anywhere between 0 and 3500', 14, 1)
			END

			IF EXISTS (SELECT * FROM ChessPlayer WHERE player_name=@player_name AND title_id=@title_id AND club_id=@club_id)
			BEGIN
				RAISERROR('Player already added',14,1)
			END
			INSERT INTO ChessPlayer VALUES (@player_name, @player_rating, @title_id, @club_id)
			INSERT INTO LogTable VALUES ('add', 'player',GETDATE())
			COMMIT TRAN
		END TRY
		BEGIN CATCH 
			ROLLBACK TRAN
			print 'Transaction rollbacked'
		END CATCH

GO

CREATE OR ALTER PROCEDURE uspAddTacticsHistoryTransactional (@player_id INT, @tactic_id INT)
AS
	SET NOCOUNT ON;

	BEGIN TRAN
		BEGIN TRY
			IF NOT EXISTS (SELECT * FROM ChessPlayer P WHERE P.player_id = @player_id)
			BEGIN
				 RAISERROR('Invalid player id', 14, 1)
			END
	
			IF NOT EXISTS (SELECT * FROM Tactic T WHERE T.tactic_id = @tactic_id)
			BEGIN
				RAISERROR('Invalid tactic id', 14, 1)
			END
	
			IF EXISTS (SELECT * FROM TacticsHistory TH WHERE TH.player_id = @player_id AND TH.tactic_id = @tactic_id)
			BEGIN
				RAISERROR('Tactic + player already logged in history', 14, 1)
			END

				INSERT INTO TacticsHistory VALUES (@player_id, @tactic_id);
				print 'Added!'
				--log the transaction
				INSERT INTO LogTable VALUES('add','TacticsHistory',GETDATE())
				COMMIT TRAN
		END TRY

		BEGIN CATCH
			ROLLBACK TRAN
			print 'Transaction rollbacked'
		END CATCH
GO

select * from ChessPlayer
select * from Tactic

--each of the three transactions are independent of the others
GO

CREATE OR ALTER PROCEDURE uspPerformAddsGoodScenario
AS 
	EXEC uspAddPlayerTransactional 'Mario Iaguta', 1200, 2,2 -- all 3 will succeed
	EXEC uspAddTacticTransactional 'English Game' 
	EXEC uspAddTacticsHistoryTransactional 2, 1 
GO

CREATE OR ALTER PROCEDURE uspPerformAddsBadScenario
AS 
	EXEC uspAddPlayerTransactional 'Alen Iaguta', 4500, 3, 2 -- enter the rating validation branch so this will fail
	EXEC uspAddTacticTransactional 'Berlin Defense' 
	EXEC uspAddTacticsHistoryTransactional 2, 2 
GO

SELECT * FROM ChessPlayer
SELECT * FROM Tactic
SELECT * FROM TacticsHistory

EXEC uspPerformAddsGoodScenario
EXEC uspPerformAddsBadScenario

delete from LogTable;

SELECT * FROM LogTable
-- 4 entries were added to the log table, showing the 4 transactions which succeeded