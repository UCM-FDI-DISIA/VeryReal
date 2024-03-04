
#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER

#include "MotorEngine/MotorEngineAPI.h"
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
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

namespace me {
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

	/**
	SoundManager provides FMOD wrappers to manage audio creation and modulation,
	audio channel and audio channel groups.
	You can access the InputManager calling sm().
	*/
	class __MOTORENGINE_API SoundManager : public Singleton<SoundManager>
	{
		friend Singleton<SoundManager>;
		SoundManager();
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

		/**
		Chech if the result of any FMOD-related action is without any error.
		@param FMODResult: a flag that shows if there has been an error
		@returns A boolean representing whether there was an error or not.
		*/
		bool checkFMODResult(FMOD_RESULT FMODResult);
		//Se queda

		/**
		Gets a sound handle via the name of the sound.
		@param soundName : the name of the sound linked to a channek needed to look for a certain channel.
		@returns Nullptr if there is no sound with that given name.
		*/
		FMOD::Sound* getSound(std::string soundName);
		//Se queda

		/**
		Gets a channel handle via the sound that was last played on it.
		@param soundName : the name of the sound linked to a channel needed to look for a certain channel.
		@returns Nullptr if there is no such channel or the correspondent channel.
		*/
		FMOD::Channel* getChannel(std::string soundName);
		//Se queda

		/**
		Gets a group channel handle via the name it was created with.
		@param groupName : the name of the group channel.
		@returns Nullptr if there is no such group channel or the correspondent group channel.
		*/
		FMOD::ChannelGroup* getGroupChannel(std::string channelGroupName);

		/**
		Changes the volume of a channel.
		@param groupName : the name of the group channel which volume will be changed.
		@param volume : the new value the volume will have now.
		@returns False if there is no such channel os ir an FMOD error, true if the volume is changed.
		*/
		bool changeChannelVolume(std::string channelGroupName, float volume);

		/**
		Makes sure the sound name is in all lower case with no spaces.
		@param name : the name to change.
		*/
		void nameToLower(std::string& name);

		FMOD_RESULT mResult;

	public:

		/**
		Destructor for the SoundManager class
		*/
		~SoundManager();
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
		bool create3DSound(std::string soundPath, std::string soundName, float minDistance, float maxDistance, bool loop);
		/**
		Creates a normal sound.
		@param soundPath : relative path to the sound that will be loaded in the sound handle.
		@param soundName : the especific name of the sound which mode will be changed.
		@param loop : if the sound will loop or not.
		@return A boolean representing whether or not a the sound was created.
		*/
		bool createNormalSound(std::string soundPath, std::string soundName, bool loop);
		/**
		Sets the speed a certain sound wil be played at.
		@param soundName : the especific name of the sound which speed will be changed.
		@param newSpeed : the new value the sound will be played at.
		@return A boolean showing wether or not the speed was changed.
		*/
		bool setSpeed(std::string soundName, float newSpeed);
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

		/**
		Looks for a sound channel and in case that it exists, sets the pause state of that channel to "pause".
		@param soundName : the especific name of the sound which speed will be paused.
		@param pause : the new pause value the channel will get.
		@return True if the sound is paused, false if the sound didn't exist.
		*/
		bool pauseSound(std::string soundName, bool pause);

		/**
		Looks for a sound channel and in case that it exists, stops that channel from playing.
		@param soundName : the especific name of the sound which speed will be paused.

		@return True if the sound is stopped, false if the sound didn't exist.
		*/
		bool stopSound(std::string soundName);

		/**
		Stops every channel playing at the moment.

		@return True if every channel was stopped.
		*/
		bool stopEverySound();
		/**
		It checks for available channels to play the sound and assigns a group channel depending on the user input.
		@param soundName : the especific name of the sound which will be played.
		@param channelGroup : the channel group where the sound will played on.
		@param channelPos : the channel's position used for panning and attenuation.
		@param channelVel : the channel' group where the sound will played on's velocity in 3D space used for doppler.
		@return A boolean showing whether or not a channel group was found to play the sound.
		*/
		bool playSound(std::string soundName, std::string channelGroup, Vector3* channelPos, Vector3* channelVel, float channelVolume);
		/**
		Releases the dynamic memory created on runtime when creating new sounds.
		@param soundName : the especific name of the sound which speed will be changed.
		@return A boolean showing wether or not the sound was eliminated.
		*/
		bool deleteSound(std::string soundName);
		/**
		Updates the position of a sound listener relative to a certain sound.
		@param index : the index that refers to a certain listener.
		@param listenerPos : the position of the listener.
		@param listenerFW : the forward vector of the listener.
		@param listenerUP : the up vector of the listener.
		@param listenerVel : the velocity of the listener.
		*/
		void updateListenersPosition(int index, Vector3 listenerPos,
			Vector3 listenerFW, Vector3 listenerUP, Vector3 listenerVel = { 0,0,0 });
		/**
		Removes the listener from its vector and resets its values.
		@param index : the index that refers to a certain listener.
		*/
		void removeListener(int index);

		/**
		Sets the global position of a sound i.
		@param soundName : the especific name of the sound which position will be set.
		@param position : the value of the position of the sound.
		@return A boolean showing wether or not the position was set.
		*/
		bool setSoundAtributes(std::string soundName, Vector3 position, Vector3 velocity);

		/**
		Sets the pitch of a certain sound depending on the velocity of the object it is attached to.
		@param soundName : the especific name of the sound which pitch will be set.
		@param velocity : the value of the velocity of the object.
		@return A boolean showing wether or not the new pitch was set.
		*/
		bool setPitchVelocity(std::string soundName, Vector3 velocity);

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


	};

	/**
	This macro defines a compact way for using the singleton SoundManager, instead of
	writing SoundManager::instance()->method() we write soundManager().method()
	*/
	inline SoundManager& soundManager() {
		return *SoundManager::Instance();
	}
}

#endif // !_FMOD_SOUND_MANAGER

