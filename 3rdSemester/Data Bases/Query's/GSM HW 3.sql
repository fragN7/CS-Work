use GSM
go

--a-- 
create or alter procedure setVacancyFromEmployeeRolesTinyint as
	alter table EmployeeRoles alter column emprole_vacancy tinyint;

go

create or alter procedure setVacancyFromEmployeeRolesBit as 
	alter table EmployeeRoles alter column emprole_vacancy bit;

go

--b--
create or alter procedure addResidenceToClient as
	alter table Clients add client_residence varchar(15);

go

create or alter procedure removeResidenceClient as
	alter table Clients drop column client_residence;

go

--c--
create or alter procedure addDefaultToEmployeeRolesVacancy as
	alter table EmployeeRoles add constraint default0 default(0) for emprole_vacancy;

go

create or alter procedure removeDefaultFromEmployeeRolesVacancy as
	alter table EmployeeRoles drop constraint default0;

go

--g--
create or alter procedure addAccounts as
	create table Accounts (
		aid tinyint not null,
		account_email varchar(15),
		account_hash varchar(15) not null,
		client_id int references Clients(cid),
		constraint PK_account primary key(aid)
		)

go

exec removeAccounts;
exec addAccounts;

create or alter procedure removeAccounts as
	drop table if exists Accounts;

go

--d--
create or alter procedure addPKAccounts as
	alter table Accounts
		drop constraint PK_account
	alter table Accounts
		add constraint PK_account primary key (aid, account_hash);

go

create or alter procedure removePKAccounts as
	alter table Accounts
		drop constraint PK_account
	alter table Accounts
		add constraint PK_account primary key (aid);

go

--e--
create or alter procedure addCKLocations as
	alter table Locations
		add constraint location_candidateKey unique (lid, location_name);

go

create or alter procedure removeCKLocations as
	alter table Locations
		drop constraint location_candidateKey;

go

--f--
create or alter procedure addFKAccounts as
	alter table Accounts
		add constraint fk_client_id foreign key(client_id) references Clients(cid);

go

create or alter procedure removeFKAccounts as
	alter table Accounts
		drop constraint fk_client_id;

go

create table VersionTable(
	version_count int 
)

insert into VersionTable values (0);

go

drop table MenuTable;

create table MenuTable(
	from_version int,
	to_version int,
	proced_name varchar(50),
	primary key (from_version, to_version)
)
go

insert into MenuTable values (0, 1, 'setVacancyFromEmployeeRolesTinyint')
insert into MenuTable values (1, 0, 'setVacancyFromEmployeeRolesBit')
insert into MenuTable values (1, 2, 'addResidenceToClient')
insert into MenuTable values (2, 1, 'removeResidenceClient')
insert into MenuTable values (2, 3, 'addDefaultToEmployeeRolesVacancy')
insert into MenuTable values (3, 2, 'removeDefaultFromEmployeeRolesVacancy')
insert into MenuTable values (3, 4, 'addAccounts')
insert into MenuTable values (4, 3, 'removeAccounts')
insert into MenuTable values (4, 5, 'addCKLocations')
insert into MenuTable values (5, 4, 'removeCKLocations')
insert into MenuTable values (5, 6, 'addFKAccounts')
insert into MenuTable values (6, 5, 'removeFKAccounts')
insert into MenuTable values (6, 7, 'addPKAccounts')
insert into MenuTable values (7, 6, 'removePKAccounts')

go

create or alter procedure main(@version int) as
	declare @index int
	declare @cmd varchar(50)
	select @index = version_count from VersionTable

	if @version > (select max(to_version) from MenuTable)
		raiserror ('Not good', 0, 19)

	while @index > @version begin
		select @cmd = proced_name from MenuTable where from_version = @index and to_version = @index - 1
		exec (@cmd)
		set @index = @index - 1
	end

	while @index < @version begin
		select @cmd = proced_name from MenuTable where from_version = @index and to_version = @index + 1
		exec (@cmd)
		set @index = @index + 1
	end

	update VersionTable set version_count = @version

go

execute main 0

select *
from VersionTable

update VersionTable set version_count = 0