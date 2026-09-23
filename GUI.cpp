//
// Created by Juank on 23/09/2026.
//

#include "GUI.h"

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
}