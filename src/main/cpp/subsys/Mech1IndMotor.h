
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
#include <string>

// FRC includes
#include <frc2/Timer.h>

// Team 302 includes
#include <subsys/IMech1IndMotor.h>
#include <subsys/MechanismTypes.h>

// Third Party Includes
//#include <units/units.h>
#include <units/time.h>


// forward declares
class ControlModes;
class IDragonMotorController;
class ControlData;

class Mech1IndMotor : public IMech1IndMotor
{
	public:
        /// @brief Create a generic mechanism wiht 1 independent motor 
        /// @param [in] MechanismTypes::MECHANISM_TYPE the type of mechansim
        /// @param [in] std::string the name of the file that will set control parameters for this mechanism
        /// @param [in] std::string the name of the network table for logging information
        /// @param [in] std::shared_ptr<IDragonMotorController> motor controller used by this mechanism
        Mech1IndMotor
        (
            MechanismTypes::MECHANISM_TYPE              type,
            std::string                                 controlFileName,
            std::string                                 networkTableName,
            std::shared_ptr<IDragonMotorController>     motorController
        );
	    Mech1IndMotor() = delete;
	    ~Mech1IndMotor() override = default;

        /// @brief          Indicates the type of mechanism this is
        /// @return         MechanismTypes::MECHANISM_TYPE
        MechanismTypes::MECHANISM_TYPE GetType() const override;

        /// @brief indicate the file used to get the control parameters from
        /// @return std::string the name of the file 
        std::string GetControlFileName() const override;

        /// @brief indicate the Network Table name used to setting tracking parameters
        /// @return std::string the name of the network table 
        std::string GetNetworkTableName() const override;

        /// @brief Activates logging key values to network table
        /// @param [in] int: indicate how many millisecondsBetweenLogging updates to the network table 
        void ActivateLogging
        (
            units::second_t                 millisecondsBetweenLogging
        ) override final;
        /// @brief Stop updating the key values to network table
        void DeactivateLogging() override final;

        /// @brief log data to the network table if it is activated and time period has past
        void LogData() override;

        /// @brief update the output to the mechanism using the current controller and target value(s)
        /// @return void 
        void Update() override;

        void UpdateTarget
        (
            double      target
        ) override;

        /// @brief  Return the current position of the mechanism.  The value is in inches or degrees.
        /// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
        double GetPosition() const override;

        /// @brief  Get the current speed of the mechanism.  The value is in inches per second or degrees per second.
        /// @return double	speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms)
        double GetSpeed() const override;

        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*                                   pid:  the control constants
        /// @return void
        void SetControlConstants
        (
            ControlData*                                pid                 
        ) override;


    private:
        MechanismTypes::MECHANISM_TYPE              m_type;
        std::string                                 m_controlFile;
        std::string                                 m_ntName;
        bool                                        m_logging;
        units::second_t                             m_milliSecondsBetweenLogging;
        units::second_t                             m_lastTime;
        std::unique_ptr<frc2::Timer>                m_timer;
        std::shared_ptr<IDragonMotorController>     m_motor;
        double                                      m_target;
};



