#pragma once
#include "AudioSourceComponent.h"
#include "..\AudioLeon.h"
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>
#include "VariantClass.h"
#include <fmod_studio.hpp>

using namespace VeryReal;
using namespace std;

AudioSourceComponent::AudioSourceComponent() : 
    volume(0), speed(1), min_distance(0), max_distance(FLT_MAX), sound_channel(1), 
    sound_group("default"), sound_path("none"), sound_name("unknown"), 
    playing(false), loop(false), is_three_d(false), play_on_start(false), result(FMOD_OK){}

AudioSourceComponent::~AudioSourceComponent() {
    AL().DeleteSound(sound_name);
}
bool AudioSourceComponent::InitComponent(std::string name, std::string path, bool onstart, std::string groupchannel, float volume,
    bool threed, bool loop, float mindistance, float maxdistance) {

    SetSourceName(name);
    SetSourcePath(path);
    SetPlayOnStart(onstart);
    SetGroupChannelName(groupchannel);
    SetVolume(volume);
    SetIsThreeD(threed);
    SetLoop(loop);
    SetMinMaxDistance(mindistance, maxdistance);
    return true;
}
bool AudioSourceComponent::Create3DSound()
{
    std::string soundPath = "Assets/SONIDOS/" + sound_path;
    AL().NameToLower(sound_name);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(sound_name);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
    }

    if (!AL().CheckFMODResult(this->result)) return false;

    this->result = newSoundHandle->set3DMinMaxDistance(min_distance, max_distance);
    if (!AL().CheckFMODResult(this->result)) return false;

    if (AL().CheckFMODResult(this->result)) {
        std::pair<std::string, FMOD::Sound*> newSound(sound_name, newSoundHandle);
        AL().AddNewSound(newSound);
        
#ifdef _DEBUG
        std::cout << "Sound created." << "\n";
#endif // DEBUG
        return true;
    }
    else {
        return false;
    }
}

bool AudioSourceComponent::CreateNormalSound()
{
    std::string soundPath = "Assets/SONIDOS/" + sound_path;
    AL().NameToLower(sound_name);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(sound_name);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
    }

    if (AL().CheckFMODResult(this->result)) {
        std::pair<std::string, FMOD::Sound*> newSound(sound_name, newSoundHandle);
        AL().AddNewSound(newSound);
#ifdef _DEBUG
        std::cout << "Sound created." << "\n";
#endif // DEBUG
        return true;
    }
    else {
        return false;
    }
}

bool AudioSourceComponent::Set3DSoundAtributes(VeryReal::Vector3 position, VeryReal::Vector3 velocity)
{
    AL().NameToLower(sound_name);
    FMOD::Channel* channelHandle = AL().GetChannel(sound_name);
    if (channelHandle == nullptr) return false;
    FMOD_VECTOR p = AL().V3ToFmodV3(position), v = AL().V3ToFmodV3(velocity);

    channelHandle->set3DAttributes(&p, &v);
    return true;
}

bool AudioSourceComponent::PlayAudioSource(std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume)
{
    AL().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;

    FMOD::ChannelGroup* playedChannelGroup = AL().GetGroupChannel(channelGroup);
    if (playedChannelGroup == nullptr) return false;

    FMOD_MODE finalSoundMode;
    soundHandle->getMode(&finalSoundMode);

    FMOD::Channel* reproChannel = AL().GetChannel(sound_name);
    if (reproChannel == nullptr) {
        for (int i = 0; i < AL().GetChannelsVector().size(); i++) {
            bool IsPlaying;
            AL().GetChannelsVector()[i]->isPlaying(&IsPlaying);

            if (IsPlaying) continue;

            FMOD::Channel* channelUsed;

            this->result = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &channelUsed);
            AL().CheckFMODResult(this->result);

            AL().setChannelValue(i, channelUsed);

            reproChannel = AL().GetChannelsVector()[i];

            AL().GetChannelsVector()[i]->setVolume(channelVolume);

           AL().GetLastPlayedMap()[soundHandle] = i;

            break;
        }
    }
    else {
        this->result = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &reproChannel);
        AL().CheckFMODResult(this->result);
    }

    if (finalSoundMode & FMOD_3D) {
        FMOD_VECTOR v = AL().V3ToFmodV3(*channelVel), p = AL().V3ToFmodV3(*channelPos);
        reproChannel->set3DAttributes(&p, &v);
    }

    return true;
}

