# Linux-scheduler-latency

This project measures how accurately the Linux scheduler wakes up threads after a requested delay.

The program repeatedly requests a precise delay of one millisecond and measures the actual time until execution resumes. The difference between the requested delay and the observed wake up time is recorded as scheduler latency or jitter.

The experiment can be run using a single thread or multiple threads to observe how Linux schedules concurrent execution.

## What is a high resolution monotonic clock?

It is simply a system clock that moves strictly forward and provide very fine time measurements (typically nanoseconds).

It isn't affected by system time changes such as NTP updates (corrects the computer's wall time by synchronising with internet time servers which can cause time jumps that monotonic clocks ignore) or manual clock adjustments.

In Linux, CLOCK_MONOTONIC_RAW is an example, cause it measures elapsed time directly from the hardware time, making it ideal for benchmarking latency and jitter without messing changing from clock correction.

By repeating this many times, the benchmark captures scheduler latency and jitter, showing real wake up times rather than just the avg. delay.

## Threaded Execution

When you run multiple threads, each thread independently requests the same delay and records its own wake up latency times.

Threads same the same CPU resources and compete for execution time. This exposes how Linux sheduler time slices between runnable threads and how contention affects wake up accuracy.

This program does not use locks because each thread writes its own memory region. Any observed variation in timing is therefore caused by sheduling behaviour rather than synchronisation overhead.

Running with multiple threads increases scheduler pressure and typically results in higher latency and jitter compared to single thread execution.

## What this project demonstrates

• Scheduler wake up latency
• Scheduling jitter under load
• Effects of thread contention
• Differences between busy waiting and sleeping
• Variability across repeated measurements

## What this project cannot do

• It does not guarantee real time scheduling
• It does not measure hard real time deadlines
• It does not ensure parallel execution unless multiple CPU cores are available
• It does not isolate kernel scheduling from other system activity
• It does not model I O or interrupt driven workloads

If CPU affinity is restricted to a single core, threads run concurrently but not in parallel.

## How to run?

git clone https://github.com/yourusername/Linux-scheduler-latency.git

cd Linux-scheduler-latency

gcc -O2 latency.c -o latency #Compiles with Optimisation enabled using the -O2

./ latency
