use master
go

use GSM
go

--Client Population
insert into Clients values (1, 'Lionel Messi', '12/10/1987', 0741526306);
insert into Clients values (2, 'Cristiano Ronaldo', '11/09/1988', 0791526307);
insert into Clients values (3, 'Roy Jones', '10/08/1989', 0741526356);
insert into Clients values (4, 'Victor Ponta', '09/07/1990', 0721526206);
insert into Clients values (5, 'Adi Minune', '08/06/1991', 0741521306);
insert into Clients values (6, 'Nicolae Guta', '07/05/1992', 0731596309);
insert into Clients values (7, 'Elon Musk', '06/04/1993', 0741826308);
insert into Clients values (8, 'John Cena', '05/03/1994', 0746526305);

--Location Population
insert into Locations values (1, 'Manastur', 0, 12);
insert into Locations values (2, 'Floresti', 0, 13);
insert into Locations values (3, 'Marasti', 1, 14);
insert into Locations values (4, 'Gheorgheni', 1, 00);
insert into Locations values (5, 'Manastur', 0, 05);
insert into Locations values (6, 'FSEGA', 1, 22);

--Reservation Population
insert into Reservations values (1, 8, 1, 20); 
insert into Reservations values (2, 3, 2, 4);
insert into Reservations values (3, 4, 3, 3);
insert into Reservations values (4, 10, 4, 6);
insert into Reservations values (5, 5, 4, 2);
insert into Reservations values (6, 1, 7, 1);
insert into Reservations values (7, 7, 8, 3);

--Memmbership Types Population
insert into MembershipTypes values (1, 'World Wide', 'Germany');
insert into MembershipTypes values (2, 'Local', 'USA');
insert into MembershipTypes values (3, 'Regional', 'Germany');
insert into MembershipTypes values (4, 'Local', 'UK');
insert into MembershipTypes values (5, 'World Wide', 'Romania');

--Memberships Population
insert into Memberships values (1, 'Yearly', 'Drei', 80, 90, 4);
insert into Memberships values (2, 'Daily', 'Verizon', 1, 60, 2);
insert into Memberships values (3, 'Weekly', 'Telekom', 5, 72, 1);
insert into Memberships values (4, 'Yearly', 'Drei', 125, 28, 3);
insert into Memberships values (5, 'Monthly', 'Orange', 10, 45, 5);

--Requests Population
insert into Requests values (1, 1, 6, 1);
insert into Requests values (2, 0, 5, 3);
insert into Requests values (3, 1, 7, 1);
insert into Requests values (4, 0, 1, 4);
insert into Requests values (5, 0, 3, 5);

--Employee Roles Population
insert into EmployeeRoles values (1, 'Storage', 1);
insert into EmployeeRoles values (2, 'Cashier', 0);
insert into EmployeeRoles values (3, 'Human Relations', 1);
insert into EmployeeRoles values (4, 'Advertiser', 0);
insert into EmployeeRoles values (5, 'Human Relations', 0);

--Employees Population
insert into Employees values (1, 'Lucian Blaga', '10/11/2021', 1);
insert into Employees values (2, 'Mihai Eminescu', '04/09/2016', 1);
insert into Employees values (3, 'Ion Creanga', '04/09/2016', 2);
insert into Employees values (4, 'Ye West', '25/12/2018', 4);
insert into Employees values (5, 'Kendrick Lamar', '28/02/2021', 3);
insert into Employees values (6, 'Jermain Cole', '01/05/2017', 4);

--Action Types Population
insert into ActionTypes values (1, 'handling', 1);
insert into ActionTypes values (2, 'documenting', 1);
insert into ActionTypes values (3, 'presenting', 0);

--Request Stages Population
insert into RequestStages values ('confirmation', 2, 2, 3);
insert into RequestStages values ('selection', 5, 2, 4);
insert into RequestStages values ('preparation', 3, 5, 4);
insert into RequestStages values ('confirmation', 2, 1, 2);
insert into RequestStages values ('closing', 4, 3, 1);

--Updates
update Locations
set location_time = 12
where location_availability = 0;

update Locations
set location_availability = 1
where (location_name = 'Manastur' and location_time >= 12);

update Memberships
set membership_company = 'None'
where (membership_name = 'Yearly' or membership_name = 'Weekly');

update ActionTypes
set acttype_name = 'handling'
where not acttype_obligated = 0;

update Employees
set employee_name = 'None'
where employeerole_id <= 2;

update Memberships
set membership_price += 15
where membership_popularity is not null;

update Requests
set request_special = 1
where reqid <> 2;

update Memberships
set membership_company = 'Cosmote'
where membership_popularity > 50 and membership_price < 10;

--Deletes
delete from Locations where location_time between 0 and 8;
delete from Clients where client_name in ('Adi Minune', 'Nicolae Guta', 'Tion Wayne');
delete from MembershipTypes where memtype_country like 'U%';

--a

--id of clients who appear or don't in a reservation
select cid
from Clients
union all
select client_id
from Reservations;

--id of clients having the name Lionel Messi or their phone number starts with 07415
select cid
from Clients
where client_name = 'Lionel Messi' or client_phone like '07415%';

--b

-- id of memberships that appear at least once in a request
select mid
from Memberships
intersect
select membership_id
from Requests

--id of memberships having the company name Drei or Orange
select mid
from Memberships
where membership_company in ('Drei', 'Orange');

