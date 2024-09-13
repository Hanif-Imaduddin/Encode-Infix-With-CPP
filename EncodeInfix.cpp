#include <iostream>

using namespace std;

#include <iostream>

struct Node{
	int data;
	Node *next;
};

class Queue{
	private:
		Node *head;
		Node *tail;
	public:
		int length;
		Queue() : head(nullptr),tail(nullptr),length(0){}
		
		void enqueue(int data){
			Node *temp = new Node();
			temp->data = data;
			if (this->tail == nullptr){
				this->head = this->tail = temp;
			}else{
				this->tail->next = temp;
				this->tail = this->tail->next;
			}
			this->length++;
		}
		
		int dequeue(){
			int data = -999;
			if (this->head == nullptr){
				return data;
			}else if (this->head->next == nullptr){
				data = this->head->data;
				delete this->head;
				this->head = nullptr;
				return data;
			}else{
				data = this->head->data;
				Node *temp = this->head->next;
				delete this->head;
				this->head = temp;
				return data;
			}
		}
};

string removeWhiteSpace(string str){
	string result;
	for (size_t i = 0;i < str.size();i++){
		if (str[i] != ' '){
			result += str[i];
		}
	}
	return result;
}

bool isNumber(char c){
	if (c >= '0' && c <= '9'){
		return true;
	}else{
		return false;
	} 
}

/*
	'(' = -1
	')' = -2
	'-' = -3/-8
	'^' = -4
	'*' = -5
	'/' = -6
	'+' = -7
*/

Queue encodeInfix(string infix){
	Queue infix_encoded;
	char temp;
	string numStr;
	numStr = "";
	
	for (size_t i = 0;i < infix.size();i++){
		temp = infix[i];
		if (isNumber(temp)){
			numStr += string() + temp;
		}else{
			if (numStr != ""){
				infix_encoded.enqueue(stoi(numStr));
				numStr = "";
			}
			if (temp == '-'){
				if (infix[i-1] == '('){
					infix_encoded.enqueue(-3);
				}else{
					infix_encoded.enqueue(-8);
				}
			}else if (temp == '('){
				infix_encoded.enqueue(-1);
			}else if (temp == ')'){
				infix_encoded.enqueue(-2);
			}else if (temp == '^'){
				infix_encoded.enqueue(-4);
			}else if (temp == '*'){
				infix_encoded.enqueue(-5);
			}else if (temp == '/'){
				infix_encoded.enqueue(-6);
			}else if (temp == '+'){
				infix_encoded.enqueue(-7);
			}else if (temp == '='){
				break;
			}
		}
	}
	if (numStr != ""){
		infix_encoded.enqueue(stoi(numStr));
		numStr = "";
	}
	return infix_encoded;
}

void printlnQueue(Queue Q){
	for (size_t i = 0;i < Q.length;i++){
		cout<<Q.dequeue()<<" ";
	}
	cout<<endl;
}

int main(){
	string infix;
	Queue infixQ;
	infix = "7 - 34 *((-22)-1/5)+10";
	infix = removeWhiteSpace(infix);
	infixQ = encodeInfix(infix);
	cout<<infix<<endl;
	printlnQueue(infixQ);
	return 0;
}