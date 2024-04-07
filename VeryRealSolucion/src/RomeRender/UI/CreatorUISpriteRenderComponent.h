#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorUISpriteRenderComponent : public CreatorComponent
	{
	public:
    CreatorUISpriteRenderComponent() { }
    virtual ~CreatorUISpriteRenderComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

