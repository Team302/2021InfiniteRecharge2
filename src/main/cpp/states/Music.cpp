#include <states/Music.h>

int Music::GetButton() 
{
    for (int i = 1; i < 9; i++) 
    {
        if (m_joystick->GetRawButton(i))
        {
            return i;
        }
    }
    return 0;
}

void Music::LoadMusicSelection(int offset)
{
    songSelection += offset;

    if (songSelection >= SONG_COUNT)
    {
        songSelection = 0;
    }

    if (songSelection < 0)
    {
        songSelection = SONG_COUNT - 1;
    }

    m_orchestra -> LoadMusic(songs[songSelection]);
    timeToPlayLoops = 10;
}

void Music::Init()
{
    m_orchestra = new Orchestra();

    m_talon = new TalonFX * [TALON_COUNT];

    for (int i = 0; i < TALON_COUNT; i++)
    {
        m_talon[i] = new TalonFX(i+1);
        m_orchestra -> AddInstrument(*m_talon[i]);
    }
    m_joystick = new frc::Joystick(0);

    LoadMusicSelection(0);
}

void Music::Run()
{
    int btn = GetButton();
    int currentPOV = m_joystick->GetPOV();

    if (timeToPlayLoops > 0)
    {
        --timeToPlayLoops;
        if (timeToPlayLoops == 0)
        {
            m_orchestra -> Play();
        }
    }

    if (lastButton != btn)
    {
        lastButton = btn;

        switch (btn) 
        {
            case 1:
                if (m_orchestra -> IsPlaying())
                {
                    m_orchestra ->Pause();
                }
                else
                {
                    m_orchestra->Play();
                }
                break;
            
            case 2:
                if (m_orchestra->IsPlaying())
                {
                    m_orchestra->Stop();
                }  
                else 
                {
                    m_orchestra->Play();
                }
                break;
        }
    }
    if (lastPOV != currentPOV) {
        lastPOV = currentPOV;

        switch (currentPOV) {
            case 90:
                /* increment song selection */
                LoadMusicSelection(+1);
                break;
            case 270:
                /* decrement song selection */
                LoadMusicSelection(-1);
                break;
        }
    }
}

