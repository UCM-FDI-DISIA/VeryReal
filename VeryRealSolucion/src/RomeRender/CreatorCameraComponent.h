#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
    class CreatorCameraComponent :public CreatorComponent
    {
    public:
        CreatorCameraComponent() {};
        virtual ~CreatorCameraComponent() {};
        Component* CreatorSpecificComponent() override;
    };
};

