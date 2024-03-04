#pragma once
#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include <Component.h>
//#include "EntityComponent/FactoryComponent.h"
#include <Vector3.h>

namespace FMOD {
	class Sound;
	class FMOD_VECTOR;
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

	private:
		VeryReal::Vector3 position;
		VeryReal::Vector3 lastPosition = { 0,0,0 };
		int mListenerIndex;
	};


#endif // !EC_AUDIO_LISTENER