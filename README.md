# Projeto LinkEdge: Monitoramento Ambiental Inteligente

## Descrição do Projeto
O **LinkEdge** é um sistema embarcado de monitoramento ambiental focado na detecção precoce de condições de risco em áreas críticas, como bacias hidrográficas, encostas e zonas de instabilidade. O sistema processa dados climáticos, de nível hídrico e de vibração do solo em tempo real, fornecendo diagnósticos visuais imediatos através de um display LCD e sinalização via LEDs.

## Objetivo da Solução
O **LinkEdge** foi desenvolvido para mitigar uma das falhas mais críticas em desastres naturais: o colapso da infraestrutura de comunicação. Em eventos como enchentes, deslizamentos e incêndios, torres de celular e redes de energia são frequentemente destruídas, isolando regiões remotas justamente quando a ajuda é mais necessária.

Nosso objetivo é fornecer um sistema de monitoramento resiliente e autônomo, focado em três pilares:

* **Resiliência via Rede Mesh:** Nós de sensores que se comunicam localmente, garantindo que a falha de um dispositivo não interrompa a coleta de dados de toda a região.
* **Conectividade Global (Satélite LEO):** Transmissão de alertas críticos em menos de 30 segundos, utilizando constelações de satélites de órbita baixa para superar o isolamento geográfico.
* **Inteligência para Resposta Rápida:** Fornecer à Defesa Civil, Bombeiros e gestores municipais dados em tempo real — incluindo localização GPS e nível de criticidade — permitindo decisões ágeis de evacuação e direcionamento preciso de equipes de resgate.

Em suma, o LinkEdge transforma dados de sensores locais em ações globais de resposta, convertendo o isolamento em conectividade e viabilizando, com precisão e agilidade, a proteção de vidas, a preservação de infraestruturas críticas e a continuidade das operações em áreas de risco.

## Componentes Utilizados
* **Microcontrolador:** Arduino Uno R3.
* **Sensor Climático:** DHT22 (Temperatura e Umidade).
* **Sensor de Nível:** HC-SR04 (Ultrassônico).
* **Sensor de Vibração/Sismo:** MPU6050 (Acelerômetro/Giroscópio).
* **Display:** LCD 16x2 com Módulo I2C.
* **Sinalização:** 3 LEDs RGB (um para cada nó).
* **Outros:** Jumpers, Protoboard e Resistores.

## Explicação do Funcionamento
O código opera através de três funções de avaliação (`avaliarNoA`, `avaliarNoB`, `avaliarNoC`):
1. **Nó A (CLIMA):** Monitora temperatura e umidade. Identifica riscos como calor excessivo, geadas e saturação de umidade.
2. **Nó B (NÍVEL):** Monitora a distância de um objeto (nível da água) via ultrassom. Identifica enchentes (nível muito alto) e secas (nível muito baixo).
3. **Nó C (SISMO):** Calcula a aceleração total do dispositivo para identificar vibrações estruturais ou tremores de terra.

Cada nó é processado ciclicamente e o resultado é exibido no LCD com status categorizados como **NORMAL, ALERTA ou ATENÇÃO**, garantindo fácil interpretação pelo usuário final.

## Estrutura do Circuito
* **Barramento I2C:** LCD e MPU6050 conectados aos pinos A4 (SDA) e A5 (SCL).
* **Nó A:** Pino de dados (SDA) do DHT22 conectado ao Pino 11 do Arduino.
* **Nó B:** Pino Trig do HC-SR04 no Pino 12; Pino Echo no Pino 13.
* **Sinalização (LEDs RGB):**
  * **Nó A:** Pinos 2, 3 e 4.
  * **Nó B:** Pinos 5, 6 e 7.
  * **Nó C:** Pinos 8, 9 e 10.

## Instruções de Execução
1. **Montagem:** Conecte os componentes físicos ou no simulador (Wokwi) seguindo a estrutura do circuito acima. 
2. **Dependências:** Certifique-se de ter as seguintes bibliotecas instaladas na sua IDE do Arduino:
   * `LiquidCrystal I2C`
   * `DHT sensor library` (e a `Adafruit Unified Sensor`)
   * `Adafruit MPU6050`
3. **Upload:** Compile o código e faça o upload para a placa Arduino.
4. **Operação:** Ao ligar, o display mostrará "LinkEdge Active".
   * Em seguida, o sistema iniciará as leituras e atualizará o status no LCD a cada ciclo.
   * Acompanhe o estado de segurança pelos LEDs e pelos alertas na tela (NORM (Verde) = Seguro, ATEN (Amarelo) = Atenção, ALER (Vermelho) = Risco Imediato).

## Link da Simulação
Você pode visualizar e testar o funcionamento completo do projeto no simulador Wokwi através do link abaixo:

**[Clique aqui para acessar o projeto no Wokwi](https://wokwi.com/projects/465118117258551297)**

*Dica: No simulador, você pode alterar os valores dos sensores (clicando neles durante a execução) para simular diferentes cenários de alerta e verificar a resposta do sistema no LCD e nos LEDs.*

---
**Desenvolvido por:**
* KAIO HIROKI KINOSHITA - RM569127
* LEONARDO DANIEL DOS SANTOS - RM571092
* MATHEUS DIONISIO CINTRA - RM569844
---
