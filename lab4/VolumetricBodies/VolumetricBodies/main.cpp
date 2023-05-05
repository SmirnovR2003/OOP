#include <iostream>
#include "CBody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include <iterator>
#include <limits>

using namespace std;

const int waterDensity = 1000;

shared_ptr<CBody>* ReadFigure(string& answer);

shared_ptr<CBody>* ReadCone()
{
    double baseRadius = 0.0, height = 0.0, density = 0.0;
    cout << "Enter base radius:";
    cin >> baseRadius;
    cout << "Enter height:";
    cin >> height;
    cout << "Enter density:";
    cin >> density;
    auto cone = new shared_ptr<CBody>(new CCone(baseRadius, height, density));
    return cone;
}

shared_ptr<CBody>* ReadCylinder()
{
    double baseRadius = 0.0, height = 0.0, density = 0.0;
    cout << "Enter base radius:";
    cin >> baseRadius;
    cout << "Enter height:";
    cin >> height;
    cout << "Enter density:";
    cin >> density;
    auto cylinder = new shared_ptr<CBody>(new CCylinder(baseRadius, height, density));
    return cylinder;
}

shared_ptr<CBody>* ReadParallelepiped()
{
    double height = 0.0, width = 0.0, depth = 0.0, density = 0.0;
    cout << "Enter height:";
    cin >> height;
    cout << "Enter width:";
    cin >> width;
    cout << "Enter depth:";
    cin >> depth;
    cout << "Enter density:";
    cin >> density;
    auto parallelepiped = new shared_ptr<CBody>(new CParallelepiped(height, width, depth, density));
    return parallelepiped;
}

shared_ptr<CBody>* ReadSphere()
{
    double radius = 0.0, density = 0.0;
    cout << "Enter radius:";
    cin >> radius;
    cout << "Enter density:";
    cin >> density;
    auto sphere = new shared_ptr<CBody>(new CSphere(radius, density));
    return sphere;
}

shared_ptr<CBody>* ReadCompound()
{
    string answer;
    CCompound* compoundBody = new CCompound();
    cout << "To finish reading shapes, enter the 'stop' command\n";
    while (cout << "Enter the shape type or 'stop'\n>" && cin >> answer)
    {
        auto figure = ReadFigure(answer);
        if (answer == "stop")
        {
            break;
        }
        else if (figure->get())
        {
            compoundBody->AddChildBody(*figure);
        }
        else
        {
            cout << "The command is not identified";
        }
    }
    auto returnBody = new shared_ptr<CBody>(compoundBody);
    return  returnBody;
}

shared_ptr<CBody>* ReadFigure(string& answer)
{   
    if (answer == "cone")
    {
        return ReadCone();
    }
    else if (answer == "cylinder")
    {
        return ReadCylinder();
    }
    else if (answer == "parallelepiped")
    {
        return ReadParallelepiped();
    }
    else if (answer == "sphere")
    {
        return ReadSphere();
    }
    else if (answer == "compound")
    {
        return ReadCompound();
    }
    else 
    {
        shared_ptr<CBody>* figure = new shared_ptr<CBody>(nullptr);
        return figure;
    }
}

void ReadShapes(vector<shared_ptr<CBody>>& bodies)
{
    string answer;
    cout << "To finish reading shapes, enter the 'stop' command\n";
    while (cout << "Enter the shape type or 'stop'\n>" && cin >> answer)
    {
        auto figure = ReadFigure(answer);
        if (figure->get())
        {
            bodies.push_back(*figure);
        }
        else if (answer == "stop")
        {
            return;
        }
        else
        {
            cout << "The command is not identified";
        }
    }
}

void ShowShapesInfo(vector<shared_ptr<CBody>>& bodies)
{
    for (auto& body : bodies)
    {
        cout << body.get()->ToString();
    }
}

void FindAndShowShapeWithMinMassInWater(const vector<shared_ptr<CBody>>& bodies)
{
    shared_ptr<CBody> shapeWithMinMassInWater;
    double shapeWithMinMassInWaterGravity = numeric_limits<double>::max();
    for (const auto& body : bodies)
    {
        if (double gravity = (body.get()->GetDensity() - waterDensity) * body.get()->GetVolume();
            gravity < shapeWithMinMassInWaterGravity)
        {
            shapeWithMinMassInWater = body;
            shapeWithMinMassInWaterGravity = gravity;
        }
    }

    cout << "Shape with min mass in water:\n";
    cout << shapeWithMinMassInWater.get()->ToString();
}

void FindAndShowShapeWithMaxMass(const vector<shared_ptr<CBody>>& bodies)
{
    shared_ptr<CBody> shapeWithMaxMass;
    double shapeWithMaxMassMass = numeric_limits<double>::min();
    for (const auto& body : bodies)
    {
        if (double mass = body.get()->GetMass();
            mass > shapeWithMaxMassMass)
        {
            shapeWithMaxMass = body;
            shapeWithMaxMassMass = mass;
        }
    }

    cout << "Shape with max mass:\n";
    cout << shapeWithMaxMass.get()->ToString();
}

int main()
{
    /*vector<shared_ptr<CBody>> bodies;

    ReadShapes(bodies);
    ShowShapesInfo(bodies);
    FindAndShowShapeWithMaxMass(bodies);
    FindAndShowShapeWithMinMassInWater(bodies);*/
    CCompound compoundBody;
    (!compoundBody.AddChildBody(make_shared<CCompound>(compoundBody)));
}

