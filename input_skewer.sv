module input_skewer
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic [DATA_SIZE-1:0] data [MATRIX_SIZE-1:0],
    input logic reset, clk, enable_in,
    output logic [DATA_SIZE-1:0] data_skewed [MATRIX_SIZE-1:0]
);

assign data_skewed[0] = data[0];    // first row does not need delay

genvar i;
generate
    for (i = 1; i < MATRIX_SIZE; i++)
    begin
        // shift registers will delay i cycles for ith row of input
        VX_shift_register   #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(i), .NTAPS(1))
				            shift_reg (.clk(clk), .reset(reset), .enable(enable_in), .data_in(data[i]), .data_out(data_skewed[i]));
    end
endgenerate

endmodule