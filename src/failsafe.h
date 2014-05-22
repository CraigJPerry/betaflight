#pragma once

#define FAILSAFE_POWER_ON_DELAY_US (1000 * 1000 * 5)

typedef struct failsafeConfig_s {
    uint8_t failsafe_delay;                 // Guard time for failsafe activation after signal lost. 1 step = 0.1sec - 1sec in example (10)
    uint8_t failsafe_off_delay;             // Time for Landing before motors stop in 0.1sec. 1 step = 0.1sec - 20sec in example (200)
    uint16_t failsafe_throttle;             // Throttle level used for landing - specify value between 1000..2000 (pwm pulse width for slightly below hover). center throttle = 1500.
    uint16_t failsafe_min_usec;
    uint16_t failsafe_max_usec;
} failsafeConfig_t;

typedef struct failsafeVTable_s {
    void (*reset)(void);
    bool (*shouldForceLanding)(bool armed);
    bool (*hasTimerElapsed)(void);
    bool (*shouldHaveCausedLandingByNow)(void);
    void (*incrementCounter)(void);
    void (*updateState)(void);
    bool (*isIdle)(void);
    void (*checkPulse)(uint8_t channel, uint16_t pulseDuration);
    bool (*isEnabled)(void);
    void (*enable)(void);

} failsafeVTable_t;

typedef struct failsafe_s {
    const failsafeVTable_t *vTable;

    int16_t counter;
    int16_t events;
    bool enabled;
} failsafe_t;

void useFailsafeConfig(failsafeConfig_t *failsafeConfigToUse);

