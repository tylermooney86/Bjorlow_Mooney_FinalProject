#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>

struct HashElem{
	std::string title, genre;
	int year;
	int quantity;
	int ranking;
	int rented;
	HashElem *next;
    HashElem *previous;

	HashElem(){
        next = NULL;
        previous = NULL;
        title = " ";
        year = 0;
        ranking = 0;
        quantity = 0;
        genre = " ";
	}
	HashElem(std::string in_title, int in_year)
	{
		title = in_title;
		year = in_year;
		ranking = 0;
		quantity = 0;
		genre = " ";
		next = NULL;
		previous = NULL;
	}
	HashElem(int in_rank, std::string in_title, int in_year)
	{
		title = in_title;
		year = in_year;
		ranking = in_rank;
		quantity = 0;
		genre = " ";
		next = NULL;
		previous = NULL;
	}
	HashElem(int in_rank, std::string in_title, int in_year, int in_quantity)
	{
		title = in_title;
		year = in_year;
		ranking = in_rank;
		quantity = in_quantity;
		genre = " ";
		next = NULL;
		previous = NULL;
	}
	HashElem(int in_rank, std::string in_title, int in_year, int in_quantity, std::string in_genre)
	{
		title = in_title;
		year = in_year;
		ranking = in_rank;
		quantity = in_quantity;
		genre = in_genre;
		next = NULL;
		previous = NULL;
	}

};

class HashTable
{
	public:
		HashTable();
		~HashTable();
		void printTableContents();
		void insertMovie( std::string name, int year, int quantity,std::string genre);
		void insertMovie( int ranking, std::string name, int year, int quantity,std::string genre);
		void deleteMovie(std::string name);
		void findMovie(std::string name);
		void findMovieRanking(int ranking);
		void rentMovie(std::string name);
		void printGenre(std::string genre);
		void printRank();
		void changeQuantity(int quantity,std::string name);
		void changeGenre(std::string genre, std::string name);

	private:
		int hashSum(std::string x, int s);
		int tableSize = 10;
		void adjustRankDown(int ranking);
		void adjustRankUp(int ranking);
		HashElem* hashTable[10];
		bool checkTable();
		bool ifIn;
		int MAX_RANK = 1;

};

#endif // HASHTABLE_H
