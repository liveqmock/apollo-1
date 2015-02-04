#ifndef COMMON_H
#define COMMON_H

#define ANIM_LINE_WIDTH 3


typedef enum {
    TASK_DEFAULT,
    TASK_RUNNING,
    TASK_NOPROBLEM,
    TASK_PROBLEM
} TASKSTAUS;


typedef enum {
    BUTTON_DEFAULT,
    BUTTON_SCALED,
    BUTTON_ENTER,
    BUTTON_LEAVE,
    BUTTON_PRESSED,
    BUTTON_DISABLE
} BUTTONSTATUS;

typedef enum {
    SCORE_NO_BUTTON = 0,
    SCORE_CANCLE_BUTTON,
    SCORE_FIX_BUTTON,
    SCORE_RE_BUTTON
} SCOREBUTTONSTATUS;

typedef enum {
    SCORE_QUESTION,
    SCORE_EXCLAMATION,
    SCORE_NUMBERS
} SCORESTATUS;

#endif // COMMON_H
