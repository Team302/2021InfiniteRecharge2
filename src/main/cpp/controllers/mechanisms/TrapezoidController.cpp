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

//C++ includes
#include <memory>
#include <string>

//Team 302 includes
#include <controllers/mechanisms/IMechController.h>
#include <controllers/mechanisms/TrapezoidController.h>
#include <controllers/ControlData.h>
#include <utils/Logger.h>

using namespace std;

TrapezoidController::TrapezoidController
(
    shared_ptr<IDragonMotorController>      motor,
    double                                  target,
    shared_ptr<ControlData>                 controlData
) : IMechController(),
    m_motor ( motor ),
    m_target( target ),
    m_control( controlData )
{
    if (m_motor.get() == nullptr )
    {
        Logger::GetLogger()->LogError( Logger::ERROR_ONCE, "Trapezoid Controller constructor", "Motor is a nullptr");
    }
    if (m_control.get() == nullptr )
    {
        Logger::GetLogger()->LogError( Logger::ERROR_ONCE, "Trapzoid Controller constructor", "ControlData is a nullptr");
    }
}

void TrapezoidController::Init()
{
    if ( m_motor.get() != nullptr && m_control.get() != nullptr )
    {
        m_motor.get()->SetControlConstants( m_control.get() );
        m_motor.get()->SetControlMode( m_control.get()->GetMode() );
    }
    Run();

}

void TrapezoidController::UpdateTarget
(
    double target
)
{
    m_target = target;
}

void TrapezoidController::Run()
{
    if( m_motor.get() != nullptr )
    {
        m_motor.get()->Set( m_target );
    }
}