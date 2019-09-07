//
//  ViewController.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 2/7/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit
import SQLite

class ViewController: UIViewController {

    var favsDone = 0;
    
    @IBAction func goToSettings(_ sender: Any) {
        performSegue(withIdentifier: "goToSettings", sender: self)
    }
    @IBAction func shareFact(_ sender: Any) {
        let bounds = UIScreen.main.bounds
        UIGraphicsBeginImageContextWithOptions(bounds.size, true, 0.0)
        self.view.drawHierarchy(in: bounds, afterScreenUpdates: false)
        let img = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        let activityViewController = UIActivityViewController(activityItems: [img as Any], applicationActivities: nil)
        self.present(activityViewController, animated: true, completion: nil)
    }
    @IBOutlet weak var favoriteButton: UISwitch!
    @IBAction func favorite(_ sender: Any) {
        if(favsDone < Database.sharedDatabase.coins - 1){
            Database.sharedDatabase.updateFavorite(table: Database.sharedDatabase.tablesArray[0], updateField: Database.sharedDatabase.favoriteBool)
            favsDone = favsDone + 1
            print("favs done", favsDone)
        }
        else{
            favoriteButton.isEnabled = false
            factLabel.text = "You have no more pills to favorite!!"
        }
    }
    @IBOutlet weak var factLabel: UILabel!
    @IBAction func generateFact(_ sender: Any) {
        if(favsDone < Database.sharedDatabase.coins - 1){
            favoriteButton.isEnabled = true
            factLabel.text = Database.sharedDatabase.query(table: Database.sharedDatabase.tablesArray[0])
            favoriteButton.isOn = Bool(truncating: Database.sharedDatabase.factFav as NSNumber)
            favsDone = favsDone + 1
        }
        else{
            factLabel.text = "You have no more pills to generate Fact!!"
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        //howOftenToFactify()
        factLabel.lineBreakMode = NSLineBreakMode.byWordWrapping
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        if checkToFactify(){
            factLabel.text = Database.sharedDatabase.query(table: Database.sharedDatabase.tablesArray[0])
            favoriteButton.isOn = Bool(truncating: Database.sharedDatabase.factFav as NSNumber)
            howOftenToFactify()
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func checkToFactify() -> Bool {
        let date = Date()
        var diff = Date()
        let calendar = Calendar.current
        
        let monthly: TimeInterval = 2629746
        let weekly: TimeInterval = 604800
        let daily: TimeInterval = 86400
        
        var chosen = UserDefaults.standard.object(forKey: "howOftenToFactify")
        if chosen == nil {
            chosen = "Daily"
        }
        var setDate = UserDefaults.standard.object(forKey: "setDate")
        if setDate == nil {
            setDate = date
        }
        
        if chosen as! String == "Daily" {
            diff = Date(timeInterval: daily, since: setDate as! Date)
        }
        if chosen as! String == "Weekly" {
            diff = Date(timeInterval: weekly, since: setDate as! Date)
        }
        if chosen as! String == "Monthly" {
            diff = Date(timeInterval: monthly, since: setDate as! Date)
        }
        print("DIFF: ", diff)
        print("DATE: ", date)
        if date >= diff {
            return true
        }
        return false
    }
    
    func howOftenToFactify(){
        let date = Date()
        let calendar = Calendar.current
        
        UserDefaults.standard.set(date, forKey: "setDate")
    }


}

