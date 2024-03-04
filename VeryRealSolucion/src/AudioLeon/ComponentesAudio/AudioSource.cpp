#include "AudioSource.h"
#include "Audio/SoundManager.h"
#include "EntityComponent/Transform.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"


me::Component* me::FactoryAudioSource::create(Parameters& params)
{
    AudioSource* audioSource = new AudioSource();

    audioSource->setSourceName(Value(params, "name", std::string()));
    //Hacer el wrapeado aqui
    audioSource->setSourcePath(Value(params, "path", std::string("fire.wav")));
    //Hacer el wrapeado aqui
    audioSource->setPlayOnStart(Value(params, "onstart", false));
    //Hacer el wrapeado aqui
    audioSource->setGroupChannelName(Value(params, "groupchannel", std::string("master")));
    //Hacer el wrapeado aqui
    audioSource->setVolume(Value(params, "volume", 1.0f));
    //Hacer el wrapeado aqui
    audioSource->setIsThreeD(Value(params, "threed", false));
    //Hacer el wrapeado aqui
    audioSource->setLoop(Value(params, "loop", false));
    //Hacer el wrapeado aqui
    audioSource->setMinDistance(Value(params, "mindistance", 1.0f));
    //Hacer el wrapeado aqui
    audioSource->setMaxDistance(Value(params, "maxdistance", 60.0f));
    //Hacer el wrapeado aqui

    return audioSource;
}

void me::FactoryAudioSource::destroy(Component* component)
{
    delete component;
}


me::AudioSource::AudioSource()
{
}

me::AudioSource::~AudioSource()
{
    soundManager().deleteSound(mSoundName);
}

void me::AudioSource::start()
{
    mTransform = mEntity->getComponent<Transform>("transform");

    if (!mTransform) {
        errorManager().throwMotorEngineError("AudioSource error", "An entity doesn't have transform component");
        sceneManager().quit();
        return;
    }

    // Create a 3D sound or a normal sound
    if (mIsThreeD)
        soundManager().create3DSound(mSoundPath, mSoundName, mMinDistance, mMaxDistance, mLoop);
    //Hacer el wrapeado aqui
    else
        soundManager().createNormalSound(mSoundPath, mSoundName, mLoop);
    //Hacer el wrapeado aqui

    if (mPlayOnStart)
        play();
}

void me::AudioSource::update(const double& dt)
{
    if (mIsThreeD) {
        soundManager().setSoundAtributes(mSoundName, mEntity->getComponent<me::Transform>("transform")->getPosition(), mEntity->getComponent<me::Transform>("transform")->getVelocity());
        //Hacer el wrapeado aqui
    }
}

void me::AudioSource::play()
{
    Vector3 pos = mTransform->getPosition();
    Vector3 vel = mTransform->getVelocity();
    soundManager().playSound(mSoundName, mSoundGroup, &pos, &vel, mVolume);
    //Hacer el wrapeado aqui

    mPlaying = true;
}

void me::AudioSource::stop()
{
    soundManager().stopSound(mSoundName);
    //Hacer el wrapeado aqui
}

void me::AudioSource::pause()
{
    soundManager().pauseSound(mSoundName, true);
    //Hacer el wrapeado aqui
}

void me::AudioSource::resume()
{
    soundManager().pauseSound(mSoundName, false);
}

bool me::AudioSource::isPlaying()
{
    return mPlaying;
}

void me::AudioSource::setVolume(float value) {
    mVolume = value;
}

void me::AudioSource::setSpeed(float value) {
    mSpeed = value;
}

void me::AudioSource::setMinDistance(float value) {
    mMinDistance = value * DISTANCE_FACTOR;
}

void me::AudioSource::setMaxDistance(float value) {
    mMaxDistance = value * DISTANCE_FACTOR;
}

void me::AudioSource::setSourcePath(std::string path) {
    mSoundPath = path;
}

void me::AudioSource::setSourceName(std::string name) {
    mSoundName = name;
}

void me::AudioSource::setGroupChannelName(std::string name) {
    mSoundGroup = name;
}

void me::AudioSource::setLoop(bool loop) {
    mLoop = loop;
}

void me::AudioSource::setIsThreeD(bool threeD) {
    mIsThreeD = threeD;
}

void me::AudioSource::setPlayOnStart(bool playOnStart) {
    mPlayOnStart = playOnStart;
}

float me::AudioSource::getVolume() {
    return mVolume;
}
