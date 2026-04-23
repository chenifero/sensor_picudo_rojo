<div align="center">

# 🌴 Sensor Picudo Rojo — Detector IoT Sísmico

**Detección temprana de la larva del Picudo Rojo (*Rhynchophorus ferrugineus*) en palmeras mediante vibraciones sísmicas.**

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Bluetooth](https://img.shields.io/badge/BLE-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![License](https://img.shields.io/badge/Licencia-Open%20Source-brightgreen?style=for-the-badge)

</div>

---

## 🧠 ¿Qué es esto?

El **Picudo Rojo** es una plaga devastadora y silenciosa. Las larvas devoran el interior de las palmeras antes de que aparezca cualquier síntoma visual. Cuando el árbol muestra señales externas, ya suele ser irrecuperable.

Este proyecto es un **dispositivo IoT de bajo coste** que escucha las vibraciones sísmicas dentro del tronco de la palmera para detectar la masticación de las larvas en etapas tempranas, cuando aún se puede actuar.

---

## 🔬 Base Científica

El algoritmo está respaldado por estudios del **IVIA (Instituto Valenciano de Investigaciones Agrarias)**:

| Fase | Frecuencia detectada |
|------|---------------------|
| 🐛 Larva activa | 2.210 Hz — 2.290 Hz |
| 🦋 Fase pupa | 2.400 Hz — 2.600 Hz |
| 🐜 Otros insectos (falsos positivos) | > 5.500 Hz |

> El sistema discrimina automáticamente entre el Picudo y otros artrópodos gracias a esta diferencia de frecuencia.

---

## ⚙️ Hardware Necesario

| Componente | Detalle |
|---|---|
| 🖥️ Microcontrolador | Seeed Studio XIAO nRF52840 Sense |
| 📡 Sensor | Disco piezoeléctrico de latón (pin A0) |
| 🔋 Batería | Celda Li-ion 18650 (3.7V) |
| 🔩 Sonda | Tornillo de acero galvanizado (8–10 cm) |

---

## 💻 ¿Cómo funciona el software?

```
1. Auto-Calibrado     →  Mide el "silencio" durante 1 seg al encender
2. Filtro Anti-Rebote →  250 ms de espera entre impactos (evita contar uno solo como varios)
3. Ventana de Tiempo  →  Requiere N impactos dentro de X segundos para confirmar la alarma
4. Alerta BLE         →  Si se confirma el patrón, envía notificación vía Bluetooth
```

---

## 📱 Dashboard Web (Web Bluetooth)

Sin instalación. Solo abre el navegador y conecta vía BLE:

- 🔋 Porcentaje real de batería
- 💥 Contador de impactos sísmicos en tiempo real
- 🚨 Alerta visual **"Larva Detectada"** cuando se confirma el patrón

> Compatible con **Chrome** y **Edge**.

---

## 🧪 Prueba Rápida (sin palmeras)

1. Carga el código en la placa con **Arduino IDE**
2. Abre el Monitor Serie a **115200 baudios**
3. Espera 1 seg en silencio → auto-calibrado
4. Apoya el piezoeléctrico en una mesa
5. Rompe **3 espaguetis secos** en menos de 10 segundos cerca del sensor
6. ✅ Verás la **ALERTA CONFIRMADA** en el monitor

---

## 🗺️ Hoja de Ruta

- [x] Filtro sísmico de impulsos calibrado en laboratorio
- [x] Lectura de batería Li-ion integrada
- [ ] Fusión del algoritmo con el módulo BLE (bluefruit.h)
- [ ] Pruebas destructivas en tocón real de palmera
- [ ] Modo Deep Sleep para alargar vida de batería a meses

---

## 🌍 Impacto y Sostenibilidad

| ODS | Contribución |
|-----|-------------|
| ♻️ ODS 12 — Producción Responsable | Reduce el uso masivo de insecticidas al focalizar el tratamiento |
| 🌿 ODS 15 — Vida Terrestre | Protege la flora local controlando especies invasoras |

---

<div align="center">

**Proyecto de código abierto — úsalo, mejóralo y salva palmeras en tu ciudad. 🌴**

</div>
