#pragma once
#include "CreatorComponent.h"
namespace VeryReal {

	class CreatorLightComponent :public CreatorComponent
	{
		CreatorLightComponent(){}
		virtual ~CreatorLightComponent(){}
		Component* CreatorSpecificComponent() override;
	};
}



