USE ChessDB;
GO


DROP TABLE IF EXISTS LogTable 
CREATE TABLE LogTable(
	Lid INT IDENTITY PRIMARY KEY,
	TypeOperation VARCHAR(50),
	TableOperation VARCHAR(50),
	ExecutionDate DATETIME
);
GO

DROP FUNCTION uf_ValidateRating;
DROP PROCEDURE uspAddTactic;
DROP PROCEDURE uspAddPlayer;
DROP PROCEDURE uspAddTacticsHistory;
DROP PROCEDURE uspAddCommitScenario;
DROP PROCEDURE uspAddRollbackScenario;
GO

--rating validation
CREATE FUNCTION uf_ValidateRating(@rating INT) RETURNS INT AS 
BEGIN
    DECLARE @return INT 
    SET @return = 0 

    IF @rating BETWEEN 0 AND 3500
        SET @return = 1 

    RETURN @return
END
GO


-- check for duplicates
CREATE PROCEDURE uspAddTactic (@tactic_name VARCHAR(30))
AS
	IF EXISTS (SELECT * FROM Tactic WHERE tactic_name=@tactic_name)
	BEGIN 
		RAISERROR('Tactic already exists',14,1)
	END
	INSERT INTO Tactic VALUES (@tactic_name)
	INSERT INTO LogTable VALUES('add','tactic',GETDATE())
GO

-- check for duplicates and validate rating
CREATE PROCEDURE uspAddPlayer (@player_name VARCHAR(100), @player_rating INT, @title_id TINYINT, @club_id TINYINT)
AS
	IF(dbo.uf_ValidateRating(@player_rating) <> 1)
	BEGIN
		RAISERROR('Rating should be anywhere between 0 and 3500', 14, 1)
	END

	IF EXISTS (SELECT * FROM ChessPlayer WHERE player_name=@player_name AND rating=@player_rating AND title_id=@title_id AND club_id=@club_id)
	BEGIN
		RAISERROR('Player already added',14,1)
	END

	INSERT INTO ChessPlayer VALUES (@player_name, @player_rating, @title_id, @club_id)
	INSERT INTO LogTable VALUES ('add', 'player', GETDATE())
GO

-- check that player_id is ok, tactic_id is ok  & the pair doesn't already exist 
CREATE PROCEDURE uspAddTacticsHistory (@player_id INT, @tactic_id INT)
AS
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
GO

CREATE PROCEDURE uspAddRollbackScenario 
AS
	BEGIN TRAN
	BEGIN TRY 
		EXEC uspAddPlayer 'Alen Iaguta', 4500, 3, 2 -- enter the rating validation branch so this will fail, so the next two will never be reached
		EXEC uspAddTactic 'Berlin Defense' 
		EXEC uspAddTacticsHistory 2, 2 
		COMMIT TRAN
	END TRY
	BEGIN CATCH -- if one transaction fails i.e. throws exception, rollback everything
		ROLLBACK TRAN
	END CATCH
GO

CREATE PROCEDURE uspAddCommitScenario
AS
	BEGIN TRAN
	BEGIN TRY 
		EXEC uspAddPlayer 'Mario Iaguta', 1200, 2,2 -- all 3 will succeed
		EXEC uspAddTactic 'English Game' 
		EXEC uspAddTacticsHistory 2, 1 
		COMMIT TRAN
	END TRY
	BEGIN CATCH 
		ROLLBACK TRAN
		RETURN
	END CATCH

GO

EXEC uspAddRollbackScenario
EXEC uspAddCommitScenario
GO

--3 entries will be added to the log table
--select * from LogTable
select * from LogTable;