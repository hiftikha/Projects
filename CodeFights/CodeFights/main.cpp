//
//  main.cpp
//  CodeFights
//
//  Created by Haroon Iftikhar on 11/12/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

long long standingInTheQueue(std::vector<int> heights, std::string directions) {
    
    long long sumOfHowManyPeopleCanBeSeen = 0;
    int myHeight = 999;
    char myDirection = 'a';
    int lastPersonsHeight = 0;
    if(heights.size() == directions.length()){
        for (int heightOfPerson = 0; heightOfPerson < heights.size(); heightOfPerson++) {
            for (int directionOfPerson = 0; directionOfPerson < directions.length(); directionOfPerson++) {
                if (heights[heightOfPerson] < heights[heightOfPerson+1] && strcmp(&directions[directionOfPerson], "R")) {
                    sumOfHowManyPeopleCanBeSeen++;
                }
                if (heights[heightOfPerson] < heights[heightOfPerson-1] && strcmp(&directions[directionOfPerson], "L")) {
                    sumOfHowManyPeopleCanBeSeen++;
                }
                if (heights[heightOfPerson] > heights[heightOfPerson+1] && strcmp(&directions[directionOfPerson], "R")) {
                    myHeight = heights[heightOfPerson];
                    myDirection = directions[directionOfPerson];
                }
                if (myHeight > heights[heightOfPerson] && myDirection == 'R'){
                    if (lastPersonsHeight < heights[heightOfPerson]) {
                        sumOfHowManyPeopleCanBeSeen++;
                    }
                    lastPersonsHeight = heights[heightOfPerson];
                    sumOfHowManyPeopleCanBeSeen++;
                }
            }
        }
    }
    return sumOfHowManyPeopleCanBeSeen;
}

bool checkPalindrome(string inputString) {
    int lengthOfString = inputString.length();
    bool palin = false;
    
    for(int i = 0; i < lengthOfString; i++){
        if(inputString[i] == inputString[lengthOfString-i-1]){
            palin = true;
        }
        if(inputString[i] != inputString[lengthOfString-i-1]){
            palin = false;
        }
    }
    return palin;
}

int adjacentElementsProduct(std::vector<int> inputArray) {
    int product = 0;
    int LargestProduct = 0;
    for(int i=0; i< inputArray.size(); i++){
        product = inputArray[i] * inputArray[i+1];
        if(product > LargestProduct){
            LargestProduct = product;
        }
    }
    return LargestProduct;
}

int maximumSubsetProduct(std::vector<int> a) {
    vector<int> b;
    long long multipleA = 1;
    long long multipleB = 1;
    int HighestNeg = 1;
    int temp = 0;
    int numNegative = 0;
    if(a.size() == 1){
        return 1;
    }
    for(int i=0; i < a.size(); i++){
        multipleA *= a[i];
        if(a[i] < 0){
            numNegative++;
        }
    }
    b = a;
    if(numNegative % 2 == 0){
        return 1;
    }
    else{
        for(int i=0; i < b.size(); i++){
            if(b[i]<0){
                if(b[i]<0 && b[i]>temp){
                    temp = b[i];
                    b[i] = 1;
                }
                temp = b[i];
                if(numNegative == 1){
                    b[i] = 1;
                }
            }
        }
        for(int i=0; i < b.size(); i++){
            multipleB *= b[i];
        }
    }
    return multipleA/multipleB;
}

int shapeArea(int n) {
    int maxWidth = 0;
    int answer = 0;
    if(n != 1){
        maxWidth = 2*n-1;
    }
    else{
        maxWidth = 1;
        return 1;
    }
    answer = shapeArea(n-1) + maxWidth + 1;
    return answer;
}

