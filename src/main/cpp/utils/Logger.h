
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
/// Logger.h
//========================================================================================================
///
/// File Description:
///     This logs error messages
///
//========================================================================================================

#pragma once

// C++ Includes
#include <string>
#include <set>

// FRC includes

// Team 302 includes


// Third Party Includes



class Logger
{
    public:

        /// @enum LOGGER_OPTION
        /// @brief Define where the items being logged should be sent
        enum LOGGER_OPTION
        {
            CONSOLE,        ///< write to the RoboRio Console
            DASHBOARD,      ///< write to the SmartDashboard
            EAT_IT          ///< don't write anything (useful at comps where we want to minimize network traffic)
        };

        /// @enum LOGGER_LEVEL
        /// @brief Define what level the message is as well as this can be used to write only the messages of a certain level or worse.  The enum is ordered from worse to better and corresponds to the driver's station levels
        enum LOGGER_LEVEL
        {
            ERROR,             ///< this is catastrophic 
            ERROR_ONCE,        ///< this is catastrophic that we only want to see once
            WARNING,           ///< this is a medium level error
            WARNING_ONCE,      ///< this is a medium level error we only want to see once
            PRINT,             ///< this is an information/debug message
            PRINT_ONCE         ///< this is an information/debug message we only want to see once
        };

        /// @brief Find or create the singleton logger
        /// @returns Logger* pointer to the logger
        static Logger* GetLogger();

        /// @brief set the option for where the logging messages should be displayed
        /// @param [in] LOGGER_OPTION:  logging option for where to log messages
        void SetLoggingOption
        (
            LOGGER_OPTION option    // <I> - Logging option
        );

        /// @brief set the level for messages that will be displayed
        /// @param [in] LOGGER_LEVEL:  logging level for which messages to display
        void SetLoggingLevel
        (
            LOGGER_LEVEL level    // <I> - Logging level
        );

        /// @brief log a message
        /// @param [in] std::string: classname or object identifier
        /// @param [in] std::string: message
        void LogError
        (
            const std::string&      locationIdentifier,     
            const std::string&      message                 
        );

        /// @brief log a message
        /// @param [in] LOGGER_LEVEL: message level
        /// @param [in] std::string: classname or object identifier
        /// @param [in] std::string: message
        void LogError
        (
            LOGGER_LEVEL            level,
            const std::string&      locationIdentifier,     
            const std::string&      message                 
        );


        /// @brief Write a message to the dashboard
        /// @param [in] std::string: classname or object identifier
        /// @param [in] std::string: message
        void OnDash
        (
            const std::string&   locationIdentifier,    
            const std::string&   message  
        );              

        /// @brief Write a message to the dashboard
        /// @param [in] std::string: classname or object identifier
        /// @param [in] bool: boolean that should be written
        void OnDash
        (
            const std::string&   locationIdentifier,     
            bool                 value                 
        );

    protected:


    private:
        Logger();
        ~Logger() = default;

        LOGGER_OPTION           m_option;
        LOGGER_LEVEL            m_level;
        std::set<std::string>   m_alreadyDisplayed;
        static Logger*          m_instance;


};


