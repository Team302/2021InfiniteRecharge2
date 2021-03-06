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


// C++ includes
#include <memory>

// Team 302 includes
#include <controllers/mechanisms/MechControllerFactory.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <controllers/mechanisms/IMechController.h>
#include <controllers/ControlData.h>
#include <controllers/mechanisms/OpenLoopController.h>
#include <controllers/mechanisms/VelocityRPSController.h>
#include <controllers/mechanisms/VelocityDegreesPerSecController.h>

using namespace std;

MechControllerFactory* MechControllerFactory::m_factory = nullptr;

MechControllerFactory* MechControllerFactory::GetMechanismFactory()
{
	if ( MechControllerFactory::m_factory == nullptr )
	{
		MechControllerFactory::m_factory = new MechControllerFactory();
	}
	return MechControllerFactory::m_factory;
}

IMechController* MechControllerFactory::CreateMechController
(
    std::shared_ptr<IDragonMotorController>     motor,
    double                                      target,
    std::shared_ptr<ControlData>                controlData
)
{
    IMechController* controller = nullptr;
       
    auto mode = controlData->GetMode();
    auto server = controlData->GetRunLoc();

    switch ( mode )
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            controller = new OpenLoopController( motor, target );
            break;

        case ControlModes::CONTROL_TYPE::POSITION_INCH:
            break;

        case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
            break;

        case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
            break;

        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            controller = new VelocityDegreesPerSecController( motor, target, controlData );
            break;

        case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
            controller = new VelocityRPSController( motor, target, controlData );
            break;

        case ControlModes::CONTROL_TYPE::VOLTAGE:
            break;

        case ControlModes::CONTROL_TYPE::CURRENT:
            break;

        case ControlModes::CONTROL_TYPE::TRAPEZOID:
            break;

        case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
            break;

        case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
            break;

        default:
            break;



    }
    return controller;
}

