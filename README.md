# Smart Waste Solutions: Integrating AI in Next-Gen Waste Sorting

![Diagram](/demo/blog.jpg)

Have you ever thought of using AI to sort your customer's waste? There are many companies & waste management contractors in the market globally who want to maximize recycling and save the environment. But, the main problem is people tend to throw the waste in the bin they want or nearest to them, regardless of waste signs & symbols located on bins. Some of the key reasons are people: 
- are unaware of the categories (usually there is a variation of categories)
- don't know which waste is classified under what category
- don't have time to think/wait
- and many more... 

Due to the unsorted waste collection at the source, it becomes difficult for the recycling facility to sort 100% accurately. This blog shows the procedure of setting up the system (hardware & software) at/near waste collection bins. 

## Hardware Requirements
1. Raspberry Pi
2. Camera
3. Arduino Uno
4. Breadboard
5. Wires & LED Lights

## Software Requirements
1. Python
2. Arduino IDE

## Steps.
1. Configure Raspberry Pi Setup - [Getting started - Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/computers/getting-started.html)
2. Install Python if not installed.
3. SSH your Raspberry Pi into your local system or connect with HDMI display, keyboard & mouse to set up the system. _This is only required once_
4. Create a Project Directory. Create Python Virtual Env.
5. Install packages required for running the inference. You can run the trained model Inference. This document is not meant to explain [Ultralytics YOLO model training] (https://docs.ultralytics.com/modes/train/) & various ways of optimizing inferences for your custom use-cases & requirements using [Roboflow](https://inference.roboflow.com/) or [Ultralytics HUB Inference ](https://docs.ultralytics.com/hub/inference-api/). The Waste Category Predictor (AI Model) predicts the waste type and sends the signal to Arduino.
6. Install [Arduino IDE](https://www.makeuseof.com/how-to-install-and-run-arduino-ide-on-raspberry-pi/) in Raspberry Pi.
7. Connect your [Arduino with Baseboard](https://roboticsbackend.com/arduino-led-complete-tutorial/) & Setup the led lights. Based on the custom blinking you want for each port, Send the Code to the Arduino system. Remember the custom serial constant you set for each LED light.
8. Install pyserial package and [connect](https://projecthub.arduino.cc/ansh2919/serial-communication-between-python-and-arduino-663756) your app with LED using serial commands. 
9. Now, you are all set, once you connect the camera with the Raspberry Pie, Run the Python App.

Some of the steps to configure in VS code are elaborated on at the end of this blog.

## Workflow
- The user approaches the bin to dispose of the waste item. 
- When the user points the waste item to the camera, then live video frames are sent to the Raspberry where the Python Code is running. 
- AI model predicts the waste type & categorizes it. 
- Based on the classified waste, the response is sent back to the LED light (installed on top of the bin) so the user can get guided where s/he has to throw the waste based on the Light color.


Generally, Raspberry Pi has less computing power affecting the prediction. To tackle this problem, Connect [Coral Edge TPU](https://docs.ultralytics.com/guides/coral-edge-tpu-on-raspberry-pi/) with Raspberry Pi if you want to run locally. Otherwise, you can connect your camera live streams to the remote server (running either in GCP/AWS/Azure or any other cloud computing platform) using a WiFi connection _(Make sure you set up proper authentication, making your system secure)_. 
This blog doesn't provide Python code & Arduino js code. But if you want to learn more, feel free to [connect](https://www.linkedin.com/in/jivaniyash/) with me. I would help you set up the configuration & happy to work on building projects like these.


```md
# Steps to Install Packages in Raspberry Pi
## 1. Create & Activate Virtualenv, Install Dependencies

python3 -m venv .venv
.\.venv\Scripts\activate
pip install -r .\requirements.txt

yolo predict model=yolov8s.pt source=0 show=True

# Steps YOLO

## With using Docker
### Install Docker
sudo apt update
sudo apt upgrade -y

sudo reboot

### Install Docker on Raspberry Pi

curl -sSL https://get.docker.com | sh

cd ./
Pull & Run docker image

t=ultralytics/ultralytics:latest-arm64 && sudo docker pull $t && sudo docker run -it --ipc=host $t

## Without using docker

### 1.Create a directory

mkdir waste_sorter

### 2. Create & Activate Virtualenv, Install Dependencies
sudo apt update
sudo apt install python3-pip -y
pip install -U pip

python3 -m venv .venv
.\.venv\Scripts\activate
pip install -r .\requirements.txt

https://docs.ultralytics.com/guides/raspberry-pi/#start-without-docker


pip install ultralytics[export]
```

```python
# test.py to test Led light configuration
# You need to adjust the code as per your requirements
import random

ser = serial.Serial(port='/dev/ttyACM0', baudrate=9600)

time.sleep(2)

def start_led(n):
	'''Lit Led light for 1 sec & Dim it for n times'''
	for _ in range(n):
		print('start_led function - Command D')
		ser.write(b'D')
		time.sleep(1)

start_led(5)


while True:
	print(f'''It's A, class 0''')
	ser.write(b'A')
	print(f'''It's B, class 1''')
	ser.write(b'B')
	print(f'''It's C, class 2''')
	ser.write(b'C')
	time.sleep(20)
	break


while True:
    try:
        command_input = input('Please Enter Command - 0 for blue, 1 for yellow, 2 for green :')
        command = int(command_input)
    except Exception as e:
        print(f'Error Occured :{e}')
        print('Please enter a valid command')
        
    if command == 0:
        ser.write(b'A')
    elif command == 1:
        ser.write(b'B')
    elif command == 2:
        ser.write(b'C')
```


