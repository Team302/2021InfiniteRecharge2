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
#include <frc2/Timer.h>

// Team 302 includes
#include <controllers/ControlData.h>
#include <subsys/Mech1IndMotor.h>
#include <subsys/IMech1IndMotor.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>

// Third Party Includes
#include <units/units.h>

using namespace frc2;
using namespace std;

/// @brief Create a generic mechanism wiht 1 independent motor 
/// @param [in] MechanismTypes::MECHANISM_TYPE the type of mechansim
/// @param [in] std::string the name of the file that will set control parameters for this mechanism
/// @param [in] std::string the name of the network table for logging information
/// @param [in] std::shared_ptr<IDragonMotorController> motor controller used by this mechanism
Mech1IndMotor::Mech1IndMotor

(
    MechanismTypes::MECHANISM_TYPE              type,
    std::string                                 controlFileName,
    std::string                                 networkTableName,
    std::shared_ptr<IDragonMotorController>     motorController
) : m_motor( std::move(motorController) ),
    m_target( 0.0 )
{
    if (m_motor.get() == nullptr )
    {
        Logger::GetLogger()->LogError( Logger::LOGGER_LEVEL::ERROR_ONCE, string( "Mech1IndMotor constructor" ), string( "motorController is nullptr" ) );
    }
}

/// @brief          Indicates the type of mechanism this is
/// @return         MechanismTypes::MECHANISM_TYPE
MechanismTypes::MECHANISM_TYPE Mech1IndMotor::GetType() const 
{
    return m_type;
}

/// @brief indicate the file used to get the control parameters from
/// @return std::string the name of the file 
std::string Mech1IndMotor::GetControlFileName() const 
{
    return m_controlFile;
}


/// @brief indicate the network table name used to for logging parameters
/// @return std::string the name of the network table 
std::string Mech1IndMotor::GetNetworkTableName() const 
{
    return m_ntName;
}

/// @brief Activates logging key values to network table
/// @param [in] int: indicate how many millisecondsBetweenLogging updates to the network table 
void Mech1IndMotor::ActivateLogging
(
    units::second_t     millisecondsBetweenLogging
) 
{
    m_milliSecondsBetweenLogging = millisecondsBetweenLogging;
    m_logging = true;
}

/// @brief log data to the network table if it is activated and time period has past
void Mech1IndMotor::LogData()
{
    if(m_logging)
    {
        auto currentTime = m_timer.get()->GetFPGATimestamp();
        if ((currentTime - m_lastTime) > m_milliSecondsBetweenLogging )
        {
            // TODO:  update the network table
        }

    }
}
/// @brief Stop updating the key values to network table
void Mech1IndMotor::DeactivateLogging() 
{
    m_logging = false;
}

void Mech1IndMotor::Update()
{
    if ( m_motor.get() != nullptr )
    {
        m_motor.get()->Set( m_target );
    }
}

void Mech1IndMotor::UpdateTarget
(
    double  target
)
{
    m_target = target;
    Update();
}


double Mech1IndMotor::GetPosition() const

{
    return m_motor.get()->GetRotations() * 360.0;
}



double Mech1IndMotor::GetSpeed() const

{
    return m_motor.get()->GetRPS();
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData* pid:  the control constants
/// @return void
void Mech1IndMotor::SetControlConstants
(
    ControlData*                                pid                 
)
{
    if ( m_motor.get() != nullptr )
    {
        m_motor.get()->SetControlConstants( pid );
    }
}





