module()
    reg [15:0] x1;
    reg [15:0] x2;
    reg ctrl;

    wire [15:0] z;

    mux #(16) mux16(z, ctrl, x1, x2);
endmodule

//SINTASSI SCORRETTISSIMA, MA NON HO VOGLIA DI CORREGGERLA ORA :)