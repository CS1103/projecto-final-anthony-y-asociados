[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Lj3YlzJp)
# Proyecto Final 2025-1: AI Neural Network
## **CS2013 Programación III** · Informe Final

### **Descripción**

Este proyecto consiste en la implementación de una red neuronal multicapa en C++ para controlar un agente que juega una versión simplificada del juego Pong. Se desarrolla un entorno simulado (`EnvGym`) donde la posición de la bola y la paleta se actualizan en tiempo real, y un agente (`PongAgent`) toma decisiones sobre el movimiento usando una red neuronal implementada desde cero.

### Contenidos

*. [Datos generales](#datos-generales)
*. [Requisitos e instalación](#requisitos-e-instalación)
1. [Investigación teórica](#1-investigación-teórica)
2. [Diseño e implementación](#2-diseño-e-implementación)
3. [Ejecución](#3-ejecución)
4. [Análisis del rendimiento](#4-análisis-del-rendimiento)
5. [Trabajo en equipo](#5-trabajo-en-equipo)
6. [Conclusiones](#6-conclusiones)
7. [Bibliografía](#7-bibliografía)
8. [Licencia](#licencia)
---

### Datos generales

* **Tema**: Redes Neuronales en AI
* **Grupo**: Anthony y Asociados
* **Integrantes**:

  * Anthony Yair Caypane Ramirez – 202410690 (Responsable de investigación teórica)
  * Luciano Gabriel Rivera Valentin – 202410149 (Documentación y demo)
  * Luis Joaquín Tangüis Ayllón – 202410755 (Implementación del modelo)

* **Curso**: CC3101 - Programación III
* **Nombre del profesor:** Ruben Rivas.

---

### Requisitos e instalación

1. **Compilador**: GCC 11 o superior
2. **Dependencias**:

   * CMake 3.18+
   * Eigen 3.4
   * Catch2 3.5.2
3. **Instalación**:

   ```bash
   git clone https://github.com/CS1103/projecto-final-anthony-y-asociados.git
   cd projecto-final-anthony-y-asociados
   mkdir build && cd build
   cmake ..
   make
   ```
   
---

### 1. Investigación teórica

* **Objetivo**: Explorar fundamentos y arquitecturas de redes neuronales artificiales aplicadas a toma de decisiones.
* **Contenido del proyecto**:

* Las redes neuronales artificiales (ANN) son sistemas computacionales inspirados en las redes biológicas del cerebro.

* Este proyecto implementa un perceptrón multicapa (MLP) con una función de activación ReLU y una capa de salida softmax.

* Se utiliza el algoritmo de retropropagación (backpropagation) para ajustar los pesos, basado en el gradiente descendente.

* El agente decide sus acciones basándose en el estado del entorno (posición de la bola y paleta).

* Este enfoque forma parte del campo de aprendizaje por refuerzo, aunque aquí no se incluye el proceso de entrenamiento completo.

---

### 2. Diseño e implementación

#### 2.1 Arquitectura de la solución

* **Diseño modular** usando clases como EnvGym, PongAgent, y capas de red neuronal (Dense, Activation, Loss).


* **Estructura de carpetas**:

```

projecto-final-anthony-y-asociados/
├── CMakeLists.txt
├── docs
│   ├── BIBLIOGRAFIA.md
│   ├── LICENSE
│   └── README.md
├── include
|   └── utec
│       ├── agent
│       |   ├── EnvGym.h
│       |   └── PongAgent.h
│       ├── algebra
│       |   └── Tensor.h
│       ├── nn
│       │   ├── activation.h
│       │   ├── dense.h
│       │   ├── layer.h
│       │   ├── loss.h
│       │   ├── neural_network.h
│       │   └── optimizer.h
│       └── threading
│           └── ThreadPool.h
├── src
│   ├── bench
│   │   ├── bench_seq.cpp
│   │   └── bench_thread.cpp
│   ├── main.cpp
│   └── utec
│       ├── agent
│       │   ├── EnvGym.cpp
│       │   └── PongAgent.cpp
│       └── threading
│           └── ThreadPool.cpp
├── tests
│   ├── test_agent_env.cpp
│   ├── test_neural_network.cpp
│   └── test_tensor.cpp

```

#### 2.2 Manual de uso y casos de prueba

* **Cómo ejecutar**: `./build/neural_net_demo input.csv output.csv`
* **Casos de prueba**:

  * Test unitario de capa densa.
  * Test de función de activación ReLU.
  * Test de convergencia en dataset de ejemplo.

> *Personalizar rutas, comandos y casos reales.*

---

### 3. Ejecución

> **Demo de ejemplo**: Video/demo alojado en `docs/demo.mp4`.
* Al ejecutar el binario principal, se simula un entorno Pong donde el agente toma decisiones de movimiento. La salida se presenta por consola indicando el estado del entorno y la acción tomada por el agente.
> Pasos:
>
> 1. Preparar datos de entrenamiento (formato CSV).
> 2. Ejecutar comando de entrenamiento.
> 3. Evaluar resultados con script de validación.

---

### 4. Análisis del rendimiento

* **Estado actual:**

* El sistema responde en tiempo real y ejecuta decisiones por cuadros.

* No se realiza entrenamiento completo; el modelo funciona con pesos inicializados.

**Limitaciones:**

* No hay paralelización.

* No se aplica retropropagación sobre múltiples partidas.

**Futuras mejoras:**

* Entrenar con refuerzo profundo (DQN).

* Agregar visualización o exportación a CSV.

* Optimización con librerías BLAS o multithreading en capa dense.

---

### 5. Trabajo en equipo

| Tarea                     | Miembro                         | Rol                        |
| ------------------------- | ------------------------------- | -------------------------- |
| Investigación teórica     | Anthony Yair Caypane Ramirez    | Documentar bases teóricas  |
| Investigación teórica     | Luciano Gabriel Rivera Valentin | Documentación y demo       |
| Investigación teórica     | Luis Joaquín Tangüis Ayllón     | Documentación y demo       |

---

### 6. Conclusiones

* El proyecto permitió comprender a fondo cómo funcionan las redes neuronales a bajo nivel.

* Se logró una integración completa entre un entorno simulado y un agente inteligente.

* Quedaron como retos el entrenamiento real y el análisis visual, pero el objetivo académico se cumplió con éxito.

* Se reforzaron habilidades en programación modular, CMake y pruebas unitaria

---

### 7. Bibliografía

* >[1] Y. LeCun, Y. Bengio y G. Hinton, "Deep learning", Nature, vol. 521, no. 7553, pp. 436–444, 2015.
* >[2] I. Goodfellow, Y. Bengio, A. Courville, Deep Learning, MIT Press, 2016.
* >[3] M. Nielsen, Neural Networks and Deep Learning, Determination Press, 2015.
* >[4] Documentación de Eigen C++: https://eigen.tuxfamily.org
* >[5] Documentación de Catch2: https://github.com/catchorg/Catch2



### Licencia

Este proyecto usa la licencia **GPLv3**. Ver [LICENSE](LICENSE) para detalles.

---
