#include <gtest/gtest.h>
#include <gasoline/GasolineFuelComputer.h>

TEST(GasFuelComputer, testgas)
{
	GasolineInjectionConfiguration config{ 10.0f };
	GasolineFuelComputer gfc(config);

	AirflowEstimate airflow;
	airflow.CylinderAirMass = 1_g;
	airflow.TotalMassFlowRate = 1_g / second;

	auto result = gfc.ComputeFuel(airflow);

	ASSERT_NEAR(1e-4, result.BaseCylinderFuelMass.getValue(), 1e-6);
	ASSERT_EQ(result.BaseCylinderFuelMass, result.AdjustedCylinderFuelMass);
}

class MockPipelineStage : public FuelAdjustmentPipelineStage
{
private:
	const Number m_multiplier;

public:
	MockPipelineStage(float multiplier)
		: m_multiplier(multiplier)
	{
	}

	virtual QMass AdjustFuel(QMass input) override
	{
		return m_multiplier * input;
	}
};

TEST(GasFuelComputer, TestSinglePipelineStage)
{
	GasolineInjectionConfiguration config{ 10.0f };
	GasolineFuelComputer gfc(config);

	AirflowEstimate airflow;
	airflow.CylinderAirMass = 1_g;
	airflow.TotalMassFlowRate = 1_g / second;

	MockPipelineStage ps1(2);

	gfc.AddPipelineStage(&ps1);

	auto result = gfc.ComputeFuel(airflow);

	ASSERT_NEAR(1e-4, result.BaseCylinderFuelMass.getValue(), 1e-6);
	ASSERT_NEAR(2e-4, result.AdjustedCylinderFuelMass.getValue(), 1e-6);
}

TEST(GasFuelComputer, TestMultiPipelineStage)
{
	GasolineInjectionConfiguration config{ 10.0f };
	GasolineFuelComputer gfc(config);

	AirflowEstimate airflow;
	airflow.CylinderAirMass = 1_g;
	airflow.TotalMassFlowRate = 1_g / second;

	MockPipelineStage ps1(2);
	MockPipelineStage ps2(3);

	gfc.AddPipelineStage(&ps1);
	gfc.AddPipelineStage(&ps2);

	auto result = gfc.ComputeFuel(airflow);

	ASSERT_NEAR(1e-4, result.BaseCylinderFuelMass.getValue(), 1e-6);
	ASSERT_NEAR(6e-4, result.AdjustedCylinderFuelMass.getValue(), 1e-6);
}
