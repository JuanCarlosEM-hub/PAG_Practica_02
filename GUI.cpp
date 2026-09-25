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
        if (ImGui::Begin("COLOR DE FONDO")) {
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

        ImGui::SetNextWindowPos(ImVec2(400,10), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(360, 420), ImGuiCond_Once);
        if (ImGui::Begin("CONSOLA")) {

            //Añadimos un botón para limpiar la consola
            if (ImGui::Button("Limpiar")) {
                mensajes.clear();
            }

            ImGui::SameLine();
            ImGui::Checkbox("Auto-scroll", &autoScroll);
            ImGui::Separator();

            ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            for (const auto& msg : mensajes) {
                ImGui::TextUnformatted(msg.c_str());
            }

            // Desplazar automáticamente hacia abajo si hay nuevos mensajes
            if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();
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

    void GUI::addMensaje(const std::string &mensaje) {
        mensajes.push_back(mensaje);
    }
}
