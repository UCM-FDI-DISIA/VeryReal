#pragma once
#ifndef CREATORTRANSFORMCOMPONENT
#define CREATORTRANSFORMCOMPONENT
#include "CreatorComponent.h"
namespace VeryReal {
	//subf�brica 
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		CreatorTransformComponent();
		virtual ~CreatorTransformComponent();
		Component* CreatorSpecificComponent() override;	
	};
}
#endif

