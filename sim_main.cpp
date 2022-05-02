#include <iostream>
#include "verilated.h"
#include "Vsystolic_array_frame.h"
#include "Vsystolic_array_frame__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vsystolic_array_frame *systolic_array_frame = new Vsystolic_array_frame;
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
        if (timestamp > 1 && timestamp < RESET_TIME)
        {
            systolic_array_frame->reset = 1; // Assert reset
        }
        else
        {
            systolic_array_frame->reset = 0; // Deassert reset
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
        if (timestamp == 20)
        {
            systolic_array_frame->enable = 1;
            systolic_array_frame->weights_input[0] = 3;
            systolic_array_frame->weights_input[1] = 4;
        }
        if (timestamp == 30)
        {
            systolic_array_frame->weights_input[0] = 1;
            systolic_array_frame->weights_input[1] = 2;
        }

        systolic_array_frame->eval();
        timestamp++;
    }
    systolic_array_frame->final();
    delete systolic_array_frame;
    return 0;
}
