#pragma once

#include <core/Types.h>
#include <core/sensors/ISensor.h>

struct AirflowEstimate
{
	QMass CylinderAirMass;
	massrate_t TotalMassFlowRate;
	Number EngineLoad;
};

struct AirflowEstimatorConfiguration
{
	// Displacement of one cycle for one cylinder (or rotor)
	QVolume CylinderDisplacement;

	// Number of combustion events per crankshaft revolution
	// For 4 stroke engines, this is cyl count / 2
	// For 2 stroke engines, this is cyl count
	// For wankel engines, this is cyl count
	Number CylindersPerRevolution;

	QTemperature FailedCltValue;
	QTemperature FailedIatValue;
};

class IAirflowEstimator
{
protected:
	const AirflowEstimatorConfiguration m_configCommon;

	const SensorHolder<QFrequency> m_enginespeed;
	const SensorHolder<QTemperature> m_iat;
	const SensorHolder<QTemperature> m_clt;

	IAirflowEstimator(const AirflowEstimatorConfiguration& config, const ISensor* iat, const ISensor* clt, const ISensor* enginespeed)
		: m_configCommon(config)
		, m_enginespeed(enginespeed)
		, m_iat(iat)
		, m_clt(clt)
	{
	}
public:
	virtual AirflowEstimate EstimateAirflow() = 0;
};
