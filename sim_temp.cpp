#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vsystolic_array_frame_temp.h"
#include "Vsystolic_array_frame_temp__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 500

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vsystolic_array_frame_temp *systolic_array_frame_temp = new Vsystolic_array_frame_temp;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    systolic_array_frame_temp->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            systolic_array_frame_temp->clk = !systolic_array_frame_temp->clk;
            if (systolic_array_frame_temp->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << systolic_array_frame_temp->result_out[0] << " " << systolic_array_frame_temp->result_out[1] << std::endl;
            }
        }
        if (timestamp < RESET_TIME)
        {
            systolic_array_frame_temp->reset = 1; // Assert reset
        }
        else
        {
            systolic_array_frame_temp->reset = 0; // Deassert reset
            systolic_array_frame_temp->enable = 1;
            systolic_array_frame_temp->input_ready = 1;
            systolic_array_frame_temp->output_ready = 1;
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
               // Cycle 1
        if (timestamp == 10)
        {
            // All PEs are enabled during weights loading
            // systolic_array_frame_temp->load_weight = 1;
            systolic_array_frame_temp->enable = 1;

            systolic_array_frame_temp->weights_input[0] = 2;
            systolic_array_frame_temp->weights_input[1] = 4;

            systolic_array_frame_temp->data_input[0] = 1;
            systolic_array_frame_temp->data_input[1] = 3;
        }
        // Cycle 2
        if (timestamp == 20)
        {

            systolic_array_frame_temp->weights_input[0] = 1;
            systolic_array_frame_temp->weights_input[1] = 3;

            systolic_array_frame_temp->data_input[0] = 0;
            systolic_array_frame_temp->data_input[1] = 0;
        }
        // Finished loading weights

        // Start feeding inputs
        // Cycle 3
        if (timestamp == 30)
        {
            // Turn off load weight signal
            // systolic_array_frame_temp->load_weight = 0;
            systolic_array_frame_temp->weights_input[0] = 0;
            systolic_array_frame_temp->weights_input[1] = 0;
        }

        // Cycle 5
        if (timestamp == 50)
        {
            systolic_array_frame_temp->data_input[0] = 2;
            systolic_array_frame_temp->data_input[1] = 4;
        }

        // Cycle 9
        if (timestamp == 60)
        {
            systolic_array_frame_temp->data_input[0] = 0;
            systolic_array_frame_temp->data_input[1] = 0;
        }

        // comment this out after making sure that skewer is functional
        // Cycle 13
        // if (timestamp == 130)
        // {
        //     systolic_array_frame_temp->data_input[0] = 5;
        //     systolic_array_frame_temp->data_input[1] = 6;
        // }

        systolic_array_frame_temp->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    systolic_array_frame_temp->final();
    trace->close();
    delete trace;
    delete systolic_array_frame_temp;
    return 0;
}
