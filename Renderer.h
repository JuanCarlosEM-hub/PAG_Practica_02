//
// Created by Juank on 21/09/2026.
//

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
    };
}



#endif //PR02_RENDERER_H
