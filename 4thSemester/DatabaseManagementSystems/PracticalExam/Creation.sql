use SportPerformances;

CREATE TABLE SportTypes (
    sport_type_id INT PRIMARY KEY,
    description VARCHAR(255)
);

CREATE TABLE Sports (
    sport_id INT PRIMARY KEY,
    sport_type_id INT,
    name VARCHAR(255),
    description VARCHAR(255),
    location VARCHAR(255),
    FOREIGN KEY (sport_type_id) REFERENCES SportTypes(sport_type_id)
);

CREATE TABLE Players (
    player_id INT PRIMARY KEY,
    sport_id INT,
    name VARCHAR(255),
    surname VARCHAR(255),
    date_of_birth DATE,
    gender CHAR(1),
    FOREIGN KEY (sport_id) REFERENCES Sports(sport_id)
);

CREATE TABLE Clubs (
    club_id INT PRIMARY KEY,
    name VARCHAR(255),
    opening_year INT,
    number_of_start INT
);

CREATE TABLE Participations (
    club_id INT,
    player_id INT,
    fee DECIMAL(10, 2),
    enrollment_date DATE,
    PRIMARY KEY (club_id, player_id),
    FOREIGN KEY (club_id) REFERENCES Clubs(club_id),
    FOREIGN KEY (player_id) REFERENCES Players(player_id)
);
