#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool isLetter(char ch){
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool isDigit(char ch){
  return (ch >= '0' && ch <= '9');
}

bool isOperator(char ch){
  vector<char> special_chars = {
    '+', '-', '*', '<', '>', '&', '.', 
    '@', '/', ':', '=', '~', '|', '$', 
    '!', '#', '%', '^', '_', '[', ']', 
    '{', '}', '"', '\'', '?'
  };

  return find(special_chars.begin(), special_chars.end(), ch) != special_chars.end();
}

bool check_identifier(string input){
  int states[2][3] = {{1,-1,-1},{1,1,1}};
  int i=0;
  int FINAL_STATE = 1;
  int state = 0;
  const int digit_size = 10;

  int length = input.length();

  int col = 0;
  while (i < length){
    char ch = input[i];

    if (isLetter(ch)){
      col = 0;
    }else if(isDigit(ch)){
      col = 1;
    }else if(ch == '_'){
      col = 2;
    }else{
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i+=1;
  } 

  if (state == FINAL_STATE){
    cout<<"<IDENTIFIER, "<<input<<">"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_integer(string input){
  int states[2][1] = {{1},{1}};
  int i=0;
  int FINAL_STATE = 1;
  int state = 0;
  const int digit_size = 10;

  int length = input.length();

  int col = 0;
  while (i < length){
    char ch = input[i];

    if(isDigit(ch)){
      col = 0;
    }else{
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i+=1;
  } 

  if (state == FINAL_STATE){
    cout<<"<INTEGER, "<<input<<">"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_operator(string input){
  int states[2][1] = {{1},{1}};
  int i=0;
  int FINAL_STATE = 1;
  int state = 0;
  const int digit_size = 10;

  int length = input.length();

  int col = 0;
  while (i < length){
    char ch = input[i];

    if(isOperator(ch)){
      col = 0;
    }else{
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i+=1;
  } 

  if (state == FINAL_STATE){
    cout<<"<OPERATOR, "<<input<<">"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_string(string input){
  int states[4][5] = {
    {1, -1, -1, -1, -1},  
    {-1, 2, -1, 1, 3},     
    {-1, -1, 1, -1, -1},   
    {-1, -1, -1, -1, -1}  
  };
  
  int i = 0;
  int FINAL_STATE = 3;
  int state = 0;
  int length = input.length();

  while (i < length){
    char ch = input[i];
    int col = -1;

    if (state == 0 && ch == '\''){
      col = 0; 
    }
    else if (state == 1){
      if (ch == '\''){
        col = 4; 
      }
      else if (ch == '\\'){
        col = 1; 
      }
      else if (ch == '(' || ch == ')' || ch == ';' || ch == ',' || ch == ' ' || 
               isLetter(ch) || isDigit(ch) || isOperator(ch)){
        col = 3; 
      }
    }
    else if (state == 2){
      if (ch == 't' || ch == 'n' || ch == '\\' || ch == '\''){
        col = 2; 
      }
    }

    if (col == -1){
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i++;
  }

  if (state == FINAL_STATE){
    cout<<"<STRING, "<<input<<">"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_whitespace(string input){
  
  int states[2][1] = {{1},{1}};
  int i = 0;
  int FINAL_STATE = 1;
  int state = 0;
  int length = input.length();

  if (length == 0){
    return false;
  }

  int col = 0;
  while (i < length){
    char ch = input[i];

    if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r'){
      col = 0;
    }else{
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i++;
  }

  if (state == FINAL_STATE){
    //cout<<"<DELETE>"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_comment(string input){
  int states[4][3] = {
    {1, -1, -1},
    {-1, 2, -1},
    {2, 2, 3},
    {-1, -1, -1}
  };
  
  int i = 0;
  int FINAL_STATE = 3;
  int state = 0;
  int length = input.length();

  while (i < length){
    char ch = input[i];
    int col = -1;

    if (state == 0 && ch == '/'){
      col = 0;
    }
    else if (state == 1 && ch == '/'){
      col = 1;
    }
    else if (state == 2){
      if (ch == '\n' || ch == '\r'){
        col = 2;
      }
      else if (ch == '\'' || ch == '(' || ch == ')' || ch == ';' || ch == ',' || 
               ch == '\\' || ch == ' ' || ch == '\t' || 
               isLetter(ch) || isDigit(ch) || isOperator(ch)){
        col = 1;
      }
    }

    if (col == -1){
      return false;
    }

    state = states[state][col];

    if (state == -1){
      return false;
    }
    i++;
  }

  if (state == FINAL_STATE){
    //cout<<"<DELETE>"<<endl;
    return true;
  }else{
    return false;
  }
}

bool check_punctuation(string input){
  if (input.length() != 1){
    return false;
  }
  
  char ch = input[0];
  if (ch == '(' || ch == ')' || ch == ';' || ch == ','){
    cout<<"<PUNCTUATION, \""<<ch<<"\">"<<endl;
    return true;
  }
  return false;
}

bool check_keyword(string input){
  vector<string> keywords = {
    "let", "where", "true", "false", "not", "fn", "ls", "gr", "ge", 
    "aug", "le", "nil", "dummy", "or", "in", "eq", "ne", "and", 
    "rec", "within"
  };
  
  // Convert input to lowercase for comparison
  string lower_input = input;
  transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);
  
  for (const string& keyword : keywords){
    if (lower_input == keyword){
      cout<<"<KEYWORD, "<<input<<">"<<endl;
      return true;
    }
  }
  return false;
}

void tokenize(string input){
  int i = 0;
  int length = input.length();
  
  while (i < length){
    string token = "";
    char ch = input[i];
    
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r'){
      token += ch;
      i++;
      while (i < length && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')){
        token += input[i];
        i++;
      }
      check_whitespace(token);
      continue;
    }
    
    if (ch == '/' && i + 1 < length && input[i + 1] == '/'){
      token += ch;
      i++;
      while (i < length && input[i] != '\n' && input[i] != '\r'){
        token += input[i];
        i++;
      }
      if (i < length){
        token += input[i];
        i++;
      }
      check_comment(token);
      continue;
    }
    
    if (ch == '\''){
      token += ch;
      i++;
      while (i < length){
        if (input[i] == '\\' && i + 1 < length){
          token += input[i];
          i++;
          token += input[i];
          i++;
        } else if (input[i] == '\''){
          token += input[i];
          i++;
          break;
        } else {
          token += input[i];
          i++;
        }
      }
      check_string(token);
      continue;
    }
    
    if (ch == '(' || ch == ')' || ch == ';' || ch == ','){
      token += ch;
      i++;
      check_punctuation(token);
      continue;
    }
    
    if (isLetter(ch)){
      token += ch;
      i++;
      while (i < length && (isLetter(input[i]) || isDigit(input[i]) || input[i] == '_')){
        token += input[i];
        i++;
      }
      if (!check_keyword(token)){
        check_identifier(token);
      }
      continue;
    }
    
    if (isDigit(ch)){
      token += ch;
      i++;
      while (i < length && isDigit(input[i])){
        token += input[i];
        i++;
      }
      check_integer(token);
      continue;
    }
    
    if (isOperator(ch)){
      token += ch;
      i++;
      while (i < length && isOperator(input[i]) && input[i] != '/' && input[i] != '\''){
        token += input[i];
        i++;
      }
      check_operator(token);
      continue;
    }
    
    i++;
  }
}

int main(){
  string filename;
  cout<<"Enter input file name: ";
  cin>>filename;
  
  ifstream inputFile(filename);
  if (!inputFile.is_open()){
    cout<<"Error: Could not open file "<<filename<<endl;
    return 1;
  }
  
  string line;
  string allInput = "";
  while (getline(inputFile, line)){
    allInput += line + "\n";
  }
  inputFile.close();
  
  tokenize(allInput);
  
  return 0;
}
