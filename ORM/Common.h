#pragma once
#include "Factory.h"
class CCommon :	public CFactory
{
public:
	DECALRE_FACTORY_CLASS(CCommon)
	CCommon(void);
	virtual ~CCommon(void);
};

