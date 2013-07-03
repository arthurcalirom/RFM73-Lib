#ifndef _RFM73_H_
#define _RFM73_H_

#include <avr/io.h>
#include <inttypes.h>

#define TRUE 1
#define FALSE 0

#define RFM73_IRQ_PIN     PB5
#define RFM73_IRQ_PORT    PORTB
#define RFM73_IRQ_IN      PINB
#define RFM73_IRQ_DIR     DDRB
#define RFM73_CE_PIN      PB4
#define RFM73_CE_PORT     PORTB
#define RFM73_CE_IN       PINB
#define RFM73_CE_DIR      DDRB
#define RFM73_CSN_PIN     PB0
#define RFM73_CSN_PORT    PORTB
#define RFM73_CSN_IN      PINB
#define RFM73_CSN_DIR     DDRB

#define RFM73_CE_HIGH     RFM73_CE_PORT |= (1 << RFM73_CE_PIN)
#define RFM73_CE_LOW      RFM73_CE_PORT &=~(1 << RFM73_CE_PIN)
/* It is important to never stay in TX mode for more than 4ms at one time. */
#define RFM73_CE_TX_PULSE RFM73_CE_HIGH; _delay_us(20); RFM73_CE_LOW
#define RFM73_CSN_HIGH    RFM73_CSN_PORT |= (1 << RFM73_CSN_PIN)
#define RFM73_CSN_LOW     RFM73_CSN_PORT &=~(1 << RFM73_CSN_PIN)
#define RFM73_CSN_PULSE   RFM73_CSN_HIGH; _delay_us(10); RFM73_CSN_LOW


#define RFM73_OUT_PWR_MINUS10DBM   0
#define RFM73_OUT_PWR_MINUS5DBM    1
#define RFM73_OUT_PWR_0DBM         2
#define RFM73_OUT_PWR_5DBM         3

#define RFM73_LNA_GAIN_HIGH        1
#define RFM73_LNA_GAIN_LOW         0

#define RFM73_DATA_RATE_1MBPS      0
#define RFM73_DATA_RATE_2MBPS      0b10
#define RFM73_DATA_RATE_250KBPS    0b01

#define RFM73_TX_WITH_ACK          1
#define RFM73_TX_WITH_NOACK        0

#define RFM73_RX_WITH_ACK          1
#define RFM73_RX_WITH_NOACK        0

#define RFM73_MAX_PACKET_LEN       32// max value is 32

#define RFM73_ADR_WID_3BYTES       0b01
#define RFM73_ADR_WID_4BYTES       0b10
#define RFM73_ADR_WID_5BYTES       0b11

/* Transmit address */
uint8_t rfm73_tx_addr[5];


uint8_t _rfm73_read_reg(uint8_t reg);
void _rfm73_read_buf(uint8_t reg, uint8_t *pBuf, uint8_t bytes);

void _rfm73_write_reg(uint8_t reg, uint8_t value);
void _rfm73_write_buf(uint8_t reg, uint8_t *pBuf, uint8_t length);

void rfm73_tx_mode(void);
void rfm73_rx_mode(void);
void rfm73_power_up();
void rfm73_power_down();

void rfm73_init(uint8_t out_pwr, uint8_t lna_gain, uint8_t data_rate);
void rfm73_set_rf_params(uint8_t out_pwr, uint8_t lna_gain, uint8_t data_rate);
void rfm73_mask_int(uint8_t mask_rx_dr, uint8_t mask_tx_ds, uint8_t mask_max_rt);
void rfm73_set_address_width(uint8_t aw);
void rfm73_set_autort(uint16_t rt_time, uint8_t rt_count);
void rfm73_set_channel(uint8_t _cfg);

uint8_t rfm73_receive_packet(uint8_t type, uint8_t* data_buf, uint8_t* len);
uint8_t rfm73_send_packet(uint8_t type, uint8_t* pbuf, uint8_t len);

uint8_t rfm73_observe(uint8_t* packet_lost, uint8_t* retrans_count);
uint8_t rfm73_carrier_detect();
uint8_t rfm73_get_channel();
uint8_t rfm73_find_receiver(uint8_t* ch, uint8_t* dr);

#endif