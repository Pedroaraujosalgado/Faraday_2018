# Faraday_2018

Este código tem o propósito fundamental de fornecer sinal de aceleração ao Inversor do Motor, levando em consideração
as plausibilidades.

Primeiramente, este código lê o sinal do FBAir se, o FBAir estiver ligado. Depois verifica se o freio está precionado,
com o sinal do freio ativo é ligado a seatswitch. Em seguida espera o sinal do botão do RTD, se o RTD, estiver ligado,
liga o footswitch, acionando a sirene e a led e começando as leituras dos aceleradores, freio e do sinal de um possível shutdown externo (FBAir)
devido à sistemas como IMD, BSPD, BMS, etc.

Em seguida, começam as checagens de plausibilidades uma a uma:
  1) Shutdown Externo (se o feedback air estiver desligado houve um Shtd Externo) 
  2) Diferença entre o sinal dos aceleradores maior que limDeltaAC
  

Uma vez que esse relé foi ativado, ele irá permanecer ativado, até que qualquer uma das 3 condições de shutdown
tornem-se verdade.

Com o relé ativado, o código faz um mapeamento da leitura do acelerador e passa esses valores com uma modulação
por largura de pulso (PWM) para o inversor.

Se houver sinal de shutdown, além de ser enviado um comando para o desligamento do relé, o sinal de PWM também é zerado.

