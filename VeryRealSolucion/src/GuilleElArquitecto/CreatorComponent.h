#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "Singleton.h"
#include "Component.h"


namespace VeryReal {
	
	class CreatorComponent{
	private:
		
	public:
		virtual ~CreatorComponent() {};
		virtual Component* CreatorSpecificComponent() const = 0;
		
		
	};
}
#endif


