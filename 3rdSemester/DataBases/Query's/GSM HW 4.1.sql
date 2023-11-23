--use GSM
go

create or alter procedure addEmployeeRoles (@rows int) as
begin
	declare @index int = 0
	while @index < @rows 
	begin
		insert into EmployeeRoles values (@index, 'Name', rand(1))
		set @index = @index + 1
	end
end
go

create or alter procedure deleteEmployeeRoles as
begin 
	delete from EmployeeRoles where emprole_name like 'Name%'
end
go

create or alter procedure addEmployees (@rows int) as
begin
	declare @index int = 0
	while @index < @rows
	begin
		declare @role int = (select top 1 erid from EmployeeRoles where emprole_name like 'Name%' order by NEWID())
		insert into Employees values (@index, 'Name', sysdatetime() - rand(14), @role)
		set @index = @index + 1
	end
end
go

create or alter procedure deleteEmployees as
begin 
	delete from Employees where employee_name like 'Name%'
end
go

create or alter procedure addActionTypes (@rows int) as
begin
	declare @index int = 0
	while @index < @rows
	begin 
		insert into ActionTypes values (@index, 'Name', rand(1))
		set @index = @index + 1
	end
end
go

create or alter procedure deleteActionTypes as
begin 
	delete from ActionTypes where acttype_name like 'Name%'
end
go

create or alter procedure addRequestStages (@rows int) as
begin
	declare @index int = 0
	declare @actiontype int
	declare @employee int

	declare TestDataCursor cursor for
	select a.atid, e.eid
	from (select atid from ActionTypes where acttype_name like 'Name%') a
	cross join
		(select eid from Employees where employee_name like 'Name%') e

	open TestDataCursor
	fetch TestDataCursor
	into @actiontype, @employee

	while @index < @rows
	begin
		insert into RequestStages values ('Name', @employee, @actiontype, @index)
		set @index = @index + 1

		fetch TestDataCursor
		into @actiontype, @employee
	end

	close TestDataCursor
	deallocate TestDataCursor
end
go

create or alter procedure deleteRequestStages as
begin
	delete from RequestStages where reqstage_name like 'Name'
end
go

--shows--

create or alter view showEmployeeRoles as
	select employee_name from Employees where employee_name like 'Name%'
go

create or alter view showEmployees as
	select Employees.employee_name as 'Employee name', Employees.employee_servstart as 'Employee start service'
	from Employees inner join EmployeeRoles on EmployeeRoles.erid = Employees.employeerole_id
go

create or alter view showRequestStages as
	select RequestStages.reqstage_name as 'Request stage name'
	from RequestStages right join Employees on RequestStages.employee_id = Employees.eid
					   inner join ActionTypes on RequestStages.actiontype_id = ActionTypes.atid
go

create or alter procedure selectView (@name varchar(100)) as
begin
	declare @cmd varchar(250) = 'select * from ' + @name
	exec @cmd
end
go

--tests--

insert into Tests(Name) values ('addEmployeeRoles'), ('deleteEmployeeRoles'),
							   ('addEmployees'), ('deleteEmployees'),
							   ('addActionTypes'), ('deleteActionTypes'),
							   ('addRequestStages'), ('deleteRequestStages'),
							   ('selectView')
go

insert into Tables(Name) values ('EmployeeRoles'), ('Employees'), ('ActionTypes'), ('RequestStages')
go

insert into Views(Name) values ('showEmployeeRoles'), ('showEmployees'), ('showRequestStages')
go

insert into TestViews(TestID, ViewID) values (9, 1), (9, 2), (9, 3)
go

insert into TestTables(TestID, TableID, NoOfRows, Position) values (1, 1, 50, 3), (2, 1, 75, 1),
																 (3, 2, 500, 3), (4, 2, 1000, 2),
																 (5, 3, 5000, 1), (6, 3, 5000, 3)
go

--run tests--

create or alter procedure runDeleteTests as
begin
	declare @testId int

	declare fetchDeleteTests cursor
	for select TestID from TestTables where TestID % 2 = 0 order by Position asc

	open fetchDeleteTests
	fetch fetchDeleteTests into @testId
	while @@FETCH_STATUS = 0
	begin
		declare @cmd varchar(MAX) = (select Name from Tests where TestID = @testId)
		exec @cmd

		fetch fetchDeleteTests into @testId
	end
	close fetchDeleteTests
	deallocate fetchDeleteTests
end
go

create or alter procedure runInsertTests (@runTestId int) as
begin
	declare @testId int
	declare @tableId int
	declare @numOfRows int

	declare fetchInsertTests cursor
	for select TestID, TableID, NoOfRows from TestTables where TestID % 2 = 1 order by Position asc

	open fetchInsertTests
	fetch fetchInsertTests into @testId, @tableId, @numOfRows
	while @@FETCH_STATUS = 0
	begin
		declare @cmd varchar(MAX) = (select Name from Tests where TestID = @testId)
		declare @startTime datetime = GETDATE()

		exec (@cmd + ' ' + @numOfRows)

		declare @endTime datetime = GETDATE()
		insert into TestRunTables(TestRunID, TableID, StartAt, EndAt) values (@runTestId, @tableId, @startTime, @endTime)

		fetch fetchInsertTests into @testId, @tableId, @numOfRows
	end

	close fetchInsertTests
	deallocate fetchInsertTests
end
go

create or alter procedure runViewTests (@runTestId int) as
begin
	declare @testId int
	declare @viewId int

	declare fetchViewTests cursor for
	select * from TestViews

	open fetchViewTests
	fetch fetchViewTests into @testId, @viewId
	while @@FETCH_STATUS = 0
	begin
		declare @cmd varchar(MAX) = (select Name from Tests where TestID = @testId)
		declare @args varchar(MAX) = (select Name from Views where ViewID = @viewId)
		declare @startTime datetime = GETDATE()
		
		exec (@cmd + ' ' + @args)

		declare @endTime datetime = GETDATE()
		insert into TestRunViews(TestRunID, ViewID, StartAt, EndAt) values (@runTestId, @viewId, @startTime, @endTime)

		fetch fetchViewTests into @testId, @viewId
	end

	close fetchViewTests
	deallocate fetchViewTests
end
go

--all execs--

create or alter procedure main as 
begin 
	insert into TestRuns(startAt) values(getdate())
	declare @testId int = SCOPE_IDENTITY()
	exec runDeleteTests
	exec runInsertTests @testId
	exec runViewTests @testId

	update TestRuns set Description = 'delete + insert + view', EndAt = GETDATE() where TestRunID = @testId

	select * from TestRunTables
	select * from TestRunViews
	select * from TestRuns

end
go

create or alter procedure runTests (@n int) as
begin
	declare @i int = 0
	while @i < @n
	begin
		exec main
		set @i = @i + 1
	end

	select * from TestRunTables
	select * from TestRunViews
	select * from TestRuns
end
go

exec runTests 1