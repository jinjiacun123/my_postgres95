#ifndef MISCADMIN_H
#define MISCADMIN_H
#include "postgres.h"

#define MAX_PARSER_BUFFER 8192
#define NDBUFS            64

extern int Quiet;

typedef enum ProcessingMode {
  NoProcessing,
  BootstrapProcessing,
  InitProcessing,
  NomalProcessing
} ProcessingMode;

extern bool IsBootstrapProcessingMode(void);

#endif
