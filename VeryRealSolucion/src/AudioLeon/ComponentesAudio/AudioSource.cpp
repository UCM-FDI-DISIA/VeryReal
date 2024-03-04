#include "AudioSource.h"
#include "AudioLeon.h"
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
        AL().create3DSound(mSoundPath, mSoundName, mMinDistance, mMaxDistance, mLoop);
    //Hacer el wrapeado aqui
    else
        AL().createNormalSound(mSoundPath, mSoundName, mLoop);
    //Hacer el wrapeado aqui

    if (mPlayOnStart)
        play();
}

void AudioSource::Update(const double& dt)
{
    if (mIsThreeD) {
        AL().setSoundAtributes(mSoundName, this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetPosition(), this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform")->GetVelocity());
        //Hacer el wrapeado aqui
    }
}

void AudioSource::play()
{
    VeryReal::Vector3 pos = mTransform->GetPosition();
    VeryReal::Vector3 vel = mTransform->GetVelocity();
    AL().playSound(mSoundName, mSoundGroup, &pos, &vel, mVolume);
    //Hacer el wrapeado aqui

    mPlaying = true;
}

void AudioSource::stop()
{
    AL().stopSound(mSoundName);
    //Hacer el wrapeado aqui
}

void AudioSource::pause()
{
    AL().pauseSound(mSoundName, true);
    //Hacer el wrapeado aqui
}

void AudioSource::resume()
{
    AL().pauseSound(mSoundName, false);
}

bool AudioSource::isPlaying()
{
    return mPlaying;
}

void AudioSource::setVolume(float value) {
    mVolume = value;
}

void AudioSource::setSpeed(float value) {
    mSpeed = value;
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
