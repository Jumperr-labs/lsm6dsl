$(shell mkdir -p modeling-framework/LSM6DSL/_build)

PERIPHERAL_CFLAGS =  $(CFLAGS)

ifeq ($(OPTIMIZE), 0)
PERIPHERAL_CFLAGS += -g -ggdb
endif

modeling-framework/LSM6DSL/_build/LSM6DSL.o: modeling-framework/LSM6DSL/LSM6DSL.cpp
	$(CC) -fPIC -c -o $@ $^ $(PERIPHERAL_CFLAGS) -I./modeling-framework/LSM6DSL -I./modeling-framework/include

modeling-framework/LSM6DSL/_build/LSM6DSL.so: modeling-framework/LSM6DSL/_build/LSM6DSL.o obj/src/core/ModelingFramework.o
	$(CC) -shared -o $@ $^

LSM6DSL: modeling-framework/LSM6DSL/_build/LSM6DSL.so