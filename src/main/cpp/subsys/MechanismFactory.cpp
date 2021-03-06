
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

//========================================================================================================
/// MechanismFactory.cpp
//========================================================================================================
///
/// File Description:
///     This controls the creation of mechanisms/subsystems
///
//========================================================================================================

// C++ Includes
#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>
#include <hw/usages/AnalogInputMap.h>
#include <hw/usages/DigitalInputMap.h>
#include <hw/usages/DragonSolenoidMap.h>
#include <hw/usages/ServoMap.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonServo.h>
#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <subsys/ControlPanel.h>
#include <subsys/MechanismFactory.h>
#include <subsys/HookDelivery.h>
#include <subsys/MechanismTypes.h>
#include <subsys/Intake.h>
#include <utils/Logger.h>
#include <subsys/Impeller.h>
#include <subsys/BallTransfer.h>
#include <subsys/Turret.h>
#include <subsys/Shooter.h>
#include <subsys/ShooterHood.h>

// Third Party Includes
#include <rev/ColorSensorV3.h>
#include <ctre/phoenix/sensors/CANCoder.h>


using namespace std;
using namespace rev;
using namespace ctre::phoenix::sensors;


//=====================================================================================
/// Method:         GetMechanismFactory
/// Description:    Find or create the mechanism factory
/// Returns:        MechanismFactory* pointer to the mechanism factory
//=====================================================================================
MechanismFactory* MechanismFactory::m_mechanismFactory = nullptr;
MechanismFactory* MechanismFactory::GetMechanismFactory()
{
	if ( MechanismFactory::m_mechanismFactory == nullptr )
	{
		MechanismFactory::m_mechanismFactory = new MechanismFactory();
	}
	return MechanismFactory::m_mechanismFactory;
}

MechanismFactory::MechanismFactory() :  m_balltransfer(),
										m_climber(),
										m_controlPanel(),
										m_crawler(),
										m_hookDelivery(),
										m_impeller(),
										m_intake(),
										m_shooter(),
										m_shooterHood(),
										m_turret()
{
}




/// @brief      create the requested mechanism
/// @param [in] MechanismTypes::MECHANISM_TYPE  type - the type of mechanism to create
/// @param [in] const IDragonMotorControllerMap& map of the motor usage to the motor controller
/// @param [in] 
/// @param [in] 
/// @param [in] 
/// @param [in] 
/// @return  IMech*  pointer to the mechanism or nullptr if mechanism couldn't be created.
void  MechanismFactory::CreateIMechanism
(
	MechanismTypes::MECHANISM_TYPE			type,
	const IDragonMotorControllerMap&        motorControllers,   // <I> - Motor Controllers
	const DragonSolenoidMap&                solenoids,
	const ServoMap&						    servos,
	const DigitalInputMap&					digitalInputs,
	const AnalogInputMap&                   analogInputs,
	ColorSensorV3*					        colorSensor,
	shared_ptr<CANCoder>					canCoder
)
{

	bool found = false;
	// Create the mechanism
	switch ( type )
	{
		case MechanismTypes::MECHANISM_TYPE::INTAKE:
		{
			if (m_intake.get() == nullptr )
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::INTAKE );
				if ( motor.get() != nullptr )
				{
					auto solenoid = GetSolenoid( solenoids, SolenoidUsage::SOLENOID_USAGE::INTAKE );
					if ( solenoid.get() != nullptr )
					{
						m_intake = make_shared<Intake>( motor, solenoid );
					}
				}
			}
			else
			{
				found = true;
			}
			
		}
		break;

		case MechanismTypes::MECHANISM_TYPE::IMPELLER:
		{
			if ( m_impeller.get() == nullptr )
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::IMPELLER );
				if ( motor.get() != nullptr )
				{
					m_impeller = make_shared<Impeller>( motor, canCoder );
				}
			}
			else
			{
				found = true;
			}

		}
		break;
		
		case MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER:
		{
			if ( m_balltransfer.get() != nullptr )
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::BALL_TRANSFER );
				if ( motor.get() != nullptr )
				{
					m_balltransfer = make_shared<BallTransfer>( motor );
				}
			}
			else
			{
				found = true;
			}
		}
		break;			
		
		case MechanismTypes::MECHANISM_TYPE::SHOOTER:
		{
			if ( m_shooter.get() != nullptr )
			{
				auto motor1 = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_1 );
				auto motor2 = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_2 );
				if ( motor1.get() != nullptr && motor2.get() != nullptr )
				{
					m_shooter = make_shared<Shooter>(motor1, motor2);
				}
			}
			else
			{
				found = true;
			}

		}
		break;			
		
		case MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD:
		{
			if ( m_shooterHood.get() != nullptr )
			{
				auto shooterHoodMotor = GetMotorController ( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_HOOD );
				if ( shooterHoodMotor.get() != nullptr )
				{
					m_shooterHood = make_shared<ShooterHood>( shooterHoodMotor, canCoder);
				}
			}
			else
			{
				found = true;
			}
		}
		break;		
		
		case MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR:
		{
			if ( m_controlPanel.get() == nullptr )
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::CONTROL_TABLE_MANIPULATOR );
				if ( motor.get() != nullptr )
				{
					auto solenoid = GetSolenoid( solenoids, SolenoidUsage::SOLENOID_USAGE::CONTROL_TABLE_MANIPULATOR );
					if ( solenoid.get() != nullptr )
					{
						if ( colorSensor !=nullptr )
						{
							//todo color sensor pointer needs to be added to the constructor
							m_controlPanel = make_shared<ControlPanel>( motor, solenoid, colorSensor );
						}
					}
				}
			}
			else
			{
				found = true;
			}
		}
		break;		
		
		case MechanismTypes::MECHANISM_TYPE::CLIMBER:
		{
		}
		break;		
		
		case MechanismTypes::MECHANISM_TYPE::CRAWLER:
		{
		}
		break;
		
		case MechanismTypes::MECHANISM_TYPE::TURRET:
		{
			if ( m_turret.get() == nullptr )
			{
				auto motor = GetMotorController(motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::TURRET);
				if(motor.get() != nullptr)
				{
					m_turret = make_shared<Turret>(motor);
				}
			}
			else
			{
				found = true;
			}
		}
		break;

		case MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY:
		{
			if ( m_hookDelivery.get() == nullptr )
			{
				auto motor = GetMotorController(motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::HOOK_DELIVERY);
				if(motor.get() != nullptr)
				{
					m_hookDelivery = make_shared<HookDelivery>(motor);
				}
			}
			else
			{
				found = true;
			}
		}
		break;

		default:
		{
			string msg = "unknown Mechanism type ";
			msg += to_string( type );
			Logger::GetLogger()->LogError( "MechanismFactory::CreateIMechanism", msg );
		}
		break;
	}
    // See if the mechanism was created already, if it wasn't create it
	if ( found )
    {
        string msg = "mechanism already exists";
        msg += to_string( type );
        Logger::GetLogger()->LogError( string("MechansimFactory::CreateIMechanism" ), msg );
    }
}


