#pragma once

#include <core/Types.h>

struct IAirflowEstimator
{
	virtual massrate_t GetMassFlowRate() = 0;
};
