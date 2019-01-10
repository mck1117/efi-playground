
#include <gasoline/IAirflowEstimator.h>
#include <gasoline/GasolineFuelComputer.h>

class GasolineEngine
{
private:
    IAirflowEstimator* const m_airflowEstimator;
    GasolineFuelComputer* const m_fuelComputer;

    // Set by fast callback
    // consumed by injection scheduling
    GasolineFuelResult m_currentFuel;
public:
    GasolineEngine(IAirflowEstimator* airflowEstimator, GasolineFuelComputer* fuelComputer);

    void FastCallback();
};
