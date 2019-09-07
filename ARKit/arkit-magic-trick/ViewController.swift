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
    var ballsThrown: [SCNNode] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Set the view's delegate
        sceneView.delegate = self
        sceneView.session.delegate = self
        
        // Show statistics such as fps and timing information
        sceneView.showsStatistics = true
        
        // Set the scene to the view
        sceneView.scene = SCNScene()
        sceneView.debugOptions = [.showPhysicsShapes]
        sceneView.debugOptions = [.showCreases]
        //sceneView.debugOptions = [.showBoundingBoxes]
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

    private func createNewBall() {
        NSLog("New Ball is working!")
        
        //let ball = SCNSphere(radius: 0.02)
        let ballNode = magicBall.node()
        ballNode.name = UUID().uuidString
        ballName = ballNode.name!
        ballsNode?.addChildNode(ballNode)
        
        print("The name of the ball's node is " + ballName)
        
        let camera = sceneView.session.currentFrame?.camera
        let cameraTransform = camera?.transform
        ballNode.simdTransform = cameraTransform!
        
    }
    
    @IBAction func onThrowBall(_ sender: Any) {
        createNewBall()
        
        NSLog("Ball Throw is working!")
        if !(ballName == "") {
        let ballToThrow = ballsNode?.childNode(withName: ballName, recursively: true)
        ballsThrown.append(ballToThrow!)
            print("The ball's X is?: ", ballToThrow?.worldPosition.x as Any)
            print("The ball's Y is?: ", ballToThrow?.worldPosition.y as Any)
            print("The ball's Z is?: ", ballToThrow?.worldPosition.z as Any)
        
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
        //ballToThrow?.removeFromParentNode()
        }
    }
    
    @IBAction func onMagicTrick(_ sender: Any) {
        NSLog("Magic Trick is working!")
        let magicBound = sceneView.scene.rootNode.childNode(withName: "magicBounds", recursively: true)
        
        let magicBoundWorldPosition = magicBound!.worldPosition
        let (tubeMin, tubeMax): (SCNVector3, SCNVector3) = magicBound!.boundingBox
        
        let minX = magicBoundWorldPosition.x + tubeMin.x
        let minY = magicBoundWorldPosition.y + tubeMin.y
        let minZ = magicBoundWorldPosition.z + tubeMin.z
        
        print("MIN", tubeMin.x, tubeMin.y, tubeMin.z)
        print("MAX", tubeMax.x, tubeMax.y, tubeMax.z)
        
        let maxX = magicBoundWorldPosition.x + tubeMax.x
        let maxY = magicBoundWorldPosition.y + tubeMax.y
        let maxZ = magicBoundWorldPosition.z + tubeMax.z
        
        print("The magicBounds X are?: ", magicBoundWorldPosition.x)
        print("The magicBounds Y are?: ", magicBoundWorldPosition.y)
        print("The magicBounds Z are?: ", magicBoundWorldPosition.z)
        
        for ball in ballsThrown{
            let ballPosition = ball.presentation.worldPosition
            let MagicTrickCondition = ballPosition.x <= maxX && ballPosition.x >= minX && ballPosition.y <= maxY && ballPosition.y >= minY && ballPosition.z <= maxZ && ballPosition.z >= minZ
            
            print("The boundaries of the hat's X are: ", minX,", ", maxX)
            print("The boundaries of the hat's Y are: ", minY,", ", maxY)
            print("The boundaries of the hat's Z are: ", minZ,", ", maxZ)
            
            print("The ball's X is?: ", ballPosition.x)
            print("The ball's Y is?: ", ballPosition.y)
            print("The ball's Z is?: ", ballPosition.z)
            
            print("The ball is in the hat?: ", MagicTrickCondition)
            if(MagicTrickCondition){
                if(!ball.isHidden){
                ball.isHidden = true
                print("The ball has been hidden: ", ball.name!)
                }
                else if(ball.isHidden){
                ball.isHidden = false
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
        
        let hatMaterial = SCNMaterial()
        hatMaterial.diffuse.contents = UIColor.lightGray
        
        if(!hatPlaced && anchor is ARPlaneAnchor){
            let hat = SCNTube(innerRadius: 0.15, outerRadius: 0.16, height: 0.2)
            hat.firstMaterial = hatMaterial
            //hat.firstMaterial?.diffuse.contents = UIColor.black
            let hatNode = SCNNode(geometry: hat)
            hatNode.name = "magicBounds"
            //hatNode.physicsBody = SCNPhysicsBody(type: .static, shape: shape)
            
            
            let cap = SCNTube(innerRadius: 0.15, outerRadius: 0.25, height: 0.01)
            cap.firstMaterial = hatMaterial
            //cap.firstMaterial?.diffuse.contents = UIColor.black
            let capNode = SCNNode(geometry: cap)
            //capNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            capNode.position = yTransformation(point: hatNode.position, distance: 0.1)
           
            let bottom = SCNCylinder(radius: 0.15, height: 0.01)
            bottom.firstMaterial = hatMaterial
            //bottom.firstMaterial?.diffuse.contents = UIColor.black
            let bottomNode = SCNNode(geometry: bottom)
            //bottomNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            
            bottomNode.position = yTransformation(point: hatNode.position, distance: -0.1)
            
            let floor = SCNFloor()
            floor.reflectivity = 0.10
            floor.firstMaterial?.colorBufferWriteMask = SCNColorMask(rawValue: 0)
            let floorNode = SCNNode(geometry: floor)
            floorNode.physicsBody?.categoryBitMask = 4
            floorNode.physicsBody?.collisionBitMask = 1
            floorNode.physicsBody = SCNPhysicsBody(type: .static, shape: nil)
            floorNode.simdTransform = anchor.transform
            
            // Add physics node to plane node
           
            planeNode = SCNNode()
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
