#include "rp2040.h"

#define SYSTICK_CSR    ((volatile uint*)(PPB_BASE + 0xE010))
#define SYSTICK_RVR    ((volatile uint*)(PPB_BASE + 0xE014))
#define SYSTICK_CVR    ((volatile uint*)(PPB_BASE + 0xE018))
#define SYSTICK_CALIB  ((volatile uint*)(PPB_BASE + 0xE01C))

#define NVIC_ISER   ((volatile uint*)(PPB_BASE + 0xE100))
#define NVIC_ICER   ((volatile uint*)(PPB_BASE + 0xE180))
#define NVIC_ISPR   ((volatile uint*)(PPB_BASE + 0xE200))
#define NVIC_ICPR   ((volatile uint*)(PPB_BASE + 0xE280))
#define NVIC_IPR0	((volatile uint*)(PPB_BASE + 0xE400))
#define NVIC_IPR1	((volatile uint*)(PPB_BASE + 0xE404))
#define NVIC_IPR2	((volatile uint*)(PPB_BASE + 0xE408))
#define NVIC_IPR3	((volatile uint*)(PPB_BASE + 0xE40C))
#define NVIC_IPR4	((volatile uint*)(PPB_BASE + 0xE410))
#define NVIC_IPR5	((volatile uint*)(PPB_BASE + 0xE414))
#define NVIC_IPR6	((volatile uint*)(PPB_BASE + 0xE418))
#define NVIC_IPR7	((volatile uint*)(PPB_BASE + 0xE41C))

#define CPUID       ((volatile uint*)(PPB_BASE + 0xED00))
#define ICSR        ((volatile uint*)(PPB_BASE + 0xED04))
#define VTOR        ((volatile uint*)(PPB_BASE + 0xED08))
#define AIRCR       ((volatile uint*)(PPB_BASE + 0xED0C))
#define SCR         ((volatile uint*)(PPB_BASE + 0xED10))
#define CCR         ((volatile uint*)(PPB_BASE + 0xED14))
#define SHPR2       ((volatile uint*)(PPB_BASE + 0xED1C))
#define SHPR3       ((volatile uint*)(PPB_BASE + 0xED20))
#define SHCSR       ((volatile uint*)(PPB_BASE + 0xED24))

#define MPU_TYPE    ((volatile uint*)(PPB_BASE + 0xED90))
#define MPU_CTRL    ((volatile uint*)(PPB_BASE + 0xED94))
#define MPU_RNR     ((volatile uint*)(PPB_BASE + 0xED98))
#define MPU_RBAR    ((volatile uint*)(PPB_BASE + 0xED9C))
#define MPU_RASR    ((volatile uint*)(PPB_BASE + 0xEDA0))


#define SYS_CSR_COUNTFLAG   (1 << 16)
#define SYS_CSR_CLKSOURCE   (1 << 2)
#define SYS_CSR_TICKINT     (1 << 1)
#define SYS_CSR_ENABLE      (1 << 0)
#define SYS_RVR_RELOAD      (0x00ffffff)
#define SYS_CVR_CURRENT     (0x00ffffff)
#define SYS_CALIB_NOREF     (1 << 31)
#define SYS_CALIB_SKEW      (1 << 30)
#define SYS_CALIB_TENMS     (0x00ffffff)

#define ICSR_NMIPENDSET		(1 << 31)
#define ICSR_PENDSVSET		(1 << 28)
#define ICSR_PENDSVCLR		(1 << 27)
#define ICSR_PENDSTSET		(1 << 26)
#define ICSR_PENDSTCLR		(1 << 25)
#define ICSR_ISRPREEMPT		(1 << 23)
#define ICSR_ISRPENDING		(1 << 22)
#define ICSR_VECTPENDING	(0x1FF << 12)
#define ICSR_VECTACTIVE		(0x1FF << 0)

#define VTOR_TBLOFF			0xFFFFFF00

#define AIRCR_SYSRESETREQ   (1 << 2)
#define AIRCR_VECTCLRACTIVE	(1 << 1)

#define SCR_SEVONPEND       (1 << 4)
#define SCR_SLEEPDEEP       (1 << 2)
#define SCR_SLEEPONEXIT     (1 << 1)

#define SHPR2_PRI_11		(3 << 30)
#define SHPR3_PRI_15		(3 << 30)
#define SHPR3_PRI_14		(3 << 22)

#define SHCSR_SVCALLPENDED  (1 << 15)

#define MPU_CTRL_PRIVDEFENA	(1 << 2)
#define MPU_CTRL_HFNMIENA	(1 << 1)
#define MPU_CTRL_ENABLE		(1 << 0)
#define MPU_RNR_REGION		(0xF << 0)
#define MPU_RBAR_ADDR		(0xFFFFFF00)
#define MPU_RBAR_VALID		(1 << 4)
#define MPU_RBAR_REGION		(0xF << 0)
#define MPU_RASR_ATTRS		(0xFFFF << 16)
#define MPU_RASR_SRD		(0xFF << 8)
#define MPU_RASR_SIZE		(0x1F << 1)
#define MPU_RASR_ENABLE		(1 << 0)



void systick(uint ticks) {
	*SYSTICK_CSR = SYS_CSR_ENABLE | SYS_CSR_TICKINT | SYS_CSR_CLKSOURCE;
	*SYSTICK_RVR = ticks;
	*SYSTICK_CVR = ticks;
}
