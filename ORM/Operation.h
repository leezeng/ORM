#pragma once
class IOperation
{
public:
	IOperation(){};
	virtual ~IOperation(){};
	virtual bool Open(const char* chPath)=0;
};