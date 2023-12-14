extern echo(double);

fun man(input)
    with eta = 2023-input do
        if !(eta < 18) then
            echo(input*10)
        else
            echo(-input)
        end
    end
;