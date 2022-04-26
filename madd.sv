module madd #(
    parameter DATA_SIZE = 32, MULTIPLY_CYCLES = 3
) (
    input wire clk,    
    input wire enable,
    input wire reset,
    input wire [DATA_SIZE-1:0]  dataa,
    input wire [DATA_SIZE-1:0]  datab,
    input wire [DATA_SIZE-1:0]  datac,
    output wire [DATA_SIZE-1:0] result
);
    wire[DATA_SIZE-1:0] mult_out, add_out;
    VX_multiplier #(.WIDTHA(DATA_SIZE), 
                    .WIDTHB(DATA_SIZE), 
                    .WIDTHP(DATA_SIZE), 
                    .SIGNED(1), 
                    .LATENCY(MULTIPLY_CYCLES)) 
                    multiplier (.clk(clk), .enable(enable), .dataa(dataa), .datab(datab), .result(mult_out));
    VX_shift_register #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(MULTIPLY_CYCLES), .NTAPS(1))
                    shift_reg (.clk(clk), .reset(reset), .enable(enable), .data_in(datac), .data_out(add_out));

    assign result = mult_out + add_out;
endmodule