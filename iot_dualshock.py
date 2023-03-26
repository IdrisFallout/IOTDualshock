import socket
import pygame

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# use (192.168.137.110, 192.168.1.110)
host = '192.168.1.110'
message = 0

# connect to the server
client_socket.connect((host, 80))
toggle = [None, None]
counter = 0

mystring_buffer = ["", ""]
mystring_counter = 0
the_message = ["", ""]

# Initialize Pygame
pygame.init()
joystick_count = pygame.joystick.get_count()

# Get the controller
controller = pygame.joystick.Joystick(0)
controller.init()


def make_request(message):
    send = ""
    send += str(message[0]) + ":"
    if message[1] is not None:
        if str(message[1][0]) == "left_x" or str(message[1][0]) == "right_x" or str(message[1][0]) == "left_y" or str(message[1][0]) == "right_y":
            return
        else:
            send += str(message[1][0]) + "/" + str(message[1][1])
    else:
        send += "None"

    client_socket.send(str(send).encode() + b'\n')
    print(send)


def send_message(message):
    if message[0] is None and message[1] is None:
        return
    global counter

    if message[1] is not None:
        if counter == 0:
            toggle[0] = message[1]
            counter = 1
        elif counter == 1:
            toggle[1] = message[1]
            counter = 0
        if toggle[0] != toggle[1]:
            make_request(message)
            # print(message)
            return
    # print(message)
    make_request(message)


def process_axis(axis_name, axis_value):
    new_axis_value = ""
    if axis_name == "axis_0":
        if axis_value < -0.5:
            new_axis_value = "-1.0"
        elif axis_value > 0.5:
            new_axis_value = "1.0"
        else:
            new_axis_value = "0.0"
        return ["left_x", new_axis_value]
    elif axis_name == "axis_1":
        if axis_value < -0.5:
            new_axis_value = "1.0"
        elif axis_value > 0.5:
            new_axis_value = "-1.0"
        else:
            new_axis_value = "0.0"
        return ["left_y", new_axis_value]
    elif axis_name == "axis_2":
        if axis_value < -0.5:
            new_axis_value = "-1.0"
        elif axis_value > 0.5:
            new_axis_value = "1.0"
        else:
            new_axis_value = "0.0"
        return ["right_x", new_axis_value]
    elif axis_name == "axis_3":
        if axis_value < -0.5:
            new_axis_value = "1.0"
        elif axis_value > 0.5:
            new_axis_value = "-1.0"
        else:
            new_axis_value = "0.0"
        return ["right_y", new_axis_value]
    elif axis_name == "axis_4":
        if axis_value < -0.5:
            new_axis_value = "-1.0"
        elif axis_value > 0.5:
            new_axis_value = "1.0"
        else:
            return
        return ["left_trigger", new_axis_value]
    elif axis_name == "axis_5":
        if axis_value < -0.5:
            new_axis_value = "-1.0"
        elif axis_value > 0.5:
            new_axis_value = "1.0"
        else:
            return
        return ["right_trigger", new_axis_value]
    else:
        return [axis_name, axis_value]


def optimize_message(message):
    global mystring_buffer, mystring_counter
    mystring = str(message)
    if mystring_counter == 0:
        mystring_buffer[0] = mystring
        mystring_counter = 1
    elif mystring_counter == 1:
        mystring_buffer[1] = mystring
        mystring_counter = 0

    if mystring_buffer[0] != mystring_buffer[1]:
        if message is not None:
            return message
    else:
        return


if joystick_count > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print("DualShock 4 detected.")

    while True:
        pygame.event.pump()
        for event in pygame.event.get():
            data = [None, None]
            if event.type == pygame.JOYBUTTONDOWN:
                button = event.button
                data[0] = button
            elif event.type == pygame.JOYAXISMOTION:
                # An axis was moved
                axis_name = "axis_" + str(event.axis)
                axis_value = event.value
                data[1] = optimize_message(process_axis(axis_name, axis_value))

            send_message(data)

else:
    print("No DualShock 4 detected.")
