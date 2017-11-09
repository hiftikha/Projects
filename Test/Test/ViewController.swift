//
//  ViewController.swift
//  Test
//
//  Created by Haroon Iftikhar on 10/10/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet var Image: UIImageView!
    override func viewDidLoad() {
        super.viewDidLoad()
        Image.image = UIImage(named: "FavoritePic.jpg")
        
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

