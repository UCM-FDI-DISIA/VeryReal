#pragma once
#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H


#include <memory>
#include <Component.h>
#include "PhysicsValues.h"
#include <Vector3.h>

    enum PBShapes;
    enum PBMovementType;
    class btCollisionShape;
    class btRigidBody;
    class btDefaultMotionState;


namespace VeryReal {

    class TransformComponent;
    class Collider;
    class RigidBodyComponent : public Component {
    public:
        RigidBodyComponent(PBShapes shapeType, float mass, float friction = 0.5f, float restitution = 0.0f, PBMovementType movementType = MOVEMENT_TYPE_DYNAMIC, bool trigger = false);
        virtual ~RigidBodyComponent();

        // Funciones para manipular el cuerpo rígido
        void SetVelocity(const Vector3& velocity);
        void SetAngularVelocity(const Vector3& velocity);
        Vector3 GetVelocity() const;
        void AddImpulse(const Vector3& impulse);
        void AddTorque(const Vector3& torque);

        void SetActiveRB(bool b);
        void SetActiveTrigger(bool b);
        bool GetActiveRB();
        bool GetActiveTrigger();

        // Obtiene el btRigidBody 
        btRigidBody* GetBulletRigidBody() const;

    private:
        TransformComponent* transformComponent;
        std::unique_ptr<btCollisionShape> collisionShape;
        std::unique_ptr<btDefaultMotionState> motionState;
        std::unique_ptr<btRigidBody> rigidBody;

        bool isActive;
        bool isTrigger;
        float mass;
        float friction;
        float restitution;
        PBMovementType movementType;
        Collider* collider = nullptr;
        void InitializeRigidBody(PBShapes shapeType);
        btCollisionShape* CreateCollisionShape(PBShapes shapeType);
    };

} 

#endif 



/*FALTA:
*   - Mascara
*   - Capa
*   - Setters/ Getters(algunos hechos)
*   - Convertir en trigger(medio hecho pero falta)
*/