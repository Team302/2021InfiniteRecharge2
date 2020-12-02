///@class Climber
///@brief The Climber subsystem. Includes pneumatic extender and winch.

//C++ Includes
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <subsys/Climber.h>
#include <hw/DragonSolenoid.h>
#include <hw/interfaces/IDragonMotorController.h>

// Third Party Includes
using namespace std;

///@brief Create and initialize the Climber sub-mechanism
///@param [in] std::shared_ptr<IDragonMotorController>  masterMotor - motor for Climber
///@param [in] std::shared_ptr<DragonSolenoid>  masterSolenoid - solenoid for Climber
///@param [in] double   winchDiameter - The diameter of winch in inches.
Climber::Climber
(
    shared_ptr<IDragonMotorController>             motorController,
    shared_ptr<DragonSolenoid>                     solenoid,
    double                                         winchDiameter
) : Mech1IndMotor( MechanismTypes::MECHANISM_TYPE::CLIMBER,  string("climber.xml"),  string("ClimberNT"), motorController ),
    Mech1Solenoid(solenoid),
    m_winchDiameter( winchDiameter)
{
}


///@brief Return the current position of the climber in inches
///@return double   position in inches (positive is forward, negative is backward)
double Climber::GetPosition() const
{
    double distance = ( m_winchDiameter * M_PI);
    auto nRotations = Mech1IndMotor::GetPosition() / 360.0;    // degrees to rotations
    distance *= nRotations;

    return distance;
}

///@brief return the current speed of the climber in degrees per second.
///@return double   speed in degrees per second
double Climber::GetSpeed() const
{
    auto rps = Mech1IndMotor::GetSpeed();    // number of rotations per second
    auto speed = ( m_winchDiameter * M_PI ); // distance the wheel travels per revolution (inches)
    speed *= rps;                            // distance per revolution * revolutions per second is inches per second
    return speed;
}

