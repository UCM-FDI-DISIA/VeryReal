#pragma once
#include "CreatorComponent.h"
namespace VeryReal {

	class CreatorMeshRenderComponent :public CreatorComponent
	{
		CreatorMeshRenderComponent(){}
		virtual ~CreatorMeshRenderComponent(){}
		Component* CreatorSpecificComponent() override;
	};
}

