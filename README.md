ThreadX RTOS Performance Benchmark
==================================

This repo implements some of the Thread-Metric RTOS tests for ThreadX.
It is meant to reproduce the results mentioned in [Jacob Beningo's report](
https://www.linkedin.com/posts/jacobbeningo_rtos-popularity-and-shiny-features-dont-activity-7244314864809078786-QO40/)

This work is aiming to provide some grounds for future Zephyr's performance testings and investigations.

Background
----------
The Eclipse/ThreadX RTOS has been integrated in some semiconductor's SDK/Boards, see: https://github.com/eclipse-threadx/getting-started

Running Eclipse/ThreadX elsewhere is not trivial, and requires some integration efforts. The goal of this work is to:
- exercise ThreadX integration
- potentially simplify running the tests for a wider range of boards. 

Integration 
-----------
I've chosen to use integrate ThreadX within the platformio / Arduino framework.
A previous port with ThreadX 6.1.12 ("Azure RTOS ThreadX") exists: 
https://registry.platformio.org/libraries/xiongyu0523/Azure%20RTOS%20ThreadX

The current repo follows this port, but integrates the latest version of Eclipse/ThreadX (v6.4.1)

Running the benchmarks on your Cortex-M4 boards
-----------------------------------------------
To run the benchmarks on your Cortex M4 boards:
- install platformio core
  https://docs.platformio.org/en/latest/core/installation/index.html
- edit the **platformio.ini** file.
  Change the **env** section to match your target board:
```
[env]
platform = ststm32
board = nucleo_f411re         # change this line to match your board
framework = arduino
build_unflags = -Os
build_flags = 
	-O2 
	-DSYSTEM_CLOCK=100000000  # your processor speed in Hz
	-DHAS_CORTEX_M4 
```
The list of supported boards can be founds at: https://docs.platformio.org/en/latest/boards/
In my case, I have a STM32 nucleo board (Nucleo F411RE) which runs at 100 MHz. 

- compile the wanted benchmark and upload the sketch
```
source ~/.platformio/penv/bin/activate
(penv)$ pio run -e tm_basic            # compile tm
(penv)$ pio run -e tm_basic -t upload  # upload 
```

Benchmarks available:

| Configuration | Benchmark                       |
| ------------- | ------------------------------- |
| tm_basic      | Basic Processing Test           |
| tm_coop       | Cooperative Scheduling Test     |
| tm_preempt    | Preemptive Scheduling Test      |
| tm_malloc     | Memory Allocation Test          |
| tm_message    | Message Processing Test         |
| tm_sync       | Synchronization Processing Test |

You can then connect to your board over the serial line your preferred terminal emulators (minicom, screen,...). If everything goes well, you should see every 30 seconds the current metric report.


Pitfalls and future works
-------------------------
This work is a proof of concept, and has some limitations:
- Only Cortex-M4 boards are integrated. 
- Dependencies to the Arduino framework.
- Dependencies to platformio build system / toolchain 

Future work might include:
- support for other processors and architectures.
- for benchmarking comparison, make sure that the same compiler flags are
used for Zephyr/ThreadX.
- Remove dependencies to the Arduino framework.
- Use the Zephyr's compiler/toolchain, and framework if applicable.

Credits
-------
Thanks to xiongyu0523 aka. Neo for the his initial port of Azure RTOS ThreadX
library for Arduino.


Project Structure
-----------------
.
├── include
├── lib
├── src
├── test
├── platformio.ini
└── README.md

`lib` contains:
    - The ThreadX kernel
    - The ThreadX porting layer for the RTOS performance benchmark
    - The BSP layer for Cortex M4 boards

`src` contains:
The RTOS performance benchmarks for:
    - Basic Processing Test
    - Cooperative Scheduling Test
    - Preemptive Scheduling Test
    - Message Processing Test
    - Synchronization Processing Test

 
