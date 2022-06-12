#include<iostream>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

class Graf
{
	private:
		int **distance; //ðàñòîÿíèå
		string *name; //íàçâàíèÿ
		int vertex; // êîëè÷åñòâî ðåáåð è âåðøèí
		bool *visited;
		bool *used;
		queue <int> peak;
		queue <int> track;
		
	public:
		Graf()
		{
			string letter_1, letter_2;
			int value,k,t;
			
			ifstream file;                 
			file.open("note.txt");
			if (file.is_open())           
			{
				cout<<"File open."<<endl;
				file>>vertex; //ñêîëüêî èìåí â ãðàôå
				
				visited = new bool[vertex];				
				name = new string[vertex];	//âûäåëÿåì ïàìÿòü äëÿ èìåí				
				distance = new int* [vertex]; //êîëè÷åñòâî ñòðîê â ìàñèâå				
				for (int i = 0; i<vertex; i++)
					distance[i] = new int[vertex]; //êîëè÷åñòâî ñòîëáöîâ â ìàñèâå
				
				for(int i=0; i<vertex; i++) //çàïîëíÿåì ìàñèâ èìåí
					file>>name[i];
				
				for(int i=0; i<vertex; i++)
					for(int j=0; j<vertex; j++)
						distance[i][j] = 0;
				
				while(!file.eof()) //  feof(file)
				{
					file>>letter_1;
					file>>letter_2;
					file>>value;
					for(int i=0; i<vertex; i++)
					{
						if(letter_1 == name[i]) k=i;
						if(letter_2 == name[i]) t=i;
					}
					distance[k][t] = value;
					distance[t][k] = value;
				}
			}
			else cout<<"File is not open";
			file.close(); 
		}
		
		void Dfs(int value)
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
		
		void Write_Dfs()
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
		
		void Prim(int value)
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
		
		void Write_prim()
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
		
		void Write_graf()
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
		
		~Graf()
		{
			for (int i = 0; i<vertex; i++) //óäâëåíèå ñîëáöîâ ìàñèâà
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
