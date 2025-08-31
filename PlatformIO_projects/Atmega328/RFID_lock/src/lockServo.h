#include <Servo.h>
#include "common.h"

extern Servo lockServo;

extern int startPosition;
extern int endPosition;
extern boolean isLocked;

extern void openLock();
extern void closeLock();