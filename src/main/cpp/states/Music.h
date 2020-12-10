#pragma once

#include <vector>

#include <ctre/Phoenix.h>
#include <string>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>

#define TALON_COUNT 4
#define SONG_COUNT 11

class Music  
{
    public:
        enum STATES 
        {
            CLIMB,
            AUTON
        };
        void Run();
        void LoadMusicSelection(STATES state);
        Music(std::vector<TalonFX*> m_talon);
        

    private:
        

        

        Orchestra* m_orchestra;
        std::vector<TalonFX*> m_talon;

        std::string songs[SONG_COUNT] =
        {
            "song1.chrp",
            "song2.chrp",
            "song3.chrp",
            "song4.chrp",
            "song5.chrp",
            "song6.chrp",
            "song7.chrp",
            "song8.chrp",
            "song9.chrp",
            "song10.chrp",
            "song11.chrp",
        };

        int songSelection = 0;
        int timeToPlayLoops = 0;

        


};