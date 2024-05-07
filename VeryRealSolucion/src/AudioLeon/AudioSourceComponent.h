#pragma once
#ifndef __ENTITYCOMPONENT_AUDIOSOURCE
#define __ENTITYCOMPONENT_AUDIOSOURCE

#include <string>
#include <Component.h>
#include "exportAudioLeon.h"

namespace FMOD {
	class Sound;
}

namespace VeryReal {
	class TransformComponent;
	class Vector3;
    class AudioManager;
  }

enum FMOD_RESULT;
typedef unsigned int FMOD_MODE;
	

	
#pragma warning(disable : 4251)

namespace VeryReal{
    //AudioSourceComponent se encarga de reproducir un archivo de audio en la escena.
    //Los Audio_Listeners que se encuentren en rango escuchar�n el audio con distintas variaciones en lugar de su posici�n en la escena.
    class VERYREAL_AUDIOLEON AudioSourceComponent : public VeryReal::Component {
            public:
        //Constructor por defecto.
        AudioSourceComponent();
        //Destructora que se encarga de eliminar la memoria din�mica del sonido concreto.
        ~AudioSourceComponent();
        std::pair<bool, std::string> InitComponent(std::string name, std::string path, bool onstart = false, std::string groupchannel = "master",
                                                   float volume = 0.1,
                                                   bool threed = false, bool loop = false, float mindistance = 1.0f, float maxdistance = 60.0f);


            /// <summary>
            /// Crea un sonido 3D.
            /// </summary>
            /// <returns>Devuelve true o false en funci�n de si el sonido fue creado con �xito o no.</returns>
            bool Create3DSound();

            /// <summary>
            /// Crea un sonido no 3D.
            /// </summary>
            /// <returns>Devuelve true o false en funci�n de si el sonido fue creado con �xito o no.</returns>
            bool CreateNormalSound();

            /// <summary>
            /// Configuira los atributos 3D (posici�n y velocidad) de un sonido.
            /// </summary>
            /// <param name="soundName">El nombre del sonido cuyos atributos se van a configurar.</param>
            /// <param name="position">El valor de la posici�n de la fuente de sonido.</param>
            /// <param name="velocity"EL valor de la velocidad a la que se mueve la fuente de sonido.</param>
            /// <returns>Devuelve true o false en funci�n de si los atributos fueron configurados con �xito o no.</returns>
            bool Set3DSoundAtributes(VeryReal::Vector3 position, VeryReal::Vector3 velocity);

            /// <summary>
            /// Comprueba si hay alg�n canal disponible para reproducir el sonido asignado al componente y se lo asigna para ser reproducido.
            /// </summary>
            /// <param name="channelGroup">EL grupo de canales desde el que se reproducir� el sonido.</param>
            /// <param name="channelPos">La posici�n del canal que ser� usado para paneado y atenuaci�n.</param>
            /// <param name="channelVel">La velocidad del cana que ser� usado para efecto doppler.</param>
            /// <param name="channelVolume">Volumen de reproducci�n del sonido.</param>
            /// <returns>Devuelve true o false en funci�n de si se encontr� un canal para re3producir el sonido.</returns>
            bool PlayAudioSource(std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume);

            /// <summary>
            /// Busca un canal y en caso de que exista, para el sonido que se este reproduciendo, devolvi�ndolo al principio.
            /// </summary>
            /// <returns>Devuelve true o false en funci�n de si el sonido fue detenido con �xito o no.</returns>
            bool StopSound();

            /// <summary>
            /// Busca un canal y en caso de que exista, pause el sonido que se est� reproduciendo en ese canal.
            /// </summary>
            /// <param name="Pause">: indica si se pausa o se reactiva</param>
            /// <returns>Devuelve true o false en funci�n de si el sonido fue detenido con �xito o no.</returns>
            bool PauseSound(bool Pause);

        /// <summary>
        /// Inicia el sonido con los par�metros que se hayan facilitado desde la factor�a.
        /// </summary>
        virtual std::pair<bool, std::string> Start();

            /// <summary>
            /// Actualiza a cada paso del bucle principal el componente AudioSource.
            /// </summary>
            /// <param name="dt">El delta time que se encarga de sincronizar las actualizaciones.</param>
            virtual void Update(const double& dt);

            /// <summary>
            /// Le da play al sonido del AudioSourceComponent.
            /// </summary>
            void Play();

            /// <summary>
            /// Detiene por completo el sonido del AudioSourceComponent.
            /// </summary>
            void Stop();

            /// <summary>
            /// Para el sonido del AudioSourceComponent.
            /// </summary>
            void Pause();

            /// <summary>
            /// Vuelve a reproducir un sonido desde donde se paus�.
            /// </summary>
            void Resume();

            /// <summary>
            /// Chequea si un audio esta siendo reproducido o no.
            /// </summary>
            /// <returns>DEvuelve truo o false en func�n de si el audio esta siendo reproducido o no.</returns>
            bool IsPlaying();

