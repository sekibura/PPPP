#pragma once
#include "Strategy.h"
class ConcreteThirdStrategy final : public Strategy
{
public:
	Track Algorithm(int* _path, int _volume) override;
};

