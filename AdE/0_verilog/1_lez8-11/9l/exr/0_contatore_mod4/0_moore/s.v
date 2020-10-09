module s(output [1:0]out, input [1:0]state, input in);
    assign 
        out[1] = (~(state[1])&&state[0]&&in) || (state[1]&&(~state[0])) || (state[1]&&(~in));

    assign
        out[0] = ((~state[0])&&in) || ((~in)&&state[0]);

endmodule