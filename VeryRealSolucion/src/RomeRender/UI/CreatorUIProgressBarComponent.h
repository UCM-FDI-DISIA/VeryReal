#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorUIProgressBarComponent : public CreatorComponent
	{
	public:
        CreatorUIProgressBarComponent() { }
        virtual ~CreatorUIProgressBarComponent() { }
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};
