module data_fetcher
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic reset, clk, enable,
    output logic [DATA_SIZE-1:0] data_w_interval_out [MATRIX_SIZE-1:0]
);

reg [DATA_SIZE-1:0] data_w_interval [MATRIX_SIZE-1:0];

reg [DATA_SIZE-1:0] dmem [MATRIX_SIZE * MATRIX_SIZE-1:0];

reg [1:0] counter;
reg [31:0] pointer;

initial begin
      $readmemh(`IDMEMINITFILE , dmem);
      counter <= 0;
      pointer <= MATRIX_SIZE - 1;
end

always @ (posedge clk or posedge reset) begin
    if (reset or !enable) begin
        data_w_interval [MATRIX_SIZE-1:0] <= 0;
        counter <= 0;
        pointer <= MATRIX_SIZE - 1;
    end
    else begin
        counter <= counter + 1;
    end
end 

always @ (counter) begin
    if (counter == 2'b11) begin
        data_w_interval [MATRIX_SIZE-1:0] <= dmem [pointer:pointer-MATRIX_SIZE];
        pointer <= pointer + MATRIX_SIZE;   // should we use blocking statement for updating the pointer value?
    end
    else begin
        data_w_interval [MATRIX_SIZE-1:0] <= 0;
    end
end

assign data_w_interval_out = data_w_interval;

endmodule