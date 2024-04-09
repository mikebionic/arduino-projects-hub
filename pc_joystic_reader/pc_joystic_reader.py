import serial
import sys
import time

import pyautogui
pyautogui.FAILSAFE = False

print(len(sys.argv))
serial_port = sys.argv[1] if len(sys.argv) > 1 else '/dev/ttyACM0'
baud_rate = int(sys.argv[2]) if len(sys.argv) > 2 else 9600

screenWidth  = int(sys.argv[3]) if len(sys.argv) > 3 else 1366
screenHeight = int(sys.argv[4]) if len(sys.argv) > 4 else 768

maxValueX = 1023
maxValueY = 1023

ser = serial.Serial(serial_port, baud_rate)

while True:
    serial_stream = ser.readline()
    if serial_stream:
        command = str(serial_stream.decode()).strip()
        ser.flushInput()
        # print("new command:", command)

        if command == 'up':
            pyautogui.press("up")
            time.sleep(0.6)

        if command == 'down':
            pyautogui.press("down")

        else:
            try:
                if len(command) < 3:
                    raise Exception
                splitted = command.strip().split(':')
                if len(splitted) < 2:
                    raise Exception

                xdata, ydata = splitted[0].strip(), splitted[1].strip()
                if len(xdata) > 0 and len(ydata) > 0:
                    xdata, ydata = int(xdata), int(ydata)
                    screen_x = xdata*screenWidth/maxValueX
                    screen_y = ydata*screenHeight/maxValueY

                    print(xdata, ydata)
                    pyautogui.moveTo(screen_x, screen_y)
                if len(splitted) > 2:
                    joybutton = int(splitted[2].strip())
                    if joybutton == 1:
                         pyautogui.press("space")

            except Exception as ex:
                print(ex)


# # checking UI
# pyautogui.mouseInfo()
# pyautogui.moveTo(69,750)
# pyautogui.click(69,750,duration=1)
# pyautogui.write('Chrome')
# pyautogui.moveTo(478,363,duration=1)
# pyautogui.click(478,363,duration=1)
# pyautogui.moveTo(177,58,duration=1)
# pyautogui.click(177,58,duration=1)
# pyautogui.write('https://www.youtube.com/')
# pyautogui.press('enter')
# pyautogui.moveTo(458,135,duration=2)
# pyautogui.click(458,135,duration=2)
# pyautogui.write('perfect strangers')
# pyautogui.press('Enter')
# pyautogui.moveTo(763,222,duration=3)
# pyautogui.click(763,222,duration=3)
# pyautogui.moveTo(1253,27,duration=3)
# pyautogui.click(1253,27,duration=3)
