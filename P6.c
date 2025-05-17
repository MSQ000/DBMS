create procedure merge_rollcall_data()
begin
    declare n_id int; -- Student ID
    declare n_name varchar(255); -- Student Name
    declare n_birth_date date; -- Birth Date
    declare done int default false; -- Flag to indicate end of cursor
    declare n_cursor cursor for 
    select student_id, student_name, birth_date from N_rollcall; -- Selecting from N_rollcall table
    declare continue handler for not found
    set done=true; -- Set flag when cursor reaches the end

    open n_cursor;
    cursor_loop:Loop
    fetch n_cursor into n_id, n_name, n_birth_date;
    if done then leave cursor_loop; -- Exit loop if cursor is done
    end if;
    if not exists(
    select 1 from O_rollcall where student_id=n_id) then
    insert into O_rollcall(student_id, student_name, birth_date)
    values(n_id, n_name, n_birth_date); -- Insert new record into O_rollcall
    end if;
    end loop;

    close n_cursor;
end//
