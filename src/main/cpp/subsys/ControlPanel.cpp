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


#include <vector>
#include <memory>
#include <string>

#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/ControlPanel.h>

#include <frc/util/color.h>
#include <rev/ColorMatch.h>
#include <rev/ColorSensorV3.h>

#include <hw/interfaces/IDragonMotorController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <utils/logger.h>
#include <rev/ColorSensorV3.h>

using namespace std;
using namespace frc;
using namespace rev;

ControlPanel::ControlPanel
(
    std::shared_ptr<IDragonMotorController>     motorController,
    std::shared_ptr<DragonSolenoid>             solenoid,
    ColorSensorV3*                              colorSensor
) : Mech1IndMotor( MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR, 
                   string("controlpanel.xml"), 
                   string("ControlPanelNT"), 
                   move(motorController) ),
    Mech1Solenoid(solenoid),
    m_color( colorSensor ),
    m_colorMatcher( new ColorMatch())
{
    m_colorMatcher->AddColorMatch(kBlueTarget);
    m_colorMatcher->AddColorMatch(kGreenTarget);
    m_colorMatcher->AddColorMatch(kRedTarget);
    m_colorMatcher->AddColorMatch(kYellowTarget);
}


ControlPanelColors::COLOR ControlPanel::GetColorSeen()
{
    frc::Color detectedColor = m_color->GetColor();
    //uint32_t detectedProximity = m_color->GetProximity();
    //std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher->MatchClosestColor(detectedColor, confidence);
    if(matchedColor == kGreenTarget && confidence >= 0.94 )
    {
        return ControlPanelColors::COLOR::BLUE;
    }
    else if(matchedColor == kBlueTarget && confidence >= 0.94 )
    {
        return ControlPanelColors::COLOR::GREEN;
    }
    else if(matchedColor == kYellowTarget && confidence >= 0.9 )
    {
        return ControlPanelColors::COLOR::YELLOW;
    }
    else if(matchedColor == kBlueTarget && confidence >= 0.9 )
    {
        return ControlPanelColors::COLOR::RED;
    }
    return ControlPanelColors::COLOR::UNKNOWN;
}