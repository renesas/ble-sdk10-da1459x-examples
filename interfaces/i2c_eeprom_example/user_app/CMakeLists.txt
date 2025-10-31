target_include_directories(app PRIVATE .)
target_sources(app PRIVATE
	app_gpio.c
	i2c_task.c
)
