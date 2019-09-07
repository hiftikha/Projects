//
//  ViewController.swift
//  ScanProSwift
//
//  Created by Haroon Iftikhar on 3/15/18.
//  Copyright © 2018 Voyomotive. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var background: UIImageView!
    @IBOutlet weak var mainStack: UIStackView!
    @IBOutlet weak var overviewStack: UIStackView!
    @IBOutlet weak var controllerStack: UIStackView!
    @IBOutlet weak var issueStack: UIStackView!
    @IBOutlet weak var overviewTitle: UIStackView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        addTitleViewImage()
        background.image = #imageLiteral(resourceName: "scan_pro_background")
        addBackgroungToStacks(overview: overviewTitle, controller: controllerStack, issue: issueStack)
       
        let tapControllers = UITapGestureRecognizer(target: self, action: #selector(scanType))
        let tapIssues = UITapGestureRecognizer(target: self, action: #selector(scanType))
        issueStack.accessibilityIdentifier = "issues"
        controllerStack.accessibilityIdentifier = "controllers"
        issueStack.addGestureRecognizer(tapIssues)
        controllerStack.addGestureRecognizer(tapControllers)
        
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    @objc func scanType(_sender: UITapGestureRecognizer){
        if let sender = _sender.view!.accessibilityIdentifier{
        
            switch sender {
            case "issues":
                self.performSegue(withIdentifier: "issuesController", sender: nil)
            case "controllers":
                self.performSegue(withIdentifier: "controllersController", sender: nil)
            default:
                self.performSegue(withIdentifier: "overviewController", sender: nil)
            }
        }
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
    
    func addBackgroungToStacks( overview: UIStackView, controller: UIStackView, issue: UIStackView){
        let view = UIView()
        view.backgroundColor = UIColor.green
        view.translatesAutoresizingMaskIntoConstraints = false
        overview.insertSubview(view, at: 0)
        pin(this: view, to: overview)
        
        let viewTwo = UIView()
        viewTwo.backgroundColor = UIColor.red
        viewTwo.translatesAutoresizingMaskIntoConstraints = false
        controller.insertSubview(viewTwo, at: 0)
        pin(this: viewTwo, to: controller)
        
        let viewThree = UIView()
        viewThree.backgroundColor = UIColor.yellow
        viewThree.translatesAutoresizingMaskIntoConstraints = false
        issue.insertSubview(viewThree, at: 0)
        pin(this: viewThree, to: issue)
        
    }
    
    func pin(this: UIView, to view: UIStackView){
        NSLayoutConstraint.activate([this.leadingAnchor.constraint(equalTo: view.leadingAnchor),this.trailingAnchor.constraint(equalTo: view.leadingAnchor),this.topAnchor.constraint(equalTo: view.topAnchor),this.bottomAnchor.constraint(equalTo: view.bottomAnchor)])
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

