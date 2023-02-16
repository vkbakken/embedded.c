#include <stdint.h>
#include <stdbool.h>

#include <init.h>
#include <chip/io.h>


void board_init(void)
{
    NRF_P0->OUTSET = (1 << 13);
    NRF_P0->DIRSET = (1 << 13);
}


void board_uart_init(void)
{
    NRF_P0->OUTSET = (1 << 13);
    NRF_P0->DIRSET = (1 << 13);
}
