// CORSE 7 PROJECT 1 PART 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<vector>
#include<iomanip> 
#include <string> 
#include<fstream>
using namespace std; 


short readaccountnumber(string msg);

enum enLISToption
{
    showclient = 1 ,
    addclient , 
    deleteaclient, 
    updateaclient , 
    findclient ,
    transactions ,
    Exit ,
};

enum enTRANSACTIONSlist
{
    diposit = 1, 
    withdraw,
    showBALANCE,
    backTOmainMenu
};


struct STclientdetails
{
    short accountnumber = 0;
    short pincode = 0; 
    string fullname;
    string phonenumber;
    int accountbalance;
    bool markfordeletion = false;
};

vector <STclientdetails> assignelementsTOaVECTOR(string filename);

void mainMENUscreen(vector <STclientdetails>& Vclient);
void tranactionsSCREEN(vector <STclientdetails>& Vclient);

bool checkIFclientexists(vector <STclientdetails>client, int accountnumber)
{
    for (STclientdetails &member : client)
    {
        if (member.accountnumber == accountnumber)
        {
            return true;
        }

    }
    return false;


}


STclientdetails readclientdetailsfunction(vector<STclientdetails>&Vclient)
{
    STclientdetails info;

    cout << "please enter account number: "; cin >> info.accountnumber; cout << endl;
    
    while (checkIFclientexists(Vclient, info.accountnumber))
    {  
        system("color C0");

        cout << "WRONG INPUT !!! client number ALREADY exists please enter another account number: "; cin >> info.accountnumber; cout << endl;

    }
    system("color 07");

    cout << "please enter PINCODE: "; cin >> info.pincode; cout << endl;
    cout << "please enter fullname: "; getline(cin >> ws, info.fullname); cout << endl;
    cout << "please enter phone number: "; cin >> info.phonenumber; cout << endl;
    cout << "please enter account balance: "; cin >> info.accountbalance; cout << endl; 

    return info;
}

string convertRecordTOlineFunction(STclientdetails STclient , string delimiter)
{
    string fullline = "";


    fullline += to_string( STclient.accountnumber)  + delimiter;
    fullline += to_string(STclient.pincode) + delimiter; 
    fullline += STclient.fullname + delimiter;
    fullline += STclient.phonenumber + delimiter;
    fullline += to_string(STclient.accountbalance);

    return fullline;


}

void addlinetofile(vector<STclientdetails>& Vclient) // MAIN FUNCTION
{ 
    string line = "";
    fstream myfile;

    myfile.open("project-1-part-2.txt", ios::app);

    if (myfile.is_open())
    {
        line = convertRecordTOlineFunction(readclientdetailsfunction(Vclient), "---");

        myfile << line << endl;

    }
    myfile.close(); 

    Vclient = assignelementsTOaVECTOR("project-1-part-2.txt");


    cout << "Client ADDED succesfully !!! " << endl;
}

vector <string> splitstringFUNCTION(string line , string delimiter)
{
    vector <string> Vclient;
    short pos;
    string vectorELEMENT; 

    while ((pos = line.find(delimiter)) !=  string ::npos)
    {
        vectorELEMENT = line.substr(0, pos);

        Vclient.push_back(vectorELEMENT);

        line.erase(0, pos + delimiter.length() );

    }

    if (line!="")
    {
        Vclient.push_back(line);
    }

    return Vclient;

}

STclientdetails assignVECTORelementsTOst(vector<string>vline )
{
    STclientdetails stclient;

    stclient.accountnumber =   stoi (vline[0]);
    stclient.pincode = stoi(vline[1]);
    stclient.fullname = vline[2];
    stclient.phonenumber = vline[3];
    stclient.accountbalance = stoi(vline[4]); 

    return stclient;

}

vector<STclientdetails>assignelementsTOaVECTOR(string filename)
{
    vector<STclientdetails>Vclient;
    STclientdetails stclient;
    fstream myfile;

    myfile.open(filename, ios::in);

    if (myfile.is_open())
    {
        string line;

        while (getline(myfile, line))
        {
            stclient = assignVECTORelementsTOst(splitstringFUNCTION(line, "---"));

            Vclient.push_back(stclient);

        }

        myfile.close();

    }

    






    return Vclient;


}


void showEACHclientDETAILS(vector<STclientdetails>vclient)
{
    for (STclientdetails member : vclient)
    {

        cout << left << setw(15) << member.accountnumber << setw(15) << member.pincode << setw(25) << member.fullname << setw(15)
            << member.phonenumber << member.accountbalance << endl;

    }





}

