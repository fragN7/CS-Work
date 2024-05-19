use ChessDB;
go

select * from ChessPlayer;
select * from Tactic;
select * from TacticsHistory;
delete from ChessPlayer where player_name like 'Mario Iaguta';
delete from ChessPlayer where player_name like 'Alen Iaguta';
delete from Tactic where tactic_name like 'English Game';
delete from Tactic where tactic_name like 'Berlin Defense';
delete from TacticsHistory where player_id = 2 and tactic_id = 2;