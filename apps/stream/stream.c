#include <stdint.h>
#include <stdbool.h>


#include <init.h>
#include <stream.h>


#define BUFFER_SIZE                 (128)


static char mem[BUFFER_SIZE];
static struct stream s1;


int main(void)
{
    board_init();
    stream_init(&s1, mem, sizeof(mem));

    stream_printf(&s1, "stream test %i %f %s\r\n", 100, 1.001, "Complete");

    while (true) {
        stream_worker(&s1);
    }

    return 0;
}
