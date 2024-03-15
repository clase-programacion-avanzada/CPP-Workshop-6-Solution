# Taller6 - Repaso de todos los temas

En este taller es obligatorio el uso de estructuras y funciones. Debe usar headers para evitar que el código se vea muy extenso, y ***no puede usar `cin` o `cout` en ninguna parte del código que no sea el archivo `main.cpp`.***

## Matriz de Eisenhower (5.0)

La [Matriz de Eisenhower](https://asana.com/es/resources/eisenhower-matrix) es una herramienta de gestión del tiempo que divide las tareas en cuatro cuadrantes basados en su urgencia e importancia. Los cuatro cuadrantes son:

1. Hacer (tareas urgentes e importantes. Ejemplo: «Terminar el informe de laboratorio»)
2. Planificar (tareas importantes pero no urgentes. Ejemplo: «Leer el capítulo 3 del libro de cálculo»)
3. Delegar (tareas urgentes pero no importantes. Ejemplo: «Hacer el almuerzo»)
4. Eliminar (tareas ni urgentos ni importantes. Ejemplo: «Ver el último episodio de la serie favorita»)

Basado en esta idea, le han pedido que desarrolle un programa con los siguientes requerimientos:

1. [Defina una estructura](./libs/Task.h) que represente una tarea, con los siguientes atributos:
   - **description**: cadena de caracteres que describe una tarea.  
   - **isUrgent**: un booleano que indica si la tarea es urgente o no.
   - **isImportant**: un booleano que indica si la tarea es importante o no.
   - **estimatedTime**: un entero que indica el tiempo estimado, en minutos, necesario para completar la tarea.
2. [Desarrolle una función](./libs/Task.h) que lea un archivo de texto  que contiene una lista de tareas con el siguiente formato:
   ```c++
    Study Biology exam;0;0;120
   ```
   Como puede observar, cada uno de los datos corresponden con los atributos de la estructura que definimos previamente.</br></br>
   
   La función debe retornar una lista de tareas y recibir por referencia el nombre del archivo que debe leer.</br></br>
3. [Desarrolle una función](./libs/TaskBinary.h) que escriba la lista leída del archivo de texto y lo guarde en un archivo binario. Esta función recibe por referencia el nombre del archivo y la lista de tareas que va a escribir.</br></br>
4. [Desarrolle una función](./libs/Task.h) que reciba por referencia la lista de tareas leídas desde el archivo binario, luego debe eliminar todas las tareas del cuadrante "eliminar" y cree un nuevo archivo binario con la lista sin las tareas del cuadrante.</br></br>
5. Desarrolle una función que reciba como parámetro una lista de tareas y escriba 4 archivos de texto (uno por cada cuadrante de la Matriz de Eisenhower) en donde cada línea representa una tarea. El formato de cada línea es `‹descripcion›: ‹tiempoEstimado>minutos`. Las líneas de estos archivos deben ir ordenadas de forma descendente según el estimado de tiempo (de la tarea que requiera menos tiempo a la tarea que requiera más tiempo). Tiene un ejemplo de cada uno de estos archivos en la raíz de este proyecto.