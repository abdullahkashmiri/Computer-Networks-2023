//21L-7512 Abdullah dar CN lab 2 Q5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_cpu_times(long *total_time, long *idle_time) {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        exit(1);
    }

    char line[256];
    fgets(line, sizeof(line), fp);

    char cpu_label[16];
    long user, nice, system, idle, iowait, irq, softirq;
    sscanf(line, "%s %ld %ld %ld %ld %ld %ld %ld", cpu_label, &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    *total_time = user + nice + system + idle + iowait + irq + softirq;
    *idle_time = idle + iowait;

    fclose(fp);
}

int main() {
    while (1) {
        long total_time1, idle_time1, total_time2, idle_time2;
        get_cpu_times(&total_time1, &idle_time1);
        sleep(1); // Wait for 1 second
        get_cpu_times(&total_time2, &idle_time2);

        long total_diff = total_time2 - total_time1;
        long idle_diff = idle_time2 - idle_time1;

        double utilization = 100.0 * (1.0 - ((double)idle_diff / total_diff));
        printf("Average CPU Utilization Percentage: %.2lf%%\n", utilization);

        sleep(1); // This sleep is optional, it's added to prevent the output from flooding the console
    }

    return 0;
}