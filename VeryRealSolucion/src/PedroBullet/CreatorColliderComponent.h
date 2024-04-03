#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	class CreatorColliderComponent :public CreatorComponent
	{
	public:
		CreatorColliderComponent(){}
		virtual ~CreatorColliderComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}


