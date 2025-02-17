# BitDogLab - Controle de LEDs por Som e Botões

Este projeto implementa um sistema de controle de LEDs utilizando a placa de desenvolvimento **BitDogLab** com **Raspberry Pi Pico W**. O sistema permite alternar entre cores utilizando botões físicos e detectar sons para alterar a cor automaticamente.

## 📌 Funcionalidades
- Alternância entre cores (Vermelho, Verde, Azul) ao pressionar o botão A.
- Reset da cor para vermelho ao pressionar o botão B.
- Detecção de som para troca automática de cor.

## 🛠️ Configuração do Hardware
A BitDogLab já possui todos os componentes necessários, e os seguintes pinos são utilizados no projeto:

| Componente | Pino |
|------------|------|
| LED Vermelho | GPIO 13 |
| LED Verde | GPIO 11 |
| LED Azul | GPIO 12 |
| Botão A | GPIO 5 |
| Botão B | GPIO 6 |
| Microfone | ADC no GPIO 28 (Canal 2) |

## 🚀 Configuração e Compilação
### 📌 Requisitos
- Placa **BitDogLab**
- **Raspberry Pi Pico W**
- **SDK do Raspberry Pi Pico** instalado
- **CMake** e **Make**

4. Copie o arquivo gerado (`.uf2`) para o **Raspberry Pi Pico W**.

### 🖥️ Monitoramento do Microfone
Caso queira visualizar os valores do microfone, utilize um terminal serial:
```sh
picocom -b 115200 /dev/ttyUSB0
```
Ou, no Windows, utilize o **PuTTY**.

## 📋 Ajustes e Debugging
- **Limite de detecção de som (`SOUND_THRESHOLD`)**: Pode ser ajustado no código para melhor sensibilidade.
- **Atrasos (`sleep_ms`)**: Pequenas alterações podem evitar leituras falsas.
- **Teste os valores do microfone** via terminal para definir corretamente os parâmetros.

## 📜 Licença
Este projeto é de código aberto sob a licença **MIT**.

---
✉️ Em caso de dúvidas, contribuições ou sugestões, sinta-se à vontade para abrir um **issue** ou enviar um **pull request**! 🚀
