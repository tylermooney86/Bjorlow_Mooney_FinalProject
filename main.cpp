#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "HashTable.h"

using namespace std;

void printMenu();

void printIntro();

int main()
{
    HashTable h;
	
    printIntro();
    
    string menuNum = "0";

    ifstream inFile;
    string data;

    //filestream
    inFile.open("movies.txt");
	
    if(inFile.good())
    {
        char tmp[100];
        string tmpstring;
        int ranking, year, quantity;
        string name, genre;

        while(!inFile.eof())
        {
			
            inFile.getline(tmp,256,',');
    
            ranking = atoi(tmp);

            inFile.getline(tmp,256,',');
            name=tmp;

            inFile.getline(tmp,256,',');
            year = atoi(tmp);

            inFile.getline(tmp,256,',');
            quantity = atoi(tmp);

            inFile.getline(tmp,256,'\n');
            genre = tmp;

            h.insertMovie(ranking,name,year,quantity,genre);
        }

    }
    else
    {
        cout<<"File opened unsuccessfully"<<endl;
    }
    inFile.close();


    while (menuNum != "8")
    {


        printMenu();
        getline(cin,menuNum);
        //insert
        if (menuNum == "1")
        {
            string title, genre, genreNum,tmpyear;
            int year, quantity;

            cout<<"======Insert======"<<endl;

            cout<<"Enter title:"<<endl;
            getline(cin,title);
            cout<<"Enter year:"<<endl;
            getline(cin,tmpyear);
            year = stoi(tmpyear);

            cout<<"======Genre======"<<endl;
            cout<<"1. Action/Adventure"<<endl;
            cout<<"2. Comedy"<<endl;
            cout<<"3. Drama"<<endl;
            cout<<"4. Sci-fi"<<endl;
            cout<<"5. Horror/Suspense"<<endl;
            cout<<"Enter genre:"<<endl;

            getline(cin,genreNum);

            if (genreNum=="1")
            {
                genre = "ActionAdventure";
            }
            else if (genreNum=="2")
            {
                genre = "Comedy";
            }
            else if (genreNum=="3")
            {
                genre = "Drama";
            }
            else if (genreNum=="4")
            {
                genre = "Scifi";
            }
            else if (genreNum=="5")
            {
                genre = "HorrorSuspense";
            }
            else
            {
                genre = "Unknown";
            }

            cout<<"Enter quantity:"<<endl;
            cin>>quantity;
            cin.ignore();

            h.insertMovie(title, year, quantity,genre);


        }
        //delete
        if (menuNum == "2")
        {
            cout<<"===Delete==="<<endl;
            string title;
            cout<<"Enter title:"<<endl;
            getline(cin,title);

            h.deleteMovie(title);
        }
        //find
        if (menuNum == "3")
        {
            string findMenuNum = "0";
            while (findMenuNum!= "4")
            {
                cout<<"======Search Menu======"<<endl;
                cout<<"1. Search by rank"<<endl;
                cout<<"2. Search by name"<<endl;
                cout<<"3. Browse by genre"<<endl;
                cout<<"4. Return to main menu"<<endl;

                getline(cin, findMenuNum);
                //insert movie
                if (findMenuNum == "1")
                {
                    string ranking;
                    cout<<"Enter Rank:"<<endl;
                    getline(cin,ranking);
                    int rankInt = stoi(ranking);
                    h.findMovieRanking(rankInt);
                }
                if (findMenuNum == "2")
                {
                    string title;
                    cout<<"Enter title:"<<endl;
                    getline(cin,title);

                    h.findMovie(title);
                }
                if (findMenuNum == "3")
                {
                    string genreNum = "0";

                    while(genreNum!= "6")
                    {
                        cout<<"======Genre======"<<endl;
                        cout<<"1. Action/Adventure"<<endl;
                        cout<<"2. Comedy"<<endl;
                        cout<<"3. Drama"<<endl;
                        cout<<"4. Sci-fi"<<endl;
                        cout<<"5. Horror/Suspense"<<endl;
                        cout<<"6. Exit"<<endl;

                        getline(cin,genreNum);

                        if (genreNum == "1")
                        {
                            cout<<"======Action/Adventure======"<<endl;
                            h.printGenre("ActionAdventure");
                        }
                        else if (genreNum == "2")
                        {
                            cout<<"======Comedy======"<<endl;
                            h.printGenre("Comedy");
                        }
                        else if (genreNum == "3")
                        {
                            cout<<"======Drama======"<<endl;
                            h.printGenre("Drama");
                        }
                        else if (genreNum == "4")
                        {
                            cout<<"======Sci-fi======"<<endl;
                            h.printGenre("Scifi");
                        }
                        else if (genreNum == "5")
                        {
                            cout<<"======Horror/Suspense======"<<endl;
                            h.printGenre("HorrorSuspense");
                        }
                        else
                        {
                            break;
                        }
                    }
                }


            }
        }
        //print menu
        if (menuNum == "4")
        {
            string printMenuNum = "0";
            while(printMenuNum != "3")
            {
                cout<<"======Print Menu======"<<endl;
                cout<<"1. Print by rank"<<endl;
                cout<<"2. Print by index"<<endl;
                cout<<"3. Return to main menu"<<endl;

                getline(cin,printMenuNum);
                //print rank
                if (printMenuNum == "1")
                {
                    h.printRank();
                }
                //print hash table
                else if (printMenuNum == "2")
                {
                    h.printTableContents();
                }
                //return to main menu
                else
                {
                    break;
                }
            }

        }
        //Rent Movie
        if (menuNum == "5")
        {
            cout<<"======Rental======"<<endl;
            string title;
            cout<<"Enter name: "<<endl;
            getline(cin,title);
            h.rentMovie(title);
        }
        //Change quantity of a movie
        if (menuNum == "6")
        {
            cout<<"===Change Quantity==="<<endl;
            string title,quantity;
            int tmpRank;
            cout<<"Enter name: "<<endl;
            getline(cin,title);
            cout<<"Enter new quantity: "<<endl;
            getline(cin,quantity);
            tmpRank = stoi(quantity);
            h.changeQuantity(tmpRank, title);
        }
        //change genre of a movie
        if (menuNum == "7")
        {
            cout<<"===Change Genre==="<<endl;
            string title;
            cout<<"Enter name: "<<endl;
            getline(cin,title);

            string genreNum = "0";

            cout<<"======Select Genre======"<<endl;
            cout<<"1. Action/Adventure"<<endl;
            cout<<"2. Comedy"<<endl;
            cout<<"3. Drama"<<endl;
            cout<<"4. Sci-fi"<<endl;
            cout<<"5. Horror/Suspense"<<endl;

            getline(cin,genreNum);

            if (genreNum == "1")
            {
                h.changeGenre("ActionAdventure", title);
            }
            else if (genreNum == "2")
            {
                h.changeGenre("Comedy", title);
            }
            else if (genreNum == "3")
            {
                h.changeGenre("Drama", title);
            }
            else if (genreNum == "4")
            {
                h.changeGenre("Scifi", title);
            }
            else if (genreNum == "5")
            {
                h.changeGenre("HorrorSuspense", title);
            }


        }

    }

    //exit
    cout<<"Goodbye!"<<endl;

    return 0;
}

void printMenu()
{
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Insert Movie"<<endl;
    cout<<"2. Delete Movie"<<endl;
    cout<<"3. Find Movie"<<endl;
    cout<<"4. Print Inventory"<<endl;
    cout<<"5. Rent Movie"<<endl;
    cout<<"6. Change Quantity"<<endl;
    cout<<"7. Change Genre"<<endl;
    cout<<"8. Quit"<<endl;
    cout<<"====================="<<endl;
}

void printIntro()
{
    cout<<"Movie Store 2.0"<<endl;
    cout<<"====================="<<endl;
}
