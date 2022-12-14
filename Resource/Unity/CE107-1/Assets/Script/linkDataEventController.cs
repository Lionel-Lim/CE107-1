using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class linkDataEventController : MonoBehaviour
{   
    public GameObject animationObject;
    public GameObject barrel;
    float rotationSpeed = 100f;
    Vector3 rotationAxis = Vector3.right;
    float rotateDegree = 30f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // animationObject.transform.Rotate(Vector3.right, 30f, Space.World);
        // float step = 10f * Time.deltaTime;
        // int rotationDirection = 1;
        // Vector3 rotationVector = new Vector3();
        // rotationVector = new Vector3(
        //         barrel.transform.localEulerAngles.x + (rotationDirection * rotateDegree),
        //         barrel.transform.localEulerAngles.y,
        //         barrel.transform.localEulerAngles.z);
        // barrel.transform.localRotation = Quaternion.Lerp(
        //             barrel.transform.localRotation,
        //             Quaternion.Euler(rotationVector),
        //             step);
    }
    public void linkData(){
        Debug.Log("ON");
        GameObject disassembleBtnObject = GameObject.Find("DisassembleBtn");
        Button disassemblebuttonComp = disassembleBtnObject.GetComponent<Button>();
        GameObject linkDataBtnObject = GameObject.Find("LinkMQTTBtn");
        Button linkDataButtonComp = linkDataBtnObject.GetComponent<Button>();
        GameObject changeDataBtnObject = GameObject.Find("changeDataBtn");
        Button changeDataButtonComp = changeDataBtnObject.GetComponent<Button>();

        // Get a reference to the Animator component on the animation object
        Animator animator = animationObject.GetComponent<Animator>();
        animator.enabled = false;

        disassemblebuttonComp.interactable = false;
        changeDataButtonComp.interactable = true;
    }

    public void changeData(){
        StartCoroutine(RotateObjectOverTime());
    }
        
    IEnumerator RotateObjectOverTime(){
        float currentValue = barrel.transform.localEulerAngles.x;
        float unitRotation = rotateDegree / rotationSpeed;
        float destination = currentValue + rotateDegree;

        Debug.Log("currentValue is" + currentValue + "Rotating by " + unitRotation + "to " + destination);

        while (true)
        {
            float rotatingTo = unitRotation + barrel.transform.localEulerAngles.x;
            if (rotatingTo >= currentValue + rotateDegree){
                barrel.transform.Rotate(destination,barrel.transform.localEulerAngles.y,barrel.transform.localEulerAngles.z);
                // barrel.transform.localRotation = Quaternion.Euler(destination,barrel.transform.localEulerAngles.y,barrel.transform.localEulerAngles.z);
                break;
            }
            // Rotate the object by the specified amount along the specified axis
            barrel.transform.Rotate(rotatingTo,barrel.transform.localEulerAngles.y,barrel.transform.localEulerAngles.z);
            // barrel.transform.localRotation = Quaternion.Euler(rotatingTo,barrel.transform.localEulerAngles.y,barrel.transform.localEulerAngles.z);

            // Wait for the next frame before continuing the loop
            yield return null;
        }
        // yield return null;
    }
}   
