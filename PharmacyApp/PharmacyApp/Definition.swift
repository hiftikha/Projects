//
//  Definition.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 4/1/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Definition: UIViewController {

    @IBAction func shareButton(_ sender: Any) {
        let bounds = UIScreen.main.bounds
        UIGraphicsBeginImageContextWithOptions(bounds.size, true, 0.0)
        self.view.drawHierarchy(in: bounds, afterScreenUpdates: false)
        let img = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        let activityViewController = UIActivityViewController(activityItems: [img as Any], applicationActivities: nil)
        self.present(activityViewController, animated: true, completion: nil)
    }
    @IBAction func searchInSafari(_ sender: Any) {
        UIApplication.shared.openURL(URL(string: "http://www.google.com/search?q=" + genericName.text!)!)
    }
    
    var termID = Int()
    @IBOutlet weak var genericName: UILabel!
    @IBOutlet weak var brandName: UILabel!
    @IBOutlet weak var commonDoses: UILabel!
    @IBOutlet weak var className: UILabel!
    @IBOutlet weak var mechanicOfAction: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        genericName.text = Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: termID)
        brandName.text = (Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "brandName", row: termID) != "" ? "Brand Name: \n" : "") + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "brandName", row: termID)
        commonDoses.text = (Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "common", row: termID) != "" ? "Common: \n" : "") + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "common", row: termID)
        className.text = (Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "class", row: termID) != "" ? "Class Name: \n" : "") + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "class", row: termID)
        if(Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "action", row: termID).replacingOccurrences(of: " ", with: "", options: NSString.CompareOptions.literal, range: nil).count != 0){
            mechanicOfAction.text = "Mechanic Of Action: \n" + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "action", row: termID)
        }
        else {
            mechanicOfAction.isHidden = true
        }
        print("<", Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "action", row: termID), ">")
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
