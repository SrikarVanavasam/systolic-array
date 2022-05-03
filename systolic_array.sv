module systolic_array

#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic [DATA_SIZE-1:0] in_data [MATRIX_SIZE-1:0],
    input logic [DATA_SIZE-1:0] in_weights [MATRIX_SIZE-1:0],
    input logic load_weight,            // from scheduler
    input logic enable,                 // from scheduler
    input logic reset, clk,
    output logic [DATA_SIZE-1:0] out_sum [MATRIX_SIZE-1:0]
);

// internal wires
logic [DATA_SIZE-1:0] row_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];
logic [DATA_SIZE-1:0] col_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];
// logic ld_weight_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];           // horizontal passthrough
// logic PE_enable_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];           // horizontal passthrough

logic ld_weight [MATRIX_SIZE-1:0];
logic PE_enable [MATRIX_SIZE-1:0];

// genvar h;
// generate
//     for (h = 0; h < MATRIX_SIZE; h++)
//     begin
//         assign ld_weight[h] = load_weight[h];
//         assign PE_enable[h] = enable_mult[h];
//     end
// endgenerate

genvar i, j;    //i: row index; j: col index
generate
    // PE_1: non-input PEs
    for (i = 1; i < MATRIX_SIZE; i++)       // excluding first row
    begin
        for (j = 1; j < MATRIX_SIZE; j++)       // excluding first col
        begin
            localparam PE_index = MATRIX_SIZE * i + j;
            // horizontal wires
            localparam in_data_wire_index = PE_index - 1;
            localparam out_data_wire_index = PE_index;
            // ld_weight_in wire at the same location as the in_data wire
            // ld_weight_out wire at the same location as the out_data wire
            // vertical wires
            localparam in_sum_wire_index = PE_index - MATRIX_SIZE;
            localparam out_sum_wire_index = PE_index;
            systolic_pe #   (   .DATA_SIZE(DATA_SIZE)) pe_1 
                            (   .in_data(row_wire[in_data_wire_index]), 
                                .in_sum(col_wire[in_sum_wire_index]), 
                                .out_data(row_wire[out_data_wire_index]), 
                                .out_sum(col_wire[out_sum_wire_index]), 
                                .reset(reset), 
                                .clk(clk), 
                                // .ld_weight_in(ld_weight_wire[in_data_wire_index]),
                                // .ld_weight_out(ld_weight_wire[out_data_wire_index]),
                                // .enable_in(PE_enable_wire[in_data_wire_index]),
                                // .enable_out(PE_enable_wire[out_data_wire_index]),
                                .enable(enable),
                                .ld_weight(load_weight));
        end
    end

    // PE_2:
    //  i = 0;      // only the first row
    for (j = 1; j < MATRIX_SIZE; j++)       // excluding the first col
    begin
        localparam PE_index = j;
        // horizontal wires
        localparam in_data_wire_index = PE_index - 1;
        localparam out_data_wire_index = PE_index;
        // ld_weight_in wire at the same location as the in_data wire
        // ld_weight_out wire at the same location as the out_data wire
        // vertical wires
        localparam out_sum_wire_index = PE_index;
        systolic_pe #   (   .DATA_SIZE(DATA_SIZE)) pe_2 
                        (   .in_data(row_wire[in_data_wire_index]), 
                            .in_sum(in_weights[j]), 
                            .out_data(row_wire[out_data_wire_index]), 
                            .out_sum(col_wire[out_sum_wire_index]), 
                            .reset(reset), 
                            .clk(clk), 
                            // .ld_weight_in(ld_weight_wire[in_data_wire_index]),
                            // .ld_weight_out(ld_weight_wire[out_data_wire_index]),
                            // .enable_in(PE_enable_wire[in_data_wire_index]),
                            // .enable_out(PE_enable_wire[out_data_wire_index]),
                            .enable(enable),
                            .ld_weight(load_weight));
    end

    // PE_3:
    //  j = 0;      // only the first col
    for (i = 1; i < MATRIX_SIZE; i++)       // excluding the first row
    begin
        localparam PE_index = MATRIX_SIZE * i;
        // horizontal wires
        localparam out_data_wire_index = PE_index;
        // ld_weight_out wire at the same location as the out_data wire
        // vertical wires
        localparam in_sum_wire_index = PE_index - MATRIX_SIZE;
        localparam out_sum_wire_index = PE_index;
        systolic_pe #   (   .DATA_SIZE(DATA_SIZE)) pe_3 
                        (   .in_data(in_data[i]), 
                            .in_sum(col_wire[in_sum_wire_index]), 
                            .out_data(row_wire[out_data_wire_index]), 
                            .out_sum(col_wire[out_sum_wire_index]), 
                            .reset(reset), 
                            .clk(clk), 
                            // .ld_weight_in(ld_weight[i]),
                            // .ld_weight_out(ld_weight_wire[out_data_wire_index]),
                            // .enable_in(PE_enable[i]),
                            // .enable_out(PE_enable_wire[out_data_wire_index]),       
                            .enable(enable),
                            .ld_weight(load_weight));
    end

    // PE_4:
    systolic_pe #   (   .DATA_SIZE(DATA_SIZE)) pe_4
                    (   .in_data(in_data[0]), 
                        .in_sum(in_weights[0]), 
                        .out_data(row_wire[0]), 
                        .out_sum(col_wire[0]), 
                        .reset(reset), 
                        .clk(clk), 
                        // .ld_weight_in(ld_weight[0]),
                        // .ld_weight_out(ld_weight_wire[0]),
                        // .enable_in(PE_enable[0]),
                        // .enable_out(PE_enable_wire[0]),
                        .enable(enable),
                        .ld_weight(load_weight));
    
    // Map column wires to output
    for (j = 0; j < MATRIX_SIZE; j++)
    begin
        // Map column wires to output
        assign out_sum[j] = col_wire[MATRIX_SIZE * (MATRIX_SIZE - 1) + j];
    end
endgenerate
endmodule