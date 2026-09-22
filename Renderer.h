/**
* @file Renderer.h
 * @author Juan Carlos Enríquez Muñoz
 *
 * @date 22/09/2026
 *
 * @brief Declaración de la clase Renderer
 */
#ifndef PR02_RENDERER_H
#define PR02_RENDERER_H

namespace PAG
{
    class Renderer
    {
        private:
            static Renderer* instance;
            // El constructor es privado para evitar que se cree el objeto desde otros módulos
            Renderer();
        public:
            static Renderer& getInstance();
    };
}



#endif //PR02_RENDERER_H
