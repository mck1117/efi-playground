#include <gasoline/SpeedDensity.h>

#define AIR_MASS_PER_MOL (0.0289647_kg)

QMass SpeedDensity::GetMassPerEngineCycle(QTemperature chargeTemperature, Number ve, QPressure map)
{
	constexpr auto precalc = AIR_MASS_PER_MOL / GAS_CONSTANT;

	Number mols = ((ve * map * m_config.EngineDisplacement) / (GAS_CONSTANT * chargeTemperature));

	return mols * AIR_MASS_PER_MOL;
}

massrate_t SpeedDensity::GetMassFlowRate()
{
	// Read sensors
	QTemperature clt = m_clt.GetOrDefault(m_config.FailedCltValue);
	QTemperature iat = m_iat.GetOrDefault(m_config.FailedIatValue);
	QPressure map = m_map.Get().Value;
	QFrequency rpm = m_enginespeed.Get().Value;
	//float ve = m_config.VeTable->Get(rpm, map);
	float ve = 1.0f;

	QFrequency cyclesPerSecond = rpm / m_config.RevolutionsPerCycle;

	QMass cycle = GetMassPerEngineCycle(iat, ve, map);
	massrate_t result = cycle * cyclesPerSecond;

	return result;
}
