#include <gasoline/SpeedDensity.h>

#define AIR_MASS_PER_MOL (0.0289647_kg)

/* static */ constexpr QMass SpeedDensity::GetCylinderAirMassSd(QVolume cylinderDisplacement, QTemperature chargeTemperature, Number ve, QPressure map)
{
	constexpr auto precalc = AIR_MASS_PER_MOL / GAS_CONSTANT;

	Number mols = ((ve * map * cylinderDisplacement) / (GAS_CONSTANT * chargeTemperature));

	return mols * AIR_MASS_PER_MOL;
}

AirflowEstimate SpeedDensity::EstimateAirflow()
{
	// Read sensors
	QTemperature clt = m_clt.GetOrDefault(m_configCommon.FailedCltValue);
	QTemperature iat = m_iat.GetOrDefault(m_configCommon.FailedIatValue);
	QPressure map = m_map.Get().Value;
	QFrequency rpm = m_enginespeed.Get().Value;
	//float ve = m_config.VeTable->Get(rpm, map);
	Number ve = Number(1.0f);

	AirflowEstimate result;

	// Primary calculation
	result.CylinderAirMass = GetCylinderAirMassSd(m_configCommon.CylinderDisplacement, iat, ve, map);

	// Secondary calculations
	result.TotalMassFlowRate = result.CylinderAirMass * m_configCommon.CylindersPerRevolution * rpm;
	
	// Engine load is fraction of 'ideal' we could be doing with 1 atm, and 100% VE
	// With boost, this is expected to be over 1.0.  1 bar boost, 100% ve, at standard temperature
	// means you should should get 2.0 engine load.
	auto optimum = GetCylinderAirMassSd(m_configCommon.CylinderDisplacement, QTemperature(273.15f), Number(1.0), 101.325_kpa);
	result.EngineLoad = result.CylinderAirMass / optimum;

	return result;
}
