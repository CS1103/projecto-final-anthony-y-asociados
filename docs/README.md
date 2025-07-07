[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Lj3YlzJp)
# Proyecto Final 2025-1: AI Neural Network
## **CS2013 Programación III** · Informe Final

### **Descripción**

> Ejemplo: Implementación de una red neuronal multicapa en C++ para clasificación de dígitos manuscritos.

### Contenidos

1. [Datos generales](#datos-generales)
2. [Requisitos e instalación](#requisitos-e-instalación)
3. [Investigación teórica](#1-investigación-teórica)
4. [Diseño e implementación](#2-diseño-e-implementación)
5. [Ejecución](#3-ejecución)
6. [Análisis del rendimiento](#4-análisis-del-rendimiento)
7. [Trabajo en equipo](#5-trabajo-en-equipo)
8. [Conclusiones](#6-conclusiones)
9. [Bibliografía](#7-bibliografía)
10. [Licencia](#licencia)
---

### Datos generales

* **Tema**: Redes Neuronales en AI
* **Grupo**: Anthony y Asociados
* **Integrantes**:

  * Anthony Yair Caypane Ramirez – 202410690 (Responsable de investigación teórica)
  * Luciano Gabriel Rivera Valentin – 202410149 (Documentación y demo)
  * Luis Joaquín Tangüis Ayllón – 202410755 (Implementación del modelo)

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

* **Objetivo**: Explorar fundamentos y arquitecturas de redes neuronales.
* **Contenido de ejemplo**:

  1. Historia y evolución de las NNs.
  2. Principales arquitecturas: MLP, CNN, RNN.
  3. Algoritmos de entrenamiento: backpropagation, optimizadores.

---

### 2. Diseño e implementación

#### 2.1 Arquitectura de la solución

* **Patrones de diseño**: ejemplo: Factory para capas, Strategy para optimizadores.
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

pong_ai /
+-- include / # cabeceras principales
| +-- utec /
| +-- algebra / # á lgebra : implementa Tensor <T , Rank >
| | +-- Tensor .h
| +-- nn / # red neuronal : define capas y NeuralNetwork
| | +-- layer .h
| | +-- dense .h
| | +-- activation .h
| | +-- loss .h
| | +-- neural_network .h
| +-- agent / # agente y entorno : PongAgent y EnvGym
| +-- PongAgent .h
| +-- EnvGym .h
+-- src / # archivos fuentes ( si se requiriera )
| +-- utec /
| +-- agent / # agente y entorno : PongAgent y EnvGym
| +-- PongAgent . cpp
| +-- EnvGym . cpp
+-- tests / # casos de prueba automatizados para Gradescope
| +-- test_tensor . cpp
| +-- test_neural_network . cpp
| +-- test_agent_env . cpp
+-- docs / # documentaci ón del proyecto y bibliograf ía
+-- README . md
+-- BIBLIOGRAFIA . md

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
> Pasos:
>
> 1. Preparar datos de entrenamiento (formato CSV).
> 2. Ejecutar comando de entrenamiento.
> 3. Evaluar resultados con script de validación.

---

### 4. Análisis del rendimiento

* **Métricas de ejemplo**:

  * Iteraciones: 1000 épocas.
  * Tiempo total de entrenamiento: 2m30s.
  * Precisión final: 92.5%.
* **Ventajas/Desventajas**:

  * * Código ligero y dependencias mínimas.
  * – Sin paralelización, rendimiento limitado.
* **Mejoras futuras**:

  * Uso de BLAS para multiplicaciones (Justificación).
  * Paralelizar entrenamiento por lotes (Justificación).

---

### 5. Trabajo en equipo

| Tarea                     | Miembro  | Rol                       |
| ------------------------- | -------- | ------------------------- |
| Investigación teórica     | Alumno A | Documentar bases teóricas |
| Diseño de la arquitectura | Alumno B | UML y esquemas de clases  |
| Implementación del modelo | Alumno C | Código C++ de la NN       |
| Pruebas y benchmarking    | Alumno D | Generación de métricas    |
| Documentación y demo      | Alumno E | Tutorial y video demo     |

> *Actualizar con tareas y nombres reales.*

---

### 6. Conclusiones

* **Logros**: Implementar NN desde cero, validar en dataset de ejemplo.
* **Evaluación**: Calidad y rendimiento adecuados para propósito académico.
* **Aprendizajes**: Profundización en backpropagation y optimización.
* **Recomendaciones**: Escalar a datasets más grandes y optimizar memoria.

---

### 7. Bibliografía

> *Actualizar con bibliografia utilizada, al menos 4 referencias bibliograficas y usando formato IEEE de referencias bibliograficas.*

---

### Licencia

Este proyecto usa la licencia **GPLv3**. Ver [LICENSE](LICENSE) para detalles.

---
