CREATE DATABASE Chess4

CREATE TABLE ChessTitle(
	tid TINYINT PRIMARY KEY,
	title_name CHAR(15)
);

CREATE TABLE ChessClub(
	cid INT PRIMARY KEY,
	club_name VARCHAR(100)
);

CREATE TABLE ChessPlayer (
	player_id INT PRIMARY KEY,
	player_name VARCHAR(100),
	rating INT DEFAULT 'TBA',
	title_id TINYINT REFERENCES ChessTitle(tid),
	club_id INT REFERENCES ChessClub(cid) DEFAULT 'TBA'
);

CREATE TABLE ClubPlayers(
	centry_id INT PRIMARY KEY,
	club_id INT,
	player_id INT,
	CONSTRAINT FK_ClubPlayers_ChessPlayer FOREIGN KEY (player_id) REFERENCES ChessPlayer (player_id),
	CONSTRAINT FK_ClubPlayers_ChessClub FOREIGN KEY (club_id) REFERENCES ChessClub (cid)
);

CREATE TABLE Tournament(
	tourn_id INT PRIMARY KEY,
	tourn_name VARCHAR(200)
);

CREATE TABLE TournamentParticipantsHistory(
	entry_id INT PRIMARY KEY,
	player_id INT,
	tourn_id INT,
	CONSTRAINT FK_TournamentParticipantsHistory_ChessPlayer FOREIGN KEY (player_id) REFERENCES ChessPlayer (player_id),
	CONSTRAINT FK_TournamentParticipantsHistory_Tournament FOREIGN KEY (tourn_id) REFERENCES Tournament (tourn_id)
);

CREATE TABLE FideStandings(
	rank_id INT PRIMARY KEY,
	player_id INT REFERENCES ChessPlayer(player_id)
);

CREATE TABLE MatchFormat(
	type_id TINYINT PRIMARY KEY,
	type VARCHAR(15)
);

CREATE TABLE Match(
	match_id INT PRIMARY KEY, 
	white_id INT REFERENCES ChessPlayer(player_id),
	black_id INT REFERENCES ChessPlayer(player_id), 
	match_type TINYINT REFERENCES MatchFormat(type_id)
);


CREATE TABLE WorldChampions(
	worldc_id TINYINT PRIMARY KEY,
	player_id INT REFERENCES ChessPlayer(player_id),
	years TINYINT DEFAULT 'TBA'
);

CREATE TABLE Tactic (
	tactic_id INT PRIMARY KEY,
	tactic_name VARCHAR(30) DEFAULT 'TBA'
);

CREATE TABLE TacticsHistory(
	player_id INT, 
	tactic_id INT,
	CONSTRAINT FK_TacticsHistory_ChessPlayer FOREIGN KEY (player_id) REFERENCES ChessPlayer (player_id),
	CONSTRAINT FK_TacticsHistory_Tactic FOREIGN KEY (tactic_id) REFERENCES Tactic (tactic_id),
	CONSTRAINT PK_TacticsHistory PRIMARY KEY NONCLUSTERED (player_id,tactic_id)
);