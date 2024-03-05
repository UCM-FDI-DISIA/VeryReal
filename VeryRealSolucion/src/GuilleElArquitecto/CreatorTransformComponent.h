#pragma once
#include "CreatorComponent.h"
#include "TransformComponent.h"

namespace VeryReal {
	//subfábrica 
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		Component* CreatorSpecificComponent()  override  {
			TransformComponent* t = new TransformComponent();
			return t;
		}
		
	};
}


