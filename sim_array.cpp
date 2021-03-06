#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vsystolic_array.h"
#include "Vsystolic_array__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 250

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
            systolic_array->clk = !systolic_array->clk;
            if (systolic_array->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << systolic_array->out_sum[0] << " " << systolic_array->out_sum[1] << std::endl;
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
            systolic_array->enable = 1;

            systolic_array->in_weights[0] = 2;
            systolic_array->in_weights[1] = 4;
        }
        // Cycle 1
        if (timestamp == 20)
        {

            systolic_array->in_weights[0] = 1;
            systolic_array->in_weights[1] = 3;
        }
        // Finished loading weights

        // Start feeding inputs
        // Cycle 2
        if (timestamp == 30)
        {
            // Turn off load weight signal
            systolic_array->load_weight = 0;
            systolic_array->in_weights[0] = 0;
            systolic_array->in_weights[1] = 0;
            systolic_array->in_data[0] = 1;
            systolic_array->in_data[1] = 0;
        }

        // Cycle 6
        if (timestamp == 70)
        {
            systolic_array->in_data[0] = 2;
            systolic_array->in_data[1] = 3;
        }

        // Cycle 10
        if (timestamp == 110)
        {
            systolic_array->in_data[0] = 0;
            systolic_array->in_data[1] = 4;
        }

        // Cycle 14
        if (timestamp == 150)
        {
            systolic_array->in_data[0] = 0;
            systolic_array->in_data[1] = 0;
        }

        systolic_array->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    systolic_array->final();
    trace->close();
    delete trace;
    delete systolic_array;
    return 0;
}
