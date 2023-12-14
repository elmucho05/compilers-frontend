extern echo(double);

fun man(input)
    with controllo = input do
        for i = 0, i < input, 1 do 
            controllo = controllo/10 :
            echo(controllo)
        end 
    end
;

