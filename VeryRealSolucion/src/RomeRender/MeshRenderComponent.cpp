#include "MeshRenderComponent.h"
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


void MeshRenderComponent::InitComponent(bool isstatic, std::string modelname, std::string entityname, std::string matirialname, Ogre::SceneNode* node, Ogre::SceneManager* scenemanager, Ogre::FileSystemLayer* filesystemlayer_) {

   
    material_name = matirialname;
    mStaticObject = isstatic;
    entity_name = entityname;
    mesh_name = modelname;
    scene_node = node;
    //como se deberia hacer pero que falla 
    mSM = scenemanager;
    ent_ogre = mSM->createEntity(modelname);
    scene_node->attachObject(ent_ogre);
    scene_node->setVisible(true);
    //TIENE QUE SER ENTIDAD MIAm??
   // auto t = getComponent<Transform>(m_ent);

   /* m_scene_node->setScale(t->getScale());
    m_scene_node->setPosition(t->getPosition());
    m_scene_node->setOrientation(t->getRotation());
    m_scene_node->attachObject(m_ent_ogre);*/


    if (material_name != "")
        ent_ogre->setMaterialName(material_name,"General");



}

//destructora
MeshRenderComponent::~MeshRenderComponent() {

}

 bool MeshRenderComponent::createMesh() {
     if (mesh_name.size() > 0) {
         Ogre::SceneNode* entityNode = scene_mngr->getRootSceneNode()->createChildSceneNode(entity_name);
     }

     return false;
}
 


 void MeshRenderComponent::update() {
     if (!mStaticObject) setTransform(transform->GetPosition(), transform->GetScale(), transform->GetRotation());
}
void MeshRenderComponent::setName(std::string name) {
     entity_name = name;
}
void MeshRenderComponent::setMeshName(std::string meshName) {
     mesh_name = meshName;
}
void setStatic(bool stat) {

}
void MeshRenderComponent::setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector3 rot) {
    conversor conve;
    
    setPosition(pos);
    setScale(scale);
    setRotation(rot);
}
void MeshRenderComponent::setPosition(VeryReal::Vector3 pos) {
    conversor conve;
   // m_scene_node->setPosition(conve.VRconversorOgre(pos));
}
void MeshRenderComponent::setScale(VeryReal::Vector3 scale) {
    conversor conve;
   // m_scene_node->setScale(conve.VRconversorOgre(scale));
}
void MeshRenderComponent::setRotation(VeryReal::Vector3 rot) {
    conversor conve;
   // m_scene_node->setOrientation(Ogre::Quaternion(conve.VRconversorOgre(rot)));//necesita un Quaternion
}
void MeshRenderComponent::activeMesh() {
    scene_node->setVisible(true);
}
void MeshRenderComponent::desactiveMesh() {
    scene_node->setVisible(false);
}
void MeshRenderComponent::setMaterial(std::string materialName) {
   
    material_name = materialName;
    ent_ogre->setMaterialName(materialName);
}
void MeshRenderComponent::changeMaterial(std::string t_materialName) {
    material_name = t_materialName;
    if (material_name != "")
        ent_ogre->setMaterialName(material_name);
}
void MeshRenderComponent::setRenderingDistance(float t_d) {
    ent_ogre->setRenderingDistance(t_d);
}
void MeshRenderComponent::setDebugVisibility(bool t_d) {
    ent_ogre->setDebugDisplayEnabled(t_d);
}
std::string MeshRenderComponent::getNameEntity() {
    return entity_name;
}
std::string MeshRenderComponent::getNameMesh() {
    return mesh_name;
}
Ogre::Entity* MeshRenderComponent::getOgreEntity() {
    return ent_ogre;
}
Ogre::AxisAlignedBox MeshRenderComponent::getBoundingBox() {
    return ent_ogre->getBoundingBox();
}
Ogre::SceneNode* MeshRenderComponent::getNode() {
    return scene_node;
}
void MeshRenderComponent::setCastShadows(bool t_shadow)
{
    ent_ogre->setCastShadows(t_shadow);
}