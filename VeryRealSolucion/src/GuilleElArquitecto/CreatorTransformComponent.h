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
        void SpecificInitComponent(Component* c) override;
        void SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
};

