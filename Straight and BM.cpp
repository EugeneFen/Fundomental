#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct notebook 
{
	int day, month, year,longDay;  
	string telephone, fio, size;
	bool good;
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
			hotel[i].good = false;
		}
	}
	else {
		cout<<"file is not open";  
	}
	file.close();                  
};



void straight(notebook *hotel, string pattern, int k, int size_mas) 
{
	int size_pattern = pattern.length(); 
	 
	for(int i=0; i<size_mas; i++) 
	{
		int count = 0; 
		int size_hotel = hotel[i].fio.length();  	
		int buff = -1; 
		
		do {
			buff++;
			int correspond = 0; 
			while((correspond<size_pattern) && (hotel[i].fio[buff+correspond] == pattern[correspond])) 
			{
				correspond++;		
			}
			if(correspond == size_pattern) 
			{
				count++;
			}
	       } 
		   while(buff<size_hotel-size_pattern); 
		if(count == k) 
		{
			hotel[i].good = true;
		}
	} 	
		for(int i=0; i<size_mas; i++) 
	{
		int count = 0; 
		int size_hotel = hotel[i].size.length();  		
		int buff = -1; 
		
		do {
			buff++;
			int correspond = 0; 
			while((correspond<size_pattern) && (hotel[i].size[buff+correspond] == pattern[correspond])) 
			{
				correspond++;			
			}
			if(correspond == size_pattern) 
			{
				count++;
			}
	       } 
		   while(buff<size_hotel-size_pattern); 
		if(count == k) 
		{
			hotel[i].good = true;
		}
	}
};

int* preBmBc(string pattern) // good
{
	int pattern_size = pattern.length();	
	int* table = new int[255];
	
	for(int i=0; i<255; i++)
	{
		table[i] = pattern_size;
	}
	for(int i=0; i<pattern_size-1; i++)
	{
		table[(int)(pattern[i]) + 127] = pattern_size - i -1;
	}   
	return table;
};

int* suffixes(string pattern) 
{	
	int size_pattern = pattern.length(); 
	int* suff = new int[size_pattern];
	
   int f = 0; 
   suff[size_pattern - 1] = size_pattern; //last suff
   int g = size_pattern - 1; 
   
   for (int i = size_pattern - 2; i >= 0; i--) 
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
 
int* preBmGs(string pattern) 
{
	int size_pattern = pattern.length(); //m
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
 
 
void BM(notebook *hotel, string pattern, int k, int size_mas) 
{
	int size_pattern = pattern.length(); //m
	int* BmGs = new int[size_pattern];
	int* BmBc = new int[255];
	
	BmBc = preBmBc(pattern);
	BmGs = preBmGs(pattern);
   
   for(int a=0; a<size_mas; a++)
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
			hotel[a].good = true;
		}
   }  
};

int main()
{
	int number,k;                                       
	string shablon;
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
	notebook *hotel2=new notebook[number];
	readFile(hotel);                                  
	readFile(hotel2);  	
	
	cout<<"Enter pattern: ";
	cin>>shablon;
	cout<<"Enter k repetitions: ";
	cin>>k; 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	straight(hotel,shablon,k,number);
	BM(hotel2,shablon,k,number) ;

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ofstream file1;                                       
	file1.open("output_1.txt", ios::out);                 
	if (file1.is_open())
	{
		for(int i=0; i<number; i++)
		{
			if(hotel[i].good == true)	
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
	
	ofstream file2;                                        
	file2.open("output_2.txt", ios::out);                
	if (file2.is_open())
	{
		for(int i=0; i<number; i++)
		{
			if(hotel2[i].good == true)	
			{
				file2<<hotel2[i].day<<"  ";
        		file2<<hotel2[i].month<<"  ";
        		file2<<hotel2[i].year<<"  ";
        		file2<<hotel2[i].longDay<<"  ";
        		file2<<hotel2[i].size<<"  ";
        		file2<<hotel2[i].telephone<<"  ";
        		file2<<hotel2[i].fio<<"\n";
			}	
		}
		cout<<"File open!"<<endl;
	}
	file2.close();                                         
  	
	delete[] hotel; 
	delete[] hotel2;
	return 0;	
}

/*
Teat text:
0 0 0 0  single 0 Fen_Evgenia_Vladimirovna
0 0 0 0  four-seater 0 Strelnikova_Elena_Dmitrovna
*/
