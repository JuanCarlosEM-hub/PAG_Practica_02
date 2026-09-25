//
// Created by Juank on 23/09/2026.
//

#ifndef PR02_GUI_H
#define PR02_GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

namespace PAG {
    class GUI {
        private:
            static GUI* instance; ///< Instancia Única
            GUI();

            // Almacén de mensajes y estado del scroll
            std::vector<std::string> mensajes;
            bool autoScroll = true;

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
