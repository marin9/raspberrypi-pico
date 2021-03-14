MEMORY {
	ram : ORIGIN = 0x20000000, LENGTH = 1024
}

SECTIONS {
	.text : { *(.text*) } > ram
}

