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
        std::pair<bool, std::string> SpecificInitComponent(Component* c) override;
        std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
}

