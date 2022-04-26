module matrix_multiply
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)
(input logic [DATA_SIZE-1:0] in_data [MATRIX_SIZE-1:0],
 input logic [DATA_SIZE-1:0] in_weights [MATRIX_SIZE-1:0],
 input logic reset, clk, ld_weight,
 output logic [DATA_SIZE-1:0] out_sum [MATRIX_SIZE-1:0]);

	logic [DATA_SIZE-1:0] row_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];
	logic [DATA_SIZE-1:0] col_wire [MATRIX_SIZE*MATRIX_SIZE-1:0];

	// add all the blocks which are not connected directly to the inputs
	genvar i, j;
	generate
		// iterate over rows
		for(i = 1; i<MATRIX_SIZE; i++)
		begin
			//iterate over columns
			for(j=1; j<MATRIX_SIZE; j++)
			begin
				// logic of wiring connection => use MATRIX_SIZE*i to get first mu's wiring and add column no. incrementally
				localparam in_wire_count = MATRIX_SIZE*i+j;
				// similarly the out wire will be in the next row so use i+1
				localparam out_wire_count = MATRIX_SIZE*(i+1)+j;
				systolic_pe #(.data_size(DATA_SIZE)) pe (.in_data(row_wire[in_wire_count]), .in_sum(col_wire[in_wire_count - MATRIX_SIZE]), .out_data(row_wire[in_wire_count+1]), .out_sum(col_wire[out_wire_count - MATRIX_SIZE]), .reset(reset), .clk(clk), .ld_weight(ld_weight));
			end
		end

		// now generate 1st row of each col except top right block
		for(i=1; i<MATRIX_SIZE; i++)
			begin
				systolic_pe #(.data_size(DATA_SIZE)) mu_row (.in_data(row_wire[i]), .in_sum(in_weights[i]), .out_data(row_wire[i+1]), .out_sum(col_wire[i]),  .reset(reset), .clk(clk), .ld_weight(ld_weight));
			end
		// now generate 1st col of each row except top right block
		for(j=1; j<MATRIX_SIZE; j++)
			begin
				localparam in_wire_count = MATRIX_SIZE*(j - 1);
				systolic_pe #(.data_size(DATA_SIZE)) mu_col (.in_data(in_data[j]), .in_sum(col_wire[in_wire_count]), .out_data(row_wire[in_wire_count+MATRIX_SIZE+1]), .out_sum(col_wire[in_wire_count+MATRIX_SIZE]),  .reset(reset), .clk(clk), .ld_weight(ld_weight));
			end
        for(i=0; i<MATRIX_SIZE; i++)
            begin
                // Map column wires to output
                assign out_sum[i] = col_wire[MATRIX_SIZE * (MATRIX_SIZE - 1) + i];
            end
        // now add the top left block
		systolic_pe #(.data_size(DATA_SIZE)) mu_top (.in_data(in_data[0]), .in_sum(in_weights[0]), .out_data(row_wire[1]), .out_sum(col_wire[0]),  .reset(reset), .clk(clk), .ld_weight(ld_weight));
	endgenerate

endmodule