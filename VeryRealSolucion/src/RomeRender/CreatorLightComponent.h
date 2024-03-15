#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
    class CreatorLightComponent :public CreatorComponent
    {
    public:
        CreatorLightComponent() {}
        virtual ~CreatorLightComponent() {}
        Component* CreatorSpecificComponent() override;
    };

};

