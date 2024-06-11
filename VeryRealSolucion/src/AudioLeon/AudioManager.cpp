#pragma once
#include "AudioManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <algorithm>

using namespace VeryReal;
using namespace FMOD;

AudioManager::AudioManager() { result = FMOD_OK; }

std::pair<bool, std::string> AudioManager::InitManager() {
    this->result = FMOD::System_Create(&sound_system);   // Create the main system object.
    auto tryCreateAudioSystem = CheckFMODResult(result);
    if (!tryCreateAudioSystem.first) return tryCreateAudioSystem;

    this->result = sound_system->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);   // Initialize FMOD.
    auto tryInitAudioSystem = CheckFMODResult(result);
    if (!tryInitAudioSystem.first) return tryInitAudioSystem;

    this->result = sound_system->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);
    auto trySet3DSettings = CheckFMODResult(result);
    if (!trySet3DSettings.first) return trySet3DSettings;

    this->result = sound_system->createChannelGroup("master", &master);
    auto tryCreateMasterChannel = CheckFMODResult(this->result);
    if (!tryCreateMasterChannel.first) return tryCreateMasterChannel;
    channel_group_maps ["master"] = master;

    this->result = sound_system->createChannelGroup("effects", &effects);
    auto tryCreateEffectsChannel = CheckFMODResult(this->result);
    if (!tryCreateEffectsChannel.first) return tryCreateEffectsChannel;
    channel_group_maps ["effects"] = effects;

    this->result = sound_system->createChannelGroup("music", &music);
    auto tryCreateMusicChannel = CheckFMODResult(this->result);
    if (!tryCreateMusicChannel.first) return tryCreateMusicChannel;
    channel_group_maps ["music"] = music;

    this->result = master->addGroup(effects);
    auto tryAddEffectsToMaster = CheckFMODResult(this->result);
    if (!tryAddEffectsToMaster.first) return tryAddEffectsToMaster;

    this->result = master->addGroup(music);
    auto tryAddMusicToMaster = CheckFMODResult(this->result);
    if (!tryAddMusicToMaster.first) return tryAddMusicToMaster;

    listeners = std::vector<bool>(FMOD_MAX_LISTENERS, false);   // Vector used to know which listeners are being used

    channels_vector.reserve(MAX_CHANNELS);
    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels_vector.push_back(0);
    }

    auto tryInitRecordAudio = InitAudioRecording();
    if (!tryInitRecordAudio.first) return tryInitRecordAudio;


    return {true, "AudioManager sucesfully initialized"};
}

std::pair<bool, std::string> AudioManager::InitAudioRecording() {
    int nativeRate = 0;
    int nativeChannels = 0;

    this->result = sound_system->getRecordDriverInfo(0, NULL, 0, NULL, &nativeRate, NULL, &nativeChannels, NULL);
    auto tryGetRecordDriver = CheckFMODResult(result);
    if (!tryGetRecordDriver.first) return tryGetRecordDriver;

    FMOD_CREATESOUNDEXINFO exinfo = {0};
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels = nativeChannels;
    exinfo.format = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = nativeRate;
    exinfo.length = nativeRate * sizeof(short) * nativeChannels; /* 1 second buffer, size here doesn't change latency */

    this->result = sound_system->createSound(0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &mic_sound);
    auto tryCreateRecordingAudio = CheckFMODResult(result);
    if (!tryCreateRecordingAudio.first) return tryCreateRecordingAudio;

    this->result = sound_system->recordStart(0, mic_sound, true);
    auto tryRecordStart = CheckFMODResult(result);
    if (!tryRecordStart.first) return tryRecordStart;

    unsigned int soundLength = 0;
    this->result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
    auto tryGetLength = CheckFMODResult(result);
    if (!tryGetLength.first) return tryGetLength;

    return {true, "Audio recording initialized succesfully."};
}

std::pair<bool, std::string> AudioManager::CheckFMODResult(FMOD_RESULT FMODResult) {
    if (FMODResult != FMOD_OK) {
        return {false, FMOD_ErrorString(FMODResult)};
    }
    return {true, FMOD_ErrorString(FMODResult)};
}

