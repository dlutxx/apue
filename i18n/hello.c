#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _(string) gettext(string)

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

int main()
{
    char pwd[PATH_MAX], *p;
    printf("see: %s\n", "http://fedoraproject.org/wiki/How_to_do_I18N_through_gettext");
    setlocale(LC_ALL, "");
    if ((p=getcwd(pwd, PATH_MAX))==NULL) {
        perror("getcwd");
        abort();
    }
    bindtextdomain("helloworld", p);
    textdomain("helloworld");
    printf("%s\n", _("hello"));
    return 0;
}

