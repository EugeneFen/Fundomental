#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct list //обьявление списка
{
	int day,month,year,longDay,size; 
	string telephone;
	struct list *next; //
	struct list *prev; //
};

list *Head, *Tail;

void readFile() //создание списка
{
	int one,two,three,four,five;
	string six;
	
	int Size; //размер списка. берется из файла
	ifstream file;
	file.open("note.txt");
	if (file.is_open())
	{
		file>>Size;		
    	
		for(int i=0; i<Size; i++)
		{
			list *additional = new list; //
			file>>one;			
			additional->day = one;							
			file>>two;  
			additional->month = two;
			file>>three;
			additional->year = three;
			file>>four;
			additional->longDay = four;
			file>>five;
			additional->size = five;
			file>>six; 
			additional->telephone = six;
			additional->next = NULL;
			additional->prev = NULL; //
			if(Head==NULL)
			{
				Head = additional;
				Tail = additional;
			}
			else 
			{
				additional->prev = Tail;
				Tail->next = additional;
				Tail = additional;
			}
		}
	}
	else {
		cout<<"file is not open";
	}
	file.close();	
};

void WriteStruct() //вывод в файл
{
	int size;
	ifstream file1;
	file1.open("note.txt");
	if (file1.is_open())
	{
		file1>>size;
	}
	else cout<<"error  ";
	file1.close();
	
	ofstream file;
	file.open("output.txt", ios::out); 
	if (file.is_open())
	{
		for(int i=0; i<size; i++)
		{
			if(Head == NULL )
			{
				cout<<"Not elements"<<endl;
			}	
			else
			{	    		
				file<<Head->day<<"  ";
				file<<Head->month<<"  ";
				file<<Head->year<<"  ";
				file<<Head->longDay<<"  ";
				file<<Head->size<<"  ";
				file<<Head->telephone<<"\n";
				Head = Head->next;
			}
		}				
	}
	else cout<<"output not open  "<<endl;
	file.close();
}

bool Check (list *Tree, list *Tree2) //сравнение значений
{
	if (Tree->year == Tree2->year)
	{
		if (Tree->month == Tree2->month)
		{
			if (Tree->day == Tree2->day)
			{
				if (Tree->longDay == Tree2->longDay)
				{
					if (Tree->size == Tree2->size)
					{
						return false;
					}
					else if (Tree->size < Tree2->size) return true;
					else return false;
				}
				else if (Tree->longDay < Tree2->longDay) return true;
				else return false;
			}
			else if (Tree->day < Tree2->day) return true;
			else return false;
		}
		else if (Tree->month < Tree2->month) return true;		  
		else return false;
	}
	else if (Tree->year < Tree2->year) return true;
	else return false;
	
}

void myShakerSort()  //шейкерная сортировка
{
	list *leftMark = Head;
	list *RightMark = Tail->prev;
	
//	while (leftMark<number)
//	{ 		
list *i = leftMark; //
	while (i != RightMark) //
		{			
			if (Check(i->next,i)) //
			{
				if(i == Head)
				{
					cout<<"qqqq  "<<endl;
					list *woot = i->next; 
					list *poot = woot->next;
					i->next = poot;
					i->prev = woot;
					poot->prev = i;
					woot->prev = NULL;
					woot->next = i;										
					i = woot;
					Head = i; 
					woot = NULL;
					poot = NULL;
					
				}
				else 
				{
					if( i == Tail) //îøèáêà
					{
						cout<<"yyy"<<endl;
						list *qwee = i->next;						
						list *prow = i->prev;					    
						prow->next = qwee;			
				    	qwee->prev = prow;
				    	qwee->next = i;
				    	i->next = NULL;
				    	i->prev = qwee;
				    	i = qwee;
				    	Tail = i->next;				    	
				    	qwee = NULL;
				    	prow = NULL;
				    	cout<<i->day<<endl;
				    	cout<<Tail->day<<endl;
					} 
					else			
					{
						cout<<"oooo "<<endl;
						list *qwee = i->next;
						list *prow = i->prev;
						list *lop = qwee->next;
					    prow->next = qwee;
					    lop->prev = i;
					    i->next = lop;
					    i->prev =qwee;					    
				    	qwee->prev = prow;			    					    	
				    	qwee->next = i;	
				    	i = qwee;
				    	lop = NULL;
				    	prow = NULL;				    	
				    	qwee = NULL;
					}									
				}			
			}	
			i = i->next	;
			cout<<"1  "<<endl;
		}
		RightMark=RightMark->prev;
	
/*		list *j=RightMark; //закоментила, чтобы отладить первую часть
		while(j->prev !=  leftMark)
		{ 
			if (Check(j,j->prev)) //
			{
				if(j == Tail)
				{
					list *woot = j->prev; 
					list *poot = woot->prev;					
					j->prev = poot;
					poot->next = j;
					woot->next = NULL;
					woot->prev = j;
					j->next = woot;
					j = woot;
					Tail = j;
					woot = NULL;					
					poot = NULL;
				}
				else 
				{
					list *woot = j->prev;
					if(woot == Head)	//îøèáêà
					{
						cout<<"ttt"<<endl;
						
						list *prow = j->next;
						prow->prev = woot;	
						woot->next = prow;
						woot->prev = j;
						j->next = woot;
						j->prev = NULL;
						Head = j;
						j = woot;
						woot = NULL;
						prow = NULL;						
			    	}
			    	else 
			    	{
			    		list *loop = j->next;
			    		list *qoot = woot->prev;
			    		qoot->next = j;
			    		j->prev = qoot;
			    		j->next = woot;
			    		loop->prev = woot;
			    		woot->prev = j;
			    		woot->next = loop;
			    		j = woot;
			    		woot = NULL;
			    		loop = NULL;
			    		qoot = NULL;
					}
				}
			}
			j = j->prev;
		} */
		leftMark=leftMark->next; 
		i = NULL; //хз
		//j=NULL;
//	}


}

int main() //основной код
{
	setlocale (LC_ALL,"Rus"); //русский язык
	Head = NULL; //голова
	Tail = NULL; //хвост	
	readFile(); //читаем данные
	myShakerSort(); //сортируем
	WriteStruct(); //записываем
	return 0;
}