FMOD::Sound* AudioManager::GetSound(std::string soundName) {
    NameToLower(soundName);
    auto returnedSound = sounds_map.find(soundName);
    if (returnedSound == sounds_map.end()) return nullptr;
    return returnedSound->second;
}

FMOD::Channel* AudioManager::GetChannel(std::string soundName) {
    NameToLower(soundName);
    FMOD::Sound* soundHandle = GetSound(soundName);
    if (soundHandle != nullptr) {
        auto returnedChannel = last_played_map.find(soundHandle);
        if (returnedChannel == last_played_map.end()) return nullptr;
        return channels_vector [returnedChannel->second];
    }
    else {
        return nullptr;
    }
}

FMOD::ChannelGroup* AudioManager::GetGroupChannel(std::string channelGroupName) {
    NameToLower(channelGroupName);
    auto returnedGroup = channel_group_maps.find(channelGroupName);
    if (returnedGroup == channel_group_maps.end()) return nullptr;
    return returnedGroup->second;
}

std::vector<FMOD::Channel*> AudioManager::GetChannelsVector() { return channels_vector; }

std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> AudioManager::GetLastPlayedMap() { return last_played_map; }

void VeryReal::AudioManager::setChannelValue(int pos, FMOD::Channel* newChannel) { channels_vector [pos] = newChannel; }

std::pair<bool, std::string> AudioManager::ChangeChannelVolume(std::string channelGroupName, float volume) {
    NameToLower(channelGroupName);
    auto returnedGroup = channel_group_maps.find(channelGroupName);
    if (returnedGroup == channel_group_maps.end()) return {false, "No channel group with the name " + channelGroupName};
    this->result = returnedGroup->second->setVolume(volume);
    return CheckFMODResult(this->result);
}

void AudioManager::NameToLower(std::string& name) {
    name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
}

AudioManager::~AudioManager() {
    for (std::pair<std::string, Sound*> s : sounds_map) {
        result = s.second->release();
        CheckFMODResult(result);
    }
    sounds_map.clear();

    result = sound_system->close();
    CheckFMODResult(result);

    result = sound_system->release();
    CheckFMODResult(result);
}

void AudioManager::Update(const double& dt) {
    this->result = sound_system->update();
    auto tryUpdate = CheckFMODResult(result);
    if (!tryUpdate.first) std::cout << tryUpdate.second << std::endl;
}

FMOD_VECTOR AudioManager::V3ToFmodV3(VeryReal::Vector3 conversion) const {
    FMOD_VECTOR newVector{};
    newVector.x = conversion.GetX();
    newVector.y = conversion.GetY();
    newVector.z = conversion.GetZ();
    return newVector;
}

FMOD::System* AudioManager::GetSoundSystem() { return sound_system; }

void AudioManager::AddNewSound(std::pair<std::string, FMOD::Sound*> newSound) { sounds_map.insert(newSound); }

void VeryReal::AudioManager::SetLastPlayedMap(FMOD::Sound* sound, int channelNumber) { last_played_map [sound] = channelNumber; }

std::pair<bool, std::string> AudioManager::StopEverySound() {
    for (auto i : channels_vector) {
        this->result = i->stop();
        auto tryStopSounds = CheckFMODResult(this->result);
        if (!tryStopSounds.first) return tryStopSounds;
    }
    return {true, "Every sound stopped succesfully."};
}
std::pair<bool, std::string> AudioManager::PauseEverySound() {
    for (auto i : channels_vector) {
        this->result = i->setPaused(true);
        auto tryPauseSounds = CheckFMODResult(this->result);
        if (!tryPauseSounds.first) return tryPauseSounds;
    }
    return {true, "Every sound paused succesfully."};
}
std::pair<bool, std::string> AudioManager::ResumeEverySound() {
    for (auto i : channels_vector) {
        this->result = i->setPaused(false);
        auto tryResumeSounds = CheckFMODResult(this->result);
        if (!tryResumeSounds.first) return tryResumeSounds;
    }
    return {true, "Every sound resumed succesfully."};
}


