#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    char buf1[] ="aaa, ,a, ,,,bbb-c,,,ee|abc";
    /* Establish string and get the first token: */
    char* token = strtok( buf1, ",-|");
        printf( "%s \n", token );
    while( token != NULL )
    {
        /* While there are tokens in "string" */
        printf( "%s \n", token );
        /* Get next token: */
        token = strtok( NULL, ",-|");
    }
    return 0;
}
