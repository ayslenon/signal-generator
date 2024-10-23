#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#define CONST_PERIOD_2_PI   6.2832
#define ARRAY_LEN           200

#include <stdio.h>
#include <math.h>

#include "dac_controller.h"
#include "types.h"

extern uint8_t waveform[ARRAY_LEN];

/**
 * @brief callback para ajuste de frequência
 * 
 * Testado apenas com range 2kHz a 4kHz com passo de 100Hz
 */
void handle_freq();

/**
 * @brief callback para ajuste de amplitude
 * 
 * Testado apenas com range 25 a 250 com passo de 25
 * 
 * Testado sem offset
 */
void handle_ampl();

/**
 * @brief callback para troca de forma de onda
 * 
 * Testado apenas com range 25 a 250 com passo de 25
 */
void handle_switch_sig();

/**
 * @brief função para geração do vetor da onda escolhida
 */
void new_waveform();

#endif // SIGNAL_GENERATOR_H
