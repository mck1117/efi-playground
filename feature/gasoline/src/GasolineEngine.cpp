#include <gasoline/GasolineEngine.h>

GasolineEngine::GasolineEngine(IAirflowEstimator* airflowEstimator, GasolineFuelComputer* fuelComputer)
    : m_airflowEstimator(airflowEstimator)
    , m_fuelComputer(fuelComputer)
{

}

void GasolineEngine::FastCallback()
{
    // Compute fuel
    AirflowEstimate airflow = m_airflowEstimator->EstimateAirflow();
    m_currentFuel = m_fuelComputer->ComputeFuel(airflow);

    //// compute spark
    // m_currentSpark = m_sparkComputer->ComputeSpark(airflow);
}
