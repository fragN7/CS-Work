use GSM
go

delete Requests 
go

delete Reservations
go

delete Clients
go

delete Locations
go

create or alter procedure insertIntoClients(@rows int) as
    while @rows > 0 begin
        insert into Clients values (@rows, 'Name', '2022-12-14', @rows)
        set @rows = @rows-1
    end
go

create or alter procedure insertIntoLocations(@rows int) as
    while @rows > 0 begin
        insert into Locations values (@rows, 'Name', rand(1), @rows)
        set @rows = @rows - 1
    end
go

create or alter procedure insertIntoReservations(@rows int) as
    declare @cid int
    declare @lid int
    while @rows > 0 begin
        set @cid = (select top 1 cid from Clients order by NEWID())
        set @lid = (select top 1 lid from Locations order by NEWID())
        insert into Reservations values (@rows, @rows % 50, @cid, @lid)
        set @rows = @rows-1
    end
go

exec insertIntoClients 1000
exec insertIntoLocations 2000
exec insertIntoReservations 3000
go

--a--

create nonclustered index index1 on Clients(client_phone)
go

drop index index1 on Clients
go

-- Clustered Index Scan --0.007345
select * from Clients order by cid 
go

-- Clustered Index Seek --0.0032831
select * from clients where cid = 1 
go

-- Nonclustered Index Scan --0.0051227
select Clients.client_phone from Clients order by client_phone 
go

select * from Clients
select * from Locations
select * from Reservations

-- Nonclustered Index Seek --0.0065704
select Clients.client_phone from Clients where client_phone = 1
go

select * from Clients

-- Key Lookup --0.0065704
select Clients.client_birth from Clients where Clients.client_phone = 1
go

--b--

create nonclustered index index2 on Locations(location_time) --include (lid, location_availability)
go

drop index index2 on Locations
go

--0.099264
select * from Locations where location_time = 4 
go

--c--

create or alter view MyView as
    select top 100 Clients.client_phone, Locations.location_time
    from Reservations join Clients on Reservations.client_id = Clients.cid join Locations on Reservations.location_id = Locations.lid
    where Locations.location_time > 50 or Clients.client_phone < 15
go

select * from MyView