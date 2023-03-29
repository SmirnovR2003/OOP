#pragma once

#include <map>

struct SpeedLimit
{
	int lowerBound;
	int upperBound;
};

class Car
{
public:
	Car();

	~Car();

	bool TurnOnEngine();

	bool TurnOffEngine();

	bool SetGear(int gear);

	bool SetSpeed(int speed);

	bool IsTurnedOn()const;

	int GetDirection()const;

	int GetSpeed()const;

	int GetGear()const;

	std::pair<int, int> GetSpeedsInGear()const;


private:

	int gear;

	int speed;

	int direction;

	bool isTurnedOnEngine;

	bool SetSpeedWithGearIsZero(int newSpeed);

	bool SetSpeedWithCommonGear(int newSpeed);

	bool SetGearWithNewGearIsOne(int newGear);

	bool SetGearWithNewGearIsMinusOne(int newGear);

};


