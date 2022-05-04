module data_fetcher
#(parameter MATRIX_SIZE = 2, DATA_SIZE = 32)

(
    input logic reset, clk, enable,
    output logic [DATA_SIZE-1:0] data_w_interval_out [MATRIX_SIZE-1:0]
);

reg [DATA_SIZE-1:0] data_w_interval [MATRIX_SIZE-1:0];

reg [DATA_SIZE-1:0] dmem [MATRIX_SIZE * MATRIX_SIZE-1:0];
wire [DATA_SIZE-1:0] dmem_out [MATRIX_SIZE * MATRIX_SIZE-1:0];

reg [1:0] counter;
reg [31:0] pointer;


always @ (posedge clk or posedge reset) begin
    if (reset || !enable) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            assign data_w_interval[i] = 32'b0;
        end
        counter <= 0;
        pointer <= 0;

        for (int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++) begin
            dmem[i] <= i + 1;
        end

        // dmem [0] <= 1;
        // dmem [1] <= 2;
        // dmem [2] <= 3;
        // dmem [3] <= 4;
    end
    else if (pointer > MATRIX_SIZE*MATRIX_SIZE - MATRIX_SIZE) begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= 32'b0;
        end
        counter <= 0;
        pointer <= MATRIX_SIZE*MATRIX_SIZE;
    end
    else begin
        counter <= counter + 1;
    end

    if (counter == 3) begin
        // data_w_interval [MATRIX_SIZE-1:0] <= dmem_out [pointer +: MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= dmem[pointer + i];
        end
        pointer <= pointer + MATRIX_SIZE;   // should we use blocking statement for updating the pointer value?
    end
    else begin
        for (int i = 0; i < MATRIX_SIZE; i++) begin
            data_w_interval[i] <= 32'b0;
        end
    end


end 

// always @ (posedge clk) begin
//     if (counter == 2'b11) begin
//         // data_w_interval [MATRIX_SIZE-1:0] <= dmem_out [pointer +: MATRIX_SIZE];
//         for (int i = 0; i < MATRIX_SIZE; i++) begin
//             data_w_interval [i] <= dmem [pointer + i];
//         end
//         pointer <= pointer + MATRIX_SIZE;   // should we use blocking statement for updating the pointer value?
//     end
//     else begin
//         for (int i = 0; i < MATRIX_SIZE; i++) begin
//             data_w_interval [i] <= 32'b0;
//         end
//     end
// end

assign data_w_interval_out = data_w_interval;

endmodule