void showclientlistSCREEN(vector<STclientdetails> &vclients) // main function
{

    cout << left << "--------------------" << "CLIENTS [ " << vclients.size() << " ] " << "---------------------------------------------" << endl;
    cout << left << "--------------------------------------------------------------------------------" << endl;

    cout << left << "|Account number|" << setw(5) << "| pin code |" << setw(22) << "| full name |" << setw(20) << "| phone number |" << setw(15) << "| balance | \n" << endl;

    cout << "---------------------------------------------------------------------------------\n" << endl;


    showEACHclientDETAILS(vclients);



     
}

string convertrecordTOline(STclientdetails record, string delimiter)
{
    string line = "";

    line = line + to_string(record.accountnumber) + delimiter;
    line = line + to_string(record.pincode) + delimiter;
    line = line + record.fullname + delimiter;
    line = line + record.phonenumber + delimiter;
    line = line + to_string(record.accountbalance) ;

    return line;
}

bool findaclient(vector<STclientdetails> vclient, STclientdetails &clientcard, int accountnumber)
{

    for (STclientdetails &member : vclient)
    {
        if (member.accountnumber == accountnumber)
        {
            clientcard = member;

            return true;
        }
    }

    return false;



}



void PRINTclientCARD(STclientdetails clientcard)
{
    cout << "Here Are This CLIENT details: " << endl;

    cout << "Account Number: " << clientcard.accountnumber << endl;
    cout << "Account PINCODE: " << clientcard.pincode << endl;
    cout << "Account Full Name: " << clientcard.fullname << endl;
    cout << "Account Phone number: " << clientcard.phonenumber << endl;
    cout << "Account Balance: " << clientcard.accountbalance << endl;



}


void findAclientSCREEN(vector <STclientdetails> vclient)
{
    STclientdetails clientcard; int accountnumber = readaccountnumber("Please enter the account nnumber of the client you want to FIND: ");

    findaclient(vclient, clientcard, accountnumber); 
    PRINTclientCARD(clientcard);

}

void markfordeletion(vector<STclientdetails> &Vclient , int accountnumber)
{

    for (STclientdetails &member : Vclient)
    {

        if (member.accountnumber == accountnumber)
        {
            member.markfordeletion = true;
        }

    }





}


void deleteclientFROMFILE(vector<STclientdetails>&vclient)
{ 
    string line;
    fstream myfile;

    myfile.open("project-1-part-2.txt", ios::out);

    if (myfile.is_open())
    {
        for (STclientdetails &member : vclient)
        {
            if (member.markfordeletion == false)
            {
                line = convertrecordTOline(member, "---");

                myfile << line << endl;

            }



        }



    }






}

short readaccountnumber(string msg)
{
    short accountnumber = 0;

    cout << msg; cin >> accountnumber;

    return accountnumber;
}

void deleteclientSCREEN(vector <STclientdetails> &Vclient) //mainfunction
{  
    char answer;

    short accnumber = readaccountnumber("Please enter the account number of the client you want to DELETE: ");
    STclientdetails oneclient;
    if (findaclient(Vclient, oneclient, accnumber))
    {
        PRINTclientCARD(oneclient);

        cout << "Do you still want to delete this client IF yes answer with 'y' OR 'Y' : "; cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            markfordeletion(Vclient, accnumber);
            deleteclientFROMFILE(Vclient);

            cout << "Client deleted successfully !!!! " << endl;
        }





    }
    else cout << "WRONG INPUT ! This account number doesn't exist ! " << endl;

    Vclient = assignelementsTOaVECTOR("project-1-part-2.txt");


}

STclientdetails changeCLIENTdetailsFunction(short accountnumber)
{
    STclientdetails info;

    info.accountnumber = accountnumber;
   
    cout << "please enter PINCODE: "; cin >> info.pincode; cout << endl;
    cout << "please enter fullname: "; getline(cin >> ws, info.fullname); cout << endl;
    cout << "please enter phone number: "; cin >> info.phonenumber; cout << endl;
    cout << "please enter account balance: "; cin >> info.accountbalance; cout << endl;

    return info;




}

void UPDATEclientINaVector(vector<STclientdetails> &vclient , short accountnumber)
{
   
       
        for (STclientdetails & element : vclient)
        {
            if (element.accountnumber == accountnumber)
            {
                element = changeCLIENTdetailsFunction(accountnumber);

            }

        }


}

void performTHEupdate(vector<STclientdetails>vclient)
{ 
    fstream myfile;

    myfile.open("project-1-part-2.txt", ios::out);

    if (myfile.is_open())
    {

        for (STclientdetails& element : vclient)
        {
            string line = convertRecordTOlineFunction(element, "---");
            myfile << line << endl;

            


        }




    }




}

