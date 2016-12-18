#include "PiCalculator.h"
#include <stdlib.h>
#include <ctime>
#include <math.h> 

namespace
{
double GenerateRandomNumber()
{
	return double(rand()) / RAND_MAX;
}
}

double CPiCalculator::CalculatePi(int iterationsCount)
{
	auto time_ui = static_cast<unsigned>(time(NULL) % 1000);
	srand(time_ui); // change seed value for random number generation
	int hitsCount = 0;
	for (auto index = 0; index < iterationsCount; index++)
	{
		hitsCount += static_cast<int>(HitInCircle(GenerateRandomNumber(), GenerateRandomNumber()));
	}
	return 4.0 * hitsCount / iterationsCount;
}

bool CPiCalculator::HitInCircle(double x, double r)
{
	return (x*x + r*r) <= 1;
}
