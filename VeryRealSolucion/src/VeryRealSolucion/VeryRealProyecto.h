#pragma once
#include <Singleton.h>

class VeryRealProyecto : public VeryReal::Singleton<VeryRealProyecto> {
	friend Singleton<VeryRealProyecto>;
public:
	bool Init();
	void Loop();
	virtual void Delete();
	void CreateCreators();
};

inline VeryRealProyecto& VR() {
	return *VeryRealProyecto::Instance();
}