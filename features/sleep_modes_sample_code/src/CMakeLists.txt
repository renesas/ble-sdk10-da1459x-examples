add_subdirectory(cli_app)
add_subdirectory(cli_deep_sleep)
add_subdirectory(cli_hibernation)
add_subdirectory(cli_por_gpio)
add_subdirectory(cli_rtc)
target_sources(app PRIVATE
	sleep_modes_task.c
)
