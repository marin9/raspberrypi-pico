MEMORY {
	ram : ORIGIN = 0x20000000, LENGTH = 4096
}

SECTIONS {
	.text : { *(.text*) } > ram
}