int makeArrayConsecutive2(std::vector<int> statues) {
    vector<int> HaveStatues;
    int statuesNeeded = 0;
    int statuesDiff = 0;
    for(int i =0; i < statues.size(); i++){
        HaveStatues.push_back(statues[i]);
    }
    sort(HaveStatues.begin(), HaveStatues.end());
    for (int i=0; i< statues.size(); i++) {
        if (i != 0 && HaveStatues[i] != HaveStatues[i-1]+1) {
            statuesDiff = HaveStatues[i]-HaveStatues[i-1];
            for (int j=0; j< statuesDiff-1; j++) {
                HaveStatues.push_back(HaveStatues[i-1] + 1 + j);
                statuesNeeded++;
            }
        }
    }
    return statuesNeeded;
}

bool almostIncreasingSequence(std::vector<int> sequence) {
    int numbersInSequence = 0;
    for(int i=0; i <= sequence.size(); i++){
        if (i == 0 && sequence[i] <= sequence[i+1]) {
            numbersInSequence++;
        }
        else if (i == sequence.size()-1 && sequence[i] <= sequence[i-1]) {
            numbersInSequence++;
        }
        else if (sequence.size() > 2 && sequence[i-1] < sequence[i] > sequence[i+1]){
            sequence.erase(sequence.begin()+i);
            numbersInSequence = numbersInSequence + 2;
        }
        else if (i == 0 && sequence[i] >= sequence[i+1]){
            sequence.erase(sequence.begin());
        }
        else if (i == sequence.size()-1 && sequence[i] <= sequence[i-1]) {
            sequence.erase(sequence.begin()+sequence.size()-1);
        }
        else if (sequence[i] < sequence[i+1]){
            numbersInSequence++;
        }
        else if (sequence[i] > sequence[i+1]){
            if (sequence[i]>sequence[i-1]) {
                sequence.erase(sequence.begin()+i+1);
                numbersInSequence++;
            }
            else if (sequence[i]<sequence[i-1]) {
                sequence.erase(sequence.begin()+i);
                numbersInSequence++;
            }
        }
        else if (sequence[i-1] == sequence[i+1]){
            return false;
        }
        else if (numbersInSequence == sequence.size()){
            return true;
        }
        
    }
    return false;
}

int matrixElementsSum(std::vector<std::vector<int>> matrix) {
    
    int rooms = 0;
    vector<int> zeroColumn;
    for(int row = 0; row <matrix.size(); row++){
        for(int column = 0; column < matrix[0].size(); column++){
            if (zeroColumn.size() == matrix[0].size() && zeroColumn[column] == 0) {
                rooms = matrix[row][column] + rooms;
            }
            if (row == 0 && matrix[row][column] != 0) {
                rooms = matrix[row][column] + rooms;
            }
            if(matrix[row][column] == 0){
                if (row == 0) {
                    zeroColumn.push_back(1);
                }
                else
                zeroColumn[column] = 1;
            }
            else{
                if (row == 0) {
                    zeroColumn.push_back(0);
                }
                else if(zeroColumn[column] != 1){
                    zeroColumn[column] = 0;
                }
            }
            
        }
    }
    return rooms;
}

std::vector<std::string> allLongestStrings(std::vector<std::string> inputArray) {
    
    vector<string> longestWords;
    int longestWordSize = 0;
    for (int i=0; i < inputArray.size(); i++) {
        if (inputArray[i].size() > longestWordSize) {
            longestWordSize = inputArray[i].size();
        }
    }
    for (int i=0; i < inputArray.size(); i++) {
        if (inputArray[i].size() == longestWordSize) {
            longestWords.push_back(inputArray[i]);
        }
    }
    return longestWords;
}

int commonCharacterCount(std::string s1, std::string s2) {
    
    int commonCharacters = 0;
    for (int i=0; i<s1.length(); i++) {
        for (int j=0; j<s2.length(); j++) {
            if (s1[i] == s2[j]) {
                commonCharacters++;
                s2[j] = ' ';
                i++;
                j=0;
            }
        }
    }
    return commonCharacters;
}

