#include <stdio.h>

#include "RunningStats1.h"

//from https://stackoverflow.com/a/1175491
double data1[4][5] =
{
	{0.01, 0.01, 0.02, 0.04, 0.03},
	{0.00, 0.02, 0.02, 0.03, 0.02},
	{0.01, 0.02, 0.02, 0.03, 0.02},
	{0.01, 0.00, 0.01, 0.05, 0.03}
};

int main(int argc, char *argv[])
{
	RunningStats1 rs1;
	
	for(auto i = 0 ; i < 4; ++i)
	{
		for(auto j = 0; j < 5; ++j)
		{
			rs1.update(data1[i][j]);
		}
/*
rs1.std()  sample 0.01303840, population 0.01166190, mean 0.02200000
rs1.std()  sample 0.01095445, population 0.00979796, mean 0.01800000
rs1.std()  sample 0.00707107, population 0.00632456, mean 0.02000000
rs1.std()  sample 0.02000000, population 0.01788854, mean 0.02000000
 */
		printf("rs1.std()  sample %.8f, population %.8f, mean %.8f\n", rs1.stddevSample(), rs1.stddevPopulation(), rs1.mean());
		rs1.reset();
	}
	
	return 0 ;
}
