#include <gtest/gtest.h>

#include <gasoline/SpeedDensity.h>
#include <gasoline/MassAirFlow.h>

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

	SpeedDensityConfiguration config{ QVolume(2.3 * litre), 2, 273_k, 273_k, tcharge };

	SpeedDensity sd(config, &rpm, &map, &iat, &clt);

	QFrequency x = 1000_Rpm;
	QPressure p = 100_kpa;

	rpm.Set({ true, (float)x.getValue() });
	map.Set({ true, (float)p.getValue() });
	iat.Set({ true, 273.15f });
	clt.Set({ true, 273.15f });

	massrate_t rate = sd.GetMassFlowRate();

	ASSERT_NEAR(0.0244f, rate.getValue(), 0.001f);
}

class MafTest : public ::testing::Test
{
protected:
	MockSensor rpm;
	MockSensor maf;
	MockSensor iat;
};

TEST_F(MafTest, test2)
{
	MassAirFlowConfiguration config{};

	MassAirFlow mf(config, &maf, &rpm, &iat);

	rpm.Set({ true, (float)(1000_Rpm).getValue() });
	maf.Set({ true, (float)(40_g / second).getValue() });
	iat.Set({ true, 273.15f });

	massrate_t rate = mf.GetMassFlowRate();

	ASSERT_NEAR(0.040f, rate.getValue(), 0.001f);
}
