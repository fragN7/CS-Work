create database pc
go

use pc
go

create table ComponentTypes(
	ctid int primary key,
	ctype_name varchar(15),
	ctype_description varchar(15)
)

create table Companies(
	companyid int primary key,
	company_name varchar(15) unique,
	company_address varchar(15)
)

create table Components(
	componentid int primary key,
	component_name varchar(15),
	component_price decimal,
	component_time int,
	ctid int,
	foreign key (ctid) references ComponentTypes(ctid)
)

create table Models(
	mid int primary key,
	model_name varchar(15) unique,
	companyid int,
	componentid int,
	foreign key (companyid) references Companies(companyid),
	foreign key (componentid) references Components(componentid)
)

insert into ComponentTypes values (1, 'life', 'none')
insert into ComponentTypes values (2, 'no', 'life')
insert into ComponentTypes values (3, '421', '6094')

insert into Companies values (1, 'comp1', 'piezisa')
insert into Companies values (2, 'comp2', 'mihali')
insert into Companies values (3, 'comp3', 'fsega')

insert into Components values (1, 'component', 142.12, 41, 1)
insert into Components values (2, 'component2', 123.32, 55, 2)
insert into Components values (3, 'sdasdas', 314.412, 222, 1)

insert into Models values (1, 'myname', 1, 2)
insert into Models values (2, 'yourname', 2, 3)
go

create procedure addToPc (@mid int, @cid int, @price int, @time int) as
	declare @nr int
	set @nr = 0
	select @nr = count(*) from Models where mid = @mid and componentid = @cid
	if (@nr <> 0) begin
		update Components
		set component_price = @price, component_time = @time
		where componentid = @cid
	end
	else begin
		insert into Components values (@cid, 'name', @price, @time, 1)
	end
go

create or alter view viewComp as
	select cm.company_name
	from (
		select distinct Models.companyid, Companies.company_name
		from Models, Companies
	) as cm
	group by cm.company_name
	having count(*) = (select count(*) from Components)
go

create or alter procedure procedureAvg (@r int) as
begin
	select component_name
	from Components
	group by component_name
	having avg(component_time) > @r
end
go

exec procedureAvg 5
go
