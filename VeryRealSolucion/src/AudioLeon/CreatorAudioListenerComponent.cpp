#include "CreatorAudioListenerComponent.h"
#include "AudioListenerComponent.h"
using namespace VeryReal;
Component* CreatorAudioListenerComponent::CreatorSpecificComponent() {
	return new AudioListenerComponent();
}

void CreatorAudioListenerComponent::SpecificInitComponent(Component* c) {
	static_cast<AudioListenerComponent*>(c)->InitComponent();
}

void CreatorAudioListenerComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    AudioListenerComponent* audio = static_cast<AudioListenerComponent*>(c);
    AudioListenerComponent* copia = static_cast<AudioListenerComponent*>(other);
    audio->InitComponent();
}