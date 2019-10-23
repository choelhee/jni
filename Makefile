.SUFFIXES: .cpp .c .o 


JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.212.b04-0.el7_6.x86_64
JRE_HOME=/usr/lib/jvm/jre-1.8.0-openjdk-1.8.0.212.b04-0.el7_6.x86_64

CC = g++
CFLAGS = -g -Wall 

LIB = $(JRE_HOME)/lib/amd64/server/libjvm.so

INC=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

OBJS=JDBCNativeInterface.o \
	DriverManager.o \
	Connection.o main.o \
	Statement.o \
	PreparedStatement.o \
	ResultSet.o

all:
		$(CC) $(CFLAGS) -c $(INC) JDBCNativeInterface.cpp
		$(CC) $(CFLAGS) -c $(INC) DriverManager.cpp
		$(CC) $(CFLAGS) -c $(INC) Connection.cpp
		$(CC) $(CFLAGS) -c $(INC) main.cpp
		$(CC) $(CFLAGS) -c $(INC) Statement.cpp
		$(CC) $(CFLAGS) -c $(INC) PreparedStatement.cpp
		$(CC) $(CFLAGS) -c $(INC) ResultSet.cpp
		$(CC) -o jnitest $(OBJS) $(LIB)

clean:
		rm -rf $(OBJS) jnitest 

