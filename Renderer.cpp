/**
 * @file Renderer.cpp
 * @author Juan Carlos Enríquez Muñoz
 *
 * @date 22/09/2026
 *
 * @brief Implementación de la clase Renderer
 */

#include "Renderer.h"

//Inicialización del atributo
PAG::Renderer* PAG::Renderer::instance = nullptr;

PAG::Renderer& PAG::Renderer::getInstance() {
    if (!PAG::Renderer::instance) {//Inicialización perezosa
        instance = new PAG::Renderer();
    }
    return *instance;
}