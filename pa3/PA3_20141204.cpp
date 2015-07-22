#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Function prototypes
string fileContentsToStrNLDelimited(string fileName);
void printHangman(int guessCount);

int main() 
{
  // Generate pseudo random seed based on time
  srand(time(NULL)); 

  // Start printing the game
  cout << "***Hangman***";
  cout << "\n";

  // Enter loop for game
  char playAgainInput = 'y';
  while (playAgainInput == 'y') 
  {
    cout << "\n";
    cout << "Select a difficulty:";
    cout << "\n";
    cout << "[1]Easy [2]Medium [3]Hard";
    cout << "\n";

    int difficultyLevel;
    cin >> difficultyLevel;

    // String to hold unscrubbed file contents from file
    string fileContents;

    if (difficultyLevel == 1) 
    {
      fileContents = fileContentsToStrNLDelimited("easy.txt");
      //cout << "File contents: " << fileContents;
    }
    else if (difficultyLevel == 2) 
    {
      fileContents = fileContentsToStrNLDelimited("medium.txt");
      //cout << "File contents: " << fileContents;
    }
    else if (difficultyLevel == 3) 
    {
      fileContents = fileContentsToStrNLDelimited("hard.txt");
      //cout << "File contents: " << fileContents;
    }
    else
    {
      //pass
    }


    // Get number of space occurrences which will be used to split fileContents str
    int countWords = 0;
    for (int i = 0; i < fileContents.size(); i++) 
    {
      if (fileContents[i] == ' ')
      {
        countWords++;
      }
    }
    //cout << "\n";
    //cout << "Number of spaces in string: " << countWords;


    // Populate word bank array using stringstream to tokenize on space
    string * wordsArray = new string[countWords];
    int i = 0;
    stringstream ssin(fileContents);
    while (ssin.good() && i < countWords) 
    {
      ssin >> wordsArray[i];
      ++i;
    }
    //cout << "\n";
    //cout << "Word bank array: ";
    for (int i = 0; i < countWords; i++) 
    {
      //cout << wordsArray[i] << ",";
    }

    // Generate a random number from 0 to countWords to pick a word to use and store
    int random = rand();
    int randomIndex = random % countWords;
    string randomWord = wordsArray[randomIndex];
    string letterGuess;
    string currentState= "";
    int guessCounter = 1;
    bool incrementGuessCounterFlag = 0;

    cout << "\n";
    cout << "Random word is: " << randomWord;
    cout << "\n";

    for (int i = 0; i < randomWord.length(); i++) 
    {
      currentState += "_";
    }

    while (currentState != randomWord) 
    {
      cout << "\n";
      cout << "\n";
      if (incrementGuessCounterFlag == 1) 
      {
        guessCounter++;
        printHangman(guessCounter);
      }
      else if (incrementGuessCounterFlag == 0)
      {
        printHangman(guessCounter);
      }
      else 
      {
        // pass
      }

      cout << "Your letters:" << currentState;
      cout << "\n";
      cout << "Your guess: ";
      cin >> letterGuess;

      incrementGuessCounterFlag = 1;
      for (int i = 0; i < randomWord.length(); i++) 
      {
        if (randomWord[i] == letterGuess[0]) 
        {
          currentState[i] = letterGuess[0];
          incrementGuessCounterFlag = 0;
        }
        else if (randomWord[i] == '_') 
        {
          currentState[i] = '_';
        }
        else 
        {
          // pass (print letters guessed correctly earlier)
        }
      }


      if (currentState == randomWord) 
      {
        cout << "Congratulations! You guessed the word: " << currentState;
        cout << "\n";
        cout << "Play again?(y/n)";
        cin >> playAgainInput;
        if (playAgainInput == 'n')
        {
          break;
        }
        guessCounter = 0;
        break;
      }
      else if (guessCounter >= 13) 
      {
        cout << "YOU LOSE! The word was: " << randomWord;
        cout << "\n";
        cout << "Play again?(y/n)";
        cin >> playAgainInput;
      if (playAgainInput == 'n')
      {
        break;
      }
        guessCounter = 0;
        break;
      }

    }
  }

//  cin.ignore();
  return 0;
}



string fileContentsToStrNLDelimited(string fileName)
{
  string line;
  string lineAccumulated = "";
  ifstream myfile(fileName.c_str());

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      lineAccumulated += line + " ";
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
  return lineAccumulated;
}

void printHangman(int guessCount) 
{
  if (guessCount == 1) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 2) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|       (" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 3) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|       ( )" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 4) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 5) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 6) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|        |" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 7) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 8) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 9) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|        |" << "\n" << "|" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 10) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|        |" << "\n" << "|       /" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 11) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|        |" << "\n" << "|       / \\" << "\n" << "|" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 12) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|        |" << "\n" << "|       / \\" << "\n" << "|      /" << "\n" << "________________" << "\n";
  }
  else if (guessCount == 13) 
  {
    cout << "---------" << "\n" << "|        |" << "\n" << "|      \\( )/" << "\n" << "|       \\|/" << "\n" << "|        |" << "\n" << "|       / \\" << "\n" << "|      /   \\" << "\n" << "________________" << "\n";
  }
}
