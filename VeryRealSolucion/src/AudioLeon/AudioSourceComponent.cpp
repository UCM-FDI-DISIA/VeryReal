#pragma once
#include "AudioSourceComponent.h"
#include "AudioManager.h"
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>
#include "VariantClass.h"
#include <fmod_studio.hpp>

using namespace VeryReal;
using namespace std;

AudioSourceComponent::AudioSourceComponent()
    : volume(0), speed(1), min_distance(0), max_distance(FLT_MAX), sound_channel(1), sound_group("default"), sound_path("none"),
      sound_name("unknown"), playing(false), loop(false), is_three_d(false), play_on_start(false), result(FMOD_OK) { }

AudioSourceComponent::~AudioSourceComponent() { AM().DeleteSound(sound_name); }
std::pair<bool, std::string> AudioSourceComponent::InitComponent(std::string name, std::string path, bool onstart, std::string groupchannel,
                                                                 float volume, bool threed,
                                         bool loop, float mindistance, float maxdistance) {

    SetSourceName(name);
    SetSourcePath(path);
    SetPlayOnStart(onstart);
    SetGroupChannelName(groupchannel);
    SetVolumeValue(volume);
    SetIsThreeD(threed);
    SetLoop(loop);
    SetMinMaxDistanceValue(mindistance, maxdistance);

    return {true, "AudioSourceComponent sucessfully initialized"};
}
std::pair<bool, std::string> AudioSourceComponent::Create3DSound() {
    std::string soundPath = "Assets/SONIDOS/" + sound_path;
    AM().NameToLower(sound_name);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AM().GetSound(sound_name);
    if (soundHandle != nullptr) return {false, "AudioSourceComponent error: Create3DSound(). Another 3D sound was already created with the same name."};

    if (loop) {
        this->result = AM().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AM().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
    }

    auto tryCreate3DSound = AM().CheckFMODResult(this->result);
    if (!tryCreate3DSound.first) return tryCreate3DSound;

    auto trySetMinMaxDistance = SetMinMaxDistance(min_distance, max_distance);
    if (trySetMinMaxDistance.first) {
        std::pair<std::string, FMOD::Sound*> newSound(sound_name, newSoundHandle);
        AM().AddNewSound(newSound);
#ifdef _DEBUG
        std::cout << "Sound created."
                  << "\n";
#endif   // DEBUG
        return {true, sound_name + " AudioSource sucessfully created."};
    }
    else {
        return trySetMinMaxDistance;
    }
}

std::pair<bool, std::string> AudioSourceComponent::CreateNormalSound() {
    std::string soundPath = "Assets/SONIDOS/" + sound_path;
    AM().NameToLower(sound_name);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AM().GetSound(sound_name);
    if (soundHandle != nullptr) return {false, "AudioSourceComponent error: CreateNormalSound(). Another 2D sound was already created with the same name."};

    if (loop) {
        this->result = AM().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AM().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
    }

    auto tryCreate2Dsound = AM().CheckFMODResult(this->result);
    if (tryCreate2Dsound.first) {
        std::pair<std::string, FMOD::Sound*> newSound(sound_name, newSoundHandle);
        AM().AddNewSound(newSound);
#ifdef _DEBUG
        std::cout << "Sound created."
                  << "\n";
#endif   // DEBUG
        return {true, sound_name + " AudioSource sucessfully created."};
    }
    else {
        return tryCreate2Dsound;
    }
}

std::pair<bool, std::string> AudioSourceComponent::Set3DSoundAtributes(VeryReal::Vector3 position, VeryReal::Vector3 velocity) {
    AM().NameToLower(sound_name);
    FMOD::Channel* channelHandle = AM().GetChannel(sound_name);
    if (channelHandle == nullptr) return {false, "AudioSourceComponent error :Set3DSoundAtributes(). No channels linked to this sound available to set 3D atributes."};
    FMOD_VECTOR p = AM().V3ToFmodV3(position), v = AM().V3ToFmodV3(velocity);

    this->result = channelHandle->set3DAttributes(&p, &v);
    auto trySet3DAtributes = AM().CheckFMODResult(this->result);
    if (!trySet3DAtributes.first) return trySet3DAtributes;
    return {true, "AudioSource 3D sounds atributes succesfully set in sound " + sound_name};
}

