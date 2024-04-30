#pragma once
#ifndef MESHRENDERCOMPONENT
#define MESHRENDERCOMPONENT
#include "Component.h"
#include <string>
#include "Vector3.h"
#include "exportRomeRender.h"
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

    class  MeshRenderComponent : public Component {
    public:
		// Constructor por defecto temporal sin parámetros, se espera que los creadores lo inicialicen correctamente.
		VERYREAL_ROMERENDER MeshRenderComponent(){};

		// Inicializa el componente de renderizado de malla con la información proporcionada.
		VERYREAL_ROMERENDER bool InitComponent(bool isstatic, std::string modelname, std::string entityname, std::string matirialname);

		// Destructor de la clase MeshRenderComponent.
		VERYREAL_ROMERENDER virtual ~MeshRenderComponent();

		// Crea la malla para el componente de renderizado.
		VERYREAL_ROMERENDER bool createMesh();

		// Actualiza el componente de renderizado de malla.
		VERYREAL_ROMERENDER virtual void Update(const double& dt);

		// Establece el nombre del componente.
		VERYREAL_ROMERENDER void setName(std::string name);

		// Establece el nombre de la malla del componente.
		VERYREAL_ROMERENDER void setMeshName(std::string meshName);

		// Establece si el componente es estático o no.
		VERYREAL_ROMERENDER void setStatic(bool stat);

		// Establece la transformación del componente (posición, escala y rotación).
		VERYREAL_ROMERENDER void setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector3 rot);

		// Establece la posición del componente.
		VERYREAL_ROMERENDER void setPosition(VeryReal::Vector3 const& pos);

		// Escala la malla del componente.
		VERYREAL_ROMERENDER void setScale(VeryReal::Vector3 const& scale);

		// Rota la malla del componente.
		VERYREAL_ROMERENDER void setRotation(VeryReal::Vector3 const& rot);

		// Activa la malla del componente.
		VERYREAL_ROMERENDER void activeMesh();

		// Desactiva la malla del componente.
		VERYREAL_ROMERENDER void desactiveMesh();

		// Establece el nombre del material para la malla del componente.
		VERYREAL_ROMERENDER void setMaterial(std::string materialName);

		// Cambia el material de la malla del componente.
		VERYREAL_ROMERENDER void changeMaterial(std::string t_materialName);

		// Establece la distancia de renderizado del componente.
		VERYREAL_ROMERENDER void setRenderingDistance(float t_d);

		// Establece la visibilidad del modo de depuración del componente.
		VERYREAL_ROMERENDER void setDebugVisibility(bool t_b);

		// Obtiene el nombre de la entidad asociada al componente.
		VERYREAL_ROMERENDER std::string getNameEntity();

		// Obtiene el nombre de la malla asociada al componente.
		VERYREAL_ROMERENDER std::string getNameMesh();

		// Obtiene la entidad de Ogre asociada al componente.
		Ogre::Entity* getOgreEntity();

		// Obtiene el cuadro delimitador (bounding box) del componente.
		Ogre::AxisAlignedBox getBoundingBox();

		// Obtiene el nodo de escena asociado al componente.
		Ogre::SceneNode* getNode();

		// Establece si el componente debe arrojar sombras o no.
	   VERYREAL_ROMERENDER void setCastShadows(bool t_shadow);

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
        VeryReal::Vector3 rotation;
    };
}

#pragma warning(default : 4251)

#endif !MESHRENDERCOMPONENT