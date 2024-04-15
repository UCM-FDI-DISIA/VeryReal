#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorUITextComponent : public CreatorComponent
	{
	public:
		CreatorUITextComponent() { }
		virtual ~CreatorUITextComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;

	};
};

