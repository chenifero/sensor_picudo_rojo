🌴 Picudo-IoT: Sistema de Detección Temprana Sísmica
Este proyecto desarrolla un sensor inteligente de bajo coste para la detección precoz del Picudo Rojo (Rhynchophorus ferrugineus) en palmeras. Utiliza un sensor sísmico de contacto y procesamiento de señal en el borde (Edge Computing) para identificar patrones de masticación larval antes de que el daño sea visible.

🚀 Características Principales
Detección Sísmica: Filtro de vibraciones de alta sensibilidad mediante disco piezoeléctrico de latón.

Algoritmo de Confirmación: Sistema basado en ráfagas de impulsos dentro de ventanas de tiempo para eliminar falsos positivos.

Conectividad BLE: Transmisión de alertas y estado de batería vía Bluetooth Low Energy.

Web-App Dashboard: Interfaz de monitoreo en tiempo real accesible desde el navegador (Chrome/Edge) sin necesidad de instalación.

Eficiencia Energética: Monitoreo inteligente del voltaje de batería Li-ion 18650.

🔬 Base Científica y Teórica
El diseño del dispositivo se fundamenta en estudios empíricos del IVIA (Instituto Valenciano de Investigaciones Agrarias) y publicaciones recientes sobre manejo sísmico de plagas:

Firma Acústica: La actividad de alimentación de las larvas se concentra en el rango de 2.210 Hz a 2.290 Hz. En estados avanzados (fase pupa), el sonido asciende al rango de 2.400 Hz - 2.600 Hz.

Selectividad: El sistema diferencia al Picudo de otros artrópodos (hormigas, arañas, cochinillas) que operan en frecuencias superiores a los 5.500 Hz.

Acoplamiento Sísmico: Se recomienda el uso de un tornillo de acero de entre 6 cm y 12 cm insertado en el tronco para captar vibraciones internas con un radio de detección de hasta 130 cm a lo largo del estípite.

🛠️ Hardware Necesario
Microcontrolador: Seeed Studio XIAO nRF52840 Sense.

Sensor: Disco piezoeléctrico de latón (conectado a pin A0).

Batería: Celda Li-ion 18650 (con soporte para lectura de voltaje mediante VBAT_ENABLE).

Sonda: Tornillo de acero galvanizado (8-10 cm).

💻 Algoritmo de Software
El código implementa una lógica de procesamiento rápida para capturar eventos de lectura positiva (PRE):

Calibración Inicial: Cálculo del "DC Offset" (nivel de reposo) durante 1 segundo para aislar el ruido eléctrico de la lectura sísmica.

Filtro Anti-Rebote: Tiempo refractario de 250ms tras cada impacto detectado para evitar el conteo múltiple de una misma vibración.

Confirmación por Eventos: Requiere un número mínimo de impactos (ej. 10) dentro de una ventana de tiempo (ej. 60 seg) para activar la alarma real.

📱 Visualización (Web Bluetooth)
La aplicación web permite conectar con el dispositivo de forma inalámbrica:

Muestra el porcentaje de batería real.

Contador de impactos detectados en la ventana activa.

Alerta visual de "Larva Detectada" en caso de confirmación de patrón.

ODS 12 (Producción Responsable): Permite tratamientos curativos focalizados, reduciendo el uso masivo de insecticidas químicos preventivos.

ODS 15 (Vida de Ecosistemas Terrestres): Control de especies invasoras y protección de la flora local.
