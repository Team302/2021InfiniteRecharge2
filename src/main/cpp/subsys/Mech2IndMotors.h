
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
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

#pragma once


// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <subsys/Mech1IndMotor.h>
#include <subsys/IMech2IndMotors.h>

// Third Party Includes

class ControlData;
class IDragonMotorController;

class Mech2IndMotors : public IMech2IndMotors
{
	public:
        /// @brief update the output to the mechanism using the current controller and target value(s)
        /// @return void 
        void Update() override;

        void UpdateTargets
        (
            double      primary,
            double      secondary
        ) override;

        /// @brief  Return the current position of the primary motor in the mechanism.  The value is in inches or degrees.
        /// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
        double GetPrimaryPosition() const override;

        /// @brief  Return the current position of the secondary motor in the mechanism.  The value is in inches or degrees.
        /// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
        double GetSecondaryPosition() const override;

        /// @brief  Get the current speed of the primary motor in the mechanism.  The value is in inches per second or degrees per second.
        /// @return double	speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms)
        double GetPrimarySpeed() const override;

        /// @brief  Get the current speed of the secondary motor in the mechanism.  The value is in inches per second or degrees per second.
        /// @return double	speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms)
        double GetSecondarySpeed() const override;

        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*                                   pid:  the control constants
        /// @return void
        void SetControlConstants
        (
            ControlData*                                pid                 
        ) override;

        Mech2IndMotors
        (
            std::unique_ptr<IDragonMotorController>     primaryMotor,
            std::unique_ptr<IDragonMotorController>     secondaryMotor
        );
	    Mech2IndMotors() = delete;
	    ~Mech2IndMotors() = default;

    private: 
        std::unique_ptr<Mech1IndMotor>         m_primary;
        std::unique_ptr<Mech1IndMotor>         m_secondary;
        
};



