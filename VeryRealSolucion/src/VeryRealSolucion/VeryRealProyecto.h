#pragma once
#include <Singleton.h>

class VeryRealEngine : public VeryReal::Singleton<VeryRealEngine> {
	friend Singleton<VeryRealEngine>;
public:
	bool Init();
	void Loop();
	virtual void Delete();
};

inline VeryRealEngine& VR() {
	return *VeryRealEngine::Instance();
}