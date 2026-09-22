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
    /**
    * @brief Esta clase coordina el renderizado de las escenas OpenGL. Se implementa
    * aplicando el patrón de diseño Singleton. Está pensada para que las funciones callback hagan llamadas a sus métodos
     */
    class Renderer
    {
        private:
            static Renderer* instance; ///< Puntero al objeto
            // El constructor es privado para evitar que se cree el objeto desde otros módulos
            Renderer();
        public:
            ~Renderer();

            static Renderer& getInstance();
    };
}



#endif //PR02_RENDERER_H
