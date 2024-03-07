#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "Component.h"
namespace VeryReal {
	
	class CreatorComponent{
	private:
		
	public:
		CreatorComponent();
		virtual ~CreatorComponent();
		virtual Component* CreatorSpecificComponent() = 0;
	};
}
#endif


