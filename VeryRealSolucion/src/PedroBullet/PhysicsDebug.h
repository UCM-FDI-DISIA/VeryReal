
#ifdef _DEBUG

#ifndef PHYSICSDEBUG
#define PHYSICSDEBUG
#include <vector>
#include <btBulletCollisionCommon.h>
#include <Ogre.h>



struct ContactPoint {
    Ogre::Vector3 from;
    Ogre::Vector3 to;
    Ogre::ColourValue color;
    size_t dieTime;
};
namespace VeryReal {

class DebugMode : public btIDebugDraw, public Ogre::FrameListener {
        private:
    DebugDrawModes mDebugModes;
    Ogre::SceneNode* node;
    std::list<Ogre::ManualObject*> lines;
    Ogre::MaterialPtr mtl;

    public:
    DebugMode();
    ~DebugMode();
     protected:
 

     virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

     virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
     virtual void reportErrorWarning(const char* warningString);
     virtual void draw3dText(const btVector3& location, const char* textString);
     virtual void setDebugMode(int debugMode);
     virtual int getDebugMode() const;
     void clearLines() override;
};
}
#endif   

#endif //Debug