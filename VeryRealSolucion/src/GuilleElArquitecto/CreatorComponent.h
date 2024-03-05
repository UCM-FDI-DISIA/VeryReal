#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "Singleton.h"
#include "Component.h"

namespace VeryReal {
	template<typename T>
	class CreatorComponent :public Singleton<T>{
		friend Singleton<T>;
	private:
	public:
		virtual ~CreatorComponent() {};
		virtual Component* CreatorSpecificComponent() const = 0;

		//OPCION B: llamar a Dios y luego Profetas
		void LlamaalCreator(string component_name) {
			//Creatorcomponent_name->CreatorSpecificComponent();
		}
	};
}
#endif


