extern echo(double);

fun man(n)
    with f1, f2 = 1, next do
        if (n < 1) then
            echo(0)
        else
            echo(f1):
            for i = 1, i < n do
                echo(f2):
                next = f1 + f2:
                f1 = f2:
                f2 = next
            end
        end
    end
;