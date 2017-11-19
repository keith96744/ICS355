#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "md5.h"
#define SALT_SIZE 100
//keith Nakamatsu

using namespace std;

		//this class will have information about currency such as the description, UDS dollar armount (using a golden standard), blah blah 

class Currency
{
   friend ostream &operator<<(ostream &, const Currency &);

   public:
      string CountryCode;
      string Description;
      float USD_DollarAmount;

      Currency();
      Currency(string x, string y, float z);
      Currency(const Currency &);
      ~Currency(){};
      Currency &operator=(const Currency &rhs);
      int operator==(const Currency &rhs) const;
      int operator<(const Currency &rhs) const;
     
};

Currency::Currency()   // Constructor
{
   CountryCode = "NaN";
   USD_DollarAmount = 0.0f;
   Description = "NaN";
   
}

Currency::Currency(string x , string y, float z)
{
	CountryCode = x;
	Description = y;
	USD_DollarAmount = z;
}

Currency::Currency(const Currency &copyin)   // Copy constructor to handle pass by value.
{                             
   CountryCode = copyin.CountryCode;
   Description = copyin.Description;
   USD_DollarAmount = copyin.USD_DollarAmount;
}

ostream &operator<<(ostream &output, const Currency &CurrencyObj)
{
   output << CurrencyObj.CountryCode << ' ' << CurrencyObj.USD_DollarAmount << ' ' << CurrencyObj.Description << endl;
   return output;
}

Currency& Currency::operator=(const Currency &rhs)
{
   this->CountryCode = rhs.CountryCode;
   this->Description = rhs.Description;
   this->USD_DollarAmount = rhs.USD_DollarAmount;
   return *this;
}

int Currency::operator==(const Currency &rhs) const
{
   if( this->CountryCode != rhs.CountryCode) return 0;
   if( this->Description != rhs.Description) return 0;
   if( this->USD_DollarAmount != rhs.USD_DollarAmount) return 0;
   return 1;
}

