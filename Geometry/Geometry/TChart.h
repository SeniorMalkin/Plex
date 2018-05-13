#include "TRoot.h"
#include <stack>
#include <vector>
#include <string>
#include <fstream>

//using namespace std;
using namespace System::Drawing;
class TChart;
struct Record {
	int num;
	int xB;
	int yB;
	int xE;
	int yE;
	bool visible;
};
struct TCurrLine{
	TChart* tc;
	TPoint* pB;
	TPoint* pE;
	int deeplevel;
};

class TChart: public TRoot
{

protected:
	TRoot * pBegin, *pEnd;
	TChart* pRes;
	bool visible;
	std::stack<TCurrLine> st;
	
	
	

	virtual void Hide(Graphics^ gr)
	{

	}
	virtual void Move(Graphics^ gr, int dx, int dy)
	{

	}

	TRoot* Show(Graphics^ gr,TRoot* curr)
	{
		TPoint * tp, *pB,*pE;
		tp = dynamic_cast<TPoint*>(curr);
		TChart* tc;
		if(tp)
		{
			tp->Show(gr);
			return tp;
		}
		tc = dynamic_cast<TChart*>(curr);
		if(tc)
		{
			pB = dynamic_cast<TPoint*>(Show(gr, tc->GetBegin()));
			pE = dynamic_cast<TPoint*>(Show(gr, tc->GetEnd()));
			if (pB != NULL && pE != NULL)
			{
				gr->DrawLine(Pens::Black, pB->GetX(), pB->GetY(), pE->GetX(), pE->GetY());
				return tc;
			}
		}
		return 0;

	}

	
	public:
		bool first;
		TChart(TRoot* pB = NULL, TRoot* pE = NULL)
		{
			visible = true;
		}
		void Unvisible()
		{
			visible = false;
		}
		void SetBegin(TRoot* pB)
		{
			TPoint* tp = dynamic_cast<TPoint*>(pB);
			TChart* tc = dynamic_cast<TChart*>(pB);
			if (tp != NULL || tc != NULL)
			{
				pBegin = pB;
			}
		}
		void SetEnd(TRoot* pB)
		{
			TPoint* tp = dynamic_cast<TPoint*>(pB);
			TChart* tc = dynamic_cast<TChart*>(pB);
			if (tp != NULL || tc != NULL)
			{
				pEnd = pB;
			}
		}
		TRoot* GetBegin()
		{
			return pBegin;
		}

