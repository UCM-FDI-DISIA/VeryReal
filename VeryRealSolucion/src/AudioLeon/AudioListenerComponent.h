#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOLISTENER
#define __ENTITYCOMPONENT_AUDIOLISTENER

#include <Component.h>
#include "exportAudioLeon.h"
#include "Vector3.h"
namespace FMOD {
	class Sound;
}

 namespace VeryReal {
    class TransformComponent;
    //FMOD ofrece "escuchadores" din�micos que hacen de veces de receptores de los sonidos reproducidos por FMOD.
    //Este componente gestiona el listener de una entidad y actualiza sus par�metros.
    class VERYREAL_AUDIOLEON AudioListenerComponent : public VeryReal::Component {
    public:
        //Constructora por defecto de AudioListener.
        AudioListenerComponent();
        //Destructora del componente AudioListener.
        ~AudioListenerComponent();
        std::pair<bool,std::string> InitComponent();
        
        /// <summary>
        /// Actualiza la posici�n del "listener" de FMOD en funci�n de la posici�n de la entidad a la que este componente esta enlazado.
        /// </summary>
        /// <param name="dt">El delta time que se encarga de sincronizar las actualizaciones.</param>
        void Update(const double& dt);


        /// <summary>
        /// Establece la posici�n de un listener.
        /// </summary>
        /// <param name="index">El �ndice necesario para referirse a un listener.</param>
        /// <param name="listenerPos">�Vector posici�n a establecer del listener.</param>
        /// <param name="listenerFW">Vector forward a establecer del listener.</param>
        /// <param name="listenerUP">Vector up a establecer del listener.</param>
        /// <param name="listenerVel">Vector de velocidad a establecer del listener.</param>
        void UpdateListenersPosition(int index, VeryReal::Vector3 listenerPos, VeryReal::Vector3 listenerFW, VeryReal::Vector3 listenerUP,
                                     VeryReal::Vector3 listenerVel = {0, 0, 0});

    private:
        //Posici�n del listener.
        VeryReal::Vector3 position;
        //�ltima posici�n registrada del listener.
        VeryReal::Vector3 last_position = VeryReal::Vector3(0, 0, 0);
        //�ndice con el que se identifica cada listener para FMOD.
        int listener_index;
        //Almacena el componente "Transform" y "RigidBody" de la entidad a la que este componente esta enlazada.
        VeryReal::TransformComponent* transform = nullptr;

    };
 }
	


#endif // !EC_AUDIO_LISTENER