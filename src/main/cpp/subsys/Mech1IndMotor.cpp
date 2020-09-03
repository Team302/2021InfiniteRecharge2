//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
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

// FRC includes

// Team 302 includes
#include <controllers/ControlData.h>
#include <subsys/Mech1IndMotor.h>
#include <subsys/IMech1IndMotor.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;

Mech1IndMotor::Mech1IndMotor

(
    std::unique_ptr<IDragonMotorController>     motorController
) : m_motor( std::move(motorController) ),
    m_target( 0.0 )
{
    if (m_motor.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Mech1IndMotor constructor" ), string( "motorController is nullptr" ) );
    }
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





