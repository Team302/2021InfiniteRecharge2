
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
#include <map>
#include <memory>

//Team 302 includes
#include <auton/PrimitiveFactory.h>
#include <auton/primitives/DriveDistance.h>
#include <auton/primitives/DriveToTarget.h>
#include <auton/primitives/DriveTime.h>
#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParser.h>
#include <auton/primitives/DoNothing.h>
#include <auton/primitives/HoldPosition.h>
#include <auton/primitives/TurnAngle.h>
#include <auton/primitives/DriveToWall.h>
#include <auton/primitives/AutoShoot.h>
#include <auton/primitives/IPrimitive.h>
#include <utils/Logger.h>
#include <xmlmechdata/StateDataDefn.h>

using namespace std;

/// @brief Return the PrimitiveFactory Singleton (if it doesn't already exist create it)
PrimitiveFactory* PrimitiveFactory::m_instance = nullptr;
PrimitiveFactory* PrimitiveFactory::GetInstance() 
{
	if (PrimitiveFactory::m_instance == nullptr) 					//If we do not have an instance
	{					
		PrimitiveFactory::m_instance = new PrimitiveFactory();		//Create a new instance
	}
	return PrimitiveFactory::m_instance;							//Return said instance
}

/// @brief clean up the singleton factory
void PrimitiveFactory::Cleanup()
{
	if (PrimitiveFactory::m_instance != nullptr) 	
	{
		delete PrimitiveFactory::m_instance;
		PrimitiveFactory::m_instance = nullptr;
	}				
}

/// @brief Construct the PrimitiveFactory Singleton
PrimitiveFactory::PrimitiveFactory() : m_primitives()
{
    // initialize the xml string to state map
    map<string, PRIMITIVE_IDENTIFIER> primitiveMap;
    primitiveMap["DRIVETRAIN_DONOTHING"] = DO_NOTHING;
    primitiveMap["DRIVETRAIN_HOLDPOSITION"] = HOLD_POSITION;
    primitiveMap["DRIVETRAIN_DRIVEDISTANCE"] = DRIVE_DISTANCE;
    primitiveMap["DRIVETRAIN_DRIVETIME"] = DRIVE_TIME;
    primitiveMap["DRIVETRAIN_DRIVETOWALL"] = DRIVE_TO_WALL;
    primitiveMap["DRIVETRAIN_TURNTOANGLE"] = TURN_ANGLE_REL;
	auto it = m_primitives.begin();
	m_primitives.insert(it, MAX_AUTON_PRIMITIVES, nullptr);

    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::DRIVETRAIN_SIDE );

   // create the Drive Primitives passing the configuration data
    for ( auto td: targetData )
    {
        auto primitiveString = td->GetStateString();
        auto primitiveStringToEnumItr = primitiveMap.find( primitiveString );
        if ( primitiveStringToEnumItr != primitiveMap.end() )
        {
            auto primEnum = primitiveStringToEnumItr->second;
            if ( m_primitives[primEnum] == nullptr )
            {
                auto controlData = td->GetController();
                switch ( primEnum )
                {
                    case DO_NOTHING:
                    {   
						m_primitives[DO_NOTHING] = new DoNothing();
                    }
                    break;

                    case HOLD_POSITION:
                    {   
						m_primitives[HOLD_POSITION] = new HoldPosition();
                    }
                    break;

                    case DRIVE_DISTANCE:
                    {   
						m_primitives[DRIVE_DISTANCE] = new DriveDistance();
                    }
                    break;

                    case DRIVE_TIME:
                    {
						m_primitives[DRIVE_TIME] = new DriveTime();
                    }
                    break;

					case TURN_ANGLE_ABS:
					case TURN_ANGLE_REL:  // intentional fallthrough since it is the same primitive
					{
						m_primitives[TURN_ANGLE_ABS] = new TurnAngle(controlData);
						m_primitives[TURN_ANGLE_REL] = m_primitives[TURN_ANGLE_ABS];
					}
					break;

                    default:
                    {
                        Logger::GetLogger()->LogError( Logger::LOGGER_LEVEL::ERROR_ONCE, string("PrimitiveFactory::PrimitiveFactory"), string("unknown drive primitive"));
                    }
                    break;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( Logger::LOGGER_LEVEL::ERROR_ONCE, string("PrimitiveFactory::PrimitiveFactory"), string("multiple primitive info for primitive"));
            }
        }
        else
        {
            Logger::GetLogger()->LogError( Logger::LOGGER_LEVEL::ERROR_ONCE, string("PrimitiveFactory::PrimitiveFactory"), string("primitive not found"));
        }
    }

    // Create the non-drive Primitives
    m_primitives[AUTO_SHOOT] = new AutoShoot();

    // Verify all primitives are available
	for ( auto primitive : m_primitives )
	{
		if ( primitive == nullptr )
		{
            Logger::GetLogger()->LogError( Logger::LOGGER_LEVEL::ERROR_ONCE, string("PrimitiveFactory::PrimitiveFactory"), string("not all primitives were created"));
		}
	}

}


/// @brief delete the factory 
PrimitiveFactory::~PrimitiveFactory() 
{
	for ( auto primitive : m_primitives )
	{
		if ( primitive != nullptr )
		{
			delete primitive;
		}
	}
}

/// @brief return the primitive of the desired type
/// @param [in] PrimitiveParams* pointer to the parameters that identify the primitive to return.
IPrimitive* PrimitiveFactory::GetIPrimitive(PrimitiveParams* primitivePasser)
{
	return m_primitives[primitivePasser->GetID()];
}
