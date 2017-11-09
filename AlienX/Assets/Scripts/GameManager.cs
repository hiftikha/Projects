using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : Singleton<GameManager> {

  private bool alive = true;
	public GameObject spawnPoint;
	[SerializeField]
	private GameObject[] enemies;
	[SerializeField]
	private int maxEnemiesOnScreen;
	[SerializeField]
	private int totalEnemies;
	[SerializeField]
	private int enemiesPerSpawn;
	[SerializeField]
	private int spawnDelay;
	private int enemiesOnScreen = 0;
	public int score = 0;
  int randomAlien = 0;
  int spawnedAlien = 5;

	// Use this for awake time
	void Awake() {
	}
	public void Death(){
		alive = false;
	}
	public bool getLife(){
		return alive;
	}
  public int getScore(){
    return score;
  }
	// Spawns new enemy on the screen
	void spawnEnemy() {
		if (enemiesPerSpawn > 0 && enemiesOnScreen < totalEnemies) {
			for (int i = 0; i < enemiesPerSpawn; i++) {
				if (enemiesOnScreen < maxEnemiesOnScreen) {
					GameObject newEnemy = Instantiate(enemies[0]) as GameObject;
					newEnemy.transform.position = spawnPoint.transform.position;
					enemiesOnScreen++;
				}
			}
		}
	}

	IEnumerator spawn(){
		if ( enemiesPerSpawn > 0 && enemiesOnScreen < totalEnemies) {
			for (int i = 0; i < enemiesPerSpawn; i++) {
        do {
            randomAlien = Random.Range (0, 4);
        } while(randomAlien == spawnedAlien);
				if (enemiesOnScreen < maxEnemiesOnScreen) {
					Debug.Log("Generating Enemy!");
          if (spawnedAlien != randomAlien) {
            GameObject newEnemy = Instantiate(enemies[randomAlien]) as GameObject;
  					newEnemy.transform.position = spawnPoint.transform.position;
          }
          spawnedAlien = randomAlien;
					enemiesOnScreen++;
				}
			}
			yield return new WaitForSeconds(Random.Range(0.0f,4f));
			StartCoroutine(spawn());
		}
	}

	// Destroys an enemy
 	public void removeEnemyFromScreen(){
		if (enemiesOnScreen > 0) {
			enemiesOnScreen--;
		}
		score++;
	}

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {
			StartCoroutine(spawn());
 			 if (Input.GetKeyDown(KeyCode.R))
 			 {
 				  SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
 			}
      else if (Input.GetKeyDown(KeyCode.M))
      {
         SceneManager.LoadScene(0);
     }
	}
}
