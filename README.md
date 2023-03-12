# Laboratório 01

O sistema descrito consiste em um microcontrolador ESP32 conectado a um microfone e um display de 7 segmentos. O objetivo do sistema é capturar o sinal de áudio do microfone, identificar a frequência dominante e exibir essa frequência no display de 7 segmentos.

Para garantir que o sistema atenda aos requisitos de tempo real, foi implementado um executivo cíclico que separa as tarefas em intervalos de tempo fixos e garante que cada tarefa seja executada dentro do prazo estabelecido.

### Obejetivo

A implementação de um executivo cíclico em um sistema em tempo real, como o descrito (ESP32 conectado a um microfone e um display de 7 segmentos), é importante para garantir que as tarefas sejam executadas em um intervalo de tempo pré-determinado e atendam aos requisitos de tempo real do sistema.

O objetivo de um sistema com executivo cíclico é garantir que as tarefas sejam executadas dentro de um determinado prazo, evitando atrasos que possam prejudicar a performance e a eficiência do sistema. Isso é especialmente importante em sistemas em tempo real, que precisam responder rapidamente a eventos externos e realizar tarefas críticas em um prazo definido.

Ao implementar um executivo cíclico, o sistema é capaz de separar as tarefas em intervalos de tempo fixos e garantir que cada tarefa seja executada dentro do prazo estabelecido. Isso ajuda a reduzir a latência e o tempo de resposta do sistema, melhorando sua eficiência e confiabilidade.

Além disso, a implementação de um executivo cíclico facilita a manutenção e a evolução do sistema, pois as tarefas estão organizadas em intervalos de tempo fixos e bem definidos, tornando mais fácil a identificação e a correção de possíveis falhas ou problemas de desempenho.

Em resumo, a implementação de um executivo cíclico é fundamental em sistemas em tempo real, pois garante que as tarefas sejam executadas dentro de um intervalo de tempo fixo, melhorando a eficiência, a confiabilidade e a manutenção do sistema.

### Arquitetura
Interface com o usuário: Camada responsável pela interação do usuário com o sistema, como a entrada do sinal de áudio do microfone e a exibição da frequência dominante no display de 7 segmentos. Implementada utilizando as bibliotecas adequadas do ESP32 para capturar o sinal de áudio do microfone e enviar os dados para a camada intermediária de lógica de negócios.

Lógica de negócios: Essa camada seria responsável por processar os dados recebidos da camada de interface com o usuário e determinar a frequência dominante do sinal de áudio. Implementada utilizando uma biblioteca de processamento de sinal, como a biblioteca Fast Fourier Transform (FFT), que permite analisar o espectro de frequência do sinal de áudio e identificar a frequência dominante.

Camada de dados: Camada seria responsável por gerenciar o armazenamento e a recuperação dos dados do sistema. Nesse caso, não é necessário armazenar dados em um banco de dados ou em outro tipo de repositório, pois a frequência dominante será exibida diretamente no display de 7 segmentos.

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

### Executivo Ciclico

Pelos códigos de display_tempos e microfone_1_tempos foram calculados o tempo de execução dos algoritmos. A captação do audio e aplicação da FFT dura 31ms, o display dos valores dura 12ms. Para as duas execuções são 43ms. Um executivo de 50ms seria adequado ao sistema, e esse valor foi aplicado.

```
   |<-------------------------- Ciclo de 50ms --------------------------->|
   |<-- Execução (31ms) -->|
                           |<---- Exibição (12ms) ---->|
                                                       |<- Resto (7ms) ->|

```
   
### Demonstração

A demonstração abaixo mostra testes de sons vocais e sua identificação no display.

https://user-images.githubusercontent.com/50549048/224558280-c741ed49-0383-4163-88b0-18791d5b31ca.mp4

Futuro: realizar demonstração em ambiente de isolamento acustico com produção de frequencia em gerador. 



