target_sources(app PRIVATE
	BusFault_handler.c
	BusFault_handler_asm.S
	HardFault_handler.c
	MemManage_handler.c
	MemManage_handler_asm.S
	UsageFault_handler.c
	UsageFault_handler_asm.S
	fault_handling.c
)
