module D(output q, output nq, input clock, input d);

    wire r, s;

    assign
        r = clock & (~d);

    assign
        s = clock & d;
    
    SR sr(q, nq, s, r);

endmodule