int Currency::operator<(const Currency &rhs) const
{
   if( this->CountryCode == rhs.CountryCode && this->Description == rhs.Description && this->USD_DollarAmount < rhs.USD_DollarAmount) return 1;
   if( this->CountryCode == rhs.CountryCode && this->Description < rhs.Description) return 1;
   if( this->CountryCode < rhs.CountryCode ) return 1;
   return 0;
}




	// this class will keep track and house all of the currency objects 
	class Currency_Collection{


		public:
			map<string, Currency> Map;

			Currency Obj;

			Currency_Collection(){
				//cout << "Currency constructor" << endl;

				ifstream file( "con.txt", ios::in );
				    string part1;
				    float num1;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				   
				    while( file >> part1 >> num1  )
				    {
				        
				        Obj.CountryCode = part1;
				        Obj.USD_DollarAmount = num1;
				        Map[part1] = Obj;
				       // i++;

				     //   cout<< "i: "<<i << endl;
				    }

				   // cout << "Part1: "<<part1 << "\n" << endl;
				    //cout << "Num1: "<<num1 << "\n" << endl;

				    file.close();

			}
			

			float Load(string search) // locate a currency and return that value
			{
				map<string, Currency>::iterator ii;
				if(Map.find(search) == Map.end())
				{
					return 123456789.987654321;
				}
				else
				{
				ii= Map.find(search);

				//cout << "loading value: "<<(*ii).second.USD_DollarAmount << endl;

				return (*ii).second.USD_DollarAmount;

			 	}

			}






			void Save() // save things to the map this will be used import a large file with all the different curriences , change so that it can individuall add things via the interface
			{


			
				ifstream file( "con.txt", ios::in );
				    string part1;
				    float num1;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				    int i = 0;
				    while( file >> part1 >> num1  )
				    {
				        
				        Obj.CountryCode = part1;
				        Obj.USD_DollarAmount = num1;
				        Map[part1] = Obj;
				     

				     //   cout<< "i: "<<i << endl;
				    }

				   // cout << "Part1: "<<part1 << "\n" << endl;
				    //cout << "Num1: "<<num1 << "\n" << endl;

				    file.close();


				



			}
			void Dump()
			{


				for( map<string, Currency>::iterator ii=Map.begin(); ii!=Map.end(); ++ii)
				   {
				       cout << (*ii).first << ": " << (*ii).second << endl;
				   }
			
	


				
			} // print a list of all the curriencies 
		
			

	};



	// this class will have everything dealing with the users account, banking functions
	class Money{


		
			


		public:



			float value;
			string CurrentCountry;
			string CurrentC;
			Currency_Collection Denomination;
			// constructor
			// default constructor

			Money()
			{
				//value = 100;
				//CurrentC = "USD";

			}
			Money(float valuez, string cc)
			{
				value = valuez;
				CurrentC = cc;
				CurrentCountry = cc;
			}

			void ADD(float amount){
				value = value + amount;
				
				cout << "made it to money class: adding: "<< amount << endl;
			}
			void SUB(float amount){
				value = value - amount;
			}
			void View()
			{
				//cout << "This is the curriencies avaliable for conversion" << endl;
				//Denomination.Dump();

				cout << "Account balance: " << CurrentCountry << " "<< value << endl;
			}
			void ConvertTo(string z)
			{	
				float temp=0;
					// this function was working but now its not working

				 temp = Denomination.Load(z);
			
			// assuming no errors  need to check for errors later 
				 if(z != "USD" || "AUS" || "GPB")
				 {
				 		// error checking implement this
				 }

				 if(CurrentCountry == "USD")
				 {
				 	value = value*temp;
				 	CurrentCountry = z;

		

				 }
				 else 
				 {
				 	cout << "Converting: "<< CurrentCountry << " to: " << z << endl;

				 	float temp2;
				 	temp2 = (value/Denomination.Load(CurrentCountry))*Denomination.Load(z);
				 
				 	value = temp2;
		
				 	
				 	value = temp2;
				 	CurrentC = z;
				 	CurrentCountry = z;

				 }
				
					
				 
			}
			

	};







	//  this class will have informtion about different users, such as Name, (maybe password implementaiton later so only a ceratin person can access his or her acocunt)
	class User{


		public:
			
			Money Balance; 
			
			string UserName;
			string PassWord; // this will be a hashed password 
			int permissions;
			string NaCl;
			int operator<(const User &rhs) const;
			
			
			
			void User_setup (string UN, float val, string countryCode, string pW,int perm, string salt)
			{
				UserName = UN;
				PassWord = pW;
				Balance.value = val;
				Balance.CurrentCountry = countryCode;
				permissions = perm;
				this->NaCl = salt;
			}
			
			User &operator=(const User &rhs);

		
			void Display()
			{
				cout << "Account: " << UserName << endl;
				cout << "Password: " << PassWord << endl;
				Balance.View();

			}
			void add(float a)
			{
				Balance.ADD(a);
				cout << "adding this amount: " << a << endl;
			}
			void sub(float b)
			{
				Balance.SUB(b);
			}
			
			void ConvertingTime(string countrycode)
			{
				Balance.ConvertTo(countrycode);
			}

			bool checkPermissions()
			{
				if(permissions = 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		
		


	};



User& User::operator=(const User &rhs)
{
   this->UserName = rhs.UserName;
   this->Balance.value = rhs.Balance.value;
   this->Balance.CurrentCountry = rhs.Balance.CurrentCountry;
   this->PassWord = rhs.PassWord;
   this->permissions = rhs.permissions;
   this->NaCl = rhs.NaCl;
   
   
   return *this;
}



int User::operator<(const User &rhs) const
{
   if( this->UserName == rhs.UserName && this->Balance.value == rhs.Balance.value && this->Balance.CurrentCountry < rhs.Balance.CurrentCountry) return 1;
   if( this->UserName == rhs.UserName && this->Balance.value < rhs.Balance.value) return 1;
   if( this->UserName < rhs.UserName ) return 1;
   return 0;
}


	// this class will house and keep track of all the users
	class User_Collection
	{
		public:

			map<int, User> UMap;

			User Account;
			int positionOfAccount;
			
			const char alphanum[100] ={'0','1','2','3','4','5','6','7','8','9','!','@','#','$','%','^','&','*','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		
			
			int stringLength = sizeof(alphanum) - 1;
			string salt[SALT_SIZE];

			User_Collection()
			{
				//cout << "User_Collection constructor" << endl;

				ifstream file( "UserCollection.txt", ios::in );
				    string getName;
				    float getBalance;
				    string getCountryCode;
				    string getPassWord;
				    int getPermissions;
				    string getSalt;
				   //cout << "made it here 1"<< endl; 
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				   int i = 0;
				   
				   
				   
				//   cout << "made it here 2"<< endl; 
				   
				   
				   
				   
				    while( file >> getName >> getBalance >> getCountryCode >> getPassWord >> getPermissions >> getSalt   )
				    {
				     
				      
				      Account.User_setup(getName, getBalance, getCountryCode, getPassWord,getPermissions,getSalt);

				        UMap[i] = Account;

					
				       i++;


				       
				    }
				  
				    file.close();

			}
			
			
			void Dump()// total dump of all users and account information 
			{
				cout << "Displaying all user accounts \n\n";
				for(int x=0; x < UMap.size(); x++)
				{
					Account = UMap[x];
					cout << x +1<< ". ";
					Account.Display();
				}
			
			}
			void UpdatePositionBasedOnName(string accountName)
			{
				positionOfAccount = 0;
				
				for(int x=0; x < UMap.size(); x++)
				{
					Account = UMap[x];
					
					
				if(Account.UserName == accountName)	
				{	
					
				//	cout << "Account at position: " << positionOfAccount << endl;
					positionOfAccount=x;
					return;
					
				}
			
				positionOfAccount=x;
				
				}
				
			}
			
			void view ()
			{
				Account.Display();
			}
			void ConvertMoneyTo(string c)
			{
				Account.ConvertingTime(c);
			}
			
			
			void TransferTo(string from,string to, float amount)
			{	 // from = source account name
				 // to = destination account name
				 string temp_countrycode1, temp_countrycode2;
				 // once again using the CheckIfAccountExists to select account
				 
				 cout<< "Transfering money from " << from << " to " << to << endl;
				 cout << "Transfering " << amount << endl;
				 
				 CheckIfAccountExists(from); 
				 
				 temp_countrycode1 = Account.Balance.CurrentCountry;
				 
				 CheckIfAccountExists(to);
				 
				 temp_countrycode2 = Account.Balance.CurrentCountry;
				 
				 if(temp_countrycode1==temp_countrycode2)
				 {
				 	//cout << "there the same" << endl;
					  CheckIfAccountExists(from); 
				 
				 
					 if(Account.Balance.value >= amount)
					 {
					 	
					 	CheckIfAccountExists(from); 
					 	UpdatePositionBasedOnName(from);
						 SubMoney(amount);
						 
						 
						 CheckIfAccountExists(to);
						 UpdatePositionBasedOnName(to);
						 AddMoney(amount);
						 
						 WriteToFile();
						 
					 }
					 else
					 {
					 	cout << "not enough money to transfer" << endl;
					 
					 	
					 	
					 }
					 
				 }
				 else
				 {
				 	/*
				 	//goal: convert the second account to match the currency of the first account then do the transfer
				 		CheckIfAccountExists(from);
			
					 	UpdatePositionBasedOnName(from);
					 	SubMoney(amount);
					 	
					 	
					 	// switching focus to second account
					 	CheckIfAccountExists(to);
					 	
					 	cout << "country code of second account: " << Account.Balance.CurrentCountry << "value: " << Account.Balance.value << endl;
					 	
					 	ConvertMoneyTo(temp_countrycode1);
					 	
					 		cout << "after convserion country code of second account: " << Account.Balance.CurrentCountry << "value: " << Account.Balance.value << endl;
					 		CheckIfAccountExists(to);
					 		UpdatePositionBasedOnName(to);
					 		AddMoney(amount);
					 		//	UpdatePositionBasedOnName(to);
					 		
					 			cout << "after convserion country code of second account: " << Account.Balance.CurrentCountry << "after transfering value: " << Account.Balance.value << endl;
					 			
					 			ConvertMoneyTo(temp_countrycode2);
					 			
					 			cout << "after convserion country code of second account: " << Account.Balance.CurrentCountry << "after transfering value: " << Account.Balance.value << endl;

					 	 
					 //	 UpdatePositionBasedOnName(to);
				 */
					 	
					 	
				/*	 	
					 cout << "$##########################################" << endl;
					 cout << "subtracted amount:" << amount <<endl;
					 cout << "country code of first account: " << Account.Balance.CurrentCountry << endl;
					 
					 
					 //convert the second account to match the currency of the first account
					 
					 // change to second account
					 CheckIfAccountExists(to);
					 UpdatePositionBasedOnName(to);
					 
					 cout << "Country code of the second account before converssion: " << Account.Balance.CurrentCountry << endl;
				
					 ConvertMoneyTo(temp_countrycode1);
					// add money to second account once the currency of the second matches the curency of the first
					 cout << "Country code of the second account after converssion: " << Account.Balance.CurrentCountry << endl;
					 
					 UpdatePositionBasedOnName(to);
					 AddMoney(amount);
					 WriteToFile();
					 
					 cout << "Country code of the second account after adding money: " << Account.Balance.CurrentCountry << endl;
					 
					 cout << " account with new money in it: " << Account.Balance.value << endl;
					 
					 // then convert the currency of the second account back to the original 
					 // UpdatePositionBasedOnName(to);
					 
					  
					  ConvertMoneyTo(temp_countrycode2);
					
					  
					 cout << "Country code of the second account after changing back to original currency: " << Account.Balance.CurrentCountry << endl;
					 	 cout << " account with new money in it: " << Account.Balance.value << endl;
				 	
				 	*/
				 }
				 
				 // return user to current logged in account
				 
				 CheckIfAccountExists(from);
				 

				
			}
			
			void WriteToFile()
			{
				
			

				ofstream file("UserCollection.txt",ios::out);
				if(!file)
				{
					cerr << "Cant open" << endl;
					
				}
				else
				{
				
					for(int x = 0; x <UMap.size();x++)
					{
					
					Account = UMap[x];
				
					
					file << Account.UserName << " "<< Account.Balance.value <<" " <<Account.Balance.CurrentCountry<< " "<<Account.PassWord<<" "<<Account.permissions<<" "<<Account.NaCl << endl;
					
					}
				
				
				}
				    file.close();


			}
			
			
			void FindAccount(int x)
			{				
				this->Account = UMap[x-1]; 
				
				this->positionOfAccount =(x);
				
				cout << "This is the account that was selected: ";
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				Account.Display();
				
				
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			}
			
			void AddMoney(float v)
			{
				Account.add(v);
				
				UMap[positionOfAccount] = Account;
				
				cout << "This is the account that was selected: ";
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				
				
				Account.Display();
				
				
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				WriteToFile();
				
				
			}
			void SubMoney(float v)
			{
				Account.sub(v);
				UMap[positionOfAccount] = Account;
				WriteToFile();
			}
			void ConvertTo(string countryC)
			{
				Account.ConvertingTime(countryC);
				UMap[positionOfAccount] = Account;
				WriteToFile();
			}
			
			
			char genRandom()
			{// generates a random characters and returns it
			
			    return alphanum[rand() % stringLength];
			}
			
			void CreateAccount()
			{// function to create an account
				string createName;
				string createPassWord;
				// create a function to check if a username is already taken 
				//but for not just make accounts
				cout << "Enter new Username: ";
				cin >> createName;
				cout << "Enter new Password: ";
				cin >> createPassWord;
				
				srand(time(0));
			    string salt;
			    for(unsigned int i = 0; i < 20; ++i)
			    {
			    salt += genRandom();
			
			
			    }
			    
			
				
			
				
				string saltedpass;
				
				saltedpass = md5(salt+createPassWord);
				
				
				Account.User_setup(createName, 0, "USD", saltedpass,0,salt);
				
			//	cout <<"size of UMap" << UMap.size() <<endl;
				
				positionOfAccount = UMap.size();
				
				UMap[positionOfAccount] = Account;
				
		
				WriteToFile();
				positionOfAccount++;
			}
			
			
			bool CheckIfAccountExists(string accountName)
			{// check if an account exist and will also be used to change between Account objects when using certain operations
				
				
				for(int x=0; x < UMap.size(); x++)
					{
						Account = UMap[x];
						
				
					
						if(accountName == Account.UserName)
						{
							return true;
						}
					
				
					}	
				return false;
			
				
			}
			bool CheckPassword(string accountPassword)
			{
				// check if the password is correct
			
					
					
					string hashedPasswordSalted;
				;
					
					hashedPasswordSalted = Account.NaCl + accountPassword;
			
						if(md5(hashedPasswordSalted) == Account.PassWord)
						{
							//cout << "its true" << endl;
							return true;
							
						}
						else
						{
								cout << "Incorrect Password" << endl;
							return false;
						
						}
				
				
			}
			
			bool CheckPermissions(string accountName)
			{// check if its an admin account or not
				cout << "account name:" << accountName << endl;
				for(int x=0; x < UMap.size(); x++)
					{
						Account = UMap[x];
						
						
						if(accountName == Account.UserName)
						{
							//cout << Account.UserName << endl;
						//	cout << Account.permissions << endl;
							if(Account.permissions == 1)
							{
								// admin account
								return true;
							}
							else
							{
								// not admin account
								cerr << "General User " << endl;
								return false;
							}
						}
					
					}
					// this case should never happen 
					return false;
				
				
				
			}
			void DeleteAccount(int position)
			{// delete an account by finding a position 
				int preventAdminFromBeingDeleted = position -1;
				
				if(preventAdminFromBeingDeleted<=0)
				{
					cerr << "Invalid Option" << endl;
				}
				else
				{
					UMap.erase(preventAdminFromBeingDeleted);
					cout << "Account Deleted!" << endl;
				}
				
				WriteToFile();
			}

	};






int main()
{



User_Collection Bank;

string denom;

	

//create a log in thingy



	int choice;
	
	// this controls the loops 
bool gameOn = true;
bool gameOn1 = true;
bool gameOn2 = true;
while (gameOn != false)
{
	
	Bank.Dump();
string temp_username;
string temp_password;
cout << "Username: "; 

cin >> temp_username;





	if(Bank.CheckIfAccountExists(temp_username) == true)
	{
		gameOn2=true; 
		
		cout << "Password: ";
		cin >> temp_password;

		
		if(Bank.CheckPassword(temp_password) == true)
		{
			if(Bank.CheckPermissions(temp_username) == true)
			{
				while (gameOn1 != false)
				{
				cout<< "Welcome Administrator" << endl;
				cout << "*******************************\n";
				cout << " 1 - View accounts.\n";
				cout << " 2 - Create Account.\n";
				cout << " 3 - Delete Account.\n";
				cout << " 4 - Logout.\n";
				cout << " 5 - Shutdown.\n";
				cout << " Enter your choice and press return: ";
				
				cin >> choice;
				switch (choice)
				{
					case 1:
					cout << "*******************************\n";
					Bank.Dump();
					// rest of code here
					break;
					case 2:
					Bank.CreateAccount();
				
					// rest of code here
					break;
					case 3:
					cout << "*******************************\n";
					
					Bank.Dump();
						cout << "*******************************\n";
					cout << "Enter number to select account:";
					int i;
					cin >> i;
					
					Bank.DeleteAccount(i);
					
				
					break;
					case 4:
					cout << "End of Program.\n";
				
					gameOn1 = false;
					
					break;
					
					case 5:
					cout << "Shutdown Complete" << endl;
					
					gameOn1 = false;
					gameOn2 = false;
					break;
					
					default:
					cout << "Not a Valid Choice. \n";
					cout << "Choose again.\n";
					//cin >> choice;
					cin.clear();
					cin.ignore();
					break;
				}
				
				}
			}	
			else
			{
				
				while (gameOn2 != false)
				{
					// non admin account should only have access to its own account
				
					// use this to select account
					Bank.CheckIfAccountExists(temp_username);
					cout <<"account exists" << endl;
					
					cout << "*******************************\n";
					cout << " 1 - View account.\n";
					cout << " 2 - Add Money\n";
					cout << " 3 - Sub Money.\n";
					cout << " 4 - Convert to.\n";
					cout << " 5 - Transfer to.\n";
					cout << " 6 - Logout.\n";
					cout << " 7 - Shutdown.\n";
					
					cout << " Enter your choice and press return: ";
					
					cin >> choice;
					// need to make it so that once you log into an acocunt you do not have 
					// access to the other accounts, therefor change view accounts to view accojnt and make select account built in to the account
					// that is logged in. 
					switch (choice)
					{
						case 1:
						cout << "*******************************\n";
						Bank.view();
						break;
						
						
						case 2:
						cout << "*******************************\n";
						cout << "NOTE: You can only add money that matches accounts Country Code \n";
						cout << "Enter amount of money to add:";
						
						float m;
						cin >> m;
						Bank.AddMoney(m);
						break;
						
						
						
						case 3:
						cout << "*******************************\n";
						cout << "NOTE: You can only add money that matches accounts Country Code \n";
						cout << "Enter amount of money to add:";
						float n;
						cin >> n;
						Bank.SubMoney(n);
						break;
						
						case 4:
						cout << "*******************************\n";
						
						Bank.Account.Balance.Denomination.Dump();
			
						cout << "Enter Country Code of the currency you want:";
						
						cin >> denom;
						Bank.ConvertTo(denom);
						
						cout << "Conversion complete!\n";
						Bank.CheckIfAccountExists(temp_username);
						Bank.view();
						
					
						break;
						
						
						case 5:
						{
						string temp_username2;
						
						cout << "Enter account to transfer money too: ";
						
						cin >> temp_username2;
						
						if(Bank.CheckIfAccountExists(temp_username2)==true)
						{
							Bank.CheckIfAccountExists(temp_username);
								float transferAmount;
							cout << "Enter amount to transfer: ";
						
							cin >> transferAmount;
						
						Bank.TransferTo(temp_username,temp_username2,transferAmount);
						}
						else
						{
							cout<< "Account does not exist" << endl;
						}
					
						
					
					
						
					
						
						}
						break;
						
						
						case 6:
						cout << "Logging out.\n";
						gameOn2 = false;
						break;
						
						case 7:
						cout << "Shutdown Complete" << endl;
						gameOn = false;
						gameOn1 = false;
						gameOn2 = false;
						break;


						default:
						cout << "Not a Valid Choice. \n";
						cout << "Choose again.\n";
						//cin >> choice;
						cin.clear();
						cin.ignore();
						break;
					}
				}
			}
				
			
		}
		else
		{
			cout << "invalid password try again!" << endl;
		}
		
		

	}
	else
	{
		cout << "Account doesn't exist" << endl;
	}

	
	

}
return 0;
	


}