std::pair<bool, std::string> AudioManager::DeleteSound(std::string soundName) {
    NameToLower(soundName);
    auto returnedSound = GetSound(soundName);
    returnedSound->release();
    sounds_map.erase(soundName);
    FMOD::Sound* soundHandle = GetSound(soundName);
    if (soundHandle == nullptr) return {false, "No sound found with that name loaded in the AudioManager to delete."};

    last_played_map.erase(soundHandle);

    return {true, soundName + " sound deleted from the AudioManager."};
}

void AudioManager::RemoveListener(int index) { listeners [index] = false; }

std::pair<bool, std::string> AudioManager::CreateChannelGroup(std::string groupName) {
    NameToLower(groupName);
    const char* channelGroupName = groupName.c_str();
    if ((int(channelGroupName [0]) > 96) && (int(channelGroupName [0]) < 122)) {
        char* copyGroupName = _strdup(channelGroupName);   // Copiar la cadena original
        channelGroupName = copyGroupName;
        free(copyGroupName);
    }
    auto channelGroup = channel_group_maps.find(channelGroupName);
    if (channelGroup == channel_group_maps.end()) {
        FMOD::ChannelGroup* newChannelGroup;
        this->result = sound_system->createChannelGroup(channelGroupName, &newChannelGroup);
        auto tryCreateChannelGroup = CheckFMODResult(this->result);
        if (!tryCreateChannelGroup.first) return tryCreateChannelGroup;
        std::pair<std::string, FMOD::ChannelGroup*> newGroup(channelGroupName, newChannelGroup);
        channel_group_maps.insert(newGroup);
        this->result = master->addGroup(newChannelGroup);
        auto tryAddGroup = CheckFMODResult(this->result);
        if (!tryAddGroup.first) return tryAddGroup;
        return {true, "Channel group created succesfully."};
    }
    return {false, "Impossible to create a new channel group."};
}

std::pair<bool, std::string> AudioManager::SetGroupChannelVolume(std::string groupName, float newVolume) {
    NameToLower(groupName);
    const char* channelGroup = groupName.c_str();
    FMOD::ChannelGroup* changedGroup = GetGroupChannel(channelGroup);
    if (changedGroup == nullptr) {
        return {false, "No group channel with the name " + groupName};
    }
    else {
        return ChangeChannelVolume(channelGroup, newVolume);
    }
}

std::pair<bool, std::string> AudioManager::GetGroupChannelVolume(std::string groupName, float &volume) {
    NameToLower(groupName);
    FMOD::ChannelGroup* groupChannel = GetGroupChannel(groupName);
    if (groupChannel != nullptr) {
        this->result = groupChannel->getVolume(&volume);
        auto tryGetVolume = CheckFMODResult(this->result);
        if (!tryGetVolume.first) return tryGetVolume;
        return {true, "Volume of group channel " + groupName + " changed succesfully."};
    }
    else {
        return {false, "No group channel with the name " + groupName};
    }
}

float AudioManager::InputSoundIntensity() {
    // Longitud del sonido
    unsigned int soundLength = 0;
    this->result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
    auto tryGetMicLength = CheckFMODResult(result);
    if (!tryGetMicLength.first) std::cout << tryGetMicLength.second << std::endl;

    int numSamples = soundLength / sizeof(short);   // Numero de muestras de audio

    // Obtener los datos de audio
    short* audioData = 0;
    this->result = mic_sound->lock(0, soundLength, (void**)&audioData, nullptr, &soundLength, nullptr);
    auto tryMicSoundLock = CheckFMODResult(result);
    if (!tryMicSoundLock.first) std::cout << tryMicSoundLock.second << std::endl;

    // Calcular la "potencia" del sonido
    float totalEnergy = 0.0f;
    for (int i = 0; i < numSamples; ++i) {
        float sample = static_cast<float>(audioData [i]) / 32768.0f;   // Normalizar la muestra
        totalEnergy += sample * sample;                                // Sumar el cuadrado de la muestra
    }

    this->result = mic_sound->unlock(audioData, nullptr, soundLength, 0);
    auto tryMicUnlock = CheckFMODResult(result);
    if (!tryMicUnlock.first) std::cout << tryMicUnlock.second << std::endl;

    // Calcular la intensidad (en un rango de 0 a 1)
    float intensity = totalEnergy / numSamples;
    return intensity;
}