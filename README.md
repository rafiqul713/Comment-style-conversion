# Convert C-style Comment to C++ style comment

> **In the given example use C-style comment** 

> #include<iostream> <br />
> #include<cstdio> <br />
> using namespace std; <br />
> /* <br />
> 	This is multi-line comment <br />
> */ <br /> 


> /* This is single line comment */ <br />
> int main(){ <br /> 
>	cout<<" /* this is string */ "<<endl; <br />
>	printf("%d ",10 /* here print 10*/); <br /> 
>	return 0; <br />
>	/* successfully finished */ <br /> 
> } <br />

> **Now it is converted to** 

> #include<iostream> <br />
> #include<cstdio> <br />
> using namespace std;  <br />
> //  <br />
> //	This is multi-line comment <br />
> // <br />

> // This is single line comment  <br />
> int main(){ <br />
>	cout<<" /* this is string */ "<<endl; <br />
>	printf("%d ",10 /* here print 10*/); <br />
>	return 0; <br /> 
>	//successfully finished <br />
> } <br />
