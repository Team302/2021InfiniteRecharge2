#pragma once

//C++ Includes
#include <memory>

//Team 302 includes
#include <subsys/Mech1IndMotor.h>
#include <subsys/Mech1Solenoid.h>

// Third Party Includes

class IDragonMotorController;
class DragonSolenoid;

///@class Climber
///@brief This is the climber sub-system
class Climber : public Mech1IndMotor , public Mech1Solenoid
{
    public:

        ///@brief   Create and initialize the Climber sub-mechanism
        ///@param [in] std::shared_ptr<IDragonMotorController>   masterMotor - master motor for the Climber
        ///@param [in] std::shared_ptr<DragonSolenoid>  masterSolenoid - master solenoid for the Climber
        ///@param [in] double   **
        Climber
        (
            std::shared_ptr<IDragonMotorController>          masterMotor,
            std::shared_ptr<DragonSolenoid>                  masterSolenoid,
            double                                           winchDiameter
        );
        Climber() = delete;
        ///@brief Clean up memory when this object gets deleted
        virtual ~Climber() = default;



        ///@brief Return the current position of the climber in inches (positive is forward, negative is backward)
        ///@return  double position in inches
        double GetPosition() const override;

        ///@brief Return the current position of the climber in inches (positive is forward, negative is backward)
        ///@return double speed in inches
        double GetSpeed() const override;


    private:
        double                                              m_winchDiameter;
};
