//
//  Definitions.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 3/28/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Terms: UIViewController {
    
    @IBOutlet weak var Definition1: UILabel!
    @IBOutlet weak var Definition2: UILabel!
    @IBOutlet weak var Definition3: UILabel!
    @IBOutlet weak var Definition4: UILabel!
    @IBOutlet weak var Definition5: UILabel!
    @IBOutlet weak var Definition6: UILabel!
    var DefinitionArray = [UILabel]()
    var DefinitionsQuery = [String]()
    var queryTerm = String()
    var tagCounter = 1
    @IBAction func nextSetOfTerms(_ sender: Any) {
        loadNewTerms()
        addGestures()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        DefinitionArray = [Definition1, Definition2, Definition3, Definition4, Definition5, Definition6]
        
        // Do any additional setup after loading the view.
        loadNewTerms()
        addGestures()
        
    }
    
    func loadNewTerms(){
        tagCounter = 1;
        for label in DefinitionArray{
            label.text = Database.sharedDatabase.queryTerm(table: Database.sharedDatabase.tablesArray[2])
            label.tag = tagCounter
            tagCounter = tagCounter + 1
        }
    }
    
    func addGestures(){
        let tapOne = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        let tapTwo = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        let tapThree = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        let tapFour = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        let tapFive = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        let tapSix = UITapGestureRecognizer(target: self, action: #selector(tapFunction))
        
        Definition1.addGestureRecognizer(tapOne)
        Definition2.addGestureRecognizer(tapTwo)
        Definition3.addGestureRecognizer(tapThree)
        Definition4.addGestureRecognizer(tapFour)
        Definition5.addGestureRecognizer(tapFive)
        Definition6.addGestureRecognizer(tapSix)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let def = segue.destination as! Definition
        def.termID = Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: queryTerm)
    }
    
    @objc func tapFunction(sender:UITapGestureRecognizer) {
        let sender = sender.view!.tag
        
        switch sender {
        case 1:
            queryTerm = Definition1.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        case 2:
            queryTerm = Definition2.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        case 3:
            queryTerm = Definition3.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        case 4:
            queryTerm = Definition4.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        case 5:
            queryTerm = Definition5.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        case 6:
            queryTerm = Definition6.text!
            performSegue(withIdentifier: "goToDefinition", sender: nil)
        default:
            print("tap working for ", sender)
        }
        
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
