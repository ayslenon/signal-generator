#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "driver/gpio.h"

#include "signal_generator.h"
#include "types.h"

#define BUTTON_SIG_PIN 0
#define BUTTON_AMP_PIN 35
#define BUTTON_FREQ_PIN 32

extern Button bt_freq;
extern Button bt_amp;
extern Button bt_sw_sig;

/**
 * @brief configura botão como INPUT PULL UP
 * @param pin pino da GPIO para ser configurado como botão
 */
void config_button(uint8_t pin);

/**
 * @brief faz a configuração dos botões
 */
void config_buttons();

/**
 * @brief verifica se um botão foi apertado (para contabilizar outro clique o botão deve ser solto)
 * @param bt botão para verificar se foi apertado
 * @param button_s variável global para flag de botões apertados
 */
void handle_button(Button *bt, uint8_t *button_s);

#endif // BUTTONS_H