bool isLucky(int n) {
    
    int length = to_string(n).length();
    int div = 1;
    int lastHalf = 0;
    int firstHalf = 0;
    int pointer = length;
    int mid = length/2 - 1;
    while (pointer >= 0)
    {
        if(pointer > mid){
            lastHalf = (n / div % 10) + lastHalf;
            div = div /10;
            pointer--;
        }
        else{
            firstHalf = (n / div % 10) + firstHalf;
            div = div /10;
            pointer--;
        }
    }
    
    if(lastHalf == firstHalf){
        return true;
    }
    return false;
}

string solution(string S, int K) {
    // write your code in C++14 (g++ 6.2.0)
    string licenseKey;
    int reversePointer = 0;
    int place = 0;
    for(int pointer = S.size()-1; pointer >= 0 ; pointer--){
        if(S[pointer] != '-'){
            licenseKey.insert(licenseKey.begin(),toupper(S[pointer]));
            reversePointer++;
        }
        if (reversePointer % K == 0) {
            if(pointer != 0){
            licenseKey.insert(licenseKey.end()-reversePointer-place,'-');
                place++;
            }
        }
    }
    return licenseKey;
}

int firstDuplicate(std::vector<int> a) {
    vector<int> isDuplicate(a.size()+1,0);
    for(int i=0; i < a.size(); i++){
        if(isDuplicate[a[i]] != 0){
            return a[i];
        }
        isDuplicate[a[i]] = 1;
    }
    return -1;
}

int firstDuplicateON(std::vector<int> a) {
    for(int i=0; i < a.size(); i++){
        int t = abs(a[i]);
        if(a[t - 1] < 0)
            return t;
        a[t - 1] = - a[t - 1];
    }
    return -1;
}

char firstNotRepeatingCharacter(std::string s) {
    int arr[256]={0};
    char c = '_';
    
    for(int j=0;j<s.length();j++)
    {
        arr[s[j]]++;
    }
    for(int j=0;j<s.length();j++)
    {
        if(arr[s[j]]==1)
        {
            c=s[j];
            break;
        }
    }
    return c;
}

std::vector<std::vector<int>> rotateImage(std::vector<std::vector<int>> a) {
    int m = a.size();
    int n = m;
    vector<vector<int>> b(m, vector<int>(n));
    for ( int i = 0; i < m; i++ ) {
        for ( int j = i; j < n; j++ ) {
            int tmp = a[i][j];
            b[i][j] = a[j][i];
            b[j][i] = tmp;
        }
    }
    // Swap the columns
    for ( int i = 0; i < m; i++ ) {
        for ( int j = 0; j < n/2; j++ ) {
            int tmp = b[i][j];
            b[i][j] = b[i][n-1-j];
            b[i][n-1-j] = tmp;
        }
    }
    return b;
}

/* JAVA
bool containsDuplicate(int[] nums) {
    Arrays.sort(nums);
    for (int i = 0; i < nums.length - 1; ++i) {
        if (nums[i] == nums[i + 1]) return true;
    }
    return false;
}
*/

bool sumOfTwo(std::vector<int> a, std::vector<int> b, int v) {
    unordered_set<int> hashset;
    if(a.size() && b.size() == 0)
        return false;
    for(int i=0; i<a.size(); i++){
        hashset.insert(v-a[i]);
    }
    for(int j=0; j<b.size(); j++){
        if(hashset.count(b[j]))
            return true;
    }
    
    return false;
}

int arrayMaxConsecutiveSum2(std::vector<int> inputArray) {
    int can = 0, best = -1001;
    for(int n : inputArray){
        can += n;
        best = best > can ? best : can;
        can = can > 0 ? can : 0;
    }
    return best;
}

