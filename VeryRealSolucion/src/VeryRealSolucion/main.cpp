#pragma once
#include "VeryRealProyecto.h"
#include <cerrno>
#include <iostream>
#include "ErrorInformant.h"
#include "ErrorManager.h"

int main(int argc, char* argv []) {
    if (VeryReal::VeryRealProyecto::Init()) {
        auto veryRealInit = VeryReal::VR().InitVeryReal();
        //Error de carga inicial / motor
        if (!veryRealInit.first) {
            std::string p = veryRealInit.second;
            VeryReal::ErrorInformant::Instance()->showErrorMessageBox("ERROR Init Loading", p, VeryReal::EI_ERROR, VeryReal::EI_W_OK);
            VeryReal::VR().Delete();
            return 0;
        }
        VeryReal::VR().Loop();

        //Error de ejecucion en el bucle
        auto veryRealLoopEnded = VeryReal::ErrorManager::Instance()->getError();
        if (!veryRealLoopEnded.first) {
            std::string p = veryRealLoopEnded.second;
            VeryReal::ErrorInformant::Instance()->showErrorMessageBox("ERROR Loop Execution", p, VeryReal::EI_ERROR, VeryReal::EI_W_OK);
            VeryReal::VR().Delete();
            return 0;
        }
        std::cout << "Game ended sucesfully";
        VeryReal::VR().Delete();
    }
    delete VeryReal::VR().Instance();
    delete VeryReal::ErrorInformant::Instance();
    return 1;
}