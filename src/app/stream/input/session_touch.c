#include "stream/input/session_input.h"
#include <stdio.h>
#include <time.h>

void stream_input_handle_touch(const stream_input_t *input, const SDL_TouchFingerEvent *event) {
    static FILE *debuglog = NULL;
    if (!debuglog) {
        debuglog = fopen("/tmp/moonlight_debug.txt", "w+");
    }
    
    if (debuglog) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timestamp[64];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
        
        fprintf(debuglog, "[%s] Touch event: type=%u, touchId=%lld, fingerId=%lld, x=%.3f, y=%.3f, pressure=%.3f\n",
                timestamp, event->type, (long long)event->touchId, (long long)event->fingerId, 
                event->x, event->y, event->pressure);
        fflush(debuglog);
    }

    // acabou!
    return;
    if (input->view_only) {
        return;
    }
    uint8_t type;
    switch (event->type) {
        case SDL_FINGERDOWN:
            type = LI_TOUCH_EVENT_DOWN;
            break;
        case SDL_FINGERUP:
            type = LI_TOUCH_EVENT_UP;
            break;
        case SDL_FINGERMOTION:
            type = LI_TOUCH_EVENT_MOVE;
            break;
        default:
            return;
    }
    LiSendTouchEvent(type, event->fingerId, event->x, event->y, event->pressure, 0, 0, 0);
}
