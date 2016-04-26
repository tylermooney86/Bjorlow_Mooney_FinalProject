#include "HashTable.h"
#include <iostream>
#include <string>
#include <hashtable.h>

using namespace std;
//constructor
HashTable::HashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        hashTable[i]=NULL;
    }
}
//Destructor
HashTable::~HashTable()
{

}
//print contents in order they are stored checks if empty first
void HashTable::printTableContents()
{
    if (!checkTable())
    {
        cout<<"empty"<<endl;
    }
    else
    {
        for (int i = 0; i < tableSize; i++)
        {
            cout<<"Index: "<<i<<endl;
            HashElem *tmp = hashTable[i];
            if (tmp!=NULL)
            {
                while (tmp != NULL)
                {
                    cout<<tmp->title<<" Rank:"<<tmp->ranking<<":"<<" Year:"<<tmp->year<<" Quantity:"<<tmp->quantity<<" Genre:"<<tmp->genre<<endl;
                    tmp = tmp->next;
                }
            }
        }
    }
}
//insert function w/out ranking
void HashTable::insertMovie(std::string name, int year, int quantity,std::string genre)
{
    int index = hashSum(name, tableSize);

    HashElem *hashElement = new HashElem(MAX_RANK,name,year,quantity, genre);

    if (hashTable[index] == NULL)
    {
        hashElement->previous = NULL;
        hashTable[index] = hashElement;
        MAX_RANK++;
    }
    else if (hashTable[index]->next == NULL)
    {
        if (hashTable[index]->title == name)
        {
            cout<<"duplicate"<<endl;
        }
        else
        {

            hashElement->previous = hashTable[index];
            hashElement->next = NULL;
            hashTable[index]->next = hashElement;
            MAX_RANK++;
        }
    }
    else
    {
        bool dup = false;
        HashElem *tmp = hashTable[index];
        while(tmp->next != NULL)
        {
            if (tmp->title == name)
            {
                cout<<"duplicate"<<endl;
                dup = true;
                break;
            }
            tmp = tmp->next;
        }
        if (!dup)
        {
            hashElement->next = NULL;
            hashElement->previous = tmp;
            tmp->next = hashElement;
            MAX_RANK++;
        }
    }
}
//insert movie with ranking
void HashTable::insertMovie(int ranking, std::string name, int year, int quantity,std::string genre)
{
    int index = hashSum(name, tableSize);

    HashElem *hashElement = new HashElem(MAX_RANK,name,year,quantity,genre);

    if (hashTable[index] == NULL)
    {
        hashElement->previous = NULL;
        hashTable[index] = hashElement;
        MAX_RANK++;
    }
    else if (hashTable[index]->next == NULL)
    {
        if (hashTable[index]->title == name)
        {
            cout<<"duplicate"<<endl;
        }
        else
        {

            hashElement->previous = hashTable[index];
            hashElement->next = NULL;
            hashTable[index]->next = hashElement;
            MAX_RANK++;
        }
    }
    else
    {
        bool dup = false;
        HashElem *tmp = hashTable[index];
        while(tmp->next != NULL)
        {
            if (tmp->title == name)
            {
                cout<<"duplicate"<<endl;
                dup = true;
                break;
            }
            tmp = tmp->next;
        }
        if (!dup)
        {
            hashElement->next = NULL;
            hashElement->previous = tmp;
            tmp->next = hashElement;
            MAX_RANK++;
        }
    }
}
//delete movie function
void HashTable::deleteMovie(std::string name)
{
    int tmpRank;
    bool found = false;
    int index = hashSum(name, tableSize);
    if (hashTable[index] != NULL)
    {
        HashElem *tmp = hashTable[index];
        while(tmp!=NULL)
        {
            if(tmp->title == name)
            {
                if (tmp->previous==NULL)
                {
                    if(tmp->next != NULL)
                    {
                        tmp->next->previous = NULL;
                        hashTable[index]=tmp->next;
                    }
                    else
                    {

                        hashTable[index]=NULL;
                    }

                    tmpRank = tmp->ranking +1;
                    adjustRankDown(tmpRank);
                    found = true;
                    delete tmp;
                    break;
                }
                else
                {

                    if(tmp->next != NULL)
                    {
                        tmp->next->previous = tmp->previous;
                        tmp->previous->next = tmp->next;
                    }
                    else
                    {
                        tmp->previous->next = NULL;
                    }

                    tmpRank = tmp->ranking +1;
                    adjustRankDown(tmpRank);
                    found = true;
                    delete tmp;
                    break;
                }
            }
            tmp = tmp->next;
        }
    }
    if (!found)
    {
        cout<<"Movie not found."<<endl;
    }
    else
    {
        MAX_RANK--;
    }
}
//find and print movie
void HashTable::findMovie(std::string name)
{
    int index = hashSum(name,tableSize);
    bool found = false;
    if (hashTable[index] != NULL)
    {
        HashElem *tmp = new HashElem;
        tmp = hashTable[index];

        while(tmp!= NULL)
        {
            if (tmp->title == name)
            {
                cout<<"Rank:"<<tmp->ranking<<":"<<tmp->title<<" Year:"<<tmp->year<<" Quantity:"<<tmp->quantity<<" Genre:"<<tmp->genre<<endl;
                found = true;
                break;
            }
            else
            {
                tmp = tmp->next;
            }
        }
        if (!found)
        {
            cout<<"not found"<<endl;

        }
    }
}
//hash function
int HashTable::hashSum(std::string x, int s)
{
    int sum = 0;
    for (int i = 0; i < x.size(); i++)
    {
        sum = sum + x[i];
    }
    sum = sum % s;

    return sum;
}
//check if table is empty
bool HashTable::checkTable()
{
    bool built = false;
    for (int i = 0; i<tableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            built = true;
        }

    }
    return built;
}
//print in order of rank
void HashTable::printRank()
{
    int ranking = 0;
    while (ranking < MAX_RANK)
    {
        findMovieRanking(ranking);
        ranking++;
    }
}
//find specific movie by rank
void HashTable::findMovieRanking(int ranking)
{
    for (int i = 0; i < tableSize; i++)
    {
        HashElem *tmp = hashTable[i];
        if (tmp!=NULL)
        {
            while (tmp != NULL)
            {
                if(tmp->ranking == ranking)
                {
                    cout<<"Rank:"<<tmp->ranking<<":"<<tmp->title<<" Year:"<<tmp->year<<" Quantity:"<<tmp->quantity<<" Genre:"<<tmp->genre<<endl;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
}
//rent movie decreasing quantity
void HashTable::rentMovie(string name)
{
    int index = hashSum(name,tableSize);
    bool found = false;
    if (hashTable[index] != NULL)
    {
        HashElem *tmp = new HashElem;
        tmp = hashTable[index];

        while(tmp!= NULL)
        {
            if (tmp->title == name)
            {
                if (tmp->quantity > 0)
                {
                    cout<<"Renting: ";
                    cout<<tmp->ranking<<":"<<tmp->title<<" Year:"<<tmp->year<<" Quantity:"<<tmp->quantity<<" Genre:"<<tmp->genre<<endl;
                    found = true;
                    tmp->quantity--;
                    break;
                }
                else
                {
                    cout<<"Out of stock"<<endl;
                    found=true;
                    break;
                }
            }
            else
            {
                tmp = tmp->next;
            }
        }
        if (!found)
        {
            cout<<"not found"<<endl;

        }
    }
}
// print movies by genre
void HashTable::printGenre(std::string genre)
{
    for (int i = 0; i < tableSize; i++)
    {
        HashElem *tmp = hashTable[i];
        if (tmp!=NULL)
        {
            while (tmp != NULL)
            {
                if(tmp->genre == genre)
                {
                    cout<<tmp->ranking<<":"<<tmp->title<<":"<<tmp->year<<":"<<tmp->quantity<<endl;

                }
                tmp = tmp->next;
            }
        }
    }
}
//move rank down on all above ranked movies
void HashTable::adjustRankDown(int ranking)
{
    while (ranking < MAX_RANK)
    {
        for (int i = 0; i < tableSize; i++)
        {
            HashElem *tmp = hashTable[i];
            if (tmp!=NULL)
            {
                while (tmp != NULL)
                {
                    if(tmp->ranking == ranking)
                    {
                        tmp->ranking--;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }
        ranking++;
    }
}
//move rank up on all above ranked movies
void HashTable::adjustRankUp(int ranking)
{
    while (ranking < MAX_RANK)
    {
        for (int i = 0; i < tableSize; i++)
        {
            HashElem *tmp = hashTable[i];
            if (tmp!=NULL)
            {
                while (tmp != NULL)
                {
                    if(tmp->ranking == ranking)
                    {
                        tmp->ranking++;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }
        ranking++;
    }
}
//take user input for quantity of movie
void HashTable::changeQuantity(int quantity, std::string name)
{

    for (int i = 0; i < tableSize; i++)
    {
        HashElem *tmp = hashTable[i];
        if (tmp!=NULL)
        {
            while (tmp != NULL)
            {
                if(tmp->title == name)
                {
                    tmp->quantity = quantity;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
}
//take user input for different genre for movie
void HashTable::changeGenre(std::string genre, std::string name)
{

    for (int i = 0; i < tableSize; i++)
    {
        HashElem *tmp = hashTable[i];
        if (tmp!=NULL)
        {
            while (tmp != NULL)
            {
                if(tmp->title == name)
                {
                    tmp->genre = genre;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
}