int solution(string A, string B) {
    // write your code in C++14 (g++ 6.2.0)
    string holder = A;
    string substring = B;
    int holderSize = A.size();
    int substringSize = B.size();
    int numberOfRepeats = 1;
    while (numberOfRepeats < substringSize) {
        if (holderSize < substringSize) {
            if (holder.find(substring) != std::string::npos) {
                return numberOfRepeats;
            }
            holder.append(A);
            numberOfRepeats++;
        }
        if (holderSize > substringSize) {
            if (holder.find(substring) != std::string::npos) {
                return 1;
            }
        }
        if (holderSize == substringSize && holder.compare(substring) == 0) {
            return 1;
        }
    }
    return -1;
}

std::vector<std::vector<std::string>> groupingDishes(std::vector<std::vector<std::string>> dishes) {
    map <string, vector<string>> my_map;
    
    for (int i = 0; i < dishes.size(); i++) {
        for (int j = 1; j < dishes[i].size(); j++) {
            my_map[dishes[i][j]].push_back(dishes[i][0]);
        }
    }
    
    vector <vector <string>> result;
    
    for (auto const& m : my_map) {
        string key = m.first;
        vector<string> val = m.second;
        
        if (val.size() > 1) {
            vector <string> temp;
            temp.push_back(key);
            sort(val.begin(), val.end());
            for (int i = 0; i < val.size(); i++)
                temp.push_back(val[i]);
            result.push_back(temp);
        }
        
    }
    
    return result;
    
}

bool areFollowingPatterns(std::vector<std::string> strings, std::vector<std::string> patterns) {
    map<string,string> mp12;
    map<string,string> mp21;
    for(int i=0;i<strings.size();i++){
        if(mp12.find(strings[i]) != mp12.end() && mp12[strings[i]] != patterns[i]) return false;
        if(mp21.find(patterns[i]) != mp21.end() && mp21[patterns[i]] != strings[i]) return false;
        mp12[strings[i]] = patterns[i];
        mp21[patterns[i]] = strings[i];
    }
    return true;
}

bool palindromeRearranging(std::string inputString) {
    map<char,int> letters;
    map<char,int>:: iterator it;
    int numOfTimes = 1;
    bool palindrome = false;
    for(char i: inputString){
        letters.find(i);
        if(it != letters.end())
            it->second++;
        else
            letters.insert(pair<char,int>(i,numOfTimes));
    }
    for(auto& x: letters){
        if(x.second%2 == 0) palindrome = true;
        else palindrome = false;
    }
    return palindrome;
}

struct Record {
    int idNum;
    string fname;
    string lname;
    string phoneNum;
    Record(int ID, string first, string last, string phone){
        idNum = ID;
        fname = first;
        lname = last;
        phoneNum = phone;
    }
};

ostream & operator<<(ostream & out, const Record & p) {
    out << p.idNum << " " << p.fname << " " << p.lname << " " << p.phoneNum << "\n";
    return out;
}

bool LOGOUT(){
    cout << "200 OK" << "\n";
    return false;
}

void ADD(int id, string first, string last, string phone, vector<Record>& addressBook){
    addressBook.push_back(Record(id, first, last, phone));
    cout << "200 OK \n";
    cout << "The new Record ID is " << id << "\n";
}

void LIST(vector<Record> addBook) {
    cout << "200 OK" << "\n";
    cout << "\nThe list of records in the book: \n";
    for (auto i = addBook.begin(); i != addBook.end(); i++)
        cout << i->idNum << "        " << i->fname << "        " << i->lname << "        " << i->phoneNum << "\n";
}

bool DELETE(int id, vector<Record>& addBook) {
    for (auto i = addBook.begin(); i != addBook.end(); i++) {
        if (i->idNum == id) {
            i = addBook.erase(i);
            cout << "200 OK \n";
            return true;
        }
        else
            cout << "403 The Record ID does not exist. \n";
    }
    return false;
}

