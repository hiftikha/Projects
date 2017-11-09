/*
main.cpp
//  QuadTree
//
//  Created by Haroon Iftikhar on 2/14/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.

Description:
The program takes in the pre-order and produces the tree of that order listing the levels the pixels are in and an ascii image which corresponds to that tree


*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

//const int IMG_SIZE = 64;

struct QuadNode{
   char type;
   int level;
   QuadNode * quads[4];
   QuadNode(char color = 'u', int lvl = -1, QuadNode * ul = nullptr,
      QuadNode * ur = nullptr, QuadNode * dl = nullptr, QuadNode * dr = nullptr){
         type = color;
         level = lvl;
         quads[0] = ul;
         quads[1] = ur;
         quads[2] = dl;
         quads[3] = dr;
   }
};

class QuadTree{
   QuadNode *root;
    
/* Pre-Condition: The string should have been input */
   void frmStr(QuadNode * & ptr, string & encodeStr, int level)
   {
      char firstLetter;
      if (encodeStr.size() <= 0) return;
      else 
      {
         firstLetter = encodeStr[0];
         encodeStr = encodeStr.substr(1, encodeStr.size() - 1);
         if (firstLetter == 'i')
         {
            ptr = new QuadNode(firstLetter, level);
            for (int i = 0; i < 4; i++)
               frmStr(ptr->quads[i], encodeStr, level + 1);
         }
         else
            ptr = new QuadNode(firstLetter, level);
      }
   }
/* Post-Condition: The quadtree is produced. 
 The string is decoded into determining what nodes are i,b,and w. The levels are also assigned to each node. */
    
/* Pre-Condition: The quadtree should have been produced already */
   void totalLevels(QuadNode * ptr)
   {
      if (ptr != nullptr)
      {
         if (levels < ptr->level)
            levels = ptr->level;
         for (int i = 3; i >= 0; i--)
         {
            totalLevels(ptr->quads[i]);
         }
      }
   }
/* Post-Condition: The total # of levels of nodes are found. 
 The function checks which child has the most levels and then assigns the number to the variable levels */
    
/* Pre-Condition: The image should have been produced */
   void clearImage()
   {
      if (image != NULL)
      {
         for (int i = 0; i < imageDimension; i++)
            delete[] image[i];
         delete[] image;
         image = NULL;

         levels = 0;
         blacks = 0;
         pixelWidth = 0;
         imageDimension = 0;
      }
   }
/* Post-Condition: The image is cleared */
    
/* Pre-Condition: The tree should be created and then the function is able to call itself recursively using index and x and y Quads */
   void fillImage(QuadNode * ptr, int index, int xQuad, int yQuad)
   {
      char output;
      if (ptr != nullptr)
      {
         if (ptr->type == 'i')
         {
            for (int iter = 0; iter <= 3; iter++)
            {
               int n = imageDimension / pow(2, ptr->level + 1);
               int x = iter % 3 == 0 ? 0 : 1;
               int y = iter < 2 ? 0 : 1;
               x = xQuad + x * n;
               y = yQuad + y * n;
               fillImage(ptr->quads[iter], iter, x, y);
            }
            return;
         }
         else if (ptr->type == 'b')
            output = '@';
         else
            output = ' ';
         
         int n = imageDimension / pow(2, ptr->level);
         for (int i = 0; i < n; i++)
         {
            for (int j = 0; j < n; j++)
            {
               image[i+yQuad][j+xQuad] = output;
            }
         }
      }
   }
/* Post-Condition:  creates a matrix that contains image depending on the tree */
    
/* Pre-Condition:  Tree should be created and imageSize should have been input */
   void createImage(QuadNode * ptr, int imageSize)
   {
      clearImage();
      totalLevels(ptr);
      imageDimension = sqrt(imageSize);
      pixelWidth = sqrt(imageSize / pow(4, levels));
      if (image == NULL)
      {
         image = new char*[imageDimension];
         for (int i = 0; i < imageDimension; i++)
            image[i] = new char[imageDimension];
      }
      fillImage(ptr, 0, 0, 0);
   }
/* Post-Condition:  creates a 2-dimensional array that holds the image according to the image dimension */
    
/* Pre-Condition:  FrmStr() should have been called */
   void printTree(QuadNode * ptr, int indent){
      if (ptr != nullptr){
         for (int i = 0; i < indent; i++){
            cout << "     ";
         }
         cout << ptr->type << " " << ptr->level << endl;
         for (int i = 3; i >= 0; i--){
            printTree(ptr->quads[i], indent + 1);
         }
      }
   }
/* Post-Condition:  prints out the tree made by frmStr */

