#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "Component.h"
namespace VeryReal {
	
	class CreatorComponent{
	private:
		
	public:
		virtual Component* CreatorSpecificComponent() = 0;
	};
}
#endif


