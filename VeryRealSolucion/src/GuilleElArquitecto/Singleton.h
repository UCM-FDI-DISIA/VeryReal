#pragma once
#ifndef SINGLETON
#define SINGLETON
#include <memory>


namespace VeryReal {
    template<class T>
    class Singleton {
    private:
        //unica instancia de la clase de tipo T
        static std::unique_ptr<T> instance_pointer;

    protected:
        Singleton(){};

    public:
        // Eliminar el operador de asignación
        void operator=(const VeryReal::Singleton<T>& o) = delete;
        // Eliminar el constructor de copia
        Singleton(const VeryReal::Singleton<T>& o) = delete;
        virtual ~Singleton() { this->instance_pointer.release(); }

      
        static T* Instance() {
            if (instance_pointer.get() == nullptr) 
                //return Init();
                //assert
            return instance_pointer.get();
        }

         /* if (instance_pointer.get() == nullptr) {
                instance_pointer.reset(new T());
                
            }
            return instance_pointer.get();*/
        static void InitPointer(T** t) {
            std::cout << "pointer";
            instance_pointer.reset(*t);
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