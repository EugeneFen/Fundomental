#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
Реализовать два алгоритма поиска подстроки в строке: Прямой и Бойера-Мура, 
при этом подстрока должна содержаться в строке k-раз и подстрока должна находиться хотя бы в одном поле.
Поиск происходит по двум полям: ФИО и тип номера.
*/

struct notebook                                     //данны хранящиеся в файле
{
	int day, month, year,longDay;  
	string telephone, fio, size;
};

void readFile(notebook *hotel)                       //чтение из файла данных
{
	int Size;                      
	ifstream file;                 
	file.open("note.txt");                       //открываем файл для чтения
	if (file.is_open())                          //если файл открыт, то начинаем чтение
	{
		file>>Size;                          //первая строка в файле - это сколько у нас записей
		for(int i=0; i<Size; i++)            //циклом читаем данные, которые расположены через пробел
		{   
			file>>hotel[i].day;	
			file>>hotel[i].month;  
			file>>hotel[i].year;
			file>>hotel[i].longDay;
			file>>hotel[i].size;
			file>>hotel[i].telephone; 
			file>>hotel[i].fio;          //после последнего слова нет пробела
		}
	}
	else                                         //если файл небыл открыт, ты выдаем сообщение об ошибке
	{
		cout<<"file is not open";  
	}
	file.close();                                //обязательно закрываем файл
};

bool straight_FIO(notebook *hotel, string pattern, int k, int a, int size_pattern) //прямой поиск по фамилии
{	
		int count = 0;                                  //счетчик шаблонов в строке
		int size_hotel = hotel[a].fio.length();  	//колличество символов в "Фамилия" (или размер "Фамилия")
		int buff = -1;                                  //с помощью нее смотрим, чтобы последнии символы шаблона невышли за границу строки "фамилия"
		
		do {
			buff++;
			int correspond = 0;                     //счетчик совпадающих символов в строках "Фамилия" и шаблон
			while((correspond<size_pattern) && (hotel[a].fio[buff+correspond] == pattern[correspond])) 
			{
				correspond++;		        //проходим по шаблону и сравниваем каждый его символ с символами строки "Фамилия"
			}
			if(correspond == size_pattern)          //если нашли совпадение шаблона и строки "Фамилия", то увеличиваем счетчик шаблонов
			{
				count++;
			}
	           } 
		while(buff<size_hotel-size_pattern);            //пока не дошли до конца строки
	
		if(count == k)                                  //если нашли нужное колличество шаблонов с строке, то истина
		{
			return true;
		}
		else return false;	
};

bool straight_Size(notebook *hotel, string pattern, int k, int a, int size_pattern) //прямой поиск
{
		int count = 0;                                 //счетчик шаблонов в строке
		int size_hotel = hotel[a].size.length();       //колличество символов в "Тип номера" (или размер "Тип номера")
		int buff = -1;                                 //с помощью нее смотрим, чтобы последнии символы шаблона невышли за границу строки "Тип номера"
		
		do {
			buff++;
			int correspond = 0;                    //счетчик совпадающих символов в строках "Тип номера" и шаблон
			while((correspond<size_pattern) && (hotel[a].size[buff+correspond] == pattern[correspond])) 
			{
				correspond++;		       //проходим по шаблону и сравниваем каждый его символ с символами строки "Тип номера"
			}
			if(correspond == size_pattern)         //если нашли совпадение шаблона и строки "Тип номера", то увеличиваем счетчик шаблонов
			{
				count++;
			}
	       } 
		   while(buff<size_hotel-size_pattern);        //пока не дошли до конца строки
		if(count == k)                                 //если нашли нужное колличество шаблонов с строке, то истина
		{
			return true;
		}
		else return false;
};

int* preBmBc(string pattern) // таблица сдвигов
{
	int pattern_size = pattern.length();	                      //размер шаблона (колличесво символов в строке 
	int* table = new int[255];                                    //динамическая таблица для всех символов алфавита
	
	for(int i=0; i<255; i++)
	{
		table[i] = pattern_size;                              //заполнение таблицы
	}
	for(int i=0; i<pattern_size-1; i++)
	{
		table[(int)(pattern[i]) + 127] = pattern_size - i -1; //заполнение тех символов, которые есть в шаблоне
	}   
	return table;
};

