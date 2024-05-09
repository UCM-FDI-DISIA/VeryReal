#pragma once
#ifndef VARIANTCLASS
#define VARIANTCLASS

#include <variant>
#include <iostream>
#include <string>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "export.h"

#pragma warning(disable : 4251)

/*
	Clase encargada de almacenar un valor que puede ser de varios tipos.
	Esta clase es usada a la hora de añadir parametros a nuestro componente.
*/

namespace VeryReal {
	class VERYREAL_GUILLEELARQUITECTO VariantClass
	{
	private:
		std::variant<int, float, double,VeryReal::Vector2, VeryReal::Vector3, VeryReal::Vector4,std::string,bool> myvariant;
		
	public:
		inline auto GetVariant() { return myvariant; }
		template<typename T>
		inline void SetVariant(T variable) { myvariant = variable; }

	};
}

#pragma warning(default : 4251)

#endif