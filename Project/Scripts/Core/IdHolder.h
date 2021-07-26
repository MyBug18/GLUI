#pragma once

#include "RandomManager.h"

/// <summary>
/// The class inheriting it will hold unique (maybe) id.
/// </summary>
class IdHolder
{
private:
	unsigned long id;
protected:
	IdHolder()
	{
		id = RandomManager::GetRandomLong();
	}
	virtual ~IdHolder()
	{
	}
public:
	unsigned long GetId()
	{
		return id;
	}
};
