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
        std::pair<bool, std::string> SpecificInitComponent(Component* c) override;
        std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
};

