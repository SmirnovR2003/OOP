// VolumetricBodies_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../../catch2/catch.hpp"
#include "../VolumetricBodies/CBody.h"
#include "../VolumetricBodies/CCompound.h"
#include "../VolumetricBodies/CCone.h"
#include "../VolumetricBodies/CCylinder.h"
#include "../VolumetricBodies/CParallelepiped.h"
#include "../VolumetricBodies/CSPhere.h"
using namespace std;


SCENARIO("CCone tests")
{
	SECTION("Check with norm base radius, height and density")
	{
		Approx expectedMass = Approx(523333.34).epsilon(0.01);
		Approx expectedVolume = Approx(523.33).epsilon(0.01);
		CCone cone(10, 5, 1000);
		CHECK(cone.GetBaseRadius() == 10);
		CHECK(cone.GetHeight() == 5);
		CHECK(cone.GetDensity() == 1000);
		CHECK(cone.GetMass() == expectedMass);
		CHECK(cone.GetVolume() == expectedVolume);
		CHECK(cone.ToString() == "Cone:\n\tdensity = 1000\n\tvolume = 523.3333333\n\tmass = 523333.3333\n\tbase radius = 10\n\theight = 5\n");
	}

	SECTION("Check with base radius, height and density less then zero")
	{
		CCone cone(-1, -1, -1);
		CHECK(cone.GetBaseRadius() == 0.0);
		CHECK(cone.GetHeight() == 0.0);
		CHECK(cone.GetDensity() == 0.0);
		CHECK(cone.GetMass() == 0.0);
		CHECK(cone.GetVolume() == 0.0);
		CHECK(cone.ToString() == "Cone:\n\tdensity = 0\n\tvolume = 0\n\tmass = 0\n\tbase radius = 0\n\theight = 0\n");
	}
}

SCENARIO("CCylinder tests")
{
	SECTION("Check with norm base radius, height and density")
	{
		CCylinder cylinder(10, 5, 1000);
		CHECK(cylinder.GetBaseRadius() == 10);
		CHECK(cylinder.GetHeight() == 5);
		CHECK(cylinder.GetDensity() == 1000);
		CHECK(cylinder.GetMass() == 1570000);
		CHECK(cylinder.GetVolume() == 1570);
		CHECK(cylinder.ToString() == "Cylinder:\n\tdensity = 1000\n\tvolume = 1570\n\tmass = 1570000\n\tbase radius = 10\n\theight = 5\n");
	}

	SECTION("Check with base radius, height and density less then zero")
	{
		CCylinder cylinder(-1, -1, -1);
		CHECK(cylinder.GetBaseRadius() == 0.0);
		CHECK(cylinder.GetHeight() == 0.0);
		CHECK(cylinder.GetDensity() == 0.0);
		CHECK(cylinder.GetMass() == 0.0);
		CHECK(cylinder.GetVolume() == 0.0);
		CHECK(cylinder.ToString() == "Cylinder:\n\tdensity = 0\n\tvolume = 0\n\tmass = 0\n\tbase radius = 0\n\theight = 0\n");
	}
}

SCENARIO("CParallelepiped tests")
{
	SECTION("Check with norm depth, height, width and density")
	{
		CParallelepiped parallelepiped(10, 5, 5, 1000);
		CHECK(parallelepiped.GetHeight() == 10);
		CHECK(parallelepiped.GetDepth() == 5);
		CHECK(parallelepiped.GetWidth() == 5);
		CHECK(parallelepiped.GetDensity() == 1000);
		CHECK(parallelepiped.GetMass() == 250000);
		CHECK(parallelepiped.GetVolume() == 250);
		CHECK(parallelepiped.ToString() == "Parallelepiped:\n\tdensity = 1000\n\tvolume = 250\n\tmass = 250000\n\theight = 10\n\twidth = 5\n\tdepth = 5\n");
	}

	SECTION("Check with depth, height, width and density less then zero")
	{
		CParallelepiped parallelepiped(-1, -1, -1, -1);
		CHECK(parallelepiped.GetHeight() == 0.0);
		CHECK(parallelepiped.GetDepth() == 0.0);
		CHECK(parallelepiped.GetWidth() == 0.0);
		CHECK(parallelepiped.GetDensity() == 0.0);
		CHECK(parallelepiped.GetMass() == 0.0);
		CHECK(parallelepiped.GetVolume() == 0.0);
		CHECK(parallelepiped.ToString() == "Parallelepiped:\n\tdensity = 0\n\tvolume = 0\n\tmass = 0\n\theight = 0\n\twidth = 0\n\tdepth = 0\n");
	}
}

