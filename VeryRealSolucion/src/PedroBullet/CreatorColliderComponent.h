#pragma once
#include "CreatorComponent.h"
#include "exportPedroBullet.h"
namespace VeryReal {
	class VERYREAL_PEDROBULLET CreatorColliderComponent :public CreatorComponent
	{
	public:
		CreatorColliderComponent(){}
		virtual ~CreatorColliderComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}


