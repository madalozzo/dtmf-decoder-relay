# DTMF Decoder Relay

Created by Saulo Madalozzo, saulo.zz@gmail.com March/2017
based on dtmf_loopback by Igor Ramos

Receive a DTMF (Dual Tone Multi Frequency) signal using a shield.

You will need:
- One Arduino or compatible.
- Dossant DTMF shield - https://www.seeedstudio.com/DTMF(Dual-Tone-Multi-Frequency)-Shield-p-1839.html
- Relays conected to 2, 3, 4 and 5, or other thing

This program is for activating digital outputs of Arduino based on DTMF tones.
Its intend to be used in radio stations to do some functions based on audio like turn on or off some equipments at exact moment.

It receive one tone (doesn't matter what), and must receive the second one in less than 1000ms (can be configured in code).
The second tone can be 2, 3, 4 or 5, and activate respective digital output for 500ms.
    
