#pragma once

template<typename TValue>
struct SensorResult
{
    bool Valid;
    TValue Value;
};

template <typename TValue>
class SensorHolder;

class ISensor
{
	template <typename TValue>
	friend class SensorHolder;
protected:
    virtual SensorResult<float> Get() const = 0;
};

template <typename TValue>
class SensorHolder
{
private:
	const ISensor* m_sensor;

public:
	explicit SensorHolder(const ISensor* sensor)
		: m_sensor(sensor)
	{
	}

	SensorResult<TValue> Get() const
	{
		if (m_sensor)
		{
			SensorResult<float> raw = m_sensor->Get();

			return { raw.Valid, raw.Value };
		}
		else
		{
			return { false, 0.0f };
		}
	}

	TValue GetOrDefault(TValue defaultValue) const
	{
		SensorResult<TValue> raw = Get();
		
		if (raw.Valid)
		{
			return raw.Value;
		}
		else
		{
			return defaultValue;
		}
	}
};

class MockSensor final : public ISensor
{
protected:
	SensorResult<float> m_value{ false, 0.0f };

public:
	void Set(SensorResult<float> value)
	{
		m_value = value;
	}

	virtual SensorResult<float> Get() const
	{
		return m_value;
	}
};
