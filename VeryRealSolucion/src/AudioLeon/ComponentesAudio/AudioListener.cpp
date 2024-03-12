#include "AudioListener.h"
#include <AudioLeon.h>
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>

using namespace VeryReal;
Component* CreatorAudioListener::CreatorSpecificComponent() {
	Audio_Listener* a = new Audio_Listener();
	a->InitComponent();
	return a;
}

Audio_Listener::Audio_Listener(){}

Audio_Listener::~Audio_Listener()
{
	AL().RemoveListener(listener_index);
	UpdateListenersPosition(listener_index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

void Audio_Listener::InitComponent()
{
	// Get the next available index for a listener in the sound manager
	listener_index = AL().GetNextUsefulListenerIndex();

#ifdef _DEBUG
	if (listener_index == -1)
		std::cout << "ERROR: Listeners vector is full\n";
#endif // _DEBUG
}

void Audio_Listener::Update(const double& dt)
{
	if (!this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")) {
		ErrorInf().showErrorMessageBox("Audio_Listener error", "An entity doesn't have transform component", EI_ERROR);
	/*	sceneManager().quit();*/
		return;
	}


	VeryReal::Vector3 position = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetPosition();
	VeryReal::Vector3 velocity = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetVelocity();
	//VeryReal::Vector3 up = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->up();
	//VeryReal::Vector3 forward = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->forward();

	//VeryReal::Vector3 v = { (position.x - last_position.x) * float(dt),(position.y - last_position.y) * float(dt),(position.z - last_position.z) * float(dt) };

	//last_position = position;

	//// Update the position of the audio listener in the sound manager
	//UpdateListenersPosition(listener_index, position, forward, up, v);
}

void Audio_Listener::UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel)
{
	FMOD_VECTOR pos = AL().V3ToFmodV3(listenerPos), fw = AL().V3ToFmodV3(listenerFW), up = AL().V3ToFmodV3(listenerUP), vel = AL().V3ToFmodV3(listenerVel);
	AL().GetSoundSystem()->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}
