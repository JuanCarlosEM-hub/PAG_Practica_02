/**
* @file GUI.h
 * @author Juan Carlos Enríquez Muñoz
 * @date 23/09/2026
 * @brief Declaración de la clase GUI para la gestión de la interfaz con Dear ImGui.
 */

#ifndef PR02_GUI_H
#define PR02_GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

#include "Listener.h"
namespace PAG {
    /**
     * @brief Gestiona la interfaz gráfica y actúa como Sujeto en el patrón Observador.
     */
    class GUI {
        private:
            static GUI* instance; ///< Instancia Única
            GUI();

            // Almacén de mensajes y estado del scroll
            std::vector<std::string> mensajes; ///< Vector de almacenamiento de mensajes para la consola interna.
            bool autoScroll = true; ///< Booleano para controlar el desplazamiento automático de la consola.

            // Ventanas
            void selectorColorTriangular();
            void consola();
        public:
            virtual ~GUI();
            static GUI& getInstance();

            // Métodos principales encapsulados
            void inicializar(GLFWwindow* window);
            void render();
            void finalizar();

            //Gestión de eventos
            void procesarBotonRaton(int button, int action);

            //Añadir mensaje a ala consola
            void addMensaje(const std::string& mensaje);
    };
}


#endif //PR02_GUI_H
