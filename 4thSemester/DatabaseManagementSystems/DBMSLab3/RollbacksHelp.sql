use ChessDB;
go

select * from ChessPlayer;
select * from Tactic;
select * from TacticsHistory;
delete from ChessPlayer where player_name like 'Mario Iaguta';
delete from Tactic where tactic_name like 'English Game';
delete from TacticsHistory where player_id = 2 and tactic_id = 1;