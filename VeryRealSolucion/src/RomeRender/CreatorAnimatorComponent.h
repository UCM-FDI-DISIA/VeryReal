#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_API CreatorAnimatorComponent : public CreatorComponent
	{
	public:
		CreatorAnimatorComponent() {}
		virtual ~CreatorAnimatorComponent() {}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
};

