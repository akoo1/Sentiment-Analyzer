//
// Created by Alfred on 2/7/20.
//

#include <iostream>
#include <cstring>

#include "DSString.h"

using namespace std;


// default constructor
DSString::DSString() {

    data = nullptr;
}


// parameterized constructor
DSString::DSString(char* new_data) {

    if (new_data != nullptr) {
        data = new char[strlen(new_data) + 1];   // add 1 space for the null terminator
        strcpy(data, new_data);  // copies str2 over to str1. Deep copy
    }
    else {
        data = nullptr;
    }
}


// destructor
DSString::~DSString() {
    delete[] data;
}


// copy constructor
DSString::DSString(const DSString& rhs) {

    if (rhs.data != nullptr) {
        data = new char[strlen(rhs.data) + 1];
        strcpy(data, rhs.data);
    }
    else {
        data = nullptr;
    }

    pos_count = rhs.pos_count;
    neg_count = rhs.neg_count;

    pos_pct = rhs.pos_pct;
    neg_pct = rhs.neg_pct;

    sentiment = rhs.sentiment;

}
// reference: https://stackoverflow.com/questions/57731678/how-do-implement-the-copy-constructor-for-my-custom-c-class




// copy assignment operator
DSString& DSString::operator=(const DSString& rhs) {

    // avoid self-copy
    if (this != &rhs) {

        // destructor
        delete[] data;

        // copy constructor
        if (rhs.data != nullptr) {
            data = new char[strlen(rhs.data) + 1];
            strcpy(data, rhs.data);

        }
        else {
            data = nullptr;
        }
    }


    return *this;
}


//================================================================================================================================


bool DSString::operator<=(const DSString& rhs) const{

    if (strcmp(this->data, rhs.data) < 0) {
        return true;
    }
    else if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator>=(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) > 0) {
        return true;
    }
    else if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator<(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) < 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator>(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) > 0) {
        return true;
    }
    else {
        return false;
    }
}


bool DSString::operator==(const DSString& rhs) const {

    if (strcmp(this->data, rhs.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool DSString::operator==(const char* rhs) const {

    if (strcmp(this->data, rhs) == 0) {
        return true;
    }
    else {
        return false;
    }
}






// Another copy assignment operator
DSString& DSString::operator=(const char* new_data) {

    // avoid self-copy
    if (this->data != new_data) {

        // destructor
        delete[] data;

        // copy constructor
        if (new_data != nullptr) {
            data = new char[strlen(new_data) + 1];
            strcpy(data, new_data);

        }
        else {
            data = nullptr;
        }
    }


    return *this;
}




DSString DSString::substring(int start, int num_chars) {

    // input validation
    if (start >= 0 && num_chars > 0) {
        // if index exceeds the length of data, then just include all the chars after starting index
        if ((start + num_chars) > strlen(data)) {
            num_chars = strlen(data) - start;
        }

        char* temp = new char[num_chars + 1];   // add 1 space for the null terminator
        memcpy(temp, data + start, num_chars);

        temp[num_chars] = '\0';    // append the null terminator

        DSString substr(temp);

        delete [] temp;

        return substr;
    }

    // for invalid inputs, return an empty DSString
    return DSString();
}
// reference: https://stackoverflow.com/questions/57751384/what-is-wrong-with-this-substring-function






// bool DSString::constains(char* sub_str) {

// 	// strstr() returns a pointer to the first occurrence of sub_str in str, or a null pointer if sub_str is not part of str.
// 	if (strstr(data, sub_str) != nullptr) {
// 		return true;
// 	}
// 	else {
// 		return false;
// 	}
// }


char* DSString::getData() {
    return data;
}



int DSString::getLength() {
    return strlen(data);
}



bool DSString::isEmpty() {
    if (data == nullptr) {
        return true;
    }
    else {
        return false;
    }
}


void DSString::print() {
    cout << data << endl << "pos_count: " << pos_count << endl << "neg_count: " << neg_count << endl;
    cout << sentiment << endl;
}





//============================================================================================================================




void DSString::increment_pos_count() {
    pos_count += 1;
}

void DSString::increment_neg_count() {
    neg_count += 1;
}



void DSString::set_pos_pct() {
    pos_pct = pos_count / (pos_count + neg_count) * 100;
}


void DSString::set_neg_pct() {
    neg_pct = neg_count / (pos_count + neg_count) * 100;
}


double DSString::get_pos_pct() {

    return pos_pct;
}


double DSString::get_neg_pct() {

    return neg_pct;
}


void DSString::set_sentiment(char s) {
    sentiment = s;
}


char DSString::get_sentiment() {
    return sentiment;
}















