module systolic_pe
#(parameter DATA_SIZE = 32)
(
 input wire [DATA_SIZE-1:0] in_data,
 input wire [DATA_SIZE-1:0] in_sum, // also used to load the weights
 input wire clk, reset, enable, ld_weight,
 // output logic enable_out, ld_weight_out,
 output reg [DATA_SIZE-1:0] out_data,
 output reg [DATA_SIZE-1:0] out_sum);

reg [DATA_SIZE-1:0] weight;
wire[DATA_SIZE-1:0] madd_out;
wire[DATA_SIZE-1:0] shift_out;
wire [DATA_SIZE-1:0] add;
assign add = ld_weight ? 0 : in_sum;
madd #(.DATA_SIZE(DATA_SIZE), .MULTIPLY_CYCLES(3)) madd_unit (.clk(clk), .enable(enable), .reset(reset), .dataa(in_data), .datab(weight), .datac(add), .result(madd_out));
VX_shift_register #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(3), .NTAPS(1))
				shift_reg (.clk(clk), .reset(reset), .enable(enable), .data_in(in_data), .data_out(shift_out));
always_ff @(posedge clk)
	begin
		if(reset || !enable)
			begin
				out_data <= 0;
				out_sum <= 0;
			end
		else if(ld_weight) 
			begin 
				weight <= in_sum;
				out_sum <= in_sum;
			end 	
		else
			begin
				out_data <= shift_out;
				out_sum <= madd_out;
			end
	end

// // load_weight signal passthrough (horizontal row-wise)
// assign ld_weight_out = ld_weight_in;

// // enable signal passthrough (horizontal row-wise)
// assign enable_out = enable_in;

endmodule