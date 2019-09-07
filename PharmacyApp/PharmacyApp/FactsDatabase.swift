//
//  FactsDatabase.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 2/16/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import Foundation
import SQLite

class Database{
    
    class var sharedDatabase: Database {
        struct My {
            static var instance = Database()
        }
        return My.instance
    }

    private var database: Connection!
    public let tablesArray: [Table]
    public var FavArray: [String]
    public var factsUsed: [UInt32]
    public var termsUsed: [UInt32]
    public var factID: Int
    public var factFav: Int
    public var coins: Int
    public var id: Expression<Int>
    public var factDefination: Expression<String>
    public var alreadyUsed: Expression<Int>
    public var favoriteBool: Expression<Int>
    public var genericName: Expression<String>
    public var brandName: Expression<String>
    public var className: Expression<String>
    public var actionName: Expression<String>
    
    init() {
        do{
            let fileUrl = Bundle.main.path(forResource: "pharmacyDB", ofType: "db")
            database = try Connection(fileUrl!)
            print("Database created \(fileUrl ?? "DocumentDirectory")")
        } catch {
            print("This is an error \(error)")
        }
        tablesArray = [Table("Fact"), Table("HistoryFact"),Table("Term"),Table("ThemedFact")]
        FavArray = []
        factsUsed = []
        termsUsed = []
        factID = 0
        factFav = 0
        coins = 5
        id = Expression<Int>("_id")
        factDefination = Expression<String>("fact")
        alreadyUsed = Expression<Int>("alreadyused")
        favoriteBool = Expression<Int>("favorite")
        genericName = Expression<String>("genericname")
        brandName = Expression<String>("brandname")
        className = Expression<String>("class")
        actionName = Expression<String>("action")
        //category = Expression<Int>("category")
    }
    
    func addCoins(earned: Int){
        coins = earned + coins
    }

    func query(table: Table) -> String{
        do{
            let facts = try database.prepare(table)
            let totalFacts = try database.scalar(table.count)
            var random: UInt32
            if Int(factsUsed.count) == totalFacts {
                factsUsed.removeAll()
            }
            repeat {
                random = arc4random_uniform(UInt32(totalFacts))
            } while factsUsed.contains(random)
            for fact in facts{
                if(fact[id] == Int(random)){
                    print(fact[factDefination])
                    factsUsed.append(random)
                    factID = fact[id]
                    factFav = 0
                    return fact[factDefination]
                }
            }
        } catch{
            print(error)
        }
        return ""
    }
    
    func queryTerm(table: Table) -> String{
        do{
            let terms = try database.prepare(table)
            let totalTerms = try database.scalar(table.count)
            var random: UInt32
            if Int(termsUsed.count) == totalTerms {
                termsUsed.removeAll()
            }
            repeat {
                random = arc4random_uniform(UInt32(totalTerms))
            } while termsUsed.contains(random)
            for term in terms{
                if(term[id] == Int(random)){
                    //print(term[genericName])
                    termsUsed.append(random)
                    return term[genericName]
                }
            }
        } catch{
            print(error)
        }
        return ""
    }
    
    func queryTermField(table: Table, chooseString: String, row: Int) -> String{
        do{
            let terms = try database.prepare(table)
            for term in terms{
                if(chooseString == "genericName"){
                    if(term[id] == row){
                        return term[genericName]
                    }
                }
                if(chooseString == "brandName"){
                    if(term[id] == row){
                        return term[brandName]
                    }
                }
                if(chooseString == "class"){
                    if(term[id] == row){
                        return term[className]
                    }
                }
                if(chooseString == "action"){
                    if(term[id] == row){
                        return term[actionName]
                    }
                }
                
            }
        } catch {
            print(error)
        }
        return ""
    }
    
    func queryTermID(table: Table, termToCheck: String) -> Int{
        do{
            let terms = try database.prepare(table)
            for term in terms{
                if(term[genericName] == termToCheck){
                    return term[id]
                }
            }
        } catch {
            print(error)
        }
        return 0
    }
    
    func queryFactID(table: Table, factToCheck: String) -> Int{
        do{
            let facts = try database.prepare(table)
            for fact in facts{
                if(fact[factDefination] == factToCheck){
                    return fact[id]
                }
            }
        } catch{
            print(error)
        }
        return 0
    }
    
    func queryFav(table: Table) -> [String]{
        do{
            FavArray.removeAll()
            let favorites = table.filter(favoriteBool == 1)
            let facts = try database.prepare(favorites)
            for fact in facts{
                    //fact[self.favorite]
                    print(fact[factDefination])
                    FavArray.append(fact[factDefination])
            }
        } catch{
            print(error)
        }
        return FavArray
    }

    func updateFavorite(table: Table, updateField: Expression<Int>){
        let factToUpdate = table.filter(id == factID)
        var favorite: Bool
        //var used: Bool
        if (factFav == 0){
            favorite = false
        }
        else{
            favorite = true
        }
        if favorite {
            do{
                try database.run(factToUpdate.update(updateField <- 0))
                factFav = 0
                print("Unfavorited")
            } catch{
                print(error)
            }
        }
        else{
            do{
                    let example = try database.prepare(factToUpdate)
                try database.run(factToUpdate.update(updateField <- 1))
                factFav = 1
                print("Favorited")
                for fact in example{
                    print("After updating", fact[favoriteBool])
                }
            } catch{
                print(error)
            }
        }
    }
}
