#ifndef IRQ_ARCH_CORTEXM_H_INCLUDED
#define IRQ_ARCH_CORTEXM_H_INCLUDED


#define xstr(s)		str(s)
#define str(s)		#s


#define INTC_DEFINE_HANDLER(id, handler)		\
    asm ("   .section .vec_tbl \n\t .org =[%0]\n\t .long %[flag]\n\t" : : )
#endif /*IRQ_ARCH_CORTEXM_H_INCLUDED*/
