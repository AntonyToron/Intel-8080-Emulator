/*
  File name : CPU.h
  
  Description : Header file for 8080 processor.
  Author : Antony Toron
 */

typedef struct State8080* State8080_T;
typedef struct ConditionCodes* ConditionCodes_T;
typedef struct Drivers* Drivers_T;

void Emulate8080Op(State8080_T state);

State8080_T State8080_init();

ConditionCodes_T ConditionCodes_init();

Drivers_T Drivers_init();

void State8080_load_mem(State8080_T state, int start, unsigned char *buffer);