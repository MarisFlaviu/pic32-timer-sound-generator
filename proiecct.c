#include <xc.h>

#define SYS_CLK 80000000UL

#define BUTTON_PORT PORTFbits.RF0
#define BUTTON_TRIS TRISFbits.TRISF0

#define PWM_TRIS TRISBbits.TRISB14
#define PWM_ANS ANSELBbits.ANSB14
#define PWM_RPB RPB14R

void DelayMs(int ms);
void SetFreqPWM(int freq);
void PWMInit(void);

typedef struct {
    int freq;      // Hz, 0 = pauza
    int duration;  // ms
} Note;

Note melody[] = {
    {330, 200}, {0, 100},
    {392, 200}, {0, 100},
    {440, 200}, {0, 100},
    {494, 200}, {0, 100},
    {523, 200}, {0, 100},
    {659, 200}, {0, 100},
    {587, 200}, {0, 100},
    {523, 200}, {0, 100},
    {494, 400}, {0, 200},
    {440, 200}, {0, 100},
    {392, 200}, {0, 100},
    {330, 400}, {0, 400}
};

#define MELODY_LENGTH (sizeof(melody) / sizeof(Note))

int main(void) {
    int prev = 1;

    BUTTON_TRIS = 1;

    PWMInit();

    while(1) {
        int btn = BUTTON_PORT;

        if(prev == 1 && btn == 0) {
            int i;

            for(i = 0; i < MELODY_LENGTH; i++) {
                SetFreqPWM(melody[i].freq);
                DelayMs(melody[i].duration);
            }

            SetFreqPWM(0);
            DelayMs(300);
        }

        prev = btn;
        DelayMs(10);
    }

    return 0;
}

void DelayMs(int ms) {
    volatile unsigned int i;

    while(ms--) {
        for(i = 0; i < 40000; i++) {
            asm("nop");
        }
    }
}

void SetFreqPWM(int freq) {
    unsigned int pr3;
    int presc;

    if(freq <= 0) {
        T3CONbits.ON = 0;
        LATBbits.LATB14 = 0;
        return;
    }

    T3CONbits.ON = 0;

    if(freq >= 300) {
        presc = 6; // 1:64
        pr3 = (unsigned int)(SYS_CLK / (64.0 * freq));
    } else {
        presc = 7; // 1:256
        pr3 = (unsigned int)(SYS_CLK / (256.0 * freq));
    }

    if(pr3 > 0xFFFF) {
        pr3 = 0xFFFF;
    }

    if(pr3 < 1) {
        pr3 = 1;
    }

    PR3 = pr3;
    OC1R = pr3 / 2;
    OC1RS = pr3 / 2;

    T3CONbits.TCKPS = presc;
    TMR3 = 0;
    T3CONbits.ON = 1;
}

void PWMInit(void) {
    PWM_ANS = 0;
    PWM_TRIS = 0;

    PWM_RPB = 0x0C; // OC1 pe RB14

    T3CON = 0;
    TMR3 = 0;

    OC1CON = 0;
    OC1CONbits.OCM = 0b110;  // PWM mode
    OC1CONbits.OCTSEL = 1;   // Timer3
    OC1CONbits.ON = 1;

    SetFreqPWM(0);
}