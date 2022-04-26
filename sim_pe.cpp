#include <iostream>
#include "verilated.h"
#include "Vsystolic_pe.h"
#include "Vsystolic_pe__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vsystolic_pe *pe = new Vsystolic_pe;
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            pe->clk = !pe->clk;
            if (pe->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out Sum: " << pe->out_sum << " " << pe->out_data << std::endl;
            }
        }
        if (timestamp > 1 && timestamp < RESET_TIME)
        {
            pe->reset = 1; // Assert reset
        }
        else
        {
            pe->reset = 0; // Deassert reset
            pe->enable = 1;
        }
        // Load a weight
        if (timestamp == 20)
        {
            pe->ld_weight = 1;
            pe->in_sum = 3;
        }
        // Perform multiply
        if (timestamp == 30)
        {
            pe->ld_weight = 0;
            pe->in_sum = 1;
            pe->in_data = 2;
        }

        pe->eval();
        timestamp++;
    }
    int final_sum = pe->out_sum;
    pe->final();
    delete pe;
    std::cout << "Final Sum: " << final_sum << std::endl;
    return 0;
}
