//: Playground - noun: a place where people can play

import Cocoa
/*
var num = 0
var answer = 0
let times = 13
var space = "   "

for _ in 0..<times{
    for j in 0..<times{
        answer = j*num
        if(answer < 10){
            space = "   "
            print(space, j*num, terminator: "")
        }
        else if(answer < 100){
            space = "  "
            print(space, j*num, terminator: "")
        }
        else{
            space = " "
            print(space, j*num, terminator: "")
        }
    }
    num += 1
    print("")
}
*/

var numbers = [3,6,9,10,11,12,13]
var numbers2 = [4,6,5,9,13,15,3]
numbers.map({
    (number: Int) -> Int in
    let remainder = number % 2
    return remainder == 1 ? 0 : number
    })
