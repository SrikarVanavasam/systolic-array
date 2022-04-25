#include <iostream>
#include "verilated.h"
#include "Vmac.h"
#include "Vmac__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 1000

#define CLOCK_PERIOD 10

#define RESET_TIME 100

int main(int argc, char **argv, char **env)
{
    Vmac *mac = new Vmac;
    while (timestamp < RUN_CYCLES)
    {
        if ((timestamp % CLOCK_PERIOD))
            mac->clk = !mac->clk;
        if (timestamp > 1 && timestamp < RESET_TIME)
        {
            mac->reset = 1; // Assert reset
        }
        else
        {
            mac->reset = 0; // Deassert reset
        }
        // Load a weight
        if (timestamp == 150)
        {
            mac->ld_weight = 1;
            mac->in_sum = 3;
        }
        // Perform multiply
        if (timestamp == 160)
        {
            mac->ld_weight = 0;
            mac->in_sum = 1;
            mac->in_data = 2;
        }

        mac->eval();
        timestamp++;
    }
    int final_sum = mac->out_sum;
    mac->final();
    delete mac;
    std::cout << "Final Sum: " << final_sum << std::endl;
    return 0;
}
