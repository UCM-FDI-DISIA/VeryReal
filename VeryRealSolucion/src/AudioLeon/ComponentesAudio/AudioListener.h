#pragma once
#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include <Component.h>
//#include "EntityComponent/FactoryComponent.h"
#include <Vector3.h>

namespace FMOD {
	class Sound;
}


	class SoundManager;

	////Creates and destroys AudioListener components
	//class FactoryAudioListener : public FactoryComponent {
	//public:
	//	Component* create(Parameters& params) override;
	//	void destroy(Component* component) override;
	//};


	/**
	An Entity with this component will output the audio it listens
	where it is located.
	*/
	class AudioListener : public VeryReal::Component
	{
	public:
		AudioListener();
		~AudioListener();

		virtual void Start();

		/**
		* Update the position of the audio listener based on the position of the entity it is attached to.
		*/
		virtual void Update(const double& dt);

		/**
		Updates the position of a sound listener relative to a certain sound.
		@param index : the index that refers to a certain listener.
		@param listenerPos : the position of the listener.
		@param listenerFW : the forward vector of the listener.
		@param listenerUP : the up vector of the listener.
		@param listenerVel : the velocity of the listener.
		*/
		void updateListenersPosition(int index, VeryReal::Vector3 listenerPos,
			VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel = { 0,0,0 });

	private:
		VeryReal::Vector3 position;
		VeryReal::Vector3 lastPosition = { 0,0,0 };
		int mListenerIndex;
	};


#endif // !EC_AUDIO_LISTENER