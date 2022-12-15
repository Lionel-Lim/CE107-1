using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class linkDataEventController : MonoBehaviour
{   
    public GameObject barrel;
    float rotationSpeed = 1000f;
    Vector3 rotationAxis = Vector3.right;
    float rotateDegree = 90f;
    float accmRotation = 0;
    int rotationDirection = 1;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void changeData(){
        StartCoroutine(RotateObjectOverTime());
    }
        
    IEnumerator RotateObjectOverTime(){
        float unitRotation = rotateDegree / rotationSpeed;
        float localAccumRotation = 0f;
        Debug.Log("Accumulated rotation is :" + accmRotation);
        Debug.Log(unitRotation);

        while (true)
        {
            localAccumRotation += unitRotation;
            if (localAccumRotation >= rotateDegree){
                barrel.transform.Rotate((localAccumRotation - rotateDegree) * rotationDirection,0,0);
                break;
            }
            barrel.transform.Rotate(unitRotation * rotationDirection,0,0);
            yield return null;
        }
        localAccumRotation = 0f;
        accmRotation += rotateDegree * rotationDirection;
        if (accmRotation == 360 || accmRotation == 0){
            rotationDirection = rotationDirection * -1;
        }
        setLED((int) (accmRotation / rotateDegree));
    }

    public static void setLED(int index){
        
        GameObject ledContainer = GameObject.FindWithTag("LEDs");
        int ledNum = 0;
        if(index == 0){
            ledNum = (int)Mathf.Lerp(0, 34, Mathf.InverseLerp(30, 140, (float)appendData.CE_dB));   // dB
        }else if(index == 1){
            ledNum = (int)Mathf.Lerp(0, 34, Mathf.InverseLerp(0, 250, appendData.CE_pm1));    // PM1
        }else if(index == 2){
            ledNum = (int)Mathf.Lerp(0, 34, Mathf.InverseLerp(0, 30, appendData.CE_RoomCapacity));    // RC
        }else if(index == 3){
            ledNum = (int)Mathf.Lerp(0, 34, Mathf.InverseLerp(15, 35, appendData.CE_Temperature));    // Temp
        }else{
            Debug.Log("Wrong Index");
        }
        Debug.Log("Index is " + index + " led num is " + ledNum);
        for(int i = 0; i < ledNum + 1; i++){
            GameObject led = ledContainer.transform.GetChild(i).gameObject;
            Renderer renderer = led.GetComponent<Renderer>();
            renderer.materials[1].SetColor("_Color", Color.cyan);
            renderer.materials[1].SetColor("_EmissionColor", Color.white);
            renderer.materials[3].SetColor("_Color", Color.cyan);
            renderer.materials[3].SetColor("_EmissionColor", Color.white);
        }
        for(int i = ledNum + 1; i < 35; i++){
            GameObject led = ledContainer.transform.GetChild(i).gameObject;
            Renderer renderer = led.GetComponent<Renderer>();
            renderer.materials[1].SetColor("_Color", Color.black);
            renderer.materials[1].SetColor("_EmissionColor", Color.black);
            renderer.materials[3].SetColor("_Color", Color.black);
            renderer.materials[3].SetColor("_EmissionColor", Color.black);
        }
        // ledContainer.transform.GetChild(index).gameObject;
    }
}   
