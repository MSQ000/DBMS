delimiter //

create procedure fetch_employee_data()
begin
declare emp_id int;
declare emp_name varchar(255);
declare emp_age int;
declare emp_salary decimal(10, 2);

declare emp_cursor cursor for
select e_id, e_name, age, salary from employee;

declare continue handler for not found set @finished = 1;

open emp_cursor;

set @finished = 0;

cursor_loop: loop
fetch emp_cursor into emp_id, emp_name, emp_age, emp_salary;

if @finished = 1 then
leave cursor_loop;
end if;

select concat('Employee ID: ', emp_id, ', Name: ', emp_name, ', Age: ', emp_age, ', Salary: ', emp_salary) as employee_info;
end loop;

close emp_cursor;
end//