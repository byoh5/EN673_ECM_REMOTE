function [methodinfo,structs,enuminfo,ThunkLibName]=CLI_proto
%CLI_PROTO Create structures to define interfaces found in 'CLI'.

%This function was generated by loadlibrary.m parser version  on Tue Jan 23 14:05:37 2018
%perl options:'CLI.i -outfile=CLI_proto.m -thunkfile=CLI_thunk_pcwin64.c -header=CLI.h'
ival={cell(1,0)}; % change 0 to the actual number of functions to preallocate the data.
structs=[];enuminfo=[];fcnNum=1;
fcns=struct('name',ival,'calltype',ival,'LHS',ival,'RHS',ival,'alias',ival,'thunkname', ival);
MfilePath=fileparts(mfilename('fullpath'));
ThunkLibName=fullfile(MfilePath,'CLI_thunk_pcwin64');
%  int NetCon ( char * addr , char * port ); 
fcns.thunkname{fcnNum}='int32cstringcstringThunk';fcns.name{fcnNum}='NetCon'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'cstring', 'cstring'};fcnNum=fcnNum+1;
%  int NetClo ( int fd ); 
fcns.thunkname{fcnNum}='int32int32Thunk';fcns.name{fcnNum}='NetClo'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32'};fcnNum=fcnNum+1;
%  int getImagefromRemote ( int fd , int cnt ); 
fcns.thunkname{fcnNum}='int32int32int32Thunk';fcns.name{fcnNum}='getImagefromRemote'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32', 'int32'};fcnNum=fcnNum+1;
%  int getImgDataSizeFromList ( int n , int * size , void * data ); 
fcns.thunkname{fcnNum}='int32int32voidPtrvoidPtrThunk';fcns.name{fcnNum}='getImgDataSizeFromList'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32', 'int32Ptr', 'voidPtr'};fcnNum=fcnNum+1;
%  int getImgSizeFromList ( int n ); 
fcns.thunkname{fcnNum}='int32int32Thunk';fcns.name{fcnNum}='getImgSizeFromList'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32'};fcnNum=fcnNum+1;
%  int getImgDataFromList ( int n , void * data ); 
fcns.thunkname{fcnNum}='int32int32voidPtrThunk';fcns.name{fcnNum}='getImgDataFromList'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32', 'voidPtr'};fcnNum=fcnNum+1;
%  int deleteList_ALL ( void ); 
fcns.thunkname{fcnNum}='int32voidThunk';fcns.name{fcnNum}='deleteList_ALL'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
%  int getDataFromRemote ( int fd , int addr , int size , int module , void * value ); 
fcns.thunkname{fcnNum}='int32int32int32int32int32voidPtrThunk';fcns.name{fcnNum}='getDataFromRemote'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32', 'int32', 'int32', 'int32', 'voidPtr'};fcnNum=fcnNum+1;
%  int setDataFromRemote ( int fd , int addr , int size , int module , void * value ); 
fcns.thunkname{fcnNum}='int32int32int32int32int32voidPtrThunk';fcns.name{fcnNum}='setDataFromRemote'; fcns.calltype{fcnNum}='Thunk'; fcns.LHS{fcnNum}='int32'; fcns.RHS{fcnNum}={'int32', 'int32', 'int32', 'int32', 'voidPtr'};fcnNum=fcnNum+1;
methodinfo=fcns;