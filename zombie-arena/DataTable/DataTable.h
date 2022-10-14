#pragma once
#include <string>

class DataTable
{
public:
	enum class Types
	{
		String,
	};

private:
	Types type;
	DataTable(const DataTable& ref);
	DataTable& operator=(const DataTable& ref);

public:
	static int TotalTypes;

	DataTable(Types t);
	virtual ~DataTable();

	virtual void Release() = 0;
	virtual bool Load() = 0;
};

