#pragma once
#include "CreatorComponent.h"
#include "exportRomeRender.h"
namespace VeryReal
{
class VERYREAL_ROMERENDER CreatorAnimatorComponent : public CreatorComponent
	{
	public:
		CreatorAnimatorComponent() {}
		virtual ~CreatorAnimatorComponent() {}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