shared_ptr<IDragonMotorController> MechanismFactory::GetMotorController
(
	const IDragonMotorControllerMap&				motorControllers,
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
)
{
	shared_ptr<IDragonMotorController> motor;
	auto it = motorControllers.find( usage );
	if ( it != motorControllers.end() )  // found it
	{
		motor = it->second;
	}
	else
	{
		string msg = "motor not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetMotorController" ), msg );
	}
	
	if ( motor.get() == nullptr )
	{
		string msg = "motor is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetMotorController" ), msg );
	}
	return motor;
}

shared_ptr<DragonSolenoid> MechanismFactory::GetSolenoid
(
	const DragonSolenoidMap&						solenoids,
	SolenoidUsage::SOLENOID_USAGE					usage
)
{
	shared_ptr<DragonSolenoid> solenoid;
	auto it = solenoids.find( usage );
	if ( it != solenoids.end() )  // found it
	{
		solenoid = it->second;
	}
	else
	{
		string msg = "solenoid not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetSolenoid" ), msg );
	}
	
	if ( solenoid.get() == nullptr )
	{
		string msg = "solenoid is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetSolenoid" ), msg );
	}
	return solenoid;
}
shared_ptr<DragonServo> MechanismFactory::GetServo
(
	const ServoMap&									servos,
	ServoUsage::SERVO_USAGE							usage
)
{
	shared_ptr<DragonServo> servo;
	auto it = servos.find( usage );
	if ( it != servos.end() )  // found it
	{
		servo = it->second;
	}
	else
	{
		string msg = "servo not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetServo" ), msg );
	}
	
	if ( servo.get() == nullptr )
	{
		string msg = "servo is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetServo" ), msg );
	}
	return servo;

}
shared_ptr<DragonDigitalInput> MechanismFactory::GetDigitalInput
(
	const DigitalInputMap&							digitaInputs,
	DigitalInputUsage::DIGITAL_SENSOR_USAGE			usage
)
{
	shared_ptr<DragonDigitalInput> dio;
	auto it = digitaInputs.find( usage );
	if ( it != digitaInputs.end() )  // found it
	{
		dio = it->second;
	}
	else
	{
		string msg = "digital input not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetDigitalInput" ), msg );
	}
	
	if ( dio.get() == nullptr )
	{
		string msg = "digital input is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetDigitalInput" ), msg );
	}
	return dio;
}
shared_ptr<DragonAnalogInput> MechanismFactory::GetAnalogInput
(
	const AnalogInputMap&							analogInputs,
	AnalogInputUsage::ANALOG_SENSOR_USAGE			usage
)
{
	shared_ptr<DragonAnalogInput> anIn;
	auto it = analogInputs.find( usage );
	if ( it != analogInputs.end() )  // found it
	{
		anIn = it->second;
	}
	else
	{
		string msg = "analog input not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetAnalogInput" ), msg );
	}
	
	if ( anIn.get() == nullptr )
	{
		string msg = "analog input is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetAnalogInput" ), msg );
	}
	return anIn;
}



