# Ahorcado en C
Juego clásico del **Ahorcado**, implementado en **C** y en español, que selecciona palabras aleatorias desde un diccionario externo y permite al usuario adivinarlas letra por letra antes de quedarse sin vidas.

El proyecto está pensado como ejercicio práctico de manejo de archivos, strings, control de flujo y validación de entrada en C.

---

## Descripción

El programa selecciona una palabra al azar desde un archivo de diccionario y muestra su longitud mediante guiones bajos.  
El jugador debe ingresar letras individuales para intentar descubrir la palabra oculta.

- Cada letra incorrecta consume una vida.
- Las letras repetidas no descuentan vidas, pero se rechazan.
- El juego termina cuando el jugador adivina la palabra o se queda sin vidas.
- El juego se repite por rondas consecutivas.

---

## Características principales

- Selección aleatoria de palabras desde archivo.
- Validación de entrada del usuario.
- Control de letras ya utilizadas.
- Visualización progresiva de la palabra.
- Número fijo de vidas por ronda.
- Múltiples rondas por ejecución.
- Código modularizado en funciones pequeñas y claras.
- Compatible con diccionarios grandes (más de 100.000 palabras).

---

## Diccionario

El juego utiliza un archivo externo llamado `diccionario.txt`, que debe contener **una palabra por línea**.

### Codificación del diccionario

El diccionario fue convertido de **UTF-8 a US-ASCII** para eliminar tildes y caracteres especiales, evitando problemas al comparar caracteres en C.

La conversión se realizó utilizando la herramienta `iconv` desde la terminal.

Créditos por la ayuda en este proceso a **@pmt** en Stack Overflow.

---

## Selección de palabra aleatoria

La palabra se elige recorriendo el archivo completo para contar la cantidad de líneas y luego seleccionando una línea al azar.

Este enfoque está basado en una respuesta de Stack Overflow:

- Source: https://stackoverflow.com/a/20774074  
- Autor: Farouq Jouti  
- Licencia: CC BY-SA 3.0  

Los créditos se mantienen explícitamente en el código fuente.

---

## Reglas del juego

- Solo se aceptan letras del alfabeto inglés (`a-z`).
- No se permiten números, símbolos ni espacios.
- Las letras ingresadas no distinguen entre mayúsculas y minúsculas.
- Cada letra incorrecta resta una vida.
- El jugador gana cuando no quedan letras ocultas.
- El jugador pierde cuando se queda sin vidas.

---

## Estructura general

El programa está organizado en funciones independientes para:

- Lectura y depuración del diccionario.
- Limpieza de saltos de línea.
- Validación de letras ingresadas.
- Actualización del estado visible de la palabra.
- Detección de condición de victoria.
- Control de rondas y vidas.

Esto facilita la lectura, el mantenimiento y la extensión futura del juego.

---

## Posibles mejoras futuras

- Dibujar el ahorcado en ASCII.
- Mostrar las letras ya utilizadas.
- Permitir adivinar la palabra completa.
- Ajustar dificultad según longitud de la palabra.
- Soporte para otros diccionarios o idiomas.
- Guardar estadísticas de partidas.

---

## Cómo compilar

En tu consola tenés que poner:
`gcc -Wall -Wextra -g -o hangman hangman-es.c && ./hangman`

Van a salir advertencias acerca de funciones que no se usan (como `cat ()` para propósitos de debugging) pero no es un problema relevante.

Si no querés que moleste, podés poner el comando:
`gcc -o hangman hangman-es.c && ./hangman`.

## Autor
Desarrollado por Juan Ignacio Elosegui.

Proyecto desarrollado como ejercicio personal en **C**, con fines educativos.

Inspirado en el juego clásico del Ahorcado y en soluciones compartidas por la comunidad de Stack Overflow.

