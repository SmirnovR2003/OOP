// Car-tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"
#include "sstream"

using namespace std;

bool SetAndCheckGear(Car& car, int newGear)
{
	if (!car.SetGear(newGear))
	{
		return false;
	}
	if (car.GetGear() != newGear)
	{
		return false;
	}
	return true;
}

bool SetAndCheckSpeed(Car& car, int newSpeed)
{
	if (!car.SetSpeed(newSpeed))
	{
		return false;
	}
	if (car.GetSpeed() != newSpeed)
	{
		return false;
	}
	return true;
}

SCENARIO("TurnOnEngine function tests")
{
	SECTION("Check with on engine")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		CHECK(car.TurnOnEngine());
	}

	SECTION("Check with off engine")
	{
		Car car;
		CHECK(car.TurnOnEngine());
	}
}

SCENARIO("TurnOffEngine function tests")
{
	SECTION("Check with on engine")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		CHECK(car.TurnOffEngine());
	}

	SECTION("Check with on engine and not zero speed and not zero gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());

		REQUIRE(SetAndCheckGear(car, 1));

		REQUIRE(!car.TurnOffEngine());

		REQUIRE(SetAndCheckSpeed(car, 25));

		CHECK(!car.TurnOffEngine());

	}


	SECTION("Check with off engine")
	{
		Car car;
		CHECK(car.TurnOffEngine());
	}
}

//недьзя переключить на 2 передачу с задней 20
//исправить ^Z

SCENARIO("SetGear and SetSpeed functions tests")
{
	SECTION("Check with off engine")
	{
		Car car;
		REQUIRE(!SetAndCheckSpeed(car, 1));
		REQUIRE(!SetAndCheckGear(car, 1));
	}

	SECTION("Check with on engine and adequate speed or gear")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE(SetAndCheckGear(car, 0));
		REQUIRE(SetAndCheckGear(car, -1));

		REQUIRE(SetAndCheckGear(car, 1));
		REQUIRE(SetAndCheckSpeed(car, 25));

		REQUIRE(SetAndCheckGear(car, 2));
		REQUIRE(SetAndCheckSpeed(car, 45));

		REQUIRE(SetAndCheckGear(car, 4));
		REQUIRE(SetAndCheckSpeed(car, 60));

		REQUIRE(SetAndCheckGear(car, 5));
		REQUIRE(SetAndCheckSpeed(car, 100));

		REQUIRE(SetAndCheckGear(car, 0));
		REQUIRE(SetAndCheckSpeed(car, 60));
	}

	SECTION("Check with on engine and not adequate speed or gear")
	{
		Car car;
		car.TurnOnEngine();
		CHECK(!car.SetGear(2));

		REQUIRE(SetAndCheckGear(car, 1));
		REQUIRE(SetAndCheckSpeed(car, 2));

		CHECK(!car.SetGear(-1));

		REQUIRE(SetAndCheckSpeed(car, 0));
		REQUIRE(SetAndCheckGear(car, -1));

		REQUIRE(SetAndCheckSpeed(car, 20));
		REQUIRE(!car.SetSpeed(21));
		CHECK(!car.SetGear(1));
		CHECK(!car.SetGear(2));

		REQUIRE(SetAndCheckGear(car, 0));
		REQUIRE(!car.SetGear(-1));

		REQUIRE(SetAndCheckSpeed(car, 0));

		REQUIRE(car.GetDirection() == Direction::inPlace);

		REQUIRE(SetAndCheckGear(car, 1));
		REQUIRE(SetAndCheckSpeed(car, 30));
		REQUIRE(!SetAndCheckSpeed(car, 31));

		REQUIRE(SetAndCheckGear(car, 2));
		REQUIRE(SetAndCheckSpeed(car, 50));
		REQUIRE(!car.SetSpeed(51));
		REQUIRE(!car.SetSpeed(19));

		REQUIRE(SetAndCheckGear(car, 3));
		REQUIRE(SetAndCheckSpeed(car, 60));
		REQUIRE(!car.SetSpeed(61));
		REQUIRE(!car.SetSpeed(29));

		REQUIRE(SetAndCheckGear(car, 4));
		REQUIRE(SetAndCheckSpeed(car, 90));
		REQUIRE(!car.SetSpeed(91));
		REQUIRE(!car.SetSpeed(39));

		REQUIRE(SetAndCheckGear(car, 5));
		REQUIRE(SetAndCheckSpeed(car, 150));
		REQUIRE(!car.SetSpeed(151));
		REQUIRE(!car.SetSpeed(49));
	}
}

SCENARIO("IsTurnedOn function tests")
{
	SECTION("Check with on engine")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		CHECK(car.IsTurnedOn());
	}

	SECTION("Check with off engine")
	{
		Car car;
		CHECK(!car.IsTurnedOn());
	}
}

SCENARIO("GetDirection function tests")
{
	SECTION("Check with default direction")
	{
		Car car;
		CHECK(car.GetDirection() == Direction::inPlace);
	}

	SECTION("Check with reverse gear and not zero speed")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(SetAndCheckGear(car, -1));
		REQUIRE(SetAndCheckSpeed(car, 5));
		CHECK(car.GetDirection() == Direction::back);
	}

	SECTION("Check with forward gear and not zero speed")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(SetAndCheckGear(car, 1));
		REQUIRE(SetAndCheckSpeed(car, 5));
		CHECK(car.GetDirection() == Direction::forward);
	}
}

SCENARIO("GetSpeed function tests")
{
	SECTION("Check with default speed")
	{
		Car car;
		CHECK(car.GetSpeed() == 0);
	}

	SECTION("Check with not zero speed")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(SetAndCheckGear(car, -1));
		REQUIRE(SetAndCheckSpeed(car, 5));
	}
}

SCENARIO("GetGear function tests")
{
	SECTION("Check with default gear")
	{
		Car car;
		CHECK(car.GetGear() == 0);
	}

	SECTION("Check with not zero gear")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(SetAndCheckGear(car, -1));
		REQUIRE(SetAndCheckGear(car, 1));
	}
}