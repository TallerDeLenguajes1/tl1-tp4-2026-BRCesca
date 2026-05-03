# Módulo To-Do: Gestión de Tareas con Listas Enlazadas
Este módulo es un sistema de administración de tareas desarrollado en C. Su función principal es organizar y mover datos entre dos estados (**Pendientes** y **Realizadas**) optimizando el uso de la memoria dinámica.

## Funcionamiento

### 1. Gestión de Memoria Dinámica
A diferencia de los arreglos fijos, este módulo utiliza **listas enlazadas**. El programa solicita memoria al sistema operativo solo cuando se crea una tarea y la devuelve inmediatamente al finalizar, evitando el desperdicio de RAM.

### 2. Estructura de los Nodos
La información se fragmenta en "Nodos". Cada nodo funciona como un contenedor con dos partes esenciales:
*   **La Tarea (Carga Útil):** Guarda el ID autoincremental (desde 1000), la descripción dinámica y la duración.
*   **El Enlace (Puntero):** Contiene la dirección de memoria de la siguiente tarea, permitiendo recorrer la lista de forma secuencial.

### 3. Transferencia por Reasignación de Punteros
El proceso de mover una tarea de "Pendiente" a "Realizada" es el corazón del módulo:
*   En lugar de copiar o sobrescribir datos, el programa **desconecta** el puntero del nodo en la lista original y lo **reconecta** en la nueva lista.
*   Esta operación es extremadamente eficiente ya que solo modifica direcciones de memoria, sin importar qué tan largo sea el texto de la descripción.

### 4. Algoritmos de Búsqueda
El módulo implementa un recorrido secuencial para las consultas:
*   **Por ID:** Compara el valor numérico en cada nodo hasta encontrar la coincidencia.
*   **Por Palabra Clave:** Utiliza la función `strstr` para buscar subcadenas dentro de las descripciones alojadas en la memoria dinámica.

### 5. Ciclo de Vida y Limpieza (Memory Leaks)
Para garantizar la integridad del sistema, se implementa una rutina de **liberación en cascada**. Al cerrar el programa, se recorren las listas liberando primero las cadenas de texto (`char *`) y luego los nodos (`free`), asegurando que no existan fugas de memoria.

---