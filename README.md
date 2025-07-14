# get_next_line_42

El objetivo es implementar una función en C capaz de leer una línea completa desde un descriptor de archivo, independientemente de la longitud de la línea, gestionando la memoria de manera eficiente.

# ¿Qué hace get_next_line?

Función principal: char *get_next_line(int fd);
Comportamiento: Cada vez que llamas a get_next_line, devuelve la siguiente línea (incluyendo el salto de línea \n si existe) leída del archivo representado por el descriptor fd. Cuando se alcanza el final del archivo, retorna NULL.

Lectura progresiva: No necesariamente lee todo el archivo de golpe; utiliza un buffer de tamaño fijo (por ejemplo, 42, 1024 bytes, etc.) para leer fragmentos y construir la línea completa poco a poco.

Manejo de múltiples archivos: Debe ser capaz de manejar varios descriptores de archivo abiertos al mismo tiempo, sin mezclar sus lecturas.

# Objetivo pedagógico

Gestión dinámica de memoria: Practicar el uso de malloc, free, gestión de leaks y evitar errores comunes de memoria.
Manejo de buffers y cadenas: Trabajas con buffers, concatenación de strings, y fragmentos para construir líneas.
Manejo de archivos y descriptores: Uso de funciones del sistema como read, comprensión de cómo funcionan los descriptores de archivos en Unix/Linux.
Gestión de estados entre llamadas: Aprender a mantener el estado entre llamadas a la función para cada archivo abierto (normalmente usando variables estáticas o estructuras).
Robustez y edge cases: Enfrentar casos límite como líneas extremadamente largas, archivos vacíos, errores de lectura, etc.

En resumen, get_next_line es un ejercicio pensado para fortalecer habilidades en C, especialmente en lo que respecta a la gestión de memoria, manipulación de archivos y desarrollo de funciones robustas y reutilizables.
