delimiter //
create procedure fetch_employee_data()
begin
-- declare variables to store cursor values
declare emp_id int;
declare emp_name varchar(255);
declare emp_age int;
declare emp_salary decimal(10, 2);

-- declare a cursor for the employee table
declare emp_cursor cursor for
select e_id, e_name, age, salary from employee;

-- declare a continue handler for the cursor
declare continue handler for not found set @finished = 1;

-- open the cursor
open emp_cursor;

-- initialize a variable to control cursor loop
set @finished = 0;

-- loop through the cursor results
cursor_loop: loop
-- fetch the next row from the cursor into variables
fetch emp_cursor into emp_id, emp_name, emp_age, emp_salary;

-- check if no more rows to fetch
if @finished = 1 then
leave cursor_loop;
end if;

-- output or process each row (for demonstration, print the values)
select concat('Employee ID: ', emp_id, ', Name: ', emp_name, ', Age: ', emp_age, ', Salary: ', emp_salary) as employee_info;
end loop;

-- close the cursor
close emp_cursor;
end//