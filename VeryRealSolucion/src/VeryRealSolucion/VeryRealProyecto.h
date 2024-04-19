#pragma once
#include <Singleton.h>
#include <Windows.h>		//por ahora lo dejo aqui
#include <string>

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
};

inline VeryRealProyecto& VR() { return *VeryRealProyecto::Instance(); }
}
