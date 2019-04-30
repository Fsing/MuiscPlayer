#include "localplay.h"

void LocalPlay::play(QString songName)
{
    m_localPlayThreadContain.play(songName);
}
