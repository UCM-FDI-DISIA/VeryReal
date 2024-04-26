#pragma once
#include <Singleton.h>
#include <Windows.h>		//por ahora lo dejo aqui
#include <string>
typedef void(__cdecl* MainLoop)();

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
    bool InitVeryReal();
    void Loop();
    virtual void Delete();
    bool InitPointers();
    bool InitManagers();
    bool CreateCreators();

    bool LoadGame(std::string gameName);

    private:
    HMODULE gameDll = NULL;
    MainLoop gameLoop = NULL;
};

inline VeryRealProyecto& VR() { return *VeryRealProyecto::Instance(); }
}
