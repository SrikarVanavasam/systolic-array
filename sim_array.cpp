#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vsystolic_array_frame.h"
#include "Vsystolic_array_frame__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 20

int main(int argc, char **argv, char **env)
{
    Vsystolic_array *systolic_array = new Vsystolic_array;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    systolic_array->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            systolic_array_frame->clk = !systolic_array_frame->clk;
            if (systolic_array_frame->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << systolic_array_frame->result_out[0] << " " << systolic_array_frame->result_out[1] << std::endl;
            }
        }
        // if (timestamp < RESET_TIME)
        // {
        //     systolic_array_frame->reset = 1; // Assert reset
        // }
        // else
        // {
        //     systolic_array_frame->reset = 0; // Deassert reset
        //     systolic_array_frame->enable = 0;
        // }
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

        // Cycle 0
        if (timestamp == 10)        
        {
            // All PEs are enabled during weights loading
            systolic_array->load_weight = 1;
            systolic_array->enable_mult = 1;

            systolic_array->in_weights[0] = 1;
            systolic_array->in_weights[1] = 3;

        }
        // Cycle 1
        if (timestamp == 15)
        {

            systolic_array->in_weights[0] = 2;
            systolic_array->in_weights[1] = 4;

        }
        // Finished loading weights

        // Start feeding inputs
        // Cycle 2
        if (timestamp == 20)
        {
            // Turn off load weight signal
            systolic_array->load_weight = 0;

            systolic_array->in_data[0] = 1;
            systolic_array->in_data[1] = 0;
        }

        // Cycle 6
        if (timestamp == 40)
        {            
            systolic_array->in_data[0] = 2;
            systolic_array->in_data[1] = 3;
        }

        // Cycle 10
        if (timestamp == 60)
        {            
            systolic_array->in_data[0] = 0;
            systolic_array->in_data[1] = 4;
        }

        systolic_array_frame->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    systolic_array_frame->final();
    trace->close();
    delete trace;
    delete systolic_array_frame;
    return 0;
}
