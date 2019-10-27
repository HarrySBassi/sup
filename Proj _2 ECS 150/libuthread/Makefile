# Target library
targets := \
  queue.o \
	uthread.o \
	context.o \
	preempt.o \

lib := libuthread.a

all: $(lib)

CC	:= gcc
CFLAGS	:= -Wall -Werror
CFLAGS	+= -g


ifneq ($(v),1)
Q = @
endif

deps	:= $(patsubst %.o,%.d,$(targets))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)


$(lib): $(targets)
	@echo "make lib"
	$(Q)ar rcs $(lib) $(targets)


%.o:%.c %.h
	@echo "CC  $@"
	$(Q)$(CC) $(CFLAGS)  -c -o $@ $< $(DEPFLAGS)

clean:
	@echo "CLEAN"
	$(Q)@rm -f $(targets) $(lib) $(deps)
