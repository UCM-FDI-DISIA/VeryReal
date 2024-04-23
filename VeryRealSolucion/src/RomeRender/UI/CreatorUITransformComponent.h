#pragma once
#include "CreatorComponent.h"
#include "../exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorUITransformComponent : public CreatorComponent
	{
	public:
    CreatorUITransformComponent() { }
    virtual ~CreatorUITransformComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

