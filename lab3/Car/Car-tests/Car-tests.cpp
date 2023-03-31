// Car-tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"
#include "sstream"

using namespace std;

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

		REQUIRE(car.SetGear(1));

		REQUIRE(!car.TurnOffEngine());

		REQUIRE(car.SetSpeed(25));

		CHECK(!car.TurnOffEngine());
	}


	SECTION("Check with off engine")
	{
		Car car;
		CHECK(car.TurnOffEngine());
	}
}

SCENARIO("SetGear and SetSpeed functions tests")
{
	SECTION("Check with off engine")
	{
		Car car;
		CHECK(!car.SetSpeed(1));
		CHECK(!car.SetGear(1));
	}

	SECTION("Check with on engine and adequate speed or gear")
	{
		Car car;
		car.TurnOnEngine();
		CHECK(car.SetGear(0));
		CHECK(car.SetGear(-1));

		REQUIRE(car.SetGear(1));
		REQUIRE(car.SetSpeed(25));

		REQUIRE(car.SetGear(2));
		REQUIRE(car.SetSpeed(45));

		REQUIRE(car.SetGear(4));
		REQUIRE(car.SetSpeed(60));

		REQUIRE(car.SetGear(5));

		CHECK(car.SetGear(0));

	}

	SECTION("Check with on engine and not adequate speed or gear")
	{
		Car car;
		car.TurnOnEngine();
		CHECK(!car.SetGear(2));

		CHECK(car.SetGear(1));
		REQUIRE(car.SetSpeed(2));
		CHECK(!car.SetGear(-1));

		REQUIRE(car.SetSpeed(0));
		REQUIRE(car.SetGear(-1));

		REQUIRE(car.SetSpeed(20));
		REQUIRE(!car.SetSpeed(21));
		CHECK(!car.SetGear(1));

		REQUIRE(car.SetGear(0));
		REQUIRE(!car.SetGear(-1));

		REQUIRE(car.SetSpeed(0));

		REQUIRE(car.GetDirection() == 0);

		REQUIRE(car.SetGear(1));
		REQUIRE(car.SetSpeed(30));
		REQUIRE(!car.SetSpeed(31));

		REQUIRE(car.SetGear(2));
		REQUIRE(car.SetSpeed(50));
		REQUIRE(!car.SetSpeed(51));
		REQUIRE(!car.SetSpeed(19));

		REQUIRE(car.SetGear(3));
		REQUIRE(car.SetSpeed(60));
		REQUIRE(!car.SetSpeed(61));
		REQUIRE(!car.SetSpeed(29));

		REQUIRE(car.SetGear(4));
		REQUIRE(car.SetSpeed(90));
		REQUIRE(!car.SetSpeed(91));
		REQUIRE(!car.SetSpeed(39));

		REQUIRE(car.SetGear(5));
		REQUIRE(car.SetSpeed(150));
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
		CHECK(car.GetDirection() == 0);
	}

	SECTION("Check with reverse gear and not zero speed")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.SetSpeed(5));
		CHECK(car.GetDirection() == -1);
	}

	SECTION("Check with forward gear and not zero speed")
	{
		Car car;
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.SetSpeed(5));
		CHECK(car.GetDirection() == 1);
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
		REQUIRE(car.SetGear(1));
		REQUIRE(car.SetSpeed(5));
		CHECK(car.GetSpeed() == 5);
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
		REQUIRE(car.SetGear(1));
		CHECK(car.GetGear() == 1);
	}
}