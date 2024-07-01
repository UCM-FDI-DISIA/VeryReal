#pragma once
#include "CreatorComponent.h"
#include "exportRomeRender.h"
#include <string>

namespace VeryReal {
class VERYREAL_ROMERENDER CreatorSmokeEffect : public CreatorComponent {
        public:
    CreatorSmokeEffect() { }
    virtual ~CreatorSmokeEffect() { }
    Component* CreatorSpecificComponent() override;
    std::pair<bool, std::string> SpecificInitComponent(Component* c) override;
    std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;

        private:
    static int smokeEffectCounter;   // Static counter for unique names
};
}
