#pragma once
#ifndef VARIANTCLASS
#define VARIANTCLASS

#include <variant>
#include <iostream>
#include <string>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


namespace VeryReal {
	class VariantClass
	{
	private:
		std::variant<int, float,Vector2,Vector3,Vector4,std::string,bool> myvariant;
		
	public:
		inline auto GetVariant() { return myvariant; }
		template<typename T>
		inline void SetVariant(T variable) { myvariant = variable; }

	};
}


#endif

