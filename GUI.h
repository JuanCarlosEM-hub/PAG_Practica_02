//
// Created by Juank on 23/09/2026.
//

#include <imgui.h>
#include <../backends/imgui_impl_glfw.h>
#include <../backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#ifndef PR02_GUI_H
#define PR02_GUI_H

namespace PAG {
    class GUI {
        private:
            static GUI* instance; ///< Instancia Única
            GUI();

        public:
            virtual ~GUI();
            static GUI& getInstance();

            // Métodos principales encapsulados
            void inicializar(GLFWwindow* window);
            void renderer();
            void finalizar();
    };
}


#endif //PR02_GUI_H