void updateclientSCREEN(vector <STclientdetails>& Vclient)
{
    char answer; 

    short accnumber = readaccountnumber("Please enter the account number of the clinet you want to UPDATE: ");

    STclientdetails clientcard;

    if (findaclient(Vclient, clientcard, accnumber))
    {  
        PRINTclientCARD(clientcard);

        cout << "Are you sure you want to update this client's details if YES answer with [y] OR [Y] : "; cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            UPDATEclientINaVector(Vclient, accnumber);
            performTHEupdate(Vclient);

            cout << "Client Updated succesfully !!! " << endl; 
        }


    }
    else cout << "WRONG INPUT !!! Client doesn't exist ! " << endl;


}

void backtoMAINmenu(vector <STclientdetails>&Vclient)
{
    cout << "Press any key to go back to main MENU: "; system("pause>0");
    system("cls");
    mainMENUscreen(Vclient);
}

void ExitProgramFunction()
{

    cout << "Press any key to go back to EXIT PROGRAM: "; system("pause>0");
    cout << system("cls");


}

void GobackTOtransactionsMENU(vector <STclientdetails> &Vclient)
{

    cout << "Press any key to go back to TRANSACTIONS MENU: "; system("pause>0");
    system("cls"); 
    system("color 07");

    tranactionsSCREEN(Vclient);
}

void performDEPOSIT(vector <STclientdetails>& Vclient , short accountnumber , int balance)
{
    for (STclientdetails &element : Vclient)
    {
        if (element.accountnumber == accountnumber)
        {

            element.accountbalance = element.accountbalance + balance;

        }
        

    }
    system("color A0");
    cout << "Amount succefully deposited !!! " << endl;


}

void depositBalanceSCREEN(vector <STclientdetails> &Vclient)
{
    short accountnumber; 
    int balance; 
    STclientdetails clientcard;
    char answer = 'h';

    cout << "-----------------------------------------------\n" << endl;
    cout << "                   DEPOSIT SCREEN             \n" << endl;
    cout << "-------------------------------------------------\n" << endl; 

    cout << "Please enter account number of the client to deposit balance: "; cin >> accountnumber; cout << endl;

    while (findaclient(Vclient , clientcard , accountnumber) == false)
    {
        cout << "WRONG INPUT client does not exist please enter a valid account number: "; cin >> accountnumber; cout << endl;
        system("color C0");

    }
    system("color 07");

    PRINTclientCARD(clientcard);

    cout << "Please enter the balance you want to deposit: "; cin >> balance;
    cout << "Are you sure you want to perform this Transcation ? if YES type [y] OR [Y]: "; cin >> answer; cout << endl;

    if (answer == 'y' || answer == 'Y')
    {
        performDEPOSIT(Vclient, accountnumber, balance); 
        performTHEupdate(Vclient);
    }

}

void printEACHclientBALANCE(vector <STclientdetails> Vclient)
{  
    int totalBALANCE = 0;

    for (STclientdetails &element : Vclient)
    {

        cout << left << setw(15) <<  element.accountnumber << setw(22) << element.fullname << setw(15) << element.accountbalance << endl;

        totalBALANCE = totalBALANCE + element.accountbalance;
    }

    cout << "---------------------------------------------------------------------------------\n" << endl;

    cout << setw(20)<< "Total Balances: " << totalBALANCE << endl;
}

void showTOTALbalancesSCREEN(vector<STclientdetails>Vclient)
{


    cout << left << "--------------------" << "CLIENTS [ " << Vclient.size() << " ] " << "---------------------------------------------" << endl;
    cout << left << "--------------------------------------------------------------------------------" << endl;

    cout << left << "|Account number|" << setw(22) << "| full name |" << setw(15) << "| balance | \n" << endl;

    cout << "---------------------------------------------------------------------------------\n" << endl;


    printEACHclientBALANCE(Vclient);


}

void performWITHDRAW(vector<STclientdetails>&Vclient , short accountnumber )
{  
    char answer ='t';

    
    int balance = readaccountnumber("Please enter the amount you want to withdraw: ");


    for (STclientdetails &element : Vclient)
    {
        if (element.accountnumber == accountnumber)
        {
            while (balance > element.accountbalance)
            { 
                system("color C0");


                cout << "Amount you entered exceeds the balance you can withdraw up to " << element.accountbalance << " only, Please enter another amount: "; cin >> balance; cout << endl;


            } 
            system("color 07");

            cout << "Are you sure you want to withdraw this amount if yes answer with [y] OR [Y] : "; cin >> answer; cout << endl;

            if (answer == 'y' || answer == 'Y')
            {
                element.accountbalance = element.accountbalance - balance;

            }


        }


    }
    system("color A0");
    cout << "Amount succefully withdrawn !!! " << endl;


}

