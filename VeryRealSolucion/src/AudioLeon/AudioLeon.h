
#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER

#include <Manager.h>
#include <Vector3.h>
#include <string>
#include <unordered_map>
#include <fmod_studio.hpp>
#include <fmod.hpp>

namespace FMOD {
	class Sound;
	class ChannelGroup;
	class Channel;
	class System;
}

enum FMOD_RESULT;
typedef unsigned int FMOD_MODE;
typedef int CHANNEL_NUMBER;

	//Maximum number of channels allowed to exist in this particular system setting.
	const int MAX_CHANNELS = 100;
	//Scaling factor for how much the pitch varies due to doppler shifting in 3D sound.
	const float DOPPLER_SCALE = 1.0f;
	//Relative distance factor, compared to 1.0 meters. How many units per meter my engine have.
	const float DISTANCE_FACTOR = 1.0f;
	//Global attenuation rolloff factor. 
	const float ROLLOFF_SCALE = 1.0f;
	//Base pitch of a sound. The "normal" pitch of a sound when it is not moving.
	const float BASE_PITCH = 1.0f;

	/* SoundManager provides FMOD wrappers to manage audio creation and modulation,
	audio channel and audio channel groups.
	You can access the InputManager calling sm(). */

	class AudioLeon : public VeryReal::Manager<AudioLeon> {
		friend Singleton<AudioLeon>;
		AudioLeon();
		//Inicializacion de los recursos necesarios para recoger input del microfono
		void InitAudioRecording();
		//Stores audio handles linked to their name.
		std::unordered_map<std::string, FMOD::Sound*> mSoundsMap;
		//Stores audio handles linked to the last channel they where played in.
		std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> mLastPlayedMap;
		//Stores channel group names linked to their handle.
		std::unordered_map<std::string, FMOD::ChannelGroup*> mChannelGroupMaps;
		//Stores every audio channel.
		std::vector<FMOD::Channel*> mChannelsVector;
		//Basic channel groups provided by the SoundManager.
		FMOD::ChannelGroup* mEffects, * mMusic, * mMaster;
		std::vector<bool> mListeners;
		//The sound system over which every bit of audio gets created.
		FMOD::System* mSoundSystem = nullptr;
		//Sonido recibido por el microfono
		FMOD::Sound* micSound = NULL;

		FMOD_RESULT mResult;

		
		//Se queda

		//Se queda
		
		//Se queda

		
		/**
		Changes the volume of a channel.
		@param groupName : the name of the group channel which volume will be changed.
		@param volume : the new value the volume will have now.
		@returns False if there is no such channel os ir an FMOD error, true if the volume is changed.
		*/
		bool changeChannelVolume(std::string channelGroupName, float volume);

	public:

		/**
		Destructor for the SoundManager class
		*/
		~AudioLeon();
		/**
		Updates the sound system every step of the game loop.
		*/
		void systemRefresh(const double& dt);
		/**
		Creates a 3D sound.
		@param soundPath : relative path to the sound that will be loaded in the sound handle.
		@param soundName : the especific name of the sound which mode will be changed.
		@param minDistance : minimum audible distance for a 3D sound.
		@param maxDistance : maximum audible distance for a 3D sound.
		@param loop : if the sound will loop or not.
		@return A boolean representing whether or not a the sound was created.
		*/

		/*
		Returns the conversion of a Vector3 to an FMOD_VECTOR
		*/
		FMOD_VECTOR V3ToFmodV3(VeryReal::Vector3 conversion) const;

		/**
		Makes sure the sound name is in all lower case with no spaces.
		@param name : the name to change.
		*/
		void NameToLower(std::string& name);

		/**
		Chech if the result of any FMOD-related action is without any error.
		@param FMODResult: a flag that shows if there has been an error
		@returns A boolean representing whether there was an error or not.
		*/
		bool CheckFMODResult(FMOD_RESULT FMODResult);

		/**
		Gets a sound handle via the name of the sound.
		@param soundName : the name of the sound linked to a channek needed to look for a certain channel.
		@returns Nullptr if there is no sound with that given name.
		*/
		FMOD::Sound* GetSound(std::string soundName);

		/**
		Returns the reference to the FMOD sound system.
		*/
		FMOD::System* GetSoundSystem();

		/**
		Gets a group channel handle via the name it was created with.
		@param groupName : the name of the group channel.
		@returns Nullptr if there is no such group channel or the correspondent group channel.
		*/
		FMOD::ChannelGroup* GetGroupChannel(std::string channelGroupName);

		std::vector<FMOD::Channel*> GetChannelsVector();

		std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> GetLastPlayedMap();

		/*
		Adds a new sound to the sounds map.
		*/
		void AddNewSound(std::pair<std::string, FMOD::Sound*> newSound);

		/**
		Gets a channel handle via the sound that was last played on it.
		@param soundName : the name of the sound linked to a channel needed to look for a certain channel.
		@returns Nullptr if there is no such channel or the correspondent channel.
		*/
		FMOD::Channel* GetChannel(std::string soundName);

		/**
		Sets the mode of a certain sound.
		@param soundName : the especific name of the sound which mode will be changed.
		@param newMode: the new flag the sound will be changed to.
		@return A boolean showing wether or not the mode was set.
		*/
		bool setMode(std::string soundName, FMOD_MODE newMode);
		/**
		Sets a new minimum and maximum distance a 3D sound can be heard from.
		@param soundName : the especific name of the sound which hearing distance will be changed.
		@param minDistance : the new minimum distance a 3D sound can be heard from.
		@param maxDistance : the new maximun distance a 3D sound can be heard from.
		@return A boolean showing wether or not the new hearing distances was set.
		*/
		bool setMinMaxDistance(std::string soundName, float minDistance, float maxDistance);
		/**
		Create a channel group if a channel with the same name doesn't already exists.
		@param newChannelGroup : the name for the new channel group.
		@return A boolean representing whether or not a new channel was indeed created.
		*/
		bool createChannelGroup(std::string groupName);
		/**
		Changes the volume of a certain group channel if it exists.
		@param groupName : the name of the channel group.
		@param newVolume : the volume value the group channel will be changed to.
		@return A boolean representing whether or not a the volume was changed.
		*/
		bool setChannelVolume(std::string groupName, float newVolume);
		/**
		Changes the volume of a certain channel if it exists.
		@param soundName : the especific name of the sound which volume will be changed.
		@param newVolume : the volume value the channel will be changed to.
		@return A boolean representing wether or not the volume was changed.
		*/
		bool setVolume(std::string soundName, float newVolume);

		/**
		Checks the volume of a certain channel if it exists.
		@param soundName : the especific name of the sound which speed will be changed.
		@return The specific float of the volume.
		*/
		float getVolume(std::string soundName);

		/// Obtiene la intensidad del sonido recibido por el microfono
		/// @return Intensidad del sonido (en un rango de 0 a 1)
		float inputSoundIntensity();

		/**
		Stops every channel playing at the moment.

		@return True if every channel was stopped.
		*/
		bool stopEverySound();

		/**
		Releases the dynamic memory created on runtime when creating new sounds.
		@param soundName : the especific name of the sound which speed will be changed.
		@return A boolean showing wether or not the sound was eliminated.
		*/
		bool deleteSound(std::string soundName);
		/**
		Removes the listener from its vector and resets its values.
		@param index : the index that refers to a certain listener.
		*/
		void removeListener(int index);
		//Se queda;

		/**
		Gets the useful listener which will be able to listen to a new sound.
		@return A integer showing whether or not a useful listener was found.
		*/
		inline int getNextUsefulListenerIndex() {
			for (int i = 0; i < mListeners.size(); i++) {
				if (!mListeners[i])
					mListeners[i] = true;
				return i;
			}
			return -1;
		}
		/*void startRecording();*/
	};

	/**
	This macro defines a compact way for using the singleton SoundManager, instead of
	writing SoundManager::instance()->method() we write soundManager().method()
	*/
	inline AudioLeon& AL() {
		return *AudioLeon::Instance();
	}

#endif // !_FMOD_SOUND_MANAGER