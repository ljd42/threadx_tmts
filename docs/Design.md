# ThreadX with Arduino- Internal Documentation

## Project Layout
The project is organized as follows:
```
.
├── lib             # ThreadX related librairies
├── src             # benchmark code
├── platformio.ini  # platformio project settings
└── README.md
```

## platformio.ini
This file drives the build. The `[env]` section defines the common build environment, the `[env:xxx]` defines the build environment for benchmark xxx. 

A benchmark consists of building xmain.cpp and the corresponding benchmark (C-file) and linking against the Arduino and the threadX related librairies (see below).

## Benchmark code
The C-files located under **src** correspond to the file found in:
`threadx-6.4.1_rel/utility/benchmarks/thread_metric/`

The `xmain.cpp` file is the main entry point for the benchmark. 
It performs:
1. The Arduino framework initialization
2. The initialization of ThreadX and benchmark execution by calling `tm_main()` provided by the benchmark itself.

The file `xmain.cpp` provides a simple implementation for `printf()`. This function is needed by the benchmark, but the Arduino framework does not natively support it on most boards.

## ThreadX related libraries

The **lib** directory is intended for project specific (private) libraries.
PlatformIO will compile them to static libraries and link into executable file.
```
lib
├── ports          # BSP
├── thread_metric  # TM porting layer for ThreadX
├── threadx        # ThreadX source
└── LICENSE.txt    # ThreadX license
```

### lib/threadx
This is the ThreadX kernel. 

The files located under threadx/ corresponds to the files found in:
``
threadx-6.4.1_rel/common/inc/*
threadx-6.4.1_rel/common/src/*
``

The only added file is `tx_port.h`. This header takes care of including the "proper" `tx_port.h` for the target board from the BSP layer located under `lib/ports`.

### lib/ports
This is the BSP for the target boards.

The files located under cortex_m4/ folder correspond to the files found in:
```
threadx-6.4.1_rel/ports/cortex_m4/gnu/src/*
threadx-6.4.1_rel/ports/cortex_m4/gnu/inc/*
threadx-6.4.1_rel/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.S
```

The file `tx_initialize_low_level.S` has been modified to match the Arduino framework.

### lib/thread_metric 
This contains the porting layer source code for ThreadX to run the 
Thread-Metric RTOS Test Suite

The files located under thread_metric correspond to the files found in:
```
threadx-6.4.1_rel/utility/benchmarks/thread_metric/tm_api.h
threadx-6.4.1_rel/utility/benchmarks/thread_metric/tm_porting_layer.h
threadx-6.4.1_rel/utility/benchmarks/thread_metric/threadx_example/tm_porting_layer_threadx.c
```

