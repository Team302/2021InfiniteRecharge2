
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
#include <string>

// FRC includes

// Team 302 includes
#include <subsys/IMech.h>
#include <subsys/MechanismTypes.h>

// Third Party Includes


///	 @interface IMech
///  @brief	    Interface for subsystems
class Mech : public IMech
{
	public:

        /// @brief          Indicates the type of mechanism this is
        /// @return         MechanismTypes::MECHANISM_TYPE
        MechanismTypes::MECHANISM_TYPE GetType() const override;

        /// @brief indicate the file used to get the control parameters from
        /// @return std::string the name of the file 
        std::string GetControlFileName() const override;

        /// @brief indicate the Network Table name used to setting tracking parameters
        /// @return std::string the name of the network table 
        std::string GetNetworkTableName() const override;

        /// @brief create the general mechanism
        /// @param [in] MechanismTypes::MECHANISM_TYPE the type of mechansim
        /// @param [in] std::string the name of the file that will set control parameters for this mechanism
        /// @param [in] std::string the name of the network table for logging information
        Mech
        (
            MechanismTypes::MECHANISM_TYPE  type,
            std::string                     controlFileName,
            std::string                     networkTableName
        );
	    Mech() = delete;
	    virtual ~Mech() = default;

    private:
        MechanismTypes::MECHANISM_TYPE  m_type;
        std::string                     m_controlFile;
        std::string                     m_ntName;
};