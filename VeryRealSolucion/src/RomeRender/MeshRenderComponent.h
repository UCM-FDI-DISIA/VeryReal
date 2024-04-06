#pragma once
#ifndef MESHRENDERCOMPONENT
#define MESHRENDERCOMPONENT
#include "Component.h"
#include <string>

namespace Ogre
{
	class AxisAlignedBox;
	class OgreEntity;
	class Entity;
	class SceneNode;
	class Entity;
	class SceneManager;
	class SceneNode;
	class Node;
	class FileSystemLayer;

}

#pragma warning(disable : 4251)

namespace  VeryReal {
	class TransformComponent;
	class Vector4;
	class Vector3;
	class conversor;

    class VERYREAL_API MeshRenderComponent : public Component {
    public:
		// Constructor por defecto temporal sin parámetros, se espera que los creadores lo inicialicen correctamente.
		MeshRenderComponent(){};

		// Inicializa el componente de renderizado de malla con la información proporcionada.
		bool InitComponent(bool isstatic, std::string modelname, std::string entityname, std::string matirialname);

		// Destructor de la clase MeshRenderComponent.
		virtual ~MeshRenderComponent();

		// Crea la malla para el componente de renderizado.
		bool createMesh();

		// Actualiza el componente de renderizado de malla.
		void update();

		// Establece el nombre del componente.
		void setName(std::string name);

		// Establece el nombre de la malla del componente.
		void setMeshName(std::string meshName);

		// Establece si el componente es estático o no.
		void setStatic(bool stat);

		// Establece la transformación del componente (posición, escala y rotación).
		void setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector3 rot);

		// Establece la posición del componente.
		void setPosition(VeryReal::Vector3 const&  pos);

		// Escala la malla del componente.
		void setScale(VeryReal::Vector3 const&  scale);

		// Rota la malla del componente.
		void setRotation(VeryReal::Vector3 const& rot);

		// Activa la malla del componente.
		void activeMesh();

		// Desactiva la malla del componente.
		void desactiveMesh();

		// Establece el nombre del material para la malla del componente.
		void setMaterial(std::string materialName);

		// Cambia el material de la malla del componente.
		void changeMaterial(std::string t_materialName);

		// Establece la distancia de renderizado del componente.
		void setRenderingDistance(float t_d);

		// Establece la visibilidad del modo de depuración del componente.
		void setDebugVisibility(bool t_b);

		// Obtiene el nombre de la entidad asociada al componente.
		std::string getNameEntity();

		// Obtiene el nombre de la malla asociada al componente.
		std::string getNameMesh();

		// Obtiene la entidad de Ogre asociada al componente.
		Ogre::Entity* getOgreEntity();

		// Obtiene el cuadro delimitador (bounding box) del componente.
		Ogre::AxisAlignedBox getBoundingBox();

		// Obtiene el nodo de escena asociado al componente.
		Ogre::SceneNode* getNode();

		// Establece si el componente debe arrojar sombras o no.
		void setCastShadows(bool t_shadow);

    private:
		bool mStaticObject = false;
		std::string material_name = "";
        std::string entity_name = "";
        std::string mesh_name = "";

		VeryReal::TransformComponent* transform = nullptr;
        Ogre::Entity* ent_ogre = nullptr;
        Ogre::SceneManager* scene_mngr = nullptr;
        Ogre::SceneNode* scene_node = nullptr;
        Ogre::SceneManager* mSM = nullptr;
    };
}

#pragma warning(default : 4251)

#endif !MESHRENDERCOMPONENT