#pragma once

#include <frc/Joystick.h>
#include <ctre/Phoenix.h>
#include <string>
#include <states/IState.h>

#define TALON_COUNT 4
#define SONG_COUNT 11

class Music : public IState
{
    public:
        void Init() override;
        void Run() override;

    private:
        int GetButton();

        void LoadMusicSelection(int offset);

        Orchestra* m_orchestra;
        TalonFX** m_talon;

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

        frc::Joystick* m_joystick;
        int lastButton = 0;
        int lastPOV = 0;


};