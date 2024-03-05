

#include "MeshRender.h"

#include <OgreAxisAlignedBox.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "Vector4.h"

#include "RenderManager.h"
//entity y transform (transform ya esta en el otro lado)
#include <cassert>

using namespace VeryReal;
using namespace Ogre;


//constructora aqui se le pasaran todos los datos necesarios para inicializar
MeshRender::MeshRender(bool isstatic) {
    mStaticObject = isstatic;
    
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
    // if (!mStaticObject) setTransform(mTransform->GetPosition(), mTransform->GetScale(), mTransform->GetRotation());
}
void MeshRender::setName(std::string name) {
     m_entity_name = name;
}
void MeshRender::setMeshName(std::string meshName) {
     m_mesh_name = meshName;
}
void MeshRender::setTransform(VeryReal::Vector3 pos, VeryReal::Vector3 scale, VeryReal::Vector4 rot) {
   // m_scene_node->setPosition(pos.());
   // m_scene_node->setScale(scale.());
   // m_scene_node->setOrientation(rot.());
}
void MeshRender::setPosition(VeryReal::Vector3 pos) {
   // m_scene_node->setPosition(pos.());
}
void MeshRender::setScale(VeryReal::Vector3 scale) {
   // m_scene_node->setScale(scale); //necesito que pase de nuestro v3 al de ogre 
}
void MeshRender::setRotation(VeryReal::Vector4 rot) {
   // m_scene_node->setOrientation();//necesita un Quaternion
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