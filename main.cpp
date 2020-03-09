
#define  CATCH_CONFIG_RUNNER
#include  "catch.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "DSString.h"


using namespace std;


// helper functions
void get_lower(char*);
bool isSubString(char* str, char* sub_str);
bool way_to_sort(DSString& lhs, DSString& rhs);


// command line arguments to run the program
// ./a.out stop-word-list.txt dev-train-data.csv dev-train-target.csv dev-test-data.csv dev-test-target.csv output01.txt

int main(int argc, char **argv) {

    // If pass less than 5 arguments in the terminal , run the test.
    // Else, run the program.
    // (5 input files +  1 output file + ./a.out) usually we will pass 7 args in terminal.
    if(argc < 10) {
        Catch::Session().run();
        return 0;
    }


    // vector<DSString> words_list;

    // words_list.push_back(DSString("zlfred"));
    // words_list.push_back(DSString("blfred"));
    // words_list.push_back(DSString("clfred"));
    // words_list.push_back(DSString("alfred"));

    // for (int i = 0; i < words_list.size(); i += 1) {
    //     cout << words_list.at(i).getData() << endl;
    // }

    // cout << endl << "Sorting...." << endl << endl;

    // sort(words_list.begin(), words_list.end(), way_to_sort);


    //  for (int i = 0; i < words_list.size(); i += 1) {
    //     cout << words_list.at(i).getData() << endl;
    // }





    // Reading stop words
    char stop_word_list_file[50] = "stop-word-list.txt";

    ifstream my_stop_word_list_ifs(argv[1]);

    if (!my_stop_word_list_ifs.is_open()) {
        cout << "Unable to open file: " << stop_word_list_file << endl;
        return -1;
    }


    vector<DSString> stop_word_list;

    char line_stop_word[1000];


    while (!my_stop_word_list_ifs.eof()) {

        my_stop_word_list_ifs.getline(line_stop_word, 100, '\n');

        stop_word_list.push_back(line_stop_word);

        cout << line_stop_word << endl;

    }

    my_stop_word_list_ifs.close();





    cout << endl << endl;

    // train input file names
    char train_data_file[50] = "dev-train-data.csv";
    char train_target_file[50] = "dev-train-target.csv";

    // input file objects
    ifstream my_train_data_ifs(argv[2]);
    ifstream my_train_target_ifs(argv[3]);

    // input filename validation
    if (!my_train_data_ifs.is_open()) {
        cout << "Unable to open file: " << train_data_file << endl;
        return -1;
    }

    if (!my_train_target_ifs.is_open()) {
        cout << "Unable to open file: " << train_target_file << endl;
        return -1;
    }


    // A vector of DSStrings, each DSString represents a unique word from the tweets
    vector<DSString> words_list;

    char line_train_data[1500];
    char line_train_target[1500];



    // (buffer, stream_size, delimiter)
    my_train_data_ifs.getline(line_train_data, 1000, '\n');            // to skip the first row
    my_train_target_ifs.getline(line_train_target, 1000, '\n');        // to skip the first row


    int row_num = 0;
    // Read data from both files
    while (!my_train_data_ifs.eof() && !my_train_target_ifs.eof()) {

        // read the first line from the file and store it in the char array "line_train_data"
        my_train_data_ifs.getline(line_train_data, 1500, '\n');

        row_num += 1;
        cout << "row_num: " << row_num << "  training file.................................................................." << endl;
        // convert the line to lowercase
        get_lower(line_train_data);


        // read the actual first line from the other file and store it in the char array "line_train_target"
        my_train_target_ifs.getline(line_train_target, 1500, '\n');

        // find the sentiment for this line first, from the "train_target_file" (0 or 4)
        // ex. 7,0,1692856516
        // it will return a pointer to the first "," in the line
        char* comma = strstr(line_train_target, ",");

        // dereference the next pointer to get the sentiment of that line
        // positive = ‘4’ or negative = ‘0’
        char sentiment = *(comma + 1);



        // Returns first token
        char* token = strtok(line_train_data, ",");  // 0,2177110313,afail,Getting Ready to start another busy week - lots of work to do today

        // A variable to store the last token in a line, which is the tweet
        char* tweet;

        // Tokenize the line
        while (token != nullptr) {

            tweet = token;
            token = strtok(nullptr, ",");
        }

        // The last token is the tweet
        // Tokenize the tweet again into individual words
        // token2 is the single word we want to process
        char* token2 = strtok(tweet, " ?,.-!:;\"()Â®š¿Ã±¯•ª†°Š²¤µ");


        while (token2 != nullptr) {

            bool word_found = false;
            bool is_stop_word = false;

            // check if token2 is a stop word first
            for (int i = 0; i < stop_word_list.size(); i += 1) {
                if (strcmp(token2, stop_word_list.at(i).getData()) == 0) {
                    is_stop_word = true;
                    //cout << "stop word: " << stop_word_list.at(i).getData() << endl;  // debug purpose
                    break;
                }

            }


            if (!is_stop_word) {

                // iterate through the vector
                for (int i = 0; i < words_list.size(); i += 1) {

                    // if already exists, just increment the pos or neg count of that object

                    // if ( binary_search( words_list.begin(), words_list.end(), words_list.at(i), way_to_sort) ) {
                    //     word_found = true;
                    //     cout << "binary search found word" << endl;
                    if (strcmp(token2, words_list.at(i).getData()) == 0) {   // strcmp() returns 0 if both c-strings are equal, otherwise > 0 or < 0
                        
                        word_found = true;

                        if (sentiment == '4') {
                            words_list.at(i).increment_pos_count();
                            //words_list.at(i).print();
                        }
                        else {
                            words_list.at(i).increment_neg_count();
                            //words_list.at(i).print();
                        }
                    }

                }

                // the word doesn't already exist, create a new object, push back, increment pos or neg count
                if (!word_found) {
                    words_list.push_back(DSString(token2));

                    if (sentiment == '4') {
                        words_list.at(words_list.size() - 1).increment_pos_count();
                        //words_list.at(words_list.size() - 1).print();
                    }
                    else {
                        words_list.at(words_list.size() - 1).increment_neg_count();
                        //words_list.at(words_list.size() - 1).print();
                    }
                }

            }


            // Sort the vector
            // The third optional parameter is used when sorting a vector of custom type objects
            // sort(words_list.begin(), words_list.end(), way_to_sort);
            // for (int i = 0; i < words_list.size(); i += 1) {
            //     cout << words_list.at(i).getData() << endl;
            // }


            // assign the next word in the line to token2, process again
            token2 = strtok(nullptr, " ?,.-!:;\"()Â®š¿Ã±¯•ª†°Š²¤µ");

        }

        if (row_num == 15000) {
            break;
        }

    }


    my_train_data_ifs.close();
    my_train_target_ifs.close();


    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;



    // Calculate the pos and neg percentages of each word
    // Print out all information
    for (int i = 0; i < words_list.size(); i += 1) {

        words_list.at(i).set_pos_pct();
        words_list.at(i).set_neg_pct();

        words_list.at(i).print();
        // cout << "pos_pct: " << words_list.at(i).get_pos_pct() << "%" << endl;
        // cout << "neg_pct: " << words_list.at(i).get_neg_pct() << "%" << endl << endl;
    }



    // Keep only the high pos_pct and high neg_pct words in a separate vector
    vector<DSString> good_words_list;

    for (int i = 0; i < words_list.size(); i += 1) {

        if (words_list.at(i).get_pos_pct() >= 70) {
            words_list.at(i).set_sentiment('4');
            good_words_list.push_back(words_list.at(i));
        }

        if (words_list.at(i).get_neg_pct() >= 70) {
            words_list.at(i).set_sentiment('0');
            good_words_list.push_back(words_list.at(i));
        }
    }


    cout << "printing the good words list......................................................" << endl << endl;


    for (int i = 0; i < good_words_list.size(); i += 1) {
        good_words_list.at(i).print();
        cout << "pos_pct: " << good_words_list.at(i).get_pos_pct() << "%" << endl;
        cout << "neg_pct: " << good_words_list.at(i).get_neg_pct() << "%" << endl << endl;
    }







    //==========================================================================================================================



    // SECOND PART
    // (predict the sentiment of each tweet in "dev-test-data.csv", then compare the result with the answer in "dev-test-target.csv")

    // see if find substrings will work, if result is not accurate, try compare word for word


    // test input file names
    char test_data_file[50] = "dev-test-data.csv";
    char test_target_file[50] = "dev-test-target.csv";

    // input file objects
    ifstream my_test_data_ifs(argv[4]);
    ifstream my_test_target_ifs(argv[5]);

    ofstream my_output_ifs(argv[6]);


    // input filename validation
    if (!my_test_data_ifs.is_open()) {
        cout << "Unable to open file: " << test_data_file << endl;
        return -1;
    }

    if (!my_test_target_ifs.is_open()) {
        cout << "Unable to open file: " << test_target_file << endl;
        return -1;
    }



    row_num = 0;

    double num_tweets = 0;
    double num_right_tweets = 0;

    vector<DSString> wrong_tweet_list;



    char line_test_data[1500];
    char line_test_target[1500];

    // (buffer, stream_size, delimiter)
    my_test_data_ifs.getline(line_test_data, 1000, '\n');            // to skip the first row
    my_test_target_ifs.getline(line_test_target, 1000, '\n');        // to skip the first row


    while (!my_test_data_ifs.eof() && !my_test_target_ifs.eof()) {

        // read the first line from the file and store it in the char array "line_train_data"
        my_test_data_ifs.getline(line_test_data, 1500, '\n');

        num_tweets += 1;

        row_num += 1;
        cout << "row_num: " << row_num << "  testing file............................................................" << endl;
        // convert the line to lowercase
        get_lower(line_test_data);


        // read the actual first line from the other file and store it in the char array "line_train_target"
        my_test_target_ifs.getline(line_test_target, 1500, '\n');

        // find the sentiment for this line first, from the "test_target_file" (0 or 4)
        // ex. 7,0,1692856516
        // it will return a pointer to the first "," in the line
        char* comma = strstr(line_test_target, ",");

        // dereference the next pointer to get the sentiment of that line
        // positive = ‘4’ or negative = ‘0’
        char sentiment = *(comma + 1);

        char* tweet_id = comma + 3;






        // Returns first token
        char* token = strtok(line_test_data, ",");  // 0,2177110313,afail,Getting Ready to start another busy week - lots of work to do today

        // A variable to store the last token in a line, which is the tweet
        char* tweet;

        // Tokenize the line
        while (token != nullptr) {

            tweet = token;
            token = strtok(nullptr, ",");
        }


        // compare the tweet with every good word in the vector
        for (int i = 0; i < good_words_list.size(); i += 1) {
            if (isSubString(tweet, good_words_list.at(i).getData())) {
                if (good_words_list.at(i).get_sentiment() == sentiment) {
                    num_right_tweets += 1;
                    break;
                }
                else {
                    wrong_tweet_list.push_back(tweet_id);
                    break;
                }
            }

        }




    }

    // display the statistics
    cout << endl;
    cout << "num_tweets: " << num_tweets << endl;
    cout << "num_right_tweets: " << num_right_tweets << endl;
    cout << "Accuracy: " <<  setprecision(3) << num_right_tweets / num_tweets << endl;
    cout << endl;


    my_output_ifs << setprecision(3) << num_right_tweets / num_tweets << endl;

    // print and write to output.txt the IDs of the tweets my algorithm incorrectly classified.
    for (int i = 0; i < wrong_tweet_list.size(); i += 1) {
        cout << wrong_tweet_list.at(i).getData() << endl;
        my_output_ifs << wrong_tweet_list.at(i).getData() << endl;
    }




    my_test_data_ifs.close();
    my_test_target_ifs.close();
    my_output_ifs.close();


    return 0;
}

// Final run results (Feb 10, 2020  8:45pm)
// num_tweets: 144000
// num_right_tweets: 90178
// Accuracy: 0.626






// This functions takes a char array and lowercase every letter
void get_lower(char* cha) {

    for (int i = 0; cha[i] != 0; i += 1) {

        if ((cha[i] >= 'A') && (cha[i] <= 'Z')){       // Ascii table. A = 65, Z = 90, a = 97, z = 122.
            cha[i] = cha[i] - 'A' + 'a';
        }

    }
}

// This function returns true if the second parameter is a substring of the first parameter  
bool isSubString(char* str, char* sub_str) {

    // strstr() returns a pointer to the first occurrence of sub_str in str, or a null pointer if str2 is not part of str1.
    if (strstr(str, sub_str) != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// We need this function to define how to sort the vector. We will pass this function into the
// third parameter and it will tell it to sort descendingly.
bool way_to_sort(DSString& lhs, DSString& rhs) {
    return lhs.getData() < rhs.getData();
}













// In C++, stream classes support line-oriented functions, getline() and write() to
// perform input and output functions respectively.