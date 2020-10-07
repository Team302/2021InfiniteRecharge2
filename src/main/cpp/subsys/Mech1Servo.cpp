
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
#include <hw/DragonServo.h>
#include <subsys/Mech1Servo.h>
#include <subsys/IMech1Servo.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;

/// @brief Create a generic mechanism wiht 1 servo 
/// @param [in] MechanismTypes::MECHANISM_TYPE the type of mechansim
/// @param [in] std::string the name of the file that will set control parameters for this mechanism
/// @param [in] std::string the name of the network table for logging information
/// @param [in] std::shared_ptr<DragonServo> servo used by this mechanism
Mech1Servo::Mech1Servo
(
    MechanismTypes::MECHANISM_TYPE              type,
    std::string                                 controlFileName,
    std::string                                 networkTableName,
    std::shared_ptr<DragonServo>                servo
) : IMech1Servo(),
    m_servo(std::move(servo)) 
{
    if (m_servo.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Mech1Servo constructor" ), string( "servo is nullptr" ) );
    }
}

/// @brief          Indicates the type of mechanism this is
/// @return         MechanismTypes::MECHANISM_TYPE
MechanismTypes::MECHANISM_TYPE Mech1Servo::GetType() const 
{
    return m_type;
}

/// @brief indicate the file used to get the control parameters from
/// @return std::string the name of the file 
std::string Mech1Servo::GetControlFileName() const 
{
    return m_controlFile;
}


/// @brief indicate the network table name used to for logging parameters
/// @return std::string the name of the network table 
std::string Mech1Servo::GetNetworkTableName() const 
{
    return m_ntName;
}


/// @brief      Move servo to the desired angle
/// @param [in] double angle: Target angle in degrees
/// @return     void
void Mech1Servo::SetAngle
(
    double angle       
) 
{
    if ( m_servo.get() != nullptr )
    {
        m_servo.get()->SetAngle( angle );
    }
}






