#pragma once
#include "VeryRealProyecto.h"
#include <cerrno>
#include <iostream>

int main(int argc, char* argv[]) {
    if (VeryReal::VeryRealProyecto::Init()) {
        auto veryRealInit = VeryReal::VR().InitVeryReal();
        if (!veryRealInit.first) {
            std::cout << veryRealInit.second << std::endl;
            VeryReal::VR().Delete();
            return 0;
        }
        VeryReal::VR().Loop();
        VeryReal::VR().Delete();
	}
	return 1;
}