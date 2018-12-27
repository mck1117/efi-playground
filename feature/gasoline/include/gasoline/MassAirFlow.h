
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
    const SensorHolder<QFrequency> m_enginespeed;
    const SensorHolder<QTemperature> m_iat;

public:
	MassAirFlow(const MassAirFlowConfiguration& config, const ISensor* maf, const ISensor* enginespeed, const ISensor* iat)
		: m_config(config)
		, m_maf(maf)
		, m_enginespeed(enginespeed)
		, m_iat(iat)
	{
	}

	massrate_t GetMassFlowRate() override;
};
