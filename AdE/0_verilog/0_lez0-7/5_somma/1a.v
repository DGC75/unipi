module somma(output z, output rout, input rin, input x, input y);

    assign
        z = (~rin & ~x & y) |
            (~rin & x & ~y) |
            (rin & ~x & ~y) |
            (rin & ~x & ~y);

    assign 
        rout = (rin == 0 ? (x&y) : (x|y));



endmodule