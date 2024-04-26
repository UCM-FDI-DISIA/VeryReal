#include "AudioSourceComponent.h"
#include "CreatorAudioSourceComponent.h"
using namespace VeryReal;
using namespace std;

Component* VeryReal::CreatorAudioSourceComponent::CreatorSpecificComponent() { 
    return new AudioSourceComponent();
}

void VeryReal::CreatorAudioSourceComponent::SpecificInitComponent(Component* c) {
    string name, path, groupchannel;
    bool onstart = false, threed = false, loop = false;
    float volume = 0.1f, mindistance = 1.0f, maxdistance = 60.0f;

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
    static_cast<AudioSourceComponent*>(c)->InitComponent(name, path, onstart, groupchannel, volume, threed, loop, mindistance, maxdistance);
    static_cast<AudioSourceComponent*>(c)->Start();
}
