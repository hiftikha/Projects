//
//  Controllers.swift
//  ScanProSwift
//
//  Created by Haroon Iftikhar on 3/26/18.
//  Copyright © 2018 Voyomotive. All rights reserved.
//

import UIKit

class Controllers: UIViewController, UITableViewDataSource, UITableViewDelegate{
    
    var Favs1: [String] = ["CAN-HS1 Engine Control Module", "CAN-SW Radio Control Module", "CAN-HS1 Instrument Panel Module", "CAN-HS1 Brake Control Module", "CAN-HS1 Transmission Control Module", "CAN-HS1 Airbag Control Module", "CAN-HS1 Body Control Module", "CAN-SW HVAC Control Module", "CAN-SW Occupant Control Module", "CAN-SW Parking Aid Control Module", "CAN-HS1 Steering Control Module", "CAN-HS1 Telematics Control Module"]

    var Controllers: [String] = []
    @IBOutlet weak var controllerTable: UITableView!
    @IBOutlet weak var background: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        addTitleViewImage()
        controllerTable.dataSource = self
        controllerTable.backgroundColor = UIColor.clear
        Controllers = addSpaces(array: Favs1)
        background.image = #imageLiteral(resourceName: "scan_pro_background")
        // Do any additional setup after loading the view.
    }
    
    func addTitleViewImage(){
        let image = #imageLiteral(resourceName: "logo")
        let voyoIcon = UIImageView(image: image)
        let bannerWidth = navigationController!.navigationBar.frame.size.width
        let bannerHeight = navigationController!.navigationBar.frame.size.height
        
        let bannerX = bannerWidth / 2 - image.size.width / 2
        let bannerY = bannerHeight / 2 - image.size.height / 2
        
        voyoIcon.contentMode = .scaleAspectFit
        
        let titleView = UIView(frame: CGRect(x: bannerX, y: bannerY, width: bannerWidth/4, height: bannerHeight))
        voyoIcon.frame = titleView.bounds
        titleView.addSubview(voyoIcon)
        
        self.navigationItem.titleView = titleView
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return Favs1.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = UITableViewCell()
        
        if indexPath.row % 2 == 0 {
            cell = tableView.dequeueReusableCell(withIdentifier: "controllerCell", for: indexPath) as! IssueCell
            cell.textLabel?.text = Controllers[indexPath.row]
            cell.selectionStyle = UITableViewCellSelectionStyle.blue
        } else {
            cell = tableView.dequeueReusableCell(withIdentifier: "controllerSpaceCell", for: indexPath) as! controllerSpaceCell
            cell.textLabel?.text = " "
            cell.backgroundColor = UIColor.clear
            cell.isUserInteractionEnabled = false
            cell.selectionStyle = UITableViewCellSelectionStyle.none
        }
        
        return cell
    }

    func addSpaces(array: [String]) -> [String]{
        var spacedArray = [String](repeating: "", count: array.count*2)
        var counter = 0
        for i in 0..<array.count{
            spacedArray[i + counter] = array[i]
            counter += 1
        }
        return spacedArray
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
