cmake_minimum_required(VERSION 3.20.0)

project(suoserial_host)

add_executable(suoserial_host)

target_sources(suoserial_host PRIVATE
	host_suoserial.c
)
