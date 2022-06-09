#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Notebook
{
	int day,month,year,longDay,size,telephone,state;
	string fio;
};

void Read_File(Notebook *hotel)
{
	int Size;
	ifstream file;
	file.open("note.txt");
	if (file.is_open())
	{
		cout<<"Open"<<endl;
		file>>Size;				
		for(int i=0; i<Size; i++)
	{
		file>>hotel[i].day;
		file>>hotel[i].month;
	    file>>hotel[i].year;
		file>>hotel[i].longDay;
		file>>hotel[i].size;
		file>>hotel[i].telephone;
		file>>hotel[i].fio;
		hotel[i].state = true;
	}
	}
	else 
	{
		cout<<"file is not open";
	}
	file.close();
}
		
void Write_Hotel(Notebook *Hotel, int size)
{
ofstream file2;
			file2.open("output_2.txt", ios::out);
			if (file2.is_open())
			{
				for(int i=0; i<size; i++)
				{
					file2<<Hotel[i].day<<" ";
					file2<<Hotel[i].month<<" ";
					file2<<Hotel[i].year<<" ";
					file2<<Hotel[i].longDay<<" ";   
					file2<<Hotel[i].size<<"  ";
					file2<<Hotel[i].telephone<<"  ";
					file2<<Hotel[i].fio<<"\n";
        		}
        		cout<<"File open!"<<endl;
        	}
        	file2.close();
}
		
class Hash
{
	Notebook *table;
	int size; //ñêîëüêî ýë äîáàâëåííî
	const double rehash_size = 0.75;
	int buffer_size; //ðàçìåð ñàìîãî ìàññèâà
	int size_all_non_nullptr;	
  	
  	int Hash_One_Function(int key) //ïåðâèÿíàÿ õåø-ôóíêöèÿ
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

void Start(Hash a, Notebook *hotel, int size_hotel)
{
	for(int i=0; i<size_hotel; i++)
	{
		a.Add(hotel[i]);
	}
	int N = 0;
	do
	{
		cout<<endl;
	cout<<"Choose an action:"<<endl;
	cout<<"1 - Add"<<endl;
	cout<<"2 - Search"<<endl;
	cout<<"3 - Delete"<<endl;
	cout<<"4 - Write Table in file"<<endl;
	cout<<"5 - Exit"<<endl;
	cin>>N;
	
	switch(N)
	{
	case 1: 
	{
	Notebook date;
	cout<<"Enter the variable you want to add:  ";
	cin>>date.telephone;
	if (a.Add(date)) cout<<"Good"<<endl;
	else cout<<"Not good"<<endl;
	}
	break;
	
	case 2: 
	{
	int snils;
	cout<<"Enter the variable you want to search: ";
	cin>>snils;
	if (a.Search(snils) >= 0) cout<<"Index variable in hash table: "<<a.Search(snils)<<endl;
	else cout<<"this variable is not in the table!"<<endl;
	}
	break;
	
	case 3:
	{
	int memories;
	cout<<"Enter the variable you want to delete: ";
	cin>>memories;
	if (a.Del(memories)) cout<<"Variable removed"<<endl;
	else cout<<"Variable not deleted"<<endl;
	}
	break;
	
	case 4:
	{
		a.Write_Table();
		cout<<"Ok"<<endl;
	}
	break;	
	}
	} while (N != 5);
}

int main()
{
	int number;
	ifstream file1;
	file1.open("note.txt");
	if (file1.is_open())
	{
		file1>>number;
	}
	else
	{
		cout<<"file is not open!";
	}
	file1.close();	
	Notebook *hotel = new Notebook[number];	
	Read_File(hotel);	
	Write_Hotel(hotel,number);
	
	Hash a(number);
	Start(a,hotel,number);
	
	delete[] hotel;
	return 0;
}
