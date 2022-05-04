#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vsystolic_array_frame_temp.h"
#include "Vsystolic_array_frame_temp__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 350

#define CLOCK_PERIOD 5

#define RESET_TIME 20

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
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " | ";
                std::cout << "Out: " << systolic_array_frame_temp->result_out[0] << " " << systolic_array_frame_temp->result_out[1] << " | ";
                std::cout << "results_ready: " << int(systolic_array_frame_temp->results_ready) << " | ";
                std::cout << "module_busy: " << int(systolic_array_frame_temp->module_busy) << " | ";
                std::cout << "module_ready: " << int(systolic_array_frame_temp->module_ready) << " | ";
                std::cout << "valid_in: " << int(systolic_array_frame_temp->valid_in) << " | ";
                std::cout << "ready_out: " << int(systolic_array_frame_temp->ready_out) << " | ";
                std::cout << "ready_in: " << int(systolic_array_frame_temp->ready_in) << " | ";
                std::cout << "valid_out: " << int(systolic_array_frame_temp->valid_out) << std::endl;

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
            systolic_array_frame_temp->valid_in = 1;
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

        // Cycle 3
        if (timestamp == 50)
        {
            // All PEs are enabled during weights loading
            // systolic_array_frame_temp->load_weight = 1;
            systolic_array_frame_temp->enable = 1;

            // systolic_array_frame_temp->weights_input[0] = 2;
            // systolic_array_frame_temp->weights_input[1] = 4;

            // systolic_array_frame_temp->data_input[0] = 1;
            // systolic_array_frame_temp->data_input[1] = 3;
        }
        // Cycle 4
        if (timestamp == 60)
        {

            // systolic_array_frame_temp->weights_input[0] = 1;
            // systolic_array_frame_temp->weights_input[1] = 3;

            // systolic_array_frame_temp->data_input[0] = 0;
            // systolic_array_frame_temp->data_input[1] = 0;
        }
        // Finished loading weights

        // Cycle 5
        if (timestamp == 70)
        {
            // Turn off load weight signal
            // systolic_array_frame_temp->load_weight = 0;
            // systolic_array_frame_temp->weights_input[0] = 0;
            // systolic_array_frame_temp->weights_input[1] = 0;
        }

        // Cycle 7
        if (timestamp == 90)
        {
            // systolic_array_frame_temp->data_input[0] = 2;
            // systolic_array_frame_temp->data_input[1] = 4;
        }

        // Cycle 8
        if (timestamp == 100)
        {
            // systolic_array_frame_temp->data_input[0] = 0;
            // systolic_array_frame_temp->data_input[1] = 0;
        }

        // Cycle 11
        if (timestamp == 130)
        {
            // systolic_array_frame_temp->data_input[0] = 0;
            // systolic_array_frame_temp->data_input[1] = 0;
        }
        
        if (timestamp == 280)
        {
            systolic_array_frame_temp->ready_out = 1;
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
