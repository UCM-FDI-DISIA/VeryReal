#pragma once
#include "CreatorComponent.h"
#include "../exportRomeRender.h"
namespace VeryReal {
class VERYREAL_ROMERENDER CreatorButtonComponent : public CreatorComponent {
        public:
    CreatorButtonComponent(){};
    virtual ~CreatorButtonComponent(){};
    Component* CreatorSpecificComponent() override;
    void SpecificInitComponent(Component* c) override;
}; 
}