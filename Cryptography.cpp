/*
This is Deepak Kumar's Cryptographic Algorithm which can withstand Quantum Computer's onslaught.
This is a simple algorithm which takes advantage of Diffie Hellman Key Exchange Algorithm to begin with.
Initially communicate with a known user, who have a declared Public Key Machine B.
With a new user nonce private key,communicate with Machine B, using Diffie Hellman Key Exchange Algorithm
and create a new Session Key.
DK Algorithm is used to create a session key. This session key identifies a user Machine B, for communication.
This session key is a symmetric key which is held by Machine A and Machine B both.
We will get into the implementation of this DK Cryptographic Algorithm
*/
#include <iostream>
#include <ctime>
#include <set>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define ARRAYSIZE 10   // Array Size
#define MAXASCIILEN 3  // Maximum Length of a ASCII Character

using namespace std;

int main()
{
	/* This is the Session Symmetric Key after getting form Diffie Hellman Key exchange as before.
	It has to be fed manually here for this simulation*/
	string SessionKey;

	/* This holds the ASCII value of every Text character, one by one, to be fed in this DK Algorithm*/
	int AsciiDigitInputText = 0;

	/* Seed for Random number to be generated and sent from Machine B to Machine A*/
	srand((unsigned) time(0));

	/* Random Number which will be generated from Machine B to be sent to Machine A, for every transaction*/
	int MacBRandomNumber = 0;

	/* Random Number which will be received by Machine A, for every transaction*/
	int MacARandomNumber = 0;

	/*This is the Text which will be sent by Machine A, at the beginning to Machine B*/
	string EncryptText;

	/*This is the Text which will be received by Machine B, in the end from Machine A*/
	string DecryptedText;

	/*This is length of EncryptText, that will be sent from Machine A to Machine B*/
	int TextLength = 0;

	/*Intermediate Value computed during Machine A calculations*/
	int MacAInter = 0;

	/*Intermediate Value computed during Machine B calculations*/
	int MacBInter = 0;

	/* Intermediate Random Number generated for calculating Jumbled[] values*/
	int GenRandom = 0;

	/* Input Value present in the position of Machine A MacAKeys[i].
		position here is MacARandomNumber. MacAInput is used to calculate next MacAKeys[i+1]*/
	int MacAInput = 0;

	/* Input Value present in the position of Machine B MacBKeys[i].
		position here is MacBRandomNumber. MacBInput is used to calculate next MacBKeys[i+1]*/
	int MacBInput = 0;

	/* It holds the digits in every ASCII character, sent from Machine A to Machine B.
		This is digit by which actual data transfer takes place  */
	int Position = 0;

	/* This is the Match digit between Jumbled[i] and MacBKeys[i+1]
		Match contains the Position, digit by which actual data transfer takes place*/
	int Match = 0;

	/*This vector contains ASCII Value digits of every character received by Machine B*/
	vector<int> OutputDigit;

	/* LoopAgain transports the MacAKeys[3] to the next input text character MacAkeys[0] to again loop for next character*/
	int* const LoopAgain = new int[ARRAYSIZE];

	/* Checks Whether Last Digit of ASCII Value of every Character comes.
	To Enter Last elements of LoopAgain to MacAKey[0]*/
	bool LastDigitASCII = false;
	
	/*This receives the Text that has to be transmitted from Machine A to Machine B
	As, there is a problem of Stack Overflow, This Program may terminate abruptly.
	Let's try with One or Two Characters alone*/
	cout<<"Enter the text to be Encrypted and transmitted[ One or Two Characters ] :";
	cin>>EncryptText;

	/* Calculating the Length of the Text to be sent from Machine A to Machine B */
	TextLength = EncryptText.length();

	/*This is a intermediate vector v used to calculate Jumbled[]*/
	vector<int> v[MAXASCIILEN*TextLength];

	/*This contains character array of SessionKey*/
	char* SessionKeyChar = new char[ARRAYSIZE];
	
	int Option = 0;
	cout<<"Session Key contains Unique Decimal Number from [0-9]"<<endl<<endl;
	cout<<"Type Your Own or Use Default Session Key"<<endl;
	cout<<"Option 1 for your Own Key"<<endl;
	cout<<"Option 2 for Default Key"<<endl;
	cout<<"Enter Your Option :";
	cin>>Option;
	
	if(Option == 1)
	{
		cout<<"Enter the 10 Digit Session Key Value : ";
		cin>>SessionKey;
	}
	else
	{
		SessionKey = "0192837465";
		cout<<"Default Session Key :"<<SessionKey<<endl;
	}
	
	/* Initialize the Loop, which transfers MacBKeys[3] to next MacAKey[0]*/
	for(int count = 0; count<ARRAYSIZE; count++)
		*(LoopAgain + count) = 0;

	for(int TextDigit = 0; TextDigit<TextLength ; TextDigit++ )
	{
		//cout<<endl<<"-----------Reached beginning of first loop--------"<<endl;
		
		/*MacAKeys Stores the Array of Machine A Keys */
		int* const MacAKeys = new int[MAXASCIILEN*ARRAYSIZE];
		
		/*MacBKeys Stores the Array of Machine B Keys */
		int* const MacBKeys = new int[MAXASCIILEN*ARRAYSIZE];

		/*InputValues contains ASCII value of every character, input one at a time from EncryptText 
		Example 'A' which is 065*/
		int* const InputValues = new int[MAXASCIILEN];  
	
		/*Holds the Jumbled Array*/
		int* const Jumbled = new int[MAXASCIILEN*ARRAYSIZE];

		/*Initializing Machine A, Machine B and Jumbled Keys*/
		for(int count = 0; count<(MAXASCIILEN*ARRAYSIZE) ; count++)
		{
			*(MacAKeys + count) = 0;
			*(MacBKeys + count) = 0;
			*(Jumbled + count) = 0;
		}
		
		/*Initializing InputValues, which has the ASCII Value of Character to be sent*/
		for(int count = 0; count<MAXASCIILEN; count++)
			*(InputValues + count) = 0;
		

		/*Initialize the MacAKeys[0] and MacBKeys[0] with the Session Key.
		Do it for First character*/
		if(TextDigit == 0)
		{
			cout<<endl<<"Initial Key Value :";
			strcpy(SessionKeyChar, SessionKey.c_str());
			for(int j=0;j<ARRAYSIZE;j++)
			{
				int InputNumChar = (int) (SessionKeyChar[j] - '0');
				*(MacAKeys+ 0*ARRAYSIZE + j) = InputNumChar;
				*(MacBKeys+ 0*ARRAYSIZE + j) = InputNumChar;
				cout<<InputNumChar;
			}
		}/*Initialize the MacAKeys[0] and MacBKeys[0] with the LoopAgain Key.
		Do it at the end of every character*/
		else if(LastDigitASCII == true)
		{
			cout<<endl<<"Loop Again Machine A and B Keys for next Iteration :";
			for(int j=0;j<ARRAYSIZE;j++)
			{
				*(MacAKeys+ 0*ARRAYSIZE + j) = *(LoopAgain + j);
				*(MacBKeys+ 0*ARRAYSIZE + j) = *(LoopAgain + j);
				cout<<*(MacAKeys+ 0*ARRAYSIZE + j);
			}
			LastDigitASCII = false;
		}

		cout<<endl<<"Entered MacA Key is :";
		for(int j=0;j<ARRAYSIZE;j++)
			cout<<*(MacAKeys+ 0*ARRAYSIZE + j);

		/*ASCII value of every Input Text Character
		Example 065 for 'A'*/
		AsciiDigitInputText = int(EncryptText[TextDigit]);

		/*This is the Digit which needs to be preserved, when creating Jumbled[i] */
		int ValueOfMacANotchanges = 0;

		/*Take each digit from AsciiDigitInputText and assign it to InputValues[] 
		Example InputValues[] will hold 065 of Character 'A'*/
		for(int i=MAXASCIILEN-1; i>=0; i--)
		{
			*(InputValues+i) = (AsciiDigitInputText % 10);
			AsciiDigitInputText = (AsciiDigitInputText/10) ;
		}
		AsciiDigitInputText = 0;
		
		/*This Prints the InputValues[].
		Example InputValues[] will hold 065 of Character 'A'*/
		cout<<endl<<"Entered Input Value :";
		for(int InputCount=0; InputCount<MAXASCIILEN; InputCount++)
			cout<<*(InputValues + InputCount);
		cout<<endl;

		/*Iterate through every ASCII Digit of a Character and perform the Communication.
		Communication takes place from Machine A to Machine B */
		for(int i=0; i<MAXASCIILEN; i++)
		{
			/* Machine B geneartes a Random Number (MacBRandomNumber) and send it to Machine A*/
			MacBRandomNumber = (rand() % 10);
			cout<<endl<<"Machine B sends Random Number : "<< MacBRandomNumber <<" to Machine A"<<endl;
			MacARandomNumber = MacBRandomNumber;

			cout<<endl<<"---------------------------------------------------------"<<endl;
			//Machine A Calculation
			cout<<"Machine A Calculations"<<endl;
			cout<<"---------------------------------------------------------"<<endl;
			
			/*Assign the Input Value of selected Random Number (MacARandomNumber)
			 from Machine A Keys (MacAKeys) to MacAInput for further Calculation*/
			MacAInput = *(MacAKeys + i*ARRAYSIZE + MacARandomNumber);

			cout<< "Machine A Encrypt using digit : "<<MacAInput<<" from position : "<<MacARandomNumber<<endl;

			//Perform the initial permutation of Machine A at every loop cycle
			for(int j=0;j<=9;j++)
			{
				MacAInter = (MacAInput + j)% 10;
				
				//MacAKeys[i+1][MacAKeys[i][MacAInter]]= ((MacAInter + MacAInput) % 10);
				*(MacAKeys + (i+1)*ARRAYSIZE + *(MacAKeys + i*ARRAYSIZE + MacAInter)) = ((MacAInter + MacAInput) % 10);
			}
			cout<<endl;

			/*Print Machine A values of Iteration i*/
			cout<<"Machine A Key for iteration ["<<i<<"] = ";
			for(int k=0; k<=9; k++)
			{
				//cout<<MacAKeys[i+1][k];
				cout<<*(MacAKeys + i*ARRAYSIZE + k);
			}
			cout<<endl;

			/*Print the Result of Permutation of MacAKeys [i+1]*/
			cout<<"Machine A Key for iteration ["<<i+1<<"] = ";
			for(int k=0; k<=9; k++)
			{
				//cout<<MacAKeys[i+1][k];
				cout<<*(MacAKeys + (i+1)*ARRAYSIZE + k);
			}
			cout<<endl;

			/* Assign the InputValues[i] to Position for transmiting the Data Digit in the Position */
			Position = *(InputValues+i); // InputValues[] = (0,6,5)
			
			/*This is the Value of the Data Digit which does not change,
			while creating the Jumbled Array*/
			ValueOfMacANotchanges = *(MacAKeys + (i+1)*ARRAYSIZE + Position);
			v[i].push_back(ValueOfMacANotchanges);

			cout<<endl<<"The Digit in MacAKeys which does not change :"<<ValueOfMacANotchanges<<endl;	
			//cout<<"Position =: "<<Position<<endl;
		
			bool Found = false;
			
			/*Calculate Jumbled from the MacAKeys[i+1], by changing every array digit,
			except the ValueOfMacANotchanges in Position*/
			for(int l=0; l<=9; l++)
			{
				if(l==Position)
					*(Jumbled + i*ARRAYSIZE + Position) = ValueOfMacANotchanges;
				else
				{
					Found = false;
					GenRandom = (rand() % 10 );

					for(int Count=0; Count<v[i].size() ; Count++)
						if(v[i][Count] == GenRandom)
							Found = true;

					//Check whether GenRandom and digit in MacAKeys[i+1][] matches
					if(*(MacAKeys + (i+1)*ARRAYSIZE + l) == GenRandom)
						Found = true;

					if(Found == false)
					{
						//Append the chosen number to the Vector v and Jumbled[]
						*(Jumbled +i*ARRAYSIZE + l)= GenRandom;
						v[i].push_back(GenRandom);
					}
					if(Found == true)
						l--;
				}
				if((l==9) && (*(MacAKeys + (i+1)*ARRAYSIZE + 9)==GenRandom))
                {
					l=0;
					v[i].clear();
					v[i].push_back(ValueOfMacANotchanges);
                }
			}
			v[i].clear();

			cout<<"Preserve the encrypted Digit in Position :";
			cout<<Position<<endl;
			
			cout<<"--------------------------------------------------------"<<endl;
			cout<<"Jumbled Array Send to Machine B : ";
			for(int k=0; k<=9; k++)
			{
				if(k==Position)
					cout<<"[";
				cout<<*(Jumbled + i*ARRAYSIZE + k);
				if(k==Position)
					cout<<"]";
			}
			
			cout<<endl<<"--------------------------------------------------------"<<endl;
			//Machine B Calculations
			cout<<endl<<"Machine B Calculations"<<endl;
			cout<<"--------------------------------------------------------"<<endl;
			
			//Get the Input Value of same Random Number as Machine A
			//MacBInput = MacBKeys[i][MacBRandomNumber];
			MacBInput = *(MacBKeys + i*ARRAYSIZE + MacBRandomNumber);

			cout<< "Machine B Permutation using digit :"<<MacBInput<<" in position :"<<MacBRandomNumber<<endl<<endl;

			/*Print Machine A values of Iteration i*/
			cout<<"Machine B Key for Iteration ["<<i<<"] = ";
			for(int j=0; j<=9; j++)
				//cout<<MacBKeys[i][j];
				cout<<*(MacBKeys + i*ARRAYSIZE + j);
			cout<<endl;

			//Perform the initial permutation of Machine B same as A
			for(int j=0;j<=9;j++)
			{
				MacBInter = (MacBInput + j)% 10;
				//MacBKeys[i+1][MacBKeys[i][MacBInter]]= ((MacBInter + MacBInput) % 10);
				*(MacBKeys+ (i+1)*ARRAYSIZE + *(MacBKeys + i*ARRAYSIZE +MacBInter)) = ((MacBInter + MacBInput) % 10);

			}

			/*Print the Result of Permutation of MacBKeys [i+1]*/			
			cout<<"Machine B Key for iteration ["<<i+1<<"] = ";
			for(int k=0; k<=9; k++)
			{
				//cout<<MacBKeys[i+1][k];
				cout<<*(MacBKeys + (i+1)*ARRAYSIZE + k);
			}

			Match = 0;
			cout<<endl<<endl<<"Compare the Jumbled Array with Machine B Key"<<endl;

			for(int m=0;m<=9;m++)
			{
				int MacBMatch = *(MacBKeys + (i+1)*ARRAYSIZE + m);
				int JumbledMatch = *(Jumbled + i*ARRAYSIZE + m);
				if(MacBMatch == JumbledMatch)
				{
					Match = m;
					cout<<"Match Found :"<<Match<<endl;
				}
			}
			//v[i].clear();

			//cout<<"Data sent from Machine A to Machine B is :"<<Match<<endl;
			cout<<"Digit Received :"<<Match<<endl;
			OutputDigit.push_back(Match);

			if(i== (MAXASCIILEN - 1))
			{
				//cout<<endl<<"Reached End of MaxAscci value 3"<<endl<<" Looped again Loop is:";
				for(int k = 0; k<ARRAYSIZE ;k++)
				{

					*(LoopAgain + k) = *(MacBKeys + (i+1)*ARRAYSIZE + k);
					//cout<<*(LoopAgain + k);
				}
				//goto end;
			}
			cout<<endl;
		if(i == (MAXASCIILEN - 1))
			LastDigitASCII = true;

		}
//After i loop
		int Output = 0;
		cout<<endl<<"OutputDigit is :";
		for(int j=0 ; j<MAXASCIILEN; j++)
		{
			cout<<OutputDigit[j];
			Output = Output * 10;
    		Output = Output + OutputDigit[j];
		}
		OutputDigit.clear();

		cout<<endl<<"Character sent from Machine A to Machine B Output is ASCII : "<<Output<<" Character : "<< char(Output);
		DecryptedText.push_back(char(Output));

/*		delete[] MacAKeys;
		delete[] MacBKeys;
		delete[] InputValues;
		delete[] Jumbled;
			//cout<<endl<<"Output Text is :"<<DecryptedText;
*/	}
//	delete[] LoopAgain;
	cout<<endl<<"Output Text is :"<<DecryptedText;
	//TextDigit ends before braces
	return 0;
}

