//CONTATORE MOD4 DA 1bit
//PER OGNI VOLTA CHE VEDO UN 1, RESTITUIRE (cont++)%4
//IMPLEMENTAZIONE DI MEALY


module cntMod4(output [1:0]out, input in, input clk);
    
    wire [1:0]r2s; 
    wire [1:0]s2r;

    //COMPONENTI
    r #(2) rg(r2s, s2r, clk, clk);
    s state(s2r, r2s, in);
    z z_mod(out, r2s, in);

endmodule
    
