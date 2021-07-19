#pragma once

#include "RandomManager.h"

/// <summary>
/// The class inheriting it will hold unique (maybe) id.
/// </summary>
class IdHolder
{
private:
	unsigned int id;
protected:
	IdHolder()
	{
		id = RandomManager::GetRandomInt();
	}
	virtual ~IdHolder()
	{
	}
public:
	unsigned int GetId()
	{
		return id;
	}
};
