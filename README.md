--Detector IoT Sísmico: Picudo Rojo (Red Palm Weevil)--
Un dispositivo IoT de bajo coste y código abierto diseñado para la detección temprana de la larva de Picudo Rojo (Rhynchophorus ferrugineus) en palmeras. Utiliza sensores de contacto sísmico para alertar sobre patrones de masticación de larvas en el interior del tronco antes de que el árbol sufra daños irreversibles.

--El Problema--
El Picudo Rojo es una plaga letal y silenciosa. Las hembras depositan sus huevos en el interior de la palmera y las larvas devoran el estípite (tronco) desde dentro. Cuando los síntomas visuales (hojas caídas, corona marchita) aparecen, la palmera suele ser irrecuperable. La única forma de salvar el árbol es detectar el sonido de las larvas alimentándose en las primeras semanas de infestación.

--Base Científica--
El algoritmo y el diseño físico de este proyecto no son experimentales; están respaldados por literatura científica de primer nivel en agronomía:

Huella Acústica (IVIA, 2008): El patrón de masticación de las larvas tiene una firma clara en el rango de los 2210 Hz - 2290 Hz. En la fase de pupa, asciende a 2400 Hz - 2600 Hz. Otros insectos (hormigas, arañas) operan por encima de los 5500 Hz, lo que evita falsos positivos.

Acople Físico: El aire es un mal conductor. Para captar las ondas sísmicas sin pérdida de energía y minimizando el daño al árbol, la literatura recomienda insertar una sonda o tornillo de acero de entre 6 cm y 12 cm de profundidad en el tronco.

Gestión Sísmica y Filtro de Falsas Alarmas (Mendel et al., 2023): Los dispositivos comerciales más avanzados utilizan sensores sísmicos y algoritmos que cuentan "ráfagas de impulsos" en ventanas de tiempo específicas, ahorrando batería y descartando ruidos ambientales aislados.

--Hardware Necesario--
Microcontrolador: Seeed Studio XIAO nRF52840 Sense (Elegido por su procesador rápido y chip BLE integrado).

Sensor Sísmico: Disco Piezoeléctrico de latón (conectado al pin A0).

Antena Acústica: Un tirafondo/tornillo de acero galvanizado o inoxidable de 8-10 cm.

Alimentación: Batería Li-ion 18650 (3.7V nominales).

--Arquitectura del Software--
El código ha evolucionado de pesadas Transformadas de Fourier (FFT) a un Filtro de Impactos Sísmicos ultrarrápido y de bajo consumo:

Auto-Calibrado (DC Offset): Al encenderse, la placa lee el nivel eléctrico de reposo durante 1 segundo para establecer su "centro de gravedad".

Medición de Amplitud: Lee los picos de vibración crudos saltándose matemáticas complejas para ganar velocidad de muestreo.

Filtro Anti-Rebote: Aplica un "tiempo refractario" (ej. 250 ms) tras cada impacto para garantizar que un solo crujido largo no se cuente como múltiples mordiscos.

Ventana de Confirmación: Requiere registrar un número mínimo de impactos (ej. 3 crujidos) en una ventana de tiempo estricta (ej. 10 segundos). Si se cumple, dispara la alarma BLE; si no, resetea el contador asumiendo ruido ambiental.


--Instalación y Pruebas--
Si quieres probar el código en tu mesa sin taladrar una palmera:

Carga el código actual en la placa XIAO usando Arduino IDE.

Abre el Monitor Serie a 115200 baudios.

Espera 1 segundo en absoluto silencio para el auto-calibrado.

Apoya el piezoeléctrico en la mesa.

Apoya un espagueti seco en la mesa y rómpelo cerca del sensor. El monitor registrará un IMPACTO SÍSMICO.

Rompe 3 espaguetis en menos de 10 segundos para ver saltar la ALERTA CONFIRMADA.

Despliegue en Campo
Para probar en un entorno real:

Clava el tornillo de acero en un tocón o palmera sana.

Adhiere firmemente la chapa de latón del piezoeléctrico a la cabeza plana del tornillo (Usando superglue).

Introduce materia seca (palillos, nueces, fideos crudos) en un hueco cercano del tocón y tritúralos con un destornillador para simular la masticación de la larva.

--Escalabilidad--
[x] Ajuste de sensibilidad y ventana de tiempo en pruebas de laboratorio.

[ ] Pruebas acústicas destructivas en tocón real de palmera.

[ ] Fusión del algoritmo sísmico con el módulo de comunicación BLE (bluefruit.h).

[ ] Optimización de energía: Implementar modo Deep Sleep y despertares periódicos (ej. cada 24 horas) para alargar la vida de la batería a meses.

--Licencia--
Este proyecto es de código abierto. Siéntete libre de clonarlo, mejorarlo y usarlo para salvar palmeras en tu ciudad.
