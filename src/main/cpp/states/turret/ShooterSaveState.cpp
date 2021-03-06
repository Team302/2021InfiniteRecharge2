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

// FRC includes

// Team 302 includes
#include <controllers/ControlData.h>
#include <states/turret/HoldTurretPosition.h>
#include <states/Mech1MotorState.h>
#include <subsys/MechanismFactory.h>

#include <states/turret/ShooterSaveState.h>

// Third Party Includes



ShooterSaveState::ShooterSaveState
(
    ControlData*    control,
    double          target
) : Mech1MotorState( MechanismFactory::GetMechanismFactory()->GetTurret().get(), control, target ),
    m_target( target )

{
    m_turret = MechanismFactory::GetMechanismFactory()->GetTurret();
}
 

void ShooterSaveState::Init()
{
    m_turret.get()->SetControlConstants( m_control );
}

void ShooterSaveState::Run()           
{
    m_turret.get()->Update();
}


bool ShooterSaveState::AtTarget() const                                 //confirms that it worked
{
    return ( (m_turret.get()->GetPosition() >= (m_target - 5) &&  m_turret->GetPosition() <= (m_target + 5) ) );
}