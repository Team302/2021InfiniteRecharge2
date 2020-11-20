#pragma once

#include <states/Mech1MotorState.h>
#include <controllers/MechanismTargetData.h>

class ControlData;

class ShooterHoodManual : public Mech1MotorState
{
    public:
    ShooterHoodManual
    (
        ControlData* control,
        double target
    );
    ShooterHoodManual() = delete;
    ~ShooterHoodManual() = default;

    void Init() override;
    void Run() override;
};