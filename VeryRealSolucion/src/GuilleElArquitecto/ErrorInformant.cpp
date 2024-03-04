#include "ErrorInformant.h"

options ErrorInformant::showErrorMessageBox(string ErrorName, string ErrorMessage, errorType ErrorType, windowType WindowType) {
	wstring wName = wstring(ErrorName.begin(), ErrorName.end());
	wstring wMessage = wstring(ErrorMessage.begin(), ErrorMessage.end());

	return (options)MessageBox(NULL, wMessage.c_str(), wName.c_str(), ErrorType | WindowType); // MB_ABORTRETRYIGNORE
}