//====================================================================================================================================================
/// Copyright 2020 Lake Orion Robotics FIRST Team 302 
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <controllers/ControlData.h>
#include <gamepad/TeleopControl.h>
#include <gamepad/IDragonGamePad.h>
#include <states/turret/ManualAim.h>
#include <states/Mech1MotorState.h>
#include <subsys/MechanismFactory.h>
#include <subsys/Turret.h>

using namespace std;


ManualAim::ManualAim
(
    ControlData* controlData
) : Mech1MotorState( MechanismFactory::GetMechanismFactory()->GetTurret().get(), controlData, 0.0 ),
    m_controlData(controlData), 
    m_atTarget(false)
{
    m_turret = MechanismFactory::GetMechanismFactory()->GetTurret();
}

void ManualAim::Init()
{
    TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_AXIS, IDragonGamePad::AXIS_PROFILE::CUBED);
    TeleopControl::GetInstance()->SetAxisScaleFactor(TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_AXIS, 0.75);
}

void ManualAim::Run()
{
    double val = TeleopControl::GetInstance()->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_AXIS);
    m_turret.get()->UpdateTarget(val);
    m_turret.get()->Update();
    m_atTarget = true;
}

bool ManualAim::AtTarget() const
{
    return m_atTarget;
}
