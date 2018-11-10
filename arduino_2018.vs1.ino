/* Cédigo arduino Faraday Racing - 2018
 * 
 * 
 * 
 * 
 * 
 */

// PINOS
// Analogico
const int pinAcel1    = A3;                                  
const int pinAcel2    = A4;
const int pinCorrente = A0;
const int pinFreio    = A5;

// Digital
const int pinRTD = 5;                                             // Pino de entrada do sinal RTD
const int pinFBair = 13;                                          // Pino de entrada do sinal do feedback AIR
const int pinSirene =12;                                          // Pino Sirene
const int pinShtd = 11;                                           // Pino comando Relé de shutdown                                * 
const int pinSeatswitch = 4;                                      // Pino de saida do Seatswitch 
const int pinFootswitch = 2;                                      // Pino de saida do Footswitch
const int pinLedRTD = 7;                                          // Pino da led RTD  
const int pinLedShtd = 8;                                         // Pino led Shutdown
const int pinMotor    = 3;                                        // Pino do sinal PWM do motor


// Variáveis de input e output 
int acel1   = 0;                                                  // Variável Acelerador1 (0~100%)
int acel2   = 0;                                                  // Variável Acelerador2 (0~100%)
int motor   = 0;                                                  // variavel PWM pro motor
int shtdout = 0;                                                  // Variável de indicação de Shutdown externo
int diferenca = 0;                                                // Variavel que ve a diferenca de Acel1 e Acel2
int freio = 0;                                                    // Variavel freio
int estadoBrk = 0;                                                // Variavel com valor do freio

// Variáveis de limite

const int delaySirene = 1500; // Tempo em que a sirene fica ligado (milissegundos)

// Variáveis de estado
boolean feedbackAIR = 0;            // estado do FeedBack AIR
boolean estadoRTD = 0;              // estado do RTD
boolean shtdE = 0;                  // estado do sht Externo
boolean shtd = 0;                   // Variável de controle do shutdown

// Variáveis de tempo
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
  pinMode (pinRTD         ,INPUT);
  pinMode (pinFBair       ,INPUT);
  
  
  pinMode (pinSirene         ,OUTPUT);
  pinMode (pinShtd           ,OUTPUT);
  pinMode (pinSeatswitch     ,OUTPUT);
  pinMode (pinFootswitch     ,OUTPUT);
  pinMode (pinLedRTD         ,OUTPUT);
  pinMode (pinLedShtd        ,OUTPUT);

  Serial.begin(9600);                               //inicia o envio de dados pela porta serial a 9600 bits/s

}

void loop()
{
  feedbackAIR = digitalRead(pinFBair);              // Lê estado do feedback AIR

  if(feedbackAIR == HIGH)                           // Se feedbackAIR estiver ligado vai entrar no if
  {
    estadoBrk = analogRead(pinFreio);                  // Lê se o freio esta acionado ou não
    digitalWrite(pinSeatswitch, HIGH);              // fecha a seatswitch
    estadoRTD = digitalRead(pinRTD);                // Lê estado do botão RTD
    if(estadoRTD == HIGH && estadoBrk > 100)                            // se o pino RTD estiver ligado
    {
      digitalWrite(pinFootswitch, HIGH);            // fecha o footswitch
      digitalWrite(pinSirene, HIGH);                // Liga a Sirene
      digitalWrite(pinLedRTD, HIGH);                // Acende o LED do RTD
      delay(delaySirene);
      digitalWrite(pinSirene, LOW);                 // Desliga Sirene
      digitalWrite(pinLedRTD, LOW);                 // Desliga a LED

      while(1)                                      // loop infinito onde vai pegar os valores dos sensores do acelerador
      {
       feedbackAIR = digitalRead(pinFBair);
       acel1 = map(analogRead(pinAcel1), 0, 1023, 0, 100); // Adequa a leitura do Acel1 de 0~255 valor da porta PWM
       acel2 = map(analogRead(pinAcel2), 0, 1023, 0, 100); // Adequa a leitura do Acel2 de 0~255 valor da porta PWM
       motor = (acel1+acel2)/2;                            // pega a media de acel1 e acel2 
       analogWrite (pinMotor,motor);
       diferenca = (acel1 - acel2)*(acel1 - acel2);
       freio = analogRead(pinFreio);
       //========================================================================================================================================================
       // PLAUSIBILIDADE
       
     
       if(diferenca >= 100)                            // Se Acel1 e Acel2 tiverem uma diferença de 10 
       {
        shtd = shtd + 1;
        shtdout = 1;
        digitalWrite(pinSeatswitch, LOW);
        digitalWrite(pinLedShtd, shtd);
        break;                   
       }
       if(acel1 > 100 || acel1 < 0)
       {
        shtd = 1;
        shtdout = 1;
        digitalWrite(pinSeatswitch, LOW);
        digitalWrite(pinLedShtd, shtd);
        break;
       }
         if(acel2 > 100 || acel2 < 0)
       {
        shtd = 1;
        shtdout = 1;
        digitalWrite(pinSeatswitch, LOW);
        digitalWrite(pinLedShtd, shtd);
        break;
       }
       /*
       if(freio < 100 || freio > )// MEDIR O QUE CHEGA 2 sensore freio //nao funciona
       {
        shtd = 1;
        shtdout = 1;
        digitalWrite(pinSeatswitch, LOW);
        digitalWrite(pinLedShtd, shtd);
        break;
       }
       */
       if(feedbackAIR) //Se feedbackAIR estiver desligado durante a aceleracao
       {
        shtd=1;
        shtdout = 1;
        digitalWrite(pinSeatswitch, LOW);
        digitalWrite(pinLedShtd, shtd);
        break;
       }
       //==========================================================================================================================================================
       
      }
      
        analogWrite(pinMotor, 0);                         // Envia 0 de PWM pro motor 
              
      }
  
  }else{
        digitalWrite(pinSeatswitch, LOW);            // abre a seatswitch
        digitalWrite(pinFootswitch, LOW);            // abre o footswitch 
        digitalWrite(pinLedShtd,    LOW);    
       }
  
}
