--Phantom
--phantom problem T1
BEGIN TRAN 
WAITFOR DELAY '00:00:04'
INSERT INTO Participations(player_id, club_id) VALUES (1, 1)
COMMIT TRAN
GO

select * from Participations;
DELETE FROM Participations WHERE player_id=1