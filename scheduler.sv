module scheduler #(
    parameter MATRIX_SIZE = 2, 
    parameter DATA_SIZE = 32
) (
    input wire clk, reset, general_enable, 
    output wire [MATRIX_SIZE-1:0] load_weight,     // each bit controls one row
    // output wire [MATRIX_SIZE-1:0] enable_mult,     // each bit controls one row
    // output wire done_load_wire,
    output wire done
);
    
    // internal signals
    reg[MATRIX_SIZE:0] load_counter;
    reg[MATRIX_SIZE+2 : 0] mult_counter;
    reg done_load;      // internal signal that indicates loading is finished
    reg done_next;
    
    // signals for pipelining
    reg[MATRIX_SIZE-1:0] load_weight_next;
    reg[MATRIX_SIZE-1:0] enable_mult_next;
    reg [MATRIX_SIZE-1:0] load_weight_reg;     // each bit controls one row
    reg [MATRIX_SIZE-1:0] enable_mult_reg;     // each bit controls one row
    reg done_reg;

    // initialize signals
    // initial begin
    //     load_weight_next = {MATRIX_SIZE{1'b0}};
    //     enable_mult_next = {MATRIX_SIZE{1'b0}};
    //     load_counter = 0;
    //     mult_counter = 0;
    //     done_load = 0;
    //     done_next = 0;
    // end

    always @ (posedge clk) begin
        if (load_counter < MATRIX_SIZE)
        begin
            if (load_counter < MATRIX_SIZE-1)
            begin
                load_weight_next = {MATRIX_SIZE{1'b1}};
                load_counter += 1;
            end
            else 
            begin   
                //load_weight_next = {0, (MATRIX_SIZE-1){1'b1}}
                load_weight_next = {MATRIX_SIZE{1'b1}};
                done_load = 1;
                //enable_mult = {1'b1, MATRIX_SIZE{1'b0}};    // once the last row is loaded, start multplying
            end
        end
    end

    always @ (posedge clk) begin
        if (done_next == 0 && done_load == 1) begin
            if (mult_counter[1:0] == 2'b00) begin        // every 4 cycles, enable another row of PE
                enable_mult_next = {1'b1, {MATRIX_SIZE-1{1'b0}}} | (enable_mult>>1);     // adding a 1 to the MSB
                mult_counter += 1;
            end
            else 
            begin
                mult_counter += 1;
            end
            
            if (mult_counter >= ((2*MATRIX_SIZE - 1) * 4)) begin        // need (2n-1)*4 cycles to finish up all the operations 
                done_next = 1;
            end
        end
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            load_weight_next = {MATRIX_SIZE{1'b0}};
            enable_mult_next = {MATRIX_SIZE{1'b0}};
            load_counter = 0;
            mult_counter = 0;
            done_load = 0;
            done_next = 0;
            // done <= 0;
            // enable_mult <= 0;
            // load_weight <= 0;
        end
        else if (general_enable) begin

            done_reg <= done_next;
            enable_mult_reg <= enable_mult_next;
            load_weight_reg <= load_weight_next;
        end
    end

    // assign done_load_wire = done_load;
    assign done = done_reg;
    // assign enable_mult = enable_mult_reg;
    assign load_weight = load_weight_reg;
    
endmodule