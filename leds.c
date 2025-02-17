#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// Definição dos pinos dos LEDs e botões
#define LED_RED_PIN 13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)

// Variável para armazenar a cor atual do LED
int current_color = 0;

// Definição dos limites para detectar som
#define SOUND_THRESHOLD 3000  // Ajustável conforme testes
#define SOUND_BASELINE 1500   // Valor médio esperado do ambiente

// Função para configurar os pinos
void setup() {
    stdio_init_all();
    
    // Inicialização dos LEDs
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    
    // Inicialização dos botões
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    // Inicialização do ADC para o microfone
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(MIC_CHANNEL);  // Seleciona o canal correto
}

// Função para definir a cor do LED
void set_led_color(int color) {
    gpio_put(LED_RED_PIN, color == 0);
    gpio_put(LED_GREEN_PIN, color == 1);
    gpio_put(LED_BLUE_PIN, color == 2);
}

// Função para ler o som do microfone e verificar picos
bool detect_sound() {
    uint32_t sum = 0;
    
    // Faz 10 leituras e tira a média (para evitar ruído)
    for (int i = 0; i < 10; i++) {
        sum += adc_read();
        sleep_us(2000);  // Pequena pausa entre leituras
    }
    
    uint16_t mic_value = sum / 10;  // Média das leituras

    // Debug: Ver o valor lido do microfone
    printf("Mic Value: %d\n", mic_value);

    // Ajuste os valores conforme necessário após testes
    return (mic_value > SOUND_THRESHOLD && mic_value > (SOUND_BASELINE + 500));
}

int main() {
    setup();
    set_led_color(current_color);

    while (1) {
        bool sound_detected = detect_sound();

        // Verifica o botão A
        if (gpio_get(BUTTON_A_PIN) == 0) {
            current_color = (current_color + 1) % 3; // Alterna entre vermelho, verde e azul
            set_led_color(current_color);
            sleep_ms(500);  // Debounce
        }

        // Verifica o botão B
        if (gpio_get(BUTTON_B_PIN) == 0) {
            current_color = 0; // Reseta para vermelho
            set_led_color(current_color);
            sleep_ms(500);  // Debounce
        }

        // Se detectar um som alto, muda de cor
        if (sound_detected) {
            current_color = (current_color + 1) % 3; // Alterna entre vermelho, verde e azul
            set_led_color(current_color);
            sleep_ms(500);  // Pequena pausa para evitar leituras falsas
        }

        sleep_ms(50);  //Aguarda um pouco antes da próxima verificação
    }
}