#include <Keypad.h>
#include <Servo.h>
#define LED_VERDE 12
#define LED_ROJO 13

Servo pestillo;
const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'A', '9', '5', '1'},
  {'B', '0', '6', '2'},
  {'C', '*', '7', '3'},
  {'D', '#', '8', '4'}
};
byte pinesFilas[FILAS] = {2, 3, 4, 5};
byte pinesColumnas[COLUMNAS] = {6, 7, 8, 9};
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

String clave = "1234";  //Cambiar aquí la clave
String entrada = "";
int ALARM_SOUND = 11;

void setup(){
  pestillo.attach(10);
  pestillo.write(90);  // Pocision inicial CERRADO  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(ALARM_SOUND, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  char tecla = teclado.getKey();

  if (tecla){
    Serial.print("Tecla presionada: ");
    Serial.println(tecla);

    if (tecla == '#'){  //tecla para comfirmar
    if (entrada == clave){
      abrirCaja();
    } else {
      errorClave();
    }
    entrada = "";
    } else if (tecla == '*'){ // borrar
      entrada = "";
    } else {
      entrada += tecla;
    }        
  }
}

void abrirCaja(){
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_ROJO, LOW);
  pestillo.write(0);
  for (int i=0; i<5; i++){
    digitalWrite(ALARM_SOUND, HIGH);
    delay(100);
    digitalWrite(ALARM_SOUND, LOW);
    delay(100);
  }
  delay(3000); //Modificar tiempo abierto aqui
  pestillo.write(90);
  digitalWrite(LED_VERDE, LOW);
}

void errorClave(){
  for (int i = 0; i < 3; i++){
    digitalWrite(LED_ROJO, HIGH);
  for (int i=0; i<2; i++){
    digitalWrite(ALARM_SOUND, HIGH);
    delay(50);
    digitalWrite(ALARM_SOUND, LOW);
    delay(100);
  }
    delay(200);
    digitalWrite(LED_ROJO, LOW);
    delay(200);
  }
}


