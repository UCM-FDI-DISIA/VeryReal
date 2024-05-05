#pragma once
#ifndef _FMOD_SOUND_MANAGER
#define _FMOD_SOUND_MANAGER

#include <Manager.h>
#include <Vector3.h>
#include <string>
#include <unordered_map>
#include "exportAudioLeon.h"

namespace FMOD {
class Sound;
class ChannelGroup;
class Channel;
class System;

}

typedef struct FMOD_VECTOR FMOD_VECTOR;
enum FMOD_RESULT;

namespace VeryReal {
typedef unsigned int FMOD_MODE;
typedef int CHANNEL_NUMBER;


//Cantidad máxima de canales que puede haber en esta configuración particular del sistema de sonido de FMOD.
const int MAX_CHANNELS = 100;
//Factor de escalado que determina cuanto varía el pitch debido al efecto dopler de un sonido 3D.
const float DOPPLER_SCALE = 1.0f;
//Factor de distancia relativo, comparado a 1 metro. Establece cuantas unidades por metro el sistema interpreta.
const float DISTANCE_FACTOR = 1.0f;
//Factor global de atenuación por distancia.
const float ROLLOFF_SCALE = 1.0f;
//Pitch base de un sonido. Determina el pitch "normal" de un sonido cuando el emisor esta parado.
const float BASE_PITCH = 1.0f;

/* AudioManager ofrece un sistema de creación, almacenaje y borrado de sonidos.
	así como toda el esqueleto interno de funcionamiento de FMOD.
	Puedes acceder a AudioManager llamando al método AM().
	*/

#pragma warning(disable : 4251)

class VERYREAL_AUDIOLEON AudioManager : public VeryReal::Manager<AudioManager> {
    friend Singleton<AudioManager>;

        private:
    //Almacena los sonidos de FMOD enlazados al nombre establecido por el usuario.
    std::unordered_map<std::string, FMOD::Sound*> sounds_map;
    //Almacena los sonidos dew FMOD enlazados al último canal en el que sonaron.
    std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> last_played_map;
    //Almacena los grupos de canales enlazados a sus nombres.
    std::unordered_map<std::string, FMOD::ChannelGroup*> channel_group_maps;
    //Almacena los canales de FMOD.
    std::vector<FMOD::Channel*> channels_vector;
    //Grupos de canales predeterminados ofrecidos por Auido_Leon
    FMOD::ChannelGroup *effects = nullptr, *music = nullptr, *master = nullptr;
    //Vector en el que se almacenan los índices disponibles para "listeners" de FMOD.
    std::vector<bool> listeners;
    //El sistema de audio ofrecido por FMOD.
    FMOD::System* sound_system = nullptr;
    //Sonido recibido por el microfono
    FMOD::Sound* mic_sound = nullptr;
    //Variable de control que sirve de comprobación después de hacer uso de cualquiera de las funciones de sistema de sonido.
    FMOD_RESULT result;

    /// <summary>
    /// Cambia el volumen de un canal determinado.
    /// </summary>
    /// <param name="channelGroupName">El canal en concreto del cuál se va acambiar el volumen.</param>
    /// <param name="volume">EL nuevo valor de volumen que se le dará al canal.</param>
    /// <returns>False si no se encontró el canal indicado o si hubo un error de FMOD. True si el volumen del canal se cambió con éxito.</returns>
    bool ChangeChannelVolume(std::string channelGroupName, float volume);

        private:
    AudioManager();

        public:
    static bool Init() {
        AudioManager* a = new AudioManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return true;
        }
        return false;
    }
    //Destructor de la clase AudioManager. Se encarga de eliminar todo sonido creado y de liberar toda la infrestructura de FMOD.
    ~AudioManager();

    void InitManager();
    //Inicializacion de los recursos necesarios para recoger input del microfono
    void InitAudioRecording();
    //Actualiza el sistema de sonido en cada bucle del juego.
    void SystemRefresh(const double& dt);

    //Convierte un Vector3 propio del motor a un FMOD_VECTOR
    FMOD_VECTOR V3ToFmodV3(VeryReal::Vector3 conversion) const;

    /**
		Makes sure the sound name is in all lower case with no spaces.
		@param name : the name to change.
		*/

    /// <summary>
    /// Pone todas las letras del nombre de un sonido en minúscula.
    /// </summary>
    /// <param name="name">El nombre del sonido que se cambia.</param>
    void NameToLower(std::string& name);

    /// <summary>
    /// Compureba si el resultado de cualquiera de las funciones de FMOD se han completado con éxito.
    /// </summary>
    /// <param name="FMODResult">El resultado a comprobar.</param>
    /// <returns>Devuelve true o false si el resultado es exitoso o no.</returns>
    bool CheckFMODResult(FMOD_RESULT FMODResult);

    /// <summary>
    /// Extrae un sonido de FMOD del mapa de sonidos a través del sonido que le dió el usuario.
    /// </summary>
    /// <param name="soundName">EL nombre de sonido mediante el cuál se busca en el mapa.</param>
    /// <returns>Devuelve el sonido concreto que se buscaba o "nullptr" si no se encontró ningún sonido con ese nombre.</returns>
    FMOD::Sound* GetSound(std::string soundName);

