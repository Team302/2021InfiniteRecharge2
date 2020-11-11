
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

//========================================================================================================
/// Logger.cpp
//========================================================================================================
///
/// File Description:
///     This logs error messages
///
//========================================================================================================


// C++ Includes
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <utils/Logger.h>


// Third Party Includes

using namespace frc;
using namespace std;


/// @brief Find or create the singleton logger
/// @returns Logger* pointer to the logger
Logger* Logger::m_instance = nullptr;
Logger* Logger::GetLogger()
{
    if ( Logger::m_instance == nullptr )
    {
        Logger::m_instance = new Logger();
    }
    return Logger::m_instance;
}

/// @brief set the option for where the logging messages should be displayed
/// @param [in] LOGGER_OPTION:  logging option for where to log messages
void Logger::SetLoggingOption
(
    LOGGER_OPTION option    
)
{
    m_option = option;
}

/// @brief set the level for messages that will be displayed
/// @param [in] LOGGER_LEVEL:  logging level for which messages to display
void Logger::SetLoggingLevel
(
    LOGGER_LEVEL level    
)
{
    m_level = level;
}

/// @brief log a message
/// @param [in] std::string: classname or object identifier
/// @param [in] std::string: message
void Logger::LogError
(
    const string&   locationIdentifier,     
    const string&   message                 
)
{
    LogError( LOGGER_LEVEL::PRINT, locationIdentifier, message );
}

/// @brief log a message
/// @param [in] LOGGER_LEVEL: message level
/// @param [in] std::string: classname or object identifier
/// @param [in] std::string: message
void Logger::LogError
(
    LOGGER_LEVEL    level,
    const string&   locationIdentifier,     
    const string&   message                 
)
{
    if ( level <= m_level )
    {
        auto display = true;
        if ( level%2 == 1 )
        {
            string key = locationIdentifier + message;
            auto it = m_alreadyDisplayed.find(key);
            display = it == m_alreadyDisplayed.end();
            if (display)
            {
                m_alreadyDisplayed.insert(key);
            }

        }
        if (display)
        {
            switch ( m_option )
            {
                case LOGGER_OPTION::CONSOLE:
                    cout << locationIdentifier << ": " << message << endl;
                    break;

                case LOGGER_OPTION::DASHBOARD:
                    SmartDashboard::PutString( locationIdentifier.c_str(), message.c_str());
                    break;

                default:  // case LOGGER_OPTION::EAT_IT:
                    break;

            }
        }
    }
}

/// @brief Write a message to the dashboard
/// @param [in] std::string: classname or object identifier
/// @param [in] std::string: message
void Logger::OnDash
(
    const string&   locationIdentifier,     // <I> - classname or object identifier
    const string&   message                 // <I> - error message
)
{
    SmartDashboard::PutString( locationIdentifier.c_str(), message.c_str());
}

/// @brief Write a message to the dashboard
/// @param [in] std::string: classname or object identifier
/// @param [in] bool: boolean that should be written
void Logger::OnDash
(
    const string&   locationIdentifier,     // <I> - classname or object identifier
    bool            val                 // <I> - error message
)
{
    SmartDashboard::PutBoolean( locationIdentifier.c_str(), val );
}

Logger::Logger() : m_option( LOGGER_OPTION::EAT_IT ), 
                   m_level( LOGGER_LEVEL::PRINT ),
                   m_alreadyDisplayed()
{
}
