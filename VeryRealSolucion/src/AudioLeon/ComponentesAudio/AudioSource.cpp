#include "AudioSource.h"
#include <AudioLeon.h>
#include <TransformComponent.h>
#include <Entity.h>
#include <ErrorInformant.h>
#include <SceneManager.h>

//Component* FactoryAudioSource::create(Parameters& params)
//{
//    AudioSource* audioSource = new AudioSource();
//
//    audioSource->setSourceName(Value(params, "name", std::string()));
//    //Hacer el wrapeado aqui
//    audioSource->setSourcePath(Value(params, "path", std::string("fire.wav")));
//    //Hacer el wrapeado aqui
//    audioSource->setPlayOnStart(Value(params, "onstart", false));
//    //Hacer el wrapeado aqui
//    audioSource->setGroupChannelName(Value(params, "groupchannel", std::string("master")));
//    //Hacer el wrapeado aqui
//    audioSource->setVolume(Value(params, "volume", 1.0f));
//    //Hacer el wrapeado aqui
//    audioSource->setIsThreeD(Value(params, "threed", false));
//    //Hacer el wrapeado aqui
//    audioSource->setLoop(Value(params, "loop", false));
//    //Hacer el wrapeado aqui
//    audioSource->setMinDistance(Value(params, "mindistance", 1.0f));
//    //Hacer el wrapeado aqui
//    audioSource->setMaxDistance(Value(params, "maxdistance", 60.0f));
//    //Hacer el wrapeado aqui
//
//    return audioSource;
//}
//
//void FactoryAudioSource::destroy(Component* component)
//{
//    delete component;
//}


AudioSource::AudioSource()
{

}

AudioSource::~AudioSource()
{
    AL().deleteSound(mSoundName);
}

bool AudioSource::create3DSound(std::string soundPath, std::string soundName, float minDistance, float maxDistance, bool loop)
{
    soundPath = "Assets/Sounds/" + soundPath;
    AL().NameToLower(soundName);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(soundName);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->mResult = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->mResult = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_3D_LINEARROLLOFF | FMOD_3D, 0, &newSoundHandle);
    }

    if (!AL().CheckFMODResult(this->mResult)) return false;

    this->mResult = newSoundHandle->set3DMinMaxDistance(minDistance, maxDistance);
    if (!AL().CheckFMODResult(this->mResult)) return false;

    if (AL().CheckFMODResult(this->mResult)) {
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

bool AudioSource::createNormalSound(std::string soundPath, std::string soundName, bool loop)
{
    soundPath = "Assets/Sounds/" + soundPath;
    AL().NameToLower(soundName);
    FMOD::Sound* newSoundHandle;
    auto soundHandle = AL().GetSound(soundName);
    if (soundHandle != nullptr) return false;

    if (loop) {
        this->mResult = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &newSoundHandle);
    }
    else {
        this->mResult = AL().GetSoundSystem()->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &newSoundHandle);
    }

    if (AL().CheckFMODResult(this->mResult)) {
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

bool AudioSource::setSoundAtributes(std::string soundName, VeryReal::Vector3 position, VeryReal::Vector3 velocity)
{
    AL().NameToLower(soundName);
    FMOD::Channel* channelHandle = AL().GetChannel(soundName);
    if (channelHandle == nullptr) return false;
    FMOD_VECTOR p = AL().V3ToFmodV3(position), v = AL().V3ToFmodV3(velocity);

    channelHandle->set3DAttributes(&p, &v);
    return true;
}

bool AudioSource::PlayAudioSource(std::string soundName, std::string channelGroup, VeryReal::Vector3* channelPos, VeryReal::Vector3* channelVel, float channelVolume)
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
            bool isPlaying;
            AL().GetChannelsVector()[i]->isPlaying(&isPlaying);

            if (isPlaying) continue;
            this->mResult = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &AL().GetChannelsVector()[i]);
            AL().CheckFMODResult(this->mResult);

            reproChannel = AL().GetChannelsVector()[i];

            AL().GetChannelsVector()[i]->setVolume(channelVolume);

           AL().GetLastPlayedMap()[soundHandle] = i;

            break;
        }
    }
    else {
        this->mResult = AL().GetSoundSystem()->playSound(soundHandle, playedChannelGroup, false, &reproChannel);
        AL().CheckFMODResult(this->mResult);
    }

    if (finalSoundMode & FMOD_3D) {
        FMOD_VECTOR v = AL().V3ToFmodV3(*channelVel), p = AL().V3ToFmodV3(*channelPos);
        reproChannel->set3DAttributes(&p, &v);
    }

    return true;
}

