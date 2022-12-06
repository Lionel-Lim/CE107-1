using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movement : MonoBehaviour
{
    private void Update() {
        transform.position = new Vector3(2, 14 + Mathf.Sin(Time.time), 0);
    }
}
