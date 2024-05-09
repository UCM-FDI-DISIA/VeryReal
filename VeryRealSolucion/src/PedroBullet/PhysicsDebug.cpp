#ifdef _DEBUG

#include "PhysicsDebug.h"
#include "RenderManager.h"
#include <LinearMath/btIDebugDraw.h>

using namespace Ogre;

VeryReal::PhysicsDebug::PhysicsDebug() {
    node = VeryReal::RenderManager::Instance()->getSceneManager()->getRootSceneNode();
    node->setVisible(true);  
    mtl = MaterialManager::getSingleton().create("RedMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mtl->setDiffuse(Ogre::ColourValue::Red);
    mDebugModes = (DebugDrawModes)DBG_DrawWireframe;
}

VeryReal::PhysicsDebug::~PhysicsDebug() 
{ 
    MaterialManager::getSingleton().remove(mtl);
    clearLines();
}

void VeryReal::PhysicsDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    auto g = VeryReal::RenderManager::Instance();
    
    Ogre::ManualObject* line = g->createManualObject(node);
    line->begin("RedMaterial", Ogre::RenderOperation::OT_LINE_LIST);
    line->position(from.x(), from.y(), from.z());
    line->position(to.x(), to.y(), to.z());
    line->colour(color.x(), color.y(), color.z());
    line->end();
    line->setCastShadows(false);
    lines.push_back(line);
}

void VeryReal::PhysicsDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
                                           const btVector3& color) {
    auto g = VeryReal::RenderManager::Instance();
    Ogre::ManualObject* line = g->createManualObject(node);
    line->begin(mtl, Ogre::RenderOperation::OT_POINT_LIST);
    line->position(PointOnB.x(), PointOnB.y(), PointOnB.z());
    btVector3 to = PointOnB + normalOnB * distance;
    line->position(to.x(), to.y(), to.z());
    line->colour(color.x(), color.y(), color.z());
    line->end();
    line->setCastShadows(false);
    lines.push_back(line);
}

void VeryReal::PhysicsDebug::reportErrorWarning(const char* warningString) { LogManager::getSingleton().getDefaultLog()->logMessage(warningString); }

void VeryReal::PhysicsDebug::draw3dText(const btVector3& location, const char* textString) { }

void VeryReal::PhysicsDebug::setDebugMode(int debugMode) { mDebugModes = (DebugDrawModes)debugMode; }

int VeryReal::PhysicsDebug::getDebugMode() const { return mDebugModes; }

void VeryReal::PhysicsDebug::clearLines() {
    auto g = VeryReal::RenderManager::Instance();
    for (std::list<Ogre::ManualObject*>::iterator it = lines.begin(); it != lines.end();) {
          g->destroyManualObject(*it);
          it = lines.erase(it);
    }
}
#endif   // DEBUG