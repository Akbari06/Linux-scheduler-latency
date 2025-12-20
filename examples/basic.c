#include "schedlat.h"

int main(void) {
    schedlat_config_t cfg = {
        .samples = 10000,
        .threads = 4,
        .busy_wait = 1,
        .pin_single_cpu = 1
    };

    schedlat_result_t res;
    if (schedlat_run(&cfg, &res) != 0) {
        return 1;
    }

    schedlat_free(&res);
    return 0;
}
