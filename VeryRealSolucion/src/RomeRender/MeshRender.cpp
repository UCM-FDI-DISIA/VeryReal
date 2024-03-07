

#include "MeshRender.h"
#include <OgreAxisAlignedBox.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "Vector4.h"
#include "RenderManager.h"
#include "TransformComponent.h"
#include <Ogre.h>
#include "conversorvectores.h"
#include <OgreSceneNode.h>
#include <OgreNode.h>
#include <OgreFileSystemLayer.h>
#include "OgreVector3.h"
#include "Vector3.h"
using namespace VeryReal;
using namespace Ogre;

void MeshRender::InitComponent(bool isstatic, string modelname, string entityname, string matirialname, Ogre::SceneNode* node, Ogre::SceneManager* scenemanager, Ogre::FileSystemLayer* filesystemlayer_) {
    //carga de archivos?
   // load resource paths from config file



    m_material_name = matirialname;
    mStaticObject = isstatic;
    m_entity_name = entityname;
    m_mesh_name = modelname;
    m_scene_node = node;
    //como se deberia hacer pero que falla 
    mSM = scenemanager;
    m_ent_ogre = mSM->createEntity(m_material_name);
    m_scene_node->attachObject(m_ent_ogre);
    m_scene_node->setVisible(true);
    //TIENE QUE SER ENTIDAD MIAm??
   // auto t = getComponent<Transform>(m_ent);

   /* m_scene_node->setScale(t->getScale());
    m_scene_node->setPosition(t->getPosition());
    m_scene_node->setOrientation(t->getRotation());
    m_scene_node->attachObject(m_ent_ogre);*/


    if (m_material_name != "")
        m_ent_ogre->setMaterialName(m_material_name);



}
//constructora aqui se le pasaran todos los datos necesarios para inicializar
MeshRender::MeshRender(bool isstatic, string modelname, string entityname, string matirialname, SceneNode* node, SceneManager* scenemana ,FileSystemLayer* filesystemlayer_) {
    //carga de archivos?
    // load resource paths from config file
   

   
    m_material_name = matirialname;
    mStaticObject = isstatic;
    m_entity_name = entityname;
    m_mesh_name = modelname;
    m_scene_node = node;
    //como se deberia hacer pero que falla 
     mSM = scenemana;
    m_ent_ogre = mSM->createEntity(m_material_name);
    m_scene_node->attachObject(m_ent_ogre);
    m_scene_node->setVisible(true);
    //TIENE QUE SER ENTIDAD MIAm??
   // auto t = getComponent<Transform>(m_ent);

   /* m_scene_node->setScale(t->getScale());
    m_scene_node->setPosition(t->getPosition());
    m_scene_node->setOrientation(t->getRotation());
    m_scene_node->attachObject(m_ent_ogre);*/
  

    if (m_material_name != "")
        m_ent_ogre->setMaterialName(m_material_name);



  
}
//destructora
 MeshRender::~MeshRender() {

}

 bool MeshRender::createMesh() {
     if (m_mesh_name.size() > 0) {
         Ogre::SceneNode* entityNode = m_scene_mngr->getRootSceneNode()->createChildSceneNode(m_entity_name);
     }

     return false;
}
 void MeshRender::start() {
    // mTransform = m_ent_ogre.transform o como se haga;

     if (!mTransform) {
        
         return;
     }
    // setTransform(mTransform->GetPosition(), mTransform->GetScale(), mTransform->GetRotation());
}


 void MeshRender::update() {
     if (!mStaticObject) setTransform(mTransform->GetPosition(), mTransform->GetScale(), mTransform->GetRotation());
}
void MeshRender::setName(std::string name) {
     m_entity_name = name;
}
void MeshRender::setMeshName(std::string meshName) {
     m_mesh_name = meshName;
}
void setStatic(bool stat) {

}
void MeshRender::setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector3 rot) {
    conversor conve;
    
    setPosition(pos);
    setScale(scale);
    setRotation(rot);
}
void MeshRender::setPosition(VeryReal::Vector3 pos) {
    conversor conve;
   // m_scene_node->setPosition(conve.VRconversorOgre(pos));
}
void MeshRender::setScale(VeryReal::Vector3 scale) {
    conversor conve;
   // m_scene_node->setScale(conve.VRconversorOgre(scale));
}
void MeshRender::setRotation(VeryReal::Vector3 rot) {
    conversor conve;
   // m_scene_node->setOrientation(Ogre::Quaternion(conve.VRconversorOgre(rot)));//necesita un Quaternion
}
void MeshRender::activeMesh() {
    m_scene_node->setVisible(true);
}
void MeshRender::desactiveMesh() {
    m_scene_node->setVisible(false);
}
void MeshRender::setMaterial(std::string materialName) {
   
    m_material_name = materialName;
    m_ent_ogre->setMaterialName(materialName);
}
void MeshRender::changeMaterial(std::string t_materialName) {
    m_material_name = t_materialName;
    if (m_material_name != "")
        m_ent_ogre->setMaterialName(m_material_name);
}
void MeshRender::setRenderingDistance(float t_d) {
    m_ent_ogre->setRenderingDistance(t_d);
}
void MeshRender::setDebugVisibility(bool t_d) {
    m_ent_ogre->setDebugDisplayEnabled(t_d);
}
std::string MeshRender::getNameEntity() {
    return m_entity_name;
}
std::string MeshRender::getNameMesh() {
    return m_mesh_name;
}
Ogre::Entity* MeshRender::getOgreEntity() {
    return m_ent_ogre;
}
Ogre::AxisAlignedBox MeshRender::getBoundingBox() {
    return m_ent_ogre->getBoundingBox();
}
Ogre::SceneNode* MeshRender::getNode() {
    return m_scene_node;
}
void MeshRender::setCastShadows(bool t_shadow)
{
    m_ent_ogre->setCastShadows(t_shadow);
}