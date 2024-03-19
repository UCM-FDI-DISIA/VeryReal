#pragma once
#include <Singleton.h>
#include <Windows.h>		//por ahora lo dejo aqui
#include <string>

class VeryRealProyecto : public VeryReal::Singleton<VeryRealProyecto> {
	friend Singleton<VeryRealProyecto>;
public:
	bool Init();
	void Loop();
	virtual void Delete();
	void CreateCreators();

	bool LoadGame(std::string gameName);
private:
	HMODULE gameDll;
};

inline VeryRealProyecto& VR() {
	return *VeryRealProyecto::Instance();
}