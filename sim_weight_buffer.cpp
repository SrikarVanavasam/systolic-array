#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vweight_buffer.h"
#include "Vweight_buffer__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 20

int main(int argc, char **argv, char **env)
{
    Vweight_buffer *weight_buffer = new Vweight_buffer;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    weight_buffer->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            weight_buffer->clk = !weight_buffer->clk;
            if (weight_buffer->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << weight_buffer->data_out[0] << " " << weight_buffer->data_out[1] << std::endl;
            }
        }
        if (timestamp < RESET_TIME)
        {
            weight_buffer->reset = 1; // Assert reset
        }
        else
        {
            weight_buffer->reset = 0; // Deassert reset
            weight_buffer->enable = 1;
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

        weight_buffer->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    weight_buffer->final();
    trace->close();
    delete trace;
    delete weight_buffer;
    return 0;
}
