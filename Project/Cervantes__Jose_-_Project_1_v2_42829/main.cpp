/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: joseluiscervantes
 * Purpose: Jumble
 * Created on April 28, 2016, 9:32 AM
 */


// The * symbol is used to make the output nicer and easier to read. 


//System Libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

// Declared functions


//User Libraries

//Global Constants
    const int WORDS=5;
    const int LEVEL=2;
    const int SIZE=20;
//Function Prototypes

int srchArr(string [], string, int);
void selSort(int[], string[],int);
void fillArr(string[][WORDS], int, int); //fills the array with the words
void randNum(int[], int size=WORDS); // generates a random order for the word bank
void defntn (string); //Contains the defnition to the words
void scramble(string);// Scrambles the word
void plyr1(string[][WORDS], int [], int, int &attempts);  //scrambles the word
int plyrs2(string , string ); // function for 2 player mode

//Execution Begins Here!

int main(int argc, char** argv) {

//Initialize Variables

    
//Input Values
    
    //Declared variables
    int attempts(0), tempV(0), rank(0);
    //attempts = keeps track of the number of attempts
    //tempV = tempearly holds the vaalue of the returned function
    //rank = holds the position of the returned value in which position you got on the leaderboard
    
    int random[WORDS]={}; 
    //random[WORDS] = holds the random numbers that were generated to output the words a new order every time
    
    char players;
    //players = holds the value the user enters
    
    unsigned short size(0), answer(0);
    //size = for two player mode to determine if the word entered is the required length
    // answer = input
    
    bool repeat = true;
    
    
    int score[SIZE]={};
    //score[SIZE] = holds the scores of the every player thats played the game
    
    string word, hint, name;    
    string scoreNm[SIZE]={};
    string wrdBank[LEVEL][WORDS]={};
    //word = used 2 player mode to hold the word entered
    //hint = used 2 player mode to hold the hint entered
    // name = used 1 player mode to hold the name entered for the scoreboard
    //scoreNm[SIZE] = holds the name of the score board
    // wrdBank[LEVEL][WORDS]= holds the 5 words in the 2 levels
    
    ofstream out;//Output file
    ofstream out_Hscore;//Output file
    ifstream in_Hscore;//input file
    //out = outputs the score for two player mode 
    //out_Hscore = out puts the score you got to the file
    //in__Hscore = inputs the leader board from the file to the screen in order
    //open files
    out.open("score.txt",ios::app);
    out_Hscore.open("high_score.txt",ios::app);
    in_Hscore.open("high_score.txt"); 
    
        
    //Generates random numbers to switch up the order of the words
        randNum(random);
    
    //Fills the array with the word bank
        fillArr(wrdBank, WORDS,LEVEL);
    
    //Menu
    cout<<"****************************************\n";
    cout<<"**              Welcome               **\n"; 
    cout<<"**                 To                 **\n"; 
    cout<<"**               JUMBLE               **\n"; 
    cout<<"****************************************\n"<<endl; 
    
    //Rules
    cout<<"****************************************************************\n"; 
    cout<<"* RULES: This game asks he user to unscramble words            *\n";
    cout<<"* From a range of difficulty. The first level is fairly easy,  *\n";
    cout<<"* but as you progress in the game, JUMBLE, it gets pretty      *\n";
    cout<<"* complicated.                                                 *\n";
    cout<<"****************************************************************"<<endl;
    // Robert ??????
    
 
 
    
// This do statement re-runs the whole game if the user wants do    
    do{  
            //This do statement re-runs the menu for what option to enter if the player
            // enters a value that does not match the one given
            do {

                    //inputs
                    cout<<"Please enter x for one player"<<endl;
                    cout<<"Please enter y for two players"<<endl;
                    cout<<"answer: ";
                    cin>>players;
                    cout<<endl;

                    //If statement for player one is true
                    if (players == 'x' || players == 'X'){
                        
                        //calls the function where the main game happens
                            plyr1(wrdBank, random, WORDS, attempts);
                            
                            
                            cout<<"It took you "<<attempts<<" attempts to complete 1 player mode"<<endl;

                            cout<<"Please enter your first, last, or nickname name with no spaces for your score:";
                            cin>>name;
                            out_Hscore<<name<<" "<<attempts<<endl;
                            cout<<endl<<endl;
                            
                            
                            int amount = -1;


                            do{ 
                                //Fills the array's to output the updated scoreboard
                                amount++; 
                                in_Hscore>>scoreNm[amount]>>score[amount];
                                
                                //Keeps filing until the last value is zero;
                            }while(score[amount]>0);

                            //Sorts the players Score from the file from highest to lowest
                            selSort(score, scoreNm, amount);
                            
                            //Holds the returned position of the place the user got
                            rank = srchArr(scoreNm, name, amount);
                            
                            //Displays the place they reived
                            cout<<"You placed "<<rank<<" place out of "<<amount<<" Total people"<<endl;


                            //Output the whole leader boards
                            cout<<endl;
                            cout<<"Leader board for Single Player."<<endl;
                            cout <<"Rnk  Name"<<"           "<<"Attempts"<<endl;
                            for(int i=0; i<amount; i++){
                                cout<<i+1<<"    "<<scoreNm[i]<<"             "<<score[i]<<endl;
                            
                                                //If statement for player two is true      
                            } 
                            cout<<"thank you"<<endl;
                    }else if(players == 'y' || players == 'Y'){

                            cout<<"You selected 2 players."<<endl<<endl;

                            cout<<"Player one:"<<endl;
                            cout<<"Enter a word thats between the length of 4 and 8 characters"
                                    " Without player 2 knowing the word: ";

                            //Inputs for the word and hint the user enters
                            cin.ignore();
                            getline (cin, word);
                            cout << "Please enter a hint: ";
                            cin.ignore();
                            getline (cin, hint);

                            //These spaces move the screen down so when player one enters a
                            //Word player two does not see what it is.
                            cout<<endl<<endl<<endl<<endl<<endl 
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl
                                <<endl<<endl<<endl<<endl<<endl;

                            //Gets the size of the word and puts it through 
                            // the proper case depending on its length.
                            size = word.length(); 

                            //This if statement only takes in words lengths from 4 through 8
                            if (size <= 8 && size >=4){
                               tempV=plyrs2(word, hint);

                            }else{
                                cout << "You did not enter a word with 4 to 8 characters"
                                    ", make sure there's no spaces or caps." << endl;
                        }

                    // If the user fails to enter x or y
                    }else{
                        cout << "you did not enter x or y" << endl;

                }

            // This not 
            }while(!((players == 'y' || players == 'Y')|| (players == 'x' || players == 'X')));
            
                out<<endl<<endl<<"New Game"<<endl;
                out<<"2 Player mode"<<endl;
                out<<"It took you "<<tempV<<" attempts to solve the word "<<word<<endl<<endl;
                out<<"END OF GAME"<<endl<<endl;

        cout << endl;
        cout << "******Congratulations You solved the word.******" << endl << endl;

        // asks the user if they want to repeat the game  
        cout << "Please enter 1 to play this game again else type in 2 to quit: ";
        
        cin  >> answer;
        cout << endl;

    // This do statement re-runs the whole game if the user wants do          
    
    }while(repeat == answer);
     
    

    
    
//Map The Inputs to the Outputs
    
//Output the Results

    //The end

//Exit Stage Right!
    return 0;
}
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** srchArr();  ***********************************
 *Inputs
 *      none
 *Outputs
 *  
 * *n --> returns the position at which the user has placed
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
int srchArr(string *n, string answer, int size){
   bool value = false;
    // Linear search
    for (int i = 0; i < size; i++){
        if (*(n+i) == answer) {
            return i+1;}
    }
     // Returns true found or false for not found
}