SCENARIO("CSphere tests")
{
	SECTION("Check with norm depth, height, width and density")
	{
		Approx expectedMass = Approx(4186666.67).epsilon(0.01);
		Approx expectedVolume = Approx(4186.67).epsilon(0.01);
		CSphere sphere(10, 1000);
		CHECK(sphere.GetRadius() == 10);
		CHECK(sphere.GetDensity() == 1000);
		CHECK(sphere.GetMass() == expectedMass);
		CHECK(sphere.GetVolume() == expectedVolume);
		CHECK(sphere.ToString() == "Sphere:\n\tdensity = 1000\n\tvolume = 4186.666667\n\tmass = 4186666.667\n\tradius = 10\n");
	}

	SECTION("Check with depth, height, width and density less then zero")
	{
		CSphere sphere(-1, -1);
		CHECK(sphere.GetRadius() == 0);
		CHECK(sphere.GetDensity() == 0.0);
		CHECK(sphere.GetMass() == 0.0);
		CHECK(sphere.GetVolume() == 0.0);
		CHECK(sphere.ToString() == "Sphere:\n\tdensity = 0\n\tvolume = 0\n\tmass = 0\n\tradius = 0\n");
	}
}

SCENARIO("CCompound tests")
{
	SECTION("Check with empty compound body")
	{
		CCompound compoundBody;
		CHECK(isnan(compoundBody.GetDensity()));
		CHECK(compoundBody.GetMass() == 0);
		CHECK(compoundBody.GetVolume() == 0);
		CHECK(compoundBody.ToString() == "Compound:\n\tdensity = -nan(ind)\n\tvolume = 0\n\tmass = 0\n");
	}

	SECTION("Check with compound body with some shapes in compound body")
	{
		CCompound compoundBody1, compoundBody2;
		CCone cone(1, 1, 1000);
		CCylinder cylinder(1, 1, 1000);
		CParallelepiped parallelepiped(1, 1, 1, 800);

		compoundBody2.AddChildBody(*(new shared_ptr<CBody>(&cone)));
		compoundBody2.AddChildBody(*(new shared_ptr<CBody>(&cylinder)));
		compoundBody1.AddChildBody(*(new shared_ptr<CBody>(&compoundBody2)));
		compoundBody1.AddChildBody(*(new shared_ptr<CBody>(&parallelepiped)));

		Approx expectedMass = Approx(4986.67).epsilon(0.01);
		Approx expectedVolume = Approx(5.19).epsilon(0.01);
		Approx expectedDensity = Approx(961.44).epsilon(0.01);

		CHECK(compoundBody1.GetDensity() == expectedDensity);
		CHECK(compoundBody1.GetMass() == expectedMass);
		CHECK(compoundBody1.GetVolume() == expectedVolume);
		CHECK(compoundBody1.ToString() == R"(Compound:
	density = 961.4395887
	volume = 5.186666667
	mass = 4986.666667
	Compound:
		density = 1000
		volume = 4.186666667
		mass = 4186.666667
		Cone:
			density = 1000
			volume = 1.046666667
			mass = 1046.666667
			base radius = 1
			height = 1
		Cylinder:
			density = 1000
			volume = 3.14
			mass = 3140
			base radius = 1
			height = 1
	Parallelepiped:
		density = 800
		volume = 1
		mass = 800
		height = 1
		width = 1
		depth = 1
)");
	}

}



