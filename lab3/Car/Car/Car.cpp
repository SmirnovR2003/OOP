#include "Car.h"
#include <map>

using namespace std;

const int MAX_GEAR = 5;
const int MIN_GEAR = -1;

const map<int, SpeedLimit> SPEEDS_IN_GEARS
{
	{-1, {0, 20}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}
};

Car::Car()
: m_gear(0)
, m_speed(0)
, m_direction(Direction::inPlace)
, m_isTurnedOnEngine(false)
{
}

Car::~Car()
{
}

bool Car::TurnOnEngine()
{
	m_isTurnedOnEngine = true;
	return m_isTurnedOnEngine;
}

bool Car::TurnOffEngine()
{
	if (m_isTurnedOnEngine && m_speed == 0 && m_direction == Direction::inPlace && m_gear == 0)
	{
		m_isTurnedOnEngine = false;
	}
	return !m_isTurnedOnEngine;
}

bool Car::SetGear(int newGear)
{
	if (!m_isTurnedOnEngine)
	{
		return false;
	}

	//не использовать магических констант
	if (newGear < MIN_GEAR || newGear > MAX_GEAR)
	{
		return false;
	}

	if (newGear == 0)
	{
		m_gear = newGear;
		return true;
	}

	if (newGear == -1)
	{
		return SetGearWithNewGearIsMinusOne(newGear);	
	}

	if (newGear == 1)
	{
		return SetGearWithNewGearIsOne(newGear);
	}

	if (SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(newGear)->second;
		m_speed >= speedLimit.lowerBound && m_speed <= speedLimit.upperBound && m_direction == Direction::forward)
	{
		m_gear = newGear;
		return true;
	}

	return false;
	
}

bool Car::SetGearWithNewGearIsMinusOne(int newGear)
{
	if (m_gear == -1 || m_speed == 0)
	{
		m_gear = newGear;
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetGearWithNewGearIsOne(int newGear)
{
	if (SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(newGear)->second;
		m_speed >= speedLimit.lowerBound && m_speed <= speedLimit.upperBound 
		&& (m_direction == Direction::inPlace || m_direction == Direction::forward))
	{
		m_gear = newGear;
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetSpeed(int newSpeed)
{
	if (!m_isTurnedOnEngine)
	{
		return false;
	}

	if (newSpeed < 0)
	{
		return false;
	}

	if (m_gear == 0)
	{
		return SetSpeedWithGearIsZero(newSpeed);
	}

	return SetSpeedWithGearFromOneToFiveOrIsMinusOne(newSpeed);
}

bool Car::SetSpeedWithGearIsZero(int newSpeed)
{
	if (newSpeed < m_speed)
	{
		m_speed = newSpeed;
		if (m_speed == 0) m_direction = Direction::inPlace;
		return true;
	}
	else
	{
		return false;
	}
}

//при чтении не понятно что такое CommonGear 
bool Car::SetSpeedWithGearFromOneToFiveOrIsMinusOne(int newSpeed)
{
	if (SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(m_gear)->second;
		newSpeed >= speedLimit.lowerBound && newSpeed <= speedLimit.upperBound)
	{
		m_speed = newSpeed;

		(m_speed == 0) ? m_direction = Direction::inPlace
			: (m_gear == -1) ? m_direction = Direction::back
			: m_direction = Direction::forward;

		return true;
	}
	return false;
}

bool Car::IsTurnedOn() const
{
	return m_isTurnedOnEngine;
}

Direction Car::GetDirection() const
{
	return m_direction ;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

pair<int, int> Car::GetSpeedsBariersWithCurrentGear()const//тесты
{
	if (m_gear == 0)
	{
		return {0, 0};
	}
	SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(m_gear)->second;

	return { speedLimit.lowerBound, speedLimit.upperBound };
}

