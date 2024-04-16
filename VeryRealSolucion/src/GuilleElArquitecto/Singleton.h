#pragma once
#ifndef SINGLETON
#define SINGLETON
#include <memory>

namespace VeryReal {
    template<class T>
    class Singleton {
  
       

    protected:
        //unica instancia de la clase de tipo T
        static std::unique_ptr<T> instance_pointer;
        Singleton(){};

    public:
        // Eliminar el operador de asignación
        void operator=(const VeryReal::Singleton<T>& o) = delete;
        // Eliminar el constructor de copia
        Singleton(const VeryReal::Singleton<T>& o) = delete;
        virtual ~Singleton() { this->instance_pointer.release(); }

        //devuelve la clase singelton:
        //->Si no existe lo crea llamando a Init
        //->Si existe lo devuelve
        static T* Instance() {
            //ASSERT
            if (instance_pointer.get() != nullptr)    
            return instance_pointer.get();
        }


        //elimina el puntero de la instancia
        /* static void Delete() {
                if (instance_pointer.get() != nullptr) {
                        instance_pointer.release();
                }
            }*/
    };

    // Inicializar la instancia estática a nullptr
    template<typename T>
    std::unique_ptr<T> VeryReal::Singleton<T>::instance_pointer = nullptr;
}
#endif