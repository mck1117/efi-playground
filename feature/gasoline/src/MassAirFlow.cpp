#include <gasoline/MassAirFlow.h>

massrate_t MassAirFlow::GetMassFlowRate()
{
	return m_maf.GetOrDefault(massrate_t(0.0f));
}
