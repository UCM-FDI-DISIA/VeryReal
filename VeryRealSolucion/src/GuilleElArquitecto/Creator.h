#pragma once
#ifndef CREATOR
#define CREATOR
#include "Singleton.h"
#include "CreatorComponent.h"
#include <unordered_map>
#include <string>
#include "export.h"

namespace VeryReal {
	using creator_name = std::string;

	class VERYREAL_API Creator :public VeryReal::Singleton<Creator>
	{
		friend Singleton<Creator>;
		
	private:
		std::unordered_map<creator_name, CreatorComponent*> creators_map;
		
	public:
		//Creator();
		//virtual ~Creator();
	
		inline Component* CallSpecificCreator(creator_name c_name) {
			return creators_map[c_name]->CreatorSpecificComponent();
		}

		inline void CallSpecificInit(creator_name c_name, Component* c) { 
			creators_map[c_name]->SpecificInitComponent(c);
		}

		void AddCreator(const creator_name& c_name, CreatorComponent* cretorcomponent);
		//Remueve el Componente de la Entidad en la que se encuentra
		void RemoveCreator(creator_name c_name);

		//Indica si la entidad tiene este componente
		inline bool HasCreator(creator_name c_name) {
			return creators_map.count(c_name);
		}
		//Devuelve el creator especifico y si no esta devuelve nullptr
	
		inline CreatorComponent* GetCreator(creator_name c_name) {
			if (!HasCreator(c_name)) {
				return nullptr;
			}
			return creators_map.at(c_name);

		}


		//ESTO NO VA AQU�, ES UN ESQUEMA PARA ENTENDER DESPU�S COMO LLERA LUA Y A QU� TENDREMOS QUE LLAMAR!!!!
		//IMPORTANTE
		void LUARead() {
			std::string namecomponent, position, rotation, scale;
			Vector3 p, r, s;
			if (HasCreator(namecomponent)) {
				GetCreator(namecomponent)->AddParameter(position, p);
			}
		}



	};
}
#endif


