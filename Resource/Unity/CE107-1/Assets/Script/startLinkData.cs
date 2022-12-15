using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class startLinkData : MonoBehaviour
{
    // Start is called before the first frame update
    public void startLink()
    {
        GameObject animationObject = GameObject.FindWithTag("animationObject");
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
        linkDataEventController.setLED(0);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
