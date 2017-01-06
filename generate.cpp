#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct method{
	string methodName;
	int argNum;
	string* argType;
	string returnType;
};

int main(int argc,char* argv[])
{
	ifstream fin(argv[1]);
	string className;
	int tracelength;
	int threadnum;
	int methodnum;
	fin>>className>>tracelength>>threadnum>>methodnum;
//	cout<<className<<tracelength<<threadnum<<methodnum;
	
	method* methodtest = new method[methodnum];
	
	for(int i =0;i < methodnum;i++){
		fin>>methodtest[i].methodName;
//		cout<<methodtest[i].methodName;
		fin>>methodtest[i].argNum;
		methodtest[i].argType = new string[methodtest[i].argNum];
		for(int j = 0;j< methodtest[i].argNum;j++){
			fin>>methodtest[i].argType[j];
		}
		fin>>methodtest[i].returnType;
	}
//	cout<<methodtest[0].methodName;
//	cout<<methodtest[1].methodName;
//	cout<<methodtest[1].argNum<<methodtest[1].returnType;
	ofstream fout;
	fout.open("TestThread.h");
	fout<<"#ifndef TESTTHREAD_H_"<<endl<<"#define TESTTHREAD_H_"<<endl;
	fout<<"#include \"MyThread.h\""<<endl;
	fout<<"#include \""<<className<<"/"<<className<<".h\""<<endl;
	fout<<"#include <iostream>"<<endl<<"#include <sys/time.h>"<<endl
		<<"#include <stdlib.h>"<<endl;
	fout<<"using namespace std;"<<endl<<endl;
	fout<<"class TestThread:public MyThread{"<<endl<<
		"private:"<<endl<<"\tint length;"<<endl<<
		"\tint* met_num;"<<endl<<"\tbool* if_suc;"<<endl<<
		"\tint* test_value;"<<endl<<"\ttimeval* start_time;"<<endl<<
		"\ttimeval* end_time;"<<endl<<"\ttimeval base_time;"<<endl<<
		"\t"<<className<<"* cl;"<<endl;

/*	fout<<	"\tvoid test1(int,int);"<<endl<<"\tvoid test2(int,int);"<<endl<<
		"\tvoid test3(int,int);"<<endl;*/
	for(int i = 0;i < methodnum;i++){
		fout<<"\tvoid test"<<(i+1)<<"(int,int);"<<endl;
	}
	fout<<"public:"<<endl<<"\tTestThread(int,"<<
		className<<"*,timeval);"<<endl<<
		"\tvoid run();"<<endl<<"\tvoid printRe();"<<endl<<
		"};"<<endl<<endl<<"#endif"<<endl;	
	fout.close();
	fout.open("TestThread.cpp");
	fout<<"#include \"TestThread.h\""<<endl<<endl;
	fout<<"TestThread::TestThread(int len,"<<className<<"* c,timeval b)"
		<<endl<<"\t:MyThread()"	<<endl<<
		"{"<<endl<<"\tlength = len;"<<endl<<
		"\tmet_num = new int[length];"<<endl<<
		"\tif_suc = new bool[length];"<<endl<<
		"\ttest_value = new int[length];"<<endl<<
		"\tstart_time = new timeval[length];"<<endl<<
		"\tend_time = new timeval[length];"<<endl<<
		"\tbase_time = b;"<<endl<<
		"\tcl = c;"<<endl<<
		"\tsrand(time(NULL));"<<endl<<
		"}"<<endl<<endl;
/*	fout<<"void TestThread::run()"<<endl<<
		"{"<<endl<<"\tfor(int i = 0;i < length; i++){"<<endl<<
		"\t\tswitch(rand()%"<<methodnum<<"){"<<endl<<
		"\t\tcase 0:"<<endl<<"\t\t\ttest1(rand()%100,i);"<<endl<<
		"\t\t\tbreak;"<<endl<<
		"\t\tcase 1:"<<endl<<"\t\t\ttest2(rand()%100,i);"<<endl<<
		"\t\t\tbreak;"<<endl<<
		"\t\tcase 2:"<<endl<<"\t\t\ttest3(rand()%100,i);"<<endl<<
		"\t\t\tbreak;"<<endl<<
		"\t\t}"<<endl<<"\t}"<<endl<<"}"<<endl<<endl;*/
	fout<<"void TestThread::run()"<<endl<<
		"{"<<endl<<"\tfor(int i = 0;i < length; i++){"<<endl<<
		"\t\tswitch(rand()%"<<methodnum<<"){"<<endl;
	for(int i = 0;i < methodnum;i++){
		fout<<"\t\tcase "<<i<<":"<<endl
		<<"\t\t\ttest"<<(i+1)<<"(rand()%100,i);"<<endl<<
		"\t\t\tbreak;"<<endl;
	}
	fout<<"\t\t}"<<endl<<"\t}"<<endl<<"}"<<endl<<endl;
		


	/*fout<<"void TestThread::test1(int value,int i)"<<endl<<"{"
		<<endl<<"\tgettimeofday(start_time+i,NULL);"<<endl<<
		"\tcl->add(value,&(if_suc[i]));"<<endl<<
		"\tgettimeofday(end_time+i,NULL);"<<endl<<
		"\ttest_value[i] = value;"<<endl<<
		"\tmet_num[i] = 0;"<<endl<<"}"<<endl<<endl;
	fout<<"void TestThread::test2(int value,int i)"<<endl<<"{"
		<<endl<<"\tgettimeofday(start_time+i,NULL);"<<endl<<
		"\tcl->remove(value,&(if_suc[i]));"<<endl<<
		"\tgettimeofday(end_time+i,NULL);"<<endl<<
		"\ttest_value[i] = value;"<<endl<<
		"\tmet_num[i] = 1;"<<endl<<"}"<<endl<<endl;
	fout<<"void TestThread::test3(int value,int i)"<<endl<<"{"
		<<endl<<"\tgettimeofday(start_time+i,NULL);"<<endl<<
		"\tcl->contains(value,&(if_suc[i]));"<<endl<<
		"\tgettimeofday(end_time+i,NULL)"<<endl<<
		"\ttest_value[i] = value;"<<endl<<
		"\tmet_num[i] = 2;"<<endl<<"}"<<endl<<endl;*/

	for(int i = 0;i < methodnum;i++){
		fout<<"void TestThread::test"<<(i+1)<<"(int value,int i)"<<endl
		<<"{"<<endl<<"\tgettimeofday(start_time+i,NULL);"<<endl;
////////////////////////////////////////////////////////////////////////////
//		fout<<"\tcl->"<<methodtest[i].methodName<<"(value,&if_suc[i]);"
//			<<endl;
		if(methodtest[i].returnType == "bool"){
			fout<<"\tif_suc[i] = "<<"cl->"<<
				methodtest[i].methodName<<"(value);"<<endl;

			fout<<"\tgettimeofday(end_time+i,NULL);"<<endl;
		fout<<"\ttest_value[i] = value;"<<endl;
		}else if(methodtest[i].returnType == "void"){
			fout<<"\tcl->"<<methodtest[i].methodName
				<<"(value);"<<endl;
	
			fout<<"\tgettimeofday(end_time+i,NULL);"<<endl;
			fout<<"\tif_suc[i] = true;"<<endl;
		fout<<"\ttest_value[i] = value;"<<endl;
		}else if(methodtest[i].returnType == "int"){
			fout<<"\tint val = cl->"<<methodtest[i].methodName
				<<"();"<<endl;
			fout<<"\tgettimeofday(end_time+i,NULL);"<<endl;
			fout<<"\tif(val == -1)"<<endl<<
				"\t\tif_suc[i] == false;"<<endl<<
				"\telse"<<endl<<"\t\tif_suc[i] = true;"<<endl;
		fout<<"\ttest_value[i] = val;"<<endl;
		}
//////////////////////////////////////////////////////////////////////////////
	//	fout<<"\tgettimeofday(end_time+i,NULL);"<<endl;
//		fout<<"\ttest_value[i] = value;"<<endl;
		fout<<"\tmet_num[i] = "<<i<<";"<<endl<<"}"<<endl<<endl;
	}


	fout<<"void TestThread::printRe()"<<endl<<"{"<<endl<<
		"\tcout<<\"thread \";"<<endl<<
		"\tfor(int i = 0;i < length; i++){"<<endl<<
		"\t\tcout<<met_num[i]<<\" \"<<if_suc[i]<<\" \"<<test_value[i]"<<		"<<\" \"<<((start_time[i].tv_sec-base_time.tv_sec)*1000000+start_time[i].tv_usec-base_time.tv_usec)<<\" \"<<"<<
		"((end_time[i].tv_sec-base_time.tv_sec)*1000000+end_time[i].tv_usec-base_time.tv_usec)<<endl;"<<endl<<"\t}"<<endl<<"}"<<endl;	
	fout.close();
	fout.open("test.cpp");
	fout<<"#include \""<<className<<"/"<<className<<".h\""<<endl<<
		"#include \"TestThread.h\""<<endl<<
		"#include <sys/time.h>"<<endl<<
		"#include <stdlib.h>"<<endl<<
		className<<" cl;"<<endl<<endl<<
		"int main()"<<endl<<"{"<<endl<<
		"\ttimeval base;"<<endl<<
		"\tgettimeofday(&base,NULL);"<<endl;
	
	//	"\tTestThread t1(200,&cl,base);"<<endl<<
	//	"\tTestThread t2(200,&cl,base);"<<endl<<
	
/*	fout<<	"\tt1.start();"<<endl<<
		"\tt2.start();"<<endl<<
		"\tt1.join();"<<endl<<
		"\tt2.join();"<<endl<<
		"\tt1.printRe();"<<endl<<
		"\tt2.printRe();"<<endl<<"}"<<endl;*/
	for(int i = 0; i < threadnum;i++){
		fout<<"\tTestThread t"<<i<<"("
			<<tracelength<<",&cl,base);"<<endl;
	}
	for(int i = 0;i < threadnum;i++){
		fout<<"\tt"<<i<<".start();"<<endl;
	}
	for(int i = 0; i < threadnum;i++){
		fout<<"\tt"<<i<<".join();"<<endl;
	}
	for(int i =0;i<threadnum;i++){
		fout<<"\tt"<<i<<".printRe();"<<endl;
	}
	fout<<"}"<<endl;
	
	fout.close();
	
	fout.open("test.sh");
	fout<<"g++ "<<className<<"/* TestThread.cpp MyThread.cpp test.cpp -pthread"<<endl;
	fout<<"rm "<<className<<"/*.gch"<<endl;
	fout<<"./a.out>result.txt"<<endl;
	fout.close();
}
	
	
