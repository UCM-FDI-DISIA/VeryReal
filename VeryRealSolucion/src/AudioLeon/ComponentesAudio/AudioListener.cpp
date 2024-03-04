#include "AudioListener.h"
#include <AudioLeon.h>
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>


//Component* FactoryAudioListener::create(Parameters& params)
//{
//	AudioListener* audioListener = new AudioListener();
//
//	return audioListener;
//}
//
//void FactoryAudioListener::destroy(Component* component)
//{
//	delete component;
//}

AudioListener::AudioListener()
{
}

AudioListener::~AudioListener()
{
	AL().removeListener(mListenerIndex);
}

void AudioListener::Start()
{
	// Get the next available index for a listener in the sound manager
	mListenerIndex = AL().getNextUsefulListenerIndex();

#ifdef _DEBUG
	if (mListenerIndex == -1)
		std::cout << "ERROR: Listeners vector is full\n";
#endif // _DEBUG
}

void AudioListener::Update(const double& dt)
{
	if (!this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")) {
		ErrorInf().showErrorMessageBox("AudioListener error", "An entity doesn't have transform component", EI_ERROR);
	/*	sceneManager().quit();*/
		return;
	}


	VeryReal::Vector3 position = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetPosition();
	VeryReal::Vector3 velocity = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetVelocity();
	//VeryReal::Vector3 up = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->up();
	//VeryReal::Vector3 forward = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->forward();

	//VeryReal::Vector3 v = { (position.x - lastPosition.x) * float(dt),(position.y - lastPosition.y) * float(dt),(position.z - lastPosition.z) * float(dt) };

	//lastPosition = position;

	//// Update the position of the audio listener in the sound manager
	//soundManager().updateListenersPosition(mListenerIndex, position, forward, up, v);
}
