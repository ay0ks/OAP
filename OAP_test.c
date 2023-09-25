#include "OAP.h"

int main(int argc, char **argv) {
    OAP *oap = OL_new(OAP, "pg", "10000", NULL);
    OAP_addopt(oap, "Enable verbose output.", NULL, NULL, NULL, "verbose", false, false, false, 3, "Va", "Verbose", "Vjblinkwjsus");
    OAP_addarg(oap, "FILE", "jjdjsjs", "/a.txt", "fd", false);

    OAP_addopt(oap, "Enable verbose 2.", "STRING", "Your name", "Daniel", "jj", true, false, false, 3, "Ab", "Abce", "Abcerum");
    OAP_parse(oap, argc, argv);
    OL_del(OAP, oap);
    
    printf("ab: %s\n", OAP_getopt(oap, "jj"));
    
}