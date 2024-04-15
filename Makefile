.PHONY: all clean

AS = as
LD = ld
ASFLAGS = --gstabs

TARGET = 1
OBJS = 1.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $(TARGET)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
