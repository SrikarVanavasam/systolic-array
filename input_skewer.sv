module input_skewer
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic [DATA_SIZE-1:0] data [MATRIX_SIZE-1:0],
    input logic reset, clk, enable_in,
    output logic [DATA_SIZE-1:0] data_skewed [MATRIX_SIZE-1:0]
);

// assign data_skewed[0] = data[0];    // first row does not need delay
// assign data_skewed[1] = one_cycle_shift;

// reg [DATA_SIZE-1:0] one_cycle_shift; 

// // always @(posedge reset) begin
// //     assign data_skewed = 0;
// // end

// always @(posedge clk) begin
//     one_cycle_shift = data[1];
// end

// always @(posedge reset) begin
//     one_cycle_shift = 0;
// end

genvar i;
generate
    for (i = 0; i < MATRIX_SIZE; i++)
    begin
        // shift registers will delay i cycles for ith row of input
<<<<<<< Updated upstream
        VX_shift_register   #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(i + MATRIX_SIZE), .NTAPS(1))
=======
        VX_shift_register   #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(4*i + MATRIX_SIZE), .NTAPS(1))
>>>>>>> Stashed changes
				            shift_reg (.clk(clk), .reset(reset), .enable(enable_in), .data_in(data[i]), .data_out(data_skewed[i]));
    end
endgenerate

endmodule