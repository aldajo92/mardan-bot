import smbus
import time
# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x03


def write_number(value):
    # bus.write_byte(address, value)
    # bus.write_byte_data(address, 0, value)
    bus.write_i2c_block_data(address, 0, value)
    return -1


def intToByteArray(value):
    result = []
    intBytes = 2
    mask = 0xFF

    for i in range(0, intBytes):
        result.insert(0, value & mask)
        value >>= 8

    return result

# def read_number():
#     local_number = bus.read_byte(address)
#     # number = bus.read_byte_data(address, 1)
#     return local_number


def send_speed(speed_r, speed_l):
    var_r = intToByteArray(speed_r)
    var_l = intToByteArray(speed_l)

    var = var_r + var_l

    write_number(var)
    print "RPI: Hi Arduino, I sent you" + str(var)


while True:
    send_speed(200, 200)
    time.sleep(1)
    send_speed(0, 0)
    time.sleep(1)

    # number = read_number()
    # print "Arduino: Hey RPI, I received a digit ", number
    # print