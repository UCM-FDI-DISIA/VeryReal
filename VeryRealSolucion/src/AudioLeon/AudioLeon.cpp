#include "AudioLeon.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <algorithm>
using namespace VeryReal;
Audio_Leon::Audio_Leon() {
	result = FMOD::System_Create(&sound_system); // Create the main system object.
	CheckFMODResult(result);

	result = sound_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	CheckFMODResult(result);

	result = sound_system->set3DSettings(0.0f, DISTANCE_FACTOR, ROLLOFF_SCALE);
	CheckFMODResult(result);

	sound_system->createChannelGroup("master", &master);
	channel_group_maps["master"] = master;
	sound_system->createChannelGroup("effects", &effects);
	channel_group_maps["effects"] = effects;
	sound_system->createChannelGroup("music", &music);
	channel_group_maps["music"] = music;

	master->addGroup(effects);
	master->addGroup(music);

	listeners = std::vector<bool>(FMOD_MAX_LISTENERS, false); // Vector used to know which listeners are being used

	channels_vector.reserve(MAX_CHANNELS);
	for (int i = 0; i < MAX_CHANNELS; i++) {
		channels_vector.push_back(nullptr);
	}
	
	InitAudioRecording();
}

void Audio_Leon::InitAudioRecording() {
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

bool Audio_Leon::CheckFMODResult(FMOD_RESULT FMODResult) {
	if (FMODResult != FMOD_OK) {
	#ifdef _DEBUG
		printf("FMOD error! (%d) %s\n", FMODResult, FMOD_ErrorString(FMODResult));
	#endif
		return false;
	}
	return true;
}

FMOD::Sound* Audio_Leon::GetSound(std::string soundName) {
	NameToLower(soundName);
	auto returnedSound = sounds_map.find(soundName);
	if (returnedSound == sounds_map.end()) return nullptr;
	return returnedSound->second;
}

FMOD::Channel* Audio_Leon::GetChannel(std::string soundName) {
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

FMOD::ChannelGroup* Audio_Leon::GetGroupChannel(std::string channelGroupName) {
	NameToLower(channelGroupName);
	auto returnedGroup = channel_group_maps.find(channelGroupName);
	if (returnedGroup == channel_group_maps.end()) return nullptr;
	return returnedGroup->second;
}

std::vector<FMOD::Channel*> Audio_Leon::GetChannelsVector() {
	return channels_vector;
}

std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> Audio_Leon::GetLastPlayedMap() {
	return last_played_map;
}

bool Audio_Leon::ChangeChannelVolume(std::string channelGroupName, float volume) {
	NameToLower(channelGroupName);
	auto returnedGroup = channel_group_maps.find(channelGroupName);
	if (returnedGroup == channel_group_maps.end()) return false;
	result = returnedGroup->second->SetVolume(volume);
	return CheckFMODResult(result);
}

void Audio_Leon::NameToLower(std::string& name) {
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace),
		name.end());
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
}

Audio_Leon::~Audio_Leon() {
	for (auto s : sounds_map) {
		result = s.second->release();
		CheckFMODResult(result);
	}
	sounds_map.clear();

	result = sound_system->close();
	CheckFMODResult(result);

	result = sound_system->release();
	CheckFMODResult(result);
}

void Audio_Leon::SystemRefresh(const double& dt) {
	result = sound_system->update();
	CheckFMODResult(result);
}

FMOD_VECTOR Audio_Leon::V3ToFmodV3(VeryReal::Vector3 conversion) const {
	FMOD_VECTOR newVector;
	newVector.x = conversion.GetX(); newVector.y = conversion.GetY(); newVector.z = conversion.GetZ();
	return newVector;
}

FMOD::System* Audio_Leon::GetSoundSystem() {
	return sound_system;
}

void Audio_Leon::AddNewSound(std::pair<std::string, FMOD::Sound*> newSound) {
	sounds_map.insert(newSound);
}

bool Audio_Leon::StopEverySound() {
	for (auto i : channels_vector) {
		i->Stop();
	}
	return true;
}

bool Audio_Leon::DeleteSound(std::string soundName) {
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle == nullptr) return false;

	last_played_map.erase(soundHandle);

	return CheckFMODResult(result);
}

void Audio_Leon::RemoveListener(int index) {
	listeners[index] = false;
}

bool Audio_Leon::CreateChannelGroup(std::string groupName) {
	NameToLower(groupName);
	const char* channelGroupName = groupName.c_str();
	if ((int(channelGroupName[0]) > 96) && (int(channelGroupName[0]) < 122)) channelGroupName[0] - 32;
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

bool Audio_Leon::SetGroupChannelVolume(std::string groupName, float newVolume) {
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

float Audio_Leon::GetGroupChannelVolume(std::string groupName) {
	NameToLower(groupName);
	FMOD::ChannelGroup* groupChannel = GetGroupChannel(groupName);
	float volume;
	if (groupChannel != nullptr) {
		result = groupChannel->GetVolume(&volume);
		CheckFMODResult(result);
		return volume;
	}
}

float Audio_Leon::InputSoundIntensity() {
	// Longitud del sonido
	unsigned int soundLength = 0;
	result = mic_sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
	CheckFMODResult(result);

	int numSamples = soundLength / sizeof(short); // Numero de muestras de audio

	// Obtener los datos de audio
	short* audioData;
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

void Audio_Leon::AudioSourceListenerTest()
{
	std::string soundPath = "musicaCircuito.mp3";
	std::string soundName = "test";
	float minDistance = 0.1f;
	float maxDistance = 9999;

	soundPath = "Assets/" + soundPath;
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
			AL().GetChannelsVector()[i]->IsPlaying(&IsPlaying);

			if (IsPlaying) continue;
			this->result = AL().GetSoundSystem()->playSound(newSoundHandle, playedChannelGroup, false, &AL().GetChannelsVector()[i]);
			AL().CheckFMODResult(this->result);

			reproChannel = AL().GetChannelsVector()[i];

			AL().GetChannelsVector()[i]->SetVolume(0.01f);

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

//void Audio_Leon::startRecording() {
//	std::cout << "a";
//	FMOD::Sound* audio;
//	result = this->sound_system->createSound(0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, 0, &audio);
//	result = this->sound_system->recordStart(0, audio, true);
//	std::cout << "a";
//	std::cin.get();
//	result = this->sound_system->recordStop(0);
//
//	const int fftSize = 1024;
//	float* spectrumData = new float[fftSize];
//	result = channel->getSpectrum(spectrumData, fftSize, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE);
//}