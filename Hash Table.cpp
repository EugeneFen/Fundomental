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
		
class Hash
{
	Notebook *table;
	int size; //ñêîëüêî ýë äîáàâëåííî
	int buffer_size; //ðàçìåð ñàìîãî ìàññèâà
  	
  	int Hash_One_Function(int key) //ïåðâèÿíàÿ õåø-ôóíêöèÿ
	{
		return (key % buffer_size);
	}	
	
	int Hash_Two_Function(int index, int j)
	{
		return ((index+j*1) % buffer_size);
	} 
	
	int Collision(int index, int buff)
	{
		int i=0;
		int j =1;
		int two_index = index;
		while (i<buffer_size)
		{
			two_index = Hash_Two_Function(index,j);
			cout<<two_index<<" :index add"<<endl;
			if (table[two_index].state == 0) return two_index;
			else if (table[two_index].state == 2)
			{
				if(Search(buff) < 0)
				{
					return two_index;
				}			
				else return -1;
			}						
			j++;
			i++;
		}
		return -1;
	}
	
	int Decision(int index, int value)
	{
		int two_index = index;
		int i = 0;
		int j = 1;
		while(i<buffer_size)
		{
			two_index = Hash_Two_Function(index,j);
			if (table[two_index].telephone == value && table[two_index].state == 1) return two_index;			
			i++;
			j++;
			cout<<two_index<<" index del"<<endl;
		}
		return -1;
	}
	
	public:
			
	Hash(int value) //êîíñòðóêòîð
	{
		buffer_size = value;
		table = new Notebook[buffer_size];
		
		for (int i=0; i<buffer_size; i++)
		{
			table[i].day = table[i].month = table[i].year = table[i].longDay = table[i].size = table[i].telephone = table[i].state = 0;
			table[i].fio = "_";
		}
	}
		
	bool Add(Notebook hotel) //äîáàâëåíèå
	{		
		int index = Hash_One_Function(hotel.telephone);
		cout<<index<<":index first"<<endl;
		
		if (table[index].telephone == hotel.telephone && table[index].state == 1) return false;
		else
		if (table[index].state == 1)
		{
			int two_index = Collision(index, hotel.telephone);
			if (two_index >= 0 )
			{
				table[two_index].day = hotel.day;
				table[two_index].month = hotel.month;
				table[two_index].year = hotel.year;
				table[two_index].longDay = hotel.longDay;
				table[two_index].size = hotel.size;
				table[two_index].telephone = hotel.telephone;
				table[two_index].fio = hotel.fio;
				table[two_index].state = 1;	
				return true;
			}
			else return false;
		}
		else
		if(table[index].state == 0)
		{
			cout<<index<<" :index 0"<<endl;
			table[index].day = hotel.day;
			table[index].month = hotel.month;
			table[index].year = hotel.year;
			table[index].longDay = hotel.longDay;
			table[index].size = hotel.size;
			table[index].telephone = hotel.telephone;
			table[index].fio = hotel.fio;
			table[index].state = 1;			
			return true;
		}
		else 
		if(table[index].state == 2)
		{
			cout<<index<<" :index 2"<<endl;
				if(Search(hotel.telephone) < 0)
				{
					cout<<" yes "<<endl;
					table[index].day = hotel.day;
					table[index].month = hotel.month;
					table[index].year = hotel.year;
					table[index].longDay = hotel.longDay;
					table[index].size = hotel.size;
					table[index].telephone = hotel.telephone;
					table[index].fio = hotel.fio;
					table[index].state = 1;
					return true;
				}			
				else 
				{
					cout<<" No "<<endl;
					return false;
				}
		}
		return false;
	}
		
	bool Del(int value) //óäàëåíèå
	{
		int index = Hash_One_Function(value);
		cout<<index<<" index two "<<endl;
		if (table[index].telephone == value && table[index].state == 1)
			{
				table[index].state = 2;
				return true;
			}
			else
			{
				int two_index = Decision(index, value);
				if (two_index >= 0)
				{
					table[two_index].state = 2;
					return true;
				}
				else false;
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
					file1<<i<<" : ";
					file1<<table[i].day<<"  ";
					file1<<table[i].month<<"  ";
					file1<<table[i].year<<"  ";
					file1<<table[i].longDay<<"  ";   
					file1<<table[i].size<<"   ";
					file1<<table[i].telephone<<"   ";
					file1<<table[i].fio<<"  ";
					file1<<table[i].state<<"\n";
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
		if (hotel[i].telephone != 0) a.Add(hotel[i]);
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
	delete[] table;
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
