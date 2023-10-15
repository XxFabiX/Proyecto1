# Proyecto1
 Juego de cartas de Clash, Proyecto1Algoritmos

 
Descripción
Este es un juego de cartas de estrategia donde compites contra una IA. Tu objetivo es derrotar a la IA reduciendo sus puntos de vida a cero antes de que ella haga lo mismo contigo. Para lograrlo, tendrás que usar cartas de Guardianes, cada una con sus propias estadísticas y habilidades.

Reglas del Juego
Cada jugador (tú y la IA) tiene un monto de 15 cartas.
En cada turno, tanto el jugador como la IA eligen una carta de su mano para colocarla en la mesa
Solo las cartas en la mesa pueden usarse en el combate. Cada jugador elige una carta de la mesa para atacar a una carta de la mesa del oponente en su turno.
El daño infligido durante el combate se calcula restando la Defensa (PD) de la carta atacada del Ataque (PA) de la carta que ataca. Si el resultado es positivo, se resta de los Puntos de Vida (PV) de la carta atacada.
Cuando una carta en la mesa llega a 0 PV, se retira del juego y se reemplaza por una nueva carta del monto del jugador o la IA.
El juego continúa hasta que uno de los jugadores (tú o la IA) se queda sin puntos de vida.

Cómo Jugar
-Creación de Cartas: Puedes crear tus propias cartas de Guardianes antes de comenzar una partida. Cada carta tiene un nombre, un tipo (magos, vikingos, nigromantes o bestias), PV, PA y PD (Puntos de Vida, Puntos de Ataque y Puntos de Defensa). Estas cartas se agregan a tu mazo.
-Comenzar el Juego: Para comenzar una partida, asegúrate de tener al menos 6 cartas en tu mazo. Luego, inicia el juego y compite contra la IA.
-Turnos: El juego se juega por turnos. En tu turno, elige una carta de tu mano para colocarla en tu lado de la mesa. Luego, selecciona una de tus cartas en la mesa para atacar una carta en la mesa de la IA. Durante el turno de la IA, ella elegirá sus cartas y objetivos automáticamente.
-Historial: El juego registra las acciones realizadas en un historial. Puedes ver el historial en cualquier momento.
-Ganar o Perder: El juego continúa hasta que uno de los jugadores se queda sin puntos de vida. Si la IA se queda sin puntos de vida, ¡ganarás! Si tú te quedas sin puntos de vida, la IA ganará.

Personalización
Puedes personalizar el juego agregando tus propias cartas de Guardianes. Abre el archivo cartas.txt y sigue el formato para agregar nuevas cartas.

Créditos
Este juego fue desarrollado como un proyecto del curso Algoritmos y Estructuras de Datos. Puedes personalizar, agregar o eliminar cartas a tu manera. 
Alumno: Fabián Arévalo V.
