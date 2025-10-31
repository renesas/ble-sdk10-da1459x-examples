target_include_directories(app PRIVATE .)
target_sources(app PRIVATE
	main.c
	glucose_sensor_task.c
	glucose_sensor_database.c
)
