module systolic_array_frame

#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic valid_in, 
    input logic [DATA_SIZE-1:0] data_input [MATRIX_SIZE-1:0],
    input logic [DATA_SIZE-1:0] weights_input [MATRIX_SIZE-1:0],
    input logic clk, reset, enable,
    output logic [DATA_SIZE-1:0] result_out [MATRIX_SIZE-1:0],
    output logic finished, 

    // hanshake signals
    input wire input_ready,    // input is ready from the other party
    input wire output_ready,   // output taret is ready to store the result
    // output wire result_ready,   // the module has done its operation (same as finished!!!)
    output wire module_ready    // the module is ready to perform the operation
);

wire [DATA_SIZE-1:0] data_skewed_out [MATRIX_SIZE-1:0];
wire [MATRIX_SIZE-1:0] load_weight;
wire [MATRIX_SIZE-1:0] enable_mult;
wire done_load;
wire enable_schdeuler;

// handshake implementation
assign enable_schdeuler = enable & input_ready;

input_skewer #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
my_input_skewer (
    .reset(reset),
    .clk(clk),
    .enable_in(done_load),  // once loading is finished, start skewing the input
    .data(data_input),
    .data_skewed(data_skewed_out)
);

scheduler #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))
my_scheduler (
    .reset(reset),
    .clk(clk),
    .general_enable(enable_schdeuler),
    .load_weight(load_weight),
    .enable_mult(enable_mult),
    .done_load_wire(done_load),
    .done(finished)
);


systolic_array #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))
my_systolic_array (
    .reset(reset),
    .clk(clk),
    .in_data(data_skewed_out),
    .in_weights(weights_input),
    .load_weight(load_weight),
    .enable_mult(enable_mult),
    .out_sum(result_out)
);




endmodule