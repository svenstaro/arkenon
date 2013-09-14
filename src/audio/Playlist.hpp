#ifndef _AUDIO_PLAYLIST_HPP
#define _AUDIO_PLAYLIST_HPP

#include <memory>
#include "audio/SoundSource.hpp"
#include "audio/Listener.hpp"
#include "audio/Stream.hpp"

class Playlist : public SoundSource {
public:
    Playlist(const std::string& name);
    Playlist(const std::string& name, std::vector<std::string> list);
    ~Playlist();
    void play();
    void stop();
    void pause();
    void resume();

    void setLoop(bool loop);

    void setPlaylist(std::vector<std::string> list);
private:
    void donePlaying();
    std::vector<std::string> mPlaylist;
    std::shared_ptr<Stream> mStream;
    bool mLooping;
    unsigned int mPos;
};

#endif