#include "rar.hpp"
#include <pthread.h>

typedef pthread_mutex_t* CRITSECT_HANDLE;
typedef pthread_t THREAD_HANDLE;
typedef void* (*NATIVE_THREAD_PTR)(void*);

static inline bool CriticalSectionCreate(CRITSECT_HANDLE *CritSection) {
  *CritSection = new pthread_mutex_t;
  return pthread_mutex_init(*CritSection, NULL) == 0;
}
static inline void CriticalSectionDelete(CRITSECT_HANDLE *CritSection) {
  if (*CritSection) {
    pthread_mutex_destroy(*CritSection);
    delete *CritSection;
    *CritSection = NULL;
  }
}
static inline void CriticalSectionStart(CRITSECT_HANDLE *CritSection) {
  if (*CritSection) pthread_mutex_lock(*CritSection);
}
static inline void CriticalSectionEnd(CRITSECT_HANDLE *CritSection) {
  if (*CritSection) pthread_mutex_unlock(*CritSection);
}
static inline THREAD_HANDLE ThreadCreate(NATIVE_THREAD_PTR Proc, void *Data) {
  pthread_t hThread;
  pthread_create(&hThread, NULL, Proc, Data);
  return hThread;
}
static inline void ThreadClose(THREAD_HANDLE hThread) {
  pthread_join(hThread, NULL);
}
