This is Readme to do the file IO

when we have file like "a.csv" 
we could use following step to read and write data


Suppose you have Class User 

step1 :  define a member in this class 
//user class
class User{
private:
  string fileName;  // the path and name of the file 
  fileIO &rf;         
}

step2 : in the constructor of user, initial the rf using :
//ctor of class user
User(string &name):filename(name),rf(fileIO::getInstance()){
    rf.setNameR(); // open the file in R for read mode
    rf.setNameW(); // open the file in W for write mode;
}

step3 : the in your function , you can 

//if you open the file in read mode: 
string line = rf.readLine() ;  // read a line in the file
string item = rf.readWordCsv(); //read one word ine the file

//if you open the file in write mode:
writeLable(string s)  // if s = "yes" ,will write   "yes," in your output file
writeArray(vector<T> &a) //write the an array in output,with "," to seperate the element




