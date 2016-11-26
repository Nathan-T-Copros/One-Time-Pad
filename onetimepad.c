#include <stdio.h>
	

	//constant defining the maximum char input size
	#define MAX 2048
	

	//Protoypes 
	int readMessage(char message[MAX]);
	int readKey(char key[MAX]);
	unsigned char rotate(unsigned char character, int count);
	int bits(unsigned char character);
	void chain(char key[MAX], int length);
	

	int main()
	{
	       //Declare variables to hold the message and the key
		char message[MAX], key[MAX];
	

		//Stores the length of the message and the key 
		int messageLength = readMessage(message);
		int keyLength = readKey(key);
	

		//Makes sure that the key’s length does not exceed the message’s length
		if(keyLength >= messageLength) 
			keyLength = messageLength;
		else
		{	//If key is shorter, repeat it as many times needed to get to the same length as the message 
			int i;
			for(i = 0; keyLength < messageLength; ++i)
				key[keyLength++] = key[i];
		}
	       
              //chains the key
		chain(key, keyLength);
		int i;
	

		//XORs each element in the key character array with that of the message char array.
		for(i = 0; i < messageLength; ++i)
			putchar(key[i] ^ message[i]);
	

	}
	//Function for getting the length of the actual message.
	int readMessage(char message[MAX])
	{
		int c, messageLength = 0;
		
		//Loops which will read up until the deMAXer.
		while((c = getchar()) != 255)
			//Stores no more than 2048 characters.
			if(messageLength < MAX)
				message[messageLength++] = c;
		return messageLength;
	}
	

	//Function for getting the length of the key.
	int readKey(char key[MAX])
	{
		int c, keyLength = 0;
		//Counts until the MAX or the end of the file is reached.
		while((c = getchar()) != EOF && keyLength < MAX)
			key[keyLength++] = c;
		return keyLength;
	}
	

	//Function for rotating the least significant bits.
	unsigned char rotate(unsigned char character, int count)
	{
		return (character >> count | character << 7 - count) & 0x7F;
	}
	

	//Function that counts the number of 1 bits. 
	int bits(unsigned char character)
	{
		int bitCount = 0;
		while(character)
		{
//Adds one to bitCount if character is one
			bitCount += character & 1; 
			character >>= 1;
		}
		return bitCount;
	}
	

	//Function for chaining.
	void chain(char key[MAX], int length)
	{
		int i;
		char prev = key[length - 1];
		int sum = prev % length;
		for(i = 0; i < length; ++i)
		{
			//Chains the key.
			key[i] = rotate(key[i] ^ key[sum], bits(prev));	
	

			//Keeps the running sum of character values.
			sum = (sum + key[i]) % length;
			prev = key[i];
		}
	}

