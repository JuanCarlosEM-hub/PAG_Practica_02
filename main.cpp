#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <random>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "GUI.h"

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback ( int errno, const char* desc )
{
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window )
{
    //Llamamos a la instancia y refrescamos
    PAG::Renderer::getInstance().refrescar();

    //Dibujamos la interfaz de usuario
    PAG::GUI::getInstance().render();

    glfwSwapBuffers ( window );
    std::cout << "Refresh callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{
    glViewport ( 0, 0, width, height );
    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods )
{
    if ( action == GLFW_PRESS )
    {
        std::cout << "Pulsado el botón: " << button << std::endl;
    }
    else if ( action == GLFW_RELEASE )
    {
        std::cout << "Soltado el botón: " << button << std::endl;
    }

    // Notificamo del evento a GUI
    PAG::GUI::getInstance().procesarBotonRaton(button, action);
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset )
{
    std::cout << "Movida la rueda del ratón " << xoffset
    //Esta salida de consola no tiene sentido puesto que la rueda solo tiene sentido vertical, a no ser que usemos el mousepad
              << " Unidades en horizontal y " << yoffset
              << " unidades en vertical" << std::endl;

    // Arreglo para guardar los componentes (R, G, B, A)
    float colorActual[4];

    // Consulta a OpenGL el color de borrado actual
    glGetFloatv(GL_COLOR_CLEAR_VALUE, colorActual);

    /*
     * Esta función es correcta, no obstante, como cambiamos todos los tonos por igual solo se ve un cambio de grises
     * Vamos a "complicar" un poco más el ejercico buscando aleaoriedad en los colores y teniendo en cuenta el sentido de giro
    for ( int i = 0; i < 3; ++i)
    {
        if (colorActual[i] >=0.9)
        {
            colorActual[i] =0.0;
        }else
        {
            colorActual[i] +=0.1;
        }
    }*/

    std::random_device rd;
    std::mt19937 gen(rd());

    // Buscamos el valor flotante mínimo justo por encima de 0.0
    double minimo_exclusivo = std::nextafter(0.0, 1.0);

    // std::uniform_real_distribution incluye el límite inferior pero excluye el superior: [min, 1.0)
    std::uniform_real_distribution<double> distrib(minimo_exclusivo, 1.0);

    // Generar el número decimal estrictamente entre 0 y 1
    double valor_sum_nuevo_color = distrib(gen);

    // Aplicamos el nuevo color a cada elemento
    for ( int i = 0; i < 3; i++ )
    {
        // Sin comprobar, modificamos el elemento del array
        // Para que el color se vea distinto, multiplicamos la posicion del elemento por el sentido de rotación. De este modo algunos elementos suman y otros restan
        // Aclarar, que aunque algunos sumen y otros resten, siempre suman o restan los mismo respectivamente el eje de la rueda
        colorActual[i] += valor_sum_nuevo_color * i *yoffset;

        //Comprobamos si se sale de rango por el límite superior
        if ( colorActual[i] > 1.0 ) {
            colorActual[i] = 0; //Lo establecemos a 0 si es inválido
        }else if ( colorActual[i] < 0.0 )
        {
            colorActual[i] = 1.0; // Lo establecemos a 1 si es inválido
        }
    }
    // Aplicamos en el fondo
    glClearColor(colorActual[0], colorActual[1], colorActual[2], colorActual[3]);

}

int main()
{
    std::cout << "Starting Application PAG - Prueba 01" << std::endl;

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback );

    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 ); // OpenGL Core Profile 4.3.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;
    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );
    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // 1. Establecer el contexto OpenGL actual antes de invocar cualquier función OpenGL o cargar GLAD
    glfwMakeContextCurrent ( window );

    // 2. Inicializar GLAD (debe hacerse inmediatamente después de establecer el contexto)
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    {
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    // Inicializamos la clase GUI pasando el puntero a la ventana GLFW
    PAG::GUI::getInstance().inicializar(window);

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto 3D construido
    std::cout << glGetString ( GL_RENDERER ) << std::endl
              << glGetString ( GL_VENDOR ) << std::endl
              << glGetString ( GL_VERSION ) << std::endl
              << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // - Configuración inicial del estado de OpenGL
    glClearColor ( 0.6f, 0.6f, 0.6f, 1.0f );
    glEnable ( GL_DEPTH_TEST );

    // - Ciclo de eventos principal de la aplicación (se unifica en un único bucle)
    while ( !glfwWindowShouldClose ( window ) )
    {
        // - Borra los buffers (color y profundidad)
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // - Intercambia los buffers back y front
        glfwSwapBuffers ( window );

        // - Procesa los eventos pendientes (teclado, ratón, etc.)
        glfwPollEvents ();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos
    std::cout << "Finishing application pag prueba" << std::endl;
    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.

    return 0;
}