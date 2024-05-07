#pragma once
#include "CreatorComponent.h"
#include "../exportRomeRender.h"
namespace VeryReal {
    class VERYREAL_ROMERENDER CreatorButtonComponent : public CreatorComponent {
            public:
        CreatorButtonComponent(){};
        virtual ~CreatorButtonComponent(){};
        Component* CreatorSpecificComponent() override;
        std::pair<bool,std::string> SpecificInitComponent(Component* c) override;
        std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
    }; 
}