bool AudioSourceComponent::StopSound()
{
    AL().NameToLower(sound_name);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(sound_name);
    if (channel != nullptr) {
        this->result = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->result);
        channel->stop();
        return true;
    }
    else {
        return false;
    }
}

bool AudioSourceComponent::PauseSound(bool Pause)
{
    AL().NameToLower(sound_name);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(sound_name);
    if (channel != nullptr) {
        this->result = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->result);
        channel->setPaused(Pause);
        return true;
    }
    else {
        return false;
    }
}

void AudioSourceComponent::Start()
{
    transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>();

    if (!transform) {
        ErrorInf().showErrorMessageBox("AudioSourceComponent error", "An entity doesn't have transform component", EI_ERROR);
        //sceneManager().quit();
        return;
    }

    // Create a 3D sound or a normal sound
    if (is_three_d)
        Create3DSound();
    else
        CreateNormalSound();

    if (play_on_start)
        Play();
}

void AudioSourceComponent::Update(const double& dt)
{
    if (is_three_d) {
        Set3DSoundAtributes(transform->GetPosition(), transform->GetVelocity());
    }
}

void AudioSourceComponent::Play()
{
    VeryReal::Vector3 pos = transform->GetPosition();
    VeryReal::Vector3 vel = transform->GetVelocity();
    PlayAudioSource(sound_group, &pos, &vel, volume);

    playing = true;
}

void AudioSourceComponent::Stop()
{
    StopSound();
}

void AudioSourceComponent::Pause()
{
    PauseSound(true);
}

void AudioSourceComponent::Resume()
{
    PauseSound(false);
}

bool AudioSourceComponent::IsPlaying()
{
    return playing;
}

bool AudioSourceComponent::SetVolume(float value) {
    volume = value;
    AL().NameToLower(sound_name);
    FMOD::Channel* channel = AL().GetChannel(sound_name);
    if (channel != nullptr) {
        result = channel->setVolume(value);
        return AL().CheckFMODResult(result);
    }
    else {
        return false;
    }
}

bool AudioSourceComponent::SetSpeed(float newSpeed) {
    speed = newSpeed;
    AL().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;

    this->result = soundHandle->setMusicSpeed(newSpeed);

    return AL().CheckFMODResult(this->result);
}

bool AudioSourceComponent::SetMinMaxDistance(float minDistance, float maxDistance)
{
    min_distance = minDistance * DISTANCE_FACTOR;
    max_distance = maxDistance * DISTANCE_FACTOR;

    AL().NameToLower(sound_name);
    auto soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;
    soundHandle->set3DMinMaxDistance(min_distance, max_distance);
    return true;
}

bool AudioSourceComponent::SetMode(FMOD_MODE newMode)
{
    AL().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;
    FMOD_MODE soundMode;
    soundHandle->getMode(&soundMode);
    FMOD_MODE newSoundMode;
    newSoundMode = soundMode | newMode;
    result = soundHandle->setMode(newSoundMode);
    soundHandle->getMode(&soundMode);

#ifdef _DEBUG
    if (soundMode & FMOD_3D)
        std::cout << "3d" << " ";
    if (soundMode & FMOD_3D_LINEARROLLOFF)
        std::cout << "atenuacion" << " ";
    if (soundMode & FMOD_LOOP_NORMAL)
        std::cout << "loop" << " ";
#endif

    return AL().CheckFMODResult(result);
}

void AudioSourceComponent::SetSourcePath(std::string path) {
    sound_path = path;
}

void AudioSourceComponent::SetSourceName(std::string name) {
    sound_name = name;
}

void AudioSourceComponent::SetGroupChannelName(std::string name) {
    sound_group = name;
}

void AudioSourceComponent::SetLoop(bool lop) {
    loop = lop;
}

void AudioSourceComponent::SetIsThreeD(bool threeD) {
    is_three_d = threeD;
}

void AudioSourceComponent::SetPlayOnStart(bool playOnStart) {
    play_on_start = playOnStart;
}

float AudioSourceComponent::GetVolume() {
    return volume;
}
