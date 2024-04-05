#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorLightComponent : public CreatorComponent
    {
    public:
        CreatorLightComponent() {}
        virtual ~CreatorLightComponent() {}
        Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
    };

};

