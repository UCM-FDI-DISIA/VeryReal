#pragma once
#ifndef ENTITY
#define ENTITY
#include "Creator.h"
#include "Component.h"


#pragma warning(disable : 4251)

namespace VeryReal {
	using component_name = std::string;
	
	class VERYREAL_GUILLEELARQUITECTO Entity {
	private:
		//Mapa de Componentes: clave: nombre, valor:puntero a ese Componente
		std::unordered_map<component_name, Component*> components_map;

		//lista de componentes a remover, porque no están activos
		std::list<component_name> components_list_removed;

		bool is_alive;
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();


		//Añade componente a la Entidad
		inline Component* AddComponent(component_name c_name, int ord) {
			//si quieres añadir de nuevo un componente ya existente, lo sobrescribe
			RemoveComponent(c_name);
            Component* component;
           
            component= Creator::Instance()->CallSpecificCreator(c_name);
            component->SetOrden(ord);
            component->SetEntity(this);
            Creator::Instance()->CallSpecificInit(c_name, component);
			components_map.insert({ c_name,component});
			//quizas initcomponentpai
			return component;
		}

		//Añade componente a la Entidad
        inline Component* AddComponentByCopy(component_name c_name, Component* other) {
            //si quieres añadir de nuevo un componente ya existente, lo sobrescribe
            RemoveComponent(c_name);

            Component* component;
            component = Creator::Instance()->CallSpecificCreator(c_name);
            component->SetOrden(other->GetOrden());
            component->SetEntity(this);
            Creator::Instance()->CallSpecificInitByCopy(c_name, component, other);

            components_map.insert({c_name, component});
            return component;
        }

		//Remueve el Componente de la Entidad en la que se encuentra
		void RemoveComponent(component_name c_name);

		//Indica si la entidad tiene este componente
		inline bool HasComponent(component_name c_name) {
			return components_map.count(c_name);
		}

		//Devuelve el componente especifico y si no esta devuelve nullptr
		template<typename T>
		inline T* GetComponent() {
            component_name n;
            std::string fullName = typeid(T).name();

            // Esto busca la ultima aparicion de ':' para obtener solo el nombre de la clase
            size_t pos = fullName.find_last_of(':');
            if (pos != std::string::npos && pos + 1 < fullName.length()) {
                n = fullName.substr(pos + 1);
            }
            else {
                n = fullName;
            }
			if (!HasComponent(n)) {
				return nullptr;
			}
			return static_cast<T*>(components_map.at(n));
		}

		//Indican si la entidad está activa o no
		inline void SetActive(bool active) { is_alive = active; }
		inline bool GetActive() { return is_alive; }

		/*
			Recorremos de primeras con un for el mapa:
				-->Comprobamos si el componente está activo-->hacemos su Update
				-->Si no está activo, lo añadimos a una lista de componentes no activos
				(Hecho de esta forma para evitar llamadas a null, a componentes ya removidos, en el propio Update)

			Posteriormente, recorremos la lista de componentes a eliminar
				-->Removemos el componente del mapa
				-->Removemos el componente de la lista

			Elimina de manera segura los componentes
		*/
		void Update(const double& dt);
		void Refresh();



		void OnCollisionEnter(Entity* other);
		void OnCollisionExit(Entity* other);
		void OnCollisionStay(Entity* other);
	};
}

#pragma warning(default : 4251)

#endif