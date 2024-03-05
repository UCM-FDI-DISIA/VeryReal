#pragma once
#include "CreatorComponent.h"
#include "TransformComponent.h"
namespace VeryReal {
	//subfábrica 
	class CreatorTransformComponent :public CreatorComponent {
	private:
	public:
		CreatorTransformComponent(){}
		virtual ~CreatorTransformComponent(){}
		//genera el componente Transform
		Component* CreatorSpecificComponent() const override  {
			Component* t = new TransformComponent();
			return t;
		}
		
	};
}


