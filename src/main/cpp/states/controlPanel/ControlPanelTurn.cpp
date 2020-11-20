#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <states/controlPanel/ControlPanelTurn.h>
#include <controllers/ControlData.h>

ControlPanelTurn::ControlPanelTurn(ControlData* control_data, double target)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_controlPanel = factory -> GetControlPanel();  

    m_target = target;
    m_control_data = control_data;
}

// Creates the desired target location for the spin to end at

void ControlPanelTurn::Init()
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_controlPanel = factory -> GetControlPanel();
    m_target = m_controlPanel.get() -> GetPosition() + m_offset;
}

// Spins the wheel to the target

void ControlPanelTurn::Run()
{
    m_controlPanel.get()->Update();
}

// Performs a check to see if the panel has been spun to the target point yet

bool ControlPanelTurn::AtTarget() const
{
    return (m_controlPanel.get() -> GetPosition() >= m_target );
}