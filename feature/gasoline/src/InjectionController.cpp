#include <gasoline/GasolineInjectionController.h>

GasolineFuelResult GasolineFuelingComputer::ComputeFuel(AirflowEstimate airflow)
{
	GasolineFuelResult result;

	result.TargetLambda = Number(1.0f); // = m_lambdaTable.Get(rpm, result.Airflow.CylinderAirMass)

	// Compute 'base' fueling
	result.TargetAfr = m_config.FuelStoichiometricMassRatio * result.TargetLambda;
	QMass cylinderFuelMass = airflow.CylinderAirMass / result.TargetAfr;
	result.BaseCylinderFuelMass = cylinderFuelMass;

	// Everyone who wants to poke the fuel quantity can do so
	// This is where IAT, CLT correction, accel enrichment, after start 
	// correction, dfco, closed loop, etc happens
	for (int i = 0; i < m_pipelineStageCount; i++)
	{
		cylinderFuelMass = m_pipeline[i]->AdjustFuel(cylinderFuelMass);
	}

	result.AdjustedCylinderFuelMass = cylinderFuelMass;

	return result;
}
