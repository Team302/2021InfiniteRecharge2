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
#include <iostream>
#include <string>
#include <utility>

//Team302 includes
#include <hw/DragonBlinkin.h>
#include <xmlhw/BlinkinDefn.h>

#include <utils/Logger.h>

//Third party includes
#include <pugixml/pugixml.hpp>

/// @class
/// @brief      parse the blinkin node and create a dragon blinkin
/// @param [in] xml_node - the blinkin node
/// @return     DragonBlink* the blinkin led controller or nullptr if the node is invalid
DragonBlinkin* BlinkinDefn::ParseXML
(
        pugi::xml_node BlinkinNode
)
{
    //initialize output
    DragonBlinkin *blinkin = nullptr;

    //initialize  pwm channel, fail state and position
    int pwmId = 0;
    std::string position = "front";

    bool hasError = false;

    //parse xml; will validate later
    for (pugi::xml_attribute attr = BlinkinNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        /// @brief checks to see if it is looking at pwmId attribute
        /// @param [in] attr.name - what the attribute's name is
        /// @param [out] pwmId - what pwm channel the blinkin will use
        if(strcmp(attr.name(), "pwmId") == 0)
        {
            int value = attr.as_int();
            if(value > -1 && value < 12)
            {
                pwmId = value;
            }
            else
            {
                //pwmId does not have a port, too high or too low
                Logger::GetLogger()->LogError(Logger::LOGGER_LEVEL::ERROR_ONCE, "if(value > -1 && value < 12", "no pwmid of that value");
                hasError = true;
            }
            
        }

        /// @brief checks to see if it is looking at position attribute
        /// @param [in] attr.name - what the attribute's name is
        /// @param [out] position - where the blinkin is physically located on the robot
        if (strcmp(attr.name(), "position") == 0)
        {
            std::string positionString = attr.as_string();

            if ( positionString.compare ( "front" ) == 0 )
            {
                position = "front";
            }
            else if ( positionString.compare ( "back" ) == 0)
            {
                position = "back";
            }
            else if ( positionString.compare ( "top" ) == 0 )
            {
                position = "top";
            }
            else if ( positionString.compare ( "bottom " ) == 0 )
            {
                position = "bottom";
            }
            else
            {
                std::string msg = "unknown position ";
                msg += attr.value();
                Logger::GetLogger()->LogError(Logger::LOGGER_LEVEL::ERROR_ONCE, "if (strcmp(attr.name(), 'position') == 0 )", msg);
                hasError = true;
            }
        }
    }
    //create blinkin
    if(!hasError)
    {
        blinkin = new DragonBlinkin(pwmId);
    }
}
