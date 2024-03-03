#pragma once
#include "Component.h"
#include <string>

namespace VeryReal {
	class  Animator : public Component
	{
		public:
			Animator(); //constructora
			virtual ~Animator(); //destructora
			//void update();
			void setActive(bool a); //metodo para activar la animacion
			void setLoop(bool l);  //metodo que pone la animacion en bucle
			string getCurrAnimName();  //para que devuelva el nombre de la anim actual
			bool isActive(); // getter
			bool isLoop(); //geter
			void playAnim(string animacion, bool loop = true); //inicia una aminacion
			void stopAnim(); //la para
			void resumeAnim(); //la vuelve a iniciar (no la crea)

		private:
			bool active;
			bool loop;
	};
}




