#pragma once
#include "AudioLeon.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <algorithm>

using namespace VeryReal;
using namespace FMOD;

void AudioLeon::InitManager() {
    result = FMOD::System_Create(&sound_system);   // Create the main system object.
    CheckFMODResult(result);

    result = sound_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);   // Initialize FMOD.
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
        channels_vector.push_back(nullptr);
    }

    InitAudioRecording();
}

void AudioLeon::InitAudioRecording() {
	int nativeRate = 0;
	int nativeChannels = 0;
	result = sound_system->getRecordDriverInfo(0, NULL, 0, NULL, &nativeRate, NULL, &nativeChannels, NULL);
	CheckFMODResult(result);

	FMOD_CREATESOUNDEXINFO exinfo = { 0 };
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

bool AudioLeon::CheckFMODResult(FMOD_RESULT FMODResult) {
	if (FMODResult != FMOD_OK) {
	#ifdef _DEBUG
		printf("FMOD error! (%d) %s\n", FMODResult, FMOD_ErrorString(FMODResult));
	#endif
		return false;
	}
	return true;
}

FMOD::Sound* AudioLeon::GetSound(std::string soundName) {
	NameToLower(soundName);
	auto returnedSound = sounds_map.find(soundName);
	if (returnedSound == sounds_map.end()) return nullptr;
	return returnedSound->second;
}

FMOD::Channel* AudioLeon::GetChannel(std::string soundName) {
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle != nullptr) {
		auto returnedChannel = last_played_map.find(soundHandle);
		if (returnedChannel == last_played_map.end()) return nullptr;
		return channels_vector[returnedChannel->second];
	}
	else {
		return nullptr;
	}
}

FMOD::ChannelGroup* AudioLeon::GetGroupChannel(std::string channelGroupName) {
	NameToLower(channelGroupName);
	auto returnedGroup = channel_group_maps.find(channelGroupName);
	if (returnedGroup == channel_group_maps.end()) return nullptr;
	return returnedGroup->second;
}

std::vector<FMOD::Channel*> AudioLeon::GetChannelsVector() {
	return channels_vector;
}

std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> AudioLeon::GetLastPlayedMap() {
	return last_played_map; }

void VeryReal::AudioLeon::setChannelValue(int pos, FMOD::Channel* newChannel) { 
	channels_vector [pos] = newChannel;
}

bool AudioLeon::ChangeChannelVolume(std::string channelGroupName, float volume) {
	NameToLower(channelGroupName);
	auto returnedGroup = channel_group_maps.find(channelGroupName);
	if (returnedGroup == channel_group_maps.end()) return false;
	result = returnedGroup->second->setVolume(volume);
	return CheckFMODResult(result);
}

void AudioLeon::NameToLower(std::string& name) {
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace),
		name.end());
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
}

AudioLeon::~AudioLeon() {
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

void AudioLeon::SystemRefresh(const double& dt) {
	result = sound_system->update();
	CheckFMODResult(result);
}

FMOD_VECTOR AudioLeon::V3ToFmodV3(VeryReal::Vector3 conversion) const {
    FMOD_VECTOR newVector {};
	newVector.x = conversion.GetX(); newVector.y = conversion.GetY(); newVector.z = conversion.GetZ();
	return newVector;
}

FMOD::System* AudioLeon::GetSoundSystem() {
	return sound_system;
}

void AudioLeon::AddNewSound(std::pair<std::string, FMOD::Sound*> newSound) {
	sounds_map.insert(newSound);
}

bool AudioLeon::StopEverySound() {
	for (auto i : channels_vector) {
		i->stop();

	}
	return true;
}
bool AudioLeon::PauseEverySound() {
	for (auto i : channels_vector) {
        i->setPaused(true);
	}
	return true;
}
bool AudioLeon::ResumeEverySound() {
	for (auto i : channels_vector) {
        i->setPaused(false);
	}
	return true;
}


bool AudioLeon::DeleteSound(std::string soundName) {
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle == nullptr) return false;

	last_played_map.erase(soundHandle);

	return CheckFMODResult(result);
}

void AudioLeon::RemoveListener(int index) {
	listeners[index] = false;
}

bool AudioLeon::CreateChannelGroup(std::string groupName) {
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

bool AudioLeon::SetGroupChannelVolume(std::string groupName, float newVolume) {
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

float AudioLeon::GetGroupChannelVolume(std::string groupName) {
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

float AudioLeon::InputSoundIntensity() {
	// Longitud del sonido
	unsigned int soundLength = 0;
	result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
	CheckFMODResult(result);

	int numSamples = soundLength / sizeof(short); // Numero de muestras de audio

	// Obtener los datos de audio
	short* audioData = 0;
	result = mic_sound->lock(0, soundLength, (void**)&audioData, nullptr, &soundLength, nullptr);
	CheckFMODResult(result);

	// Calcular la "potencia" del sonido
	float totalEnergy = 0.0f;
	for (int i = 0; i < numSamples; ++i) {
		float sample = static_cast<float>(audioData[i]) / 32768.0f; // Normalizar la muestra
		totalEnergy += sample * sample; // Sumar el cuadrado de la muestra
	}

	result = mic_sound->unlock(audioData, nullptr, soundLength, 0);
	CheckFMODResult(result);

	// Calcular la intensidad (en un rango de 0 a 1)
	float intensity = totalEnergy / numSamples;
	return intensity;
}

void AudioLeon::AudioSourceListenerTest()
{
	std::string soundPath = "musicaCircuito.mp3";
	std::string soundName = "test";
	float minDistance = 0.1f;
	float maxDistance = 9999;

	soundPath = "Assets/SONIDOS/" + soundPath;
	AL().NameToLower(soundName);
	FMOD::Sound* newSoundHandle;

	this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);

	this->result = newSoundHandle->set3DMinMaxDistance(minDistance, maxDistance);

	if (AL().CheckFMODResult(this->result)) {
		std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
		AL().AddNewSound(newSound);
	}

	AL().NameToLower(soundName);
	newSoundHandle = AL().GetSound(soundName);
	if (newSoundHandle != nullptr) {
		std::cout << "Sonido \n";
	}

	FMOD::ChannelGroup* playedChannelGroup = AL().GetGroupChannel("music");
	if (playedChannelGroup != nullptr) {
		std::cout << "Grupo de canal \n";
	}

	FMOD_MODE finalSoundMode;
	newSoundHandle->getMode(&finalSoundMode);

	FMOD::Channel* reproChannel = AL().GetChannel(soundName);
	if (reproChannel == nullptr) {
		for (int i = 0; i < AL().GetChannelsVector().size(); i++) {
			bool IsPlaying;
			AL().GetChannelsVector()[i]->isPlaying(&IsPlaying);

			if (IsPlaying) continue;
			this->result = AL().GetSoundSystem()->playSound(newSoundHandle, playedChannelGroup, false, &AL().GetChannelsVector()[i]);
			AL().CheckFMODResult(this->result);

			reproChannel = AL().GetChannelsVector()[i];

			AL().GetChannelsVector()[i]->setVolume(0.01f);

			AL().GetLastPlayedMap()[newSoundHandle] = i;

			break;
		}
	}
	else {
		this->result = AL().GetSoundSystem()->playSound(newSoundHandle, playedChannelGroup, false, &reproChannel);
		AL().CheckFMODResult(this->result);
	}
	FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	reproChannel->set3DAttributes(&pos, &vel);


	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };

	AL().GetSoundSystem()->set3DListenerAttributes(0, &pos, &vel, &forward, &up);

}