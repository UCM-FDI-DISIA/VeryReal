#ifndef ERRORINFORMANT
#define ERRORINFORMANT
#pragma once

#include "Singleton.h"
#include <Windows.h>
#include <string>

using namespace std;

enum errorType { 
	EI_WARNING = MB_ICONWARNING, 
	EI_ERROR = MB_ICONERROR, 
	EI_UNKNOWN = MB_ICONQUESTION
};

enum windowType{ 
	EI_W_OK = MB_OK, 
	EI_W_CANCEL = MB_OKCANCEL, 
	EI_W_RETRY = MB_RETRYCANCEL
};

enum options { 
	EI_OK = IDOK, 
	EI_CANCEL = IDCANCEL, 
	EI_ABORT = IDABORT, 
	EI_RETY = IDRETRY, 
	EI_IGNORE = IDIGNORE,
	EI_YES = IDYES,
	EI_NO = IDNO,
	EI_CLOSE = IDCLOSE,
	EI_HELP = IDHELP,
	EI_TRYACAIN = IDTRYAGAIN,
	EI_CONTINUE = IDCONTINUE,
	EI_TIMEOUT = IDTIMEOUT
};



class ErrorInformant : public VeryReal::Singleton<ErrorInformant> {
	friend Singleton<ErrorInformant>;

	public:
		/// Lanza una ventana de error informando al usuario de que algo no ha salido como se esperaba
		/// @param ErrorName -> Nombre del error
		/// @param ErrorMessage -> Descripcion del error ocurrido
		/// @param ErrorType -> Tipo del error (EI_WARNING, EI_ERROR o EI_UNKNOWN)
		options showErrorMessageBox(string ErrorName = "Unknown error", string ErrorMessage = "Description not avaliable", errorType ErrorType = EI_UNKNOWN, windowType = EI_W_OK);

private:
	ErrorInformant() {};
};

/// Singleton instance
/// @return A pointer of the instance
inline ErrorInformant& ErrorInf() {
	return *ErrorInformant::Instance();
}
#endif