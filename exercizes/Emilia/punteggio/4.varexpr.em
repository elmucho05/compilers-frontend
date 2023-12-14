extern echo(double);

fun man(input) 
    echo(input): 
    with a=input do        // a = input
        input = input-1:   // input -= 1
        echo(input):       // input è cambiata
        echo(a)            // a non è cambiata
    end
;

