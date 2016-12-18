#pragma once

class CPiCalculator
{
	CPiCalculator() = delete;
	CPiCalculator & operator=(CPiCalculator const&) = delete;
	CPiCalculator & operator=(CPiCalculator &&) = delete;
public:
	static double CalculatePi(int iterationsCount);

private:
	static bool HitInCircle(double x, double y);
};