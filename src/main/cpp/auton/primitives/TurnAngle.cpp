
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
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

// FRC includes
#include <frc/Timer.h>

// Team 302 includes
#include <auton/primitives/TurnAngle.h>
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <subsys/ChassisFactory.h>
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>
#include <subsys/IChassis.h>
#include <utils/Logger.h>
#include <hw/factories/PigeonFactory.h>
#include <hw/DragonPigeon.h>

// Third Party Includes


using namespace std;
using namespace frc;

//Team302 includes

TurnAngle::TurnAngle() : m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
						 m_timer( make_unique<Timer>() ),
						 m_targetAngle(0.0),
						 m_maxTime(0.0),
						 m_leftPos(0.0),
						 m_rightPos(0.0),
						 m_isDone(false),
						 m_control(nullptr),
						 m_turnRight(true)
{
}
TurnAngle::TurnAngle
(
	ControlData* 	control
) : m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
	m_timer( make_unique<Timer>() ),
	m_targetAngle(0.0),
	m_maxTime(0.0),
	m_leftPos(0.0),
	m_rightPos(0.0),
	m_isDone(false),
	m_control(control),
	m_turnRight(true)
{
}

void TurnAngle::Init(PrimitiveParams* params) 
{
	m_isDone = false;

	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto startHeading = pigeon != nullptr ? pigeon->GetYaw() : 0.0;
	auto angle = params->GetHeading();

	auto isRelative = params->GetID() == TURN_ANGLE_REL;
	m_targetAngle = isRelative ? (startHeading + angle) : angle;
	auto delta = isRelative ? angle : (startHeading - m_targetAngle);
	m_turnRight = delta > 0.0;
	
	auto turningRadius = m_chassis->GetTrack() / 2.0;
	auto arcLen = ((2.0 * M_PI * turningRadius) * delta) / 360.0;
	m_leftPos = m_chassis->GetCurrentLeftPosition() + arcLen;
	m_rightPos = m_chassis->GetCurrentRightPosition() - arcLen;


	if ( m_control == nullptr )
	{
		m_control = new ControlData( ControlModes::CONTROL_TYPE::POSITION_INCH, 
									 ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER,
									 string("TurnAngle"),
									 3.0,
									 0.0,
									 0.0,
									 0.0,
									 0.0,
									 0.0,
									 0.0,
									 1.0,
									 0.0   );
	}
	m_chassis->SetControlConstants( m_control );
	m_chassis->SetOutput( m_control->GetMode(), m_leftPos, m_rightPos );

	m_maxTime = params->GetTime();
	m_timer->Reset();
	m_timer->Start();
}

void TurnAngle::Run() 
{
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto heading = ( pigeon != nullptr ) ? pigeon->GetYaw() : 0.0;
	
	auto delta = heading - m_targetAngle;
	auto passedTarget = ( delta > 0.0 ) ? m_turnRight : !m_turnRight;

	double leftspeed = 0.0;
	double rightspeed = 0.0;
	m_isDone = ( abs(delta)  < ANGLE_THRESH );
	if ( m_isDone )
	{
		auto currLeftPos = m_chassis->GetCurrentLeftPosition();
		auto currRightPos = m_chassis->GetCurrentRightPosition();

		m_isDone = (( abs(currLeftPos - m_leftPos) < ANGLE_THRESH ) && (abs(currRightPos - m_rightPos) < ANGLE_THRESH ));
		
		if ( m_isDone && abs(delta) > ANGLE_THRESH )  // drive distance is done, but angle isn't correct
		{
			if ( m_turnRight && !passedTarget )
			{
				leftspeed = passedTarget ? -0.2 : 0.2;
				rightspeed = passedTarget ? 0.2 : -0.2;
			}
			else 
			{
				leftspeed = passedTarget ? 0.2 : -0.2;
				rightspeed = passedTarget ? -0.2 : 0.2;
			}

		}
	}
	m_chassis->SetOutput( ControlModes::PERCENT_OUTPUT, leftspeed, rightspeed );
}

bool TurnAngle::IsDone() 
{
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto heading = ( pigeon != nullptr ) ? pigeon->GetYaw() : 0.0;
	
	auto delta = heading - m_targetAngle;
	auto isDone = ( abs(delta)  < ANGLE_THRESH );

	return isDone || m_timer->HasPeriodPassed( m_maxTime );
}
