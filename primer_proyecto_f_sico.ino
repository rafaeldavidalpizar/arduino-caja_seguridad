#include <Keypad.h>
#include <Servo.h>
#define LED_VERDE 12
#define LED_ROJO 13

Servo pestillo;
const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[FILAS] = {2, 3, 4, 5};
byte pinesColumnas[COLUMNAS] = {6, 7, 8, 9};
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

String clave = "1234";  //Cambiar aquí la clave
String entrada = "";

void setup(){
  pestillo.attach(10);
  pestillo.write(90);  // Pocision inicial CERRADO  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
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
  delay(3000); //Modificar tiempo abierto aqui
  pestillo.write(90);
  digitalWrite(LED_VERDE, LOW);
}

void errorClave(){
  for (int i = 0; i < 3; i++){
    digitalWrite(LED_ROJO, HIGH);
    delay(200);
    digitalWrite(LED_ROJO, LOW);
    delay(200);
  }
}


