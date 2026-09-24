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

            void inicializar();
            void refrescar();

            void establecerViewport(int x, int y, int width, int height);

            // Gestión del color de fondo (clear color)
            void establecerColor(float r, float g, float b, float a = 1.0f);
            void obtenerColor(float colorActual[4]);

            void mostrarInformacionGL();

    };
}



#endif //PR02_RENDERER_H
