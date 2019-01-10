#include <gasoline/MassAirFlow.h>

AirflowEstimate MassAirFlow::EstimateAirflow()
{
	massrate_t massFlow = m_maf.GetOrDefault(massrate_t(0.0f));
	QFrequency enginespeed = m_enginespeed.GetOrDefault(QFrequency(0.0f));

	QFrequency cylindersPerSecond = enginespeed * m_configCommon.CylindersPerRevolution;

	AirflowEstimate result;

	result.TotalMassFlowRate = massFlow;
	result.CylinderAirMass = massFlow / (cylindersPerSecond);
	//result.EngineLoad = 
	
	return result;
}
