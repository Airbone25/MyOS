#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(
    uint8_t num,
    uint32_t handler,
    uint16_t selector,
    uint8_t flags)
{
    idt[num].offset_low  = handler & 0xFFFF;
    idt[num].selector    = selector;
    idt[num].zero        = 0;
    idt[num].type_attr   = flags;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

extern void irq0();
extern void irq1();

void idt_init(){
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for(int i=0;i<256;i++)
    {
        idt[i].offset_low = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].type_attr = 0;
        idt[i].offset_high = 0;
    }

    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);

    idt_load(&idtp);
}