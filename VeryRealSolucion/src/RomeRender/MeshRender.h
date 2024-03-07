#pragma once
#include "Component.h"

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

namespace  VeryReal {
	class TransformComponent;
	class Vector4;
	class Vector3;
    class MeshRender : public Component {
    public:
		
		MeshRender(bool isstatic, string modelname, string entityname, string matirialname, Ogre::SceneNode* node, Ogre::SceneManager* scenemanager, Ogre::FileSystemLayer* filesystemlayer_);
		virtual ~MeshRender();
		bool createMesh();
		void start();
		void update();
		void setName(std::string name);
		void setMeshName(std::string meshName);
		void setStatic(bool stat);
		void setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector3 rot); //cambia el transform en general
		void setPosition(VeryReal::Vector3 pos); //cambia la posicion del mesh
		void setScale(VeryReal::Vector3 scale); //escala la info del mesh ??
		void setRotation(VeryReal::Vector3 rot); //rota la info del mesh ???
		void activeMesh();
		void desactiveMesh();
		void setMaterial(std::string materialName); //asigna el nombre del material al objeto ejemplo.material como nombre (mirar)
		void changeMaterial(std::string t_materialName);
		void setRenderingDistance(float t_d);
		void setDebugVisibility(bool t_b);
		std::string getNameEntity();
		std::string getNameMesh();
		Ogre::Entity* getOgreEntity(); //devuelve la entidad de ogre asociada
		Ogre::AxisAlignedBox getBoundingBox(); 
		Ogre::SceneNode* getNode();
		void setCastShadows(bool t_shadow); //creo que crea las sombras solo, no lo tengo claro

    private:
		bool mStaticObject;
		std::string m_material_name;
		std::string m_entity_name;
		std::string m_mesh_name;

		//componenet transform of this.Entity
		VeryReal::TransformComponent* mTransform;
		Ogre::Entity* m_ent_ogre;
		Ogre::SceneManager* m_scene_mngr;
		Ogre::SceneNode* m_scene_node;
		Ogre::SceneManager* mSM;
		//VeryReal::Vector3 m_scale_diff;
		
    };


}
