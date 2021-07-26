#pragma once

/// <summary>
/// The class inheriting it will hold unique (maybe) id.
/// </summary>
class IdHolder
{
private:
	unsigned long id;
protected:
	IdHolder();
	virtual ~IdHolder() { }
public:
	const unsigned long& GetId();
};
