procedure Main is
begin
    x := true;
    y := true;
    z := false;
    a := 10.5;
    if (x and y) or z then
        a := a + 2.5 / 2.5;
    else
        a := 10.5 + 0.5; 
    end if;
    x := not x;
end Main;