std::pair<bool, std::string> AudioSourceComponent::Play() {
    VeryReal::Vector3 channel_pos = transform->GetPosition();
    VeryReal::Vector3 channel_vel = transform->GetVelocity();

    AM().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AM().GetSound(sound_name);
    if (soundHandle == nullptr) return {false, "AudioSourceComponent error :Play(). No sound available to play with that name."};

    FMOD::ChannelGroup* playedChannelGroup = AM().GetGroupChannel(sound_group);
    if (playedChannelGroup == nullptr) return {false, "AudioSourceComponent error :Play(). No channel linked to this sound available to play."};

    FMOD_MODE finalSoundMode;
    soundHandle->getMode(&finalSoundMode);

    FMOD::Channel* reproChannel = AM().GetChannel(sound_name);
    if (reproChannel == nullptr) {
        for (int i = 0; i < AM().GetChannelsVector().size(); i++) {
            bool IsPlaying;
            AM().GetChannelsVector() [i]->isPlaying(&IsPlaying);

            if (IsPlaying) continue;

            FMOD::Channel* channelUsed;

            this->result = AM().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &channelUsed);
            auto tryPlaySound = AM().CheckFMODResult(this->result);
            if (!tryPlaySound.first) return tryPlaySound;
            playing = true;

            AM().setChannelValue(i, channelUsed);

            reproChannel = AM().GetChannelsVector() [i];

            this->result = AM().GetChannelsVector() [i]->setVolume(volume);
            auto trySetChannelVolume = AM().CheckFMODResult(this->result);
            if (!trySetChannelVolume.first) return trySetChannelVolume;

            //AM().GetLastPlayedMap() [soundHandle] = i;
            AM().SetLastPlayedMap(soundHandle, i);

            break;
        }
    }
    else {
        this->result = AM().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &reproChannel);
        auto tryPlaySound = AM().CheckFMODResult(this->result);
        if (!tryPlaySound.first) return tryPlaySound;
    }

    if (finalSoundMode & FMOD_3D) {
        FMOD_VECTOR v = AM().V3ToFmodV3(channel_vel), p = AM().V3ToFmodV3(channel_pos);
        this->result = reproChannel->set3DAttributes(&p, &v);
        auto trySet3DAtributes = AM().CheckFMODResult(this->result);
        if (!trySet3DAtributes.first) return trySet3DAtributes;
    }

    return {true, sound_name + " AudioSource sucessfully played"};
}

std::pair<bool, std::string> AudioSourceComponent::StopSound() {
    AM().NameToLower(sound_name);
    FMOD::Channel* channel = AM().GetChannel(sound_name);
    if (channel != nullptr) {
        channel->stop();
        return {true, sound_name + " AudioSource sucessfully stopped"};
    }
    else {
        return {false, "AudioSourceComponent error :StopSound(). No channel linked to this sound available to stop with that name."};
    }
}

std::pair<bool, std::string> AudioSourceComponent::PauseSound(bool Pause) {
    AM().NameToLower(sound_name);
    bool isPaused;
    FMOD::Channel* channel = AM().GetChannel(sound_name);
    if (channel != nullptr) {
        this->result = channel->getPaused(&isPaused);
        auto tryIsPaused = AM().CheckFMODResult(this->result);
        if (!tryIsPaused.first) return tryIsPaused;

        if (!(isPaused && Pause)) {
            channel->setPaused(Pause);
        }
        return {true, sound_name + " AudioSource sucessfully paused"};
    }
    else {
        return {false, "AudioSourceComponent error :PauseSound(). No channel linked to this sound available to pause with that name."};
    }
}

std::pair<bool, std::string> AudioSourceComponent::Start() {
    transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>();

    if (!transform) {
        return { false, "AudioSourceComponent error: Start()." + sound_name + " 's entity doesn't have transform component"};
    }

    // Create a 3D sound or a normal sound
    if (is_three_d) 
    {
        auto tryCreate3DSound = Create3DSound();
        if (!tryCreate3DSound.first) return tryCreate3DSound;
    }
    else {
        auto tryCreateNormalSound = CreateNormalSound();
        if (!tryCreateNormalSound.first) return tryCreateNormalSound;
    }

    if (play_on_start) {
        auto tryPlaySound = Play();
        if (!tryPlaySound.first) return tryPlaySound;
    }

    return { true, "AudioSource " + sound_name + " started." }; 
}

void AudioSourceComponent::Update(const double& dt) {
    if (is_three_d) {
        auto trySet3DAtributes = Set3DSoundAtributes(transform->GetPosition(), transform->GetVelocity());
        if (!trySet3DAtributes.first) std::cout << trySet3DAtributes.second << std::endl;
    }
}

void AudioSourceComponent::Stop() { StopSound(); }

