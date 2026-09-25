//
// Created by Juank on 25/09/2026.
//

#ifndef PR02_LISTENER_H
#define PR02_LISTENER_H

namespace PAG {
    class Listener {
        public:
            virtual ~Listener() = default;

            virtual void notificarCambioColor(float r, float g, float b, float a) = 0;
    };
}


#endif //PR02_LISTENER_H
