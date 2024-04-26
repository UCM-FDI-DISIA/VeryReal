#include "CreatorAudioListenerComponent.h"
#include "AudioListenerComponent.h"
using namespace VeryReal;
Component* CreatorAudioListenerComponent::CreatorSpecificComponent() {
	return new AudioListenerComponent();
}

void CreatorAudioListenerComponent::SpecificInitComponent(Component* c) {
	static_cast<AudioListenerComponent*>(c)->InitComponent();
}