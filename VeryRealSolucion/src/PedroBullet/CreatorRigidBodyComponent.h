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
        void SpecificInitComponent(Component* c) override;
	};
}


