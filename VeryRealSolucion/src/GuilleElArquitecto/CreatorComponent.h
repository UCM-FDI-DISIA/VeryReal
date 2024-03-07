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
		//Tenemos que preguntar a Pedro Pablo como hacer para pasarle como argumento valores, 
		// con un template no puedes un metodo virtual
		virtual Component* CreatorSpecificComponent() = 0;
	};
}
#endif


