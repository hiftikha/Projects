//
//  ViewController.swift
//  scenekit-arkit-coordinate-systems
//
//  Created by Haroon Iftikhar on 8/9/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

import UIKit
import SceneKit
import ARKit

class ViewController: UIViewController, ARSCNViewDelegate, ARSessionDelegate {

    @IBOutlet var sceneView: ARSCNView!
    private var planeNode: SCNNode?
    private var ballsNode: SCNNode?
    var hatPlaced = false
    var ballName: String = ""
    static let velocity : Float = 4
    var visibility = true
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Set the view's delegate
        sceneView.delegate = self
        sceneView.session.delegate = self
        
        // Show statistics such as fps and timing information
        sceneView.showsStatistics = true
        
        // Set the scene to the view
        sceneView.scene = SCNScene()
        //sceneView.debugOptions = [.showPhysicsShapes]
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // Create a session configuration
        let configuration = ARWorldTrackingConfiguration()
        configuration.planeDetection = .horizontal

        // Run the view's session
        sceneView.session.run(configuration)
        ballsNode = SCNNode()
        sceneView.scene.rootNode.addChildNode(ballsNode!)
        
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        // Pause the view's session
        sceneView.session.pause()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }

    @IBAction func onViewPinched(_ sender: Any) {
        NSLog("Pinch is working!")
    }
    @IBAction func onThrowBall(_ sender: Any) {
        NSLog("Ball Throw is working!")
        let ballToThrow = ballsNode?.childNode(withName: ballName, recursively: true)
        //let forceDirection = SCNVector3Make(0, 0, -0.5)
        
        let currentFrame = sceneView.session.currentFrame!
        let n = SCNNode()
        sceneView.scene.rootNode.addChildNode(n)
        
        //let instance = sceneView.session.currentFrame?.camera
        //let cameraTransform = instance?.transform
        
        var closeTranslation = matrix_identity_float4x4
        closeTranslation.columns.3.z = -5
        
        var translation = matrix_identity_float4x4
        translation.columns.3.z = -5
        
        n.simdTransform = matrix_multiply(currentFrame.camera.transform, translation)
        //ballToThrow?.simdTransform = matrix_multiply(currentFrame.camera.transform, closeTranslation)
        
        let direction = n.position
        
        //ballToThrow?.physicsBody?.isAffectedByGravity = true
        //for ballNode in ballToThrow {
        ballToThrow?.physicsBody?.applyForce(direction, asImpulse: true)
        ballToThrow?.physicsBody?.isAffectedByGravity = true
        //ballToThrow?.removeFromParentNode()
        
    }
    @IBAction func onNewBall(_ sender: Any) {
        NSLog("New Ball is working!")
        let ball = SCNSphere(radius: 0.02)
        let ballNode = SCNNode(geometry: ball)
        ballNode.name = UUID().uuidString
        ballName = ballNode.name!
        print("The name of the ball's node is " + ballName)
        ballNode.physicsBody = SCNPhysicsBody(type: .dynamic, shape: nil)
        
        let camera = sceneView.session.currentFrame?.camera
        let cameraTransform = camera?.transform
        ballNode.simdTransform = cameraTransform!
        //ballNode.transform = SCNMatrix4MakeTranslation(0, 0, 2)
        ballNode.physicsBody?.allowsResting = true
        ballNode.physicsBody?.mass = 2
        ballNode.physicsBody?.restitution = 1
        ballNode.physicsBody?.damping = 0.1
        ballNode.physicsBody?.friction = 5
        ballNode.physicsBody?.contactTestBitMask = 1
        ballNode.physicsBody?.isAffectedByGravity = false
        ballsNode?.addChildNode(ballNode)
    }
    
    @IBAction func onMagicTrick(_ sender: Any) {
        NSLog("Magic Trick is working!")
        let magicBound = sceneView?.scene.rootNode.childNode(withName: "magicBounds", recursively: true)
        let minVector = magicBound?.boundingBox.min
        let maxVector = magicBound?.boundingBox.max
        //let ball = sceneView?.scene.rootNode
        let ballsToMagic = ballsNode?.childNodes
        
        
        for node in ballsToMagic! {
            if (node.position.x < (maxVector?.x)! && node.position.x > (minVector?.x)!){
                if (node.position.y < (maxVector?.y)! && node.position.y > (minVector?.y)!){
                    if (node.position.z < (maxVector?.z)! && node.position.z > (minVector?.z)!){
                        if (visibility == true){
                             print("The number of balls are: ", ballsToMagic?.count)
                            print("The name of node is: ", node.name)
                            node.opacity = 0.0
                            visibility = false
                            }
    
                        if (visibility == false) {
                            node.opacity = 1.0
                            print("The number of balls are: ", ballsToMagic?.count)
                            print("The name of node is: ", node.name)
                            visibility = true
                        }
                        
                    }
                }
            }
        }
    }
    
    
    @IBAction func onViewTapped(_ sender: Any) {
        NSLog("Tap is working!")
    }
    
    // Transforms the y point of the vector by a specific distance
    func yTransformation(point: SCNVector3, distance: Float) -> SCNVector3 {
        var x = Float()
        var y = Float()
        var z = Float()
        
        x = point.x
        y = point.y + distance
        z = point.z
        
        let result = SCNVector3Make(x, y, z)
        return result
    }
    
    func renderer(_ renderer: SCNSceneRenderer, nodeFor anchor: ARAnchor) -> SCNNode? {
        
        //Create light
        let light = SCNLight()
        light.castsShadow = true
        light.type = .omni
        light.intensity = 700
        let lightNode = SCNNode()
        lightNode.light = light
        
        // TODO: Apply transformation
        let camera = sceneView.session.currentFrame?.camera
        let cameraTransform = camera?.transform
        lightNode.simdTransform = cameraTransform!
        
        // Add light node to root node
        sceneView.pointOfView?.addChildNode(lightNode)
        
        if(!hatPlaced && anchor is ARPlaneAnchor){
            let hat = SCNTube(innerRadius: 0.15, outerRadius: 0.16, height: 0.2)
            //hat.firstMaterial?.diffuse.contents = UIColor.black
            let hatNode = SCNNode(geometry: hat)
            //hatNode.physicsBody = SCNPhysicsBody(type: .static, shape: shape)
            
            
            let cap = SCNTube(innerRadius: 0.15, outerRadius: 0.25, height: 0.01)
            //cap.firstMaterial?.diffuse.contents = UIColor.black
            let capNode = SCNNode(geometry: cap)
            //capNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            capNode.position = yTransformation(point: hatNode.position, distance: 0.1)
           
            let bottom = SCNCylinder(radius: 0.15, height: 0.01)
            //bottom.firstMaterial?.diffuse.contents = UIColor.black
            let bottomNode = SCNNode(geometry: bottom)
            //bottomNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            
            bottomNode.position = yTransformation(point: hatNode.position, distance: -0.1)
            
            let floor = SCNFloor()
            floor.reflectivity = 0.10
            floor.firstMaterial?.colorBufferWriteMask = SCNColorMask(rawValue: 0)
            let floorNode = SCNNode(geometry: floor)
            floorNode.physicsBody?.categoryBitMask = 5
            floorNode.physicsBody?.collisionBitMask = 1
            floorNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            floorNode.simdTransform = anchor.transform
            
            // Add physics node to plane node
           
            planeNode = SCNNode()
            planeNode?.name = "magicBounds"
            planeNode?.addChildNode(hatNode)
            planeNode?.addChildNode(capNode)
            planeNode?.addChildNode(bottomNode)
            planeNode?.addChildNode(floorNode)
            planeNode?.physicsBody?.allowsResting = true
            let shape = SCNPhysicsShape(node: planeNode!, options: [SCNPhysicsShape.Option.type: SCNPhysicsShape.ShapeType.concavePolyhedron])
            planeNode?.physicsBody = SCNPhysicsBody(type: .static, shape: shape)
            planeNode?.physicsBody?.categoryBitMask = 5
            planeNode?.physicsBody?.collisionBitMask = 1
            hatPlaced = true
            return planeNode
        }
        return nil
    }
    
    
    // MARK: - ARSCNViewDelegate
    
/*
    // Override to create and configure nodes for anchors added to the view's session.
    func renderer(_ renderer: SCNSceneRenderer, nodeFor anchor: ARAnchor) -> SCNNode? {
        let node = SCNNode()
     
        return node
    }
*/
    
    func session(_ session: ARSession, didFailWithError error: Error) {
        // Present an error message to the user
        
    }
    
    func sessionWasInterrupted(_ session: ARSession) {
        // Inform the user that the session has been interrupted, for example, by presenting an overlay
        
    }
    
    func sessionInterruptionEnded(_ session: ARSession) {
        // Reset tracking and/or remove existing anchors if consistent tracking is required
        
    }
}
