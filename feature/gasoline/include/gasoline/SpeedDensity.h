#pragma once

#include <gasoline/IAirflowEstimator.h>

#include <core/math/Table.h>

#include <core/sensors/ISensor.h>

struct SpeedDensityConfiguration
{
    //Table3d<float, float, 16>* VeTable;
    Table2d<massrate_t, Number, 8> ManifoldTransferCurve;
};

class SpeedDensity : public IAirflowEstimator
{
private:
	const SpeedDensityConfiguration m_config;

    const SensorHolder<QPressure> m_map;
    
	static constexpr QMass GetCylinderAirMassSd(QVolume cylinderDisplacement, QTemperature chargeTemperature, Number ve, QPressure map);
public:
    SpeedDensity(const AirflowEstimatorConfiguration& configCommon, const SpeedDensityConfiguration& config, const ISensor* enginespeed, const ISensor* map, const ISensor* iat, const ISensor* clt)
    : IAirflowEstimator(configCommon, iat, clt, enginespeed)
	, m_config(config)
    , m_map(map)
    {
    }

	AirflowEstimate EstimateAirflow() override;
};
