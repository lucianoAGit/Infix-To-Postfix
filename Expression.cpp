#include "Expression.h"
#include <string>
#include "StackTemplate.h"
#include <math.h>
using namespace std;

// pre: nenhuma
// pos: Dada expressao infixa expression, converte-a na notacao posfixa expression encontra seu valor
Expression::Expression(string expression)
{  setInfix(expression);
}

// pre: nenhuma
// pos: Dada expressao infixa s, converte-a na notacao posfixa e encontra seu valor
void Expression::setInfix(string expression)
{  infix = expression;
   infixToPostfix();
   evalPostfix();
}

// pre: objeto criado
// pos: retorna a expressao na notacao infixa
string Expression::getInfix()
{  return infix;
}

// pre: objeto criado
// pos: retorna a expressao na notacao posfixa (RPN)
string Expression::getPostfix()
{  return postfix;
}

// pre: objeto criado
// pos: retorna o valor da expressao na notacao posfixa (RPN)
int Expression::getValue()
{  return value;
}
//pré: Nenhuma.
//pos: Retorna o peso do operador.
//Função responsável por dar um "peso" aos operadores, para que seja possível organizar a precedencia.
int precedencia(char op){ 
    
	int peso; 
	
	switch(op){
	
		case '+':
		case '-':
				peso = 1;
				break;
		case '*':
		case '/':
		case '%':	
				peso = 2;
				break;
		case '^':
				peso = 3;
				break;
		case '(': //Menor prioridade pois deve ser excluido da notação POSFIXADA.
				peso = -2;
				break;
		default:
				peso = -1;
				break;
		}
	return peso;
}


// pre: infix contem uma expressao aritmetica valida, contendo operadores e digitos na notacao infixa
// pos: postfix contem a mesma expressao dada por infix, convertida na notacao pos-fixada (RPN)
void Expression::infixToPostfix()
{ Stack<char> s; // uma pilha de caracteres
  
 int i, tam_infix;
 char aux_top,aux_pop,aux_infix;
 string temp_post;
 
 tam_infix = infix.length();  

//Laço externo responsável por percorrer toda a string.
	for(i=0;i<tam_infix;i++){ 
			
			aux_infix = getInfix().at(i); //Encapsulamento.		
				
				if (isalpha(aux_infix)){
						cout<<"Entre com uma expressão Infixa valida, por favor."<<endl;
						abort();
				}
				 if(aux_infix != ' '){ //Caso a string tenha um espaço, o programa desconsidera.
					            	
					if (isdigit(aux_infix)) // Verifica se é um número, e se for coloca em POSTFIX.
			 			temp_post+= aux_infix;
			 
			 		else if (aux_infix == '(')			 
                		s.push(aux_infix);
				 	
					else if(aux_infix == ')'){
				
							if(!s.empty())
							s.getTop(aux_top); 				
						
							while(!s.empty() && aux_top!=  '(') { //Laço interno que coloca os elementos em POSTFIX, enquanto o topo não for ( E a pilha não esteja vazia.
									temp_post+= aux_top;
									s.pop(aux_pop);				
									if(!s.empty())
									s.getTop(aux_top);
									}							
								if(!s.empty()) 
								s.pop(aux_pop);
								}
   			 		else { //Se não for um parenteses, nem um número, é um operador.					
							
							if(s.empty())
								aux_top = 0;
							
							else if(!s.empty()){
								s.getTop(aux_top);
																	
								while(!s.empty() && precedencia(aux_infix) <= precedencia(aux_top)){ //Laço interno que organiza os operadores em POSTFIX, de acordo com a sua precedencia.						
										temp_post+= aux_top;
										s.pop(aux_pop);							
										if(!s.empty())
										s.getTop(aux_top);
									}					
								
								}
							s.push(aux_infix);																		
						}						                   
		
				}

	}
//Laço responsável por retirar todos os elementos restantes da pilha e colocar em POSTFIX.
   	
	while(!s.empty()){	
        s.pop(aux_pop);
		temp_post+= aux_pop;
       }
 postfix = temp_post;
}

// pre: postfix contem a expressao na notacao posfixa
// pos: retorna o valor da expressao, utilzando Algoritmo 2
void Expression::evalPostfix()
{
// Para declarar uma pilha usando templates, associe o tipo de dado colocado na mesma 
Stack<int>  s; // um pilha de inteiros

int i,x,valor_1, valor_2, tam_postfix;

tam_postfix = postfix.length();

	if(tam_postfix == 0){
		value = 0;
	} 
		else if(tam_postfix == 1 && !isdigit(postfix[0])) //Caso a pessoa digite apenas um operador, o valor = 0
				value = 0;
		

//Laço externo que percorre toda a string POSTFIX.	
	for(i=0;i<tam_postfix;i++){
		
		if (isdigit(postfix[i])){ 
				x = postfix[i] - '0'; //Faz a conversão de um char para Int, necessário para dar PUSH na pilha de inteiros e realizar os calculos.
				s.push(x);
				if(tam_postfix == 1){
						s.pop(valor_1);
						value = valor_1;
					}
			}
		 
		 if(tam_postfix > 1 ){
								
			switch (postfix[i]){ //Comando switch verifica qual operação é necessária e retorna o valor em OP e coloca OP na pilha, para a próxima operação.
	       		    
				case '+':
	           			s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 0;	
						s.push(valor_2 + valor_1);
						break;
			
				case '-':
	            		s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 0;	
	        			s.push(valor_2 - valor_1);
						break;
			
				case '*':
	           			s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 0;	
	        			s.push(valor_2 * valor_1);
						break;
			
				case '/':
	            		s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 0;	
	        			s.push(valor_2 / valor_1);
						break;
			
				case '^':
	        			s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 1;	
	        			s.push(pow(valor_2,valor_1));
						break;
			
				case '%':
	        			s.pop(valor_1);
	            		if(!s.empty()){
						s.pop(valor_2);
	        			}
	        			 else
						 	valor_2 = 0;	
	        			s.push(valor_2 % valor_1);
						break;
	   			default:
					 	break; 				
				}
		}
	
	}
	if(!s.empty()) //Se a pilha não for vazia, retorna o valor do topo, que contém a resposta das operações.
		s.getTop(value);

}
