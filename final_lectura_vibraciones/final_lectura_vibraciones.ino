#include <Adafruit_TinyUSB.h>

const int pinPiezo = A0; //Pin al que está conectado el sensor

//Filtro, esto ayuda a ajustar la sensibilidad del sensor
int nivelReposo = 0;               //Se utiliza para que no inicie midiendo
const int UMBRAL_RUIDO = 53;      //Variable para ajustar la sensibilidad, siendo mayor numero menos sensible

const int IMPACTOS_NECESARIOS = 10;             //Mordiscos de larva necesarios para dar llamada de atención
const long VENTANA_TIEMPO = 60000;    //Ventana de tiempo que se activa cuando detecta una mordida si pasan 30seg y no se han completado las 10 mordidas necesarias, no lo toma como ataque
const long TIEMPO_REFRACTARIO = 250;  //Pausa de 0.25s tras un golpe para no contarlo doble, ya que la placa es bastante rápida

int contadorImpactos = 0; //contador de mordiscos
unsigned long tiempoPrimerImpacto = 0; 
unsigned long ultimoImpacto = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }  //delay para que tarde un poco hasta que se abre el Monitor Series
  
  analogReadResolution(12);

  Serial.println("INICIANDO CALIBRACIÓN SÍSMICA");
  
  //auto-calibrado-leemos el silencio para calibrar y evitar leer por error electricidad estática o algo por el estilo
  long suma = 0;
  for(int i = 0; i < 500; i++) {
    suma += analogRead(pinPiezo);
    delay(2);
  }
  nivelReposo = suma / 500;
  
  Serial.print("Calibración OK");
  Serial.println(nivelReposo);
  Serial.println("Comienza la lectura");
  Serial.println("==============================================");
}

void loop() {
  //Piezoelectrico lee la vibración
  int lectura = analogRead(pinPiezo);
  
  //Calcula la fuerza, con esto podemos ajustar la sensibilidad
  int amplitud = abs(lectura - nivelReposo);

  //Si el golpe super el umbral (sensibilidad) se guarda
  if (amplitud > UMBRAL_RUIDO) {
    unsigned long ahora = millis();

    //Filtro anti-rebote, comprobamos si ha pasado suficiente tiempo desde el último golpe
    if (ahora - ultimoImpacto > TIEMPO_REFRACTARIO) {
      
      //Si es el primer golpe de la serie, empieza a contar
      if (contadorImpactos == 0) {
         tiempoPrimerImpacto = ahora; 
      }
      
      contadorImpactos++;
      ultimoImpacto = ahora;

      Serial.print("Posible mordida - Fuerza: ");
      Serial.print(amplitud);
      Serial.println("  (" + String(contadorImpactos) + "/" + String(IMPACTOS_NECESARIOS) + ")");

      // Evaluar alarma
      if (contadorImpactos >= IMPACTOS_NECESARIOS) {
        Serial.println("--------------------------------------------------");
        Serial.println("Patrón de masticación detectado, posible larva dentro de la palmera");
        Serial.println("--------------------------------------------------");
        
        contadorImpactos = 0; //Reset tras dar la alarma
        delay(1000); //Pausa para leer el mensaje
      }
    }
  }

  //Si dimos un golpe, pero pasaron VENTANA_TIEMPO segundos sin llegar a los IMPACTOS_NECESARIO, es falsa alarma.
  if (contadorImpactos > 0 && (millis() - tiempoPrimerImpacto > VENTANA_TIEMPO)) {
    Serial.println("Fin de la ventana de tiempo. Volviendo a escuchar");
    contadorImpactos = 0;
  }
}
