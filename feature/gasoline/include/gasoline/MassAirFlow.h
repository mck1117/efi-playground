#pragma once

#include <gasoline/IAirflowEstimator.h>

#include <core/math/Table.h>
#include <core/sensors/ISensor.h>

struct MassAirFlowConfiguration
{
};

class MassAirFlow : public IAirflowEstimator
{
private:
    const MassAirFlowConfiguration m_config;

    const SensorHolder<massrate_t> m_maf;

public:
	MassAirFlow(const AirflowEstimatorConfiguration& configCommon, const MassAirFlowConfiguration& config, const ISensor* maf, const ISensor* enginespeed, const ISensor* iat, const ISensor* clt)
		: IAirflowEstimator(configCommon, iat, clt, enginespeed)
		, m_config(config)
		, m_maf(maf)
	{
	}

	AirflowEstimate EstimateAirflow() override;
};
