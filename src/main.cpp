#include <stdio.h>

//needed for mkdir:
#include <sys/stat.h>
#include <sys/types.h>

//needed for execl:
#include <unistd.h>

#include <string>

#include <string.h> //for strerror


#include <sys/wait.h>  //for waitpid

//for a file like a/b/c/stuff.png, return stuff
std::string get_basename(const char * s)
{
     //find the last period:
     long unsigned int len = strlen(s);
     long unsigned int dot_index = len-1; 
     for (long unsigned int i=len-1; i >= 0; --i)
     {
          if (s[i] == '.')
          {
              dot_index = i;
              break;
          }
     } 
     //find the final slash:
     long unsigned int last_slash = 0;
     /*for (long unsigned int i=len-1; i >=0; --i)
     {
         if (s[i] == '/')
         {
             last_slash = i;
             break;
         }
     }*/ //TODO - enable this
     int has_slash = 0; // TODO - bad
     std::string ret;
     //fprintf(stderr,"last slash = %lu, dot index = %lu\n",last_slash,dot_index);
     long unsigned int start = 0;
     if (has_slash)
         start = last_slash + 1;
     for (long unsigned int i=start; i<dot_index; ++i)
     {
         ret += s[i];
     }
     return ret;
}

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        fprintf(stderr,"Usage: %s [texfile]\n",argv[0]);
        return -1;
    }
    const char * texfile = argv[1]; 

    //fprintf(stderr,"strlen of tex file is %lu\n",strlen(texfile));
    //get the basename of the texfile:
    std::string basename = get_basename(texfile);
    //fprintf(stderr,"basename = %s\n",basename.c_str());
    // create a temporary directory rooted at the current directory:
    char tempdir[256] = "abcdefghijklmnop";
    mkdir(tempdir, 0777);    
    
    
    //run tex:
    int pid = fork();
    if (pid == 0)
    {
        const char * texbin = "/usr/bin/tex";
        char * const args[5] = {const_cast<char *>(texbin), "--output-directory",tempdir,const_cast<char *>(texfile),NULL};
        fprintf(stderr,"executing:");
        for (int i=0; i<5; ++i)
            fprintf(stderr," %s",args[i]);
        fprintf(stderr,"\n");
        if (execv(texbin,args))
        {
            fprintf(stderr,"%s\n",strerror(errno));
            return -1;
        }
    }
    else
    {
        int wstatus;
        waitpid(pid,&wstatus,0);
    }
    
    //run dvipng:
    pid = fork();
    if (pid == 0)
    {
        const char * dvibin = "/usr/bin/dvipng";
    
        std::string s = std::string(tempdir)+"/"+basename+"%d.png";
        std::string t = std::string(tempdir)+"/"+basename+".dvi";
        char * const args2[5] = {const_cast<char *>(dvibin), "-o",const_cast<char *>(s.c_str()),const_cast<char *>(t.c_str()),NULL};
        fprintf(stderr,"executing:");
        for (int i=0; i<5; ++i)
            fprintf(stderr," %s",args2[i]);
        fprintf(stderr,"\n");
        if (execv(dvibin,args2))
        {
            fprintf(stderr,"%s failed: %s\n",dvibin,strerror(errno));
            return -1;
        }
    }
    else
    {
        int wstatus;
        waitpid(pid,&wstatus,0);
    }    
}
