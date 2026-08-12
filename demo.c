/*  Written by Kamila Szewczyk (k@iczelia.net), released to
    the public domain (0BSD).  */

#include <stdio.h>
#include "yarg.h"

/*  Example invocation:
    $ ./a.out -ab5 pos-arg -v -c 5 --stuff --thing=3 --thing2 5 -- -name  */
int main(int argc, char * argv[]) {
  enum { LONG_ARG = CHAR_MAX + 1, STUFF, THING, THING2 };
  yarg_options opt[] = {
    {      'h', no_argument,       "help" },
    {      'a', no_argument,       NULL },
    {      'b', required_argument, NULL },
    {      'c', optional_argument, NULL },
    {      'v', optional_argument, NULL },
    { LONG_ARG, no_argument,       "long-arg" },
    { STUFF,    no_argument,       "stuff" },
    { THING,    no_argument,       "thing" },
    { THING2,   optional_argument, "thing2" },
    {        0, no_argument,       NULL }
  };
  yarg_settings settings = { .dash_dash = true, .style = YARG_STYLE_UNIX };
  yarg_result * res = yarg_parse(argc, argv, opt, settings);
  if (res->error)
    { fputs(res->error, stderr);  yarg_destroy(res);  return 1; }
  for (int i = 0; i < res->argc; i++) {
    if (res->args[i].opt < CHAR_MAX)
      printf("Option: %c\n", res->args[i].opt);
    else
      printf("Option: `%s'\n", res->args[i].long_opt);
  
    if (res->args[i].arg)
      printf("Argument: %s\n", res->args[i].arg);
  }
  for (int i = 0; i < res->pos_argc; i++)
    printf("Positional argument: %s\n", res->pos_args[i]);
  yarg_destroy(res);
}
