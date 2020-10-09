module s(output [1:0]out, input [1:0]s, input in);

    wire dummy_r;
    wire dr2;
    wire [1:0] ext_in;
    
    assign
        ext_in[1] = 0;
    assign
        ext_in[0] = in;
    
    add2 add(dummy_r, out, dr2, s, ext_in);

    
endmodule