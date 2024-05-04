#pragma once
#include "CreatorComponent.h"
#include "../exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorUITextComponent : public CreatorComponent
	{
	public:
		CreatorUITextComponent() { }
		virtual ~CreatorUITextComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
        void SpecificInitComponentByCopy(Component* c, Component* other) override;

	};
};

