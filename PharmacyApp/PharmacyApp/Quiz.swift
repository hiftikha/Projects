//
//  Quiz.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 4/16/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Quiz: UIViewController {

    @IBOutlet weak var answer: UILabel!
    @IBOutlet weak var question: UILabel!
    @IBOutlet weak var firstChoice: UIButton!
    @IBOutlet weak var thirdChoice: UIButton!
    @IBOutlet weak var fourthChoice: UIButton!
    @IBOutlet weak var secondChoice: UIButton!
    @IBAction func first(_ sender: Any) {
        if Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: (firstChoice.titleLabel?.text)!) == correct && canAnswer {
            answer.text = "Correct!"
            score += 1
            canAnswer = false
        }
        else {
            answer.text = "Wrong! Correct answer: " + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: correct)
            canAnswer = false
        }
    }
    @IBAction func second(_ sender: Any) {
        if Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: (secondChoice.titleLabel?.text)!) == correct && canAnswer {
            answer.text = "Correct!"
            score += 1
            canAnswer = false
        }
        else {
            answer.text = "Wrong! Correct answer: " + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: correct)
            canAnswer = false
        }
    }
    @IBAction func third(_ sender: Any) {
        if Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: (thirdChoice.titleLabel?.text)!) == correct && canAnswer {
            answer.text = "Correct!"
            score += 1
            canAnswer = false
        }
        else {
            answer.text = "Wrong! Correct answer: " + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: correct)
            canAnswer = false
        }
    }
    @IBAction func fourth(_ sender: Any) {
        if Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: (fourthChoice.titleLabel?.text)!) == correct  && canAnswer {
            answer.text = "Correct!"
            score += 1
            canAnswer = false
        }
        else {
            answer.text = "Wrong! Correct answer: " + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: correct)
            canAnswer = false
        }
    }
    @IBAction func nextQuestion(_ sender: Any) {

        canAnswer = true
        newRound()
    }
    
    var choices: [UIButton] = []
    var newChoices: [String] = []
    var correct = 0
    var times = 10
    var canAnswer = true
    var score = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        times = 10
        choices = [firstChoice, secondChoice, thirdChoice, fourthChoice]
        newRound()
        
        // Do any additional setup after loading the view.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        
    }
    
    
    
    func newRound(){
        
        times -= 1
        if times > 0 {
            correct = 0
            answer.text = ""
            newChoices = loadNewChoices(array: choices)
            let ques = chooseQuestion(array: newChoices)
           let id = findTermID(choice: ques)
           setQuestion(termID: id)
        }
        else {
            answer.text = "You had \(score) correct answers! \n You won \(score*score) pills!"
            Database.sharedDatabase.addCoins(earned: score*score)
        }
        //setAnswer()
        
    }
    
    func setAnswer(){
        let random = Int(arc4random_uniform(UInt32(choices.count)))
        choices[random].titleLabel?.text = Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "genericName", row: correct)
    }

    func loadNewChoices(array: [UIButton]) -> [String]{
        var term = ""
        var newChoices : [String] = []
        print("count: ", array.count)
        for choice in array{
            term = Database.sharedDatabase.queryTerm(table: Database.sharedDatabase.tablesArray[2])
            choice.setTitle(term, for: .normal)
            newChoices.append(term)
            print("term: ", term)
        }
        return newChoices
    }
    
    func chooseQuestion(array: [String]) -> String {
        var ques = ""
        let random = Int(arc4random_uniform(UInt32(array.count)))
        ques = array[random]
        print("ques: ", ques)
        return ques
    }
    
    func findTermID(choice: String) -> Int{
        let correctAnswer = Database.sharedDatabase.queryTermID(table: Database.sharedDatabase.tablesArray[2], termToCheck: choice)
        correct = correctAnswer
        print(correctAnswer)
        return correctAnswer
    }
    
    func setQuestion(termID: Int) {
        question.text = "What is the brand name for " + Database.sharedDatabase.queryTermField(table: Database.sharedDatabase.tablesArray[2], chooseString: "brandName", row: termID)
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func shuffle(array: [UIButton]) -> [UIButton]{
        var toShuffle = array
        var shuffled : [UIButton] = []
        for i in 0..<toShuffle.count
        {
            let rand = Int(arc4random_uniform(UInt32(toShuffle.count)))
            shuffled.append(toShuffle[rand])
            toShuffle.remove(at: rand)
        }
        return shuffled
    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
