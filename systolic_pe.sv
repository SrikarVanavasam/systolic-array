module systolic_pe
#(parameter data_size = 32)
(input logic [data_size-1:0] in_data,
 input logic [data_size-1:0] in_sum, // aslo used to load the weights
 input logic clk, reset, ld_weight,
 output reg [data_size-1:0] out_data,
 output reg [data_size-1:0] out_sum);

reg [data_size-1:0] weight;

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
				out_data <= in_data;
				out_sum <= (in_data*weight) + in_sum;
			end
	end
endmodule