#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Notebook
{
	int day,month,year,longDay,size,telephone,state;
	string fio;
};

class Hash
{
	Notebook *table;
	int size; 
	const double rehash_size = 0.75;
	int buffer_size; 
	int size_all_non_nullptr;	
  	
  	int Hash_One_Function(int key) 
	{
		return (key % buffer_size);
	}	
	
	int Hash_Two_Function(int index, int j)
	{
		return ((index+j*1) % buffer_size);
	} 
	
	void Resize()
	{
		cout<<"Resize"<<endl;
		int past_buffer_size = buffer_size;
		buffer_size = (buffer_size*20)/100 + buffer_size;
		size = 0;
		size_all_non_nullptr = 0;
		Notebook *table2 = new Notebook[buffer_size];
		for(int i=0; i<buffer_size; i++) 
		{
			table2[i].day = table2[i].month = table2[i].year = table2[i].longDay = table2[i].size = table2[i].telephone = 0;
			table2[i].state = 0;
		}
		std::swap(table, table2);
		for(int i=0; i<past_buffer_size; i++)
		{
			if(table2[i].state == 1)
			Add(table2[i]);
		}
		delete[] table2;
	}
	void Rehash()
	{
		cout<<"Rehash"<<endl;
        size = 0;
        size_all_non_nullptr = 0;
        Notebook *table2 = new Notebook[buffer_size];
        for (int i = 0; i < buffer_size; i++)
        {
			table2[i].day = table2[i].month = table2[i].year = table2[i].longDay = table2[i].size = table2[i].telephone = 0;
			table2[i].state = 0;
		}
        std::swap(table, table2);
        for (int i = 0; i < buffer_size; i++)
        {
           if(table2[i].state == 1)
			Add(table2[i]);
        }
        delete[] table2;
	}
  
	public:
			
	Hash(int value) //êîíñòðóêòîð
	{
		buffer_size = value;
		size = 0;
		size_all_non_nullptr = 0;
		table = new Notebook[buffer_size];
		
		for (int i=0; i<buffer_size; i++)
		{
			table[i].day = table[i].month = table[i].year = table[i].longDay = table[i].size = table[i].telephone = 0;
			table[i].state = 0;
		}
	}
		
	bool Add(Notebook hotel) //äîáàâëåíèå
	{
		if (size+1 > rehash_size*buffer_size) Resize();
		else if(size_all_non_nullptr > size*2) Rehash();
		
		int index = Hash_One_Function(hotel.telephone);
		int two_index = index;
		int i =0;
		int j = 2;
		int del =-1;
		
		while (table[two_index].telephone != 0 && i<buffer_size)
		{
		if (table[two_index].telephone == hotel.telephone && table[two_index].state == 1)
		return false;
		if (table[two_index].state == 2 && del == -1) del = two_index;
		two_index = Hash_Two_Function(index,j);
		i++;
		j++; 
		}
		
		if (del == -1)
		{
			table[two_index].day = hotel.day;
			table[two_index].month = hotel.month;
			table[two_index].year = hotel.year;
			table[two_index].longDay = hotel.longDay;
			table[two_index].size = hotel.size;
			table[two_index].telephone = hotel.telephone;
			table[two_index].fio = hotel.fio;
			table[two_index].state = 1;			
			size_all_non_nullptr++;
		}
		else
		{
			table[del].day = hotel.day;
			table[del].month = hotel.month;
			table[del].year = hotel.year;
			table[del].longDay = hotel.longDay;
			table[del].size = hotel.size;
			table[del].telephone = hotel.telephone;
			table[del].fio = hotel.fio;
			table[del].state = 1;
		}
		size++;
		return true;
	}
		
	bool Del(int value) //óäàëåíèå
	{
		int index = Hash_One_Function(value);
		int two_index = index;
		int i = 0;
		int j = 2;
		while(table[two_index].telephone != 0 && i<buffer_size)
		{
			if (table[two_index].telephone == value && table[two_index].state == 1)
			{
				table[two_index].state = 2;
				size--;
				return true;
			}
			two_index = Hash_Two_Function(index,j);
			i++;
			j++;
		}
		return false;
	}
	
	int Search(int value) //ïîèñê
	{
		int index = Hash_One_Function(value);
		int two_index = index;
		int i = 0;
		int j = 1;		
		while(table[two_index].telephone != 0 && i<buffer_size)
		{
			j++;
			if (table[two_index].telephone == value && table[two_index].state == 1)
			return two_index;
			two_index = Hash_Two_Function(index,j);
			i++;
		}
		return -1;
	}	
		
	void Write_Table() //âûïèñûâàíèå â ôàéë
	{
			ofstream file1;
			file1.open("output_1.txt", ios::out);
			if (file1.is_open())
			{
				file1<<buffer_size<<" Size "<<"\n";
				for(int i=0; i<buffer_size; i++)
				{
					if (table[i].state == 1)
					{
					file1<<i<<" : ";
					file1<<table[i].day<<"  ";
					file1<<table[i].month<<"  ";
					file1<<table[i].year<<"  ";
					file1<<table[i].longDay<<"  ";   
					file1<<table[i].size<<"   ";
					file1<<table[i].telephone<<"   ";
					file1<<table[i].fio<<"\n";
					}
					else
					{
						file1<<i<<" : ";
						file1<<"0"<<"\n";
					}
        		}
        		cout<<"File open!"<<endl;
        	}
       	file1.close();
	}
		
	~Hash() //äèñòðóêòîð
	{
		delete[] table;
	}; 
};

/*
text file:
5
0 0 0 0 0 56487 0
0 0 0 0 0 12874 0
0 0 0 0 0 96428 0
0 0 0 0 0 13746 0
0 0 0 0 0 65482 0
*/
