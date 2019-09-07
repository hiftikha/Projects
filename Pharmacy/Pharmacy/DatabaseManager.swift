//
//  DatabaseManager.swift
//  Pharmacy
//
//  Created by Haroon Iftikhar on 2/6/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import Foundation
import SQLite3

func openDatabase() -> OpaquePointer? {
    var db: OpaquePointer? = nil
    let path = NSSearchPathForDirectoriesInDomains(
        .documentDirectory, .userDomainMask, true
        ).first!

    if sqlite3_open("\(path)/pharmacyDB.db", &db) == SQLITE_OK {
        print("Successfully opened database")
        return db
    } else {
        print("Unable to open database. Verify the directory described")
        return db
    }
}

let db = openDatabase()
//let queryStatementString = "SELECT * FROM Contact;"
//let updateStatementString = "UPDATE Contact SET Name = 'Chris' WHERE Id = 1;"

func numberOfFacts(_ queryStatementString: String) -> Int{
    var queryStatement: OpaquePointer? = nil
    // 1
    var numFacts = 0
    if sqlite3_prepare_v2(db, queryStatementString, -1, &queryStatement, nil) == SQLITE_OK {
        numFacts = Int(sqlite3_column_count(queryStatement))
        return numFacts
    }
    return Int(numFacts)
}

func query(_ queryStatementString: String) -> Fact?{
    var queryStatement: OpaquePointer? = nil
    // 1
    if sqlite3_prepare_v2(db, queryStatementString, -1, &queryStatement, nil) == SQLITE_OK {
        // 2
        if sqlite3_step(queryStatement) == SQLITE_ROW {
            // 3
            let id = sqlite3_column_int(queryStatement, 0)
            let used = sqlite3_column_int(queryStatement, 2)
            let fav = sqlite3_column_int(queryStatement, 3)
            // 4
            let queryResultCol1 = sqlite3_column_text(queryStatement, 1)
            let name = String(cString: queryResultCol1!)
            
            // 5
            print("Query Result:")
            print("\(id) | \(name)")
            let queryResult = Fact(fact: name, used: used, fav: fav)
            return queryResult
            
        } else {
            print("Query returned no results")
        }
    } else {
        print("SELECT statement could not be prepared")
    }
    
    // 6
    sqlite3_finalize(queryStatement)
    let result = Fact(fact: "name", used: 0, fav: 0)
    return result
}

func update(_ updateStatementString: String) {
    var updateStatement: OpaquePointer? = nil
    if sqlite3_prepare_v2(db, updateStatementString, -1, &updateStatement, nil) == SQLITE_OK {
        if sqlite3_step(updateStatement) == SQLITE_DONE {
            print("Successfully updated row.")
        } else {
            print("Could not update row.")
        }
    } else {
        print("UPDATE statement could not be prepared")
    }
    sqlite3_finalize(updateStatement)
}
