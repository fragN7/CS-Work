use master
go

drop database GSM 
go

create database GSM
go
use GSM
go

create table Clients(
	cid int primary key,
	client_name varchar(15) not null,
	client_birth int not null,
	client_phone int unique
);

create table Locations(
	lid int primary key,
	location_name varchar(15) not null,
	location_availability bit default 1 not null,
	location_time int not null
);

create table MembershipTypes(
	mtid int primary key,
	memtype_name varchar(15) not null,
	memtype_country varchar(15)
);

create table Memberships(
	mid int primary key,
	membership_name varchar(15) not null,
	membership_company varchar(15) not null,
	membership_price int default 0 not null,
	membership_popularity int,
	membershiptype_id int references MembershipTypes(mtid) not null
);

create table Reservations(
	resid int primary key,
	reservation_dificulty int,
	client_id int references Clients(cid),
	location_id int references Locations(lid)
);

create table Requests(
	reqid int,
	request_special bit default 0 not null, 
	reservation_id int,
	membership_id int,
	constraint fk_request_reservation foreign key (reservation_id) references Reservations(resid),
	constraint fk_request_membership foreign key (membership_id) references Memberships(mid)
);

create table EmployeeRoles(
	erid int primary key,
	emprole_name varchar(15) not null,
	emprole_vacancy bit default 0 not null
);

create table Employees(
	eid int primary key,
	employee_name char(15) not null,
	employee_servstart date,
	employeerole_id int references EmployeeRoles(erid) not null
);

create table ActionTypes(
	atid int primary key,
	acttype_name varchar(15) not null,
	acttype_obligated bit default 0 not null
);

create table RequestStages(
	reqstage_name varchar(15),
	request_id int,
	employee_id int,
	actiontype_id int,
	constraint fk_requeststage_request foreign key (request_id) references Requests(reqid),
	constraint fk_requeststage_employee foreign key (employee_id) references Employees(eid),
	constraint fk_requeststage_actiontype foreign key (actiontype_id) references ActionTypes(atid),
	constraint pk_requeststage_id primary key nonclustered (request_id, employee_id, actiontype_id)
);



