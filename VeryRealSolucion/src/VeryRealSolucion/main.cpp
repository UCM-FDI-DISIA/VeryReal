#pragma once
#include "VeryRealProyecto.h"
#include <cerrno>
#include <iostream>
#include "ErrorInformant.h"

int main(int argc, char* argv[]) {
    if (VeryReal::VeryRealProyecto::Init()) {
        auto veryRealInit = VeryReal::VR().InitVeryReal();
        if (!veryRealInit.first) {
            VeryReal::ErrorInformant().Instance()->showErrorMessageBox("Error", veryRealInit.second, VeryReal::EI_ERROR, VeryReal::EI_W_OK);
           /* std::cout << veryRealInit.second << std::endl;*/
            VeryReal::VR().Delete();
            return 0;
        }
        VeryReal::VR().Loop();
        VeryReal::VR().Delete();
	}
	return 1;
}