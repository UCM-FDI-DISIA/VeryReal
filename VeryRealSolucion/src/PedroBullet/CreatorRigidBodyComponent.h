#pragma once
#include "CreatorComponent.h"
#include "exportPedroBullet.h"
namespace VeryReal {
	class VERYREAL_PEDROBULLET CreatorRigidBodyComponent: public CreatorComponent
	{
	public:
		CreatorRigidBodyComponent(){}
		virtual ~CreatorRigidBodyComponent(){}
		Component* CreatorSpecificComponent() override;
        std::pair<bool,std::string> SpecificInitComponent(Component* c) override;
        std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) override;
	};
}


