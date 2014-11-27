#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

// Helper function prototypes
string strToUpper(string);
string fileContentsToStr(string);
string fileContentsToStrPipeDelimited(string);
string removeWhitespaceFromStr(string);


int main ()
{

  // Get file contents of Genome file
  string fileContents = fileContentsToStr("Genome");

  // Set file contents of Genome equal to var genomeDNA, get size, and turn upper
  string genomeDNA = fileContents;
  int genomeDNASize = genomeDNA.length();
  genomeDNA = strToUpper(genomeDNA);



  // Transcribe DNA to messenger RNA molecule
  string genomeRNA = "";

   for (int i = 0; i < genomeDNASize; i++)
   {
     if (genomeDNA[i] == 'A')
     {
         genomeRNA += 'U';
     }
     else if (genomeDNA[i] == 'T') 
     {
        genomeRNA += 'A';
     }
     else if (genomeDNA[i] == 'C') 
     {
        genomeRNA += 'G';
     }
     else if (genomeDNA[i] == 'G') 
     {
        genomeRNA += 'C';
     }
     else 
     {
        cout << "\nUnidentifiable DNA nucleotide present\n";
        // Break if statement
        return 0;
     }
   }

   cout << "Printing Genome RNA Transcribed: " << genomeRNA;



   // Read lookup file to str
   string CTableStr = fileContentsToStrPipeDelimited("CTable");

   // Dump all the empty spaces from CTableStr which may mess up our splits/finds
   string CTableStrScrubbed = removeWhitespaceFromStr(CTableStr);

   cout << "\nPrinting CTable String Scrubbed: " << CTableStrScrubbed;



   // Count number of ':' or ',' in string which represent possible amino acid indexes
   int countAminoAcidCodons = 0;
   for (int i = 0; i < CTableStrScrubbed.length(); i++) 
   {
      if (CTableStrScrubbed[i] == ':' || CTableStrScrubbed[i] == ',') 
      {
          countAminoAcidCodons++;
      }
   }

   cout << "\nPrinting Number of Amino Acid Codons: " << countAminoAcidCodons;



   // Populate character array which will hold amino acids in indexed order
   char * aminoAcidsArray = new char[countAminoAcidCodons];
   int trueCounter = 0;

   for (int i = 0; i < CTableStrScrubbed.length(); i++) 
   {
      // start new amino acid
      if (CTableStrScrubbed[i] == ':') 
      {
          aminoAcidsArray[trueCounter] = CTableStrScrubbed[i-1];
          trueCounter++;
      }
      // copy previous amino acid
      else if (CTableStrScrubbed[i] == ',') 
      {
          aminoAcidsArray[trueCounter] = aminoAcidsArray[trueCounter-1];
          trueCounter++;
      } 
   }

   cout << "\nPrinting Amino Acids Array Indices: ";

   for (int i = 0; i < countAminoAcidCodons; i++) 
   {
      cout << aminoAcidsArray[i] << ",";
   }



   // Populate string array which will hold codons in indexed order
   string * codonsArray = new string[countAminoAcidCodons];
   trueCounter = 0;
   string str;

   for (int i = 0; i < (CTableStrScrubbed.length()-1); i++) 
   {
      if (CTableStrScrubbed[i+1] == ':' || CTableStrScrubbed[i] == ',' || CTableStrScrubbed[i] == ':')
      {
          // you've hit a delimiter, not a codon; skip it
      }
      
      else if (CTableStrScrubbed[i+1] == ',' || CTableStrScrubbed[i+1] == '|')
      {
          // you've just passed a codon, trail back and copy it
          str = "";
          str += CTableStrScrubbed[i-2];
          str += CTableStrScrubbed[i-1];
          str += CTableStrScrubbed[i];
      
          codonsArray[trueCounter] = str;
          trueCounter++;          
      } 
   }

   cout << "\nPrinting codons array in indexed order: ";

   for (int i = 0; i < countAminoAcidCodons; i++) 
   {
      cout << codonsArray[i] << ",";
   }

   
   // Populate string array which will hold ONLY STOP codons in indexed order

   // First, count number of stop codons that exist
   bool captureStopCodonFlag = 0;
   int stopCodonsCount = 0;

   for (int i = 0; i < (CTableStrScrubbed.length()); i++) 
   {
      if (CTableStrScrubbed[i] == ':' && CTableStrScrubbed[i-1] == 'P' && CTableStrScrubbed[i-2] == 'O' && CTableStrScrubbed[i-3] == 'T' && CTableStrScrubbed[i-4] == 'S') 
      {
          // you've reached the stop codon segment; start capturing STOP codons
          captureStopCodonFlag = 1;
      }

      if (captureStopCodonFlag == 1) 
      {
          if (CTableStrScrubbed[i] == ',' || CTableStrScrubbed[i] == '|') 
          {
              // you've just passed a stop codon, increment counter
              stopCodonsCount++;
          }
      }
   }

   cout << "\nNumber of Stop Codons: " << stopCodonsCount;

   // Second, reset captureStopCodonFlag and populate stop codon array
   captureStopCodonFlag = 0;
   int stopCondonsCounter = 0;
   string * stopCodonsArray = new string[stopCodonsCount];
   
   for (int i = 0; i < (CTableStrScrubbed.length()); i++) 
   {
      if (CTableStrScrubbed[i] == ':' && CTableStrScrubbed[i-1] == 'P' && CTableStrScrubbed[i-2] == 'O' && CTableStrScrubbed[i-3] == 'T' && CTableStrScrubbed[i-4] == 'S') 
      {
          // you've reached the stop codon segment; start capturing STOP codons
          captureStopCodonFlag = 1;
      }

      if (captureStopCodonFlag == 1) 
      {
          if (CTableStrScrubbed[i] == ',' || CTableStrScrubbed[i] == '|') 
          {
              // empty string and capture the codon you just passed
              str = "";
              str += CTableStrScrubbed[i-3];
              str += CTableStrScrubbed[i-2];
              str += CTableStrScrubbed[i-1];
              stopCodonsArray[stopCondonsCounter] = str;
              stopCondonsCounter++;
          }
      }
   }

   cout << "\nPrinting stop codons: ";
   for (int i = 0; i < stopCodonsCount; i++) 
   {
      cout << stopCodonsArray[i] << ",";
   }



   // Replace amino acids array corresponding to stop codons with a newline
   // Iterate through the 64 codons and for those that == STOP codon, replace the amino acid with a newline
   for (int i = 0; i < countAminoAcidCodons; i++) 
   {
      for (int j = 0; j < stopCodonsCount; j++) 
      {
          if (codonsArray[i] == stopCodonsArray[j])
          {
              aminoAcidsArray[i] = '\n';
          }
      }
   }

   cout << "\nPrinting scrubbed amino acid array w/ newlines for STOP: ";
   for (int i = 0; i < countAminoAcidCodons; i ++) 
   {
      cout << aminoAcidsArray[i] << ",";
   }


   // Time to decode RNA
   int genomeRNAcount = genomeRNA.length();
   int i = 0;
   int aaIndex = 0;
   int * aaTranscodedIndices = new int[genomeRNAcount/3];


   while (i < genomeRNAcount) 
   {
      str = "";
      str += genomeRNA[i]; 
      str += genomeRNA[i+1]; 
      str += genomeRNA[i+2];

      // insert corresponding amino acid
      for (int j = 0; j < countAminoAcidCodons; j++) 
      {
          if (str == codonsArray[j]) 
          {
              aaIndex = j;
          }
      }
      aaTranscodedIndices[i/3] = aaIndex;
      i += 3;
   }

   // Open file for writing
   ofstream AminoAcidSequences;
   AminoAcidSequences.open("AminoAcidSequences.txt");

   cout << "\nPrinting final amino acid sequences: \n";
   // Traverse through transcoded indices
   for (int i = 0; i < genomeRNAcount/3; i++) 
   {
      // print to console and file for debugging
      cout << aminoAcidsArray[aaTranscodedIndices[i]];
      AminoAcidSequences << aminoAcidsArray[aaTranscodedIndices[i]];
   }
   AminoAcidSequences.close();

   cout << "\nFile output to AminoAcidSequences.txt completed\n";
   //cin.ignore();

   return 0;
}



// Helper functions
string strToUpper(string str) 
{
    int size = str.length();
    string strUpper = "";
    for (int i = 0; i < size; i++)
    {
        strUpper += toupper(str[i]);
    }
    return strUpper;
}

string fileContentsToStr(string fileName)
{
  string line;
  string lineAccumulated = "";
  ifstream myfile(fileName.c_str());

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      lineAccumulated += line;
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
  return lineAccumulated;
}

string fileContentsToStrPipeDelimited(string fileName)
{
  string line;
  string lineAccumulated = "";
  ifstream myfile(fileName.c_str());

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      lineAccumulated += line + "|";
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
  return lineAccumulated;
}

string removeWhitespaceFromStr(string dirtyString) 
{
   string scrubbedString = "";
   for (int i = 0; i < dirtyString.length(); i++) 
   {
      if (dirtyString[i] == ' ') 
      {
        // do nothing
      }
      else 
      {
        // concatenante
        scrubbedString += dirtyString[i];
      }
   }
   return scrubbedString;
}