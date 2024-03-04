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
	checkFMODResult(mResult);

	mResult = mSoundSystem->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);    // Initialize FMOD.
	checkFMODResult(mResult);
	mResult = mSoundSystem->set3DSettings(0.0f, DISTANCE_FACTOR, ROLLOFF_SCALE);
	checkFMODResult(mResult);

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

bool AudioLeon::checkFMODResult(FMOD_RESULT FMODResult)
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

FMOD::Sound* AudioLeon::getSound(std::string soundName)
{
	nameToLower(soundName);
	auto returnedSound = mSoundsMap.find(soundName);
	if (returnedSound == mSoundsMap.end()) return nullptr;
	return returnedSound->second;
}

FMOD::Channel* AudioLeon::getChannel(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle != nullptr) {
		auto returnedChannel = mLastPlayedMap.find(soundHandle);
		if (returnedChannel == mLastPlayedMap.end()) return nullptr;
		return mChannelsVector[returnedChannel->second];
	}
	else {
		return nullptr;
	}
}

FMOD::ChannelGroup* AudioLeon::getGroupChannel(std::string channelGroupName)
{
	nameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return nullptr;
	return returnedGroup->second;
}

bool AudioLeon::changeChannelVolume(std::string channelGroupName, float volume)
{
	nameToLower(channelGroupName);
	auto returnedGroup = mChannelGroupMaps.find(channelGroupName);
	if (returnedGroup == mChannelGroupMaps.end()) return false;
	mResult = returnedGroup->second->setVolume(volume);
	return checkFMODResult(mResult);
}

void AudioLeon::nameToLower(std::string& name)
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
		checkFMODResult(mResult);
	}
	mSoundsMap.clear();

	mResult = mSoundSystem->close();
	checkFMODResult(mResult);

	mResult = mSoundSystem->release();
	checkFMODResult(mResult);
}

void AudioLeon::systemRefresh(const double& dt)
{
	mResult = mSoundSystem->update();
	checkFMODResult(mResult);
}

bool AudioLeon::create3DSound(std::string soundPath, std::string soundName, float minDistance, float maxDistance, bool loop)
{
	soundPath = "Assets/Sounds/" + soundPath;
	nameToLower(soundName);
	FMOD::Sound* newSoundHandle;
	auto soundHandle = getSound(soundName);
	if (soundHandle != nullptr) return false;

	if (loop) {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
	}
	else {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
	}

	if (!checkFMODResult(mResult)) return false;

	mResult = newSoundHandle->set3DMinMaxDistance(minDistance, maxDistance);
	if (!checkFMODResult(mResult)) return false;

	if (checkFMODResult(mResult)) {
		std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
		mSoundsMap.insert(newSound);
#ifdef _DEBUG
		std::cout << "Sound created." << "\n";
#endif // DEBUG
		return true;
	}
	else {
		return false;
	}


}

bool AudioLeon::createNormalSound(std::string soundPath, std::string soundName, bool loop)
{
	soundPath = "Assets/Sounds/" + soundPath;
	nameToLower(soundName);
	FMOD::Sound* newSoundHandle;
	auto soundHandle = getSound(soundName);
	if (soundHandle != nullptr) return false;

	if (loop) {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
	}
	else {
		mResult = mSoundSystem->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
	}

	if (checkFMODResult(mResult)) {
		std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
		mSoundsMap.insert(newSound);
#ifdef _DEBUG
		std::cout << "Sound created." << "\n";
#endif // DEBUG
		return true;
	}
	else {
		return false;
	}
}

bool AudioLeon::pauseSound(std::string soundName, bool pause)
{
	nameToLower(soundName);
	bool isPaused;
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->getPaused(&isPaused);
		checkFMODResult(mResult);
		channel->setPaused(pause);
		return true;
	}
	else {
		return false;
	}
}

bool AudioLeon::stopSound(std::string soundName)
{
	nameToLower(soundName);
	bool isPaused;
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->getPaused(&isPaused);
		checkFMODResult(mResult);
		channel->stop();
		return true;
	}
	else {
		return false;
	}
}

bool AudioLeon::stopEverySound()
{
	for (auto i : mChannelsVector) {
		i->stop();
	}
	return true;
}

