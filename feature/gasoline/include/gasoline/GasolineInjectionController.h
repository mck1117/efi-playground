#pragma once

#include <core/Types.h>
#include <gasoline\IAirflowEstimator.h>
#include <core/math/Table.h>

struct GasolineFuelResult
{
	// The mass of fuel that should be injected per cylinder
	QMass BaseCylinderFuelMass;
	QMass AdjustedCylinderFuelMass;

	Number TargetLambda;
	Number TargetAfr;
};

struct GasolineInjectionConfiguration
{
	Number FuelStoichiometricMassRatio;
};

struct FuelAdjustmentPipelineStage
{
	virtual QMass AdjustFuel(QMass input) = 0;
};

class GasolineFuelingComputer final
{
private:
	const GasolineInjectionConfiguration m_config;

	int m_pipelineStageCount = 0;
	FuelAdjustmentPipelineStage* m_pipeline[6];

public:
	GasolineFuelingComputer(const GasolineInjectionConfiguration& config)
		: m_config(config)
	{
	}

	void AddPipelineStage(FuelAdjustmentPipelineStage* stage)
	{
		m_pipeline[m_pipelineStageCount] = stage;
		m_pipelineStageCount++;
	}

	GasolineFuelResult ComputeFuel(AirflowEstimate airflow);
};
