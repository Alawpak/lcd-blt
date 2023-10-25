#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


const int RS = 12, E = 11, D4 = 9, D5 = 8, D6 = 7, D7 = 6;

SoftwareSerial bluetooth(2, 3);  // RX, TX
 
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);


const byte defaultMatrices[64] = {
  0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //0, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //1, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //2, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //3, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //4, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //5, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //6, 0
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, //7, 0
};

//INSERT 11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000,11111,00000,00000,00000,00000,00000,00000,00000


byte allMatrices[64]; // Almacena los datos de los caracteres personalizados

void setup() {
  lcd.begin(16, 2);  // Inicializa la pantalla LCD como 2x16
  lcd.clear();  // Borra la pantalla

  // Inicializa allMatrices con los datos por defecto
  memcpy(allMatrices, defaultMatrices, sizeof(defaultMatrices));

  // Crea los 8 caracteres personalizados
  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, allMatrices + i * 8);
  }

  // Imprime los caracteres personalizados en la pantalla
  lcd.setCursor(4, 0);  // Fila 0, columna 4
  for (int i = 0; i < 4; i++) {
    lcd.write((byte)i);
  }

  lcd.setCursor(4, 1);  // Fila 1, columna 4
  for (int i = 4; i < 8; i++) {
    lcd.write((byte)i);
  }

  Serial.begin(9600); // Inicializa la comunicación serial
}
void updateCustomCharacters() {
  String input = Serial.readStringUntil('\n');
  if (input.startsWith("INSERT ")) {
    input = input.substring(7); // Elimina la palabra "INSERT" y un espacio
    input.trim();
    //Serial.println("HOLA");

    // Divide la entrada en valores separados por comas
    String values[64];
    int count = 0;
    int startPos = 0;
    int endPos = 0;

    // Extrae los valores separados por comas
    while ((endPos = input.indexOf(',', startPos)) != -1) {
      //Serial.print(input.substring(startPos, endPos) + " ");
      values[count] = input.substring(startPos, endPos);
      startPos = endPos + 1;
      count++;
    }

    // Convierte los valores en bytes y almacénalos en allMatrices
    for (int i = 0; i < count && i < 64; i++) {
     //Serial.print(atoi(values[i].c_str()));

      allMatrices[i] = strtol(values[i].c_str(), NULL, 2);
      //allMatrices[i] = atoi(values[i].c_str());
    }

    // Actualiza los caracteres personalizados en la pantalla
    lcd.clear();
    for (int i = 0; i < 8; i++) {
      lcd.createChar(i, allMatrices + i * 8);
    }

    // Imprime los caracteres personalizados en la pantalla
    lcd.setCursor(6, 0);  // Fila 0, columna 5
    for (int i = 0; i < 4; i++) {
      lcd.write(i);
    }

    lcd.setCursor(6, 1);  // Fila 1, columna 5
    for (int i = 4; i < 8; i++) {
      lcd.write(i);
    }
  }
}
void loop() {
  updateCustomCharacters();
  
  // Tu código de loop aquí
}