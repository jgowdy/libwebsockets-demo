#include <stdio.h>
#include <unistd.h>

#include "service.h"

int main(int argc, char *argv[]) {
  start_service();
  getchar();
}
