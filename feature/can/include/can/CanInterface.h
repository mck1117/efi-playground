#include <cstdint>
#include <core/sensors/ISensor.h>

class CanInterface
{
public:
    void RegisterSensor(uint16_t frameId, uint8_t frequency, ISensor* sensor) {}
};
