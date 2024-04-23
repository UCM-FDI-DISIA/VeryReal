#pragma once
#ifndef COLLIDERCOMPONENT
#define COLLIDERCOMPONENT
#include "exportPedroBullet.h"
#include <Component.h>


//ColliderComponent es una clase cuya �nica funci�n es la de llamar a los m�todos pertinentes de la clase Entity y estos metodos llamar�n a m�todos los homonimos.
//El proceso es:
	// 1.- Se detecta una colisi�n a trav�s de las funciones callback definidas en PedroBullet
	// 2.- Se comprueba que ambos objetos f�sicos tienen el componente 


namespace VeryReal 
{
	class Entity;
	class VERYREAL_PEDROBULLET ColliderComponent : public Component
	{
	public:
        ColliderComponent(){};
		virtual ~ColliderComponent(){};
		void Init();
		void OnCollisionEnter(Entity* other) override;
		void OnCollisionStay(Entity* other) override;
		void OnCollisionExit(Entity* other) override;
	private:
	};

	}

#endif