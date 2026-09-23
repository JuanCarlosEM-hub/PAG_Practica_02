//
// Created by Juank on 23/09/2026.
//

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
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
    };
}


#endif //PR02_GUI_H