int* suffixes(string pattern) //таблица суффиксов
{	
	int size_pattern = pattern.length();                                   //размер шаблона (колличесво символов в строке 
	int* suff = new int[size_pattern];                                     //динамическая таблица для всех символовов шаблона
	
   int f = 0; 
   suff[size_pattern - 1] = size_pattern;                                      //последняя ячека таблицы равна размеру шаблона
   int g = size_pattern - 1;                                                   //равно номеру последнего эл в таблице
   
   for (int i = size_pattern - 2; i >= 0; i--)                                 //от предпоследнего элемента шаблона до первого элемента
   {
      if (i > g && suff[i + size_pattern - 1 - f] < i - g)
         suff[i] = suff[i + size_pattern - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && pattern[g] == pattern[g + size_pattern - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }   
   return suff;
}
 
int* preBmGs(string pattern) //таблица префиксов
{
	int size_pattern = pattern.length(); 
	int* bmGs = new int[size_pattern];
	int* suffix = new int[size_pattern]; 
   suffix = suffixes(pattern);
 
   for (int i = 0; i < size_pattern; i++)
      bmGs[i] = size_pattern;
	     
   for (int i = size_pattern - 1; i >= 0; i--)
      if (suffix[i] == i + 1)
         for (int j=0; j < size_pattern - 1 - i; j++)
            if (bmGs[j] == size_pattern)
               bmGs[j] = size_pattern - 1 - i;
   for (int i = 0; i <= size_pattern - 2; i++)
      bmGs[size_pattern - 1 - suffix[i]] = size_pattern - 1 - i;
      
    return bmGs;
} 
 
bool BM_FIO(notebook *hotel, string pattern, int k, int a, int *BmGs, int *BmBc, int size_pattern) //БМ 
{
   	int count = 0;
    int size_hotel = hotel[a].fio.length(); 		
    int j = 0;
    
    while (j <= size_hotel - size_pattern) 
    {
    	int i = size_pattern - 1;
    	while(i >= 0 && pattern[i] == hotel[a].fio[i + j]) i--;     
      	if (i < 0) 
		  {
		  	j += BmGs[0];
		  	count++;
		  }
        else if (BmGs[i] > BmBc[(int)(hotel[a].fio[i + j]+127)] - size_pattern + 1 + i) j = j + BmGs[i];
        else j = j + BmBc[(int)(hotel[a].fio[i + j]+127)] - size_pattern + 1 + i;
	     
    }
    if(count == k) 
	{
		return true;
	}
	else return false;
};

bool BM_Size(notebook *hotel, string pattern, int k, int a,int *BmGs,int *BmBc,int size_pattern) //БМ
{   
   	int count = 0;
    int size_hotel = hotel[a].size.length(); 		
    int j = 0;
    
    while (j <= size_hotel - size_pattern) 
    {
    	int i = size_pattern - 1;
    	while(i >= 0 && pattern[i] == hotel[a].size[i + j]) i--;     
      	if (i < 0) 
		  {
		  	j += BmGs[0];
		  	count++;
		  }
        else if (BmGs[i] > BmBc[(int)(hotel[a].size[i + j]+127)] - size_pattern + 1 + i) j = j + BmGs[i];
        else j = j + BmBc[(int)(hotel[a].size[i + j]+127)] - size_pattern + 1 + i;
	     
    }
    if(count == k) 
	{
		return true;			
	}
	else return false;
 
};

void straight(notebook *hotel, string pattern, int k, string Pattern, int K, int size_mas) //прямой поиск
{
	int size_pattern = pattern.length();                           //размер шаблона для строки "ФИО"
	int size_pattern2 = Pattern.length();                          //размер шаблона для строки "Тип номера"
	
	ofstream file1;                                       
	file1.open("output_1.txt", ios::out);
	if (file1.is_open())
	{
		for(int i=0; i<size_mas; i++)                          //от 0 до конца колличества записей
		{
			if(straight_FIO(hotel,pattern,k,i,size_pattern) || straight_Size(hotel,Pattern,K,i,size_pattern2))		
			{
				file1<<hotel[i].day<<"  ";
        		file1<<hotel[i].month<<"  ";
        		file1<<hotel[i].year<<"  ";
        		file1<<hotel[i].longDay<<"  ";
        		file1<<hotel[i].size<<"  ";
        		file1<<hotel[i].telephone<<"  ";
        		file1<<hotel[i].fio<<"\n";
			}	
		}
		cout<<"File open!"<<endl;
	}
	file1.close();
};

void BM(notebook *hotel, string pattern, int k, string Pattern, int K, int size_mas) //БМ поиск
{
	int size_pattern = pattern.length(); //
	int* BmGs = new int[size_pattern];                      //выделение памяти
	int* BmBc = new int[255];                               //выделение памяти
	
	int size_pattern2 = Pattern.length(); //
	int* BmGs2 = new int[size_pattern2]; 
	int* BmBc2 = new int[255]; 
	
	BmBc = preBmBc(pattern); //создаем первую таблицу
	BmGs = preBmGs(pattern); //создаем вторую таблицу
	
	BmBc2 = preBmBc(Pattern); //создаем первую таблицу
	BmGs2 = preBmGs(Pattern); //создаем вторую таблицу
	
	ofstream file2;                                        
	file2.open("output_2.txt", ios::out);                  
	if (file2.is_open())
	{
		for(int i=0; i<size_mas; i++)
		{
			if(BM_FIO(hotel,pattern,k,i,BmGs,BmBc,size_pattern) || BM_Size(hotel,Pattern,K,i,BmGs2,BmBc2,size_pattern2))	
			{
				file2<<hotel[i].day<<"  ";
        		file2<<hotel[i].month<<"  ";
        		file2<<hotel[i].year<<"  ";
        		file2<<hotel[i].longDay<<"  ";
        		file2<<hotel[i].size<<"  ";
        		file2<<hotel[i].telephone<<"  ";
        		file2<<hotel[i].fio<<"\n";
			}	
		}
		cout<<"File open!"<<endl;
	}
	file2.close();
};

int main()
{
	int number,k,K;                                      
	string shablon,Shablon;
	ifstream file;                                   
	file.open("note.txt");
	if (file.is_open())
	{
        file>>number;                                
	}
	else 
	{
	    cout<<"File is not open!";
	}
	file.close();                                      
	                                                   
	notebook *hotel=new notebook[number];
	readFile(hotel);                                   	
	
	cout<<"Enter pattern for last name: ";
	cin>>shablon;
	cout<<"Enter k repetitions: ";
	cin>>k; 
	cout<<"Enter pattern for room type: ";
	cin>>Shablon;
	cout<<"Enter k repetitions: ";
	cin>>K; 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	straight(hotel,shablon,k,Shablon,K,number);
	BM(hotel,shablon,k,Shablon,K,number);
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                                                 
  	
	delete[] hotel;
	return 0;	
}
/*
Teat text:
2
0 0 0 0  single 0 Fen_Evgenia_Vladimirovna
0 0 0 0  four-seater 0 Strelnikova_Elena_Dmitrovna
*/
