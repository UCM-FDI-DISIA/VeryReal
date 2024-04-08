#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
class VERYREAL_API CreatorAudioListenerComponent : public CreatorComponent {
        public:
    CreatorAudioListenerComponent() { }
    virtual ~CreatorAudioListenerComponent() { }
    Component* CreatorSpecificComponent() override;
    void SpecificInitComponent(Component* c) override;
};
}


