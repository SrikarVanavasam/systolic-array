#include <iostream>
#include "verilated.h"
#include "Vmatmul.h"
#include "Vmatmul__Syms.h"

uint64_t timestamp = 0;

#define RUN_CYCLES 170

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
                std::cout << "Time: " << timestamp << " Out: " << matmul->out_sum[0] << " " << matmul->out_sum[1] << " " << matmul->out_sum[2] << std::endl;
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
         * [1, 2, 3,
         *  4, 5, 6,
         *  7, 8, 9]
         * Data:
         * [9, 8, 7,
         *  6, 5, 4,
         *  3, 2, 1]
         *
         */
        // Load a weight
        if (timestamp == 20)
        {
            matmul->ld_weight = 1;
            matmul->in_weights[0] = 7;
            matmul->in_weights[1] = 8;
            matmul->in_weights[2] = 9;
        }
        if (timestamp == 30)
        {
            matmul->ld_weight = 1;
            matmul->in_weights[0] = 4;
            matmul->in_weights[1] = 5;
            matmul->in_weights[2] = 6;
        }
        if (timestamp == 40)
        {
            matmul->ld_weight = 1;
            matmul->in_weights[0] = 1;
            matmul->in_weights[1] = 2;
            matmul->in_weights[2] = 3;
        }
        // Perform multiply
        if (timestamp == 60)
        {
            matmul->ld_weight = 0;
            matmul->in_data[0] = 9;
            matmul->in_data[1] = 0;
            matmul->in_data[2] = 0;
        }
        if (timestamp == 70)
        {
            matmul->ld_weight = 0;
            matmul->in_data[0] = 8;
            matmul->in_data[1] = 6;
            matmul->in_data[2] = 0;
        }
        if (timestamp == 80)
        {
            matmul->ld_weight = 0;
            matmul->in_data[0] = 7;
            matmul->in_data[1] = 5;
            matmul->in_data[2] = 3;
        }
        if (timestamp == 90)
        {
            matmul->ld_weight = 0;
            matmul->in_data[0] = 0;
            matmul->in_data[1] = 4;
            matmul->in_data[2] = 2;
        }
        if (timestamp == 100)
        {
            matmul->ld_weight = 0;
            matmul->in_data[0] = 0;
            matmul->in_data[1] = 0;
            matmul->in_data[2] = 1;
        }

        matmul->eval();
        timestamp++;
    }
    matmul->final();
    delete matmul;
    return 0;
}
