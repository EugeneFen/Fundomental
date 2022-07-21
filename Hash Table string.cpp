#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
version 2
*/
		
class Hash
{
	struct Notebook
	{
		string website, fio, country;
		int state;
	};
	
	Notebook *table; //таблица
	int size; //сколько эл добавленно
	int buffer_size; //размер самого массива
  	
  	int Hash_One_Function(string key) //первияная хеш-функция  ++++
	{
		int size_key = key.length();
		int summ = 0;
		int buff;
		for(int i=0; i<size_key; i++)
		{
			buff = static_cast<int> (key[i]) + 128; //зачение буквы
			summ += buff;
		}
		return (summ % buffer_size);
	}	
	
	int Hash_Two_Function(int index, int j) //++++
	{
		return ((index+j*1) % buffer_size);
	} 
	
	int Collision(int index, string buff) //++++
	{
		int i= 0;
		int j = 1;
		int two_index = index;
		while (i<buffer_size)
		{
			two_index = Hash_Two_Function(index,j);
			
			cout<<two_index<<" :index add"<<endl;
			
			if (table[two_index].fio == buff) return -1;
			else if (table[two_index].state == 0) return two_index;
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
	
	int Decision(int index, string value) //-----
	{
		int two_index = index;
		int i = 0;
		int j = 1;
		while(i<buffer_size)
		{
			two_index = Hash_Two_Function(index,j);
			if (table[two_index].fio == value && table[two_index].state == 1) return two_index;			
			i++;
			j++;
			
			cout<<two_index<<" index del"<<endl;
		}
		return -1;
	}
	
	
	public:
			
	Hash() //конструктор ++++
	{
		cout<<"Start"<<endl;
		buffer_size = 20; //размер таблицы
		table = new Notebook[buffer_size]; //сама таблица
		
		for (int i=0; i<buffer_size; i++)
		{
			table[i].country = table[i].fio = table[i].website = "_"; //заполняем таблицу пробелами
			table[i].state = 0;
		}
	}
		
	bool Add(string fio_v, string website_v, string country_v) //добавление  !!!!!!!!!!!!!!!  ++++
	{		
		int index = Hash_One_Function(fio_v); //вычисляем место для эл.
		
		cout<<index<<":index first    "<<fio_v<<endl;
		
		if (table[index].fio == fio_v && table[index].state == 1) return false;
		else
		if (table[index].state == 1)
		{
			
			int two_index = Collision(index, fio_v);
			cout<<two_index<<" :index -1    "<<table[two_index].fio<<endl;
			if (two_index >= 0)
			{
				table[two_index].website = website_v;
				table[two_index].fio = fio_v;
				table[two_index].country = country_v;
				table[two_index].state = 1;	
				return true;
			}
			else return false;
		}
		else
		if(table[index].state == 0)
		{
			cout<<index<<" :index 0"<<endl;
			
			table[index].website = website_v;
			table[index].fio = fio_v;
			table[index].country = country_v;
			table[index].state = 1;	
			return true;
		}
		else 
		if(table[index].state == 2)
		{
			cout<<index<<" :index 2"<<endl;
				if(Search(fio_v) < 0)
				{
					cout<<" yes "<<endl;
					table[index].website = website_v;
					table[index].fio = fio_v;
					table[index].country = country_v;
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
		
	bool Del(string fio_v) //удаление  ++++
	{
		int index = Hash_One_Function(fio_v);
		
		cout<<index<<" index two "<<endl;
		
		if (table[index].fio == fio_v && table[index].state == 1)
			{
				table[index].state = 2;
				return true;
			}
			else
			{
				int two_index = Decision(index, fio_v);
				if (two_index >= 0)
				{
					table[two_index].state = 2;
					return true;
				}
				else false;
			}
		return false;
	}
	
	int Search(string fio_v) //поиск ++++
	{
		int index = Hash_One_Function(fio_v);
		int two_index = index;
		int i = 0;
		int j = 1;
		while(table[two_index].fio != "_" && i<buffer_size)
		{
			
			cout<<two_index<<" index 8"<<endl;
			
			if (table[two_index].fio == fio_v && table[two_index].state == 1) return two_index;
			two_index = Hash_Two_Function(index,j);
			j++;
			i++;
		}
		return -1;
	}	
		
	void Write_Table() //выписывание в файл
	{
		cout<<" yes "<<endl;
			ofstream file1;
			file1.open("output_1.txt", ios::out);
			if (file1.is_open())
			{
				for(int i=0; i<buffer_size; i++)
				{
					if(table[i].fio != "_")
					{
						file1<<table[i].website<<"\n";
						file1<<table[i].fio<<"\n";
						file1<<table[i].country<<"\n";
					}
        		}
        		cout<<"File open!"<<endl;
        	}
       	file1.close();
	}
	
	void Read_File()
	{
		int Size;
		ifstream file;
		file.open("Author.txt");
		if (file.is_open())
		{
			cout<<"Open"<<endl;
						
			string fio_v, website_v, country_v;
				
			while(!file.eof())
			{
				getline(file, website_v);
				getline(file, fio_v);
			    getline(file, country_v);
			    
			    Add(fio_v, website_v, country_v);		    
			}
		}
		else 
		{
			cout<<"file is not open";
		}
		file.close();
	}
	
	void write_element(int index)
	{
		cout<<table[index].website<<"  "<<table[index].fio<<"  "<<table[index].country<<endl;
	}
			
	~Hash() //деструктор
	{
		cout<<" lbc "<<endl;
		delete[] table;
	}
};
	
int main()
{
	setlocale (LC_ALL,"Rus");
	Hash a;
	
	a.Read_File();
	a.Write_Table();
	int r = a.Search("Никулин Юрий Владимирович");
	if (r>0) a.write_element(r);
	else cout<<"No"<<endl;
	
	return 0;
}
