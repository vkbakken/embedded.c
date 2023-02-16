#include <stdint.h>
#include <stdbool.h>


#include <console.h>
#include <init.h>


int main(void)
{
    board_init();
    console_init();

    dbg_panic("Console panic\r\n");
    dbg_error("Console error\r\n");
    dbg_warning("Console warning\r\n");
    dbg_info("Console info\r\n");
    dbg_verbose("Console verbose\r\n");

    
    while (true) {
    }

    return 0;
}
