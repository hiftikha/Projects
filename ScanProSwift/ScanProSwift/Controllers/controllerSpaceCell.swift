//
//  SpaceCell.swift
//  ScanProSwift
//
//  Created by Haroon Iftikhar on 4/6/18.
//  Copyright © 2018 Voyomotive. All rights reserved.
//

import UIKit

class controllerSpaceCell: UITableViewCell {

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    override func prepareForReuse() {
        self.backgroundColor = UIColor.clear
        self.isUserInteractionEnabled = false
        self.selectionStyle = UITableViewCellSelectionStyle.none
    }

}
