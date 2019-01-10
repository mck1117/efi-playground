#include <gasoline/GasolineFuelComputer.h>

GasolineFuelResult GasolineFuelComputer::ComputeFuel(AirflowEstimate airflow)
{
	GasolineFuelResult result;

	result.TargetLambda = Number(1.0f); // = m_lambdaTable.Get(rpm, result.Airflow.CylinderAirMass)

	// Compute 'base' fueling
	result.TargetAfr = m_config.FuelStoichiometricMassRatio * result.TargetLambda;
	QMass cylinderFuelMass = airflow.CylinderAirMass / result.TargetAfr;
    result.BaseCylinderFuelMass = cylinderFuelMass;

	// Everyone who wants to poke the 'base' fuel quantity can do so
	// This is where IAT, CLT correction, after start correction,
    // dfco, closed loop, etc can happen
	for (int i = 0; i < m_pipelineStageCount; i++)
	{
		cylinderFuelMass = m_pipeline[i]->AdjustFuel(cylinderFuelMass);
	}

	result.AdjustedCylinderFuelMass = cylinderFuelMass;

	return result;
}
