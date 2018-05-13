using namespace System::Drawing;
//����� ����������� ������,��� ����������� ��������
class TRoot{
	bool visible,active;
public:
	virtual void Show(Graphics^ gr)= 0;
	virtual void Hide(Graphics^ gr)=0;
	virtual void Move(Graphics^ gr, int dx, int dy)=0;

};

//����� �����
class TPoint : public TRoot{
protected:
	int x,y;
public:
	TPoint(int x1,int y1)
	{
		x = x1;
		y = y1;
	}
	virtual void Show(Graphics^ gr)
	{}
	virtual void Hide(Graphics^ gr)
	{}
	virtual void Move(Graphics^ gr, int dx, int dy)
	{}
	

		//��������� �����
	
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	void SetX(int a)
	{
		 x=a;
	}
	void SetY(int a)
	{
		 y=a;
	}
};

