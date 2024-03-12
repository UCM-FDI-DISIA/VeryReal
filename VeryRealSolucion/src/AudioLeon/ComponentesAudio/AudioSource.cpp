#include "AudioSource.h"
#include <AudioLeon.h>
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>
#include "VariantClass.h"
using namespace VeryReal;
using namespace std;
Component* CreatorAudioSource::CreatorSpecificComponent() {
    Audio_Source* a = new Audio_Source;
    string name, path, groupchannel;
    bool onstart=false, threed=false, loop=false;
    float volume=0.1, mindistance=1.0f, maxdistance =60.0f;
    
    if (std::holds_alternative<string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<string>(parameters_map.at("path")->GetVariant())) {
        path = std::get<string>(parameters_map.at("path")->GetVariant());
    }
    if (std::holds_alternative<string>(parameters_map.at("groupchannel")->GetVariant())) {
        groupchannel = std::get<string>(parameters_map.at("groupchannel")->GetVariant());
    }
    if (std::holds_alternative<bool>(parameters_map.at("onstart")->GetVariant())) {
        onstart = std::get<bool>(parameters_map.at("onstart")->GetVariant());
    }
    if (std::holds_alternative<bool>(parameters_map.at("loop")->GetVariant())) {
        loop = std::get<bool>(parameters_map.at("loop")->GetVariant());
    }
    if (std::holds_alternative<bool>(parameters_map.at("threed")->GetVariant())) {
        threed = std::get<bool>(parameters_map.at("threed")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("volume")->GetVariant())) {
        volume = std::get<float>(parameters_map.at("volume")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("mindistance")->GetVariant())) {
        mindistance = std::get<float>(parameters_map.at("mindistance")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("maxdistance")->GetVariant())) {
        maxdistance = std::get<float>(parameters_map.at("maxdistance")->GetVariant());
    }
    a->InitComponent(name, path, onstart, groupchannel, volume, threed, loop, mindistance, maxdistance);
    return a;
}

Audio_Source::Audio_Source()
{}

Audio_Source::~Audio_Source()
{
    AL().DeleteSound(sound_name);
}
bool Audio_Source::InitComponent(std::string name, std::string path, bool onstart = false, std::string groupchannel = "master", float volume = 0.1,
    bool threed = false, bool loop = false, float mindistance = 1.0f, float maxdistance = 60.0f) {

    SetSourceName(name);
    SetSourcePath(path);
    SetPlayOnStart(onstart);
    SetGroupChannelName(groupchannel);
    SetVolume(volume);
    SetIsThreeD(threed);
    SetLoop(loop);
    SetMinMaxDistance(mindistance, maxdistance);


}
bool Audio_Source::Create3DSound(std::string soundPath, std::string soundName, float minDistance, float maxDistance, bool loop)
{
    soundPath = "Assets/Sounds/" + soundPath;
    AL().NameToLower(soundName);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(soundName);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
    }

    if (!AL().CheckFMODResult(this->result)) return false;

    this->result = newSoundHandle->set3DMinMaxDistance(minDistance, maxDistance);
    if (!AL().CheckFMODResult(this->result)) return false;

    if (AL().CheckFMODResult(this->result)) {
        std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
        AL().AddNewSound(newSound);
        
#ifdef _DEBUG
        std::cout << "Sound created." << "\n";
#endif // DEBUG
        return true;
    }
    else {
        return false;
    }
}

bool Audio_Source::CreateNormalSound(std::string soundPath, std::string soundName, bool loop)
{
    soundPath = "Assets/Sounds/" + soundPath;
    AL().NameToLower(soundName);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(soundName);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->result = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
    }

    if (AL().CheckFMODResult(this->result)) {
        std::pair<std::string, FMOD::Sound*> newSound(soundName, newSoundHandle);
        AL().AddNewSound(newSound);
#ifdef _DEBUG
        std::cout << "Sound created." << "\n";
#endif // DEBUG
        return true;
    }
    else {
        return false;
    }
}

bool Audio_Source::Set3DSoundAtributes(std::string soundName, VeryReal::Vector3 position, VeryReal::Vector3 velocity)
{
    AL().NameToLower(soundName);
    FMOD::Channel* channelHandle = AL().GetChannel(soundName);
    if (channelHandle == nullptr) return false;
    FMOD_VECTOR p = AL().V3ToFmodV3(position), v = AL().V3ToFmodV3(velocity);

    channelHandle->set3DAttributes(&p, &v);
    return true;
}

