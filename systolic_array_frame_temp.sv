module systolic_array_frame

#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    // input logic valid_in, 
    // input logic [DATA_SIZE-1:0] data_input [MATRIX_SIZE-1:0],
    // input logic [DATA_SIZE-1:0] weights_input [MATRIX_SIZE-1:0],
    input logic clk, reset, enable,
    output logic [DATA_SIZE-1:0] result_out [MATRIX_SIZE-1:0],
    output logic results_ready, 
    output wire module_busy,
    output wire module_ready,   // the module is ready to perform the operation

    // hanshake signals
    input wire valid_in,        // input is ready from the other party
    input wire ready_out,       // output target is ready to store the result
    output wire ready_in,       // ready to take in new data
    output wire valid_out       // the results are valid and ready to be read
);

wire [DATA_SIZE-1:0] data_skewed_out [MATRIX_SIZE-1:0];
wire [MATRIX_SIZE-1:0] enable_grid;
wire [DATA_SIZE-1:0] data_input [MATRIX_SIZE-1:0];
wire [DATA_SIZE-1:0] weights_input [MATRIX_SIZE-1:0];
wire load_weight;
wire done_load;
wire enable_schdeuler;
reg module_ready_reg;


// handshake implementation
// process the input
assign enable_schdeuler = enable && valid_in;    // if input data is ready, operate

always @(ready_out) begin
    assign ready_in = (!module_busy) && ready_out;
    assign valid_out = results_ready && (!ready_out);
end

// process the output
always @ (reset) begin
    module_ready_reg = 1;
end
assign module_ready = module_ready_reg;

weight_buffer #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
my_weight_buffer (
    .reset(reset),
    .clk(clk),
    .enable(enable),
    .data_out(weights_input)
);


data_fetcher #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
my_data_fetcher (
    .reset(reset),
    .clk(clk),
    .enable(enable),
    .data_w_interval_out(data_input)
);


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
    .module_busy_out(module_busy),
    .done(results_ready)
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