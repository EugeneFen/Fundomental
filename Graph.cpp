#include<iostream>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

class Graf
{
	private:
		int **distance; //растояние
		string *name; //имена вершин
		int vertex; // сколько вершин
		bool *visited; 
		bool *used; 
		queue <int> peak; //для одхода
		queue <int> track; //для алгоритма Прима
		
	public:
		Graf() //конструктор
		{
			string letter_1, letter_2;
			int value,k,t;
			
			ifstream file;                 
			file.open("note.txt");
			if (file.is_open())           
			{
				cout<<"File open."<<endl;
				file>>vertex; //первая строка. число вершин
				
				visited = new bool[vertex];				
				name = new string[vertex];				
				distance = new int* [vertex];				
				for (int i = 0; i<vertex; i++)
					distance[i] = new int[vertex];
				
				for(int i=0; i<vertex; i++) //читаем вершины из файла
					file>>name[i];
				
				for(int i=0; i<vertex; i++)
					for(int j=0; j<vertex; j++)
						distance[i][j] = 0; //изначально растояние между вершинам 0
				
				while(!file.eof()) //  пока не конец файла читаем между какими вершинами какие растояния
				{
					file>>letter_1; //вершина 1
					file>>letter_2; //вершина 2
					file>>value; //растояние между вершиной 1 и вершиной 2
					for(int i=0; i<vertex; i++) //ищем в масиве вершина индекс вершины 1 и вершины 2
					{
						if(letter_1 == name[i]) k=i;
						if(letter_2 == name[i]) t=i;
					}
					distance[k][t] = value; //добавляем растояние в таблицу
					distance[t][k] = value;
				}
			}
			else cout<<"File is not open";
			file.close(); 
		}
		
		void Dfs(int value) //обход в глубину
		{
			peak.push(value);
			visited[value] = true;				
			for(int i=0; i<vertex; i++)
			{
				if((distance[value][i] != 0) and (!visited[i]))
				{
					Dfs(i);
				}
			}
		};
		
		void Write_Dfs() //запись обхода в файл
		{
			ofstream file;                                        
			file.open("output1.txt", ios::out);
			if (file.is_open())
			{				
				for(int i=0; i<vertex; i++)
				{
					if(!peak.empty())
					{
						int buff = peak.front();
						peak.pop();
						file<<name[buff]<<"  ";
					}
				}
				file<<"\n";
			}
			else cout<<"File is not open"<<endl;
			file.close();
		}
		
		void Prim(int value) //алгоритм Прима.
		{
			used = new bool[vertex];		
			for (int i=0; i<vertex; i++) used[i] = false;			
			used[value] = true;			
			for(int k = 0; k<vertex-1; k++)
			{
				int minx = -1 , miny = -1;
		        for(int i=0; i<vertex; i++)
		            if(used[i])
		                for(int j=0; j<vertex; j++)
		                    if(!used[j] && distance[i][j] > 0 && (miny == -1 || distance[i][j] < distance[miny][minx]))
		                    	miny = i, minx = j;
		                             
		        used[minx] = true;
		        //cout << miny << ' ' << minx << endl;
		        track.push(miny);
		        track.push(minx);
			}
		}
		
		void Write_prim() //вывод алгоритма Прима в файл
		{
			ofstream file;                                        
			file.open("output2.txt", ios::out);
			if (file.is_open())
			{				
				for(int i=0; i<vertex; i++)
				{
					int buff_1 = track.front();
					track.pop();
					int buff_2 = track.front();
					track.pop();
					file<<name[buff_1]<<"  "<<name[buff_2]<<"  "<<distance[buff_1][buff_2]<<"\n";
				}
				file<<"\n";
			}
			else cout<<"File is not open"<<endl;
			file.close();
		}
		
		void Write_graf() //вывод графа в файл
		{
			ofstream file;                                        
			file.open("output.txt", ios::out);
			if (file.is_open())
			{
				cout<<"File open"<<endl;
				file<<vertex<<" x "<<vertex<<"\n";
				
				file<<"    ";
				for(int i=0; i<vertex; i++)
					file<<name[i]<<" ";
				file<<"\n";
				
				for(int i=0; i<vertex; i++) //ñòðîêà
				{
					file<<name[i]<<"  ";
					for(int j=0; j<vertex; j++) //ñòîëáåö
					{
						file<<distance[i][j]<<"  ";
					}
					file<<"\n";
				}
			}
			else cout<<"File is not open"<<endl;
			file.close();
		}
		
		~Graf() //диструктор
		{
			for (int i = 0; i<vertex; i++) 
			{
			    delete[] distance[i];	    
			}
			delete[] distance;
			delete[] name;
			delete[] visited;
			delete[] used;
		}
};

int main()
{
	Graf a;
	a.Dfs(1);
	a.Write_Dfs();
	a.Prim(0);
	a.Write_prim();
	a.Write_graf();
	return 0;
};