bool AudioSource::StopSound(std::string soundName)
{
    AL().NameToLower(soundName);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(soundName);
    if (channel != nullptr) {
        this->mResult = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->mResult);
        channel->stop();
        return true;
    }
    else {
        return false;
    }
}

bool AudioSource::PauseSound(std::string soundName, bool pause)
{
    AL().NameToLower(soundName);
    bool isPaused;
    FMOD::Channel* channel = AL().GetChannel(soundName);
    if (channel != nullptr) {
        this->mResult = channel->getPaused(&isPaused);
        AL().CheckFMODResult(this->mResult);
        channel->setPaused(pause);
        return true;
    }
    else {
        return false;
    }
}

void AudioSource::Start()
{
    mTransform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform");

    if (!mTransform) {
        ErrorInf().showErrorMessageBox("AudioSource error", "An entity doesn't have transform component", EI_ERROR);
        //sceneManager().quit();
        return;
    }

    // Create a 3D sound or a normal sound
    if (mIsThreeD)
        create3DSound(mSoundPath, mSoundName, mMinDistance, mMaxDistance, mLoop);
    else
        createNormalSound(mSoundPath, mSoundName, mLoop);

    if (mPlayOnStart)
        play();
}

void AudioSource::Update(const double& dt)
{
    if (mIsThreeD) {
        setSoundAtributes(mSoundName, this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetPosition(), this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetVelocity());
    }
}

void AudioSource::play()
{
    VeryReal::Vector3 pos = mTransform->GetPosition();
    VeryReal::Vector3 vel = mTransform->GetVelocity();
    PlayAudioSource(mSoundName, mSoundGroup, &pos, &vel, mVolume);
    //Hacer el wrapeado aqui

    mPlaying = true;
}

void AudioSource::stop()
{
    StopSound(mSoundName);
    //Hacer el wrapeado aqui
}

void AudioSource::pause()
{
    PauseSound(mSoundName, true);
    //Hacer el wrapeado aqui
}

void AudioSource::resume()
{
    PauseSound(mSoundName, false);
}

bool AudioSource::isPlaying()
{
    return mPlaying;
}

void AudioSource::setVolume(float value) {
    mVolume = value;
}

bool AudioSource::setSpeed(float newSpeed) {
    mSpeed = newSpeed;
    AL().NameToLower(mSoundName);
    FMOD::Sound* soundHandle = AL().GetSound(mSoundName);
    if (soundHandle == nullptr) return false;

    this->mResult = soundHandle->setMusicSpeed(newSpeed);

    return AL().CheckFMODResult(this->mResult);
}

void AudioSource::setMinDistance(float value) {
    mMinDistance = value * DISTANCE_FACTOR;
}

void AudioSource::setMaxDistance(float value) {
    mMaxDistance = value * DISTANCE_FACTOR;
}

void AudioSource::setSourcePath(std::string path) {
    mSoundPath = path;
}

void AudioSource::setSourceName(std::string name) {
    mSoundName = name;
}

void AudioSource::setGroupChannelName(std::string name) {
    mSoundGroup = name;
}

void AudioSource::setLoop(bool loop) {
    mLoop = loop;
}

void AudioSource::setIsThreeD(bool threeD) {
    mIsThreeD = threeD;
}

void AudioSource::setPlayOnStart(bool playOnStart) {
    mPlayOnStart = playOnStart;
}

float AudioSource::getVolume() {
    return mVolume;
}
