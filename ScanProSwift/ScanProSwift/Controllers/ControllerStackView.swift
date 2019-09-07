//
//  ControllerStackView.swift
//  ScanProSwift
//
//  Created by Haroon Iftikhar on 4/6/18.
//  Copyright © 2018 Voyomotive. All rights reserved.
//

import UIKit

class ControllerStackView: UIStackView {

    /*
    // Only override draw() if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func draw(_ rect: CGRect) {
        // Drawing code
    }
    */

}

extension UIStackView {
    
    func addBackground(color: UIColor) {
        let subView = UIView(frame: bounds)
        subView.backgroundColor = color
        subView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        insertSubview(subView, at: 0)
    }
    
}
