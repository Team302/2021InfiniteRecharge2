#pragma once

#include <frc/GenericHID.h>
#include <frc/Joystick.h>

#include <gamepad/IDragonGamePad.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/IButton.h>

using namespace frc;
using namespace std;

class DragonDrumset : public IDragonGamePad
{
    public:
        DragonDrumset
        (
            int port
        );
        ~DragonDrumset();

        bool IsButtonPressed
        (
            BUTTON_IDENTIFIER button
        ) const override;

        void SetAxisDeadband
        (
            AXIS_IDENTIFIER axis,
            AXIS_DEADBAND type
        ) override;

        void SetAxisProfile
        (
            AXIS_IDENTIFIER axis,
            AXIS_PROFILE curve
        ) override;

        void SetAxisScale
        (
            AXIS_IDENTIFIER axis,
            float scaleFactor
        ) override;

        void SetButtonMode
        (
            BUTTON_IDENTIFIER button,
            BUTTON_MODE mode
        ) override;

        double GetAxisValue
        (
            AXIS_IDENTIFIER axis
        ) const override;

        bool WasButtonPressed
        (
            BUTTON_IDENTIFIER button
        ) const override;

        bool WasButtonReleased
        (
            BUTTON_IDENTIFIER button
        ) const override;

        private:
            Joystick* m_gamepad;

            vector<AnalogAxis*> m_axis;
            vector <float> m_axisScale;
            vector <float> m_axisInversionFactor;
            vector <AXIS_PROFILE> m_axisProfile;
            vector <IButton*> m_button;

            const int RED_PAD_DIGITAL_ID = 0;
            const int YELLOW_PAD_DIGITAL_ID = 1;
            const int BLUE_PAD_DIGITAL_ID = 2;
            const int GREEN_PAD_DIGITAL_ID = 3;

            const int X_BUTTON_DIGITAL_ID = 4;
            const int SQUARE_BUTTON_DIGITAL_ID = 5;
            const int TRIANGLE_BUTTON_DIGITAL_ID = 6;
            const int CIRCLE_BUTTON_DIGITAL_ID = 7;

        DragonDrumset() = delete;
};