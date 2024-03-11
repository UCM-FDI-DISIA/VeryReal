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




//scene{
//entity{
//tranform{
//position {0,50,0
//rotation {0,0,0}
//scale{0,0,0}
//}
#endif

