SERIAL_DEVICE		= /dev/ttyACM*

all:
	platformio -f -c vim run

upload:
	platformio -f -c vim run --target upload

clean:
	platformio -f -c vim run --target clean

update:
	platformio -f -c vim update

find-serial:
	ls -1 $(SERIAL_DEVICE)
	$(eval USBTTY=$(shell ls -1 $(SERIAL_DEVICE) | head -n1 ))

monitor: find-serial
	screen $(USBTTY)