bool AudioLeon::playSound(std::string soundName, std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	FMOD::ChannelGroup* playedChannelGroup = getGroupChannel(channelGroup);
	if (playedChannelGroup == nullptr) return false;

	FMOD_MODE finalSoundMode;
	soundHandle->getMode(&finalSoundMode);

	FMOD::Channel* reproChannel = getChannel(soundName);
	if (reproChannel == nullptr) {
		for (int i = 0; i < mChannelsVector.size(); i++) {
			bool isPlaying;
			mChannelsVector[i]->isPlaying(&isPlaying);

			if (isPlaying) continue;
			mResult = mSoundSystem->playSound(soundHandle, playedChannelGroup, false, &mChannelsVector[i]);
			checkFMODResult(mResult);

			reproChannel = mChannelsVector[i];

			mChannelsVector[i]->setVolume(channelVolume);

			mLastPlayedMap[soundHandle] = i;

			break;
		}
	}
	else {
		mResult = mSoundSystem->playSound(soundHandle, playedChannelGroup, false, &reproChannel);
		checkFMODResult(mResult);
	}

	if (finalSoundMode & FMOD_3D) {
		FMOD_VECTOR v = channelVel->v3ToFmodV3(), p = channelPos->v3ToFmodV3();
		reproChannel->set3DAttributes(&p, &v);
	}

	return true;
}

bool AudioLeon::deleteSound(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	mLastPlayedMap.erase(soundHandle);

	return checkFMODResult(mResult);
}

void AudioLeon::updateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel)
{
	FMOD_VECTOR pos = listenerPos.v3ToFmodV3(), fw = listenerFW.v3ToFmodV3(), up = listenerUP.v3ToFmodV3(), vel = listenerVel.v3ToFmodV3();
	mSoundSystem->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}

void AudioLeon::removeListener(int index)
{
	mListeners[index] = false;
	updateListenersPosition(index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

bool AudioLeon::setSoundAtributes(std::string soundName, VeryReal::Vector3 position, VeryReal::Vector3 velocity)
{
	nameToLower(soundName);
	FMOD::Channel* channelHandle = getChannel(soundName);
	if (channelHandle == nullptr) return false;
	FMOD_VECTOR p = position.v3ToFmodV3(), v = velocity.v3ToFmodV3();

	channelHandle->set3DAttributes(&p, &v);
	return true;
}

bool AudioLeon::setPitchVelocity(std::string soundName, VeryReal::Vector3 velocity)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	float velMagnitude = velocity.Magnitude();
	float newPitch = 1 + (velMagnitude - 1) / 10;
	if (channel != nullptr) {
		channel->setPitch(newPitch);
		return true;
	}
	else return false;
}

bool AudioLeon::setSpeed(std::string soundName, float newSpeed)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;

	mResult = soundHandle->setMusicSpeed(newSpeed);

	return checkFMODResult(mResult);
}

bool AudioLeon::setMode(std::string soundName, FMOD_MODE newMode)
{
	nameToLower(soundName);
	FMOD::Sound* soundHandle = getSound(soundName);
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


	checkFMODResult(mResult);
}

bool AudioLeon::setMinMaxDistance(std::string soundName, float minDistance, float maxDistance)
{
	nameToLower(soundName);
	auto soundHandle = getSound(soundName);
	if (soundHandle == nullptr) return false;
	soundHandle->set3DMinMaxDistance(minDistance, maxDistance);
	return true;
}

bool AudioLeon::createChannelGroup(std::string groupName)
{
	nameToLower(groupName);
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
	nameToLower(groupName);
	const char* channelGroup = groupName.c_str();
	FMOD::ChannelGroup* changedGroup = getGroupChannel(channelGroup);
	if (changedGroup == nullptr) {
		return false;
	}
	else {
		return changeChannelVolume(channelGroup, newVolume);
	}
}

bool AudioLeon::setVolume(std::string soundName, float newVolume)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	if (channel != nullptr) {
		mResult = channel->setVolume(newVolume);
		return checkFMODResult(mResult);
	}
	else {
		return false;
	}
}

float AudioLeon::getVolume(std::string soundName)
{
	nameToLower(soundName);
	FMOD::Channel* channel = getChannel(soundName);
	float volume;
	if (channel != nullptr) {
		mResult = channel->getVolume(&volume);
		checkFMODResult(mResult);
		return volume;
	}
}