/*
 * Copyright (C) 2023 Sergey Koshkin <koshkin.sergey@gmail.com>
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*******************************************************************************
 *  includes
 ******************************************************************************/

#include <errno.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/times.h>

/*******************************************************************************
 *  function prototypes (scope: module-exported)
 ******************************************************************************/

extern int _chown(const char* path, uid_t owner, gid_t group);
extern int _close(int fildes);
extern int _execve(char* name, char** argv, char** env);
extern int _fork(void);
extern int _fstat(int fildes, struct stat* st);
extern int _getpid(void);
extern int _gettimeofday(struct timeval* ptimeval, void* ptimezone);
extern int _isatty(int file);
extern int _kill(int pid, int sig);
extern int _link(char* existing, char* _new);
extern int _lseek(int file, int ptr, int dir);
extern int _open(char* file, int flags, int mode);
extern int _read(int file, char* ptr, int len);
extern int _readlink(const char* path, char* buf, size_t bufsize);
extern int _stat(const char* file, struct stat* st);
extern int _symlink(const char* path1, const char* path2);
extern int _unlink(char* name);
extern int _wait(int* status);
extern int _write(int file, char* ptr, int len);
extern clock_t _times(struct tms* buf);
extern void* _sbrk(int incr);

/*******************************************************************************
 *  function implementations (scope: module-exported)
 ******************************************************************************/

__attribute__((weak))
int _chown(const char* path __attribute__((unused)),
           uid_t owner __attribute__((unused)),
           gid_t group __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _close(int fildes __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _execve(char* name __attribute__((unused)), char** argv __attribute__((unused)),
            char** env __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _fork(void)
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _fstat(int fildes __attribute__((unused)),
           struct stat* st __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _getpid(void)
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _gettimeofday(struct timeval* ptimeval __attribute__((unused)),
                  void* ptimezone __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _isatty(int file __attribute__((unused)))
{
  errno = ENOSYS;
  return (0);
}

__attribute__((weak))
int _kill(int pid __attribute__((unused)), int sig __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _link(char* existing __attribute__((unused)),
          char* _new __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _lseek(int file __attribute__((unused)), int ptr __attribute__((unused)),
           int dir __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _open(char* file __attribute__((unused)), int flags __attribute__((unused)),
          int mode __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _read(int file __attribute__((unused)), char* ptr __attribute__((unused)),
          int len __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _readlink(const char* path __attribute__((unused)),
              char* buf __attribute__((unused)),
              size_t bufsize __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _stat(const char* file __attribute__((unused)),
          struct stat* st __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _symlink(const char* path1 __attribute__((unused)),
             const char* path2 __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
clock_t _times(struct tms* buf __attribute__((unused)))
{
  errno = ENOSYS;
  return ((clock_t) -1);
}

__attribute__((weak))
int _unlink(char* name __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _wait(int* status __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
int _write(int file __attribute__((unused)), char* ptr __attribute__((unused)),
           int len __attribute__((unused)))
{
  errno = ENOSYS;
  return (-1);
}

__attribute__((weak))
void* _sbrk(int incr)
{
  extern char end; /* Set by linker.  */
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &end;
  }

  prev_heap_end = heap_end;
  heap_end += incr;

  return ((void*)prev_heap_end);
}
