#include <iostream>
#include <cassert>
using namespace std;

template<class T>			
class SA;
template<class T>			
ostream& operator <<(ostream& os, SA<T> s);
template<class T>			
class safeArrayMatrix;
template<class T>			
ostream& operator <<(ostream& os, safeArrayMatrix<T> s);

template<class T>
class SA
{
	private:
		int low, high;		
		T* p;				
	
	public:
	
		SA()											
		{
			low = 0;
			high = -1;
			p = NULL;
		}
		
		
		SA(int l, int h)									
		{
			if((h-l+1)<=0)												
			{
				cerr << "constructor error in bounds definition" << endl;
				exit(1);
			}
			low = l;
			high = h;
			p = new T[h-l+1];
		}
		
		
		SA(int size)										
		{
			low = 0;
			high = size - 1;
			p = new T[size];
		}
		
		
		SA(const SA& s)								
		{
			int size = s.high - s.low + 1;
			p = new T[size];
			for(int i=0; i<size; i++)
			{
				p[i] = s.p[i];
			}
			low = s.low;
			high = s.high;
		}
		
	
		~SA()											
		{
			delete[] p;
		}
		
	
		T& operator [](int i)							
		{
			if(i<low || i>high)				
			{
				cerr << "index" << i << "out of range" << endl;
				exit(1);
			}
			return p[i-low];
		}
		
		
		SA& operator =(const SA s)
		{
			if(this == &s)
				return *this;
			delete[] p;
			int size = s.high - s.low + 1;
			p = new T[size];
			for(int i=0; i<size; i++)
			{
				p[i] =s.p[i];
			}
			low = s.low;
			high = s.high;
			return *this;
		}
		
		
		friend ostream& operator << <T>(ostream& os, SA<T> s);
};


template<class T>
ostream& operator <<(ostream& os, SA<T> s)
{
	int size = s.high - s.low + 1;
	for(int i=0; i<size; i++)
		os << s.p[i] <<" ";
		os<< endl;
	return os;
}


template<class T>
class safeArrayMatrix
{
	private:
		int rowl, rowh, colL, colH;		
		SA<SA<T> > p;							
		
	public:
		safeArrayMatrix(int row, int col)
		{
			if(row<=0 || col<=0)			
			{
				cerr << "invalid construction" << endl;
				exit(1);
			}
			else if(row == col)			
			{
				int size = row;
				rowl = colL = 0;
				rowh = colH = size - 1;
				p = SA<SA<T> > (size);			
				for(int i=0; i<size; i++)
					p[i] = SA<T> (size);		
			}
			else								
			{
				rowl = colL = 0;
				rowh = row - 1;
				colH = col - 1;
				p = SA<SA<T> > (row);		
				for(int i=0; i<row; i++)
					p[i] = SA<T> (col);		
			}
		}
		
		
		safeArrayMatrix(int y_l, int y_h, int x_l, int x_h)
		{
			if(((y_h-y_l+1)<=0) || ((x_h-x_l+1)<=0))	
			{
				cerr << "out of bounds" << endl;
				exit(1);
			}
			rowl = y_l;
			rowh = y_h;
			colL = x_l;
			colH = x_h;
			p = SA<SA<T> > (rowl,rowh);		
			for(int i=rowl; i<=rowh; i++)
				p[i] = SA<T> (colL,colH);	
		}
		
		
		SA<T>& operator [](int i)
		{
			if(i<rowl || i>rowh)				
			{
				cerr << "out of bounds" << rowl << rowh << i << endl;
				exit(1);
			}
			return p[i];
		}
		
		safeArrayMatrix<T> operator *(safeArrayMatrix& s)
		{
			if(((colH)-(colL)+1) != (((s.rowh)-(s.rowl)))+1)	
			{
				cerr << "Cant perform multiplication on given matrices" << endl;
				exit(1);	
			}
			int leftsiderow = rowh - rowl + 1;	
			int leftsidecol = colH - colL + 1;
			int rightsiderow = s.rowh - s.rowl + 1;
			int rightsidecol = s.colH - s.colL + 1;	
			safeArrayMatrix<int> newMatrix(leftsiderow,rightsidecol);
			for(int y=0; y<leftsiderow; y++)			
			{
				for(int x=0; x<rightsidecol; x++)
				{
					newMatrix[y][x] = 0;
				}
			}
			for(int y=0; y<leftsiderow; y++)			
			{
				for(int x=0; x<rightsidecol; x++)
				{
					for(int run=0; run<rightsiderow; run++)
					{
						newMatrix[y][x] += (*this)[y+rowl][run+colL] * s[run+s.rowl][x+s.colL];
					}
				}
			}
			return newMatrix;
		}

		friend ostream& operator << <T>(ostream& os, safeArrayMatrix<T> s);		
};


template<class T>
ostream& operator <<(ostream& os, safeArrayMatrix<T> s)
{
	int row = s.rowh - s.rowl + 1;
	for(int y=s.rowl; y<=s.rowh; y++)		
	{
		os << s[y];
	}
	return os;
}

int main()
{
    int a [4];
    int b [4];
	
    cout<< "enter lower and upper bounds for rows and collums for first matrix" <<endl;
    
    for(int i = 0; i < 4; i++)
    {
        cin>>a[i];
    }
    int c = ((a[1]-a[0])+1) * ((a[3]-a[2])+1);
    int size[c];
    int fill = 0;
    int v = a[0];
	int n = a[2];
	int g =a[2];
    safeArrayMatrix <int> z(a[0],a[1],a[2],a[3]);
	
    for( int i = 0;  i <= (a[1]-a[0]); i++)
    {
        for(int j = 0; j <= (a[3]-a[2]); j++)
        {

            cout<<"fill the matrix for ["<<v<<"]"<<"["<<n<<"]"  <<endl;
            cin>>size[fill];
            z[v][n]=size[fill];
            fill++;
			n++;
        }
		n=g;
		v++;
        
    }
	
    cout<< z;
    cout<< "enter lower and upper bounds for rows and collums for second matrix" <<endl;
   

     for(int f = 0; f < 4; f++)
    {
        cin>>b[f];
    }
	
    safeArrayMatrix <int> d (b[0],b[1],b[2],b[3]);

	int sizeofd =((b[1]-b[2])+1) * ((b[3]-b[2])+1);
	int sizearyd [sizeofd];
	int fill2 = 0;
	int l = b[0];
	int nm = b[2];
	int nmn= b[2];
	for(int i = 0; i <= (b[1]-b[0]); i++)
	{
		for(int x = 0; x <= (b[3]-b[2]); x++)
		{	
			cout << "fill the matrix for ["<<l<<"]"<<"["<<nm<<"]" <<endl;
			cin >> sizearyd[fill2];
			d[l][nm] = sizearyd[fill2];
			fill2++;
			nm++;
		}
		nm=nmn;
		l++;
		
	}
    cout << "This is your second matrices"<<endl;
    cout<<d;
    
    safeArrayMatrix<int>result =z*d;
	
    cout<<"this is your matrix after multiplication" <<endl;
	cout<<result;
	
    return 0;	
}