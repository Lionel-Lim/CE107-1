using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class disassembleEventController : MonoBehaviour
{
    public void disassembleEvent(){
        // Debug.Log("Click!");
        // Get a reference to the animation object
        GameObject animationObject = GameObject.Find("Animation_V2");
        GameObject btnObject = GameObject.Find("DisassembleBtn");
        Button buttonComp = btnObject.GetComponent<Button>();

        // Get a reference to the Animator component on the animation object
        Animator animator = animationObject.GetComponent<Animator>();
        TMPro.TMP_Text txt = btnObject.GetComponentInChildren<TMPro.TMP_Text>();
        Debug.Log(txt);
        if (txt.text == "Disassemble"){
            // Activate the "ActivateAnimation" trigger in the Animator
            animator.SetTrigger("Activate_Animation");
            txt.text = "Assemble";
            // disable the Button
            buttonComp.interactable = false;
            // schedule a method to be called after 8 seconds
            Invoke("EnableButton", 8f);
        }else{
            animator.SetTrigger("Active_ReverseAnimation");
            txt.text = "Disassemble";
            buttonComp.interactable = false;
            // schedule a method to be called after 8 seconds
            Invoke("EnableButton", 8f);
        }
    }
    void EnableButton()
    {
        GameObject animationObject = GameObject.Find("Animation_V2");
        GameObject btnObject = GameObject.Find("DisassembleBtn");
        Button buttonComp = btnObject.GetComponent<Button>();
        // enable the Button again
        buttonComp.interactable = true;
    }
}
