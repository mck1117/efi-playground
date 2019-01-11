#include <can/CanInterface.h>
#include <core/sensors/ISensor.h>
#include <gasoline/GasolineEngine.h>
#include <gasoline/SpeedDensity.h>


int main(int argc, char** argv)
{
    MockSensor clt;
    MockSensor iat;
    MockSensor rpm;
    MockSensor map;
    // wire together components here


    // Set up sending sensors over CAN
    CanInterface can;
    can.RegisterSensor(0x100, 10, &clt);
    can.RegisterSensor(0x101, 10, &iat);
    can.RegisterSensor(0x102, 25, &map);
    can.RegisterSensor(0x103, 25, &rpm);

    // can.Start();

    // Here's the neat part: remote CAN sensors don't know about the engine,
    // and vice versa.  If we wanted a "CAN sensor board", we could omit the
    // below parts for the engine, and only ever send sensors over CAN.

    // Set up speed density
    Table2Data<massrate_t, Number, 8> tchargedata;
    Table2d<massrate_t, Number, 8> tcharge(tchargedata);

    // these tables/config would come from tune config
    AirflowEstimatorConfiguration configCommon{ QVolume(2.316 * litre / 4), 2, 273_k, 273_k };
    SpeedDensityConfiguration config{ tcharge };

    SpeedDensity sd(configCommon, config, &rpm, &map, &iat, &clt);

    // Set up fuel computation
    GasolineInjectionConfiguration gasConfig{ Number(14.1) }; // stoich for E10 gas is ~14.1:1
    GasolineFuelComputer fuel(gasConfig);

    GasolineEngine engine(&sd, &fuel);

    // Engine could be a PeriodicController, as already exists
    // Start periodically updating fuel&spark computation
    // engine.Start();


}
