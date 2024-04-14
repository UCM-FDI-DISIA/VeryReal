#include "Creator.h"
VeryReal::Creator::~Creator() {
	for (auto& c : creators_map)delete c.second;
	creators_map.clear();
}
void VeryReal::Creator::AddCreator(const creator_name& c_name, CreatorComponent* cretorcomponent) {
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
// bool VeryReal::Creator::Init() {
//        //VeryReal::Creator* creator = new VeryReal::Creator();
//        //if (creator != nullptr) {
//        //        //InitPointer(creator);
//        //        delete creator;   // Liberar la memoria inmediatamente si la construcción fue exitosa
//        //        return true;
//        //}
//        return false;   // Si el constructor devuelve nullptr, la construcción falló
//}