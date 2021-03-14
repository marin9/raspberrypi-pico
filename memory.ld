MEMORY {
	ram : ORIGIN = 0x10000000, LENGTH = 1024
}

SECTIONS {
	.text : { *(.text*) } > ram
}