//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** randNum();  ***********************************
 *Inputs
 *      none
 *Outputs
 *     none
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void selSort(int score[], string scoreNm[], int size){
    int tempV(0);
    string tempS;
    
    for(int i=0; i<size; i++)
        for(int x=i+1; x<size; x++){
            
            if(score[i] > score[x]){
                
                // Switches the scores of the leaderboard
                tempV=score[i];
                score[i]=score[x];
                score[x]=tempV;
                
                //The names also get switched with the score to retain the same position
                tempS=scoreNm[i];
                scoreNm[i]=scoreNm[x];
                scoreNm[x]=tempS;
               
                
            }
        }
    
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** fillArr();  ***********************************
 *Inputs
 *      none
 *Outputs
 * none
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void fillArr(string wrdBank[][WORDS], int words, int levels){
    ifstream in;
    
    //Fills the array with the wordbank from a file.
    in.open("word.txt");
    
    //Fills the two dimensional array with words from the file
    for(int x=0; x<levels; x++){
        for(int i=0; i<5; i++){
            in>>wrdBank[x][i];
        }
    }
}





//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** randNum();  ***********************************
 *Inputs
 *      none
 *Outputs
 *     *n --> returns the random numbers that will be used in 1 player mode
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void randNum(int n[], int size){
    int num(0);
    bool repeat;
    srand(time(0));
    
    //this for loop assigns a random number to the array
    for(int x=0; x<size; x++){
        //If a number is repeated this do statement reruns the program
        //until a new number is found
        do{
            repeat = true;
            num=rand()%size;
            //This for loop checks to see if the number assigned is repeated
            for (int i=0; i<x; i++){
                if (num == n[i]){
                    repeat=false;
                }//End of if statement
            }//End of for loop
        }while(!(repeat));  
        // if the number isn't repeated its assigned to the array
        n[x] = num;
    }//End of 1st for loop
}//End of function





//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** scramble();  ***********************************
 *Inputs
 *      none
 *Outputs
 *    unWord---> outputs unWord scrambled
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void scramble (string unWord){
    int size;
    size = unWord.length();
    
    //Scrambles the words in 1 player mode based upon their size
     if (size == 3){               
           // Word.at() scrambles the whole word and out puts it
           cout<<unWord.at(2)<<unWord.at(1)<<unWord.at(0)<<endl;
           
      }else if (size == 4){               
           // Word.at() scrambles the whole word and out puts it
           cout<<unWord.at(2)<<unWord.at(3)<<unWord.at(0)<<unWord.at(1)<<endl;
           
      }else if (size == 5){               
           // Word.at() scrambles the whole word and out puts it
           cout<<unWord.at(2)<<unWord.at(1)<<unWord.at(4)<<unWord.at(3)
               <<unWord.at(0)<<endl;
           
      }else if (size == 6){               
           // Word.at() scrambles the whole word and out puts it
          cout<<unWord.at(2)<<unWord.at(1)<<unWord.at(4)<<unWord.at(3)
              <<unWord.at(0)<<unWord.at(5)<<endl;
           
      }else if (size == 7){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(6)<<unWord.at(1)<<unWord.at(4)<<unWord.at(3)
                <<unWord.at(0)<<unWord.at(5)<<unWord.at(2)<<endl;
           
      }else if (size == 8){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(6)<<unWord.at(1)<<unWord.at(7)<<unWord.at(3)
               <<unWord.at(0)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)<<endl;
           
      }else if (size == 9){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(6)<<unWord.at(8)<<unWord.at(7)<<unWord.at(3)
               <<unWord.at(0)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)
               <<unWord.at(1)<<endl;
           
      }else if (size == 10){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(6)<<unWord.at(8)<<unWord.at(7)<<unWord.at(3)
               <<unWord.at(9)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)
               <<unWord.at(1)<<unWord.at(0)<<endl;
           
      }else if (size == 12){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(6)<<unWord.at(10)<<unWord.at(7)<<unWord.at(3)
                <<unWord.at(11)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)
                <<unWord.at(1)<<unWord.at(9)<<unWord.at(0)<<unWord.at(8)<<endl;
           
      }else if (size == 13){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(12)<<unWord.at(10)<<unWord.at(7)<<unWord.at(3)
                <<unWord.at(11)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)
                <<unWord.at(1)<<unWord.at(9)<<unWord.at(0)<<unWord.at(8)
                <<unWord.at(6)<<endl;
      }else if (size == 14){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(12)<<unWord.at(10)<<unWord.at(13)<<unWord.at(3)
                <<unWord.at(11)<<unWord.at(5)<<unWord.at(2)<<unWord.at(4)
                <<unWord.at(1)<<unWord.at(9)<<unWord.at(0)<<unWord.at(8)
                <<unWord.at(6)<<unWord.at(7)<<endl;
      }else if (size == 15){               
           // Word.at() scrambles the whole word and out puts it
            cout<<unWord.at(12)<<unWord.at(10)<<unWord.at(13)<<unWord.at(3)
                <<unWord.at(11)<<unWord.at(5)<<unWord.at(2)<<unWord.at(14)
                <<unWord.at(1)<<unWord.at(9)<<unWord.at(0)<<unWord.at(8)
                <<unWord.at(6)<<unWord.at(7)<<unWord.at(4)<<endl;
           
      }
    
}






