#include <stdint.h>

#include <arch/nvic.h>
#include <chip/io.h>
#include <uart/ctrl.h>


static uint32_t id_to_address(uint8_t id)
{
    switch (id) {
        case 0:
        return NRF_UARTE0_BASE;
        case 1:
        return NRF_UARTE1_BASE;
        default:
        return NRF_UARTE0_BASE;
    }
}


static void init_defaults_common(NRF_UART_Type *uart)
{
    uart->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200;
    uart->CONFIG = 0;
}


void uart_ctrl_init_defaults(uint8_t id)
{
    switch (id) {
        case 0:
            nvic_disable(UARTE0_UART0_IRQn);
            init_defaults_common((NRF_UART_Type *)NRF_UARTE0_BASE);
            nvic_clear_pending(UARTE0_UART0_IRQn);
            nvic_enable(UARTE0_UART0_IRQn);
        break;
        default: break;
    }
}


void uart_enable(uint8_t id, unsigned int flags)
{
    NRF_UART_Type *uart = (NRF_UART_Type *)id_to_address(id);

    if (flags & UART_FLAG_RX) {
        uart->TASKS_STARTRX = 0x1;
        //uart->EVENTS_ENDRX = 0;
    }
    
    if (flags & UART_FLAG_TX) {
        uart->EVENTS_TXDRDY = 0;
        uart->TASKS_STARTTX = 0x1;
    }

    uart->ENABLE = 0x4;
}


bool uart_put_byte_priv(uint8_t id, uint8_t data)
{
    NRF_UART_Type *uart = (NRF_UART_Type *)id_to_address(0);

	if (uart->EVENTS_TXDRDY) {
        uart->TXD = data;
    }

    return false;
}
