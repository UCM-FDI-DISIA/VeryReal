#pragma once
#include "CreatorComponent.h"
#include "exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorLightComponent : public CreatorComponent
    {
    public:
        CreatorLightComponent() {}
        virtual ~CreatorLightComponent() {}
        Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
        void SpecificInitComponentByCopy(Component* c, Component* other) override;
    };

};

