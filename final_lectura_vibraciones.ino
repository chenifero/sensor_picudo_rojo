#include <Adafruit_TinyUSB.h>

const int pinPiezo = A0; 

// --- CONFIGURACIÓN DEL FILTRO SÍSMICO ---
int nivelReposo = 0;               // Se calculará automáticamente al arrancar
const int UMBRAL_RUIDO = 60;      // Fuerza mínima para considerarlo un "crujido" (ajústalo si es muy sensible)

// --- LÓGICA DE CONFIRMACIÓN (Estilo 2023) ---
const int IMPACTOS_NECESARIOS = 10;             // Golpes necesarios para confirmar plaga
const unsigned long VENTANA_TIEMPO = 30000;    // Tienen que darse en menos de 10 segundos
const unsigned long TIEMPO_REFRACTARIO = 250;  // Pausa de 0.25s tras un golpe para no contarlo doble

int contadorImpactos = 0;
unsigned long tiempoPrimerImpacto = 0;
unsigned long ultimoImpacto = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); } 
  
  analogReadResolution(12);

  Serial.println("==============================================");
  Serial.println("🌍 INICIANDO CALIBRACIÓN SÍSMICA...");
  
  // 1. AUTO-CALIBRADO: Leemos el silencio para encontrar el punto medio (DC Offset)
  long suma = 0;
  for(int i = 0; i < 500; i++) {
    suma += analogRead(pinPiezo);
    delay(2);
  }
  nivelReposo = suma / 500;
  
  Serial.print("✅ Calibración completada. Centro de gravedad: ");
  Serial.println(nivelReposo);
  Serial.println("🍝 MODO MESA: ¡Empieza a crujir espaguetis!");
  Serial.println("==============================================");
}

void loop() {
  // 2. LEER VIBRACIÓN CRUDA
  int lectura = analogRead(pinPiezo);
  
  // 3. CALCULAR LA FUERZA DEL GOLPE (Distancia desde el reposo)
  int amplitud = abs(lectura - nivelReposo);

  // 4. ¿SUPERAMOS EL UMBRAL DE RUIDO?
  if (amplitud > UMBRAL_RUIDO) {
    unsigned long ahora = millis();

    // 5. FILTRO ANTI-REBOTE: Comprobamos si ha pasado suficiente tiempo desde el último golpe
    if (ahora - ultimoImpacto > TIEMPO_REFRACTARIO) {
      
      // Si es el primer golpe de la serie, arrancamos el cronómetro
      if (contadorImpactos == 0) {
         tiempoPrimerImpacto = ahora; 
      }
      
      contadorImpactos++;
      ultimoImpacto = ahora;

      Serial.print("💥 IMPACTO SÍSMICO! Fuerza: ");
      Serial.print(amplitud);
      Serial.println("  (" + String(contadorImpactos) + "/" + String(IMPACTOS_NECESARIOS) + ")");

      // 6. ¡EVALUAR SI HAY ALARMA!
      if (contadorImpactos >= IMPACTOS_NECESARIOS) {
        Serial.println("--------------------------------------------------");
        Serial.println("🚨 ¡ALERTA CONFIRMADA! Patrón de masticación detectado.");
        Serial.println("--------------------------------------------------");
        
        contadorImpactos = 0; // Reseteamos tras dar la alarma
        delay(1000); // Pausa larga para que leas el mensaje
      }
    }
  }

  // 7. LIMPIAR EL HISTORIAL SI PASA MUCHO TIEMPO
  // Si dimos un golpe, pero pasaron 10 segundos sin llegar a los 3 necesarios, es falsa alarma.
  if (contadorImpactos > 0 && (millis() - tiempoPrimerImpacto > VENTANA_TIEMPO)) {
    Serial.println("⏳ Fin de la ventana de tiempo. Descartado como ruido aleatorio.");
    contadorImpactos = 0;
  }
  
  // El loop gira a toda velocidad para no perderse ni un solo pico de sonido
}
