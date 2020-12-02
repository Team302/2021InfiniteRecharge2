
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


// C++ Includes
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <subsys/Impeller.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/ConversionUtils.h>
#include <utils/Logger.h>

// Third Party Includes
#include <ctre/phoenix/sensors/CANCoder.h>

using namespace std;
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::motorcontrol;



Impeller::Impeller
(
    shared_ptr<IDragonMotorController> motor,
    shared_ptr<CANCoder> encoder
) : Mech1IndMotor( MechanismTypes::MECHANISM_TYPE::IMPELLER,  string("impeller.xml"),  string("ImpellerNT"),  motor ),
    m_encoder( encoder )
{
    if ( motor.get() != nullptr )
    {
        if ( encoder.get() != nullptr )
        {
            motor.get()->SetRemoteSensor( encoder.get()->GetDeviceNumber(), RemoteSensorSource::RemoteSensorSource_CANCoder );
        }
        else
        {
            Logger::GetLogger()->LogError( string("Impeller::Impeller"), string("No encoder"));
        }
    }
    else
    {
        Logger::GetLogger()->LogError( string("Impeller::Impeller"), string("No motor"));
    }

}

/// @brief  Return the current position of the mechanism.  The value is in inches or degrees.
/// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
double Impeller::GetPosition() const
{
    return m_encoder.get() != nullptr ? m_encoder.get()->GetAbsolutePosition() : 0.0;
}


/// @brief  Get the current speed of the mechanism.  The value is in degrees per second.
/// @return double	speed in degrees/second (rotating mechanisms)
double Impeller::GetSpeed() const
{
    return m_encoder.get() != nullptr ? m_encoder.get()->GetVelocity()*10.0 : 0.0;
}

