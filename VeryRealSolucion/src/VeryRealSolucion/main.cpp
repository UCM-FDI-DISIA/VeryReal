#include <checkML.h>
#include "VeryRealProyecto.h"
int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	VR().Instance();
	if (!VR().Init()) {
		VR().Delete();
		return 0;
	}

	VR().Loop();
	VR().Delete();

	return 1;
}