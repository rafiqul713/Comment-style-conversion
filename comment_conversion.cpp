/*
    Author: Rafiqul Islam
*/

#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<sstream>
#include <boost/algorithm/string/trim.hpp>
using namespace std;


void write_in_file(string file_name, string content){
  ofstream outfile(file_name.c_str());
  if(outfile.is_open()){
    outfile<<content;
    outfile.close();
    cout<<"Converted Successfully"<<endl;
  }
  else{
    cout<<"Can not open the file"<<endl;
  }

}


int INITIAL_STATE; //starting state and handle single line comment

int MULTILINE_COMMENT_STATE; // For handling multiline comment
                             // for example: /*
                             //                 this is multi-line comment
                             //               */

int INSIDE_STRING_STATE;     // For handling inside printf(" /*comment inside string*/")or
                             //cout<<"/* comment inside string */ "


int INSIDE_STRINTG_STATE_2;  // For handling C style printf("%d ",x /* handle this situation */)


int main(){
    string line; //read each line of string
    string output=""; //converted C++ comment
    string temp; //temporary variable
    string replace_with="//";
    ifstream input_file("sample.cpp"); // input file for example: sample.cpp
    if(!input_file){
        cout<<"Input file does not exist. Please give the correct file name"<<endl;
        return 0;
    }

    int len=0;
    INITIAL_STATE=true;
    MULTILINE_COMMENT_STATE=false;
    INSIDE_STRING_STATE=false;
    INSIDE_STRINTG_STATE_2=false;
    while (getline(input_file,line)){
        temp=line;
        boost::trim(temp); //remove white space
        temp=temp+"\n";
        len=temp.length()-1;
        for(int i=0;i<len;i++){

            //1: Initial state
            if(INITIAL_STATE==true){
                if(temp[i]=='/' && temp[i+1]=='*'){ // C-style comment found here
                    if(i+2<=temp.length() && temp[i+2]=='\n'){ // multiline comment exists
                        //handle multiline comment
                        temp[i]=' '; // replace C-style comment with white space
                        temp[i+1]=' ';
                        MULTILINE_COMMENT_STATE=true; // transfer handling to multiline state
                        INITIAL_STATE=false;
                    }

                    else{ //handle single line comment
                        temp[i]='/';
                        temp[i+1]='/';
                        INITIAL_STATE=true;
                    }
                }

                else if(temp[i]=='*' && temp[i+1]=='/'){ //reach end of the C-style comment
                   temp[i]=' ';
                   temp[i+1]=' ';
                }

                else if(temp[i]=='"'){ // comment found inside string or printf or cout
                    INSIDE_STRING_STATE=true;
                    INITIAL_STATE=false;
                    MULTILINE_COMMENT_STATE=false;
                }

                else if(temp[i]==','){ // handling C-style printf("",/*this case*/)
                    INSIDE_STRING_STATE=false;
                    INITIAL_STATE=false;
                    INSIDE_STRINTG_STATE_2=true;
                }
            }


            //2: Inside string state
            else if(INSIDE_STRING_STATE==true){ // handle comment inside string. for example: printf("hello /**/");
                if(temp[i]=='"'){ //found second "
                    //INSIDE_COMMENT_STATE=false;
                    INSIDE_STRING_STATE=false;
                    INITIAL_STATE=true;
                }
            }


            //3: Inside string state (for C-style printf )
            else if(INSIDE_STRINTG_STATE_2==true){
                if(temp[i]=='/' && temp[i+1]=='*'){
                    continue;
                }

                else if(temp[i]=='*' && temp[i+1]=='/'){
                    INSIDE_STRINTG_STATE_2=false;
                    INITIAL_STATE=true;
                }

            }

            //4: Multi-line comment state
            else if(MULTILINE_COMMENT_STATE==true){
                if(temp[i]=='*' && temp[i+1]=='/'){ // Reach end of the multi-line comment
                    temp[i]='/'; //C-style comment replace by C++ style
                    temp[i+1]='/';
                    MULTILINE_COMMENT_STATE=false;
                    INITIAL_STATE=true;
                }

                else{ // inside multi-line comment
                    temp="//"+temp;
                    i=i+2;
                    len=len+2;
                    break;
                }

            }
        }

        output+=temp;

    }

    write_in_file("sample.cpp",output);

    return 0;
}

