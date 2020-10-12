module a(output out, input in, input clk);
    
    wire r2s;
    wire s2r;


    r #(1) rgst(r2s, s2r, clk, clk);
    s state(s2r, r2s, in);

    assign
        out = s2r;

endmodule