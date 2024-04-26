#pragma once
#include "CreatorComponent.h"
#include "../exportAudioLeon.h"
namespace VeryReal {
class  VERYREAL_AUDIOLEON  CreatorAudioListenerComponent : public CreatorComponent {
    public:
    CreatorAudioListenerComponent() { }
    virtual ~CreatorAudioListenerComponent() { }
    Component* CreatorSpecificComponent() override;
    void SpecificInitComponent(Component* c) override;
};
}