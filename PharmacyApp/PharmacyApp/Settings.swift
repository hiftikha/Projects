//
//  Settings.swift
//  Pharmacy
//
//  Created by Haroon Iftikhar on 12/20/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Settings: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource {

    @IBAction func Back(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    @IBOutlet weak var FactOptions: UIPickerView!
    let options = ["Daily", "Weekly", "Biweekly", "Monthly"]
    override func viewDidLoad() {
        super.viewDidLoad()
        FactOptions.dataSource = self
        FactOptions.delegate = self

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return options.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return options[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let howOften = options[row]
        UserDefaults.standard.set(howOften, forKey: "howOftenToFactify")
        howOftenToFactify()
    }
    
    func howOftenToFactify(){
        let date = Date()
        let calendar = Calendar.current
        
        UserDefaults.standard.set(date, forKey: "setDate")
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
