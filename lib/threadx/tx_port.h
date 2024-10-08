/* 
  The purpose of this file is to include the actual tx_port.h file for 
  current cpu architecture / board

  Author: Neo Xiong <xiongyu0523@gmail.com> 
  Author: Loic Domaigne <tech@domaigne.com>

  Copyright (c) 2024 Loic Domaigne
  SPDX-License-Identifier: MIT
*/

#ifndef TX_PORT_H
#define TX_PORT_H

#if 0
#define TX_DISABLE_ERROR_CHECKING
#define TX_DISABLE_PREEMPTION_THRESHOLD
#define TX_DISABLE_NOTIFY_CALLBACKS
#define TX_DISABLE_REDUNDANT_CLEARING
#define TX_DISABLE_STACK_FILLING
#define TX_NOT_INTERRUPTABLE
#define TX_TIMER_PROCESS_IN_ISR
#define TX_REACTIVATE_INLINE
#define TX_INLINE_THREAD_RESUME_SUSPEND
#endif 


#if ( defined(HAS_CORTEX_M4) )
#include "../ports/cortex_m4/tx_port.h"
#else
#error "Microcontroller is not supported!"
#endif


#endif

