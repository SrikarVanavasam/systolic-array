module systolic_pe
#(parameter DATA_SIZE = 32)
(
 input logic [DATA_SIZE-1:0] in_data,
 input logic [DATA_SIZE-1:0] in_sum, // aslo used to load the weights
 input logic clk, reset, enable, ld_weight,
 output reg [DATA_SIZE-1:0] out_data,
 output reg [DATA_SIZE-1:0] out_sum);

reg [DATA_SIZE-1:0] weight;
wire[DATA_SIZE-1:0] madd_out;
wire[DATA_SIZE-1:0] shift_out;
madd #(.DATA_SIZE(DATA_SIZE), .MULTIPLY_CYCLES(3)) madd_unit (.clk(clk), .enable(enable), .reset(reset), .dataa(in_data), .datab(weight), .datac(in_sum), .result(madd_out));
VX_shift_register #(.DATAW(DATA_SIZE), .RESETW(0), .DEPTH(4), .NTAPS(1))
				shift_reg (.clk(clk), .reset(reset), .enable(enable), .data_in(in_data), .data_out(shift_out));
always_ff @(posedge clk)
	begin
		if(reset)
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
endmodule