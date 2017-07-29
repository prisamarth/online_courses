#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    Bracket error(' ',0);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
	    opening_brackets_stack.push(Bracket(next,(position+1)));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
	    if(opening_brackets_stack.empty())
	    {
	    	error.type = next;
		error.position = position+1;
		break;
	    }
	    else {
	    	Bracket open = opening_brackets_stack.top();
		opening_brackets_stack.pop();
	    	if(!open.Matchc(next))
	    	{
	    		error.type = next;
			error.position = position +1;
			break;
	    	}
	    }

        }
    }

    if (error.position != 0) {
	std::cout << error.position << std::endl;
	return 0;
    }

    while (!opening_brackets_stack.empty()) {
	    error = opening_brackets_stack.top();
	    opening_brackets_stack.pop();
    }

    if (error.position != 0)
	    std::cout << error.position << std::endl;
    	

    // Printing answer, write your code here

    return 0;
}
