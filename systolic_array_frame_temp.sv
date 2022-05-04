module systolic_array_frame

#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    // input logic valid_in, 
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
wire load_weight;
wire [MATRIX_SIZE-1:0] enable_grid;
// wire [DATA_SIZE-1:0] data_input [MATRIX_SIZE-1:0];
wire done_load;
wire enable_schdeuler;
// wire reset_delayed;
// wire enable_delayed;
reg module_ready_reg;


// handshake implementation
// process the input
assign enable_schdeuler = enable && input_ready && output_ready;    // if input data is ready and 
                                                                    // output storage is avaliable, operate

// // shift register for reset
// reg r_bit0;
// reg r_bit1;
// reg r_bit2;
// reg r_bit3;

// assign reset_delayed = r_bit3;

// always @(posedge clk) begin
//   r_bit3 <= r_bit2;
//   r_bit2 <= r_bit1;
//   r_bit1 <= r_bit0;
//   r_bit0 <= reset;
// end

// // shift register for enable
// reg e_bit0;
// reg e_bit1;
// reg e_bit2;
// reg e_bit3;

// assign enable_delayed = e_bit3;

// always @(posedge clk) begin
//   e_bit3 <= e_bit2;
//   e_bit2 <= e_bit1;
//   e_bit1 <= e_bit0;
//   e_bit0 <= enable;
// end

// process the output
always @ (reset) begin
    module_ready_reg = 1;
end
assign module_ready = module_ready_reg;

// data_fetcher #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
// my_data_fetcher (
//     .reset(reset),
//     .clk(clk),
//     .enable(enable),
//     .data_w_interval_out(data_input)
// );


input_skewer #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
my_input_skewer (
    .reset(reset),
    .clk(clk),
    .enable_in(enable_schdeuler),  // once loading is finished, start skewing the input
    .data(data_input),
    .data_skewed(data_skewed_out)
);

scheduler #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))
my_scheduler (
    .reset(reset),
    .clk(clk),
    .general_enable(enable_schdeuler),
    .load_weight(load_weight),
    .enable_mult(enable_grid),
    //.done_load_wire(done_load),
    .done(finished)
);

systolic_array #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))
my_systolic_array (
    .reset(reset),
    .clk(clk),
    .in_data(data_skewed_out),
    .in_weights(weights_input),
    .load_weight(load_weight),
    .enable(enable_schdeuler),
    .out_sum(result_out)
);




endmodule