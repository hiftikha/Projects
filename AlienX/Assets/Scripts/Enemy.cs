using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour {

	[SerializeField]
	private int target = 0;
	[SerializeField]
	private Transform exitPoint;
	[SerializeField]
	private Transform[] wayPoints;
	[SerializeField]
	private float navigationUpdate = 0;
	private Transform enemy;
	private float navigationTime = 2.0f;
	private float moveSpeed = 0.05f;

	// Use this for initialization
	void Start () {
		enemy = GetComponent<Transform>();
	}

	// Update is called once per frame
	void Update () {
		if (GameManager.Instance.getScore() > 20) {
			moveSpeed = 0.1f;
		}
		if(wayPoints != null){
			//navigationTime += Time.deltaTime;
			if (navigationTime > navigationUpdate) {
				if (target < wayPoints.Length) {
					//Debug.Log("Moving towards next checkpoint");
					enemy.position = Vector2.MoveTowards(enemy.position, wayPoints[target].position, moveSpeed * navigationTime);
				}
				else {
					//Debug.Log("Moving towards end");
					enemy.position = Vector2.MoveTowards(enemy.position, exitPoint.position, moveSpeed * navigationTime);
				}
				//navigationTime = 1;
			}
		}
	}

	void OnTriggerEnter2D(Collider2D other){
		if (other.tag == "Checkpoint") {
			//Debug.Log("Collision Triggered");
			target++;
		}
		else if (other.tag == "Player") {
			//Debug.Log("Collision Triggered");

		}
		else if (other.tag == "Finish"){
			//Debug.Log("Collision Triggered");
			GameManager.Instance.removeEnemyFromScreen();
			Destroy(gameObject);
		}
	}
}
