#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vscheduler.h"
#include "Vscheduler__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vscheduler *sched = new Vscheduler;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    sched->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            sched->clk = !sched->clk;
            if (sched->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: ";
                printf("%d \n", sched->enable_mult);
            }
        }
        if (timestamp < RESET_TIME)
        {
            sched->reset = 1; // Assert reset
        }
        else
        {
            sched->reset = 0; // Deassert reset
            sched->general_enable = 1;
        }

        sched->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    sched->final();
    trace->close();
    delete trace;
    delete sched;
    return 0;
}
