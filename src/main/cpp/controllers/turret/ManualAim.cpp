/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/turret/ManualAim.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/Turret.h"
#include "controllers/ControlData.h"
#include "gamepad/TeleopControl.h"
ManualAim::ManualAim(ControlData* controlData) : m_controlData(controlData), 
    m_atTarget(false)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_turret = factory->GetIMechanism(MechanismTypes::TURRET);
}

void ManualAim::Init()
{

}

void ManualAim::Run()
{
    m_turret->SetOutput(m_controlData->GetMode(), TeleopControl::GetInstance()->GetAxisValue(TeleopControl::SHOOTER_MANUAL_AIM) * 5.0); //scaled to a percentage of a 45 degree turn
    m_atTarget = true;
}

bool ManualAim::AtTarget() const
{
    return m_atTarget;
}
