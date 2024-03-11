#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	class CreatorRigidBodyComponent: public CreatorComponent
	{
	public:
		CreatorRigidBodyComponent(){}
		virtual ~CreatorRigidBodyComponent(){}
		Component* CreatorSpecificComponent() override;
	};
}


