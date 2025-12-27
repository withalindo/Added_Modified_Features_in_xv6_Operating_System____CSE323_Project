#define SBRK_ERROR ((char *)-1)

struct stat;
struct hapinfo;

// system calls
int fork(void);
int exit(int status) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int read(int, void*, int);
int kill(int);
int exec(const char*, char**);
int fstat(int fd, struct stat*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sys_sbrk(int,int);
int hapinfo(struct hapinfo *hi);
int pause(int);
int uptime(void);
int open(const char*, int);
int write(int, const void*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int link(const char*, const char*);
int mkdir(const char*);
int close(int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
char* sbrk(int);
char* sbrklazy(int);

// printf.c
void fprintf(int fd, const char* fmt, ...);
void printf(const char* fmt, ...);

// umalloc.c
void* malloc(uint);
void free(void*);
