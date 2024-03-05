//// AudioLeon.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
////
//
//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//}
//
//// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
//// Depurar programa: F5 o menú Depurar > Iniciar depuración
//
//// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
////   2. Use la ventana de Team Explorer para conectar con el control de código fuente
////   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
////   4. Use la ventana Lista de errores para ver los errores
////   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
////   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
#include "AudioLeon.h"
#include <fmod.hpp>
#include <fmod_errors.h>

#include <algorithm>

AudioLeon::AudioLeon() {

	mResult = FMOD::System_Create(&mSoundSystem);      // Create the main system object.
	CheckFMODResult(mResult);

	mResult = mSoundSystem->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	CheckFMODResult(mResult);
	mResult = mSoundSystem->set3DSettings(0.0f, DISTANCE_FACTOR, ROLLOFF_SCALE);
	CheckFMODResult(mResult);

	mSoundSystem->createChannelGroup("master", &mMaster);
	mChannelGroupMaps["master"] = mMaster;
	mSoundSystem->createChannelGroup("effects", &mEffects);
	mChannelGroupMaps["effects"] = mEffects;
	mSoundSystem->createChannelGroup("music", &mMusic);
	mChannelGroupMaps["music"] = mMusic;


	mMaster->addGroup(mEffects);
	mMaster->addGroup(mMusic);

	mListeners = std::vector<bool>(FMOD_MAX_LISTENERS, false); // Vector used to know which listeners are being used

	mChannelsVector.reserve(MAX_CHANNELS);
	for (int i = 0; i < MAX_CHANNELS; i++) {
		mChannelsVector.push_back(nullptr);
	}
}

bool AudioLeon::CheckFMODResult(FMOD_RESULT FMODResult)
{
	if (FMODResult != FMOD_OK)
	{
#ifdef _DEBUG
		printf("FMOD error! (%d) %s\n", FMODResult, FMOD_ErrorString(FMODResult));
#endif
		return false;
	}
	return true;
}

FMOD::Sound* AudioLeon::GetSound(std::string soundName)
{
	NameToLower(soundName);
	auto returnedSound = mSoundsMap.find(soundName);
	if (returnedSound == mSoundsMap.end()) return nullptr;
	return returnedSound->second;
}

FMOD::Channel* AudioLeon::GetChannel(std::string soundName)
{
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle != nullptr) {
		auto returnedChannel = mLastPlayedMap.find(soundHandle);
		if (returnedChannel == mLastPlayedMap.end()) return nullptr;
		return mChannelsVector[returnedChannel->second];
	}
	else {
		return nullptr;
	}
}

FMOD::ChannelGroup* AudioLeon::GetGroupChannel(std::string channelGroupName)
{
	NameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return nullptr;
	return returnedGroup->second;
}

std::vector<FMOD::Channel*> AudioLeon::GetChannelsVector()
{
	return mChannelsVector;
}

std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> AudioLeon::GetLastPlayedMap()
{
	return mLastPlayedMap;
}

bool AudioLeon::changeChannelVolume(std::string channelGroupName, float volume)
{
	NameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return false;
	mResult = returnedGroup->second->setVolume(volume);
	return CheckFMODResult(mResult);
}

void AudioLeon::NameToLower(std::string& name)
{
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace),
		name.end());
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
}

AudioLeon::~AudioLeon()
{
	for (auto s : mSoundsMap)
	{
		mResult = s.second->release();
		CheckFMODResult(mResult);
	}
	mSoundsMap.clear();

	mResult = mSoundSystem->close();
	CheckFMODResult(mResult);

	mResult = mSoundSystem->release();
	CheckFMODResult(mResult);
}

void AudioLeon::systemRefresh(const double& dt)
{
	mResult = mSoundSystem->update();
	CheckFMODResult(mResult);
}

FMOD_VECTOR AudioLeon::V3ToFmodV3(VeryReal::Vector3 conversion) const
{
	FMOD_VECTOR newVector;
	newVector.x = conversion.GetX(); newVector.y = conversion.GetY(); newVector.z = conversion.GetZ();
	return newVector;
}

FMOD::System* AudioLeon::GetSoundSystem()
{
	return mSoundSystem;
}

