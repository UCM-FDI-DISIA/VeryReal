#pragma once
#include <Singleton.h>
#include <Windows.h>		//por ahora lo dejo aqui
#include <string>
typedef void(__cdecl* MainLoop)(float dt);

namespace VeryReal {
class VeryRealProyecto : public VeryReal::Singleton<VeryRealProyecto> {
    friend Singleton<VeryRealProyecto>;

    public:
    static bool Init() {
        VeryRealProyecto* a = new VeryRealProyecto();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return true;
        }
        else {
            return false;
        }
    }
    std::pair<bool,std::string> InitVeryReal();
    void Loop();
    virtual void Delete();
    std::pair<bool,std::string> InitPointers();
    void CreateCreators();

    std::pair<bool,std::string> LoadGame(std::string gameName);


    private:
    HMODULE gameDll = NULL;
    MainLoop gameLoop = NULL;
    bool managerInitializeError = false;
};

inline VeryRealProyecto& VR() { return *VeryRealProyecto::Instance(); }
}
