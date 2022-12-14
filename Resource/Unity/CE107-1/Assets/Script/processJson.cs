using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
// using System.Text.Json;

public class processJson : MonoBehaviour
{
    public class enviroMQTTStructure
    {
        public int temperature;
        public int pressure;
        public int humidity;
        public int oxidised;
        public int reduced;
        public int nh3;
        public int lux;
        public int pm1;
        public int pm25;
        public int pm10;
    }

    public string textObjectName = ""; // topic to publish
    // Start is called before the first frame update

    void dataProcess(){
        // Get MQTT Class from mqttReceiverList.cs
        mqttReceiverList mqttReceiver = GetComponent<mqttReceiverList>();
        // Ref. eventMessages where MQTT data is stored.
        List<string> mqttMessage = mqttReceiver.eventMessages;
        // Ref. Text Mesh Pro oject
        GameObject dataVisualization = GameObject.Find("dataVisualisationContainer");
        Transform canvasTransform = dataVisualization.transform.Find("Canvas");
        GameObject board = canvasTransform.Find(textObjectName).gameObject;
        TextMeshProUGUI textMeshProComponent = board.GetComponent<TextMeshProUGUI>();
        // When MQTT is connected and eventMessages has at least 1 info. change textmeshpro text to something
        if (mqttReceiver.isConnected && mqttReceiver.eventMessages.Count > 0){
            int lastIndex = mqttMessage.Count - 1;
            Debug.Log(mqttReceiver.eventTopics[lastIndex]);
            enviroMQTTStructure enviroValues = enviroJson(mqttMessage[lastIndex]);
            textMeshProComponent.alignment = TMPro.TextAlignmentOptions.MidlineLeft;
            textMeshProComponent.fontSize = 5;
            textMeshProComponent.text = "Temperature: " + enviroValues.temperature + 
            "°C<br>PM1: " + enviroValues.pm1 + 
            "μm<br>";
        }else{
            textMeshProComponent.alignment = TMPro.TextAlignmentOptions.MidlineGeoAligned;
            textMeshProComponent.fontSize = 10;
            textMeshProComponent.text = "Loading Data...";
        }
    }

    public static enviroMQTTStructure enviroJson(string json){
        return JsonUtility.FromJson<enviroMQTTStructure>(json);
    }
}
