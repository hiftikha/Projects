//
//  FactOfTheDay.swift
//  Pharmacy
//
//  Created by Haroon Iftikhar on 12/17/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

import UIKit
import SQLite

class FactOfTheDay: UIViewController {
    
    var database: Connection!

    @IBAction func MainMenu(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    
    @IBAction func openData(_ sender: Any) {

    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        do {
            let documentDirectory = try FileManager.default.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: false)
            let fileUrl = documentDirectory.appendingPathComponent("pharmacyDB").appendingPathExtension("db")
            let database = try Connection(fileUrl.path)
        } catch {
            print(error)
        }
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
