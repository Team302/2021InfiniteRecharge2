
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
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <auton/primitives/TurnAngle.h>
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>
#include <hw/DragonPigeon.h>
#include <hw/factories/PigeonFactory.h>
#include <subsys/ChassisFactory.h>
#include <subsys/IChassis.h>
#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;

//Team302 includes

/// @brief construct a Turn Angle primitive that takes in control data.
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

/// @brief construct a Turn Angle primitive that takes in control data.
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


/// @brief initialize the primitive with a new set of parameters
/// @param [in] PrimitiveParams* parameters to use for the primitive
void TurnAngle::Init
(
	PrimitiveParams* params
) 
{
	m_isDone = false;

	// get the current angle (heading) of the robot
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto startHeading = pigeon != nullptr ? pigeon->GetYaw() : 0.0;
	auto angle = params->GetHeading();

	// if relative, add the angle to the current heading to get a target
	// if absolute, the target angle is what was specified
	auto isRelative = params->GetID() == TURN_ANGLE_REL;
	m_targetAngle = isRelative ? (startHeading + angle) : angle;
	auto delta = isRelative ? angle : (startHeading - m_targetAngle);
	m_turnRight = delta > 0.0;
	
	// figure out how far each side of the robot needs to move to turn in place (circle/arc) in order to reach
	// the angle.   So, 2 * PI * radius is the distance a wheel would travel to turn 360 degrees.  
	// Thus, to travel 90 degrees, the wheel would need to move a quarter of this distance (90/360).
	// This won't be entirely accurate because of scrub and slippage, the encoder may show a slightly different distance
	// but we'll use this to get approximately there and then use the gyro and a slow speed to finish it up. 
	auto turningRadius = m_chassis->GetTrack() / 2.0;
	auto arcLen = ((2.0 * M_PI * turningRadius) * delta) / 360.0;
	m_leftPos = m_chassis->GetCurrentLeftPosition() + arcLen;
	m_rightPos = m_chassis->GetCurrentRightPosition() - arcLen;

	// Set the output to the wheels
	m_chassis->SetControlConstants( m_control );
	m_chassis->SetOutput( m_control->GetMode(), m_leftPos, m_rightPos );

	// Get the timeout and start a timer (we may hit something that prevents us from getting to the angle)
	m_maxTime = params->GetTime();
	m_timer->Reset();
	m_timer->Start();
}

/// @brief execute the primitive (call from periodic methods)
void TurnAngle::Run() 
{
	// Check the pigeon to see if we've reached the target, if we have set m_isDone to true and the speeds to 0.0
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto heading = ( pigeon != nullptr ) ? pigeon->GetYaw() : 0.0;

	auto delta = heading - m_targetAngle;
	m_isDone = ( abs(delta)  < ANGLE_THRESH );
	if ( !m_isDone )
	{	
		auto currLeftPos = m_chassis->GetCurrentLeftPosition();
		auto currRightPos = m_chassis->GetCurrentRightPosition();

		auto distReached = (( abs(currLeftPos - m_leftPos) < ANGLE_THRESH ) && (abs(currRightPos - m_rightPos) < ANGLE_THRESH ));
		
		// if the distance has been reached but the angle has been reach (only way we got here)
		// use a slow speed (percent output), to get the last little bit
		if ( distReached )  
		{
			// if the target angle hasn't been reached, make the robot hasn't turned too far, if it has turn the opposite way
			double leftspeed = 0.0;
			double rightspeed = 0.0;
			auto passedTarget = ( delta > 0.0 ) ? m_turnRight : !m_turnRight;

			if ( m_turnRight && !passedTarget )
			{
				leftspeed = passedTarget ? -1.0 * SLOW_PERCENT : SLOW_PERCENT;
				rightspeed = passedTarget ? SLOW_PERCENT : -1.0 * SLOW_PERCENT;
			}
			else 
			{
				leftspeed = passedTarget ? SLOW_PERCENT : -1.0 * SLOW_PERCENT;
				rightspeed = passedTarget ? -1.0 * SLOW_PERCENT : SLOW_PERCENT;
			}
			m_chassis->SetOutput( ControlModes::PERCENT_OUTPUT, leftspeed, rightspeed );
		}
	}
	else
	{
		m_chassis->SetOutput( ControlModes::PERCENT_OUTPUT, 0.0, 0.0 );
	}
}

/// @brief Check if the robot has reached its target angle
/// @returns bool: true - reached target (or timed out), false - still going to target
bool TurnAngle::IsDone() 
{
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	auto heading = ( pigeon != nullptr ) ? pigeon->GetYaw() : 0.0;
	
	auto delta = heading - m_targetAngle;
	auto isDone = ( abs(delta)  < ANGLE_THRESH );

	return isDone || m_timer->HasPeriodPassed( m_maxTime );
}
