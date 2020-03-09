#ifndef DSSTRING_H
#define DSSTRING_H



class DSString {


private:
    char* data;

    // increment as we parse each word for a tweet
    double pos_count = 0;
    double neg_count = 0;

    //double total_occurence = 0;

    // calcualte and return the percentages in the end
    double pos_pct;
    double neg_pct;

    // will be used to determine whether each tweet in the "test-data-file" is negative or positive
    char sentiment;




public:

    DSString();      								// default constructor
    DSString(char* new_data);  						// parameterized constructor

    ~DSString();									// destructor
    DSString(const DSString& rhs);				// copy constructor
    DSString& operator=(const DSString& rhs);	// copy assignment operator


    DSString& operator=(const char* new_data);

    // my projects works good in github action, no issues, but when I added in the catch test cases, I’m having errors.
    // Adding "const" at the end of each overloaded operator fixed it the errors

    bool operator<=(const DSString& rhs) const;            // overloaded less than or equal to operator
    bool operator>=(const DSString& rhs) const;            // overloaded greater than or equal to operator
    bool operator<(const DSString& rhs) const;             // overloaded less than operator
    bool operator>(const DSString& rhs) const;             // overloaded greater than operator
    bool operator==(const DSString& rhs) const;            // overloaded equal to operator
    bool operator==(const char* rhs) const;                // overloaded equal to operator

    // DSString operator+(const DSString& oriObj);     // ? why not return the reference of the object
    // DSString& operator+=(const DSString& oriObj);   // ?


    char* getData();
    double get_pos_pct();
    double get_neg_pct();
    char get_sentiment();

    void print();



    void increment_pos_count();
    void increment_neg_count();

    void set_pos_pct();
    void set_neg_pct();

    void set_sentiment(char s);


    // unused functions
    DSString substring(int start, int num_chars);
    bool constains(DSString& sub_str);
    int getLength();
    bool isEmpty();

};




#endif










