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
	-DHAS_CORTEX_M4           # make sure that's true for your board!
	-DUSE_JB_SETTINGS=1       # use Beningo's config settings (Appendix B)
```
The list of supported boards can be founds at: https://docs.platformio.org/en/latest/boards/
In my case, I have a STM32 nucleo board (Nucleo F411RE) which runs at 100 MHz. 

The flag `USE_JB_SETTINGS=1` configures ThreadX with the settings as per Appendix B of Beningo's report. If not set (or set to 0), the default ThreadX config settings are used. See table below for the performance differences between default and "JB settings".

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

Config Settings Performance
---------------------------

The table shows the ratio between the default and the "JB" settings measured
on the Nucleo F411RE board.

Worth noting:
- all but tm_malloc run faster with "JB" settings.
- tm_preempt runs x1.28 faster and has the most signifcant speed improvement.
- tm_malloc runs slower (x0.94) with "JB" settings.

| benchmark  |  default |       JB | JB/default |
| ---------- | -------: | -------: | :--------: |
| tm_basic   |   243889 |   243896 |    100%    |
| tm_coop    | 20830276 | 20824372 |    100%    |
| tm_preempt |  6741668 |  8602319 |    128%    |
| tm_malloc  | 29689341 | 27765900 |    94%     |
| tm_message | 14844665 | 15378021 |    104%    |
| tm_sync    | 28832942 | 30914605 |    107%    |


Pitfalls and future works
-------------------------
This work is a proof of concept, and has some limitations:
- Only Cortex-M4 boards are integrated. 
- Dependencies to the Arduino framework.
- Dependencies to platformio build system / toolchain 
- It has been only tested on one board (Nucleo F411RE)...

Future work might include:
- support for other processors and architectures.
- for benchmarking comparison, make sure that the same compiler flags are
used for Zephyr/ThreadX.
- Remove dependencies to the Arduino framework.
- Use the Zephyr's compiler/toolchain, and framework if applicable.

Want to know more?
------------------
Check the file `docs/Design.md`

Credits
-------
Thanks to Neo Xiong (aka. xiongyu0523) for his initial port of Azure RTOS ThreadX library for Arduino.

