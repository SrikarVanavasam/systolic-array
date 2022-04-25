#include <iostream>
#include "verilated.h"
#include "Vmatmul.h"
#include "Vmatmul__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 150

#define CLOCK_PERIOD 5

#define RESET_TIME 10

int main(int argc, char **argv, char **env)
{
    Vmatmul *matmul = new Vmatmul;
    while (timestamp < RUN_CYCLES)
    {
        if (!(timestamp % CLOCK_PERIOD))
        {
            matmul->clk = !matmul->clk;
            if (matmul->clk)
            {
                std::cout << "Cycle: " << timestamp / (CLOCK_PERIOD * 2) << " Out: " << matmul->out_sum[0] << " " << matmul->out_sum[1] << std::endl;
            }
        }
        if (timestamp > 1 && timestamp < RESET_TIME)
        {
            matmul->reset = 1; // Assert reset
        }
        else
        {
            matmul->reset = 0; // Deassert reset
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
            matmul->ld_weight = 1;
            matmul->in_weights[0] = 3;
            matmul->in_weights[1] = 4;
        }
        if (timestamp == 30)
        {
            matmul->ld_weight = 1;
            matmul->in_weights[0] = 1;
            matmul->in_weights[1] = 2;
        }
        if (timestamp == 40)
        {
            matmul->ld_weight = 0;
            matmul->in_weights[0] = 0;
            matmul->in_weights[1] = 0;
        }

        // Perform multiply
        if (timestamp == 60)
        {
            matmul->in_data[0] = 4;
            matmul->in_data[1] = 0;
        }
        if (timestamp == 70)
        {
            matmul->in_data[0] = 2;
            matmul->in_data[1] = 3;
        }
        if (timestamp == 80)
        {
            matmul->in_data[0] = 0;
            matmul->in_data[1] = 1;
        }

        matmul->eval();
        timestamp++;
    }
    matmul->final();
    delete matmul;
    return 0;
}
