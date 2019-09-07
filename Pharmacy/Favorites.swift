//
//  Favorites.swift
//  Pharmacy
//
//  Created by Haroon Iftikhar on 2/7/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Favorites: UIViewController, UITableViewDelegate, UITableViewDataSource {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return Int(numberOfFacts("SELECT * FROM Facts"))
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return UITableViewCell()
    }

}
