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
#pragma once

// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <subsys/Mech1IndMotor.h>
#include <subsys/Mech1Solenoid.h>
#include <utils/ControlPanelColors.h>

// Third Party Includes
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

class IDragonMotorController;
class DragonSolenoid;


class ControlPanel : public Mech1IndMotor, public Mech1Solenoid
{
    public:
        
        ControlPanel
        (
            std::shared_ptr<IDragonMotorController>             motorcontroller,
            std::shared_ptr<DragonSolenoid>                     solenoid,
            rev::ColorSensorV3*                                 colorSensor
        );
        ControlPanel() = delete;

	    virtual ~ControlPanel() = default;

        ControlPanelColors::COLOR GetColorSeen();
    private:
        rev::ColorSensorV3*                         m_color;
        rev::ColorMatch*                            m_colorMatcher;

        static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
        static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
        static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
        static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
};