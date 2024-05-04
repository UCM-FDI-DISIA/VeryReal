#pragma once
#include "CreatorComponent.h"
#include "../exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorUISpriteRenderComponent : public CreatorComponent
	{
	public:
    CreatorUISpriteRenderComponent() { }
    virtual ~CreatorUISpriteRenderComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
        void SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
};

