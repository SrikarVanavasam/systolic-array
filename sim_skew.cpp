#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vinput_skewer.h"
#include "Vinput_skewer__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vinput_skewer *skew = new Vinput_skewer;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    skew->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            skew->clk = !skew->clk;
            if (skew->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out Sum: " << skew->data_skewed[0] << " " << skew->data_skewed[1] << std::endl;
            }
        }
        if (timestamp < RESET_TIME)
        {
            skew->reset = 1; // Assert reset
        }
        else
        {
            skew->reset = 0; // Deassert reset
            skew->enable_in = 1;
        }
        if (timestamp == 20)
        {
            skew->data[0] = 3;
            skew->data[1] = 6;
        }
        if (timestamp == 60)
        {
            skew->data[0] = 1;
            skew->data[1] = 2;
        }

        skew->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    skew->final();
    trace->close();
    delete trace;
    delete skew;
    return 0;
}
