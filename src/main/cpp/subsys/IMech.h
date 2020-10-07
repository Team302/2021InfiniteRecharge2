
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

//========================================================================================================
/// @interface IMech
/// @brief     This is the interface for mechanisms regardless of what control items are available.
//========================================================================================================

// C++ Includes
#include <string>
#include <vector>

// FRC includes

// Team 302 includes
#include <subsys/MechanismTypes.h>

// Third Party Includes


///	 @interface IMech
///  @brief	    Interface for subsystems
class IMech
{
	public:

        /// @brief          Indicates the type of mechanism this is
        /// @return         MechanismTypes::MECHANISM_TYPE
        virtual MechanismTypes::MECHANISM_TYPE GetType() const = 0;

        /// @brief indicate the file used to get the control parameters from
        /// @return std::string the name of the file 
        virtual std::string GetControlFileName() const = 0;

        /// @brief indicate the Network Table name used to setting tracking parameters
        /// @return std::string the name of the network table 
        virtual std::string GetNetworkTableName() const = 0;
        
	    IMech() = default;
	    virtual ~IMech() = default;
};
typedef std::vector<IMech*> IMechVector;



