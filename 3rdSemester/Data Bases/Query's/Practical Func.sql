create or alter function fun1 (@sum int)
returns table
as
return 
	select c.CardNumber, c.Cvv
	from Cards c
	inner join Transactions t on c.CardNumber=t.CardNumber 
	GROUP BY C.cardnumber, C.CVV 
	HAVING SUM(t.Balance) > @sum
go

create or alter view view1 
as
	select sq.CardNumber
	from (    
		SELECT distinct t.CardNumber, t.AtmId
		FROM Transactions t
	) as sq
	GROUP BY sq.CardNumber
	HAVING COUNT(*) = (SELECT COUNT(*) FROM ATM)
go

create or alter procedure pr1 @cardnumber char(19)
as
begin
	delete 	
	from Transactions
	where Transactions.CardNumber Like @cardnumber
end
go
