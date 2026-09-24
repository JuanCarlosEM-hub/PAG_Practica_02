/**
 * @file Renderer.cpp
 * @author Juan Carlos Enríquez Muñoz
 *
 * @date 22/09/2026
 *
 * @brief Implementación de la clase Renderer
 */

#include "Renderer.h"
#include <glad/glad.h>

namespace PAG {

    Renderer* Renderer::instance = nullptr;

    /**
     * @brief Constructor por defecto
     */
    Renderer::Renderer()= default;

    /**
     * @brief Destructor por defecto
     */
    Renderer::~Renderer() = default;

    /**
     * @brief Consulta del objeto único de la clase
     * @return Dirección de memoria del objeto
     */
    Renderer& Renderer::getInstance() {
        if (!Renderer::instance) {//Inicialización perezosa
            instance = new Renderer();
        }
        return *instance;
    }

    void Renderer::inicializar() {
        // Configuración inicial del estado de OpenGL
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glEnable(GL_DEPTH_TEST);
    }

    /**
     * @brief Hacer el refresco de la escena
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // refrescamos el buffer
    }


}