void AudioSourceComponent::Pause() { PauseSound(true); }

void AudioSourceComponent::Resume() { PauseSound(false); }

bool AudioSourceComponent::IsPlaying() { return playing; }

std::pair<bool, std::string> AudioSourceComponent::SetVolume(float value) {
    volume = value;
    AM().NameToLower(sound_name);
    FMOD::Channel* channel = AM().GetChannel(sound_name);
    if (channel != nullptr) {
        this->result = channel->setVolume(value);
        auto trySetVolume = AM().CheckFMODResult(this->result);
        if (!trySetVolume.first) return trySetVolume;
        else return {true, "Volume from AudioSource" + sound_name + "succesfully set."};
    }
    else {
        return {false, "AudioSourceComponent error: SetVolume(). The channel from this AudioSource is not valid: Sound name is: " + sound_name};
    }
}

void VeryReal::AudioSourceComponent::SetVolumeValue(float value) { volume = value; }

std::pair<bool, std::string> AudioSourceComponent::SetSpeed(float newSpeed) {
    speed = newSpeed;
    AM().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AM().GetSound(sound_name);
    if (soundHandle == nullptr) return {false, "AudioSourceComponent error: SetSpeed(). No sounds founds linked to the name " + sound_name + "."};

    this->result = soundHandle->setMusicSpeed(newSpeed);
    auto trySetSpeed = AM().CheckFMODResult(this->result);
    if (!trySetSpeed.first) return trySetSpeed;


    return {true, "Speed from AudioSource" + sound_name + "succesfully set."};
}

std::pair<bool, std::string> AudioSourceComponent::SetMinMaxDistance(float minDistance, float maxDistance) {
    min_distance = minDistance * DISTANCE_FACTOR;
    max_distance = maxDistance * DISTANCE_FACTOR;

    AM().NameToLower(sound_name);
    auto soundHandle = AM().GetSound(sound_name);
    if (soundHandle == nullptr) return {false, "AudioSourceComponent error: SetMinMaxDistance(). Sound was not found"};
    this->result = soundHandle->set3DMinMaxDistance(min_distance, max_distance);
    auto trySetMinMaxDistance = AM().CheckFMODResult(this->result);
    if (!trySetMinMaxDistance.first) return trySetMinMaxDistance;
    return {true, "Minimum and maximum rolloff distances set sucessfully"};
}
void VeryReal::AudioSourceComponent::SetMinMaxDistanceValue(float minDistance, float maxDistance) { 
    min_distance = minDistance * DISTANCE_FACTOR;
    max_distance = maxDistance * DISTANCE_FACTOR;
}
std::pair<bool, std::string> AudioSourceComponent::SetMode(FMOD_MODE newMode) {
    AM().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AM().GetSound(sound_name);
    if (soundHandle == nullptr) return {false, "AudioSourceComponent error: SetMode(). Sound with the name " + sound_name + " was not found."};
    FMOD_MODE soundMode;
    this->result = soundHandle->getMode(&soundMode);
    auto tryGetMode = AM().CheckFMODResult(this->result);
    if (!tryGetMode.first) return tryGetMode;
    FMOD_MODE newSoundMode;
    newSoundMode = soundMode | newMode;
    this->result = soundHandle->setMode(newSoundMode);
    auto trySetMode = AM().CheckFMODResult(this->result);
    if (!trySetMode.first) return trySetMode;
    soundHandle->getMode(&soundMode);
    tryGetMode = AM().CheckFMODResult(this->result);
    if (!tryGetMode.first) return tryGetMode;

#ifdef _DEBUG
    if (soundMode & FMOD_3D)
        std::cout << "3d"
                  << " ";
    if (soundMode & FMOD_3D_LINEARROLLOFF)
        std::cout << "atenuacion"
                  << " ";
    if (soundMode & FMOD_LOOP_NORMAL)
        std::cout << "loop"
                  << " ";
#endif

    return {true, "Mode set succesfully."};
}

void AudioSourceComponent::SetSourcePath(std::string path) { sound_path = path; }

void AudioSourceComponent::SetSourceName(std::string name) { sound_name = name; }

void AudioSourceComponent::SetGroupChannelName(std::string name) { sound_group = name; }

void AudioSourceComponent::SetLoop(bool lop) { loop = lop; }

void AudioSourceComponent::SetIsThreeD(bool threeD) { is_three_d = threeD; }

void AudioSourceComponent::SetPlayOnStart(bool playOnStart) { play_on_start = playOnStart; }

float AudioSourceComponent::GetVolume() { return volume; }
