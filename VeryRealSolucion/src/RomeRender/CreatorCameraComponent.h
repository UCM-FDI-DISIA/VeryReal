#pragma once
#include "CreatorComponent.h"
namespace VeryReal {
	
	class CreatorCameraComponent:public CreatorComponent
	{
		CreatorCameraComponent();
		virtual ~CreatorCameraComponent();
		Component* CreatorSpecificComponent() override;
	};
}


