#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT

namespace VeryReal {
	class Component;
	class CreatorComponent{
	private:
		
	public:
		CreatorComponent();
		virtual ~CreatorComponent();
		virtual Component* CreatorSpecificComponent() = 0;
	};
}
#endif


