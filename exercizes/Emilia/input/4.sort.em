extern echo(double);
extern gett(double);

fun man(input)
    with a = input, b = 2 do
        echo(a):
        echo(b):
        if (a > b) then
            a = a + b:
            b = a - b:
            a = a - b
        else
            a = a
        end:
        echo(a):
        echo(b)
    end
;