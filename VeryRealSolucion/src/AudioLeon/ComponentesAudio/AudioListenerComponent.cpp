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
    transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>();
    rigid_body = this->GetEntity()->GetComponent<VeryReal::RigidBodyComponent>();

	if (!transform) {
            ErrorInf().showErrorMessageBox("AudioListenerComponent error", "An entity doesn't have transform component", EI_ERROR);
            /*	sceneManager().quit();*/
            return;
    }
    if (!rigid_body) {
        ErrorInf().showErrorMessageBox("AudioSourceComponent error", "An entity doesn't have rigid body component", EI_ERROR);
        //sceneManager().quit();
        return;
    }

	last_position = transform->GetPosition();

#ifdef _DEBUG
	if (listener_index == -1)
		std::cout << "ERROR: Listeners vector is full\n";
#endif // _DEBUG

	FMOD_VECTOR pos = {0.0f, 0.0f, 0.0f};
    FMOD_VECTOR vel = {0.0f, 0.0f, 0.0f};
    FMOD_VECTOR forward = {0.0f, 0.0f, 1.0f};
    FMOD_VECTOR up = {0.0f, 1.0f, 0.0f};

    AL().GetSoundSystem()->set3DListenerAttributes(listener_index, &pos, &vel, &forward, &up);
}

void AudioListenerComponent::Update(const double& dt)
{
	//Vector3 position = transform->GetPosition();
 //   Vector3 velocity = rigid_body->GetVelocity();
 //   VeryReal::Vector3 up = transform->up();
 //   VeryReal::Vector3 forward = transform->forward();

	//VeryReal::Vector3 v = {(position.GetX() - last_position.GetX()) * float(dt), (position.GetY() - last_position.GetY()) * float(dt),
 //                          (position.GetZ() - last_position.GetZ()) * float(dt)};

	//last_position = position;

	//// Update the position of the audio listener in the sound manager
	//UpdateListenersPosition(listener_index, position, forward, up, v);
}

void AudioListenerComponent::UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel)
{
	FMOD_VECTOR pos = AL().V3ToFmodV3(listenerPos), fw = AL().V3ToFmodV3(listenerFW), up = AL().V3ToFmodV3(listenerUP), vel = AL().V3ToFmodV3(listenerVel);
	AL().GetSoundSystem()->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}
