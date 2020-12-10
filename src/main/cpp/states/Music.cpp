#include <states/Music.h>


Music::Music(std::vector<TalonFX*> falcons)
{
    for ( auto falcon : falcons )
    {
        m_talon.push_back( falcon );
    }
}




void Music::LoadMusicSelection(STATES state)
{
    m_orchestra -> LoadMusic(songs[state]);
    timeToPlayLoops = 10;
}


void Music::Run()
{
    m_orchestra -> Play();
}

