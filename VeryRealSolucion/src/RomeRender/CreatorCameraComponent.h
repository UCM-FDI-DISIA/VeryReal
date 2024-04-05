#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorCameraComponent : public CreatorComponent
    {
    public:
        CreatorCameraComponent() {};
        virtual ~CreatorCameraComponent() {};
        Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
    };
};