/* Pre-Condition:  frmStr() should have been called already so that the tree has been made
                    createImage() called
                                            */
   void printImage(QuadNode * ptr, int &imageSize)
   {
      for (int i = 0; i < imageDimension; i++)
      {
         for (int j = 0; j < imageDimension; j++)
         {
            cout << image[i][j];
         }
         cout<<endl;
      }      
   }
/* Post-Condition:  prints out the image */
    
/* Pre-Condition:  createImage() called */
   bool compareSquare(char **image1, char **image2, int width)
   {
      bool isEqual = true;
      for (int i = 0; i < width; i++)
      {
         for (int j = 0; j < width; j++)
         {
            if (image1[i][j] != image2[i][j])
            {
               return false;
            }
         }
      }
      return isEqual;
   }
/* Post-Condition:  Decides whether pointer one quadrant matches the other or not and returns a bool */
    
/* Pre-Condition:  createImage() called */
   void copySquare(char **src, char **dest, int width)
   {
      for (int i = 0; i < width; i++)
      {
         for (int j = 0; j < width; j++)
         {
            dest[i][j] = src[i][j];
         }
      }
   }
/* Post-Condition:  copies the square from source to destination */
    
/* Pre-Condition:  FrmStr() called
                                        */
   bool sameTree(QuadNode *ptr1, QuadNode *ptr2)
   {
      int n = imageDimension / pow(2, ptr1->level);
      int imageSize = pow(imageDimension, 2);

      char **image1 = new char*[n];
      char **image2 = new char*[n];
      for (int i = 0; i < n; i++)
      {
         image1[i] = new char[n];
         image2[i] = new char[n];
      }
      
      createImage(ptr1, n*n);
      copySquare(image, image1, n);

      createImage(ptr1, n*n);
      copySquare(image, image2, n);

      bool isEqual = compareSquare(image1, image2, n);

      for (int i = 0; i < n; i++)
      {
         delete[] image1[i];
         delete[] image2[i];
      }
      delete[] image1;
      delete[] image2;

      createImage(root, imageSize);
      return isEqual;
   }
/* Post-Condition:  returns true or false whether the smallest possible tree is repeating or not */
    
public:
   QuadTree() {
      image = NULL;
      root = nullptr;
      blacks = 0;
      levels = 0;
      pixelWidth = 0;
      imageDimension = 0;
   }

   void frmStr(string encodeStr){
      frmStr(root, encodeStr, 0);
   }

   void printTree(){   // prints the tree (in inorder) 
      printTree(root, 0);
   }

   void printImage(int pixels){
      createImage(root, pixels);
      printImage(root, pixels);
      // printImage(pixels, root, 0);
   }
/* Pre-Condition:  createImage() called */
   char queryTree(int row, int col)
   {
      if (!root || row > imageDimension-1 || col > imageDimension-1)
      {
         return 0;
      }
      return image[row][col];
   }   
/* Post-Condition:  constructor that initializes the tree */
    
/* Pre-Condition:  createImage() called */
   int numBlack()
   {
      for (int i = 0; i < imageDimension; i++)
      {
         for (int j = 0; j < imageDimension; j++)
         {
            if (image[i][j] == '@')
            {
               blacks++;
            }
         }
      }

      return blacks;
   }
/* Post-Condition:  calculates the total number of black pixels in the image */
    
/* Pre-Condition:  tree should have been created */
   int largestRepeat()
   {
      if (root->level == levels)
         return 0;

      if (sameTree(root->quads[0], root->quads[2]))
      {
         return (imageDimension / pow(2, root->level + 1));
      }
      else
         return 0;
   }
/* Post-Condition:  returns the number of pixels in the largest repeating sub-tree */
private:
   int levels;
   int imageDimension;
   int pixelWidth;
   int blacks;
   char **image;
};

int main(){
   QuadTree qTree;
   int imageSize;
  // int totalBlack;
   // int largestWidth;
   string encodeStr;

   cin >> imageSize;
   cin >> encodeStr; 

   qTree.frmStr(encodeStr);
   //qTree.printTree();
   qTree.printImage(imageSize);
  // cout << "Blacks: ";
    cout << qTree.numBlack() << " "; // << endl;
  // cout << "Largest Repeat: ";
    cout << qTree.largestRepeat(); // <<endl;
   return 0;
}
/*   Part 1
ibwbw
iibwbwibwbwibwbwibwbw
ibibwbwbibwbw
iibwbwbbibwbwiibwbwbbb
ibwbiiibwbwbbbibwbwbwbw
*/
/*
iiiwbwbiwbwbiwbwbiwbwbiiwbwbiwbwbiwbwbiwbwbiiwbwbiwbwbiwbwbiwbwbiiwbwbiwbwbiwbwbiwbwb
*/


