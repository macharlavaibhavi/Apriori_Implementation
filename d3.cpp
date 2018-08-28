#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define structure map<vector<int> ,int>
#define for_map(ii,T) for(structure::iterator(ii)=(T).begin();(ii)!=(T).end();ii++)
#define for_next(jj,ii,T) for(structure::iterator(jj)=ii;(jj)!=T.end();jj++)
#define Vec vector<int>
const int min_sup=2;
structure c;
structure l;
void c1();
void l1();
void generate_C();
void generate_L();
void output(structure );

void prune();
void scan();
void set_count(Vec );
bool check(Vec,Vec);
int main()
{
	c.clear();
	l.clear();
	bool mv=true;
	int index=2;
	while(true)
	{
		if(mv)
		{
			c1();
			cout<<"C1\n";
			output(c);
			l1();
			cout<<"L1\n";
			output(l);
			mv=!mv;
		}
		else
		{
			generate_C();
			if(c.size()==0)
			break;
			cout<<"\nC"<<index<<"\n";
			output(c);
			prune();
			if(c.size()==0)
			break;
			cout<<"\n C"<<index<<"after prune\n";
			output(c);
			scan();
			cout<<"\nC"<<index<<"after scanning the datafrom file\n";
			output(c);
			generate_L();
			if(l.size()==0)
			break;
			cout<<"\nL"<<index<<"\n";
			output(l);
			index++;
		}
	}
	return 0;
}
void c1()
{   
	ifstream f2("file1.txt");
	if(!f2)
	{
		cout<<"file does not exit\n";
		return;
	}
		char str[255];
	map<int,vector<int> >m;
	
			m.clear();
			int n;
	while(f2)
    {
    f2.getline(str,255);
	 n=sizeof(str)/sizeof(str[0]);
        if(f2)
        	{  
			int j=0,i=0;
    		while(str[i]!='-')
    		{
    			j=j*10+(str[i]-'0');
    			i++;
			}
			i=i+2;
			while(i<n)
			{	
				int k=0;
			
				while(str[i]!=','&& str[i]!='/')
				{
					k=k*10+(str[i]-'0');
					i++;
				}
			  m[j].push_back(k);
			  i++;
			  if(str[i]=='/')
			  break;
			}
		}
		}
		f2.close();
		Vec v;
		
	  map<int,vector<int> >::iterator itr;
	  for(itr=m.begin();itr!=m.end();itr++)
	  {
	  	int l=itr->second.size();
	  	 
	  	for(int i=0;i<l;i++)
	  	{    v.clear();
	  		v.push_back(itr->second[i]);
	  		if(c.count(v)>0)
	  		c[v]++;
	  		else
	  		c[v]=1;
		  }
		
	  }
		
}
void output(structure T)
{
	cout<<"\n";
	Vec v;
	cout<<"itemset\t\tfrequency\n";
	for_map(ii,T)
	{
		v.clear();
		v=ii->first;
		int i;
		for( i=0;i<v.size()-1;i++)
		{
			cout<<v[i]<<",";
		}
		cout<<v[i]<<"\t\t";
		cout<<ii->second;
		cout<<"\n";
	}
}
void l1()
{
	for_map(ii,c)
	{
		if(ii->second>=min_sup)
		{
			l[ii->first]=ii->second;
		}
	}
}

void generate_C()
{
	c.clear();
	for_map(ii,l)
	{
		for_next(jj,ii,l)
		{
			if(jj==ii)
			continue;
			Vec a,b;
			a.clear();
			b.clear();
			a=ii->first;
			b=jj->first;
			if(check(a,b))
			{
				a.push_back(b.back());
				sort(a.begin(),a.end());
				c[a]=0;
			}
			
		}
	}
}

bool check(Vec a,Vec b)
{
	bool compare=true;
	for(int i=0;i<a.size()-1;i++)
	{
		if(a[i]!=b[i])
		{
			compare=false;
			break;
		}
	}
	return compare;
}

void prune()
{
	Vec a,b;
	for_map(ii,c)
	{
		a.clear();
		b.clear();
		a=ii->first;
		for(int i=0;i<a.size();i++)
		{
			b.clear();
			for(int j=0;j<a.size();++j)
			{
				if(j==i)
				continue;
				b.push_back(a[j]);
			}
			if(l.find(b)==l.end())
			{
				ii->second=-1;
				break;
			}
		}
	}
	structure temp;
	temp.clear();
	for_map(ii,c)
	{
		if(ii->second!=-1)
		{
			temp[ii->first]=ii->second;
		}
	}
	c.clear();
	c=temp;
	temp.clear();
}
	
	void scan()
	{
		ifstream f2("file1.txt");
	if(!f2)
	{
		cout<<"file does not exit\n";
		return;
	}
		char str[255];
	map<int,vector<int> >m;
	
			m.clear();
			int n;
	while(f2)
    {
    f2.getline(str,255);
	 n=sizeof(str)/sizeof(str[0]);
        if(f2)
        	{  
			int j=0,i=0;
    		while(str[i]!='-')
    		{
    			j=j*10+(str[i]-'0');
    			i++;
			}
			i=i+2;
			while(i<n)
			{	
				int k=0;
			
				while(str[i]!=','&& str[i]!='/')
				{
					k=k*10+(str[i]-'0');
					i++;
				}
			  m[j].push_back(k);
			  i++;
			  if(str[i]=='/')
			  break;
			}
		}
		}
		f2.close();
		Vec a;
		map<int,vector<int> >::iterator itr;
		for(itr=m.begin();itr!=m.end();itr++)
		{
			a=itr->second;
           set_count(a);
           a.clear();
		}
	}
	void set_count(Vec a)
	{
		for_map(ii,c)
		{
			Vec b;
			b.clear();
			b=ii->first;
			int true_count=0;
			if(b.size()<=a.size())
			{
			for(int  i=0;i<b.size();i++)
			{
				for(int j=0;j<a.size();j++)
				{
					if(b[j]==a[j])
					{
						true_count++;
						break;
					}
				}
				}	
			}
			if(true_count==b.size())
			{
				ii->second++;
			}
		}
	}
	
	void generate_L()
	{
		l.clear();
		for_map(ii,c)
		{
			if(ii->second>=min_sup)
			{
				l[ii->first]=ii->second;
			}
		}
	}
	

