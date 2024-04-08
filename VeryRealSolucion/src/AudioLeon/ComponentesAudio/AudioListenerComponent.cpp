#pragma once
#include "AudioListenerComponent.h"
#include "..\AudioLeon.h"
#include <TransformComponent.h>
#include <RigidBodyComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>
#include <Vector3.h>
#include <fmod_studio.hpp>

using namespace VeryReal;
Component* CreatorAudioListener::CreatorSpecificComponent() {
	AudioListenerComponent* a = new AudioListenerComponent();
	a->InitComponent();
	return a;
}

AudioListenerComponent::AudioListenerComponent() : listener_index(-1) {}

AudioListenerComponent::~AudioListenerComponent()
{
	AL().RemoveListener(listener_index);
	UpdateListenersPosition(listener_index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

void AudioListenerComponent::InitComponent()
{
	// Get the next available index for a listener in the sound manager
	listener_index = AL().GetNextUsefulListenerIndex();

#ifdef _DEBUG
	if (listener_index == -1)
		std::cout << "ERROR: Listeners vector is full\n";
#endif // _DEBUG
}

void AudioListenerComponent::Update(const double& dt)
{
	if (!this->GetEntity()->GetComponent<TransformComponent>("TransformComponent")) {
		ErrorInf().showErrorMessageBox("AudioListenerComponent error", "An entity doesn't have transform component", EI_ERROR);
	/*	sceneManager().quit();*/
		return;
	}


	Vector3 position = this->GetEntity()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	//Vector3 velocity = this->GetEntity()->GetComponent<VeryReal::RigidBodyComponent>("rigidbody")->GetVelocity();
	//VeryReal::Vector3 up = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("TransformComponent")->up();
	//VeryReal::Vector3 forward = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("TransformComponent")->forward();

	//VeryReal::Vector3 v = { (position.x - last_position.x) * float(dt),(position.y - last_position.y) * float(dt),(position.z - last_position.z) * float(dt) };

	//last_position = position;

	//// Update the position of the audio listener in the sound manager
	//UpdateListenersPosition(listener_index, position, forward, up, v);
}

void AudioListenerComponent::UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel)
{
	FMOD_VECTOR pos = AL().V3ToFmodV3(listenerPos), fw = AL().V3ToFmodV3(listenerFW), up = AL().V3ToFmodV3(listenerUP), vel = AL().V3ToFmodV3(listenerVel);
	AL().GetSoundSystem()->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}