//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** defntn();  ***********************************
 *Inputs
 *      none
 *Outputs
 *    unWord--> the hint of the word
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void defntn (string unWord){
    if(unWord == "hat"){
        
        cout<<"* HINT: I am Something you wear."<<endl;
    }else if (unWord == "double"){
        cout<<"* HINT: This is how you get an F in C++."<<endl;
    }else if (unWord == "pizza"){
        cout<<"* HINT: PAPA JOHNS."<<endl;
    }else if (unWord == "couch"){
        cout<<"* HINT: This is where you sit."<<endl;
    }else if (unWord == "kfc"){
        cout<<"* HINT: No comment."<<endl;
    }else if (unWord == "khaleesi"){
        cout<<"* HINT: Game of Thrones."<<endl;
    }else if (unWord == "government"){
        cout<<"* HINT: They are the most honest people on earth."<<endl;
    }else if (unWord == "obama"){
        cout<<"* HINT: Our current president."<<endl;
    }else if (unWord == "plagiarism"){
        cout<<"* HINT: This is another way to get an F in C++."<<endl;
    }else if (unWord == "schwarzenegger"){
        cout<<"* HINT: The Terminator."<<endl;
    }
}





//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** plyr1();  ***********************************
 *Inputs
 *      none
 *Outputs
 *   
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void plyr1(string wrdBank[][WORDS], int order[], int words, int &attempts){
// Declared variables
    string answer, unWord, hint;
    //
    //answer = takes in the user input if they want to run the code again
    //hint   = is a key word for the user if they need help
    //word1  = is the first word of the level
    
    
    

    //There are two levels this is the first for loops
    for(int i=0; i<2; i++){
        
        // Menu of level 1
        cout<<"*****************************************\n";
        cout<<"**              Level "<<i+1<<"                **\n"; 
        cout<<"**                                     **\n"; 
        cout<<"**   Each word in level "<<i+1<<" consist of   **\n"; 
        cout<<"**  of four or more words words.       **\n";
        cout<<"** As each level Progresses the word   **\n";
        cout<<"**  the word gets difficult.           **\n";
        cout<<"**                                     **\n"; 
        cout<<"** (MAKE SURE YOUR CAP LOCKS IS OFF )  **\n"; 
        cout<<"**   (ENTER LOWER CASE LETTERS ONLY)   **\n"; 
        cout<<"*****************************************\n" << endl;
        cout<<"***********************************************************"<<endl;
        cout<<"* Type in (hint) with no caps or spaces to give you a     *"<<endl;
        cout<<"* clue on what the word is.                               *"<<endl;
        cout<<"***********************************************************"<<endl;
            int x = 0;
            
            //This is the second for loops which contains 5 words per level
            for(x=0; x<5; x++){               
                unWord = wrdBank[i][order[x]];

                // This do while loop re-runs the code whenever the user enters the wrong word
                // and stops until the user enters the right word
                do {
                    // Tells the user what to enter, displays a hint, and outputs the word they 
                    // need to unscramble
                        cout<<"***********************************************************"<<endl;
                        cout<<"* Unscramble: ||"; 
                        scramble (unWord);
                        cout<<"* answer: ";
                        cin>>answer;
                        
                         // Displays the hint to the user
                           if (answer == "hint"){
                            cout<<"***********************************************************"<<endl; 
                     
                            //Function call
                            defntn (unWord); //definition of the word
                            cout<<"***********************************************************"<<endl; 
                            cout<<"* Make sure your caps lock is off and                     *"<<endl;
                            cout<<"* everything you enter is in lower case with no spaces.   *"<<endl;

                        //If the user enters an answer that doesn't match word1 then this will display  
                           }else if (!(answer == unWord)){
                            cout<<"***********************************************************"<<endl; 
                            cout<<"* TRY AGAIN."<<setw(47)<<"*" << endl;
                       }// else if bracket

                       if ((!(answer == unWord))) {
                       cout<<"*********************************************************** "<<endl;
                       cout<<endl<<endl;
                       } 

                attempts++;// keeps track of the number of attempts

                }while (!(answer == unWord)); // If the answer entered is false then the ! 
                                            // operator returns the value true and runs 
                                            // the program againr

                cout<<"***********************************************************"<<endl;
                cout<<"* CORRECT!!!!!                                            *"<<endl;
                cout<<"***********************************************************"<<endl;
                cout<<endl<<endl<<endl;
                }// end of 2nd for loop bracket
    
    }// end of 1st for loop bracket
}// End of function Statement





