# Sistema de Votación (SDL2)
## por Juan Ignacio Elosegui

Aplicación gráfica simple desarrollada en **C con SDL2** que simula un sistema de votación con dos candidatos.  
El programa abre una ventana interactiva donde el usuario puede votar haciendo click sobre botones asociados a cada candidato.

Este proyecto está pensado como práctica de manejo de eventos, renderizado 2D y estructura básica de una aplicación gráfica con SDL2.

---

## Descripción

El sistema recibe los nombres de dos candidatos como argumentos al momento de ejecutar el programa.  
Cada candidato es representado por un botón dentro de la ventana. Al hacer click sobre un botón, se registra un voto y el conteo se muestra por consola.

La aplicación corre en un loop principal que gestiona eventos de teclado, mouse y cierre de ventana, y renderiza continuamente la interfaz gráfica.

---

## Uso

El programa debe ejecutarse desde la consola pasando dos parámetros obligatorios:

- Nombre del primer candidato
- Nombre del segundo candidato

Si no se proporcionan ambos parámetros, el programa finaliza mostrando un mensaje de uso correcto.

---

## Controles

- Click izquierdo del mouse  
  Registra un voto para el candidato seleccionado.

- Tecla **R**  
  Reinicia el conteo de votos.

- Tecla **ESC**  
  Cierra la aplicación.

- Cerrar la ventana  
  Finaliza el programa de forma segura.

---

## Funcionamiento general

- Se inicializa SDL y se crea una ventana de 900x600 píxeles.
- Se crea un renderer acelerado con sincronización vertical.
- Se definen dos botones como rectángulos interactivos.
- Se detectan clicks del mouse dentro de cada botón.
- El conteo de votos se mantiene en memoria y se imprime por consola.
- El renderizado se ejecuta independientemente del manejo de eventos.

---

## Dependencias

- SDL2

Es necesario tener la librería SDL2 instalada para compilar y ejecutar el programa.

---

## Estructura

El programa está contenido en un único archivo fuente y sigue una estructura clásica:

- Inicialización
- Loop principal
- Manejo de eventos
- Renderizado
- Liberación de recursos

Esto facilita su extensión hacia proyectos más grandes o modularizados.

---

## Posibles extensiones

- Mostrar los nombres de los candidatos dentro de los botones usando SDL_ttf.
- Mostrar el conteo de votos en pantalla.
- Agregar confirmación visual del voto.
- Guardar resultados en archivo.
- Separar la lógica en múltiples archivos.
- Mejorar el diseño visual y la accesibilidad.

---

## Notas

Este proyecto tiene fines educativos y sirve como base para experimentar con interfaces gráficas simples en C utilizando SDL2.

