# Laboratório 01

O sistema descrito consiste em um microcontrolador ESP32 conectado a um microfone e um display de 7 segmentos. O objetivo do sistema é capturar o sinal de áudio do microfone, identificar a frequência dominante e exibir essa frequência no display de 7 segmentos.

Para garantir que o sistema atenda aos requisitos de tempo real, foi implementado um executivo cíclico que separa as tarefas em intervalos de tempo fixos e garante que cada tarefa seja executada dentro do prazo estabelecido.
### Materiais Utilizados

* ESP32 WROOM
* MICROFONE INMP441
* DISPLAY 0.56" 7-SEG LED 5463AS-F
* PLATAFORMA ARDUINOIDE
* BIBLIOTECAS: arduinoFFT, Adafruit_GFX, Adafruit_LEDBackpack
### Objetivo

A implementação de um executivo cíclico em um sistema em tempo real, como o descrito (ESP32 conectado a um microfone e um display de 7 segmentos), é importante para garantir que as tarefas sejam executadas em um intervalo de tempo pré-determinado e atendam aos requisitos de tempo real do sistema.

O objetivo de um sistema com executivo cíclico é garantir que as tarefas sejam executadas dentro de um determinado prazo, evitando atrasos que possam prejudicar a performance e a eficiência do sistema. Isso é especialmente importante em sistemas em tempo real, que precisam responder rapidamente a eventos externos e realizar tarefas críticas em um prazo definido.

Ao implementar um executivo cíclico, o sistema é capaz de separar as tarefas em intervalos de tempo fixos e garantir que cada tarefa seja executada dentro do prazo estabelecido. Isso ajuda a reduzir a latência e o tempo de resposta do sistema, melhorando sua eficiência e confiabilidade.

Além disso, a implementação de um executivo cíclico facilita a manutenção e a evolução do sistema, pois as tarefas estão organizadas em intervalos de tempo fixos e bem definidos, tornando mais fácil a identificação e a correção de possíveis falhas ou problemas de desempenho.

Em resumo, a implementação de um executivo cíclico é fundamental em sistemas em tempo real, pois garante que as tarefas sejam executadas dentro de um intervalo de tempo fixo, melhorando a eficiência, a confiabilidade e a manutenção do sistema.

### Arquitetura
Interface com o usuário: Rsponsável pela interação do usuário com o sistema, como a entrada do sinal de áudio do microfone e a exibição da frequência dominante no display de 7 segmentos. Implementada utilizando as bibliotecas adequadas do ESP32 para capturar o sinal de áudio do microfone e enviar os dados para a camada intermediária de lógica de negócios.

Lógica de negócios: Responsável por processar os dados recebidos da camada de interface com o usuário e determinar a frequência dominante do sinal de áudio. Implementada utilizando uma biblioteca de processamento de sinal, como a biblioteca Fast Fourier Transform (FFT), que permite analisar o espectro de frequência do sinal de áudio e identificar a frequência dominante.

Camada de dados: Responsável por gerenciar o armazenamento e a recuperação dos dados do sistema. Nesse caso, não é necessário armazenar dados em um banco de dados ou em outro tipo de repositório, pois a frequência dominante será exibida diretamente no display de 7 segmentos.

```
     +-------------------------+
     | Interface com o usuário |
     +-------------------------+
                    |
                    | Sinal de áudio
                    V
     +-------------------------+
     |   Lógica de negócios    |
     +-------------------------+
                    |
                    | Frequência dominante
                    V
     +-------------------------+
     |     Camada de dados     |
     +-------------------------+
                    |
                    | Exibir no display
                    V
            +-------------+
            | Display 7 seg|
            +-------------+


```
### Modelo de Três Camadas

Camada de Aplicação: esta camada é responsável pela lógica de negócios do sistema e inclui todas as funções e módulos necessários para executar as funcionalidades específicas do sistema. Nesse caso, a camada de aplicação ínclui a captura de áudio do microfone e as informações exibidas no display de 7 segmentos.

Camada de Firmware: esta camada é responsável pela comunicação com o hardware subjacente e inclui o firmware necessário para que o sistema interaja com o microfone e o display de 7 segmentos. A camada de firmware é responsável por garantir que os componentes de hardware funcionem corretamente e que as informações sejam transmitidas entre a camada de aplicação e o hardware subjacente de forma adequada. A captura do áudio a e comunicação com o display de 7 segmentos.

