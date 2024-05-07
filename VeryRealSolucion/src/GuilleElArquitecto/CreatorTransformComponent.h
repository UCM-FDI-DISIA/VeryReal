#pragma once
#include "CreatorComponent.h"
namespace VeryReal
{
class VERYREAL_GUILLEELARQUITECTO CreatorTransformComponent : public CreatorComponent {
	private:
	public:
		CreatorTransformComponent() {}
		virtual ~CreatorTransformComponent() {}
		Component* CreatorSpecificComponent() override;
        std::pair<bool, std::string> SpecificInitComponent(Component* c) override;
        std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
};

