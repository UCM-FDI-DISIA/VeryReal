#pragma once
#include "AudioManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <algorithm>

using namespace VeryReal;
using namespace FMOD;

AudioManager::AudioManager() { result = FMOD_OK; }

std::pair<bool, std::string> AudioManager::InitManager() {



    
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};
    //MIRAR ERRORES Y DEVOLVER {false, "Mensaje Error"};







    result = FMOD::System_Create(&sound_system);   // Create the main system object.
    CheckFMODResult(result);

    result = sound_system->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);   // Initialize FMOD.
    CheckFMODResult(result);

    result = sound_system->set3DSettings(DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);
    CheckFMODResult(result);

    sound_system->createChannelGroup("master", &master);
    channel_group_maps ["master"] = master;
    sound_system->createChannelGroup("effects", &effects);
    channel_group_maps ["effects"] = effects;
    sound_system->createChannelGroup("music", &music);
    channel_group_maps ["music"] = music;

    master->addGroup(effects);
    master->addGroup(music);

    listeners = std::vector<bool>(FMOD_MAX_LISTENERS, false);   // Vector used to know which listeners are being used

    channels_vector.reserve(MAX_CHANNELS);
    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels_vector.push_back(0);
    }

    InitAudioRecording();



    return {true, "AudioManager sucesfully initialized"};
}

void AudioManager::InitAudioRecording() {
    int nativeRate = 0;
    int nativeChannels = 0;
    result = sound_system->getRecordDriverInfo(0, NULL, 0, NULL, &nativeRate, NULL, &nativeChannels, NULL);
    CheckFMODResult(result);

    FMOD_CREATESOUNDEXINFO exinfo = {0};
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.numchannels = nativeChannels;
    exinfo.format = FMOD_SOUND_FORMAT_PCM16;
    exinfo.defaultfrequency = nativeRate;
    exinfo.length = nativeRate * sizeof(short) * nativeChannels; /* 1 second buffer, size here doesn't change latency */

    result = sound_system->createSound(0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, &exinfo, &mic_sound);
    CheckFMODResult(result);

    result = sound_system->recordStart(0, mic_sound, true);
    CheckFMODResult(result);

    unsigned int soundLength = 0;
    result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
    CheckFMODResult(result);
}

bool AudioManager::CheckFMODResult(FMOD_RESULT FMODResult) {
    if (FMODResult != FMOD_OK) {
#ifdef _DEBUG
        printf("FMOD error! (%d) %s\n", FMODResult, FMOD_ErrorString(FMODResult));
#endif
        return false;
    }
    return true;
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

bool AudioManager::ChangeChannelVolume(std::string channelGroupName, float volume) {
    NameToLower(channelGroupName);
    auto returnedGroup = channel_group_maps.find(channelGroupName);
    if (returnedGroup == channel_group_maps.end()) return false;
    result = returnedGroup->second->setVolume(volume);
    return CheckFMODResult(result);
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
    result = sound_system->update();
    CheckFMODResult(result);
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

bool AudioManager::StopEverySound() {
    for (auto i : channels_vector) {
        i->stop();
    }
    return true;
}
bool AudioManager::PauseEverySound() {
    for (auto i : channels_vector) {
        i->setPaused(true);
    }
    return true;
}
bool AudioManager::ResumeEverySound() {
    for (auto i : channels_vector) {
        i->setPaused(false);
    }
    return true;
}


bool AudioManager::DeleteSound(std::string soundName) {
    NameToLower(soundName);
    FMOD::Sound* soundHandle = GetSound(soundName);
    if (soundHandle == nullptr) return false;

    last_played_map.erase(soundHandle);

    return CheckFMODResult(result);
}

void AudioManager::RemoveListener(int index) { listeners [index] = false; }

bool AudioManager::CreateChannelGroup(std::string groupName) {
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
        sound_system->createChannelGroup(channelGroupName, &newChannelGroup);
        std::pair<std::string, FMOD::ChannelGroup*> newGroup(channelGroupName, newChannelGroup);
        channel_group_maps.insert(newGroup);
        master->addGroup(newChannelGroup);
        return true;
    }
    return false;
}

bool AudioManager::SetGroupChannelVolume(std::string groupName, float newVolume) {
    NameToLower(groupName);
    const char* channelGroup = groupName.c_str();
    FMOD::ChannelGroup* changedGroup = GetGroupChannel(channelGroup);
    if (changedGroup == nullptr) {
        return false;
    }
    else {
        return ChangeChannelVolume(channelGroup, newVolume);
    }
}

float AudioManager::GetGroupChannelVolume(std::string groupName) {
    NameToLower(groupName);
    FMOD::ChannelGroup* groupChannel = GetGroupChannel(groupName);
    float volume;
    if (groupChannel != nullptr) {
        result = groupChannel->getVolume(&volume);
        CheckFMODResult(result);
        return volume;
    }
    else {
        return -1;
    }
}

float AudioManager::InputSoundIntensity() {
    // Longitud del sonido
    unsigned int soundLength = 0;
    result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
    CheckFMODResult(result);

    int numSamples = soundLength / sizeof(short);   // Numero de muestras de audio

    // Obtener los datos de audio
    short* audioData = 0;
    result = mic_sound->lock(0, soundLength, (void**)&audioData, nullptr, &soundLength, nullptr);
    CheckFMODResult(result);

    // Calcular la "potencia" del sonido
    float totalEnergy = 0.0f;
    for (int i = 0; i < numSamples; ++i) {
        float sample = static_cast<float>(audioData [i]) / 32768.0f;   // Normalizar la muestra
        totalEnergy += sample * sample;                                // Sumar el cuadrado de la muestra
    }

    result = mic_sound->unlock(audioData, nullptr, soundLength, 0);
    CheckFMODResult(result);

    // Calcular la intensidad (en un rango de 0 a 1)
    float intensity = totalEnergy / numSamples;
    return intensity;
}