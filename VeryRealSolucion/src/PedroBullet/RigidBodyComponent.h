#pragma once
#ifndef RIGIDBODYCOMPONENT
#define RIGIDBODYCOMPONENT
#define BEDUG_ERROR_TRANSFORM "NO SE HA PODIDO INICIALIZAR EL COMPONENTE RIGIDBODY DADO QUE NO CONTIENE EL COMPONENTE TRANSFORM\n"

#include <memory>
#include <Component.h>
#include "PhysicsValues.h"
#include <Vector3.h>
#include "export.h"

enum PBShapes;
enum PBMovementType;
class btCollisionShape;
class btRigidBody;
struct btDefaultMotionState;

#pragma warning(disable : 4251)

namespace VeryReal {
    class TransformComponent;
    class ColliderComponent;
    class VERYREAL_API RigidBodyComponent : public Component {
    public:
        RigidBodyComponent();
        bool InitComponent(int shapeType, float mass, float friction = 0.5f, float restitution = 0.0f, int movementType = MOVEMENT_TYPE_DYNAMIC, bool trigger = false);
        virtual ~RigidBodyComponent();

        // Funciones para manipular el cuerpo rígido
        void SetVelocityLinear(const Vector3& velocity);
        void SetVelocityAngular(const Vector3& velocity);
        Vector3 GetVelocity() const;
        void AddImpulse(const Vector3& impulse);
        void AddTorque(const Vector3& torque);

        void SetActiveTrigger(bool b);
        bool GetActiveTrigger();

        void SetMass(float n);
        float GetMass();

        void SetFriction(float n);
        float GetFriction();

        void SetRestitution(float n);
        float GetRestitution();

        void SetMovementType(PBMovementType mT);

        // Obtiene el btRigidBody 
        btRigidBody* GetBulletRigidBody();

        btCollisionShape* GetCollisionShape();

    private:
        TransformComponent* transformComponent;
        btCollisionShape* collisionShape;
        std::unique_ptr<btDefaultMotionState> motionState;
        btRigidBody* rigidBody;

        bool isTrigger;
        float mass;
        float friction;
        float restitution;
        PBMovementType movementType;
        ColliderComponent* collider = nullptr;
        bool InitializeRigidBody(PBShapes shapeType, PBMovementType movementType, bool trigger);
        btCollisionShape* CreateCollisionShape(PBShapes shapeType);
    };
} 

#pragma warning(default : 4251)

#endif 

/*FALTA:
*   - Mascara
*   - Capa
*   - Convertir en trigger(medio hecho pero falta)
*/