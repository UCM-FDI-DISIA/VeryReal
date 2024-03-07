#pragma once
#ifndef CREATORTRANSFORMCOMPONENT
#define CREATORTRANSFORMCOMPONENT
#include "CreatorComponent.h"
#include "TransformComponent.h"

namespace VeryReal {
	//subfábrica 
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		CreatorTransformComponent();
		virtual ~CreatorTransformComponent();
		Component* CreatorSpecificComponent()  override  {
			TransformComponent* t = new TransformComponent();
			return t;
		}
		
	};
}
#endif

