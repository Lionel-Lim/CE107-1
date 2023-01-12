
import cv2
import numpy as np
import paho.mqtt.client as mqtt
import time

# Read MQTT Data
with open('Resource/SourceCode/ImageRecognition/config/mqttConfig.txt') as f:
    line = f.read().split(",")
    # lines = f.readlines()
    # print(lines)
    username = line[0]
    password = line[1]

# Check Running Time
start_time = time.time()

# Global Variables
Connected = False
broker = "mqtt.cetools.org"
port = 1884

# function to display the coordinates of
# of the points clicked on the image
def click_event(event, x, y, flags, params):
 
    # checking for left mouse clicks
    if event == cv2.EVENT_LBUTTONDOWN:
 
        # displaying the coordinates
        # on the Shell
        print(x, ' ', y)
 
        # displaying the coordinates
        # on the image window
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(frame, str(x) + ',' +
                    str(y), (x,y), font,
                    1, (255, 0, 0), 2)
        cv2.imshow('Result', frame)
 
    # checking for right mouse clicks    
    if event==cv2.EVENT_RBUTTONDOWN:
 
        # displaying the coordinates
        # on the Shell
        print(x, ' ', y)
 
        # displaying the coordinates
        # on the image window
        font = cv2.FONT_HERSHEY_SIMPLEX
        b = frame[y, x, 0]
        g = frame[y, x, 1]
        r = frame[y, x, 2]
        cv2.putText(frame, str(b) + ',' +
                    str(g) + ',' + str(r),
                    (x,y), font, 1,
                    (255, 255, 0), 2)
        cv2.imshow('Result', frame)

# MQTT Callback function
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to broker")
        global Connected                #Use global variable
        Connected = True                #Signal connection 
    else:
        print("Connection failed")

# Capture viedeo from the camera
VideoSignal = cv2.VideoCapture(0)
# Load YOLO weights and cfg
YOLO_net = cv2.dnn.readNet("Resource/SourceCode/ImageRecognition/config/yolov3.weights","Resource/SourceCode/ImageRecognition/config/yolov3.cfg")


# YOLO Classes
classes = []
with open("/Users/dylim/Downloads/object_tracking/yolo/yolo.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]
layer_names = YOLO_net.getLayerNames()
output_layers = [layer_names[i - 1] for i in YOLO_net.getUnconnectedOutLayers()]

# Calibrate coordinate
worldPoints = np.array([[-0.8, 4.1], [0.9, 6.8], [-4.45, 6.8], [-3.7, 2.3]],dtype=np.float32)
imagePoints = np.array([[640, 360], [470, 360], [800, 350], [1150, 460]],dtype=np.float32)

# ret, rvec1, tvec1=cv2.solvePnP(worldPoints,imagePoints,newcam_mtx,dist)
#Processing

# MQTT Set up
client = mqtt.Client("DYLim")
client.username_pw_set(username, password=password)
client.on_connect= on_connect
client.connect(broker, port=port)
client.loop_start()
while Connected == False:
    print("Try to connect...")
    time.sleep(1)

while True:
    ret, frame = VideoSignal.read()
    h, w, c = frame.shape
    cx = int(w/2)
    cy = int(h/2)
    # YOLO Input
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0),True, crop=False)
    YOLO_net.setInput(blob)
    outs = YOLO_net.forward(output_layers)

    class_ids = []
    confidences = []
    boxes = []
    # print(outs)
    for out in outs:

        for detection in out:

            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]

            if confidence > 0.2:    # Check confidence
                # Object detected
                center_x = int(detection[0] * w)
                center_y = int(detection[1] * h)
                dw = int(detection[2] * w)
                dh = int(detection[3] * h)
                # Rectangle coordinate
                x = int(center_x - dw / 2)
                y = int(center_y - dh / 2)
                boxes.append([x, y, dw, dh])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.45, 0.4)

    personNum = 0
    for i in range(len(boxes)):
        if i in indexes:
            if class_ids[i] == 0:   #Find only person which is index 0
                personNum = personNum + 1   #Count person
                x, y, w, h = boxes[i]
                label = str(classes[class_ids[i]])
                score = confidences[i]
                boxText = "{} : {}%".format(label, round(score * 100,2))

                # 경계상자와 클래스 정보 이미지에 입력
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 5)
                cv2.putText(frame, boxText, (x, y - 20), cv2.FONT_ITALIC, 0.5, (255, 255, 255), 1)
    # MQTT Publish
    # print(personNum)
    # print(int(time.time() - start_time))
    if Connected == True and (int(time.time() - start_time) % 5) == 0:
        client.publish("student/CASA0019/TwinLab/RoomCapacity", personNum)
    # Show result
    cv2.imshow("Result", frame)
    cv2.setMouseCallback('Result', click_event)
    # cv2.imshow("blob", b)

    if cv2.waitKey(100) > 0:
        break