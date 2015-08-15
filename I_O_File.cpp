#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include <iomanip>

#define F_NAME "one.dat"   //File which stores the data
#define F_ID   "fid.dat"   // To generate automatatic ID
#define F_TEMP "temp.dat"


using namespace std;

class Employee{

private:
    int id;
    char name[20];
    int salary;

public:
    Employee() {}
    ~Employee() {}
    void setID(int tempid){
    id=tempid;
    }
    int getID(){
    return (id);
    }
    void  setData(){
    cout<<"\n Eingabe Name: ";
    cin.sync();
    cin.clear();
    cin.getline(name,20);
    //cin>>name;
    cin.sync();
    cin.clear();
    cout<<"\n Eingabe Gehalt: ";
    cin>>salary;
    }
   void display(){
   cout<<id;
   cout<<"\t"<<setw(20)<<name;
   cout<<"\t"<<setw(15)<<salary;
    }
};

/*See the description below*/
void createEmployee();
void displayAllEmployee();
void modifyEmployee();
void deleteEmployee();
void searchEmployee();
int getSizeofFile();
int getID();




int main(){

int ch;
while(1){

    cout<<"================================================================================================\n";

    cout<<"                                    Kunden Management                                           \n";

    cout<<"================================================================================================\n";
    cout<<endl<<endl;
    cout<<" [1] Neuer eintrag     \n";
    cout<<" [2] Eintrag aendern    \n";
    cout<<" [3] Eintrag loeschen   \n";
    cout<<" [4] Suche eintrag      \n";
    cout<<" [5] Bericht            \n";
    cout<<" [0] Abbrechen         \n";
    cout<<"\n\n";
    cout<<"=================================================================================================\n";
    cout<<"================================================================================================= \n";
    cout<<"\n\n \n\n";
    cout<<"Eingabe           ";
    cin>>ch;

switch(ch){
    case 1: createEmployee();
    break;
    case 2: modifyEmployee();
    break;
    case 3: deleteEmployee();
    break;
    case 4: searchEmployee();
    break;
    case 5: displayAllEmployee();
    break;
    case 0: exit(0);
         }
 }
return 0;
}
/* This function reads the value from Finfile to genereate automatic ID for each employee*/
int getID(){
ifstream fin(F_ID);
int value=0;
if(fin==NULL){

    fin.close();
    ofstream fout(F_ID);
    fout<<0;
    fout.close();
    fin.open(F_ID);
}
 fin>>value;
 fin.close();
 ofstream fout(F_ID);
 fout<<value+1;
 fout.close();
return (value+1);
}
/* This function get the size of a file*/
int getSizeofFile(){
    int msize;
    int total;
    Employee t1;
    ifstream fin(F_NAME);
    fin.seekg(0,ios::end);
    total=fin.tellg();
    fin.close();
    msize=total/sizeof(t1);
    return (msize);
}

void createEmployee(){
Employee t1;
fstream fout(F_NAME,ios::app|ios::out);
t1.setID(getID());
t1.setData();
fout.write((char*)&t1,sizeof(t1));
fout.close();
cout<<"\n\n\n\n\n";
}


void modifyEmployee(){
Employee t;
int msize=getSizeofFile();
fstream fout(F_NAME,ios::ate|ios::out|ios::in);
fout.seekg(0);
int id;
int counter=0;
cout<<"Eingeben ID: ";
cin>>id;
if(fout==NULL){
cout<<"\n ******* Kein eintrag gefunden! ******* \n";
}
else {
for(int i=0;i<msize;i++){

    fout.read((char *)&t,sizeof(t));
    if(id==t.getID()){

        int msize=fout.tellg();
        msize=msize-sizeof(t);
        fout.seekp(msize,ios::beg);
        Employee newobj=t;
        newobj.setData();
        fout.write((char*) &newobj,sizeof(newobj));
        counter=1;
        break;
       }
cout<<"\n";

   }
}
fout.close();
if(counter==0){
    cout<<"\n ********* Kein eintrag gefunden ********* \n";
}
else
{
    cout<<"\n ********* Eintrag geaendert *********\n";
}
cout<<"\n\n\n\n\n";
}

void deleteEmployee(){
Employee t;
int msize=getSizeofFile();
ifstream fin(F_NAME);
ofstream fout(F_TEMP);

int id;
int counter=0;
cout<<"Bitte zum loeschen ID eingeben: ";
cin>>id;
if(fin==NULL)
{
    cout<<"\n ******** Keine eintraege gefunden! **********\n";

}
else
{
    for(int i=0;i<msize;i++)
    {

        fin.read((char*)&t,sizeof(t));
        if(id==t.getID()){

            counter=1;
        }
        else {

            fout.write((char*)&t,sizeof(t));
              }
    }
}
fin.close();
fout.close();

if(counter==0){
    cout<<"\n ******* Sorry no record found ******* \n";
}
else{

    fin.open(F_TEMP);
    fout.open(F_NAME);
    for(int i=0;i<msize-1;i++){

        fin.read((char*)&t,sizeof(t));
        fout.write((char*)&t,sizeof(t));
    }
    fin.close();
    fout.close();
}
cout<<"\n\n\n\n\n";
}




void searchEmployee(){

Employee t;
int msize=getSizeofFile();
int id=0;
int counter=0;
cout<<"Eingabe ID : ";
cin>>id;

ifstream fin(F_NAME);
 cout<<"\n\n\n\n\n";
 cout<<"================================================================================================= \n";
 cout<<"\n                                    Detail                                                      \n";
 cout<<"================================================================================================= \n";
cout<<"ID\t\t\t Namen\t\t\t Salary \n\n";
for(int i=0;i<msize;i++){

    fin.read((char*)&t,sizeof(t));
    if(id==t.getID()){
        t.display();
        counter=1;

    }
    cout<<"\n";
}

fin.close();

if(counter==0){
    cout<<"\n *********** Kein eintrag gefunden!   \n";

}
cout<<"\n\n\n\n\n";
}
void displayAllEmployee(){
Employee t;
int msize=getSizeofFile();
ifstream fin(F_NAME);
if(fin==NULL)
{


    cout<<"\n***********   Keine Eintrag ************\n";
}
else {
    cout<<"\n\n\n\n\n";
    cout<<"================================================================================================ \n";
    cout<<"\n                                    Detail                                                       \n";
    cout<<"================================================================================================= \n";
    cout<<"ID \t\t\t Name\t\t\t Salary \n\n";


for(int i=0;i<msize;i++)
{
    fin.read((char*)&t,sizeof(t));
    t.display();
    cout<<"\n";

}
}
fin.close();
cout<<"\n\n\n\n\n";
}





