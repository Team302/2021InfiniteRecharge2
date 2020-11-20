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
#include <states/shooterHood/ShooterHoodManual.h>
#include <states/Mech1MotorState.h>
#include <subsys/MechanismFactory.h>

using namespace std;

ShooterHoodManual::ShooterHoodManual
(
    ControlData* control,
    double target
 ) : Mech1MotorState( MechanismFactory::GetMechanismFactory()->GetShooterHood().get(), control, target )
{
}

void ShooterHoodManual::Init()
{
    auto gamepad = TeleopControl::GetInstance();
    if ( gamepad != nullptr )
    {
        gamepad ->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_AXIS, IDragonGamePad::AXIS_PROFILE::CUBED );
        gamepad ->SetAxisScaleFactor( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_AXIS, 0.75 );
    }
}

void ShooterHoodManual::Run()
{
    auto mech = MechanismFactory::GetMechanismFactory()->GetHookDelivery();
    auto gamepad = TeleopControl::GetInstance();
    if ( mech.get() != nullptr && gamepad != nullptr )
    {
        mech.get()->UpdateTarget(gamepad->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_AXIS ));
        mech.get()->Update();
    }
}
