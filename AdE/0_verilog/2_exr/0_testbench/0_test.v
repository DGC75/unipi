
/*IL MODULO DI TEST E' UN MODULO SENZA PARAMETRI*/

    /*DICHIARAZIONI WIRE PER OGNI OUTPUT*/
 
    /*DICHIARAZIONI REG PER OGNI INPUT*/
    //NESSUN INPUT PER IL CLOCK

    /*ISTANZIAZIONE DEL COMPONENTE*/



    /*PROGRAMMA DI PROVA: ASSEGNA VALORI DIVERSI AGLI INPUT*/
    /*VALORI DIVERSI IN TEMPI DIVERSI*/

/*FINE SCHEMA*/

module test();

wire out;

clock t_clock(out);

initial
    begin
        $monitor("%t %d", $time, out);

        #30
        $finish;
    end

endmodule