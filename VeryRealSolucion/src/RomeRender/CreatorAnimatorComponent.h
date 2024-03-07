#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	class CreatorAnimatorComponent :public CreatorComponent
	{
	public:
		CreatorAnimatorComponent(){}
		virtual ~CreatorAnimatorComponent(){}
		Component* CreatorSpecificComponent() override;
	};

}

