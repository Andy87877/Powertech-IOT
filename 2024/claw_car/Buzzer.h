#ifndef ARDUINO_BUZZER_H
#define ARDUINO_BUZZER_H

void _beep( int times )
{
    for( int i=0; i<times; i++ )
    {
        tone( BUZZER, 1000, 100);
        delay(200);
    }

}

#endif