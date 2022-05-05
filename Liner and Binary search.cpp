#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct notebook 
{
	int day,month,year,longDay,size,count;
	string telephone, fio;
};

void readFile(notebook *hotel)
{
	int Size;                      
	ifstream file;                 
	file.open("note.txt");
	if (file.is_open())           
	{
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
			hotel[i].count = 0;
		}
	}
	else {
		cout<<"file is not open";  
	}
	file.close();                  
};

bool Check (notebook Hotel, notebook Hotel2)
{
	if (Hotel.longDay == Hotel2.longDay)
	{
    	if (Hotel.year == Hotel2.year)
    	{
    		if (Hotel.month == Hotel2.month)
    		{
    			if (Hotel.day == Hotel2.day)
    			{
						return false;			
    			}
    			else if (Hotel.day < Hotel2.day) return true;
    			else return false;
    		}
    		else if (Hotel.month < Hotel2.month) return true;
     		else return false;
    	}
    	else if (Hotel.year < Hotel2.year) return true;
     	else return false;
    }
    else if (Hotel.longDay < Hotel2.longDay) return true;
	else return false;


}

void qsortRecursive(notebook *hotel,int m, int l ) //быстрая  
{    
    int i = m; //указатель в начало масива
    int j = l; //указатель в конец масива
    notebook support = hotel[l]; //опорный
    
    do {
       //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть        
        while(Check(hotel[i],support)) i++;      
        while(Check(support,hotel[j])) j--;      
    	if(i<=j)
      	{
            notebook buff = hotel[i]; hotel[i] = hotel[j]; hotel[j] = buff;
			i++;
			j--;
		}

	}	   
	while (i <= j); 
       
    if(m < j) 
    { 
        qsortRecursive(hotel,0,j);  //"Левый кусок"
    }
    if (i < l) 
	{   
        qsortRecursive(hotel,i,l); //"Правый кусок"
    } 
}

int Liner_search(notebook *hotel, int a, int key)
{
	int count = 0;
    for (int i = 0; i < a; i++)
        if (hotel[i].longDay == key)
        {
        	count++;
        	hotel[i].count = count;
        	return i;
		}
		else count++;
            
    return -1;
}

int Binary_search(notebook *hotel, int l, int a, int key, int count)
{
	if (a >= l)
	{
		int mid = l + (a - l) / 2;
		
		if (hotel[mid].longDay == key)
		{
			count ++;
			hotel[mid].count = count;
			return mid;
		}
         
            
        if (hotel[mid].longDay > key)
        {
        	count++;
        	return Binary_search(hotel, l, mid - 1, key,count);
		}
		else
		{
			count++;
			return Binary_search(hotel, mid + 1, a, key, count);
		}       
	}
	
	return -1;
}

void Search_linear(notebook *hotel, int a,int key)
{
///////////////////////////////////////////////////////////////////////////////////
	int Result = Liner_search(hotel,a,key);	
///////////////////////////////////////////////////////////////////////////////////

	ofstream file;                                        
	file.open("output_1.txt", ios::out);                  
	if (file.is_open())
	{
		if (Result>= 0)
		{
			file<<"Result: "<<Result<<"\n";
			file<<"Steps: "<<hotel[Result].count<<"\n";
		}
		else
		{
			file<<"Result: not"<<"\n";
			file<<"Steps: not"<<"\n";
		}
		cout<<"File open!"<<endl;
	}
	file.close();
};

void Search_Binary(notebook *hotel, int a,int key)
{
///////////////////////////////////////////////////////////////////////////////////
	int count = 0;
	int Result = Binary_search(hotel,0,a-1,key,count);	
///////////////////////////////////////////////////////////////////////////////////

	ofstream file;                                        
	file.open("output_2.txt", ios::out);                  
	if (file.is_open())
	{
		
		if (Result>= 0)
		{
			file<<"Result: "<<Result<<"\n";		
			file<<"Steps: "<<hotel[Result].count<<"\n";
		}
		else 
		{
			file<<"Result: not"<<"\n";
			file<<"Steps: not"<<"\n";
		}
		cout<<"File open!"<<endl;
	}
	file.close();
};


int main()
{
    setlocale (LC_ALL,"Rus");    
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
	
	int key;
	
	notebook *hotel=new notebook[number];
	notebook *hotel2=new notebook[number];
	readFile(hotel); 
	readFile(hotel2); 
	
	qsortRecursive(hotel,0,number - 1);
	qsortRecursive(hotel2,0,number - 1);
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  		
 cout<<"Введите искомое число: "<<endl;
 cin>>key;

 Search_linear(hotel, number,key);
 Search_Binary(hotel2,number,key);
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  	
	delete[] hotel; //удаляем масив
	delete[] hotel2;
	return 0;
}

/* Text file:
6
5 0 0 6  1 0 Fen_Evgenia_Vladimirovna
6 0 0 12  4 0 Strelnikova_Elena_Dmitrovna
9 0 0 5  2 0 Fen_Vladir_Georgievich
12 0 0 1  3 0 Kiseleva_Tatiyana_Valentinovna
3 0 0 7  4 0 Fen_Georgiy_Valentinovich
7 0 0 3  2 0 Kiseleva_Rita_Konstantinovna
*/
