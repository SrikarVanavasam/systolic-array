#include <iostream>
#include "verilated.h"
#include <verilated_vcd_c.h>
#include "Vdata_fetcher.h"
#include "Vdata_fetcher__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 20

int main(int argc, char **argv, char **env)
{
    Vdata_fetcher *data_fetcher = new Vdata_fetcher;

    Verilated::traceEverOn(true);
    auto trace = new VerilatedVcdC();
    data_fetcher->trace(trace, 2999);
    trace->open("trace.vcd");
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            data_fetcher->clk = !data_fetcher->clk;
            if (data_fetcher->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << data_fetcher->data_w_interval_out[0] << " " << data_fetcher->data_w_interval_out[1] << std::endl;
            }
        }
        if (timestamp < RESET_TIME)
        {
            data_fetcher->reset = 1; // Assert reset
        }
        else
        {
            data_fetcher->reset = 0; // Deassert reset
            data_fetcher->enable = 1;
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

        data_fetcher->eval();
        trace->dump(timestamp);
        timestamp++;
    }
    data_fetcher->final();
    trace->close();
    delete trace;
    delete data_fetcher;
    return 0;
}
