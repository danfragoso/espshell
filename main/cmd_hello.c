/* 
  espshell - hello command
*/

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"
#include "cmd_decl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"


/** Arguments used by 'hello' function */
static struct {
    struct arg_str *helloer;
    struct arg_end *end;

} join_args;

static int say_hello(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **) &join_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, join_args.end, argv[0]);
        return 1;
    }
    ESP_LOGI(__func__, "Hello %s I`m a esp32, nice to meet you!!!",
             join_args.helloer->sval[0]);

    return 0;
}

void register_hello()
{
    join_args.helloer = arg_str0(NULL, NULL, "<string>", "Someone to say hello");
    join_args.end = arg_end(0);

    const esp_console_cmd_t hello_cmd = {
        .command = "hello",
        .help = "Say hello for the 1st argument.",
        .hint = NULL,
        .func = &say_hello,
    };

    ESP_ERROR_CHECK( esp_console_cmd_register(&hello_cmd) );
}
