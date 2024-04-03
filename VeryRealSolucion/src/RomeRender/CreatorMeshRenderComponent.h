#pragma once
#include "CreatorComponent.h"
namespace VeryReal {

	class CreatorMeshRenderComponent :public CreatorComponent
	{
	public:
		CreatorMeshRenderComponent(){}
		virtual ~CreatorMeshRenderComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}

