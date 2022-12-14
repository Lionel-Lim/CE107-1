using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class linkDataEventController : MonoBehaviour
{   
    public GameObject barrel;
    public float rotationSpeed = 10f;
    public Vector3 rotationAxis = Vector3.right;
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
        GameObject animationObject = GameObject.Find("Animation_V2");
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
        while (true)
        {
            // Rotate the object by the specified amount along the specified axis
            barrel.transform.Rotate(rotationAxis * rotationSpeed * Time.deltaTime);

            // Wait for the next frame before continuing the loop
            yield return null;
        }
    }
}
