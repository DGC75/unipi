module clock(output out);

    reg clock;
    initial
        begin
            clock = 0;
        end
    
    assign out = clock;

    always
        begin
            #1 clock = ~clock;
        end

endmodule