void LOOK(int option, string search, vector<Record> addressBook){
    bool firstRecord = true;
    bool found = false;
    for(int i = 0; i < addressBook.size(); i++){
        if (option == 1) {
            if(addressBook[i].fname == search){
                found = true;
                if(firstRecord) cout << "200 OK" << "\n";
                cout << addressBook[i].idNum << " " << addressBook[i].fname << " " << addressBook[i].lname << " " << addressBook[i].phoneNum << "\n";
                firstRecord = false;
            }
        }
        else if (option == 2) {
            if(addressBook[i].lname == search){
                found = true;
                if(firstRecord) cout << "200 OK" << "\n";
                cout << addressBook[i].idNum << " " << addressBook[i].fname << " " << addressBook[i].lname << " " << addressBook[i].phoneNum << "\n";
                firstRecord = false;
            }
        }
        else if (option == 3) {
            if(addressBook[i].phoneNum == search){
                found = true;
                if(firstRecord) cout << "200 OK" << "\n";
                cout << addressBook[i].idNum << " " << addressBook[i].fname << " " << addressBook[i].lname << " " << addressBook[i].phoneNum << "\n";
                firstRecord = false;
            }
        }
    }
    if(!found) cout <<  "404 Your search did not match any records. \n";
}


bool LOGIN(string username, string pw, map<string,string> users){
    map<string,string>::iterator it;
    it = users.find(username);
    if(it != users.end()) {
        if(it->second == pw) {
            cout << "200 OK" << "\n";
            return true;
        }
        else {
            cout << "410 Wrong UserID or Password. \n";
            return false;
        }
    }
    else {
        cout << "410 Wrong UserID or Password. \n";
        return false;
    }
    
}

std::vector<std::vector<int>> constructSubmatrix(std::vector<std::vector<int>> matrix, std::vector<int> rowsToDelete, std::vector<int> columnsToDelete) {
    vector<vector<int>> answer;
    vector<int> temp;
    for(int i = 0; i < rowsToDelete.size(); i++){
        matrix[rowsToDelete[i]].clear();
    }
    
    
    for(int i = 0; i < columnsToDelete.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[j].size() != 0)
                matrix[j].erase(matrix[j].begin()+columnsToDelete[i]-1);
        }
    }
    for(int i = 0; i < matrix.size(); i++){
        if(matrix[i].size() == 0) matrix.erase(matrix.begin()+i);
    }
    
    cout << "size: " << matrix[0].size() << endl;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cout << matrix[i][j] << ", ";
            //
            
        }
        cout << endl;
    }
    return matrix;
    /*for(int i = 0; i < matrix.size(); i++){
     for(int j = 0; j < matrix[0].size(); j++){
     cout << matrix[i][j] << " , ";
     }
     cout << endl;
     }*/
}

std::vector<std::string> newNumeralSystem(char number) {
    vector<string> answer;
    unordered_map<int,char> alphabets;
    unordered_map<int,char>::const_iterator a;
    unordered_map<int,char>::const_iterator b;
    char num;
    int numToSum = 0;
    int ascii = 65;
    string add = "";
    for(int i = 0; i < 26; i++){
        char alpha = char(ascii);
        pair<int,char> my (i,alpha);
        alphabets.insert(my);
        ascii++;
    }
    a = alphabets.find(int(number) - 65);
    if(a != alphabets.end()){
        numToSum = a->first;
        num = a->second;
    }
    for(int i = 0; i < numToSum; i++){
        int add1 = 0;
        char char1;
        
        a = alphabets.find(i);
        if(a != alphabets.end()){
            add1 = a->first;
            char1 = a->second;
        }
        b = alphabets.find(numToSum-1);
        if(b != alphabets.end()){
            numToSum = b->first;
            num = b->second;
        }
        add += char1;
        add = add + " + ";
        add += num;
        
        answer.push_back(add);
        add = "";
        
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
    return answer;
}

int main() {
    // insert code here...
    newNumeralSystem('F');
    
    
    return 0;
}
