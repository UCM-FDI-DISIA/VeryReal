#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>

#include <Component.h>
//#include "EntityComponent/FactoryComponent.h"

namespace FMOD {
	class Sound;
}
    enum FMOD_RESULT;
	
	class AudioLeon;
	typedef unsigned int FMOD_MODE;
	namespace VeryReal {
		class TransformComponent;
		class Vector3;
	}
	//Creates and destroys AudioSource components
	/*class FactoryAudioSource : public FactoryComponent {
	public:
		Component* create(Parameters& params) override;
		void destroy(Component* component) override;
	};*/


	/**
	Plays an audio file in the scene. AudioListeners within range
	will hear it with the intensity based in their position in the scene.
	*/
	class AudioSource : public VeryReal::Component
	{
	public:

		/*
		Default constructor
		*/
		AudioSource();
		~AudioSource();

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
		Sets the global position of a sound i.
		@param soundName : the especific name of the sound which position will be set.
		@param position : the value of the position of the sound.
		@return A boolean showing wether or not the position was set.
		*/
		bool set3DSoundAtributes(std::string soundName, VeryReal::Vector3 position, VeryReal::Vector3 velocity);

		/**
		It checks for available channels to play the sound and assigns a group channel depending on the user input.
		@param soundName : the especific name of the sound which will be played.
		@param channelGroup : the channel group where the sound will played on.
		@param channelPos : the channel's position used for panning and attenuation.
		@param channelVel : the channel' group where the sound will played on's velocity in 3D space used for doppler.
		@return A boolean showing whether or not a channel group was found to play the sound.
		*/
		bool PlayAudioSource(std::string soundName, std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume);

		/**
		Looks for a sound channel and in case that it exists, stops that channel from playing.
		@param soundName : the especific name of the sound which speed will be paused.

		@return True if the sound is stopped, false if the sound didn't exist.
		*/
		bool StopSound(std::string soundName);

		/**
		Looks for a sound channel and in case that it exists, sets the pause state of that channel to "pause".
		@param soundName : the especific name of the sound which speed will be paused.
		@param pause : the new pause value the channel will get.
		@return True if the sound is paused, false if the sound didn't exist.
		*/
		bool PauseSound(std::string soundName, bool pause);
		
		virtual void Start();

		virtual void Update(const double& dt);

		/**
		* Play the audio.
		*/
		void play();

		/**
		* Stop the audio.
		*/
		void stop();

		/**
		* Pause the audio.
		*/
		void pause();

		/**
		* Resume playing the audio after it has been paused.
		*/
		void resume();

		/**
		* Check if the audio is currently playing.
		* @return True if the audio is playing, false otherwise.
		*/
		bool isPlaying();

		/*
		Changes the volume of the channel a soud is being played, if it exists.
		@param value : the volume value the channel will be changed to.
		@return A boolean representing wether or not the volume was changed.
		*/
		bool setVolume(float value);

		/**
		Sets the speed a certain sound wil be played at.
		@param newSpeed : the new value the sound will be played at.
		@return A boolean showing wether or not the speed was changed.
		*/
		bool setSpeed(float newSpeed);

		/**
		Sets a new minimum and maximum distance a 3D sound can be heard from.
		@param soundName : the especific name of the sound which hearing distance will be changed.
		@param minDistance : the new minimum distance a 3D sound can be heard from.
		@param maxDistance : the new maximun distance a 3D sound can be heard from.
		@return A boolean showing wether or not the new hearing distances was set.
		*/
		bool setMinMaxDistance(float minDistance, float maxDistance);

		/**
		Sets the mode of a certain sound.
		@param soundName : the especific name of the sound which mode will be changed.
		@param newMode: the new flag the sound will be changed to.
		@return A boolean showing wether or not the mode was set.
		*/
		bool setMode(FMOD_MODE newMode);
		
		/**
		* Set the path of the audio
		* @param path The path to the audio file to play.
		*/
		void setSourcePath(std::string path);

		/**
		* Set the name of the audio
		* @param name The name to the audio file to play.
		*/
		void setSourceName(std::string name);

		/**
		* Set the name of the group channel this audio is located in.
		* @param name The name of the group channel.
		*/
		void setGroupChannelName(std::string name);

		/**
		* Set if the audio will play in a loop
		* @param loop True if the sound should be looping, false otherwise
		*/
		void setLoop(bool loop);

		/**
		* Set if the audio will be a 3D audio
		* @param threeD if we need 3d sound
		*/
		void setIsThreeD(bool threeD);

		/**
		* Set if the adio will play at the start
		* @param playOnStart True if the sound should starting played, false otherwise
		*/
		void setPlayOnStart(bool playOnStart);

		/**
		* Get the volume of the audio.
		* @return The current volume value.
		*/
		float getVolume();


	private:
		float mVolume;  // The volume of the audio
		float mSpeed; // The speed of the audio
		float mMinDistance; //Minimum distance a 3D sound can be heard from.
		float mMaxDistance; //Maximun distance a 3D sound can be heard from.

		//FMOD::Sound* mSound; // The FMOD sound object
		int mSoundChannel; // The number of the channel this sound will be played on.
		std::string mSoundGroup; // The name of the channel group this sound will be played on.
		std::string mSoundPath; // The path to the audio file to play
		std::string mSoundName; // The name we give to the audio file to play
		bool mPlaying; // Whether the audio is currently playing or not
		bool mLoop; // Whether the audio should loop or not
		bool mIsThreeD;
		bool mPlayOnStart;


		FMOD_RESULT mResult;
		VeryReal::TransformComponent* mTransform = nullptr;
	};


#endif

