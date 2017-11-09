using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Restart : MonoBehaviour {


	public Image dialogbox;
	// Use this for initialization
	void Start () {
		dialogbox.enabled = false;
	}

	// Update is called once per frame
	void Update () {
		if (GameManager.Instance.getLife()) {
		}
		else{
			dialogbox.enabled = true;
		}
	}
}
