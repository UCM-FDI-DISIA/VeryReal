#pragma once
#ifndef CREATOR
#define CREATOR
#include "Singleton.h"
#include "CreatorComponent.h"
#include <unordered_map>
#include <string>
#include "export.h"

#pragma warning(disable : 4251)

namespace VeryReal {
using creator_name = std::string;
using prefab_name = std::string;
class Entity;

class VERYREAL_GUILLEELARQUITECTO Creator : public VeryReal::Singleton<Creator> {
    friend Singleton<Creator>;

private:
    std::unordered_map<creator_name, CreatorComponent*> creators_map;
    std::unordered_map<prefab_name, Entity*> prefabs_map;
    Creator(){};

 public:
    static std::pair<bool,std::string> Init() {
     Creator* a = new Creator();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return {true, "Creator pointer sucesfully initialized"};
        }
        return {false, "Creator pointer had a problem while it was initializing"};
    }
  
    virtual ~Creator();

    //llamada a la constructora de cada creator (deben estar vacias)
    inline Component* CallSpecificCreator(creator_name c_name) { return creators_map [c_name]->CreatorSpecificComponent(); }

    inline std::pair<bool, std::string> CallSpecificInit(creator_name c_name, Component* c) { return creators_map [c_name]->SpecificInitComponent(c); }

    inline std::pair<bool, std::string> CallSpecificInitByCopy(creator_name c_name, Component* c, Component* other) {
        return creators_map [c_name]->SpecificInitComponentByCopy(c, other);
    }

    void AddCreator(const creator_name& c_name, CreatorComponent* cretorcomponent);

    //Remueve el Creador del mapa de creadores
    void RemoveCreator(creator_name c_name);

    //Indica si el creador existe
    inline bool HasCreator(creator_name c_name) { return creators_map.count(c_name); }

    //Devuelve el creator especifico y si no esta devuelve nullptr
    inline CreatorComponent* GetCreator(creator_name c_name) {
        if (!HasCreator(c_name)) {
            return nullptr;
        }
        return creators_map.at(c_name);
    }

    // A�ade un prefab a el mapa de prefbas
    void AddPrefab(prefab_name p_name, Entity* ent);
    //elimina un prefab del mapa de prefabs
    void RemovePrefab(prefab_name p_name);

    //Indica si el prefab existe
    bool HasPrefab(prefab_name p_name);

    //Devuelve el prefab especifico y si no esta devuelve nullptr
    Entity* GetPrefab(prefab_name p_name);

   
};
}

#pragma warning(default : 4251)

#endif