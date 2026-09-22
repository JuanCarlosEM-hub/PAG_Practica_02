/**
 * @file Renderer.cpp
 * @author Juan Carlos Enríquez Muñoz
 *
 * @date 22/09/2026
 *
 * @brief Implementación de la clase Renderer
 */

#include "Renderer.h"
namespace PAG {

    Renderer* Renderer::instance = nullptr;

    Renderer& Renderer::getInstance() {
        if (!Renderer::instance) {//Inicialización perezosa
            instance = new Renderer();
        }
        return *instance;
    }
}