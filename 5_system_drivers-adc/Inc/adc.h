/**
 * @file adc.h
 * @brief ADC driver interface for STM32F401RE.
 * @details Configures ADC1 (primary ADC on STM32F401RE) for PA1/channel 1 conversions.
 * @author yougiyo
 * @date September 22, 2026
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/**
 * @brief Configure PA1 and ADC1 channel 1 for single-channel conversion.
 * @param None
 * @return None
 */
void pa1_adc_init(void);

/**
 * @brief Start ADC1 continuous conversion on the configured channel.
 * @param None
 * @return None
 */
void start_conversion(void);

/**
 * @brief Read one ADC1 conversion result.
 * @param None
 * @return Latest ADC conversion value.
 */
uint32_t adc_read(void);

#endif /* ADC_H_ */
