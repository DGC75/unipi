module fulladder(output riporto, output somma, input rpin, input x1, input x2);

    fadd_rip m1(riporto, rpin, x1, x2);
    fadd_somma m2(somma, rpin, x1, x2);

endmodule //fulladder