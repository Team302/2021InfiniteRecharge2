//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


#include "subsys/Shooter.h"
#include "hw/interfaces/IDragonMotorController.h"
#include "subsys/MechanismTypes.h"
#include "controllers/ControlModes.h"

using namespace std;

Shooter::Shooter
(
    std::shared_ptr<IDragonMotorController> motor1,
    std::shared_ptr<IDragonMotorController> motor2
) : Mech2IndMotors( MechanismTypes::MECHANISM_TYPE::SHOOTER, string( "shooter.xml") , string("BallTransferNT"), motor1, motor2 )
{

}

/**
MechanismTypes::MECHANISM_TYPE Shooter::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::SHOOTER;
}

void Shooter::SetOutput(ControlModes::CONTROL_TYPE controlType, double value)
{
    switch(controlType)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_targetSpeed = value;
            break;
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            m_targetSpeed = value;
            break;
        default:
            break;
        
    }
    m_topMotor.get()->SetControlMode(controlType);
    m_bottomMotor.get()->SetControlMode(controlType);
    m_topMotor.get()->Set(value);
    m_bottomMotor.get()->Set(value);
}

void Shooter::SetOutput(ControlModes::CONTROL_TYPE controlType, double upperValue, double lowerValue)
{
    switch(controlType)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_targetSpeed1 = upperValue;
            m_targetSpeed2 = lowerValue;
            break;
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            m_targetSpeed1 = upperValue;
            m_targetSpeed2 = lowerValue;
            break;
        default:
            break;
    }
    m_topMotor.get()->SetControlMode(controlType);
    m_bottomMotor.get()->SetControlMode(controlType);
    m_topMotor.get()->Set(upperValue);
    m_bottomMotor.get()->Set(lowerValue);
}

void Shooter::ActivateSolenoid(bool activate)
{}

bool Shooter::IsSolenoidActivated()
{
    return false;
}

double Shooter::GetCurrentPosition() const
{
    return m_topMotor.get()->GetRotations() * 360.0;
}

double Shooter::GetCurrentSpeed() const 
{
    return m_topMotor.get()->GetRPS();
}


void Shooter::SetControlConstants(ControlData* pid)
{
    m_topMotor.get()->SetControlConstants(pid);
    m_bottomMotor.get()->SetControlConstants(pid);
}
**/
