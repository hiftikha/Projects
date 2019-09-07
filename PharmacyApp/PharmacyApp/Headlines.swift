//
//  Headlines.swift
//  PharmacyApp
//
//  Created by Haroon Iftikhar on 4/15/18.
//  Copyright © 2018 Haroon Iftikhar. All rights reserved.
//

import UIKit

class Headlines: UITableViewController, XMLParserDelegate {
    
    @IBOutlet var headlineTableView: UITableView!
    
    var element = ""
    var collectItem = false
    var Titles = [String]()
    var Description = [String]()
    var Links = [String]()
    var headlinesNum = 0
    
    func parser(_ parser: XMLParser, didStartElement elementName: String, namespaceURI: String?, qualifiedName qName: String?, attributes attributeDict: [String : String] = [:]) {
        
        element = elementName
    }
    
    func parser(_ parser: XMLParser, foundCharacters string: String) {
        if element == "item" {
            collectItem = true
        }
        if string.trimmingCharacters(in: NSCharacterSet.whitespacesAndNewlines) != ""{
            if element == "title" && collectItem {
                print(string)
                Titles.append(string)
                headlinesNum += 1
            }
            if element == "link" && collectItem {
                print(string)
                Links.append(string)
            }
            if element == "pubDate" && collectItem {
                //print(string)
                Description.append(string)
            }
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        headlineTableView.dataSource = self
        loadHeadlines()
        // Uncomment the following line to preserve selection between presentations
        // self.clearsSelectionOnViewWillAppear = false

        // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
        // self.navigationItem.rightBarButtonItem = self.editButtonItem
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        //headlinesNum = 0
        //loadHeadlines()
        self.tableView.reloadData()
    }
    
    func loadHeadlines(){
        guard let requestUrl = URL(string:"http://www.pharmatimes.com/rss/appointments_rss.rss") else { return }
        let session = URLSession(configuration: .default)
        //let request = URLRequest(url:requestUrl)
        let task = session.dataTask(with: requestUrl, completionHandler: { (data, response, error) in
            if error == nil {
                //JSONSerialization
                //var urlContent = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)
                var xmlParser = XMLParser()
                xmlParser = XMLParser(data: data!)
                xmlParser.delegate = self
                xmlParser.parse()
            } else {
                print(error)
            }
        })
        task.resume()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        print(headlinesNum)
        return headlinesNum
        
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        //UIApplication.shared.open(URL(fileURLWithPath: Links[(tableView.indexPathForSelectedRow?.row)!]), options: [:], completionHandler: { (status) in })
        
        let indexPathSelect = tableView.indexPathForSelectedRow
        print(indexPathSelect?.row)
        
        UIApplication.shared.openURL(URL(string: Links[(indexPathSelect?.row)!])!)
        
        //getting the current cell from the index path
        //let currentCell = tableView.cellForRow(at: indexPathSelect!)! as UITableViewCell
        
        //getting the text of that cell
        //let currentItem = currentCell.textLabel!.text
        
        //let alertController = UIAlertController(title: "Simplified iOS", message: "You Selected " + Links[(indexPathSelect?.row)!] , preferredStyle: .alert)
        //let defaultAction = UIAlertAction(title: "Close Alert", style: .default, handler: nil)
        //alertController.addAction(defaultAction)
        
        //present(alertController, animated: true, completion: nil)
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "headline", for: indexPath)

        cell.textLabel?.text = Titles[indexPath.row]
        // Configure the cell...

        return cell
    }
    

    /*
    // Override to support conditional editing of the table view.
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    */

    /*
    // Override to support editing the table view.
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            // Delete the row from the data source
            tableView.deleteRows(at: [indexPath], with: .fade)
        } else if editingStyle == .insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        }    
    }
    */

    /*
    // Override to support rearranging the table view.
    override func tableView(_ tableView: UITableView, moveRowAt fromIndexPath: IndexPath, to: IndexPath) {

    }
    */

    /*
    // Override to support conditional rearranging of the table view.
    override func tableView(_ tableView: UITableView, canMoveRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the item to be re-orderable.
        return true
    }
    */

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