void AudioLeon::AddNewSound(std::pair<std::string, FMOD::Sound*> newSound)
{
	mSoundsMap.insert(newSound);
}

bool AudioLeon::stopEverySound()
{
	for (auto i : mChannelsVector) {
		i->stop();
	}
	return true;
}

bool AudioLeon::deleteSound(std::string soundName)
{
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle == nullptr) return false;

	mLastPlayedMap.erase(soundHandle);

	return CheckFMODResult(mResult);
}

void AudioLeon::removeListener(int index)
{
	mListeners[index] = false;
}

bool AudioLeon::setMode(std::string soundName, FMOD_MODE newMode)
{
	NameToLower(soundName);
	FMOD::Sound* soundHandle = GetSound(soundName);
	if (soundHandle == nullptr) return false;
	FMOD_MODE soundMode;
	soundHandle->getMode(&soundMode);
	FMOD_MODE newSoundMode;
	newSoundMode = soundMode | newMode;
	mResult = soundHandle->setMode(newSoundMode);
	soundHandle->getMode(&soundMode);

#ifdef _DEBUG
	if (soundMode & FMOD_3D)
		std::cout << "3d" << " ";
	if (soundMode & FMOD_3D_LINEARROLLOFF)
		std::cout << "atenuacion" << " ";
	if (soundMode & FMOD_LOOP_NORMAL)
		std::cout << "loop" << " ";
#endif


	CheckFMODResult(mResult);
}

bool AudioLeon::setMinMaxDistance(std::string soundName, float minDistance, float maxDistance)
{
	NameToLower(soundName);
	auto soundHandle = GetSound(soundName);
	if (soundHandle == nullptr) return false;
	soundHandle->set3DMinMaxDistance(minDistance, maxDistance);
	return true;
}

bool AudioLeon::createChannelGroup(std::string groupName)
{
	NameToLower(groupName);
	const char* channelGroupName = groupName.c_str();
	if ((int(channelGroupName[0]) > 96) && (int(channelGroupName[0]) < 122)) channelGroupName[0] - 32;
	auto channelGroup = mChannelGroupMaps.find(channelGroupName);
	if (channelGroup == mChannelGroupMaps.end()) {
		FMOD::ChannelGroup* newChannelGroup;
		mSoundSystem->createChannelGroup(channelGroupName, &newChannelGroup);
		std::pair<std::string, FMOD::ChannelGroup*> newGroup(channelGroupName, newChannelGroup);
		mChannelGroupMaps.insert(newGroup);
		mMaster->addGroup(newChannelGroup);
		return true;
	}
	return false;
}

bool AudioLeon::setChannelVolume(std::string groupName, float newVolume)
{
	NameToLower(groupName);
	const char* channelGroup = groupName.c_str();
	FMOD::ChannelGroup* changedGroup = GetGroupChannel(channelGroup);
	if (changedGroup == nullptr) {
		return false;
	}
	else {
		return changeChannelVolume(channelGroup, newVolume);
	}
}

bool AudioLeon::setVolume(std::string soundName, float newVolume)
{
	NameToLower(soundName);
	FMOD::Channel* channel = GetChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->setVolume(newVolume);
		return CheckFMODResult(mResult);
	}
	else {
		return false;
	}
}

float AudioLeon::getVolume(std::string soundName)
{
	NameToLower(soundName);
	FMOD::Channel* channel = GetChannel(soundName);
	float volume;
	if (channel != nullptr) {
		mResult = channel->getVolume(&volume);
		CheckFMODResult(mResult);
		return volume;
	}
}
//void AudioLeon::startRecording()
//{
//	std::cout << "a";
//	FMOD::Sound* audio;
//	mResult = this->mSoundSystem->createSound(0, FMOD_LOOP_NORMAL | FMOD_OPENUSER, 0, &audio);
//	mResult = this->mSoundSystem->recordStart(0, audio, true);
//	std::cout << "a";
//	std::cin.get();
//	mResult = this->mSoundSystem->recordStop(0);
//
//	const int fftSize = 1024;
//	float* spectrumData = new float[fftSize];
//	mResult = channel->getSpectrum(spectrumData, fftSize, 0, FMOD_DSP_FFT_WINDOW_TRIANGLE);
//
//}