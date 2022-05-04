module weight_buffer
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic reset, clk, enable,
    output logic [DATA_SIZE-1:0] data_out [MATRIX_SIZE-1:0]
);

reg [DATA_SIZE-1:0] data [MATRIX_SIZE-1:0];
reg [DATA_SIZE-1:0] dmem [15:0];
reg [31:0] counter;

always @ (posedge clk or posedge reset) begin
    if (reset || !enable) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data[i] <= 32'b0;
        end
        counter <= 0;

        dmem[0] <= 2;
        dmem[1] <= 4;
        dmem[2] <= 1;
        dmem[3] <= 3;
    end
    else begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data[i] <= dmem[i + counter];
        end
        counter <= counter + 2;
    end

    if (counter > 2) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data[i] <= 32'b0;
        end
    end
end

reg [DATA_SIZE-1:0] bit0 [MATRIX_SIZE-1:0];
reg [DATA_SIZE-1:0] bit1 [MATRIX_SIZE-1:0];
reg [DATA_SIZE-1:0] bit2 [MATRIX_SIZE-1:0];
wire [DATA_SIZE-1:0] data_delayed [MATRIX_SIZE-1:0];

always @(posedge clk) begin
    bit2 <= bit1;
    bit1 <= bit0;
    bit0 <= data;
end

assign data_delayed = bit2;
assign data_out = data_delayed;


endmodule