Camada de Hardware: esta camada é responsável pelos componentes físicos do sistema, incluindo o microfone, o display de 7 segmentos e o ESP32. A camada de hardware é responsável por garantir que os componentes funcionem corretamente e possam ser acessados pela camada de firmware e pela camada de aplicação.

```
_________________________________________________________
|                    Camada de Aplicação                 |
|________________________________________________________|
|                                                        |
| - Módulo de Captura de Áudio                           |
| - Módulo de Processamento de Áudio                     |
| - Módulo de Exibição de Informações no Display         |  
| - Módulo de Média Móvel                                |
|________________________________________________________|

_________________________________________________________
|                      Camada de Firmware                |
|________________________________________________________|
|                                                        |
| - Firmware do ESP32                                    |
| - Módulo de Comunicação com o Microfone (ADC)          |
| - Módulo de Comunicação com o Display de 7 Segmentos   |
|________________________________________________________|

_________________________________________________________
|                       Camada de Hardware               |
|________________________________________________________|
|                                                        |
| - Microfone                                            |
| - Display de 7 Segmentos                               |
| - ESP32                                                |
|________________________________________________________|

```
### Média Móvel

O algoritmo de média móvel é uma técnica estatística utilizada para suavizar uma série de dados ao longo do tempo. Ele calcula a média dos valores em um intervalo de tempo definido e, em seguida, desloca esse intervalo de tempo para o próximo conjunto de dados e recalcula a média. Esse processo é repetido até o final da série de dados.

Em uma captação de frequência, o algoritmo de média móvel é utilizado para suavizar as flutuações de frequência ao longo do tempo, evitando que os resultados sejam afetados por interferências eletromagnéticas ou outras fontes de ruído que podem causar flutuações na saída.

Para calcular a média móvel de uma série de frequências o algoritmo irá somar as frequências das ultimas 20 amostras e dividir por 20 - já que temos 20 amostras por segundo em nosso dispositvo ciclico de 50ms, o que daria uma boa suavização. Em seguida, ele irá deslocar o intervalo de tempo em 50ms segundo e recalcular a média com a nova amostra e excluindo a mais antiga.

Desse modo a aplicação desse algoritmo na captação de frequência ajudar a reduzir o ruído e as flutuações de frequência, fornecendo uma saída mais suave e estável. 

### Executivo Ciclico

Pelos códigos de ```display_tempos``` e ```microfone_1_tempos``` foram calculados o tempo de execução dos algoritmos. A captação do audio e aplicação da FFT dura 31ms, o display dos valores dura 1.7ms, e a media movél menos que 1ms. Para as três execuções são 33ms. Uma janela de execução de 33ms seria adequado ao sistema, entretanto o valor de 50 foi escolhido para melhor divisão do tempo.

```
   |<----------------------------------------- Ciclo de 50ms --------------------------------------------->|
   |<-------- Execução (31.789ms) --------->|
                                            |<- Media Movel. (0.07ms) ->|     
                                                                        |<-- Exibição (1.745ms) -->|


```
Em código é possível visualizar isso. A wait_for_interrupt() espera que o ciclo se complete antes de iniciar novamente as tarefas.
```
void loop() {
  wait_for_interrupt();           //Executivo ciclico
  double freq = processAudio();   //T1 - Processamento de audio, 31ms
  toDisplay(freq);                //T2 - Impressão no display, 12ms
  }
  
```
A implementação da interrupção com temporizador é feita com o método timerAttachInterrupt() tendo como parâmetros uma variável timer da
API do ESP32 e a função a ser executada a cada interrupção.

### Arquivos


```microfone_1``` Implementação de escuta do microfone. <br />
```microfone_1_display``` Implementação de escuta e exibição no display. <br />
```microfone_1_display_v2``` Implementação de escuta e exibição no display com executivo ciclico. <br />
```microfone_1_tempos``` Calculo do tempo do processamento do audio. <br />
```display_tempos``` Calculo do tempo da exibição no display. <br />
```timer_interrupt``` Função de interrumpção para implementar executivo ciclico. <br />
   
### Demonstração

A demonstração abaixo mostra aplicação de frequencia e sua identificação no display.
<p align="center">
     ![image](https://user-images.githubusercontent.com/50549048/225274532-f929eff4-85b0-4753-8084-1f4d786c7693.png)
</p>
 <br />
Futuro: realizar demonstração em ambiente de isolamento acustico com produção de frequencia em gerador. 



