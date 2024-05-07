#pragma once
#include "AudioListenerComponent.h"
#include "AudioManager.h"
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>

#include <fmod_studio.hpp>

using namespace VeryReal;

AudioListenerComponent::AudioListenerComponent() : listener_index(-1) {}

AudioListenerComponent::~AudioListenerComponent()
{
	AM().RemoveListener(listener_index);
	UpdateListenersPosition(listener_index, { 999999,999999,999999 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

std::pair<bool, std::string> AudioListenerComponent::InitComponent() {
	// Get the next available index for a listener in the sound manager
	listener_index = AM().GetNextUsefulListenerIndex();
    transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>();
    if (!transform) 
	{
        return {false, "An entity doesn't have a transform component"};
	}
	last_position = transform->GetPosition();

#ifdef _DEBUG
	if (listener_index == -1) return {false, "ERROR: Listeners vector is full"};
#endif // _DEBUG
    Vector3 position = transform->GetPosition();
    Vector3 velocity = transform->GetVelocity();
    VeryReal::Vector3 up = transform->up();
    VeryReal::Vector3 forward = transform->getFacingDirection();

	UpdateListenersPosition(listener_index, position, forward, up, velocity);
    return {true, "AudioListener initialized"};
}

void AudioListenerComponent::Update(const double& dt)
{
	Vector3 position = transform->GetPosition();
    Vector3 velocity = transform->GetVelocity();
    VeryReal::Vector3 up = transform->up();
    VeryReal::Vector3 forward = transform->getFacingDirection();

	VeryReal::Vector3 v = {(position.GetX() - last_position.GetX()) * float(dt), (position.GetY() - last_position.GetY()) * float(dt),
                           (position.GetZ() - last_position.GetZ()) * float(dt)};

	last_position = position;

	// Update the position of the audio listener in the sound manager
	UpdateListenersPosition(listener_index, position, forward, up, v);
}

void AudioListenerComponent::UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP, VeryReal::Vector3 listenerVel)
{
	FMOD_VECTOR pos = AM().V3ToFmodV3(listenerPos), fw = AM().V3ToFmodV3(listenerFW), up = AM().V3ToFmodV3(listenerUP), vel = AM().V3ToFmodV3(listenerVel);
	AM().GetSoundSystem()->set3DListenerAttributes(index, &pos, &vel, &fw, &up);
}
