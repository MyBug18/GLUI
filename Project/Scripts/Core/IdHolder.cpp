#include "IdHolder.h"
#include "RandomManager.h"

IdHolder::IdHolder()
{
	id = RandomManager::GetRandomLong();
}

const unsigned long& IdHolder::GetId()
{
	return id;
}
