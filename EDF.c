#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t period;        // task period in ms
    uint32_t deadline;      // relative deadline in ms
    uint32_t exec_time;     // execution time in ms
    void (*task_func)(void);  // pointer to task function
    uint32_t last_exec_time;  // last execution time in ms
} task_t;

void task1(void) {
    // Task 1 code here
}

void task2(void) {
    // Task 2 code here
}

// Define tasks here
task_t tasks[] = {
    {1000,  500, 50, &task1, 0},
    {1000, 1000, 10, &task2, 0},
};

#define NUM_TASKS (sizeof(tasks)/sizeof(task_t))

void schedule(void) {
    uint32_t min_deadline = UINT32_MAX;
    uint32_t now = millis();

    // Find the task with the earliest deadline
    for (int i = 0; i < NUM_TASKS; i++) {
        task_t *task = &tasks[i];

        if (now >= task->last_exec_time + task->period) {
            // Task is ready to run again
            task->deadline = now + task->period;
            task->last_exec_time = now;
        }

        if (task->deadline < min_deadline) {
            min_deadline = task->deadline;
        }
    }

    // Execute the task with the earliest deadline
    for (int i = 0; i < NUM_TASKS; i++) {
        task_t *task = &tasks[i];

        if (task->deadline == min_deadline) {
            task->task_func();
            task->deadline += task->period;
            task->last_exec_time = now;
        }
    }
}

int main(void) {
    while (true) {
        schedule();
    }

    return 0;
}
