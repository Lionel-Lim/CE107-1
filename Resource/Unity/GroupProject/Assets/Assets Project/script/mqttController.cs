using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class mqttController : MonoBehaviour
{
    public string nameController = "Controller 1";
    public string tagOfTheMQTTReceiver = "";

    public mqttReceiver _eventSender;

     void Start()
    {
        if (GameObject.FindGameObjectsWithTag(tagOfTheMQTTReceiver).Length > 0)
        {
            _eventSender = GameObject.FindGameObjectsWithTag(tagOfTheMQTTReceiver)[0].gameObject.GetComponent<mqttReceiver>();
        }
        else
        {
            Debug.LogError("At least one GameObject with mqttReceiver component and Tag == tagOfTheMQTTReceiver needs to be provided");
        }
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
    }

    private void OnMessageArrivedHandler(string newMsg)
    {
        this.GetComponent<TextMeshPro>().text=newMsg;
        Debug.Log("Event Fired. The message, from Topic " + " is = " + newMsg);
    }

}
