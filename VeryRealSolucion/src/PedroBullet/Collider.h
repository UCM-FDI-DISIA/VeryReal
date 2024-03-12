#pragma once
#ifndef COLLIDER
#define COLLIDER

#include <Component.h>


//Collider es una clase cuya �nica funci�n es la de llamar a los m�todos pertinentes de la clase Entity y estos metodos llamar�n a m�todos los homonimos.
//El proceso es:
	// 1.- Se detecta una colisi�n a trav�s de las funciones callback definidas en PedroBullet
	// 2.- Se comprueba que ambos objetos f�sicos tienen el componente Collider
namespace VeryReal 
{
	class Entity;
	class Collider : public VeryReal::Component
	{
	public:
		Collider();
		virtual ~Collider();
		void Init();
		void OnCollisionEnter(Entity* other) override;
		void OnCollisionStay(Entity* other) override;
		void OnCollisionExit(Entity* other) override;
	private:
	};

	}

#endif