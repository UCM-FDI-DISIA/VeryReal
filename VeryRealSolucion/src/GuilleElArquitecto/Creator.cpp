#include "Creator.h"
void VeryReal::Creator::AddCreator(creator_name c_name, CreatorComponent* cretorcomponent) {
	RemoveCreator(c_name);
	creators_map.insert({ c_name,cretorcomponent });
}
//Remueve el Componente de la Entidad en la que se encuentra
void VeryReal::Creator::RemoveCreator(creator_name c_name) {
	if (HasCreator(c_name)) {
		delete creators_map.at(c_name);
		creators_map.erase(c_name);
	}
}