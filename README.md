# Linux-scheduler-latency

This repository uses C to measures how accurately Linux schedules processes in time.

The program requests precise sleep intervals and measures how long the OS actually delays execution, using high resolution monotonic clocks.

## What is a high resolution monotonic clock?

It is simply a system clock that moves strictly forward and provide very fine time measurements (typically nanoseconds).

It isn't affected by system time changes such as NTP updates (corrects the computer's wall time by synchronising with internet time servers which can cause time jumps that monotonic clocks ignore) or manual clock adjustments.

In Linux, CLOCK_MONOTONIC_RAW is an example, cause it measures elapsed time directly from the hardware time, making it ideal for benchmarking latency and jitter without messing changing from clock correction.

By repeating this many times, the benchmark captures scheduler latency and jitter, showing real wake up times rather than just the avg. delay.

