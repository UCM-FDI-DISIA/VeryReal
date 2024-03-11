#pragma once
#ifndef CREATOR
#define CREATOR
#include "Singleton.h"
#include "CreatorComponent.h"
#include <unordered_map>
#include <string>

using namespace std;
namespace VeryReal {
	using creator_name = string;

	class Creator :public VeryReal::Singleton<Creator>
	{
		friend Singleton<Creator>;
		
	private:
		unordered_map<creator_name, CreatorComponent*> creators_map;
		
	public:
		//Creator();
		//virtual ~Creator();
	
		inline Component* CallSpecificCreator(creator_name c_name) {
			return creators_map[c_name]->CreatorSpecificComponent();
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


		//ESTO NO VA AQUÍ, ES UN ESQUEMA PARA ENTENDER DESPUÉS COMO LLERA LUA Y A QUÉ TENDREMOS QUE LLAMAR!!!!
		//IMPORTANTE
		void LUARead() {
			string namecomponent, position, rotation, scale;
			Vector3 p, r, s;
			if (HasCreator(namecomponent)) {
				GetCreator(namecomponent)->AddParameter(position, p);
			}
		}



	};
}
#endif


