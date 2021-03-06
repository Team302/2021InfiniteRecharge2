#pragma once
#include <states/IState.h>
#include <subsys/MechanismFactory.h>
#include <controllers/ControlData.h>

class ControlPanelTurn : public IState
{
    public:
    ControlPanelTurn(ControlData* control_data, double target);
    ControlPanelTurn() = delete;
    ~ControlPanelTurn() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const override;

    private:

    std::shared_ptr<ControlPanel> m_controlPanel;
    double m_target;
    ControlData* m_control_data;
    double m_offset;
    double m_current_position;

};