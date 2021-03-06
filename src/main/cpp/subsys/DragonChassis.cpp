
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
#include <subsys/DragonChassis.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <subsys/interfaces/IChassis.h>
#include <controllers/ControlModes.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlData.h>
#include <subsys/DriveTrainSide.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;
using namespace frc;

/// @class DragonChassis
/// @brief This is a differential chassis.  Each side of the robot will be treated as a separate mechanism

/// @brief Create the subobjects and initialize the DragonChassis subsystem
DragonChassis::DragonChassis
(
    double 						                            wheelDiameter,		
    double 					    	                        wheelBase,			
    double 						                            track,				
    std::shared_ptr<IDragonMotorController>                 leftMaster,
    std::shared_ptr<IDragonMotorController>                 rightMaster,
    std::shared_ptr<IDragonMotorController>                 leftFollower,
    std::shared_ptr<IDragonMotorController>                 rightFollower
) : m_leftSide( make_unique<DriveTrainSide>( leftMaster, leftFollower, wheelDiameter ) ),
    m_rightSide( make_unique<DriveTrainSide>( rightMaster, rightFollower, wheelDiameter ) ),
    m_wheelBase( wheelBase ),
    m_wheelTrack( track ),
    m_wheelDiameter( wheelDiameter )
{
}

/// @brief clean up memory when this object gets deleted
DragonChassis::~DragonChassis()
{
}


/// @brief      Run chassis 
/// @param [in] ControlModes::CONTROL_TYPE   controlType:  How are the item(s) being controlled
/// @param [in] double                                     leftVvalue:   Left side target (units are based on the controlType)
/// @param [in] double                                     rightValue:   Right side target (units are based on the controlType)
/// @return     void
void DragonChassis::SetOutput
(
    ControlModes::CONTROL_TYPE controlType,
    double                                   leftValue,
    double                                   rightValue     
)
{
    if ( controlType != m_controlMode )
    {
        // todo deal with control mode
        m_controlMode = controlType;
    }
    m_leftSide.get()->UpdateTarget( leftValue );
    m_rightSide.get()->UpdateTarget( rightValue );

    m_leftSide.get()->Update();
    m_rightSide.get()->Update();
}


/// @brief  Return the current position of the center of the DragonChassis in inches.  
/// @return double  position in inches of the center of the chassis
double DragonChassis::GetCurrentPosition() const
{
    return ( m_leftSide.get()->GetPosition() + m_rightSide.get()->GetPosition() ) / 2.0;
}

/// @brief  Return the current position of the left side of the DragonChassis in inches.  
/// @return double  position in inches of the left side of the chassis
double DragonChassis::GetCurrentLeftPosition() const
{
    return m_leftSide.get()->GetPosition();
}

/// @brief  Return the current position of the right side of the DragonChassis in inches.  
/// @return double  position in inches of the right side of the chassis
double DragonChassis::GetCurrentRightPosition() const
{
    return m_rightSide.get()->GetPosition();
}



/// @brief  Return the current speed of the center of the DragonChassis in inches per second.  
/// @return double  speed in inches per second of the center of the chassis
double DragonChassis::GetCurrentSpeed() const
{
    return ( m_leftSide.get()->GetSpeed() + m_rightSide.get()->GetSpeed() ) / 2.0;
}

/// @brief  Return the current speed of the left side of the DragonChassis in inches per second.  
/// @return double  speed in inches per second of the left side of the chassis
double DragonChassis::GetCurrentLeftSpeed() const
{
    return m_leftSide.get()->GetSpeed();
}

/// @brief  Return the current speed of the right side of the DragonChassis in inches per second.  
/// @return double  speed in inches per second of the right side of the chassis
double DragonChassis::GetCurrentRightSpeed() const
{
    return m_rightSide.get()->GetSpeed();
}




/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*   pid - the control constants
/// @return void
void DragonChassis::SetControlConstants
(
    ControlData*                                 pid               
)
{
    m_controlMode = pid->GetMode();
    m_leftSide.get()->SetControlConstants( pid );
    m_rightSide.get()->SetControlConstants( pid );
}

double DragonChassis::GetWheelDiameter() const
{ 
    return m_wheelDiameter; 
}

double DragonChassis::GetWheelBase() const 
{
    return m_wheelBase;
}
double DragonChassis::GetTrack() const 
{
    return m_wheelTrack;
}




