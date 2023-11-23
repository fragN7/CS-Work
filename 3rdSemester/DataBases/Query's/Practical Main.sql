IF DB_ID('Pregatire Practic DB') IS NULL
   create database [Pregatire Practic DB]

use [Pregatire Practic DB]

DROP TABLE IF EXISTS Transactions
DROP TABLE IF EXISTS Cards
DROP TABLE IF EXISTS BankAccounts
DROP TABLE if EXISTS Customers
DROP TABLE IF EXISTS ATM

create table Customers (
	CustomerId int primary key not null,
	Name char(50),
	BirthDate date,
)

create table BankAccounts (
	BaId int primary key not null,
	IBAN char(34),
	CurrentBalance int, 
	CustomerId int ,
	Foreign Key (CustomerId) References Customers(CustomerId)
)

create table Cards (
	CardNumber char(19) primary key,
	Cvv char(3),
	BaId int,
	Foreign Key (BaId) References BankAccounts(BaId)
)

create table ATM (
	AtmId int primary key,
	Address varchar(30),
)

create table Transactions (
	TId int primary key,
	AtmId int,
	CardNumber char(19),
	Balance int,
	Time datetime,
	Foreign Key (CardNumber) References Cards(CardNumber),
	Foreign Key (AtmId) References ATM(AtmId),
)

	--CustomerId int primary key not null,
	--Name char(50),
	--BirthDate date,
insert into Customers
values
(1, 'Ion Mircea', '01-jan-1970'),
(2, 'Dan Suciu', '03-feb-1980'),
(3, 'Maluma Baby', '09-10-1985'),
(4, 'Dan Badea', '04-10-1890')
;

	--BaId int primary key not null,
	--IBAN char(34),
	--CurrentBalance int, 
	--CustomerId int,
	--Foreign Key (CustomerId) References Customers(CustomerId)

insert into BankAccounts
values
(1, 'RO54RZBR3858514268674891', 2000, 1),
(2, 'RO04RZBR1711787311512738', 10000, 1),
(3, 'RO85PORL5457812918323614', 30000, 2),
(4, 'RO30PORL3617216244955489', 500, 3),
(5, 'RO91RZBR7969869465119449', 100, 4)
;


	--CardNumber char(19) primary key,
	--Cvv char(3),
	--BaId int,
	--Foreign Key (BaId) References BankAccounts(BaId)
insert into Cards 
values
('4617423350119807', 807, 1),
('4768925113901070', 070, 1),
('4779894410036856', 856, 2),
('4632158562688451', 451, 3),
('4703414907155415', 415, 4),
('4429681220252896', 896, 5)
;

	--AtmId int primary key,
	--Address varchar(30),
insert into Atm
values
(1, 'adresa 1'),
(2, 'adresa 1')
;

	--TId int primary key,
	--AtmId int,
	--CardNumber char(19),
	--Balance int,
	--Time datetime,
	--Foreign Key (CardNumber) References Cards(CardNumber),
	--Foreign Key (AtmId) References ATM(AtmId),
insert into Transactions
values
(1, 1, '4617423350119807', 200, '05-01-2020'),
(2, 1, '4768925113901070', 200, '05-01-2020'),
(3, 1, '4429681220252896', 200, '05-01-2020'),
(4, 2, '4703414907155415', 200, '05-01-2020'),
(5, 1, '4617423350119807', 400, '06-01-2020'),
(6, 2, '4768925113901070', 300, '04-01-2020')
;

select * from Customers
select * from BankAccounts
select * from Cards
select * from ATM
select * from Transactions

--exec pr1 '4617423350119807'
select * from view1
select * from fun1(400)