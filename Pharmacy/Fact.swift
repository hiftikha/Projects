//
//  Fact.swift
//  Pharmacy
//
//  Created by Haroon Iftikhar on 2/7/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import Foundation

class Fact{
    private var _fact : String!
    private var _used : Int32!
    private var _fav : Int32!
    
    var fact: String {
        return _fact
    }
    
    init(fact: String, used: Int32, fav: Int32) {
        _fact = fact
        _used = used
        _fav = fav
    }
    
}
