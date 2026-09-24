//
// Created by Juank on 23/09/2026.
//

#include "GUI.h"
#include "Renderer.h"

namespace PAG {
    GUI* GUI::instance = nullptr; //Inicializamos puntero

    GUI::GUI() {}
    GUI::~GUI() {}

    GUI& GUI::getInstance() {
        if (!instance) {
            instance = new GUI(); //Inicialización perezosa
        }
        return *instance;
    }

    void GUI::inicializar(GLFWwindow* window) {
        IMGUI_CHECKVERSION(); //Comprobamos versión
        ImGui::CreateContext(); // Creamos contexto
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Habilitar navvegación por teclado

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    void GUI::render() {
        //Preparamos el nuevo fragmento
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Definimos ventana y controles
        ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(360, 420), ImGuiCond_Once); //Tenemos que establcer el tamaño de la ventan
        if (ImGui::Begin("Mensajes")) {
            ImGui::SetWindowFontScale(1.0f);

            //Obtenemos color de la ventana actual
            float colorActual[4];
            PAG::Renderer::getInstance().obtenerColor(colorActual);

            // Selector de color con Rueda (PickerHueWheel)
            if (ImGui::ColorPicker4("Color de fondo", colorActual, ImGuiColorEditFlags_PickerHueWheel)) {
                // Si el usuario cambia el color, actualizamos el estado en Renderer
                PAG::Renderer::getInstance().establecerColor(
                    colorActual[0], colorActual[1], colorActual[2], colorActual[3]
                );
            }
        }
        ImGui::End();

        //Renderemos ImGui sobre el viewport de OpenGL
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI::finalizar() {
        //Liberamos los recursos
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUI::procesarBotonRaton(int button, int action) {
        ImGuiIO& io = ImGui::GetIO();

        if (action == GLFW_PRESS) {
            io.AddMouseButtonEvent(button, true);
        }else if (action == GLFW_RELEASE) {
            io.AddMouseButtonEvent(button, false);
        }
    }
}
