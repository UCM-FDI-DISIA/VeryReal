#pragma once
#include "CreatorComponent.h"
#include "exportRomeRender.h"
namespace VeryReal {

	class VERYREAL_ROMERENDER CreatorMeshRenderComponent : public CreatorComponent
	{
	public:
		CreatorMeshRenderComponent(){}
		virtual ~CreatorMeshRenderComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}

