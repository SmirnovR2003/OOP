#include "Car.h"
#include <map>

using namespace std;


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
:gear(0)
,speed(0)
,direction(0)
,isTurnedOnEngine(false)
{
}

Car::~Car()
{
}

bool Car::TurnOnEngine()
{
	if (!isTurnedOnEngine) 
	{
		isTurnedOnEngine = true;
	}
	return isTurnedOnEngine;
}

bool Car::TurnOffEngine()
{
	if (isTurnedOnEngine && speed == 0 && direction == 0 && gear == 0)
	{
		isTurnedOnEngine = false;
	}
	return !isTurnedOnEngine;
}

bool Car::SetGear(int newGear)
{
	if (!isTurnedOnEngine)
	{
		return false;
	}

	if (newGear < -1 || newGear > 5)
	{
		return false;
	}

	if (newGear == 0)
	{
		gear = newGear;
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
		speed >= speedLimit.lowerBound && speed <= speedLimit.upperBound)
	{
		gear = newGear;
		return true;
	}

	return false;
	
}

bool Car::SetGearWithNewGearIsMinusOne(int newGear)
{
	if (gear == -1 || speed == 0)
	{
		gear = newGear;
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetGearWithNewGearIsOne(int newGear)
{
	if (direction == 0 || direction == 1)
	{
		gear = newGear;
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetSpeed(int newSpeed)
{
	if (!isTurnedOnEngine)
	{
		return false;
	}

	if (newSpeed < 0)
	{
		return false;
	}

	if (gear == 0)
	{
		return SetSpeedWithGearIsZero(newSpeed);
	}

	return SetSpeedWithCommonGear(newSpeed);
}

bool Car::SetSpeedWithGearIsZero(int newSpeed)
{
	if (newSpeed < speed)
	{
		speed = newSpeed;
		if (speed == 0) direction = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool Car::SetSpeedWithCommonGear(int newSpeed)
{
	if (SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(gear)->second;
		newSpeed >= speedLimit.lowerBound && newSpeed <= speedLimit.upperBound)
	{
		speed = newSpeed;

		(speed == 0) ? direction = 0
			: (gear == -1) ? direction = -1
			: direction = 1;

		return true;
	}
	return false;
}

bool Car::IsTurnedOn() const
{
	return isTurnedOnEngine;
}

int Car::GetDirection() const
{
	return direction;
}

int Car::GetSpeed() const
{
	return speed;
}

int Car::GetGear() const
{
	return gear;
}

pair<int, int> Car::GetSpeedsInGear()const
{
	if (gear == 0)
	{
		return { };
	}
	SpeedLimit speedLimit = SPEEDS_IN_GEARS.find(gear)->second; 

	return { speedLimit.lowerBound, speedLimit.upperBound };
}

