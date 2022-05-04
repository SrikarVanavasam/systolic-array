#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vinput_buffer.h"
#include "Vinput_buffer__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 20

int main(int argc, char **argv, char **env)
{
    Vinput_buffer *input_buffer = new Vinput_buffer;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    input_buffer->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            input_buffer->clk = !input_buffer->clk;
            if (input_buffer->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << input_buffer->data_w_interval_out[0] << " " << input_buffer->data_w_interval_out[1] << std::endl;
            }
        }
        if (timestamp < RESET_TIME)
        {
            input_buffer->reset = 1; // Assert reset
        }
        else
        {
            input_buffer->reset = 0; // Deassert reset
            input_buffer->enable = 1;
        }
        /**
         * Testing matrix multiply
         * Weights:
         * [1, 2,
         *  3, 4]
         * Data:
         * [4, 3,
         *  2, 1]
         *
         */
        // Load a weight

        input_buffer->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    input_buffer->final();
    trace->close();
    delete trace;
    delete input_buffer;
    return 0;
}