/*
iiiiibbwbibbwwiwwbbibwbbiibwbwwwibwwwiibwbwwwibwwwiibwwbwiwwbbibwbbiiiwbbwibbwwiwwbbiwbbwiibbwwibwwwwiwwwbiwwiwwbbiwwbbiiwbbwwiwwbbiwbbwwwwww
@@@@@    @@@@@@
@    @   @         
@   @    @   
@@@@     @@@@
@   @    @
@    @   @
@   @    @
@@@@     @@@@@@@

@@@@@@@@@
@         @
@  @@  @@   @
@              @
@      @       @   
@      @       @
@             @ 
@   @@@@@   @
@        @
@@@@@@@@ 


iiiiwibwwbibbwbwiwibwwbibwwbibbwwiwibwwwibwwbiwwwbiwibwwwibwwbwiiibbwbibbwwibbwwibbwbiibwwwibwwbibwwbibwwwiibwwwibbwwibbwbiwwwbiibbwwibbwwibbwwiwbwbiiibwwbwibbwwiwbwwiibwwbibbwbibwwwwwwiiwibwwbibwwwwiibwwwibwwbibwwwwwwiiwiibwwbwwibwwbiibbwwibbwwwibwwbiibbwwibwwwiwwwbibbwwiiwiwbwbibwwbwiibbwwiwwwbibwwbwiibbwwwiwwwbibbwwiibwwwiwbwwibbwbwiiwibwwbibbwwibwwwiwibwwbwibbwwwwiiibbwwiwwwbibwwwwiibwwbwibbwwibbwwwwww
H   H EEEEE L     L      OOO       
H   H E     L     L     O   O      
HHHHH EEEEE L     L     O   O      
H   H E     L     L     O   O     
H   H EEEEE LLLLL LLLLL  OOO       

W   W  OOO  RRRR  L     DDDD   
W W W O   O R   R L     D   D  
W W W O   O RRRR  L     D   D  
W   W O   O R   R L     D   D
W   W  OOO  R   R LLLLL DDDD   

iiiiiibbwbibbwwibwbbibbbbiibbwwibbwwwwwiibbbbibbbbibbbbibbbbiiibbwwibbwwiwbbbwiibbbwibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiwibbbbibbbbwiiwibbbbibbbbwiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiwibbbbibbbbwiiibbbbibbbbibbbbibbbbwwiibbbbibbbbibbbbibbbbiiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbwbibwwbibbbbiibbbbibbbbibbbbibbbbiiibbbbibbbbibbbbibbbbiibbbbibwwbibwwbibbbbiibwwwibwwbibwbbwiibbbbibbbbibwwwibbwbiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiiiwwibwwbibbbbwiibbbbibwwwwibbwbiibbbbibbbbibbbbibbbbiwiwibbbbwwiibbbbibbbbibbbbibbbbiiwwbwibbbbibbbbiwbbbiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiiibbbbibbbbibbwbibbbbiibwwwiwwbwiwbbbwiiwwbwibbbbibbbbiwbbbiibbbbibwwwwibbwbiiiibwwbwwibwwbwiiwwwbwwibwbbiibbbbibbbbibbbbibbbbiwiwwibbbbwiibbbbibbbbibbbbibbbbiwibbbwiwbwwwiwiibbbwibbbbibbbbiwbwwiwibbbwiwbwwwiiwwwbwwibwbbiiibbbbibbbbibbbbibbbbiibbbbiwwwbibwbbibbbbiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiiiiibbbbibbbbibwwwibbwbiibbbbibbwbwwwwiiibbwwibbwwwwiibbwwibbwwwwiibbbbibbbbibbbbibbbbiwiwwbbibbbbiwbbbiiibbbbibbbbibbbbibbbbiibbbbibbbbibbwbibbbbiibbwbwwwiibbbbibbbbibwwwibbwwiwiwiwbbbibbbbiwbbbiibbbwibbbbibbwwwwiiiibbbbibbbbwwiibbbbibbbbibbbbibbwwiwiwbwwwwiibwbbwibwwbibbbbiiibbbbibbbbibbbbibbbbwwiibbbbibbbbibbbbibbbbiiibbbbibbbbibbbbibbbbwwiibbbbibbbbibbbbibbbbiiibbwbwwwwiwwiwwbwwwiiiiwwbbiwwbbwwiibbbbibbbbwwiibbbbiwwbbibbbbibbbbiibbbbibbbbibbbbibbbbiiibbbbibbbbiwbbwwwwiwiwbbwiwbbwibwbbiiibbbbibbbbibbbbibbbbwwiibbbbibbbwiwbbwibwwwiiibwwwibbbbibbbbwiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbiibwbbibbbbibbbbibbbbiiiibbbbibwbbwwiiwwbbiwwwbwwwiibbbbibbbbibbbbibbbbiwwiibbbbibbbbibbbbibbbbiwibbbbibbbbwiiwibbbbiwwbbwiibbbbibbbbiwwbbiwwbbiibbbbibbbbibbbbibbbbiwibbbbibbbbwiiibbbbibbbbibbbbibbbbwwiibbbbibbbbibbbbibbbbiiiiibbwwibbwwiwwbbiwwbbiwwiwwbbiwwbbwwiiwibbwwiwwbbiwwbbiibbwwibbwwiwwbbiwwbbwwwwiiiibbwwibbwwiwwbbiwwbbiibbwwwiwwbbiwwbbwwiiwiwbbwiwbbbiwwbbwwwwwwwiiiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbwwiiibbbbiwwwbibwbbibbbbiwwiwwbbiwwbbwwwwiiiwiwwbwiwbbbiwwbbiibbbbibbbbibbbbibbbbwwiiibbbbibbbbibbbbibbbbiibbbbibbbbibbbbibbbbwwwwww
hugs&kisses&hugs&kisses&hugs&kisses&hugs&kisses&hugs&kisses&
&            hugs&kisses&hugs&kisses&hu         &hugs&kisses
s&h        es&hugs&kisses&hugs&kiss                 gs&kisse
es&h      sses&hugs&kisses&hugs&k                     s&kiss
ses&      isses&hugs&kisses&hugs            &kiss      s&kis
sses      kisses&hugs&kisses&hu           ugs&kiss      s&ki
isse      &kisses&hugs&kisses&h          &hugs&kiss     gs&k
kiss      s&kisses&hugs&kisses&         es&hugs&kis     ugs&
&kis      gs&kisses&hugs&kisses        sses&hugs&k      hugs
s&ki      ugs&kisses&hugs&kisse       kisses&hugs       &hug
gs&k      hugs&kisses&hugs&kiss      s&kisses&hu        s&hu
ugs&      &hugs&kisses&hugs&kis     ugs&kisses&         es&h
hugs      s&hugs&kisses&hugs& i     hugs&kisse          ses&
&hug      es&hugs&kisses&hug  k      hugs&kis           sses
s&hu      ses&hugs&kisses&h   &       hugs&             isse
es&h      sses&hugs&kisse     s&                       &kiss
s                             gs&ki                 hugs&kis
s                             ugs&kisse         sses&hugs&ki
i             ses&h                                        k
k             sses&                                        &
&kis      gs&kisses&hug   isses&hugs      s&hugs&kisse     s
s&kis      gs&kisses&h   &kisses&hug      es&hugs&kisses   g
gs&ki      ugs&kisses&   s&kisses&hu      ses&hugs&kisses  u
ugs&ki      ugs&kisse   ugs&kisses&h      sses&hugs&kisses h
hugs&k      hugs&kiss   hugs&kisses&      isses&h gs&kisses&
&hugs&k      hugs&ki   s&hugs&kisses      kisses  ugs&kisses
s&hugs&      &hugs&k   es&hugs&kisse              hugs&kisse
es&hugs&      &hugs   sses&hugs&kiss      s&kiss  &hugs&kiss
ses&hugs      s&hug   isses&hugs&kis      gs&kiss s&hugs&kis
sses&hugs      s&h   &kisses&hugs&ki      ugs&kisses&hugs& i
isses&hug      es&   s&kisses&hugs&k      hugs&kisses&hug  k
kisses&hug      e   ugs&kisses&hugs&      &hugs&kisses&h   &
&kisses&hu          hugs&kisses&hugs      s&hugs&kisse     s
s&kisses&hu        s&hugs&kisses                           g
gs&kisses&h        es&hugs&kisse                           u
ugs&kisses&hugs&kisses&hugs&kisses&hugs&kisses&hugs&kisses&h


iiiiiwwiwbbbwiiwwbwbbbbiwbiwbwwwbiibbiwbwwwibbbibbbwwwiwiwibbwwwwwwiiiibwbbiwwbbbbiiwwbbwbbbbiiwwwiwwwbiwwiwwbwwiiwwbwbbbibiwwwbbbbibbibbibbbwiwbwwiibbwwbwwiwiiiwbwwibbbwwwiibbwbibwwwwwwwwwwiiiiwiwbbbbbbbbibibiwwbbbbbbiibbibbwbbibbwibwwwwwibbibibbwwwwibbibwwwibbwbiiiiwwbbiwwwbbbiwwwibwbbibwwibwwwbwwiiibbwwwwwwwwwwww
***********                  ***********
*****************            *****************
*********************        *********************
***********************      ***********************
************************    ************************
*************************  *************************
**************************************************
************************************************
********************************************
****************************************
**********************************
******************************
************************
********************
**************
**********
******
**

*/
