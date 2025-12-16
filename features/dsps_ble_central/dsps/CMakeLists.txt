add_subdirectory(portable)
target_include_directories(app PRIVATE
	.
	include
)
target_sources(app PRIVATE
	dsps.c
	dsps_queue.c
	portable/uart/dsps_uart.c
)
