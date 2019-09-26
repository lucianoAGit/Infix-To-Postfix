#include <iostream>
#include <string>
#include "Expression.h"

using namespace std;

int main()
{
	
	while(true){
    string x;
    
	cout<< "-------------*INFIX TO POSTFIX CALCULATOR*-------------"<<endl;
	cout<<endl<<"Entre com a expressao infixa :P : "<<endl;
    getline(cin,x);
	
	Expression e(x);

        cout << "Infix: |" << e.getInfix()<< "|" << endl<< "Postfix: |" << e.getPostfix() << "|" << endl<< "Value: " << e.getValue()<< endl;

 

	}
    return 0;
}

