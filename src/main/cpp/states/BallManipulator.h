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
#include <map>

// FRC includes

// Team 302 includes
#include <states/intake/IntakeStateMgr.h>
//#include <controllers/humanplayerflap/HumanPlayerFlapStateMgr.h>
#include <states/impeller/ImpellerStateMgr.h>
#include <states/balltransfer/BallTransferStateMgr.h>
#include <states/turret/TurretStateMgr.h>
#include <states/shooter/ShooterStateMgr.h>
#include <states/shooterhood/ShooterHoodStateMgr.h>

// Third Party Includes

class BallManipulator 
{
    public:
        /// @enum the various states of ball manipulation
        enum BALL_MANIPULATOR_STATE
        {
            OFF,
            INTAKE,
            INTAKE_HUMAN_PLAYER,
            HOLD,
            GET_READY_TO_SHOOT,
            SHOOT,
            MAX_BALL_MANIPULATOR_STATES
        };

		/// @brief  Find or create the Ball Manipulator
		/// @return AnalogInputFactory* pointer to the factory
		static BallManipulator* GetInstance();


        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     INTAKE_STATE - state to set
        /// @return void
        void SetCurrentState
        (
            BALL_MANIPULATOR_STATE      state
        );

        /// @brief  return the current state
        /// @return INTAKE_STATE - the current state
        inline BALL_MANIPULATOR_STATE GetCurrentState() const { return m_currentState; };

    private:

        BallManipulator();
        ~BallManipulator() = default;
		static BallManipulator*	m_instance;


        BALL_MANIPULATOR_STATE      m_currentState;
        IntakeStateMgr*             m_intake;
        ImpellerStateMgr*           m_impeller;
        BallTransferStateMgr*       m_transfer;
        TurretStateMgr*             m_turret;
        ShooterStateMgr*            m_shooter;
        ShooterHoodStateMgr*        m_hood;

};
