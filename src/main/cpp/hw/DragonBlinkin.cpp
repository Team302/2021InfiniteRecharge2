//====================================================================================================================================================
/// Copyright 2020 Lake Orion Robotics FIRST Team 302 
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

//C++ Includes
#include <memory>

//Team302
#include <hw/DragonBlinkin.h>

//Third Party Includes
#include <frc/SpeedController.h>
#include <frc/Spark.h>

/// @brief Create Dragon Blinkin
/// @param [in] channel which PWM channel we want the new Spark motor to ues
DragonBlinkin::DragonBlinkin
(
    int channel
)

{
    /// @brief Sets the channel for a new Spark motor
    /// @param [in] channel Sets which PWM channel the spark uses
    m_spark = std::make_shared<frc::Spark>(channel);
}

void DragonBlinkin::Set(blinkinColor color)
        {
            double PWMValue = 0;

            //Documentation for blinkin and color table https://www.revrobotics.com/content/docs/REV-11-1105-UM.pdf
            ///@brief color uses different blinkinColor types to control LED color
            switch(color) 
            {
                case GREEN:
                    PWMValue = 0.77;  //Green is 0.77
                    break;
                case WHITE:
                    PWMValue = 0.93;
                    break;
                case BLUE:
                    PWMValue = 0.87;
                    break;
                case RED:
                    PWMValue = 0.61;
                    break;
                default:
                    //log that an unknown color was used
                    break;
            }
            ///@brief sets the LED's to color specified by the switch statement
            ///@param PWMValue speed/LED value determined by color 
            m_spark->Set(PWMValue);
        }
