
#include <gtest/gtest.h>

#include <gasoline/MassAirFlow.h>

class MafTest : public ::testing::Test
{
protected:
	MockSensor rpm;
	MockSensor maf;
	MockSensor iat;
	MockSensor clt;
};

TEST_F(MafTest, test2)
{
	AirflowEstimatorConfiguration configCommon{ QVolume(2.316 * litre / 4), 2, 273_k, 273_k };
	MassAirFlowConfiguration config{};

	MassAirFlow mf(configCommon, config, &maf, &rpm, &iat, &clt);

	rpm.Set({ true, (float)(1000_Rpm).getValue() });
	maf.Set({ true, (float)(40_g / second).getValue() });
	iat.Set({ true, 273.15f });
	clt.Set({ true, 273.15f });

	auto airflow = mf.EstimateAirflow();

	ASSERT_NEAR(0.040f, airflow.TotalMassFlowRate.getValue(), 0.001f);
	ASSERT_NEAR(0.0012f, airflow.CylinderAirMass.getValue(), 0.0001f);
}