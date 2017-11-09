using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Astronaut : Singleton<Astronaut> {

	private Transform astronaut;
	private int target = 2;
	public float playerSpeed = 2.0f;
	private float navigationTime = 2.0f;
	[SerializeField]
	private Transform[] placeholderPoints;
	// Use this for initialization
	void Start () {
		//getCurrentLocation();
		astronaut = GetComponent<Transform>();
	}
	// Update is called once per frame
	void Update () {
		//getCurrentLocation();
		if (target >= 0 && target < 4 && GameManager.Instance.getLife()) {
			if (Input.GetKeyDown(KeyCode.LeftArrow))
					 {
						 //if (destination >= 0) {
						 		astronaut.position = Vector2.MoveTowards(astronaut.position, placeholderPoints[target-1].position, playerSpeed * navigationTime);
						 		target--;
								Debug.Log("Player moved to location: " + target.ToString());
								//astronaut.position = placeholderPoints[destination-1];
						 //}
					 }

					 if (Input.GetKeyDown(KeyCode.RightArrow))
					 {
						 //if (destination <= 3) {
						 astronaut.position = Vector2.MoveTowards(astronaut.position, placeholderPoints[target+1].position, playerSpeed * navigationTime);
						 target++;
						 Debug.Log("Player moved to location: " + target.ToString());
						 // }
					 }
		 }
	}

	void OnTriggerEnter2D(Collider2D other){
		if (other.tag == "Enemy") {
			GameManager.Instance.Death();
			Destroy(gameObject);
			Debug.Log("Death!");
		}
	}
}