--c

--id of employee roles that have no employees assigned
select erid
from EmployeeRoles
except
select employeerole_id
from Employees

--id of employee roles that are not in Human Relations or Storage
select erid
from EmployeeRoles
where emprole_name not in ('Human Relations', 'Storage');

--d

--full join with top 3
select top 3 Memberships.mid, MembershipTypes.mtid
from Memberships
full join MembershipTypes on Memberships.membershiptype_id = MembershipTypes.mtid;

--4 tables inner/2 m:n
select Requests.reservation_id, Reservations.resid, Memberships.mid, RequestStages.request_id
from Requests
inner join Reservations on Reservations.resid = Requests.reservation_id
inner join Memberships on Memberships.mid = Requests.membership_id
inner join RequestStages on RequestStages.request_id = Reservations.resid

--right
select Requests.reqid, Requests.membership_id, Memberships.mid
from Requests
right join Memberships on Requests.membership_id = Memberships.mid;

--2 m:n left
select Requests.reqid, Reservations.resid, Requests.reservation_id
from Requests
left join Reservations on Requests.reservation_id = Reservations.resid;

--2day
select 

--e

-- name of clients who have a reservation with id 1
select Clients.client_name
from Clients 
where Clients.cid in (select Reservations.client_id 
					  from Reservations
					  where Reservations.resid = 1);

--name of Memberships who have a membership price of 80 and have a membership type of id 4
select Memberships.membership_name
from Memberships
where Memberships.mid in (select Memberships.mid
						  from Memberships
						  where Memberships.membership_price = 80 and Memberships.membershiptype_id in 
																	(select MembershipTypes.mtid
																	 from MembershipTypes
																	 where MembershipTypes.mtid = 4
						  )
);

--f

--employees name and birthdate where they have worked on a request stage with id 2
select Employees.employee_name, Employees.employee_servstart
from Employees
where exists (select * 
		      from RequestStages
			  where RequestStages.employee_id = Employees.eid and RequestStages.request_id = 2);

--clients name where they appear in a reservation which has a difficulty between 7 and 10 
select Clients.client_name
from Clients
where exists (select * 
			  from Reservations
			  where Reservations.client_id = Clients.cid and Reservations.reservation_dificulty between 7 and 10);

--g

--clients who have a reservation with id 1
select Clients.*
from Clients inner join 
(select * 
 from Reservations
 where Reservations.resid = 1) as x
on Clients.cid = x.client_id;

--locations that appear in a reservation with id 1
select Locations.*
from Locations inner join
(select *
 from Reservations
 where Reservations.resid = 1) as x
on Locations.lid = x.location_id;

--h

--lowest price on a membership per membership type
select min(Memberships.membership_price) MinPrice
from Memberships
group by Memberships.membershiptype_id

--memberhisps that have been requested the most
select Requests.membership_id, count(*) NumMemberships
from Requests
group by Requests.membership_id
having count(*) = (select max(NumMemberships)
				   from (select count(*) NumMemberships
						 from Requests
						 group by Requests.membership_id) t
					);

--employee roles that have been assigned at least once
select Employees.employeerole_id, count(Employees.employeerole_id)
from Employees
group by Employees.employeerole_id
having count(Employees.employeerole_id) > 1
order by Employees.employeerole_id desc

--memberships which prices are greater than the average
(select Memberships.membership_price
from Memberships
group by Memberships.membership_price
having Memberships.membership_price > (select avg(Memberships.membership_price) AvgRating
									   from Memberships)
);

--i

--order desc by name all memberships with a higher price than memberships with the company name 'Drei'
select distinct Memberships.membership_company, Memberships.membership_name
from Memberships
where Memberships.membership_price > any
		(select Memberships.membership_price
		 from Memberships
		 where Memberships.membership_company = 'Drei')
order by Memberships.membership_name desc;

--same stuff but with 'in' and sorted by price asc
select distinct top 2 Memberships.membership_name, Memberships.membership_price
from Memberships
where Memberships.membership_price in
		(select Memberships.membership_price
		 from Memberships
		 where Memberships.membership_name = 'Drei'
		 )
order by Memberships.membership_price;

--names of memberships who have different price than membership with id 1
select distinct Memberships.membership_name
from Memberships
where Memberships.membership_price <> all
		(select Memberships.membership_price
		from Memberships
		where Memberships.mid = 1);

--same stuff but with 'not in'
select distinct Memberships.membership_name
from Memberships
where Memberships.membership_price not in
		(select Memberships.membership_price
		from Memberships
		where Memberships.mid = 1); 

--names of memberships that have a greater price than memberships whose membership type id is different of 2
select Memberships.membership_name
from Memberships
where Memberships.membership_price > any
		(select Memberships.membership_price
		 from Memberships
		 where Memberships.membershiptype_id = 2);

--same stuff but with min
select Memberships.membership_name
from Memberships
where Memberships.membership_price >
		(select min(Memberships.membership_price)
		 from Memberships);

--
select Memberships.membership_name
from Memberships
where Memberships.membership_price < any
		(select Memberships.membership_price
		 from Memberships
		 where Memberships.membershiptype_id = 2);

--same stuff but with max
select Memberships.membership_name
from Memberships
where Memberships.membership_price <
		(select max(Memberships.membership_price)
		 from Memberships);
