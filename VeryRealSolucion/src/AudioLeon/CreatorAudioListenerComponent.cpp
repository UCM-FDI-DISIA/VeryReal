#include "CreatorAudioListenerComponent.h"
#include "AudioListenerComponent.h"
using namespace VeryReal;
Component* CreatorAudioListenerComponent::CreatorSpecificComponent() {
	return new AudioListenerComponent();
}

std::pair<bool, std::string> CreatorAudioListenerComponent::SpecificInitComponent(Component* c) {
	return static_cast<AudioListenerComponent*>(c)->InitComponent();
}

std::pair<bool, std::string> CreatorAudioListenerComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    AudioListenerComponent* audio = static_cast<AudioListenerComponent*>(c);
    AudioListenerComponent* copia = static_cast<AudioListenerComponent*>(other);
    return audio->InitComponent();
}