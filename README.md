# Práctica 02: Renderer

**Asignatura:** Programación de Aplicaciones Gráficas (PAG)  
**Profesor:** Ángel Luis García Fernández  
**Alumno:** Juan Carlos Enríquez Muñoz  
**Año:** 2026

---

##  Resumen de Cambios Realizados

En esta práctica se ha extendido el motor gráfico desacoplando la interfaz de usuario de la lógica de renderizado mediante la integración de la biblioteca **Dear ImGui** y la implementación del patrón obsevador

### 1. Integración de Dear ImGui
* **Selector de Color de Fondo (`COLOR DE FONDO`):** Se ha añadido una ventana interactiva para modificar el color de fondo a través de un selector de color triangular.
* **Consola de Eventos Interna (`CONSOLA`):** Se ha diseñado una ventan con área de desplazamiento, botón de limpiado y checkbox de *auto-scroll* para mostrar los mensajes por consola de la aplicación directamente en la interfaz.

### 2. Arquitectura y Patrones de Diseño
* **Patrón Singleton:** Implementado en las clases `PAG::Renderer` y `PAG::GUI` para centralizar la gestión del motor gráfico y de la interfaz respectivamente.
* **Patrón Observador (Observer):**
    * **`PAG::Listener` (Interfaz/Abstracta):** Define el contrato `notificarCambioColor(r, g, b, a)` para los objetos interesados en reaccionar a cambios en la GUI.
    * **`PAG::GUI` (Sujeto/Publicador):** Gestiona la lista de observadores (`std::vector<Listener*>`). Al interactuar con la rueda de color, emite una notificación a los observadores sin tener dependencia directa de OpenGL o `PAG::Renderer`.
    * **`PAG::Renderer` (Observador Concreto):** Implementa `PAG::Listener` y se suscribe a `PAG::GUI` durante su método `inicializar()`. Al recibir la notificación, actualiza el estado de `glClearColor`.

### 3. Refactorización del Bucle Principal (`main.cpp`)
* Se han eliminado todas las llamadas directas a funciones OpenGL de `main.cpp`.
* El ciclo de renderizado llama ordenadamente a `PAG::Renderer::getInstance().refrescar()` seguido de `PAG::GUI::getInstance().render()`.

---

## Diagrama de Clases UML

El siguiente diagrama ilustra la relación de desacoplamiento entre `PAG::GUI` y `PAG::Renderer` a través de la interfaz `PAG::Listener`:

```mermaid
classDiagram
    class Listener {
        <<interface>>
        +~Listener()
        +notificarCambioColor(r: float, g: float, b: float, a: float)* void
    }

    class Renderer {
        -static instance: Renderer*
        -Renderer()
        +~Renderer()
        +static getInstance() Renderer&
        +inicializar() void
        +refrescar() void
        +establecerViewport(x: int, y: int, width: int, height: int) void
        +establecerColor(r: float, g: float, b: float, a: float) void
        +obtenerColor(colorActual: float[4]) void
        +mostrarInformacionGL() void
        +notificarCambioColor(r: float, g: float, b: float, a: float) void
    }

    class GUI {
        -static instance: GUI*
        -mensajes: vector~string~
        -autoScroll: bool
        -colorActual: float[4]
        -listeners: vector~Listener*~
        -GUI()
        -selectorColorTriangular() void
        -consola() void
        -notificarObservadoresColor() void
        +~GUI()
        +static getInstance() GUI&
        +inicializar(window: GLFWwindow*) void
        +render() void
        +finalizar() void
        +procesarBotonRaton(button: int, action: int) void
        +addMensaje(mensaje: const string&) void
        +addListener(listener: Listener*) void
        +removeListener(listener: Listener*) void
    }

    class Main ["main.cpp"] {
        <<file>>
        +main() int
    }

    Listener <|.. Renderer : Implementa
    GUI "1" o-- "*" Listener : listeners
    Main ..> GUI : Utiliza / Inicializa
    Main ..> Renderer : Utiliza / Inicializa
```