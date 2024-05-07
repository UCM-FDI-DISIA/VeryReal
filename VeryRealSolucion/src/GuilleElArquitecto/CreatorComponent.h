#pragma once
#ifndef CREATORCOMPONENT
#define CREATORCOMPONENT
#include "VariantClass.h"
#include <unordered_map>
#include "export.h"

#pragma warning(disable : 4251)

namespace VeryReal {
	class Component;
	class VERYREAL_GUILLEELARQUITECTO CreatorComponent{
		using parameters_name = std::string;
	protected:
		std::unordered_map<parameters_name, VariantClass> parameters_map;
		
	public:
        CreatorComponent(){};
    virtual ~CreatorComponent();
		virtual Component* CreatorSpecificComponent() = 0;
        virtual std::pair<bool,std::string> SpecificInitComponent(Component* c) = 0;
        virtual std::pair<bool, std::string> SpecificInitComponentByCopy(Component* c, Component* other) = 0;

		template<typename T>
		void AddParameter(parameters_name p_name,T p) {
			VariantClass v;
			v.SetVariant(p);
            if (HasParameter(p_name) ) {
				parameters_map.at(p_name) = v;
			}
			else {
				parameters_map.insert({p_name, v});
			}
		}

		void RemoveParameter(parameters_name p_name) {
			if (HasParameter(p_name)) {
				parameters_map.erase(p_name);
			}
		}

		inline bool HasParameter(std::string s) {
			return parameters_map.count(s);
		}

		inline VariantClass* GetParameter(parameters_name p_name) {
			return &parameters_map.at(p_name);
		}
	};
}

#pragma warning(default : 4251)

#endif