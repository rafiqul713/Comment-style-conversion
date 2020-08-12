# Convert C-style Comment to C++ style comment

> **In the given example use C-style comment** 

> #include<iostream>
> #include<cstdio>
> using namespace std;
> /*
> 	This is multi-line comment
> */


> /* This is single line comment */
> int main(){
>	cout<<" /* this is string */ "<<endl;
>	printf("%d ",10 /* here print 10*/);
>	return 0;
>	/* successfully finished */
> }

> **Now it is converted to** 

> #include<iostream>
> #include<cstdio>
> using namespace s td;
> //
> //	This is multi-line comment
> //

> // This is single line comment 
> int main(){
>	cout<<" /* this is string */ "<<endl;
>	printf("%d ",10 /* here print 10*/);
>	return 0;
>	//successfully finished
> }
