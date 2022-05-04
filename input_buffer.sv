module data_fetcher
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic reset, clk, enable,
    output logic [DATA_SIZE-1:0] data_w_interval_out [MATRIX_SIZE-1:0]
);

reg [DATA_SIZE-1:0] data_w_interval [MATRIX_SIZE-1:0];
reg [DATA_SIZE-1:0] dmem [15:0];
reg [31:0] counter;

always @ (posedge clk or negedge reset) begin
    if (reset || !enable) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= 32'b0;
        end
        counter <= 0;

        dmem[0] <= 1;
        dmem[1] <= 3;
        dmem[2] <= 1;
        dmem[3] <= 3;
        dmem[4] <= 1;
        dmem[5] <= 3;
        dmem[6] <= 1;
        dmem[7] <= 3;
        dmem[8] <= 2;
        dmem[9] <= 4;
        dmem[10] <= 2;
        dmem[11] <= 4;
        dmem[12] <= 2;
        dmem[13] <= 4;
        dmem[14] <= 2;
        dmem[15] <= 4;
    end
    else begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= dmem[i + counter];
        end
        counter <= counter + 2;
    end

    if (counter > 14) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= 32'b0;
        end
    end

    assign data_w_interval_out = data_w_interval;
end
endmodule