//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
/**************************** twoplyrs();  ***********************************
 *Inputs
 *      answer --->  inputs the word being guessed
 *Outputs
 * the menu
*/
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
int plyrs2(string word, string hint) {

    
    
    string answer;
    unsigned short size(0), attempts(0);
    
    cout << "Player 2:" << endl;
    
    
    
    size = word.length();
    
    cout<<"***********************************************************"<<endl;
    cout<<"* Type in (hint) with no caps or spaces to give you a     *"<<endl;
    cout<<"* clue on what the word is.                               *"<<endl;
    cout<<"***********************************************************"<<endl;  
    if (size == 4){
        
        //This do loop will keep running until the user has guessed player one's word
        do {

               // Tells the user what to enter, displays a hint, and outputs the word they 
               // need to unscramble
               cout<<"***********************************************************"<<endl;
               cout<<"* Unscramble: || ";
               
               // Word.at() scrambles the whole word and out puts it
               cout<<word.at(2)<<word.at(1)<<word.at(3)<<word.at(0)
                 << " ||                                *" << endl;

               cout<<"* answer: ";
               cin>>answer;


               // Displays the hint to the user
               if (answer == "hint"){
                cout<<"***********************************************************"<<endl; 
                cout<<"* HINT: "<<hint<<endl;
                cout<<"***********************************************************"<<endl; 
                cout<<"* Make sure your caps lock is off and                     *"<<endl;
                cout<<"* everything you enter is in lower case with no spaces.   *"<<endl;
                
                //If the user enters an answer that doesn't match word then this will display 
               }else if (!(answer == word)){
                cout<<"***********************************************************"<<endl; 
                cout<<"* TRY AGAIN."<<setw(47)<<"*"<<endl;
               }// else if bracket


               if ((!(answer == word))) {
               cout<<"*********************************************************** "<<endl;
               cout<<endl<<endl;
               } 
               
               attempts++; // Keep track of the number of attempts
               
        }while (!(answer == word)); // If the answer entered is false then the ! 
                                    // operator returns the value true and runs 
                                    // the program again
    
    
    //Displays the number of attempts the user needed to solve the word
    cout<<"It took you "<<attempts<<" attempts to unscramble the word."<<word<<endl;
    
    }else if(size == 5){
        
        //This do loop will keep running until the user has guessed player one's word
        do {

               // Tells the user what to enter, displays a hint, and outputs the word they 
               // need to unscramble
               cout<<"***********************************************************"<<endl;
               cout<<"* Unscramble: || ";
               
               // Word.at() scrambles the whole word and out puts it
               cout<<word.at(2)<<word.at(0)<<word.at(1)<<word.at(4)<<word.at(3)
                   <<" ||                                *"<<endl;

               cout<<"* answer: ";
               cin>>answer;


               // Displays the hint to the user
                if (answer == "hint"){
               cout<<"***********************************************************"<<endl; 
               cout<<"* HINT: "<<hint<<endl;
               cout<<"***********************************************************"<<endl; 
               cout<<"* Make sure your caps lock is off and                     *"<<endl;
               cout<<"* everything you enter is in lower case with no spaces.   *"<<endl;

               }else if (!(answer == word)){
                cout << "***********************************************************" << endl; 
                cout << "* TRY AGAIN."<<setw(47)<<"*" << endl;
               }// else if bracket


               if ((!(answer == word))) {
               cout<<"*********************************************************** "<<endl;
               cout<<endl<<endl;
               } 
            attempts++; // Keep track of the number of attempts 
            
        }while (!(answer == word));// If the answer entered is false then the ! 
                                   // operator returns the value true and runs 
                                   // the program again
    
    
    //Displays the number of attempts the user needed to solve the word
    cout<<"It took you "<<attempts<<" attempts to unscramble the word."<<word<<endl;
    
     // Out put to file score.txt

        
        
    }else if(size == 6){
        
        //This do loop will keep running until the user has guessed player one's word
        do {
               // Tells the user what to enter, displays a hint, and outputs the word they 
               // need to unscramble
               cout<<"***********************************************************"<<endl;
               cout<<"* Unscramble: || ";
               
               // Word.at() scrambles the whole word
               cout<<word.at(5)<<word.at(3)<<word.at(1)<<word.at(0)<<word.at(4)<<word.at(2)
                   <<" ||                                *"<<endl;

               cout<<"* answer: ";
               cin>>answer;


               // Displays the hint to the user
               if (answer == "hint"){
                cout<< "***********************************************************"<<endl; 
                cout<< "* HINT: "<<hint<<endl;
                cout<< "***********************************************************"<<endl; 
                cout<< "* Make sure your caps lock is off and                     *"<<endl;
                cout<< "* everything you enter is in lower case with no spaces.   *"<<endl;
                
                //If the user enters an answer that doesn't match word then this will display 
               }else if (!(answer == word)){
                cout<<"***********************************************************"<<endl; 
                cout<<"* TRY AGAIN."<<setw(47)<<"*"<<endl;
               }// else if bracket


               if ((!(answer == word))) {
               cout<<"*********************************************************** "<<endl;
               cout<<endl<<endl;
               } 
               
            attempts++; // Keep track of the number of attempts
            
        }while (!(answer == word)); // If the answer entered is false then the ! 
                                    // operator returns the value true and runs 
                                    // the program again
    
    
    //Displays the number of attempts the user needed to solve the word    
    cout<<"It took you "<<attempts<<" attempts to unscramble the word."<<word<<endl;
    
     // Out put to file score.txt

    
    }else if(size == 7){
        
        //This do loop will keep running until the user has guessed player one's word
        do {
               // Tells the user what to enter, displays a hint, and outputs the word they 
               // need to unscramble
               cout<<"***********************************************************"<<endl;
               cout<<"* Unscramble: || ";
               
               // Word.at() scrambles the whole word and out puts it
               cout<<word.at(4)<<word.at(3)<<word.at(1)<<word.at(6)
                   <<word.at(2)<<word.at(0)<<word.at(5)
                   <<" ||                                *"<<endl;
               
               cout<<"* answer: ";
               cin>>answer;


               // Displays the hint to the user
               if (answer == "hint"){
                cout<< "***********************************************************"<<endl; 
                cout<< "* HINT: "<<hint<<endl;
                cout<< "***********************************************************"<<endl; 
                cout<< "* Make sure your caps lock is off and                     *"<<endl;
                cout<< "* everything you enter is in lower case with no spaces.   *"<<endl;

               }else if (!(answer == word)){
                cout << "***********************************************************"<<endl; 
                cout << "* TRY AGAIN."<<setw(47)<<"*"<<endl;
               }// else if bracket

               if ((!(answer == word))) {
               cout<<"*********************************************************** "<<endl;
               cout<<endl<<endl;
               } 
               
            attempts++; // Keep track of the number of attempts
            
        }while (!(answer == word)); // If the answer entered is false then the ! 
                                    // operator returns the value true and runs 
                                    // the program again
    
    //Displays the number of attempts the user needed to solve the word
    cout<< "It took you " << attempts << " attempts to unscramble the word." << word << endl;
    
     // Out put to file score.txt

    
    }else if(size == 8){
        
        //This do loop will keep running until the user has guessed player one's word
        do {
                // Tells the user what to enter, displays a hint, and outputs the word they 
                // need to unscramble
                cout<<"***********************************************************"<<endl;
                cout<<"* Unscramble: || ";
                
                // Word.at() scrambles the whole word and out puts it
                cout<<word.at(5)<<word.at(3)<<word.at(2)<< word.at(0)<<word.at(7)
                    <<word.at(6)<<word.at(4)<<word.at(1)
                    <<" ||                                *"<<endl;

                cout<<"* answer: ";
                cin>>answer;

                // Displays the hint to the user
               if (answer == "hint"){
                cout<<"***********************************************************"<<endl; 
                cout<<"* HINT: "<<hint<<endl;
                cout<<"***********************************************************"<<endl;
                cout<<"* Make sure your caps lock is off and                     *"<<endl;
                cout<<"* everything you enter is in lower case with no spaces.   *"<<endl;
                
                //If the user enters an answer that doesn't match word then this will display 
               }else if (!(answer == word)){
                cout<<"***********************************************************"<<endl; 
                cout<<"* TRY AGAIN."<<setw(47)<<"*"<<endl;
               }// else if bracket

               if ((!(answer == word))) {
               cout<<"*********************************************************** "<<endl;
               cout<<endl<<endl;
               }
                
            attempts++; // Keep track of the number of attempts
            
        }while (!(answer == word)); // If the answer entered is false then the ! 
                                    // operator returns the value true and runs 
                                    // the program again
    
    //Displays the number of attempts the user needed to solve the word
    cout<<"It took you "<<attempts<<" attempts to unscramble the word."<<word<<endl;
    
     // Out put to file score.txt

    }// end of else if(size == 8) statement   

    return attempts;
}// end of function