bool Audio_Source::PlayAudioSource(std::string soundName, std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume)
{
    AL().NameToLower(soundName);
    FMOD::Sound* soundHandle = AL().GetSound(soundName);
    if (soundHandle == nullptr) return false;

    FMOD::ChannelGroup* playedChannelGroup = AL().GetGroupChannel(channelGroup);
    if (playedChannelGroup == nullptr) return false;

    FMOD_MODE finalSoundMode;
    soundHandle->getMode(&finalSoundMode);

    FMOD::Channel* reproChannel = AL().GetChannel(soundName);
    if (reproChannel == nullptr) {
        for (int i = 0; i < AL().GetChannelsVector().size(); i++) {
            bool IsPlaying;
            AL().GetChannelsVector()[i]->isPlaying(&IsPlaying);

            if (IsPlaying) continue;
            this->result = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &AL().GetChannelsVector()[i]);
            AL().CheckFMODResult(this->result);

            reproChannel = AL().GetChannelsVector()[i];

            AL().GetChannelsVector()[i]->setVolume(channelVolume);

           AL().GetLastPlayedMap()[soundHandle] = i;

            break;
        }
    }
    else {
        this->result = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &reproChannel);
        AL().CheckFMODResult(this->result);
    }

    if (finalSoundMode & FMOD_3D) {
        FMOD_VECTOR v = AL().V3ToFmodV3(*channelVel), p = AL().V3ToFmodV3(*channelPos);
        reproChannel->set3DAttributes(&p, &v);
    }

    return true;
}

bool Audio_Source::StopSound(std::string soundName)
{
    AL().NameToLower(soundName);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(soundName);
    if (channel != nullptr) {
        this->result = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->result);
        channel->stop();
        return true;
    }
    else {
        return false;
    }
}

bool Audio_Source::PauseSound(std::string soundName, bool Pause)
{
    AL().NameToLower(soundName);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(soundName);
    if (channel != nullptr) {
        this->result = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->result);
        channel->setPaused(Pause);
        return true;
    }
    else {
        return false;
    }
}

void Audio_Source::Start()
{
    transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform");

    if (!transform) {
        ErrorInf().showErrorMessageBox("Audio_Source error", "An entity doesn't have transform component", EI_ERROR);
        //sceneManager().quit();
        return;
    }

    // Create a 3D sound or a normal sound
    if (is_three_d)
        Create3DSound(sound_path, sound_name, min_distance, max_distance, loop);
    else
        CreateNormalSound(sound_path, sound_name, loop);

    if (play_on_start)
        Play();
}

void Audio_Source::Update(const double& dt)
{
    if (is_three_d) {
        Set3DSoundAtributes(sound_name, this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetPosition(), this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetVelocity());
    }
}

void Audio_Source::Play()
{
    VeryReal::Vector3 pos = transform->GetPosition();
    VeryReal::Vector3 vel = transform->GetVelocity();
    PlayAudioSource(sound_name, sound_group, &pos, &vel, volume);
    //Hacer el wrapeado aqui

    playing = true;
}

void Audio_Source::Stop()
{
    StopSound(sound_name);
}

void Audio_Source::Pause()
{
    PauseSound(sound_name, true);
}

void Audio_Source::Resume()
{
    PauseSound(sound_name, false);
}

bool Audio_Source::IsPlaying()
{
    return playing;
}

bool Audio_Source::SetVolume(float value) {
    volume = value;
    AL().NameToLower(sound_name);
    FMOD::Channel* channel = AL().GetChannel(sound_name);
    if (channel != nullptr) {
        result = channel->setVolume(value);
        return AL().CheckFMODResult(result);
    }
    else {
        return false;
    }
}

bool Audio_Source::SetSpeed(float newSpeed) {
    speed = newSpeed;
    AL().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;

    this->result = soundHandle->setMusicSpeed(newSpeed);

    return AL().CheckFMODResult(this->result);
}

bool Audio_Source::SetMinMaxDistance(float minDistance, float maxDistance)
{
    min_distance = minDistance * DISTANCE_FACTOR;
    max_distance = maxDistance * DISTANCE_FACTOR;

    AL().NameToLower(sound_name);
    auto soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;
    soundHandle->set3DMinMaxDistance(min_distance, max_distance);
    return true;
}

bool Audio_Source::SetMode(FMOD_MODE newMode)
{
    AL().NameToLower(sound_name);
    FMOD::Sound* soundHandle = AL().GetSound(sound_name);
    if (soundHandle == nullptr) return false;
    FMOD_MODE soundMode;
    soundHandle->getMode(&soundMode);
    FMOD_MODE newSoundMode;
    newSoundMode = soundMode | newMode;
    result = soundHandle->setMode(newSoundMode);
    soundHandle->getMode(&soundMode);

#ifdef _DEBUG
    if (soundMode & FMOD_3D)
        std::cout << "3d" << " ";
    if (soundMode & FMOD_3D_LINEARROLLOFF)
        std::cout << "atenuacion" << " ";
    if (soundMode & FMOD_LOOP_NORMAL)
        std::cout << "loop" << " ";
#endif

    AL().CheckFMODResult(result);
}

void Audio_Source::SetSourcePath(std::string path) {
    sound_path = path;
}

void Audio_Source::SetSourceName(std::string name) {
    sound_name = name;
}

void Audio_Source::SetGroupChannelName(std::string name) {
    sound_group = name;
}

void Audio_Source::SetLoop(bool loop) {
    loop = loop;
}

void Audio_Source::SetIsThreeD(bool threeD) {
    is_three_d = threeD;
}

void Audio_Source::SetPlayOnStart(bool playOnStart) {
    play_on_start = playOnStart;
}

float Audio_Source::GetVolume() {
    return volume;
}
