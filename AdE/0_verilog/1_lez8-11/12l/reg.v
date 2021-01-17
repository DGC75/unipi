module registro ( output [N -1:0] z , input [N -1:0] x , input en , input clk ) ;
    parameter N = 8;
    
    reg [N-1:0] s;

    initial
        s = 0;
    
    always @(posedge clk)
        begin
            if(en == 1)
                s = x; 
        end

    assign z = s;


endmodule