void withdrawBalanceSCREEN(vector <STclientdetails>&Vclient)
{  
    STclientdetails clientcard;
    char answer;
    cout << "-----------------------------------------------\n" << endl;
    cout << "                   WITHDRAW SCREEN             \n" << endl;
    cout << "-------------------------------------------------\n" << endl;

    short accountnumber = readaccountnumber("Please enter the account number of the client to perform withdrawal: ");

    while (findaclient(Vclient ,clientcard , accountnumber) == false)
    {
        cout << "WRONG INPUT !!! This client doesn't exist please enter a VALID account number: "; cin >> accountnumber; cout << endl;
        system("color C0");

    }
    system("color 07");


    PRINTclientCARD(clientcard);



   
       performWITHDRAW(Vclient, accountnumber);  
        
       performTHEupdate(Vclient);  // we use this function to update the file by writing the NEW UPDATED vector (with the new balance in this example) the FILE using ios :: out 

    

}
void tranactionsSCREEN(vector <STclientdetails> &Vclient)
{
    short option;

    cout << "----------------- [ " << "TRANSACTIONS MENU" << " ] ---------------\n" << endl;
    cout << "-------------------------------------------------------" << endl;

    cout << setw(10) << " " << "[ 1 ] Deposit" << endl;
    cout << setw(10) << " " << "[ 2 ] Withdraw " << endl;
    cout << setw(10) << " " << "[ 3 ] Show Total Balances " << endl;
    cout << setw(10) << " " << "[ 4 ] Go back to main menu " << endl;
   
    cout << "Choose an option from the list: "; cin >> option; cout << endl;  

    switch (enTRANSACTIONSlist(option))
    {
    case diposit: 
        depositBalanceSCREEN(Vclient);
        GobackTOtransactionsMENU(Vclient);
        break;
    case withdraw: 
        withdrawBalanceSCREEN(Vclient); 
        GobackTOtransactionsMENU(Vclient);
        break;
    case showBALANCE: 
        showTOTALbalancesSCREEN(Vclient); 
        GobackTOtransactionsMENU(Vclient);
        break;
    case backTOmainMenu: 
        backtoMAINmenu(Vclient);
        break;
    default:
        break;
    }

}

void mainMENUscreen(vector <STclientdetails> &Vclient)
{  
    short option;


    cout << "-------------------- [ " << "MAIN MENU" << " ] --------------------\n" << endl;
    cout << "-------------------------------------------------------" << endl;

    cout << setw(10) << " " << "[ 1 ] Show Client list" << endl;
    cout << setw(10) << " " << "[ 2 ] Add a new Client " << endl;
    cout << setw(10) << " " << "[ 3 ] Delete a Client " << endl;
    cout << setw(10) << " " << "[ 4 ] Update a Client " << endl;
    cout << setw(10) << " " << "[ 5 ] Find a Client " << endl; 
    cout << setw(10) << " " << "[ 6 ] TRANSACTIONS " << endl;
    cout << setw(10) << " " << "[ 7 ] EXIT" << endl;

    cout << "Please select an option from the list [1] TO [7] : "; cin >> option; cout << endl;


    enLISToption listOPTION;

    listOPTION = enLISToption(option);

    switch (listOPTION)
    {
    case showclient: 

        showclientlistSCREEN(Vclient);
        backtoMAINmenu(Vclient);
        break;
    case addclient: 

        addlinetofile(Vclient);
        backtoMAINmenu(Vclient);


        break;
    case deleteaclient: 
 
        deleteclientSCREEN(Vclient);
        backtoMAINmenu(Vclient);

        break;
    case updateaclient: 
        updateclientSCREEN(Vclient);
        backtoMAINmenu(Vclient);

        break;
    case findclient: 
       

        findAclientSCREEN(Vclient);
        backtoMAINmenu(Vclient);

        break;
    case transactions: 
        
        system("cls");
        tranactionsSCREEN(Vclient);
        backtoMAINmenu(Vclient);

        break;
    case Exit: 


        ExitProgramFunction();
        

        break;
    default:
        break;
    }





}




int main()
{
    vector <STclientdetails> Vclient;

    Vclient = assignelementsTOaVECTOR("project-1-part-2.txt");

    //showclientlistSCREEN(Vclient);

    mainMENUscreen(Vclient);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
