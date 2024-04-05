#pragma once
#include "CreatorComponent.h"
#include "export.h"
namespace VeryReal {
	class VERYREAL_API CreatorColliderComponent :public CreatorComponent
	{
	public:
		CreatorColliderComponent(){}
		virtual ~CreatorColliderComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}


