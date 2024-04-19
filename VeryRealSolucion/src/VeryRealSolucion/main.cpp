#pragma once
#include <checkML.h>
#include "VeryRealProyecto.h"
int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (VeryReal::VeryRealProyecto::Init()) {
        if (!VeryReal::VR().InitVeryReal()) {
            VeryReal::VR().Delete();
            return 0;
        }
        VeryReal::VR().Loop();
        VeryReal::VR().Delete();
       
	}

	

	return 1;
}