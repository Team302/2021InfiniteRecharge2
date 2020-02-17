
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
#include <test/IStateTest.h>
#include <states/shooter/ShooterStateMgr.h>

// Third Party Includes


///	 @class ShooterStateMgrTest
///  @brief Tests for ShooterStateMgr.  There are three states: OFF, GET_READY, and SHOOT.  This will run each for 15 seconds each;
///  		running GET_READY, then SHOOT and finally OFF.
class ShooterStateMgrTest : public IStateTest
{
	public:
		ShooterStateMgrTest();
		~ShooterStateMgrTest() = default;
		
		/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
		/// @return void
		void Init() override;
		
		/// @brief Run the test.  This will be called from Robot::TestPeriodic()
		/// @return void		
		void Periodic() override;
		
		/// @brief Indicate whether the test has completed or not.
		/// @return bool - true: test has completed, false: test is still running
		bool IsDone() override;
		
	private:
		std::unique_ptr<ShooterStateMgr>	    m_stateMgr;
		bool                                    m_ranReady;
		bool                                    m_ranShoot;
		bool                                    m_ranOff;
		bool 									m_isDone;
		int										m_loopCnt;
		const int	m_nloops = 100;
};

		