global irq1
global irq0

extern keyboard_handler

extern timer_handler

irq0:
    pusha
    call timer_handler
    popa
    iretd

irq1:
    pusha
    call keyboard_handler
    popa
    iretd
    iretd