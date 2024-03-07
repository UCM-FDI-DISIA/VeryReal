#pragma once
#ifndef CREATORTRANSFORMCOMPONENT
#define CREATORTRANSFORMCOMPONENT
#include "CreatorComponent.h"
namespace VeryReal {
	//subfábrica 
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		CreatorTransformComponent();
		virtual ~CreatorTransformComponent();
		Component* CreatorSpecificComponent() override;	
	};
}
#endif

