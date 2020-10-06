module add2(output riporto, output [1:0]somma, input ripin, input [1:0]x1, input [1:0]x2);
    
    wire rip_to_rip;

    fulladder fa0(rip_to_rip, somma[0], ripin, x1[0], x2[0]);
    fulladder fa1(riporto, somma[1], rip_to_rip, x1[1], x2[1]);

endmodule