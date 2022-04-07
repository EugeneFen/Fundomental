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

int* BM_table(string pattern)
{
	int alphabet = 255; 
	int pattern_size = pattern.length(); 
	int *shift = new int[alphabet]; 
	
	for (int i = 0; i < alphabet; i++) 
	{
		shift[i] = pattern_size;
	}
	
	for (int i = 0; i < pattern_size - 1; i++)
	{
		
		shift[(int)(pattern[i]) + 127] = pattern_size - i - 1;
	}
	
	return(shift);
}

void BM(notebook *hotel2, string pattern, int k, int* shift, int size_mas) 
{	

	int pattern_size = pattern.length(); 
	int count = 0;
	
	for (int i = 0; i < size_mas; i++) 
	{		
		int line_size = hotel2[i].fio.length(); 
		int t = 0;
		while (t <= (line_size - pattern_size)) 
		{
			int j = pattern_size - 1; 

			while (j >= 0 && pattern[j] == hotel2[i].fio[t + j]) 
				j--;		
			

			if (j < 0)
			{
				count++; 
				t++; 
				int d1;

				if (t + pattern_size < line_size) 
				{
					d1 = pattern_size - shift[hotel2[i].fio[t + pattern_size] + 127]; 
					
				}
				else d1 = 1; 
				
				t += d1; 
			}
			else 
			{
				if (1 > j - shift[(int)(hotel2[i].fio[t + j])+ 127]) t +=1;
				else t += j - shift[(int)(hotel2[i].fio[t + j])+ 127];
			};
			
		}

		if(count == k)
		{
			hotel2[i].good = true;
		}
		count = 0;
	};
	
	
	count = 0;	
	for (int i = 0; i < size_mas; i++) 
	{

		int line_size2 = hotel2[i].size.length();
		int t = 0; //

		while (t <= (line_size2 - pattern_size)) 
		{
			int j = pattern_size - 1; 

			while (j >= 0 && pattern[j] == hotel2[i].size[t + j]) 
				j--;		
			

			if (j < 0)
			{
				count++; 
				t++; 
				int d1;

				if (t + pattern_size < line_size2) 
				{
					d1 = pattern_size - shift[hotel2[i].size[t + pattern_size] + 127]; 
				
				}
				else d1 = 1;
				
				t += d1; 
			}
			else 
			{
				if (1 > j - shift[(int)(hotel2[i].size[t + j])+ 127]) t +=1;
				else t += j - shift[(int)(hotel2[i].size[t + j])+ 127];
			};
			
		}

		if(count == k) 
		{
			hotel2[i].good = true;
		}
		count = 0;
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
	
	int* rt = new int[255];
    rt = BM_table(shablon);
	BM(hotel2,shablon,k,rt,number);
	
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
  	
  	delete[] rt;
	delete[] hotel; 
	delete[] hotel2;
	return 0;	
}
