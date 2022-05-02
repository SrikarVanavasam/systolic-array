module systolic_array_frame

#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic [DATA_SIZE-1:0] data_input [MATRIX_SIZE-1:0],
    input logic [DATA_SIZE-1:0] weights_input [MATRIX_SIZE-1:0],
    input logic clk, reset, enable,
    output logic [DATA_SIZE-1:0] result_out [MATRIX_SIZE-1:0],
    output logic done
);

input_skewer #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))   
my_input_skewer (
    .reset(reset),
    .clk(clk),
    .enable(enable),
    .data(data_input),
    .data_skewed(data_skewed_out)
);

scheduler #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_SIZE(DATA_SIZE))
my_scheduler (
    .reset(reset),
    .clk(clk),
    .general_enable(enable),
    .load_weight(load_weight),
    .enable_mult(enable_mult)
)


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




end module