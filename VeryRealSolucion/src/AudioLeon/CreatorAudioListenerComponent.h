#pragma once
#include "CreatorComponent.h"
#include "exportAudioLeon.h"
namespace VeryReal {
class  VERYREAL_AUDIOLEON  CreatorAudioListenerComponent : public CreatorComponent {
    public:
    CreatorAudioListenerComponent() { }
    virtual ~CreatorAudioListenerComponent() { }
    Component* CreatorSpecificComponent() override;
    std::pair<bool,std::string> SpecificInitComponent(Component* c) override;
    std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
};
}