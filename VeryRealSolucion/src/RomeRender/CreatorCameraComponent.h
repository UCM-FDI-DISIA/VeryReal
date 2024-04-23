#pragma once
#include "CreatorComponent.h"
#include "exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorCameraComponent : public CreatorComponent
    {
    public:
        CreatorCameraComponent() {};
        virtual ~CreatorCameraComponent() {};
        Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
    };
};

