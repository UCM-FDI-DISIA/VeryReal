#ifdef _DEBUG

#include "PhysicsDebug.h"
#include "RenderManager.h"
#include <LinearMath/btIDebugDraw.h>

using namespace Ogre;

VeryReal::DebugMode::DebugMode() {
    node = VeryReal::RenderManager::Instance()->getSceneManager()->getRootSceneNode();
    node->setVisible(true);
    //mLines = VeryReal::RenderManager::Instance()->createManualObject("physics lines");
    //assert(mLines);
    //mTriangles = VeryReal::RenderManager::Instance()->createManualObject("physics triangles");
    //assert(mTriangles);
    //mLines->setDynamic(true);
    //mTriangles->setDynamic(true);

  
    mtl = MaterialManager::getSingleton().create("RedMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mtl->setDiffuse(Ogre::ColourValue::Red);
    
    //mLines->begin(matName, RenderOperation::OT_LINE_LIST);
    //mLines->position(Ogre::Vector3::ZERO);
    //mLines->colour(ColourValue::Red);
    //mLines->position(Ogre::Vector3::ZERO);
    //mLines->colour(ColourValue::Red);

    //mTriangles->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
    //mTriangles->position(Ogre::Vector3::ZERO);
    //mTriangles->colour(ColourValue::Red);
    //mTriangles->position(Ogre::Vector3::ZERO);
    //mTriangles->colour(ColourValue::Red);
    //mTriangles->position(Ogre::Vector3::ZERO);
    //mTriangles->colour(ColourValue::Red);

    mDebugModes = (DebugDrawModes)DBG_DrawWireframe;
  /*  Root::getSingleton().addFrameListener(this);*/
}

VeryReal::DebugMode::~DebugMode() { }

void VeryReal::DebugMode::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    auto g = VeryReal::RenderManager::Instance();
    
    Ogre::ManualObject* line = g->createManualObject(node);
    line->begin("Sinbad/Gold", Ogre::RenderOperation::OT_LINE_LIST);
    line->position(from.x(), from.y(), from.z());
    line->position(to.x(), to.y(), to.z());
    line->colour(color.x(), color.y(), color.z());
    line->end();
    line->setCastShadows(false);
    lines.push_back(line);
}

void VeryReal::DebugMode::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime,
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

void VeryReal::DebugMode::reportErrorWarning(const char* warningString) { LogManager::getSingleton().getDefaultLog()->logMessage(warningString); }

void VeryReal::DebugMode::draw3dText(const btVector3& location, const char* textString) { }

void VeryReal::DebugMode::setDebugMode(int debugMode) { mDebugModes = (DebugDrawModes)debugMode; }

int VeryReal::DebugMode::getDebugMode() const { return mDebugModes; }

void VeryReal::DebugMode::clearLines() {
    auto g = VeryReal::RenderManager::Instance();
    //for (std::list<Ogre::ManualObject*>::iterator it = lines.begin(); it != lines.end();) {
    //   /* g->destroyManualObject(*it);*/
    // /*   it = lines.erase(it);*/
    //}
}
#endif   // DEBUG