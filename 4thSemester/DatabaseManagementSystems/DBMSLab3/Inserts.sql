-- Insert data into ChessTitle table
use ChessDB;
go

INSERT INTO ChessTitle (title_name)
VALUES
  ('Grandmaster'),
  ('Nation Master'),
  ('FIDE Master');

-- Insert data into ChessClub table
INSERT INTO ChessClub (club_name)
VALUES
  ('Chess Club A'),
  ('Chess Club B'),
  ('Chess Club C');

-- Insert data into ChessPlayer table
INSERT INTO ChessPlayer (player_name, rating, title_id, club_id)
VALUES
  ('Magnus Carlsen', 2870, 1, 1),
  ('Fabiano Caruana', 2820, 2, 2),
  ('Ding Liren', 2805, 2, 3);

-- Insert data into ClubPlayers table
INSERT INTO ClubPlayers (club_id, player_id)
VALUES
  (1, 1),
  (2, 2),
  (3, 3);

-- Insert data into Tournament table
INSERT INTO Tournament (tourn_name)
VALUES
  ('Chess Tournament 1'),
  ('Chess Tournament 2'),
  ('Chess Tournament 3');

-- Insert data into TournamentParticipantsHistory table
INSERT INTO TournamentParticipantsHistory (player_id, tourn_id)
VALUES
  (1, 1),
  (2, 2),
  (3, 3);

-- Insert data into FideStandings table
INSERT INTO FideStandings (player_id)
VALUES
  (1),
  (2),
  (3);

-- Insert data into MatchFormat table
INSERT INTO MatchFormat (type)
VALUES
  ('Standard'),
  ('Rapid'),
  ('Blitz');

-- Insert data into Match table
INSERT INTO Match (white_id, black_id, match_type)
VALUES
  (1, 2, 1),
  (3, 1, 2),
  (2, 3, 3);

-- Insert data into WorldChampions table
INSERT INTO WorldChampions (player_id, years)
VALUES
  (1, 3),
  (2, 2),
  (3, 4);

-- Insert data into Tactic table
INSERT INTO Tactic (tactic_name)
VALUES
  ('Fork'),
  ('Pin'),
  ('Skewer');

-- Insert data into TacticsHistory table
INSERT INTO TacticsHistory (player_id, tactic_id)
VALUES
  (1, 1),
  (2, 2),
  (3, 3);
