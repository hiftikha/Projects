//
//  magicBall.swift
//  arkit-magic-trick-haroon
//
//  Created by Haroon Iftikhar on 11/10/17.
//  Copyright © 2017 Udacity. All rights reserved.
//

import Foundation
import SceneKit

class magicBall {
    static let speed:Float = 4
    static let radius:CGFloat = 0.03
    private static var sphere:SCNGeometry?
    
    
    class func node() -> SCNNode {
        
        if sphere == nil {
            sphere = SCNSphere(radius: radius)
            let ballMaterial = SCNMaterial()
            ballMaterial.diffuse.contents = UIColor.purple
            sphere!.firstMaterial = ballMaterial
        }
        
        let node = SCNNode(geometry: sphere!)
        let ballBody = SCNPhysicsBody(type: SCNPhysicsBodyType.dynamic, shape: nil)
        ballBody.contactTestBitMask = 1
        ballBody.isAffectedByGravity = true
        ballBody.mass = 2
        ballBody.restitution = 0.90
        ballBody.damping = 0.05
        ballBody.friction = 2
        
        node.physicsBody = ballBody
        
        return node
    }
}
