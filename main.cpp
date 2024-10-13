#include <sys/prctl.h>

static const char NEW_PROGRAM_NAME[] = "innocent";

int main() {
    prctl(PR_SET_NAME, (unsigned long) NEW_PROGRAM_NAME);
    while (true) {}
    return 0;
}
