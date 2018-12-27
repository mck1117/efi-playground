#pragma once

#include <gasoline/IAirflowEstimator.h>

#include <core/math/Table.h>

#include <core/sensors/ISensor.h>

struct SpeedDensityConfiguration
{
	QVolume EngineDisplacement;
	/**
	  * Identifies if the engine is 2, 4 or other stroke.  If 2 stroke, RevolutionsPerCycle = 1.
	  * If 4 stroke, RevolutionsPerCycle = 2.
	  */
	uint8_t RevolutionsPerCycle;

	QTemperature FailedCltValue;
	QTemperature FailedIatValue;

    //Table3d<float, float, 16>* VeTable;
    Table2d<massrate_t, Number, 8> ManifoldTransferCurve;
};

class SpeedDensity : public IAirflowEstimator
{
private:
	const SpeedDensityConfiguration m_config;
    const SensorHolder<QFrequency> m_enginespeed;
    const SensorHolder<QPressure> m_map;
    const SensorHolder<QTemperature> m_iat;
    const SensorHolder<QTemperature> m_clt;
	
	QMass GetMassPerEngineCycle(QTemperature chargeTemperature, Number ve, QPressure map);
public:
    SpeedDensity(const SpeedDensityConfiguration& config, const ISensor* enginespeed, const ISensor* map, const ISensor* iat, const ISensor* clt)
    : m_config(config)
    , m_enginespeed(enginespeed)
    , m_map(map)
    , m_iat(iat)
    , m_clt(clt)
    {
    }

	virtual massrate_t GetMassFlowRate() override;
};
