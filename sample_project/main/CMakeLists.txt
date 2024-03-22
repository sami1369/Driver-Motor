set(SOURCES main.cpp gpio.cpp i2c.cpp DRV2605.cpp)
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS . ../include)
