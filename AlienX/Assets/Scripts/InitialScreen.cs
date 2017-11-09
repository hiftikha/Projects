using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class InitialScreen : MonoBehaviour {

	public Image initial;
	// Use this for initialization
	void Start () {
		Invoke("StartGame", 5);
	}

	void StartGame(){
		SceneManager.LoadScene(2);
	}
	// Update is called once per frame
	void Update () {

	}
}
