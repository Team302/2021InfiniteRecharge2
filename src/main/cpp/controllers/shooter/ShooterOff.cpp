/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/shooter/ShooterOff.h"
#include "controllers/ControlData.h"
#include "controllers/ControlModes.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/MechanismTypes.h"
#include "controllers/MechanismState.h"

ShooterOff::ShooterOff
(
    ControlData* controlData, 
    double target
) : MechanismState(MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER), controlData, target)
{}

/*void ShooterOff::Init()
{
    m_shooter->SetControlConstants(m_controlData);
}

void ShooterOff::Run()
{
    m_shooter->SetOutput(m_controlData->GetMode(), m_target);
    m_atTarget = true;
}

bool ShooterOff::AtTarget() const
{
    return m_atTarget;
}
*/