    //Devuelve la referencia al sistema de sonido de FMOD.
    FMOD::System* GetSoundSystem();

    /// <summary>
    /// Extrae un grupo de canales de FMOD del mapa de grupos a través del nombre que le dió el usuario.
    /// </summary>
    /// <param name="channelGroupName">EL nombre de grupo mediante el cuál se busca en el mapa.</param>
    /// <returns>Devuelve el grupo concreto que se buscaba o "nullptr" si no se encontró ningún grupo con ese nombre.</returns>
    FMOD::ChannelGroup* GetGroupChannel(std::string channelGroupName);

    //Devuelve la referencia al vector de canales de AudioManager.
    std::vector<FMOD::Channel*> GetChannelsVector();

    //Establece el valor para un canal.
    void setChannelValue(int pos, FMOD::Channel* newChannel);

    //Devuelve la referencia al mapa que conecta los sonidos al último canal en el que se reprodujeron.
    std::unordered_map<FMOD::Sound*, CHANNEL_NUMBER> GetLastPlayedMap();

    //Añade un nuevo sonido al mapa de sonidos.
    void AddNewSound(std::pair<std::string, FMOD::Sound*> newSound);

    void SetLastPlayedMap(FMOD::Sound* sound, int channelNumber);

    /// <summary>
    /// Extrae un canal de FMOD del mapa de canales a través del nombre de sonido que se está reproduciendo en dicho canal.
    /// </summary>
    /// <param name="soundName">EL nombre del sonido que se está reproduciendo.</param>
    /// <returns>Devuelve el canal correspondiente o "nullptr" si no se encuentra dicho canal.</returns>
    FMOD::Channel* GetChannel(std::string soundName);

    /// <summary>
    /// Crea un grupo de canales si no existe ya un grupo con el mismo nombre.
    /// </summary>
    /// <param name="groupName">El nombre del grupo de canales que se quiere crear.</param>
    /// <returns>Devuelve true o false si el grupo de canales fue creado con éxito o no.</returns>
    bool CreateChannelGroup(std::string groupName);

    /// <summary>
    /// Cambia el volumen de un grupo de canales.
    /// </summary>
    /// <param name="groupName">El nombre del grupo de canales.</param>
    /// <param name="newVolume">El nuevo valor del volumen.</param>
    /// <returns>Devuelve true o false en función de si el volumen fue cambiado con éxito o no.</returns>
    bool SetGroupChannelVolume(std::string groupName, float newVolume);

    /// <summary>
    /// Comprueba el volumen de un grupo de canales concreto.
    /// </summary>
    /// <param name="groupName">El nombre del grupo de canales que se va a comprobar.</param>
    /// <returns>Devuelve el valor del volumen del grupo de canales.</returns>
    float GetGroupChannelVolume(std::string groupName);

    /// Obtiene la intensidad del sonido recibido por el microfono
    /// @return Intensidad del sonido (en un rango de 0 a 1)
    float InputSoundIntensity();

    /// <summary>
    /// Para todos los canales que estén reproduciendo añgún sonido.
    /// </summary>
    /// <returns>Devuelve true o false en función de si todos los canales dejaron de reproducir o no.</returns>
    bool StopEverySound();

    /// <summary>
    /// Para todos los canales que estén reproduciendo añgún sonido.
    /// </summary>
    /// <returns>Devuelve true o false en función de si todos los canales dejaron de reproducir o no.</returns>
    bool PauseEverySound();

    /// <summary>
    /// Para todos los canales que estén reproduciendo añgún sonido.
    /// </summary>
    /// <returns>Devuelve true o false en función de si todos los canales empezaron de reproducir o no.</returns>
    bool ResumeEverySound();

    /// <summary>
    /// Libera la memoria dinámica creada durante la ejecución al crear un nuevl sonido de FMOD.
    /// </summary>
    /// <param name="soundName">EL nombre del sonido que va a ser eliminado.</param>
    /// <returns>Devuelve true o false en función de si el sonido fue eliminado con éxito o no.</returns>
    bool DeleteSound(std::string soundName);

    /// <summary>
    /// Elimina un listener del vector de listeners y resetea sus valores.
    /// </summary>
    /// <param name="index">El índice del listener a resetear.</param>
    void RemoveListener(int index);

    /// <summary>
    /// Selecciona un listener nuevo para configurarlo.
    /// </summary>
    /// <returns>Devuelve el índice del listener configurado o -1 si no se pudo configurar con éxito.</returns>
    inline int GetNextUsefulListenerIndex() {
        for (int i = 0; i < listeners.size(); i++) {
            if (!listeners [i]) listeners [i] = true;
            return i;
        }
        return -1;
    }
    /*void startRecording();*/
};

#pragma warning(default : 4251)

//Esta macro define una manera compacta de usar el singleton AudioManager.
//En lugar de escribir AudioManager::instance->method(), escribiremos AM().method()
inline AudioManager& AM() { return *AudioManager::Instance(); }
}

#endif   // !_FMOD_SOUND_MANAGER