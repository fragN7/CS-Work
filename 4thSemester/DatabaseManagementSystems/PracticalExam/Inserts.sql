-- Insert values into SportTypes table


INSERT INTO SportTypes (sport_type_id, description)
VALUES (1, 'Football'),
       (2, 'Basketball'),
       (3, 'Tennis');

-- Insert values into Sports table
INSERT INTO Sports (sport_id, sport_type_id, name, description, location)
VALUES (1, 1, 'Football World Cup', 'International football tournament', 'Various locations'),
       (2, 2, 'NBA Finals', 'Basketball championship series', 'United States'),
       (3, 3, 'Wimbledon', 'Grand Slam tennis tournament', 'London, United Kingdom');

-- Insert values into Players table
INSERT INTO Players (player_id, sport_id, name, surname, date_of_birth, gender)
VALUES (1, 1, 'Lionel', 'Messi', '1987-06-24', 'M'),
       (2, 2, 'LeBron', 'James', '1984-12-30', 'M'),
       (3, 3, 'Serena', 'Williams', '1981-09-26', 'F');

-- Insert values into Clubs table
INSERT INTO Clubs (club_id, name, opening_year, number_of_start)
VALUES (1, 'FC Barcelona', 1899, 5),
       (2, 'Los Angeles Lakers', 1947, 16),
       (3, 'All England Lawn Tennis and Croquet Club', 1877, 100);

-- Insert values into ClubMembers table
INSERT INTO Participations (club_id, player_id, fee, enrollment_date)
VALUES (1, 1, 100.00, '2023-01-01'),
       (2, 2, 200.00, '2023-02-15'),
       (3, 3, 150.00, '2023-03-10');
GO

DELETE FROM Participations WHERE player_id = 3;


SELECT * from Sports;
SELECT * FROM Players;