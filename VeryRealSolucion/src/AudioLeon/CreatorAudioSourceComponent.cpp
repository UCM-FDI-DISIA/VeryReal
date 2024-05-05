#include "AudioSourceComponent.h"
#include "CreatorAudioSourceComponent.h"
using namespace VeryReal;
using namespace std;

Component* VeryReal::CreatorAudioSourceComponent::CreatorSpecificComponent() { return new AudioSourceComponent(); }

void VeryReal::CreatorAudioSourceComponent::SpecificInitComponent(Component* c) {
    string name, path, groupchannel;
    bool onstart = false, threed = false, loop = false;
    float volume = 0.1f, mindistance = 1.0f, maxdistance = 60.0f;
#pragma region Name

    if (parameters_map.find("name") != parameters_map.end()) {
        if (std::holds_alternative<string>(parameters_map.at("name")->GetVariant())) {
            name = std::get<string>(parameters_map.at("name")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para name este sera seteado por defecto" << std::endl;
            name = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro name este sera seteado por defecto" << std::endl;
        name = " ";
    }
#pragma endregion
#pragma region Path

    if (parameters_map.find("path") != parameters_map.end()) {
        if (std::holds_alternative<string>(parameters_map.at("path")->GetVariant())) {
            path = std::get<string>(parameters_map.at("path")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para path este sera seteado por defecto" << std::endl;
            path = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro path este sera seteado por defecto" << std::endl;
        name = " ";
    }
#pragma endregion
#pragma region GroupChannel

    if (parameters_map.find("groupchannel") != parameters_map.end()) {
        if (std::holds_alternative<string>(parameters_map.at("groupchannel")->GetVariant())) {
            groupchannel = std::get<string>(parameters_map.at("groupchannel")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para groupchannel este sera seteado por defecto" << std::endl;
            groupchannel = "effects";
        }
    }
    else {
        std::cout << "No existe ningun parametro groupchannel este sera seteado por defecto" << std::endl;
        groupchannel = "effects";
    }
#pragma endregion
#pragma region OnStart

    if (parameters_map.find("onstart") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("onstart")->GetVariant())) {
            onstart = std::get<bool>(parameters_map.at("onstart")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para onstart este sera seteado por defecto" << std::endl;
            onstart = true;
        }
    }
    else {
        std::cout << "No existe ningun parametro groupchannel este sera seteado por defecto" << std::endl;
        onstart = true;
    }
#pragma endregion
#pragma region Loop

    if (parameters_map.find("loop") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("loop")->GetVariant())) {
            loop = std::get<bool>(parameters_map.at("loop")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para loop este sera seteado por defecto" << std::endl;
            loop = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro loop este sera seteado por defecto" << std::endl;
        loop = false;
    }
#pragma endregion
#pragma region Threed

    if (parameters_map.find("threed") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("threed")->GetVariant())) {
            threed = std::get<bool>(parameters_map.at("threed")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para threed este sera seteado por defecto" << std::endl;
            threed = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro threed este sera seteado por defecto" << std::endl;
        threed = false;
    }
#pragma endregion
#pragma region Volume

    if (parameters_map.find("volume") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("volume")->GetVariant())) {
            volume = std::get<float>(parameters_map.at("volume")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para volume este sera seteado por defecto" << std::endl;
            volume = 1.0f;
        }
    }
    else {
        std::cout << "No existe ningun parametro volume este sera seteado por defecto" << std::endl;
        volume = 1.0f;
    }
#pragma endregion
#pragma region MinDistance

    if (parameters_map.find("mindistance") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("mindistance")->GetVariant())) {
            mindistance = std::get<float>(parameters_map.at("mindistance")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para mindistance este sera seteado por defecto" << std::endl;
            mindistance = 1.0f;
        }
    }
    else {
        std::cout << "No existe ningun parametro mindistance este sera seteado por defecto" << std::endl;
        mindistance = 1.0f;
    }
#pragma endregion
#pragma region MaxDistance

    if (parameters_map.find("maxdistance") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("maxdistance")->GetVariant())) {
            maxdistance = std::get<float>(parameters_map.at("maxdistance")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para maxdistance este sera seteado por defecto" << std::endl;
            maxdistance = 1.0f;
        }
    }
    else {
        std::cout << "No existe ningun parametro maxdistance este sera seteado por defecto" << std::endl;
        maxdistance = 1.0f;
    }
#pragma endregion
    static_cast<AudioSourceComponent*>(c)->InitComponent(name, path, onstart, groupchannel, volume, threed, loop, mindistance, maxdistance);
    static_cast<AudioSourceComponent*>(c)->Start();
}

void VeryReal::CreatorAudioSourceComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    string name, path, groupchannel;
    bool onstart = false, threed = false, loop = false;
    float volume = 0.1f, mindistance = 1.0f, maxdistance = 60.0f;
    AudioSourceComponent* audio = static_cast<AudioSourceComponent*>(c);
    AudioSourceComponent* copia = static_cast<AudioSourceComponent*>(other);
    audio->InitComponent(copia->GetSoundName(), copia->GetSoundPath(), copia->GetPlayOnStart(), copia->GetSoundGroup(), copia->GetVolume(),
                         copia->GetIsThreeD(), copia->GetIsLoop(), copia->GetMinDistance(), copia->GetMaxDistance());
    audio->Start();
}
