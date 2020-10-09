primitive mux2x1(output z, input c, input x1, input x2);
    table
        0 0 ? : 0;
        0 1 ? : 1;
        1 ? 0 : 0;
        1 ? 1 : 1:;
    endtable
endprimitive