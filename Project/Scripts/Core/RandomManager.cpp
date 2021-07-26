#include <random>
#include "RandomManager.h"

std::mt19937 gen(0);

unsigned int RandomManager::GetRandomInt()
{
	return gen();
}

unsigned long RandomManager::GetRandomLong()
{
	return gen();
}
