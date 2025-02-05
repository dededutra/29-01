#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>

#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11

#define BUTTON_PIN 5 // Botão A no BitDogLab, GPIO 5

// Variáveis globais para controle da sequência
volatile bool sequence_running = false; // Indica se uma sequência está em execução
// current_step: 0 = todos ligados; 1 = dois LEDs ligados; 2 = apenas um LED ligado; 3 = sequência finalizada
volatile int current_step = 0;

// Protótipo da função callback para que ela seja conhecida antes de ser usada
int64_t turn_off_callback(alarm_id_t id, void *user_data);

/**
 * Agenda um novo alarme one-shot para daqui a 3000 ms.
 */
void schedule_next_alarm()
{
    // Usa add_alarm_in_ms() com o parâmetro repeat como false para criar um alarme one-shot
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}

int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    if (current_step == 0)
    {
        // Primeiro disparo: desliga o LED azul
        gpio_put(LED_BLUE, 0);
        current_step = 1;
        printf("Callback: LED AZUL desligado. (Dois LEDs acesos: Vermelho e Verde)\n");
        schedule_next_alarm();
    }
    else if (current_step == 1)
    {
        // Segundo disparo: desliga o LED vermelho
        gpio_put(LED_RED, 0);
        current_step = 2;
        printf("Callback: LED VERMELHO desligado. (Apenas LED VERDE aceso)\n");
        schedule_next_alarm();
    }
    else if (current_step == 2)
    {
        // Terceiro disparo: desliga o LED verde e finaliza a sequência
        gpio_put(LED_GREEN, 0);
        current_step = 3;
        sequence_running = false;
        printf("Callback: LED VERDE desligado. Sequência finalizada (Todos LEDs apagados).\n");
    }
    return 0; // Retorno ignorado, pois reagendamos manualmente
}

int main(void)
{
    stdio_init_all();
    // Aguarda alguns instantes para que o terminal serial esteja pronto (útil em simulações)
    sleep_ms(2000);

    // Configurar os pinos dos LEDs como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configurar o pino do botão:
    // Usamos pull-up para tratar o botão como ativo baixo (idle = 1, pressionado = 0)
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    printf("Sistema iniciado. Pressione o Botão A (GPIO %d) para iniciar a sequência.\n", BUTTON_PIN);

    while (1)
    {
        // Exibe informações de debug a cada 500 ms
        printf("Debug: sequence_running=%d, current_step=%d\n", sequence_running, current_step);
        sleep_ms(500);

        // Verifica se o botão foi pressionado e se nenhuma sequência está em execução.
        // Como usamos pull-up, botão pressionado é lido como 0.
        if (!sequence_running && !gpio_get(BUTTON_PIN))
        {
            // Debounce: espera 50 ms e confirma se o botão continua pressionado
            sleep_ms(50);
            if (!gpio_get(BUTTON_PIN))
            {
                // Inicia a sequência
                sequence_running = true;
                current_step = 0;
                // Liga todos os LEDs
                gpio_put(LED_RED, 1);
                gpio_put(LED_BLUE, 1);
                gpio_put(LED_GREEN, 1);
                printf("Botão pressionado: Sequência iniciada - todos os LEDs ligados.\n");
                // Agenda o primeiro alarme one-shot para daqui a 3000 ms
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }
    }
}
