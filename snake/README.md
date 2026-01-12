# 🐍 Snake en C (SDL2)

Implementación del clásico juego **Snake** en lenguaje **C**, utilizando la biblioteca **SDL2** para gráficos, temporización y manejo de eventos.

El juego está construido sobre una **grilla lógica**, donde toda la lógica ocurre en coordenadas discretas (celdas) y el renderizado convierte esas coordenadas a píxeles.

---

## 🎮 Características

- Movimiento por grilla (no por píxeles).
- Tamaño de grilla configurable.
- La serpiente crece al comer manzanas.
- Las manzanas se generan en posiciones libres del tablero.
- Detección de colisiones contra los bordes.
- Detección de colisiones contra el propio cuerpo de la serpiente.
- Control mediante flechas del teclado.
- Velocidad constante controlada por tickrate.

---

## 🧱 Resolución y grilla

El juego utiliza una ventana de **900 × 600 píxeles** y una grilla cuadrada configurable.

La grilla divide la pantalla en un tablero lógico de **45 columnas por 30 filas**, donde cada celda representa una posición válida para la serpiente o la manzana.

Toda la lógica del juego ocurre en estas coordenadas de grilla, y solo al momento de dibujar se realiza la conversión a píxeles.

---

## 🐍 Modelo de datos

### Celda

Una celda representa una posición dentro del tablero lógico.  
Se utiliza para almacenar tanto las posiciones de la serpiente como de la manzana.

### Dirección

La dirección define hacia dónde se moverá la serpiente en el próximo tick del juego.  
Las direcciones posibles son arriba, abajo, izquierda y derecha.

No se permite invertir la dirección directamente para evitar colisiones instantáneas.

---

## 🍎 Lógica del juego

- La serpiente se almacena como una secuencia de celdas
- La cabeza de la serpiente siempre se encuentra en la primera posición
- En cada tick del juego ocurre lo siguiente:
  1. Se calcula la nueva posición de la cabeza según la dirección actual
  2. Se verifican colisiones con bordes y con el propio cuerpo
  3. Se inserta la nueva cabeza al inicio del cuerpo
  4. Si la cabeza coincide con la manzana, la serpiente crece
  5. Si no hay colisión con la manzana, la cola se descarta implícitamente

Las manzanas se generan en posiciones aleatorias que no estén ocupadas por la serpiente.

---

## 🖼️ Renderizado

En cada frame se realiza el siguiente orden de dibujo:

1. Limpieza de la pantalla
2. Dibujo de la grilla
3. Dibujo de la manzana
4. Dibujo de la serpiente
5. Presentación del frame en pantalla

La grilla es únicamente visual y no almacena estado del juego.

---

## ⏱️ Velocidad del juego

La velocidad del juego está controlada por un sistema de ticks, que define cuántos milisegundos deben pasar entre cada movimiento de la serpiente.

Reducir el intervalo entre ticks hace el juego más difícil.

---

## 🎮 Controles

Flecha arriba -> Mover hacia arriba
Flecha abajo -> Mover hacia abajo
Flecha izquierda -> Mover hacia la izquierda
Flecha derecha -> Mover hacia la derecha
Cerrar ventana -> Salir del juego

---

## 🧪 Compilación y ejecución

Para compilar el proyecto es necesario tener instalada la biblioteca **SDL2**.

El comando para compilar es ```gcc -o snake snake.c `sdl2-config --cflags --libs````.
Para ejecutar basta con correr ```./snake```.

El juego se compila como una aplicación de escritorio y se ejecuta desde consola.

---

## 🧠 Posibles mejoras

- Movimiento tipo wrap-around en los bordes
- Sistema de puntaje visible en pantalla
- Incremento progresivo de velocidad
- Pausa y reinicio del juego
- Efectos de sonido
- Menú inicial
- Guardado de récords

---

## ✍️ Autor

**Juan Ignacio Elosegui**

Proyecto educativo para aprender programación en **C** y desarrollo gráfico con **SDL2**.

---

## 📜 Licencia

Uso libre con fines educativos.
