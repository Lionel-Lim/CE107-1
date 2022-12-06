using UnityEngine;

public class mqttControllerList : MonoBehaviour
{
    [Tooltip("Optional name for the controller")]
    public string nameController = "Controller 1";
    public string tagOfTheMQTTReceiver = ""; //to be set on the Inspector panel. It must match one of the mqttReceiverList.cs GameObject
    [Header("   Case Sensitive!!")]
    [Tooltip("the topic to subscribe must contain this value. !!Case Sensitive!! ")]
    public string topicSubscribed = ""; //the topic to subscribe, it need to match a topic from the mqttReceiver
    private float pointerValue = 0.0f;
    [Space] [Space]
    public GameObject objectToControl; //pointer of the gauge, or other 3D models
    [Tooltip("Select the rotation axis of the object to control")]
    public enum State { X, Y, Z };
    public State rotationAxis;
    [Space] [Tooltip("Direction Rotation")]
    public bool CW = true; //CW True = 1; CW False = -1
    private int rotationDirection = 1;
    [Space] [Space]
    [Tooltip("minimum value on the dial")]
    public float startValue = 0f; //start value of the gauge
    [Tooltip("maximum value on the dial")]
    public float endValue = 180f; // end value of the gauge
    [Tooltip("full extension of the gauge in EulerAngles")]
    public float fullAngle = 180f; // full extension of the gauge in EulerAngles

    [Tooltip("Adjust the origin of the scale. negative values CCW; positive value CW")]
    public float adjustedStart = 0f; // negative values CCW; positive value CW
    [Space]
    public mqttReceiverList _eventSender;

    void Awake()
    {
        if (GameObject.FindGameObjectsWithTag(tagOfTheMQTTReceiver).Length > 0)
        {
            _eventSender = GameObject.FindGameObjectsWithTag(tagOfTheMQTTReceiver)[0].gameObject.GetComponent<mqttReceiverList>();
        }
        else
        {
            Debug.LogError("At least one GameObject with mqttReceiver component and Tag == tagOfTheMQTTReceiver needs to be provided");
        }
    }

    void OnEnable()
    {
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
    }

    private void OnDisable()
    {
        _eventSender.OnMessageArrived -= OnMessageArrivedHandler;
    }

    private void OnMessageArrivedHandler(mqttObj mqttObject) //the mqttObj is defined in the mqttReceiverList.cs
    {
        //We need to check the topic of the message to know where to use it 
        if (mqttObject.topic.Contains(topicSubscribed))
        {
            pointerValue = float.Parse(mqttObject.msg);

            Debug.Log("Event Fired. The message, from Object " + nameController + " is = " + pointerValue);
        }
    }

    private void Update()
    {
        float step = 1.5f * Time.deltaTime;
        // ternary conditional operator https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/conditional-operator
        rotationDirection = CW ? 1 : -1;

        if (pointerValue >= startValue)
        {
            Vector3 rotationVector = new Vector3();
            //If the rotation Axis is X
            if (rotationAxis == State.X)
            {
                rotationVector = new Vector3(
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart,
                objectToControl.transform.localEulerAngles.y,
                objectToControl.transform.localEulerAngles.z);
            }
            //If the rotation Axis is Y
            else if (rotationAxis == State.Y)
            {
                rotationVector = new Vector3(
                objectToControl.transform.localEulerAngles.x,
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart,
                objectToControl.transform.localEulerAngles.z);

            }
            //If the rotation Axis is Z
            else if (rotationAxis == State.Z)
            {
                rotationVector = new Vector3(
                objectToControl.transform.localEulerAngles.x,
                objectToControl.transform.localEulerAngles.y,
                (rotationDirection * ((pointerValue - startValue) * (fullAngle / (endValue - startValue)))) - adjustedStart);
            }
            objectToControl.transform.localRotation = Quaternion.Lerp(
                    objectToControl.transform.localRotation,
                    Quaternion.Euler(rotationVector),
                    step);
        }
    }
}