		TRoot* GetEnd()
		{
			return pEnd;
		}
		TChart* GetRes()
		{
			return pRes;
		}
		void CheckStruct()
		{
			std::ofstream fout("glog.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
			TCurrLine curr;
			TPoint *tmp;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			curr.deeplevel = 0;
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				//if (curr.deeplevel != 0)
				//	curr.deeplevel--;
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
						curr.deeplevel++;
						//curr.pE = NULL;
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						curr.deeplevel++;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					if (curr.tc->visible || curr.pB->GetX() == -1000 || curr.pE->GetX() == -1000)
					fout << curr.deeplevel << '\n' << curr.pB->GetX() << '\n' << curr.pB->GetY() << '\n' << curr.pE->GetX() << '\n' << curr.pE->GetY()<< '\n' << curr.tc->visible << std::endl;
					tmp = curr.pE;
					curr.deeplevel--;
					if (!st.empty())
					{
						curr = st.top();
						st.pop();
						if (curr.pB == NULL)
						{
							curr.pB = tmp;
						}
						else
						{

							curr.pE = tmp;
						}
						st.push(curr);
					}
				}
			}
			fout.close();
		}
		TChart* FindLine(Graphics^ gr, double x, double y)
		{
			double a, b,c;
			TCurrLine curr;
			TChart* res = new TChart();
			TPoint *tmp;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					
					double k1, k2;
					bool bx, by;
					bx = ((x > (double)curr.pB->GetX()) && (x < (double)curr.pE->GetX())) || ((x < (double)curr.pB->GetX()) && (x > (double)curr.pE->GetX()));
					by = ((y >(double)curr.pB->GetY()) && (y < (double)curr.pE->GetY())) || ((y < (double)curr.pB->GetY()) && (y >(double)curr.pE->GetY()));
					/*
					double t,l;
					t = (
						(x - (double)curr.pB->GetX()) *
						((double)curr.pE->GetX() - (double)curr.pB->GetX()) +
						(y - (double)curr.pB->GetY()) *
						((double)curr.pE->GetY() - (double)curr.pB->GetX())
						) / (
						((double)curr.pE->GetX() - (double)curr.pB->GetX()) *
							((double)curr.pE->GetX() - (double)curr.pB->GetX()) +
							((double)curr.pE->GetY() - (double)curr.pB->GetX()) *
							((double)curr.pE->GetY() - (double)curr.pB->GetX())
							);
					if (t <= 0)
						t = 0;
					if (t > 1)
						t = 1;
					l = sqrt(
						(
						((double)curr.pB->GetX() - x) +
						((double)curr.pE->GetX() - (double)curr.pB->GetX())*t
						)*
						(
						((double)curr.pB->GetX() - x) +
						((double)curr.pE->GetX() - (double)curr.pB->GetX())*t
						)
						+
						(
						((double)curr.pB->GetY() - y) +
						((double)curr.pE->GetY() - (double)curr.pB->GetY())*t
						)*
						(
						((double)curr.pB->GetY() - y) +
						((double)curr.pE->GetY() - (double)curr.pB->GetY())*t
						)
					);
					*/
					a = sqrt(
						((double)curr.pB->GetY() - (double)curr.pE->GetY()) * ((double)curr.pB->GetY() - (double)curr.pE->GetY()) +
						((double)curr.pB->GetX() - (double)curr.pE->GetX()) * ((double)curr.pB->GetX() - (double)curr.pE->GetX())
					);
					b = sqrt(
						(y - (double)curr.pE->GetY()) * (y - (double)curr.pE->GetY()) +
						(x - (double)curr.pE->GetX()) * (x - (double)curr.pE->GetX())
					);
					c = sqrt(
						((double)curr.pB->GetY() - y) * ((double)curr.pB->GetY() - y) +
						((double)curr.pB->GetX() - x) * ((double)curr.pB->GetX() - x)
					);
					k1 = (a + b + c) / 2;
					k2 = sqrt(k1*(k1 - a)*(k1 - b)*(k1 - c));
					k2 = (2 * k2) / a;
					if ( k2 < 20 && curr.tc->visible && bx && by)
					{
						gr->DrawLine(Pens::BlueViolet, curr.pB->GetX(), curr.pB->GetY()+2, curr.pE->GetX(), curr.pE->GetY()+2);
						gr->DrawLine(Pens::BlueViolet, curr.pB->GetX(), curr.pB->GetY() - 2, curr.pE->GetX(), curr.pE->GetY() - 2);
						curr.tc->visible = false;
						res->SetBegin(curr.pB);
						res->SetEnd(curr.pE);
						//return res;
					}
					tmp = curr.pE;
					if (st.empty())
						continue;
					curr = st.top();
					st.pop();
					if (curr.pB == NULL)
					{
						curr.pB = tmp;
					}
					else
					{

						curr.pE = tmp;
					}
					st.push(curr);
				}

			} 
			return res;
		}
		std::vector<TPoint*> FindFriends(Graphics^ gr, int x, int y)
		{
			TCurrLine curr;
			TPoint *tmp, *p1, *p2;
			TChart* res;
			std::vector<TPoint*>* arrpoint = new std::vector<TPoint*>;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					if ((curr.pB->GetX() == x) && (curr.pB->GetY() == y) && curr.tc->visible /*(curr.pB->GetX() != -1000) && (curr.pE->GetX() != -1000)*/)
					{
						TPoint* ress = new TPoint(curr.pE->GetX(), curr.pE->GetY());
						arrpoint->push_back(ress);
					}
					if ((curr.pE->GetX() == x) && (curr.pE->GetY() == y) && curr.tc->visible /*(curr.pB->GetX() != -1000) && (curr.pE->GetX() != -1000)*/)
					{
						TPoint* ress = new TPoint(curr.pB->GetX(), curr.pB->GetY());
						arrpoint->push_back(ress);
					}
					/*
					if ((abs((curr.pE->GetX()) - x) < 20) && (abs((curr.pE->GetY()) - y) < 20))
					{
						int x = curr.pE->GetX();
						int y = curr.pE->GetY();
						//first = false;
						curr.pE->SetX(curr_x);
						curr.pE->SetY(curr_y);
						res = curr.tc;
						//p2 = dynamic_cast<TPoint*>(res->GetEnd());
						p1 = dynamic_cast<TPoint*>(res->GetBegin());
						if (p1 == NULL)
						{
							res = dynamic_cast<TChart*>(res->GetBegin());
							do
							{
								p1 = dynamic_cast<TPoint*>(res->GetEnd());
								if (p1 == NULL)
									res = dynamic_cast<TChart*>(res->GetEnd());
							} while (p1 == NULL);


						}
						TPoint* ress = new TPoint(p1->GetX(), p1->GetY());
						arrpoint->push_back(ress);

						//gr->DrawLine(Pens::White, p1->GetX(), p1->GetY(), x, y);
						//gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), curr.pE->GetX(), curr.pE->GetY());
						//return true;
					}
					if ((abs((curr.pB->GetX()) - x) < 20) && (abs((curr.pB->GetY()) - y) < 20))
					{
						int x = curr.pB->GetX();
						int y = curr.pB->GetY();
						//first = true;
						curr.pB->SetX(curr_x);
						curr.pB->SetY(curr_y);
						res = curr.tc;
						//p1 = dynamic_cast<TPoint*>(res->GetBegin());
						p2 = dynamic_cast<TPoint*>(res->GetEnd());
						while (p2 == NULL)
						{
							res = dynamic_cast<TChart*>(res->GetEnd());
							p2 = dynamic_cast<TPoint*>(res->GetEnd());
						}
						TPoint* ress = new TPoint(p2->GetX(), p2->GetY());
						arrpoint->push_back(ress);

						//gr->DrawLine(Pens::Black,x,y, p2->GetX(), p2->GetY());
						//gr->DrawLine(Pens::Black, curr.pB->GetX(), curr.pB->GetY(), p2->GetX(), p2->GetY());
						//return true;
					}
					*/
					tmp = curr.pE;
					if (st.empty())
						continue;
					curr = st.top();
					st.pop();
					if (curr.pB == NULL)
					{
						curr.pB = tmp;
					}
					else
					{

						curr.pE = tmp;
					}
					st.push(curr);
				}

			}

			return *arrpoint;
		}
		std::vector<TPoint*> Bias(Graphics^ gr, int curr_x, int curr_y,int x,int y)
		{
			TCurrLine curr;
			TPoint *tmp, *p1, *p2;
			TChart* res;
			std::vector<TPoint*>* arrpoint = new std::vector<TPoint*>;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					if ((curr.pB->GetX() == x) && (curr.pB->GetY() == y))
					{
						curr.pB->SetX(curr_x);
						curr.pB->SetY(curr_y);
					}
					if ((curr.pE->GetX() == x) && (curr.pE->GetY() == y))
					{
						curr.pE->SetX(curr_x);
						curr.pE->SetY(curr_y);
					}
					/*
					if ((abs((curr.pE->GetX()) - x) < 20) && (abs((curr.pE->GetY()) - y) < 20))
					{
						int x = curr.pE->GetX();
						int y = curr.pE->GetY();
						//first = false;
						curr.pE->SetX(curr_x);
						curr.pE->SetY(curr_y);
						res = curr.tc;
						//p2 = dynamic_cast<TPoint*>(res->GetEnd());
						p1 = dynamic_cast<TPoint*>(res->GetBegin());
						if (p1 == NULL)
						{
							res = dynamic_cast<TChart*>(res->GetBegin());
							do
							{
								p1 = dynamic_cast<TPoint*>(res->GetEnd());
								if (p1 == NULL)
									res = dynamic_cast<TChart*>(res->GetEnd());
							} while (p1 == NULL);
							
							
						}
						TPoint* ress = new TPoint(p1->GetX(),p1->GetY());
						arrpoint->push_back(ress);
						
						//gr->DrawLine(Pens::White, p1->GetX(), p1->GetY(), x, y);
						//gr->DrawLine(Pens::Black, p1->GetX(), p1->GetY(), curr.pE->GetX(), curr.pE->GetY());
						//return true;
					}
					if ((abs((curr.pB->GetX()) - x) < 20) && (abs((curr.pB->GetY()) - y) < 20))
					{
						int x = curr.pB->GetX();
						int y = curr.pB->GetY();
						//first = true;
						curr.pB->SetX(curr_x);
						curr.pB->SetY(curr_y);
						res = curr.tc;
						//p1 = dynamic_cast<TPoint*>(res->GetBegin());
						p2 = dynamic_cast<TPoint*>(res->GetEnd());
						while (p2 == NULL)
						{
							res = dynamic_cast<TChart*>(res->GetEnd());
							p2 = dynamic_cast<TPoint*>(res->GetEnd());
						}
						TPoint* ress = new TPoint(p2->GetX(), p2->GetY());
						arrpoint->push_back(ress);
						
						//gr->DrawLine(Pens::Black,x,y, p2->GetX(), p2->GetY());
						//gr->DrawLine(Pens::Black, curr.pB->GetX(), curr.pB->GetY(), p2->GetX(), p2->GetY());
						//return true;
					}
					*/
					tmp = curr.pE;
					if (st.empty())
						continue;
					curr = st.top();
					st.pop();
					if (curr.pB == NULL)
					{
						curr.pB = tmp;
					}
					else
					{

						curr.pE = tmp;
					}
					st.push(curr);
				}

			}

			return *arrpoint;
		}
		void Show(Graphics^ gr)
		{
			TCurrLine curr;
			TPoint *tmp;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			SolidBrush^ br = gcnew SolidBrush(Color::Black);
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
						//curr.pE = NULL;
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					if (curr.pB->GetX()==-1000 || curr.pE->GetX()==-1000)
						curr.tc->visible = false;
					if(curr.tc->visible)
					gr->DrawLine(Pens::Black, curr.pB->GetX(), curr.pB->GetY(), curr.pE->GetX(), curr.pE->GetY());
					gr->FillEllipse(br, System::Drawing::Rectangle::Rectangle(curr.pB->GetX() - 4, curr.pB->GetY() - 4, 8, 8));
					gr->FillEllipse(br, System::Drawing::Rectangle::Rectangle(curr.pE->GetX() - 4, curr.pE->GetY() - 4, 8, 8));
					tmp = curr.pE;
					if (!st.empty())
					{
						curr = st.top();
						st.pop();
						if (curr.pB == NULL)
						{
							curr.pB = tmp;
						}
						else
						{

							curr.pE = tmp;
						}
						st.push(curr);
					}
				}
			}
			delete br;
		}

		bool Find(int _x, int _y)
		{
			TCurrLine curr;
			TPoint *tmp;
			curr.tc = this;
			curr.pB = curr.pE = NULL;
			while (!st.empty())
				st.pop();
			st.push(curr);
			while (!st.empty())
			{
				curr = st.top();
				st.pop();
				while (curr.pB == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetBegin());
					if (tmp != NULL)
						curr.pB = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>((curr.tc)->GetBegin());
					}
				}
				if (curr.pE == NULL)
				{
					tmp = dynamic_cast<TPoint*>(curr.tc->GetEnd());
					if (tmp != NULL)
						curr.pE = tmp;
					else
					{
						st.push(curr);
						curr.tc = dynamic_cast<TChart*>(curr.tc->GetEnd());
						curr.pB = NULL;
						st.push(curr);
					}
				}
				if (curr.pB && curr.pE)
				{
					if ((abs((curr.pE->GetX()) - _x) < 20) && (abs((curr.pE->GetY()) - _y) < 20))
					{
						pRes = curr.tc;
						first = false;
						return true;
					}
					if ((abs((curr.pB->GetX()) - _x) < 20) && (abs((curr.pB->GetY()) - _y) < 20))
					{
						pRes = curr.tc;
						first = true;
						return true;
					}
					tmp = curr.pE;
					if (st.empty())
						continue;
					curr = st.top();
					st.pop();
					if (curr.pB == NULL)
					{
						curr.pB = tmp;
					}
					else
					{

						curr.pE = tmp;
					}
					st.push(curr);
				}

			}
			return false;
		}
};