        /// <summary>
        /// Establece el volumen con el que un sonido ser� reproducido.
        /// </summary>
        /// <param name="value">El valor para el volumen que se establecer�.</param>
        /// <returns>Devuelve true o false en funci�n de si se ha cambiado el volumen con �xito o no.</returns>
        std::pair<bool, std::string> SetVolume(float value);

            /// <summary>
            /// Establece la velocidad a la que un sonido ser� reproducido.
            /// </summary>
            /// <param name="newSpeed"></param>
            /// <returns></returns>
            bool SetSpeed(float newSpeed);

        /// <summary>
        /// Establece una nueva configuraci�n para la atenuaci�n m�nima y m�xima que sufrir�a un sonido por distancia.
        /// </summary>
        /// <param name="minDistance">Distancia a la que no habr� ninguna atenuaci�n.</param>
        /// <param name="maxDistance">Distancia a la que habr� m�xima atenuaci�n</param>
        /// <returns>Devuelve true o false en funci�n de si las nuevas configuraciones para la atenuaci�n fueron o no establecidas.</returns>
        std::pair<bool, std::string> SetMinMaxDistance(float minDistance, float maxDistance);

      

            /// <summary>
            /// Almacena la ruta relativa del archivo de audio.
            /// </summary>
            /// <param name="path">El nombre de la ruta relativa.</param>
            void SetSourcePath(std::string path);

            /// <summary>
            /// Almacena el nombre dado por el usuario al sonido de FMOD.
            /// </summary>
            /// <param name="name">El nombre dado por el jugador.</param>
            void SetSourceName(std::string name);

            /// <summary>
            /// Almacena el nombre de grupo de canales desde el cu�l se reproducir� este sonido.
            /// </summary>
            /// <param name="name">EL nombre del grupo de canales.</param>
            void SetGroupChannelName(std::string name);

            /// <summary>
            /// Almacena le condici�n de bucle del sonido de FMOD.
            /// </summary>
            /// <param name="lop">Devuelve true o false en funci�n de si el sonido se reproducir� en bucle o no.</param>
            void SetLoop(bool lop);

            /// <summary>
            /// Almacena la condici�n de 3D del sonido de FMOD.
            /// </summary>
            /// <param name="threeD">La condici�n a almacenar.</param>
            void SetIsThreeD(bool threeD);

            /// <summary>
            /// Almacena si el sonido de FMOD ser� reproducido en cuanto sea posible o si har� falta darle al play.
            /// </summary>
            /// <param name="playOnStart">Si el sonido debe ser reproducido en cuanto sea posible o no.</param>
            void SetPlayOnStart(bool playOnStart);

            /**
		    * Get the volume of the audio.
		    * @return The current volume value.
		    */

            //Devuelve el valor de volumen almacenado en este componente.
            float GetVolume();

            inline std::string GetSoundName() { return sound_name; }
            inline std::string GetSoundPath() { return sound_path; }
            inline bool GetPlayOnStart() { return play_on_start; }
            inline std::string GetSoundGroup() { return sound_group; }
            inline bool GetIsThreeD() { return is_three_d; }
            inline bool GetIsLoop() { return loop; }
            inline float GetMinDistance() { return min_distance; }
            inline float GetMaxDistance() { return max_distance; }


       private:
            //El volumen del sonido.
            float volume;
            //La velocidad de reproducci�n del audio.
            float speed;
            //Distancia de m�nima atenuaci�n de un sonido 3D.
            float min_distance;
            //Distancia de m�xima atenuaci�n de un sonido 3D.
            float max_distance;

            //FMOD::Sound* mSound; // The FMOD sound object
            //El n�mero que se corresponde con el canal en el que se reproducir� este sonido.
            int sound_channel;
            //El nombre de grupo de canales en el que se reproducir� este sonido.
            std::string sound_group;
            //La ruta relativa al archivo de audio con el que se crear� el sonido de FMOD.
            std::string sound_path;
            //El nombre dado por el usuario al sonido de FMOD.
            std::string sound_name;
            //Si el sonido esta siendo reproducido o no.
            bool playing = true;
            //Si el sonido se reproducir� en bucle o no.
            bool loop = false;
            //Si el sonido es 3D o no.
            bool is_three_d = false;
            //Si el sonido se reproducir� de inicio o no.
            bool play_on_start = true;

            //Variable de control que sirve de comprobaci�n despu�s de hacer uso de cualquiera de las funciones de sistema de sonido.
            FMOD_RESULT result;
            //Almacena el componente "Transform" y �RigdBody" de la entidad a la que este componente esta enlazada.
            VeryReal::TransformComponent* transform = nullptr;

              /// <summary>
            /// Establece el modo de FMOD para cada sonido.
            /// </summary>
            /// <param name="newMode">Nueva flag que indica el modo a establecer.</param>
            /// <returns>Devuelve true o false en funci�n de si el nuevo modo de reproducci�n fue establecido con �xito o no.</returns>
            bool SetMode(FMOD_MODE newMode);
    };
}

#pragma warning(default : 4251)

#endif