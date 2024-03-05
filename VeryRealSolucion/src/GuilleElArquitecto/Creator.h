#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "CreatorComponent.h"

namespace VeryReal {
	using creator_name = string;

	class Creator :public VeryReal::Singleton<Creator>
	{
		friend Singleton<Creator>;
		
	private:
		unordered_map<creator_name, CreatorComponent*> creators_map;
	public:
		Creator();
		virtual ~Creator();
		template<typename ...Ts>
		inline Component* CallSpecificCreator(string creator_name, Ts && ... args) {
			return creators_map[creator_name]->CreatorSpecificComponent();
		}

		void AddCreator(const creator_name& c_name, CreatorComponent* cretorcomponent);
		//Remueve el Componente de la Entidad en la que se encuentra
		void RemoveCreator(creator_name c_name);

		//Indica si la entidad tiene este componente
		inline bool HasCreator(creator_name c_name) {
			return creators_map.count(c_name);
		}
		//Devuelve el componente especifico y si no esta devuelve nullptr
		template<typename T>
		inline T* GetCreator(creator_name c_name) {
			if (!HasCreator(c_name)) {
				return nullptr;
			}
			return static_cast<T*>(creators_map.at(c_name));

		}

	};
}


