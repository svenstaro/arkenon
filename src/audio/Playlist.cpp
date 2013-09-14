#include "Playlist.hpp"

Playlist::Playlist(const std::string& name)
    : SoundSource(name)
{

}

Playlist::Playlist(const std::string& name, std::vector<std::string> list)
    : SoundSource(name)
{
    setPlaylist(list);
}
Playlist::~Playlist() {
    stop();
}

void Playlist::play() {
    alurePlaySourceStream(mHandle, mStream->get(), 3, 0, [](void *userdata, ALuint source) { ((Playlist*)userdata)->donePlaying(); }, this);
}
void Playlist::stop() {
    alureStopSource(mHandle, AL_FALSE);
}

void Playlist::pause() {
    alurePauseSource(mHandle);
}

void Playlist::resume() {
    alureResumeSource(mHandle);
}

void Playlist::setLoop(bool loop) {
    mLooping = loop;
}

void Playlist::setPlaylist(std::vector<std::string> list) {
    mPlaylist = list;

    if(mPlaylist.size() >= 1) {
        mPos = 0;
        mStream = std::make_shared<Stream>();
        mStream->loadFromFile(mPlaylist[mPos]);
    }
}


void Playlist::donePlaying() {
    ++mPos;

    if(mPos < mPlaylist.size()) {
        mStream = std::make_shared<Stream>();
        mStream->loadFromFile(mPlaylist[mPos]);
        play();
    } else {
        if(mLooping) {
            mPos = 0;
            mStream = std::make_shared<Stream>();
            mStream->loadFromFile(mPlaylist[mPos]);
            play();
        }
    }
}


