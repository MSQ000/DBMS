create procedure merge_rollcall_data()
begin
    declare n_id int;
    declare n_name varchar(255);
    declare n_birth_date date;
    declare done int default false;
    declare n_cursor cursor for 
    select student_id, student_name, birth_date from N_rollcall;
    declare continue handler for not found
    set done=true;

    open n_cursor;

    cursor_loop:Loop
    fetch n_cursor into n_id, n_name, n_birth_date;

    if done then leave cursor_loop;
    end if;
    if not exists(
    select 1 from O_rollcall where student_id=n_id) then
    insert into O_rollcall(student_id, student_name, birth_date)
    values(n_id, n_name, n_birth_date);
    end if;
    end loop;

    close n_cursor;
end//