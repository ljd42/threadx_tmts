/* 
 * Copyright (c) 2024 Loic Domaigne
 * SPDX-License-Identifier: MIT
 */
#include <stdarg.h>
#include <Arduino.h>
#include <tx_api.h>

/* tm_main() is defined in the respective bechmarking test */
extern "C" 
void tm_main(); 

extern "C"
int printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    
    const size_t MAX_STR_LEN=128;
    char buf[MAX_STR_LEN];
    int rc;

    rc = vsnprintf(buf, MAX_STR_LEN-1, format, args);
    Serial.print(buf); Serial.print("\r");
    va_end(args);
    return rc;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("ThreadX with Arduino framework up and running\n");

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

/* Arduino framework "super-loop" */
void loop()
{
    /* Since ThreadX takes over, the arduino framework
       should never call this function */
    Serial.write("\nOops, there's a bug !\n");
}


/* Define what the initial system looks like.  */
void    tx_application_define(void *first_unused_memory)
{

     /* Enter the Thread-Metric test main function for initialization and to start the test.  */
     tm_main();
}
