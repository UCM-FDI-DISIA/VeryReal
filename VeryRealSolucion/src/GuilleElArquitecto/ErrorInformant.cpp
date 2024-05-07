#include "ErrorInformant.h"


VeryReal::options VeryReal::ErrorInformant::showErrorMessageBox(std::string ErrorName, std::string ErrorMessage, errorType ErrorType, windowType WindowType) {
	
	std::string wName = std::string(ErrorName.begin(), ErrorName.end());
	std::string wMessage = std::string(ErrorMessage.begin(), ErrorMessage.end());

	return (options)MessageBox(NULL, wMessage.c_str(), wName.c_str(), ErrorType | WindowType); // MB_ABORTRETRYIGNORE
      //  return (options)MessageBox(NULL, NULL, NULL,NULL);
}
VeryReal::ErrorInformant::~ErrorInformant() { }