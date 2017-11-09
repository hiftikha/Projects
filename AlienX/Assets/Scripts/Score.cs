using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour {

	  [SerializeField]
    private Text scoreText;
	// Use this for initialization
	void Start () {
			 //dialogbox.enabled = false;
	}

	// Update is called once per frame
	void Update () {
		setScore();
	}

	void setScore (){
		if (GameManager.Instance.getLife()) {
			scoreText.text = GameManager.Instance.score.ToString();
		}
		else{
			scoreText.text = "";
		}
	}
}
