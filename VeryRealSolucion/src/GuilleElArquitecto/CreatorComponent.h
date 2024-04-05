#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "VariantClass.h"
#include <unordered_map>
#include "export.h"
namespace VeryReal {
	class Component;
	class VERYREAL_API CreatorComponent{
		using parameters_name = std::string;
	protected:
		std::unordered_map<parameters_name, VariantClass*> parameters_map;
		
	public:
		CreatorComponent();
		virtual ~CreatorComponent();
		//Tenemos que preguntar a Pedro Pablo como hacer para pasarle como argumento valores, 
		// con un template no puedes un metodo virtual

		virtual Component* CreatorSpecificComponent() = 0;
        virtual void SpecificInitComponent(Component* c) = 0;

		template<typename T>
		void AddParameter(parameters_name p_name,T p) {
			RemoveParameter(p_name);
			VariantClass* v = new  VariantClass();
			v->SetVariant(p);
			parameters_map.insert({ p_name ,v });
		}
		void RemoveParameter(parameters_name p_name) {
			if (HasParameter(p_name)) {
				delete parameters_map.at(p_name);
				parameters_map.erase(p_name);
			}
		}
		inline bool HasParameter(std::string s) {
			return parameters_map.count(s);
		}
		inline VariantClass* GetParameter(parameters_name p_name) {
			return parameters_map.at(p_name);
		}
	};
}
#endif


