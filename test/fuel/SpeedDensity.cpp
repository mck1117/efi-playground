#include <gtest/gtest.h>

#include <gasoline/SpeedDensity.h>
#include <gasoline/GasolineInjectionController.h>

class SpeedDensityTest : public ::testing::Test
{
protected:
	MockSensor rpm;
	MockSensor map;
	MockSensor iat;
	MockSensor clt;
};

TEST_F(SpeedDensityTest, test1)
{
	Table2Data<massrate_t, Number, 8> tchargedata;
	Table2d<massrate_t, Number, 8> tcharge(tchargedata);

	AirflowEstimatorConfiguration configCommon{ QVolume(2.316 * litre / 4), 2, 273_k, 273_k };
	SpeedDensityConfiguration config{ tcharge };

	SpeedDensity sd(configCommon, config, &rpm, &map, &iat, &clt);

	QFrequency x = 1000_Rpm;
	QPressure p = 100_kpa;

	rpm.Set({ true, (float)x.getValue() });
	map.Set({ true, (float)p.getValue() });
	iat.Set({ true, 273.15f });
	clt.Set({ true, 273.15f });

	auto airflow = sd.EstimateAirflow();

	ASSERT_NEAR(0.0244f, airflow.TotalMassFlowRate.getValue(), 0.001f);
}
