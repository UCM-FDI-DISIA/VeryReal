#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	class VERYREAL_API CreatorRigidBodyComponent: public CreatorComponent
	{
	public:
		CreatorRigidBodyComponent(){}
		virtual ~CreatorRigidBodyComponent(){}
		Component* CreatorSpecificComponent() override;
        void SpecificInitComponent(Component* c) override;
	};
}


