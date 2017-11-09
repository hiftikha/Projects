//
//  InterfaceController.swift
//  Test WatchKit Extension
//
//  Created by Haroon Iftikhar on 10/10/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

import WatchKit
import Foundation

var GameArray: [(String, String)] = [("Item 1","Smash or Pass"),
                                    ("Item 2","Truth & Dare"),
                                    ( "Item 3","Never have I ever"),
                                    ("Item 4","Me vs Ex"),
                                    ("Item 5","Would you rather")]


class InterfaceController: WKInterfaceController {
    @IBOutlet weak var GamePicker: WKInterfacePicker!


    override func awake(withContext context: Any?) {
        super.awake(withContext: context)
        
        let pickerItems: [WKPickerItem] = GameArray.map {
            let pickerItem = WKPickerItem()
            pickerItem.caption = $0.0
            pickerItem.title = $0.1
            return pickerItem
        }
        GamePicker.setItems(pickerItems)
        
        // Configure interface objects here.
    }
    
    override func willActivate() {
        // This method is called when watch view controller is about to be visible to user
        super.willActivate()
    }
    
    override func didDeactivate() {
        // This method is called when watch view controller is no longer visible
        super.didDeactivate()
    }

}
