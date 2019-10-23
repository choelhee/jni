
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <jni.h>
#define TRUE 1 
static JNIEnv *s_env; 
static JavaVM *s_vm; 
static char s_url[1024]; 
static char s_driver[1024]; 

int main(int argc, char **argv) 
{ 
    jint res; 
    int nOpts = 0; 
    JavaVMOption options[10]; 
    JavaVMInitArgs vm_args; 

    options[nOpts++].optionString = "-Djava.compiler=NONE"; 

    vm_args.version = JNI_VERSION_1_4; 
    vm_args.options = options; 
    vm_args.nOptions = nOpts; 
    vm_args.ignoreUnrecognized = TRUE; 

    res = JNI_CreateJavaVM(&s_vm, (void **)&s_env, &vm_args); 
    if (res < 0) { 
        exit(0); 
    } 

    strcpy(s_url, "jdbc:mysql://localhost/test?user=test&password=test"); 
    strcpy(s_driver, "com.mysql.cj.jdbc.Driver"); 
    loadvia_forName(0); 
    if ((*s_env)->ExceptionOccurred(s_env) != NULL) { 
        (*s_env)->ExceptionDescribe(s_env); 
        (*s_env)->ExceptionClear(s_env); 
    } 
    loadvia_forName(1); 
    loadvia_DriverManager_getConnection(); 
    if ((*s_env)->ExceptionOccurred(s_env) != NULL) { 
        (*s_env)->ExceptionDescribe(s_env); 
        (*s_env)->ExceptionClear(s_env); 
    } 

    (*s_vm)->DestroyJavaVM(s_vm); 
    exit(-1); 
} 

void loadvia_forName(useClassLoader) 
    int useClassLoader; 
{ 
    char tmpbuf[1024]; 
    char methodname[512]; 
    char signature[512]; 
    char classname[512]; 
    jint init; 
    jstring oString; 
    jclass cDriverManager; 
    jclass cClass; 
    jobject oForName; 
    jmethodID mForName; 
    jclass cClassLoader; 
    jobject oClassLoader; 
    jmethodID mClassLoader; 

    /* Driver Class */ 
    oString = (*s_env)->NewStringUTF(s_env, s_driver); 

    /* Find class Class */ 
    strcpy(classname, "java/lang/Class"); 
    cClass = (*s_env)->FindClass(s_env, (char *)classname); 
    if (cClass == NULL) return; 

    /* Locate the driver manager */ 
    strcpy(classname, "java/sql/DriverManager"); 
    cDriverManager = (*s_env)->FindClass(s_env, classname); 
    if (cDriverManager == NULL) return; 

    if (useClassLoader) { 
        sprintf(tmpbuf, "\nLoad class '%s' via forName with ClassLoader()\n\n", s_driver); 
        fprintf(stderr, tmpbuf); 
        /* Create a ClassLoader object */ 
        strcpy(classname, "java/lang/ClassLoader"); 
        cClassLoader = (*s_env)->FindClass(s_env, (char *)classname); 
        if (cClassLoader == NULL) return; 
        strcpy(methodname, "getSystemClassLoader"); 
        sprintf(signature, 
                "(%s)%s", 
                "", 
                "Ljava/lang/ClassLoader;"); 
        mClassLoader = (*s_env)->GetStaticMethodID(s_env, 
                cClassLoader, 
                methodname, 
                signature); 
        if (mClassLoader == NULL) return; 
        oClassLoader = (*s_env)->CallStaticObjectMethod(s_env, 
                cClassLoader, 
                mClassLoader); 
        if (oClassLoader == NULL) return; 

        /* Create constructor. */ 
        strcpy(methodname, "forName"); 
        sprintf(signature, 
                "(%s)%s", 
                "Ljava/lang/String;ZLjava/lang/ClassLoader;", 
                "Ljava/lang/Class;"); 
        mForName = (*s_env)->GetStaticMethodID(s_env, cClass, methodname, signature); 
        if (mForName == NULL) return; 
        init = JNI_TRUE; 
        oForName = (*s_env)->CallStaticObjectMethod(s_env, 
                cClass, 
                mForName, 
                oString, 
                init, 
                oClassLoader); 
    } else { 
        sprintf(tmpbuf, "\nLoad class '%s' via forName\n\n", s_driver); 
        fprintf(stderr, tmpbuf); 
        /* Create constructor. */ 
        strcpy(methodname, "forName"); 
        sprintf(signature, 
                "(%s)%s", 
                "Ljava/lang/String;", 
                "Ljava/lang/Class;"); 
        mForName = (*s_env)->GetStaticMethodID(s_env, cClass, methodname, signature); 
        if (mForName == NULL) return; 
        oForName = (*s_env)->CallStaticObjectMethod(s_env, 
                cClass, 
                mForName, 
                oString); 
    } 
    if (oForName == NULL) return; 
} 

void loadvia_DriverManager_getConnection() 
{ 
    char methodname[512]; 
    char signature[512]; 
    char classname[512]; 
    jstring oString; 
    jclass cDriverManager; 
    jobject oConnection; 
    jmethodID mConnection; 

    fprintf(stderr, "Load Via Driver Manager\n\n"); 
    printf("Load Via Driver Manager\n"); 
    /* Locate the driver manager */ 
    strcpy(classname, "java/sql/DriverManager"); 
    cDriverManager = (*s_env)->FindClass(s_env, classname); 
    if (cDriverManager == NULL) return; 

    /* Locate the the Connection method */ 
    strcpy(methodname, "getConnection"); 
    sprintf(signature, 
            "(%s)%s", 
            "Ljava/lang/String;", 
            "Ljava/sql/Connection;"); 
    mConnection = (*s_env)->GetStaticMethodID(s_env, 
            cDriverManager, 
            methodname, 
            signature); 
    if (mConnection == NULL) return; 

    /*-----------------*/ 
    /* Connect to JDBC */ 
    /*-----------------*/ 
    oString = (*s_env)->NewStringUTF(s_env, s_url); 
    oConnection = (*s_env)->CallStaticObjectMethod(s_env, 
            cDriverManager, 
            mConnection, 
            oString); 
    if (oConnection == NULL) return; 
}
