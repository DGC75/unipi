module z(output [1:0]out, input [1:0]s);
    
    wire dummy_r;
    wire dr2;
    wire [1:0] ext_in;
    
    assign
        out[1] = in[1];
    assign
        out[0] = in[0];

endmodule