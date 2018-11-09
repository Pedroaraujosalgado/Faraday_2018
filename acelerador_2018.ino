//DIA 26/06 - Leitura de 0 - 100, funcionando.

const int pinAcel1 = A3; // Pino de entrada do sinal do Pot.Acelerador1 (ESQUERDA)
const int pinAcel2 = A4; // Pino de entrada do sinal do Pot.Acelerador2 (DIREITA)
int acel1   = 0;  // Variável Acelerador1 (0~100%)
int acel2   = 0;  // Variável Acelerador2 (0~100%)
float i = 0;
float j = 0;
float volts1 = 0;
float volts2 = 0;

void setup()
{
 Serial.begin(9600);
}  

void loop()
{
    acel1 = map(analogRead(pinAcel1), 40, 388, 9, 100); // Adequa a leitura do Acel1 de 0~100%   
    acel2 = map(analogRead(pinAcel2), 1002, 638, 0, 100); // Adequa a leitura do Acel1 de 0~100%   
    i=(float(analogRead(pinAcel1))); //Pega o valor real do Acel1 (0-1023)
    j=(float(analogRead(pinAcel2))); //Pega o valor real do Acel2 (0-1023)

    
      
    Serial.print("\n\nAcelerador 1: ") ; 
    Serial.print("Valor do Sensor: "); Serial.print(i); //Vai escrever o valor lido por Acel1
    Serial.print("\nPorcentagem: "); Serial.print(acel1); //Vai escrever a porcentagem de Acel1
    
    Serial.print("\n\nAcelerador 2: "); 
    Serial.print("Valor do Sensor: "); Serial.print(j); //Vai escrever o valor lido por Acel2
    Serial.print("\nPorcentagem: "); Serial.print(acel2); //Vai escrever a porcentagem de Acel2

    Serial.print ("\n\n=============================================================================");
    delay(2000);
  
}
