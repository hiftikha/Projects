//
//  main.cpp
//  DesignPatternsProject1
//
//  Created by Haroon Iftikhar on 10/16/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * Abstract base product.
 */
class Widget {
public:
    virtual void draw() = 0;
};

/**
 * Concrete word family 1.
 */
class Word90Button : public Widget {
public:
    void draw() { cout << "Button Word90 \n"; }
};
class Word90Panel : public Widget {
public:
    void draw() { cout << "Panel Word90 \n"; }
};
class Word90TextBox : public Widget {
public:
    void draw() { cout << "TextBox Word90 \n"; }
};

/**
 * Concrete word family 2.
 */
class Word00Button : public Widget {
public:
    void draw() { cout << "Button Word00 \n"; }
};
class Word00Panel : public Widget {
public:
    void draw() { cout << "Panel Word00 \n"; }
};
class Word00TextBox : public Widget {
public:
    void draw() { cout << "TextBox Word00 \n"; }
};

/**
 * Concrete word family 3.
 */
class Word10Button : public Widget {
public:
    void draw() { cout << "Button Word10 \n"; }
};
class Word10Panel : public Widget {
public:
    void draw() { cout << "Panel Word10 \n"; }
};
class Word10TextBox : public Widget {
public:
    void draw() { cout << "TextBox Word10 \n"; }
};

/**
 * Concrete word family 4.
 */
class Word17Button : public Widget {
public:
    void draw() { cout << "Button Word17 \n"; }
};
class Word17Panel : public Widget {
public:
    void draw() { cout << "Panel Word17 \n"; }
};
class Word17TextBox : public Widget {
public:
    void draw() { cout << "TextBox Word17 \n"; }
};

/**
 * Abstract factory defines methods to create all
 * related products.
 */
class Factory {
public:
    virtual Widget *create_button() = 0;
    virtual Widget *create_panel() = 0;
    virtual Widget *create_textbox() = 0;
};


class Word90Factory : public Factory {
private:
    Word90Factory(){}
    static Word90Factory *firstInstance;
    static Word90Factory *secondInstance;
public:
    static Word90Factory *getInstance(){
        if (firstInstance == nullptr) {
            firstInstance = new Word90Factory();
            return firstInstance;
        }
        else if(secondInstance == nullptr){
            secondInstance = new Word90Factory();
            return secondInstance;
        }
        cout << "Cannot create more than 2 instances of Word90" << endl;
        return nullptr;
    }
    Widget *create_button() {
        return new Word90Button;
    }
    Widget *create_panel() {
        return new Word90Panel;
    }
    Widget *create_textbox() {
        return new Word90TextBox;
    }
};

Word90Factory *Word90Factory::firstInstance = nullptr;
Word90Factory *Word90Factory::secondInstance = nullptr;

class Word00Factory : public Factory {
private:
    Word00Factory(){}
    static Word00Factory *firstInstance;
    static Word00Factory *secondInstance;
public:
    static Word00Factory *getInstance(){
        if (firstInstance == nullptr) {
            firstInstance = new Word00Factory();
            return firstInstance;
        }
        else if(secondInstance == nullptr){
            secondInstance = new Word00Factory();
            return secondInstance;
        }
        cout << "Cannot create more than 2 instances of Word00" << endl;
        return nullptr;
    }
    Widget *create_button() {
        return new Word00Button;
    }
    Widget *create_panel() {
        return new Word00Panel;
    }
    Widget *create_textbox() {
        return new Word00TextBox;
    }
};

Word00Factory *Word00Factory::firstInstance = nullptr;
Word00Factory *Word00Factory::secondInstance = nullptr;

class Word10Factory : public Factory {
private:
    Word10Factory(){}
    static Word10Factory *firstInstance;
    static Word10Factory *secondInstance;
public:
    static Word10Factory *getInstance(){
        if (firstInstance == nullptr) {
            firstInstance = new Word10Factory();
            return firstInstance;
        }
        else if(secondInstance == nullptr){
            secondInstance = new Word10Factory();
            return secondInstance;
        }
        cout << "Cannot create more than 2 instances of Word10" << endl;
        return nullptr;
    }
    Widget *create_button() {
        return new Word10Button;
    }
    Widget *create_panel() {
        return new Word10Panel;
    }
    Widget *create_textbox() {
        return new Word10TextBox;
    }
};

Word10Factory *Word10Factory::firstInstance = nullptr;
Word10Factory *Word10Factory::secondInstance = nullptr;

class Word17Factory : public Factory {
private:
    Word17Factory(){}
    static Word17Factory *firstInstance;
    static Word17Factory *secondInstance;
public:
    static Word17Factory *getInstance(){
        if (firstInstance == nullptr) {
            firstInstance = new Word17Factory();
            return firstInstance;
        }
        else if(secondInstance == nullptr){
            secondInstance = new Word17Factory();
            return secondInstance;
        }
        cout << "Cannot create more than 2 instances of Word17" << endl;
        return nullptr;
    }
    Widget *create_button() {
        return new Word17Button;
    }
    Widget *create_panel() {
        return new Word17Panel;
    }
    Widget *create_textbox() {
        return new Word17TextBox;
    }
};

Word17Factory *Word17Factory::firstInstance = nullptr;
Word17Factory *Word17Factory::secondInstance = nullptr;

class Client {
private:
    Factory *factory;
    
public:
    Client(Factory *f) {
        factory = f;
    }
    
    void draw() {
        if(factory)
        {
            Widget *b = factory->create_button();
            Widget *p = factory->create_panel();
            Widget *t = factory->create_textbox();
            b->draw();
            p->draw();
            t->draw();
        }
    }
};


int main() {
    ifstream WordReader;
    WordReader.open("data.txt");
    string version;
    Factory *factory = nullptr;
    
    if (!WordReader) {
        cout << "Unable to open file";
    }
    
    while (!WordReader.eof()) {
        getline(WordReader,version);
        
        if(version == "Word90"){
            factory = Word90Factory::getInstance();
        }
        if (version == "Word00") {
            factory = Word00Factory::getInstance();
        }
        if (version == "Word10") {
            factory = Word10Factory::getInstance();
        }
        if (version == "Word17") {
            factory = Word17Factory::getInstance();
        }
            Client *c = new Client(factory);
            c->draw();
    }
    
    WordReader.close();
    

}
