# Linux-scheduler-latency

This project provides a C library for measuring how accurately the Linux scheduler wakes up threads after a requested delay.

The library repeatedly requests a precise delay of one millisecond and measures the actual time until execution resumes. The difference between the requested delay and the observed wake up time is recorded as scheduler latency or jitter.

The experiment can be run using a single thread or multiple threads to observe how Linux schedules concurrent execution under different levels of contention.

## What is a high resolution monotonic clock?

A high resolution monotonic clock always moves forward and provides very fine grained time measurements, typically in nanoseconds.

It is not affected by system time changes such as NTP synchronisation or manual clock adjustments. This makes it suitable for benchmarking scheduling latency.

On Linux, CLOCK_MONOTONIC_RAW measures elapsed time directly from hardware and avoids distortions caused by clock correction. This makes it ideal for latency and jitter analysis.

By repeating the measurement many times, the library captures the full distribution of scheduler delays rather than only an average value.

## Threaded Execution

When running with multiple threads, each thread independently requests the same delay and records its own wake up latency samples.

Threads share the same CPU resources and compete for execution time. This exposes how the Linux scheduler time slices between runnable threads and how contention affects wake up accuracy.

The library does not use locks because each thread writes to its own memory region. Any observed timing variation is therefore caused by scheduling behaviour rather than synchronisation overhead.

Running with multiple threads increases scheduler pressure and typically results in higher latency and jitter compared to single thread execution.

## What this project demonstrates

• Scheduler wake up latency
• Scheduling jitter under load
• Effects of thread contention
• Differences between busy waiting and sleeping
• Variability across repeated measurements

## What this project cannot do

• It does not guarantee realtime scheduling
• It does not measure hard realtime deadlines
• It does not ensure parallel execution unless multiple CPU cores are available
• It does not isolate kernel scheduling from other system activity
• It does not model IO or interrupt driven workloads

If CPU affinity is restricted to a single core, threads run concurrently but not in parallel.

## Build and use

Build the static library and example program:

make
make clean

Manual build commands:

gcc -Isrc -Iinclude -pthread -c src/*.c
ar rcs libschedlat.a build/*.o
gcc your_app.c -Iinclude -L. -lschedlat -pthread -o your_app

What these commands do:

• The compiler step produces object files without linking
• The archive step packages the objects into a static library
• The final command links your application against the library and pthread support
