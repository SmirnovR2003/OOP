#pragma once

#include <map>

struct SpeedLimit
{
	int lowerBound;
	int upperBound;
};
//������� m_
enum class Direction
{
	back,
	inPlace,
	forward
};

class Car
{
public:
	Car();

	~Car(); //������ ����������

	bool TurnOnEngine();

	bool TurnOffEngine();

	bool SetGear(int gear);

	bool SetSpeed(int speed);

	bool IsTurnedOn()const;

	Direction GetDirection()const;//���������� enum

	int GetSpeed()const;

	int GetGear()const;

	std::pair<int, int> GetSpeedsBariersWithCurrentGear()const;//��������������


private:

	int m_gear;

	int m_speed;

	Direction m_direction;

	bool m_isTurnedOnEngine;

	bool SetSpeedWithGearIsZero(int newSpeed);

	bool SetSpeedWithGearFromOneToFiveOrIsMinusOne(int newSpeed);

	bool SetGearWithNewGearIsOne(int newGear);

	bool SetGearWithNewGearIsMinusOne(int newGear);

};


