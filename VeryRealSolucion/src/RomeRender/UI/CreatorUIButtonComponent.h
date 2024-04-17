#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
class VERYREAL_API CreatorButtonComponent : public CreatorComponent {
        public:
    CreatorButtonComponent(){};
    virtual ~CreatorButtonComponent(){};
    Component* CreatorSpecificComponent() override;
    void SpecificInitComponent(Component* c) override;
}; 
}