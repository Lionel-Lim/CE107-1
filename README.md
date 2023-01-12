<img width="452" alt="image" src="https://user-images.githubusercontent.com/93122551/212160347-6ef4ad3b-408a-476f-a195-c4133cac1396.png">

Project: CE107-1
Group Name: TwinLab
Date: 12th January 2023

*Rita *Leo *Lucy *DY

1.	Introduction

The aim of this report is to provide detailed information on the TwinLab-CE107 project. This project was initialised in mid-November 2022 and concluded on 16th December 2022.  

UCL East (One Pool Street) opened its doors in Autumn 2022. MSc Connected Environments is taught in CE107 Lab which is based on the first floor. As a newly operated building, it is thought that developing a digital twin of the lab would be beneficial for long-term management. Arup (2019) noted that digital twin can optimise the use of materials, improve user experience and predict component maintenance and replacement.  In addition, the digital twin has the ability to achieve the United Nations' Sustainable Development Goals that address rapid urbanisation, population growth and escalating infrastructure costs. One of the aims of this project is to build a digital twin of the CELab and display its parameters within a mobile app. 

 ![image](https://user-images.githubusercontent.com/93122551/212160682-64f77586-3a5e-4f4b-9574-1af1f0aa039b.jpeg)
Figure 1: CE107 Lab.	

2.	Literature Review
2.1 Space occupancy and current applications
Occupancy of spaces is currently implemented across a variety of businesses such as shopping centres, shops, gyms, offices and public transport. Transport for London (TFL) has real-time line and station crowding available on tubestatus.net website as well as predictions of the busiest period of the day (TubeStatus.net, 2022).  Medium (2018) has explored seven different sensors that are deployed within spaces to count occupancy. Each sensor has the benefits and challenges of counting accurately or ethically, as noted in Table 1. 

<img width="452" alt="image" src="https://user-images.githubusercontent.com/93122551/212160815-5263dfc7-2197-4d36-9208-c0d88ad3053d.png">
Figure 2: Prediction of busiest time on TFL trains (TubeStatus, 2022).

The project briefly explored the occupancy detecting technology that is currently on the market and their benefits and challenges. 

Density Open Areas – Uses depth data and machine learning to anonymously count. 

Density Entry – Uses infrared lasers to count people walking in and out of the room/space. 

Break-beam (AIR) – Break beam sensors have an infrared emitter and an infrared receiver. Due to human complex movement, its accuracy is questionable. 

WiFi Tracking – Phone WiFi tries to connect to available WiFi transmitters. Often used in retails and corporate offices. Seen as an invasive and unethical approach and is inaccurate at room level. 

Seat Sensors - Above each seat/underneath each desk a sensor is placed which counts seat specific data. Considered as low cost however battery replacement can be an issue on a large-scale project. 

Thermal Camera – Uses body heat and computer vision via thermal camera to detect human activity. Considered as unreliable accuracy. 

Cameras or Optical Vision Sensors – Smart cameras use second-by-second change in pixel to detect movement and identify people or other objects in a scene, Mostly used in retail building security and corporate offices. Considered inexpensive and provides impressive analytics. Limitations include field of view, privacy issues, ethics and security as camera systems are ideal for hacking. 
Table 1: Occupancy detecting technology on the market (Medium, 2018).

2.2 Importance of Air Quality
For everyone living in a metropolitan area, the importance of air quality is highly important. Defra (2022) reported that products generated from space heating, power generation and motor vehicle traffic are the major contributing factors to air pollution. Air pollution in Greater London can be detrimental to human health, as noted in Table 2. 

<img width="450" alt="image" src="https://user-images.githubusercontent.com/93122551/212161058-83012d46-7b05-4d3d-8a4e-6ed70c8fd712.png">

Figure 3: Newspaper Article about air pollution (Invisible Dust, 2022).

Pollutant and Health effects at very high levels
Nitrogen Dioxide, Sulphur Dioxide, Ozone - Irritate the airways of the lungs, increasing the symptoms of those suffering from lung diseases
Particles -	Fine particles can be carried deep into the lungs causing inflammation and worsening of heart and lung diseases
Carbon Monoxide - Prevents uptake of oxygen by the blood – reducing oxygen supply to the heart, particularly those suffering from heart disease

2.3 Noise Impacts 
Ecophon (2022) noted that excess noise within educational facilities will negatively impact learning as well as physical and mental health. According to the World Health Organisation (WHO), the safe level of noise in a classroom cannot exceed 35 decibels, and anything above this level will impair the ability to learn. 

<img width="261" alt="image" src="https://user-images.githubusercontent.com/93122551/212161434-9bc61f80-6a8d-4db7-a428-1186a18a5b56.png">
Table 3: Possible noise generated within CE107 Lab. 


2.4 Temperature within a room
Automated ventilation/heating/air conditioning within smart buildings has been on the rise, meaning that regulating temperature within the room and/or building is easier (Alawadi et al., 2020). A study in Helsinki University of Technology (2015) showed that performance increases with temperatures up to 21-22 degrees. Any temperatures above or below are stated to hinder the highest productivity. 


3.	Aims and Objectives 
First aim is to replicate the CE107 Lab structure and convert it to a digital twin using Light Detection and Ranging (LiDAR) camera to scan the lab and upload it to Unity to display accurate room dimensions. 
Second aim is to display real-time data collected from three sensors in the CE107 lab using MQTT to display real-time data on physical and digital devices. 
Third aim is to display the occupancy of the CE107 Lab by using a fixed-point camera and AI code to detect people in the room and display the data on the devices. LED lights will indicate the percentage of the available capacity. 

3.1 Team Structure and Responsibilities
Due to time constraints, it was thought that each member of the team would have an allocated task to undertake to speed up the project.

<img width="392" alt="image" src="https://user-images.githubusercontent.com/93122551/212162844-f2a0b377-fb6d-4a7d-8fbc-e7d795376a99.png">
Table 4: Allocated tasks for each team member. 

3.2 Project Plan 
To help keep track of the progress of the whole project, a project plan was used, as seen in Table 5 below. 


<img width="698" alt="image" src="https://user-images.githubusercontent.com/93122551/212162938-678306eb-9339-4aac-8c0d-9906a881905d.png">
Table 5: Project Plan.

4.	Data Feed
The main data of the project are spatial environmental data, data device model, and digital twin model. Figure 4 shows the sources and methods used to collect and process the data.

<img width="452" alt="image" src="https://user-images.githubusercontent.com/93122551/212163350-921090a7-e160-4e39-9540-1ed71563d8ee.png">
Figure 4: Data feeding process.

4.1. Environmental Data
Various environmental data was collected for the project, including occupancy, temperature, air quality, and noise. Occupancy data was collected using a webcam that uses the YOLOv3 object detection algorithm to count the number of people in a room attached to a laptop. YOLOv3 is a real-time object detection algorithm widely used in computer vision tasks and is suitable for applications such as video surveillance and self-driving cars. The algorithm uses anchor boxes, which are pre-defined bounding boxes that are used to detect objects of different shapes and sizes (Figure 5). The number of people occupying the space is published to the CASA MQTT server and used in the following stages of the project (Figure 6).

<img width="397" alt="image" src="https://user-images.githubusercontent.com/93122551/212163537-541f74fe-22b5-4edc-9681-c924151e2f4c.png">
Figure 5: Human recognition by YOLO algorithm with anchor boxes and probabilities.

<img width="397" alt="image" src="https://user-images.githubusercontent.com/93122551/212163597-66b36357-e4a1-42fe-b4c5-57266687a14d.png">
Figure 6: The published room occupancy in the CASA MQTT server.

Temperature and air quality data were collected using an Enviro environmental monitoring sensor, which is installed next to a soldering station, as shown in Figure 7. The sensor measures these variables in real time and transmits the data to the CASA MQTT server through a Raspberry Pi. Noise data was collected using a Wensn WS1361 sound pressure level metre (Figure 8), which is also connected to the Raspberry Pi and sends data to the MQTT server, as shown in Figure 9.

![image](https://user-images.githubusercontent.com/93122551/212163701-d516ac44-7149-4df4-b42f-f734b66615ec.jpeg)
Figure 7: Enviro+ environmental monitoring sensor.

![image](https://user-images.githubusercontent.com/93122551/212163770-ceb74b4b-06dc-4507-b32f-18d69f523ac5.jpeg)
Figure 8: Wensn WS1361 sound pressure level metre.

<img width="397" alt="image" src="https://user-images.githubusercontent.com/93122551/212163808-6d39efca-9afa-42eb-85f9-cbcfb2993b0a.png">
Figure 9: Wensn WS1361 sound pressure level metre.

4.2. Data Device Model
The data device model is a vital element of the project for building prototype models and implementing an AR model. As shown in Figure 10, It is created using Blender and serves as a decision tool for size, interference, and operation review between components before time-consuming 3D printing.

<img width="358" alt="image" src="https://user-images.githubusercontent.com/93122551/212163905-b186c85a-a2d1-4a9f-adaf-ed4c6b86e668.png">
Figure 10: Textured real-scale data device model in Blender for coordination.

To ensure that the data device model is accurate and up-to-date, we implemented a Single Source of Truth (SSOT) architecture (Pang & Szafron, 2014). The SSOT is a central repository of accurate and up-to-date information used as an organisation's definitive source of information. The goals of the SSOT are to ensure that all stakeholders have access to consistent, reliable information and to reduce the risk of errors or inconsistencies caused by using multiple sources of information.
Blender was chosen as the software tool for creating the data device model due to its capabilities as an open-source 3D graphics software and its ease of use. The device model is carefully designed with realistic textures (Figure 11), and data is pre-structured for the Unity workflow.

<img width="397" alt="image" src="https://user-images.githubusercontent.com/93122551/212164043-6a38872b-8157-47e3-bc61-88fdc897b74e.png">
Figure 11: Applied realistic textures on the data device model in Blender.

4.3. Digital Twin Model
The digital twin model is a tool for understanding the layout and features of the physical space and can be used to make decisions about the design and operation of physical and virtual devices. The digital twin model can visualise the physical space in a mobile application built using Unity.

The digital twin model of the project is a 3d model of the CE Lab., which is created using point cloud data captured by a Light Detection and Ranging (LiDAR) sensor mounted on an iPad Pro (Figure 12). LiDAR sensors are often used to create high-resolution 3D maps of the environment by sending out laser pulses and measuring the time it takes for the pulses to return to the sensor after reflecting off objects.

<img width="385" alt="image" src="https://user-images.githubusercontent.com/93122551/212164167-38b8fe61-cda5-4fe5-89f1-517feb1b2596.png">
Figure 12: Point cloud model by the LiDAR sensor.

In Blender, the imported model was re-shaped and textured to create a more realistic and accurate representation of the physical space (Figure 13).
 
The digital twin model was planned to be accessed and interacted with using a mobile device. However, due to time limitations, the digital twin model was implemented only in Unity (Figure 14) and not with the mobile application.

<img width="417" alt="image" src="https://user-images.githubusercontent.com/93122551/212164341-92b8e266-6747-4192-ae37-7a6828eb2a88.png">
Figure 14: Re-shaped and textured digital twin model in Unity.

5.	Building Physical Device
5.1. First Prototype - Circuitry Testing
The goal of this project is to read multiple data feeds from the CE lab. All information is processed through a wireless MQTT communication system created by the Arduino MKR WIFI 1010 board (Figure 15). MKR 1010 is capable of network connection and has a portable size, which is an advantage in terms of maximising flexibility and space efficiency. In addition, MKR 1010 is essential in providing a 5V operating voltage to the MG90S servo and the LED screen. To ensure a servo motor has a strong torque to rotate the cylinder, instead of an SG90 servo, an MG90S servo was incorporated into the design and presented no difficulties in performing the task. The 1.2" size of a single 8x8 dot-matrix LED screen was chosen for its ability to highlight the current data source, ideal visible display and perfect fit for the enclosure. The components were connected to MKR 1010 board with wires, and terminal blocks were used to create more pins (Figure 16).

<img width="446" alt="image" src="https://user-images.githubusercontent.com/93122551/212164462-768a9080-cc9d-48f4-a995-c6877ff20ae8.png">
Figure 15: Overview diagram.











Group discussion on Friday 2nd December

<img width="1376" alt="Screenshot 2022-12-02 at 16 20 10" src="https://user-images.githubusercontent.com/93122551/205337939-3f9bcfa3-4a8c-475b-ac2e-1da2338d5042.png">

Initial design in Blender for physical and virtual device to display five parameters within the CE107. 

